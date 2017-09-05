//
// Copyright (c) 1991-2016 by STEP Tools Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Author: Samson Bonfante (bonfante@steptools.com)
//

#include "nodeMachineState.h"
#include "nodeUtils.h"
#include <stp_schema.h>

StixSimGeomType GeomTypeFromString(char* typ)
{
    if (!strcmp(typ, "MESH"))
    {
	return STIXSIM_GT_MESH;
    }
    if (!strcmp(typ, "POLYLINE"))
    {
	return STIXSIM_GT_POLYLINE;
    }
    else
    {
	return STIXSIM_GT_NULL;
    }
}
v8::Local<v8::Object> makeProbeResult(double probe_contact_pt[3], double probe_loc[3]) {
	    v8::Local<v8::Object> proberesult = Nan::New<v8::Object>();
	    v8::Local<v8::Array> contact = Nan::New<v8::Array>();
	    contact->Set(0, Nan::New(probe_contact_pt[0]));
	    contact->Set(1, Nan::New(probe_contact_pt[1]));
	    contact->Set(2, Nan::New(probe_contact_pt[2]));
	    v8::Local<v8::Array> location = Nan::New<v8::Array>();
	    location->Set(0, Nan::New(probe_loc[0]));
	    location->Set(1, Nan::New(probe_loc[1]));
	    location->Set(2, Nan::New(probe_loc[2]));
	    Nan::Set(proberesult, CharTov8String("location"), location);
	    Nan::Set(proberesult, CharTov8String("contact"), contact);
	    return proberesult;
}

typedef struct { 
    /*SECRETLY A Nan::Global<v8::Promise::Resolver>* */
    void* pmise; 
    double rtn; 
    bool more;
    bool probe_hit;
    double probe_contact_pt[3];
    double probe_loc[3];
} waitstruct;
std::vector<waitstruct> promisepool;
uv_mutex_t pp_mutex;
void messager(uv_async_t *hanlde) {

    uv_mutex_lock(&pp_mutex);
    v8::HandleScope handle(v8::Isolate::GetCurrent());
    for(auto v:promisepool){
	auto ppmise = (Nan::Global<v8::Promise::Resolver>*)v.pmise;
	v8::Local<v8::Number> valrtn = Nan::New(v.rtn);
	v8::Local<v8::Boolean> morertn = Nan::New(v.more);
	v8::Local<v8::Object> rtn = Nan::New<v8::Object>();
	Nan::Set(rtn,CharTov8String("value"), valrtn);
	Nan::Set(rtn, CharTov8String("more"), morertn);
	if (v.probe_hit) { //Probe result!
	    v8::Local <v8::Object> proberesult = makeProbeResult(v.probe_contact_pt,v.probe_loc);
	    Nan::Set(rtn, CharTov8String("probe"), proberesult);
	}
	v8::Local<v8::Promise::Resolver> pmise = Nan::New(*(ppmise));
	//TODO:FIXME: The Resolve does NOT cause the event loop to fire a tick.
	//If node is just waiting for this promise, it will continue waiting until something else happens.
	pmise->Resolve(rtn);
	ppmise->Reset();
	delete v.pmise;
    }
    promisepool.clear();
    uv_mutex_unlock(&pp_mutex);
}
void __waiterFunction(void* arg) {
    machineState * ms = static_cast<machineState*>(arg);
    ms->Wait();
}
void machineState::Wait() {
    bool wait = true;
    while (wait) {
	waitstruct waiter;
	wait = _ms->WaitForStateUpdate(waiter.pmise, waiter.rtn,waiter.more,waiter.probe_hit,waiter.probe_contact_pt,waiter.probe_loc);
	if (waiter.pmise == nullptr) continue; //Oops.
	uv_mutex_lock(&pp_mutex);
	promisepool.push_back(waiter);
	uv_mutex_unlock(&pp_mutex);
	uv_async_send(&async);
	if (!wait) return;
    }
}


NAN_METHOD(machineState::New)
{

    if (info.IsConstructCall()){
    	if (info.Length() == 0){
    	    return;
    	}
        else if(info.Length() == 1 || (info.Length() == 2 && info[1]->BooleanValue() == false)){
	    char * b;
	    v8StringToChar(info[0], b);
	    machineState * ms = new machineState();
	    ms->_ms = MachineState::InitializeState(b);
	    delete[] b;
	    ms->Wrap(info.This());
	    info.GetReturnValue().Set(info.This());
        }
        else if(info.Length() == 2){
            char * b;
            v8StringToChar(info[0], b);
            bool c = info[1]->BooleanValue();
            machineState * ms = new machineState();
            ms->_ms = MachineState::InitializeState(b, c);
            delete[] b;
	    uv_async_init(uv_default_loop(), &ms->async, messager);
	    uv_thread_create(&ms->waitqueue, __waiterFunction, (void*)ms);
	    uv_mutex_init(&pp_mutex);
	    ms->Wrap(info.This());
            info.GetReturnValue().Set(info.This());
        }
	else if (info.Length() == 3) {
            char * fname;
            v8StringToChar(info[0], fname);
	    char * toolfname;
	    v8StringToChar(info[2], toolfname);
            bool c = info[1]->BooleanValue();
            machineState * ms = new machineState();
            ms->_ms = MachineState::InitializeState(fname, c,toolfname);
            delete[] fname;
	    delete[] toolfname;
	    uv_async_init(uv_default_loop(), &ms->async, messager);
	    uv_thread_create(&ms->waitqueue, __waiterFunction, (void*)ms);
	    uv_mutex_init(&pp_mutex);
	    ms->Wrap(info.This());
            info.GetReturnValue().Set(info.This());
	}
	else if (info.Length() == 4) {
            char * fname;
            v8StringToChar(info[0], fname);
			char * toolfname;
			v8StringToChar(info[2], toolfname);
			bool c = info[1]->BooleanValue();
			bool coloring = info[3]->BooleanValue();
            machineState * ms = new machineState();
            ms->_ms = MachineState::InitializeState(fname, c,toolfname,coloring);
            delete[] fname;
			delete[] toolfname;
			uv_async_init(uv_default_loop(), &ms->async, messager);
			uv_thread_create(&ms->waitqueue, __waiterFunction, (void*)ms);
			uv_mutex_init(&pp_mutex);
			ms->Wrap(info.This());
			info.GetReturnValue().Set(info.This());
		
	}
        else{
            return;
        }
    }
    else{
	return;
    }
}

NAN_METHOD(machineState::AdvanceState)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (!info[0]->IsUndefined()) return; //This function takes no arguments.
    v8::Local<v8::Promise::Resolver> pmise = v8::Promise::Resolver::New(info.GetIsolate());
    auto pased = new Nan::Global<v8::Promise::Resolver>(pmise);
    pased->Reset(pmise);
    ms->_ms->AdvanceState((pased));
    info.GetReturnValue().Set(pmise->GetPromise());
    return;
}

NAN_METHOD(machineState::AdvanceStateByT)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (info.Length()!=1) return; //This function takes one argument.
	if (!info[0]->IsNumber()) return;

    double t = Nan::To<double>(info[0]).FromJust();
    v8::Local<v8::Promise::Resolver> pmise = v8::Promise::Resolver::New(info.GetIsolate());
    auto pased = new Nan::Global<v8::Promise::Resolver>(pmise);
    pased->Reset(pmise);
    ms->_ms->AdvanceStateByT(t,(pased));
    info.GetReturnValue().Set(pmise->GetPromise());
    return;
}

NAN_METHOD(machineState::GetGeometryJSON)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    //This function has a 2 argument and a no argument version.
    if (info.Length() == 0)
    {
	RoseStringObject rtn;
	ms->_ms->GetGeometryJSON(rtn);
	auto rtnpmise = v8::Promise::Resolver::New(info.GetIsolate());
	rtnpmise->Resolve(CharTov8String(rtn.as_const()));
	info.GetReturnValue().Set(rtnpmise->GetPromise());
	return;
    }
    else
    {
	if (info.Length() != 2) return; // invalid number of arguments
	if (info[0]->IsUndefined()) return; //No Given ID
	if (info[1]->IsUndefined()) return; //No Given Typ
	if (!info[0]->IsString()) return; //ID is not valid
	if (!info[1]->IsString()) return; //Typ is not valid
	char * id;
	v8StringToChar(info[0], id);
	RoseObject * obj = ms->_ms->FindObjectByID(id);
	if (!obj)
	{
	    delete[] id;
	    return; //No Object Associated with given ID
	}
	char * typ;
	v8StringToChar(info[1], typ);
	RoseStringObject rtn;
	ms->_ms->GetGeometryJSON(rtn, id, obj, GeomTypeFromString(typ));
	auto rtnpmise = v8::Promise::Resolver::New(info.GetIsolate());
	rtnpmise->Resolve(CharTov8String(rtn.as_const()));
	info.GetReturnValue().Set(rtnpmise->GetPromise());
	delete[] id;
	delete[] typ;
	return;
    }
}

NAN_METHOD(machineState::GetDynamicGeometryJSON)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (info.Length() != 1) //Function takes one argument
	return;
    if (!info[0]->IsNumber()) { // argument of wrong type
	return;
    }
    int in = Nan::To<int32_t>(info[0]).FromJust();
    RoseStringObject rtn;
    ms->_ms->GetDynamicGeometryJSON(rtn, in);
	auto rtnpmise = v8::Promise::Resolver::New(info.GetIsolate());
	rtnpmise->Resolve(CharTov8String(rtn.as_const()));
	info.GetReturnValue().Set(rtnpmise->GetPromise());
    return;
}

NAN_METHOD(machineState::WriteDynamicGeometrySTEP)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (info.Length() != 1) //Function takes one argument
	return;
    if (!info[0]->IsString()) { // argument of wrong type
	return;
    }
    char * fname;
    v8StringToChar(info[0], fname);
    ms->_ms->ExportDynamicGeometrySTEP(fname);
	auto rtnpmise = v8::Promise::Resolver::New(info.GetIsolate());
	rtnpmise->Resolve(Nan::Null());
	info.GetReturnValue().Set(rtnpmise->GetPromise());
    return;
}

NAN_METHOD(machineState::GetDynamicGeometryVersion)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (!info[0]->IsUndefined()) return; //This function takes no arguments.
    int rtnval = ms->_ms->GetDynamicGeometryVersion();

	auto rtnpmise = v8::Promise::Resolver::New(info.GetIsolate());
	rtnpmise->Resolve(Nan::New(rtnval));
	info.GetReturnValue().Set(rtnpmise->GetPromise());
    return;
}

NAN_METHOD(machineState::ResetDynamicGeometry)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (!info[0]->IsUndefined()) return; //This function takes no arguments.
    ms->_ms->ResetDynamicGeometry();
	auto rtnpmise = v8::Promise::Resolver::New(info.GetIsolate());
	rtnpmise->Resolve(Nan::Null());
	info.GetReturnValue().Set(rtnpmise->GetPromise());
    return;
}

NAN_METHOD(machineState::GetDeltaStateJSON)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (!info[0]->IsUndefined()) return; //This function takes no arguments.
    RoseStringObject rtn;
    ms->_ms->GetStateJSON(rtn,false);
	auto rtnpmise = v8::Promise::Resolver::New(info.GetIsolate());
	rtnpmise->Resolve(CharTov8String(rtn.as_const()));
	info.GetReturnValue().Set(rtnpmise->GetPromise());
    return;
}

NAN_METHOD(machineState::GetKeyStateJSON)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (!info[0]->IsUndefined()) return; //This function takes no arguments.
    RoseStringObject rtn;
    ms->_ms->GetStateJSON(rtn,true);
	auto rtnpmise = v8::Promise::Resolver::New(info.GetIsolate());
	rtnpmise->Resolve(CharTov8String(rtn.as_const()));
	info.GetReturnValue().Set(rtnpmise->GetPromise());
    return;
}

NAN_METHOD(machineState::GoToWS)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (info.Length() != 1) //Function takes one argument
	return;
    RoseObject * obj = ms->_ms->design()->findByEntityId(Nan::To<int32_t>(info[0]).FromJust());
    if (!obj)
	return;
    stp_machining_workingstep * ws = ROSE_CAST(stp_machining_workingstep, obj);
    if(!ws)
	return;

    v8::Local<v8::Promise::Resolver> localpmise = v8::Promise::Resolver::New(info.GetIsolate());
    auto globalpmise = new Nan::Global<v8::Promise::Resolver>(localpmise);
    globalpmise->Reset(localpmise);
    ms->_ms->GoToWS(ws,(globalpmise));
    info.GetReturnValue().Set(localpmise->GetPromise());
    return;
}

NAN_METHOD(machineState::GetEIDfromUUID)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (info.Length() != 1) //Function takes one argument
	return;
    if(!info[0]->IsString())
	return;
    char * uuid = 0;
    v8StringToChar(info[0], uuid);
    RoseObject * obj = ms->_ms->FindObjectByID(uuid);
    if (!obj)
	return;
    int rtnval = obj->entity_id();
	auto rtnpmise = v8::Promise::Resolver::New(info.GetIsolate());
	rtnpmise->Resolve(Nan::New(rtnval));
	info.GetReturnValue().Set(rtnpmise->GetPromise());
    return;
}

NAN_METHOD(machineState::NextWS)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (!info[0]->IsUndefined()) return; //This function takes no arguments.
    v8::Local<v8::Promise::Resolver> localpmise = v8::Promise::Resolver::New(info.GetIsolate());
    auto globalpmise = new Nan::Global<v8::Promise::Resolver>(localpmise);
    globalpmise->Reset(localpmise);
    ms->_ms->GoToNextWS((globalpmise));
    info.GetReturnValue().Set(localpmise->GetPromise());
    return;
}

NAN_METHOD(machineState::PrevWS)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (!info[0]->IsUndefined()) return; //This function takes no arguments.
    v8::Local<v8::Promise::Resolver> localpmise = v8::Promise::Resolver::New(info.GetIsolate());
    auto globalpmise = new Nan::Global<v8::Promise::Resolver>(localpmise);
    globalpmise->Reset(localpmise);
    ms->_ms->GoToPrevWS((globalpmise));
    info.GetReturnValue().Set(localpmise->GetPromise());
    return;
}

NAN_METHOD(machineState::GetPrevWSID)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (!info[0]->IsUndefined()) return; //This function takes no arguments.
    int id = ms->_ms->GetPrevWSID();
	auto rtnpmise = v8::Promise::Resolver::New(info.GetIsolate());
	rtnpmise->Resolve(Nan::New(id));
	info.GetReturnValue().Set(rtnpmise->GetPromise());
    return;
}

NAN_METHOD(machineState::GetWSID)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (!info[0]->IsUndefined()) return; //This function takes no arguments.
    int id = ms->_ms->GetWSID();
	auto rtnpmise = v8::Promise::Resolver::New(info.GetIsolate());
	rtnpmise->Resolve(Nan::New(id));
	info.GetReturnValue().Set(rtnpmise->GetPromise());
    return;
}

NAN_METHOD(machineState::GetNextWSID)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (!info[0]->IsUndefined()) return; //This function takes no arguments.
    int id = ms->_ms->GetNextWSID();
	auto rtnpmise = v8::Promise::Resolver::New(info.GetIsolate());
	rtnpmise->Resolve(Nan::New(id));
	info.GetReturnValue().Set(rtnpmise->GetPromise());
    return;
}

NAN_METHOD(machineState::GetCurrentFeedrate)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (!info[0]->IsUndefined()) return; //This function takes no arguments.
    double feed = ms->_ms->GetCurrentFeedrate();
	auto rtnpmise = v8::Promise::Resolver::New(info.GetIsolate());
	rtnpmise->Resolve(Nan::New(feed));
	info.GetReturnValue().Set(rtnpmise->GetPromise());
    return;
}

NAN_METHOD(machineState::GetCurrentSpindleSpeed)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (!info[0]->IsUndefined()) return; //This function takes no arguments.
    double speed = ms->_ms->GetCurrentSpindleSpeed();
	auto rtnpmise = v8::Promise::Resolver::New(info.GetIsolate());
	rtnpmise->Resolve(Nan::New(speed));
	info.GetReturnValue().Set(rtnpmise->GetPromise());
    return;
}

NAN_METHOD(machineState::SetToolPosition)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (info.Length() < 5 || info.Length() > 6) return;    // bad input

    double xyz[3];
	double ijk[3]; //ijk or ac if there's only 2 values.
	bool isAC = false; //true if 5 args false if 6.
    for (int i=0; i<3; i++) {
	if (info[i]->IsUndefined()) return; // throw ex
	if (!info[i]->IsNumber()) return; // needs to be a number

	Nan::Maybe<double> num = Nan::To<double>(info[i]);

	xyz[i] = num.FromJust();
    }

    for (int i=3; i<6; i++) {
		if (info[i]->IsUndefined()) {
			if(i<5) return; // bad input, need at least 2!
			isAC = true;
			break;
		}
	if (!info[i]->IsNumber()) return; // check for number

	Nan::Maybe<double> num = Nan::To<double>(info[i]);

	ijk[i - 3] = num.FromJust();
    }

    v8::Local<v8::Promise::Resolver> pmise = v8::Promise::Resolver::New(info.GetIsolate());
    auto pased = new Nan::Global<v8::Promise::Resolver>(pmise);
    pased->Reset(pmise);
    if(isAC==false) ms->_ms->SetToolPositionIJK(xyz, ijk,(pased));
	else ms->_ms->SetToolPositionAC(xyz, ijk, (pased));
	info.GetReturnValue().Set(pmise->GetPromise());
    return;
}

NAN_METHOD(machineState::SetDumpDir)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (info.Length() != 1) //Function takes one argument
	return;
    if (!info[0]->IsString()) { // argument of wrong type
	return;
    }
    char * fname;
    v8StringToChar(info[0], fname);
    ms->_ms->SetDumpDirectory(fname);
	auto rtnpmise = v8::Promise::Resolver::New(info.GetIsolate());
	rtnpmise->Resolve(Nan::Null());
	info.GetReturnValue().Set(rtnpmise->GetPromise());
    return;
}
NAN_METHOD(machineState::WorkingstepTransitionDisableToolMove)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (!info[0]->IsUndefined()) return; //This function takes no arguments.
    ms->_ms->WorkingstepTransitionDisableToolMove();
	auto rtnpmise = v8::Promise::Resolver::New(info.GetIsolate());
	rtnpmise->Resolve(Nan::Null());
	info.GetReturnValue().Set(rtnpmise->GetPromise());
    return;
}

NAN_MODULE_INIT(machineState::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("machineState").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "AdvanceState", AdvanceState);
    Nan::SetPrototypeMethod(tpl, "AdvanceStateByT", AdvanceStateByT);
    Nan::SetPrototypeMethod(tpl, "GetGeometryJSON", GetGeometryJSON);
    Nan::SetPrototypeMethod(tpl, "GetDynamicGeometryJSON", GetDynamicGeometryJSON);
    Nan::SetPrototypeMethod(tpl, "WriteDynamicGeometrySTEP", WriteDynamicGeometrySTEP);
    Nan::SetPrototypeMethod(tpl, "GetDynamicGeometryVersion", GetDynamicGeometryVersion);
    Nan::SetPrototypeMethod(tpl, "GetDeltaStateJSON", GetDeltaStateJSON);
    Nan::SetPrototypeMethod(tpl, "GetKeyStateJSON", GetKeyStateJSON);
    Nan::SetPrototypeMethod(tpl, "GoToWS", GoToWS);
    Nan::SetPrototypeMethod(tpl, "GetEIDfromUUID", GetEIDfromUUID);
    Nan::SetPrototypeMethod(tpl, "NextWS", NextWS);
    Nan::SetPrototypeMethod(tpl, "PrevWS", PrevWS);
    Nan::SetPrototypeMethod(tpl, "GetPrevWSID", GetPrevWSID);
    Nan::SetPrototypeMethod(tpl, "GetWSID", GetWSID);
    Nan::SetPrototypeMethod(tpl, "GetNextWSID", GetNextWSID);
    Nan::SetPrototypeMethod(tpl, "GetCurrentFeedrate", GetCurrentFeedrate);
    Nan::SetPrototypeMethod(tpl, "GetCurrentSpindleSpeed", GetCurrentSpindleSpeed);
    Nan::SetPrototypeMethod(tpl, "SetToolPosition", SetToolPosition);
    Nan::SetPrototypeMethod(tpl, "SetDumpDir", SetDumpDir);
    Nan::SetPrototypeMethod(tpl, "ResetDynamicGeometry", ResetDynamicGeometry);
    Nan::SetPrototypeMethod(tpl, "WorkingstepTransitionDisableToolMove",WorkingstepTransitionDisableToolMove);
    constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("machineState").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());

    MachineState::init();
}

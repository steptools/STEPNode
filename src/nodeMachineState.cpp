// $RCSfile: $
// $Revision: $ $Date: $
// Auth: Samson Bonfante (bonfante@steptools.com)
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

#include "nodeMachineState.h"
#include "nodeUtils.h"
#include <stp_schema.h>
#include <future>
#include <thread>

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
	    std::thread([ms]() {
		bool wait = true;
		double rtn = 0;
		auto myiso = v8::Isolate::New();
		v8::Locker lock(myiso);
		v8::Isolate::Scope isoscope(myiso);
		v8::HandleScope handlescope(myiso);
		while (wait) {
		    void * vpmise;
		    wait = ms->_ms->WaitForStateUpdate(vpmise, rtn);
		    auto ppmise = (Nan::Global<v8::Promise::Resolver>*)vpmise;
		    v8::Local<v8::Promise::Resolver> pmise = v8::Local<v8::Promise::Resolver>::New(myiso,*ppmise);
		    if (!wait) return;
		    pmise->Resolve(v8::Number::New(myiso,rtn));
		    delete ppmise;
		}
	    }).detach();
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
    ms->_ms->AdvanceState(&pmise);
    info.GetReturnValue().Set(pmise);
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
	info.GetReturnValue().Set(CharTov8String(rtn.as_const()));
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
	info.GetReturnValue().Set(CharTov8String(rtn.as_const()));
	delete[] id;
	delete[] typ;
	return;
    }
}

NAN_METHOD(machineState::GetDeltaGeometryJSON)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (info.Length() != 1) //Function takes one argument
	return;
    if (!info[0]->IsNumber()) { // argument of wrong type
	return;
    }
    RoseStringObject rtn;
    ms->_ms->GetDynamicGeometryJSON(rtn,Nan::To<int32_t>(info[0]).FromJust());
    info.GetReturnValue().Set(CharTov8String(rtn.as_const()));
    return;
}

NAN_METHOD(machineState::GetDeltaStateJSON)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (!info[0]->IsUndefined()) return; //This function takes no arguments.
    RoseStringObject rtn;
    ms->_ms->GetStateJSON(rtn,false);
    info.GetReturnValue().Set(CharTov8String(rtn.as_const()));
    return;
}

NAN_METHOD(machineState::GetKeyStateJSON)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (!info[0]->IsUndefined()) return; //This function takes no arguments.
    RoseStringObject rtn;
    ms->_ms->GetStateJSON(rtn,true);
    info.GetReturnValue().Set(CharTov8String(rtn.as_const()));
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
    int rtnval = ms->_ms->GoToWS(ws);
    info.GetReturnValue().Set(rtnval);
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
    info.GetReturnValue().Set(Nan::New(rtnval));
    return;
}

NAN_METHOD(machineState::LoadMachine)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (info[0]->IsUndefined()) return;
    char * b;
    v8StringToChar(info[0], b);
    bool success = ms->_ms->SetMachine(b);
    info.GetReturnValue().Set(success);
    delete[] b;

    return;
}

NAN_METHOD(machineState::NextWS)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (!info[0]->IsUndefined()) return; //This function takes no arguments.
    ms->_ms->GoToNextWS();
    return;
}

NAN_METHOD(machineState::PrevWS)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (!info[0]->IsUndefined()) return; //This function takes no arguments.
    ms->_ms->GoToPrevWS();
    return;
}

NAN_METHOD(machineState::GetPrevWSID)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (!info[0]->IsUndefined()) return; //This function takes no arguments.
    int id = ms->_ms->GetPrevWSID();
    info.GetReturnValue().Set(id);
    return;
}

NAN_METHOD(machineState::GetWSID)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (!info[0]->IsUndefined()) return; //This function takes no arguments.
    int id = ms->_ms->GetWSID();
    info.GetReturnValue().Set(id);
    return;
}

NAN_METHOD(machineState::GetNextWSID)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (!info[0]->IsUndefined()) return; //This function takes no arguments.
    int id = ms->_ms->GetNextWSID();
    info.GetReturnValue().Set(id);
    return;
}

NAN_METHOD(machineState::GetCurrentFeedrate)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (!info[0]->IsUndefined()) return; //This function takes no arguments.
    double feed = ms->_ms->GetCurrentFeedrate();
    info.GetReturnValue().Set(feed);
    return;
}

NAN_METHOD(machineState::GetCurrentSpindleSpeed)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (!info[0]->IsUndefined()) return; //This function takes no arguments.
    double speed = ms->_ms->GetCurrentSpindleSpeed();
    info.GetReturnValue().Set(speed);
    return;
}

NAN_METHOD(machineState::SetToolPosition)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (info.Length() != 6) return;    // bad input

    double xyz[3];
    double ijk[3];

    for (int i=0; i<3; i++) {
	if (info[i]->IsUndefined()) return; // throw ex
	if (!info[i]->IsNumber()) return; // needs to be a number

	Nan::Maybe<double> num = Nan::To<double>(info[i]);

	xyz[i] = num.FromJust();
    }

    for (int i=3; i<6; i++) {
	if (info[i]->IsUndefined()) return; // bad input
	if (!info[i]->IsNumber()) return; // check for number

	Nan::Maybe<double> num = Nan::To<double>(info[i]);

	ijk[i - 3] = num.FromJust();
    }

    v8::Local<v8::Promise::Resolver> pmise = v8::Promise::Resolver::New(info.GetIsolate());
    auto pased = new Nan::Global<v8::Promise::Resolver>(pmise);
    pased->Reset(pmise);
    ms->_ms->SetToolPosition(xyz, ijk,(pased));
    info.GetReturnValue().Set(pmise);
    return;
}

NAN_MODULE_INIT(machineState::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("machineState").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "AdvanceState", AdvanceState);
    Nan::SetPrototypeMethod(tpl, "GetGeometryJSON", GetGeometryJSON);
    Nan::SetPrototypeMethod(tpl, "GetDeltaGeometryJSON", GetDeltaGeometryJSON);
    Nan::SetPrototypeMethod(tpl, "GetDeltaStateJSON", GetDeltaStateJSON);
    Nan::SetPrototypeMethod(tpl, "GetKeyStateJSON", GetKeyStateJSON);
    Nan::SetPrototypeMethod(tpl, "GoToWS", GoToWS);
    Nan::SetPrototypeMethod(tpl, "GetEIDfromUUID", GetEIDfromUUID);
    Nan::SetPrototypeMethod(tpl, "LoadMachine", LoadMachine);
    Nan::SetPrototypeMethod(tpl, "NextWS", NextWS);
    Nan::SetPrototypeMethod(tpl, "PrevWS", PrevWS);
    Nan::SetPrototypeMethod(tpl, "GetPrevWSID", GetPrevWSID);
    Nan::SetPrototypeMethod(tpl, "GetWSID", GetWSID);
    Nan::SetPrototypeMethod(tpl, "GetNextWSID", GetNextWSID);
    Nan::SetPrototypeMethod(tpl, "GetCurrentFeedrate", GetCurrentFeedrate);
    Nan::SetPrototypeMethod(tpl, "GetCurrentSpindleSpeed", GetCurrentSpindleSpeed);
    Nan::SetPrototypeMethod(tpl, "SetToolPosition", SetToolPosition);
    constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("machineState").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());

    MachineState::init();
}

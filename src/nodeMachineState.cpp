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
    int rtnval = ms->_ms->AdvanceState();
    info.GetReturnValue().Set(rtnval);
}

NAN_METHOD(machineState::GetGeometryJSON)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    //This function has a 2 argument and a no argument version.
    if (info.Length() == 0)
    {
    ms->_ms->GetGeometryJSON();
    char* rtn = ms->_ms->strbuff()->ro_str();
    info.GetReturnValue().Set(CharTov8String(rtn));
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
    ms->_ms->GetGeometryJSON(id, obj, GeomTypeFromString(typ));
    char* rtn = ms->_ms->strbuff()->ro_str();
    info.GetReturnValue().Set(CharTov8String(rtn));
    delete[] id;
    delete[] typ;
    return;
    }
}

NAN_METHOD(machineState::GetDeltaJSON)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (!info[0]->IsUndefined()) return; //This function takes no arguments.
    ms->_ms->GetDeltaJSON(false);
    char* rtn = ms->_ms->strbuff()->ro_str();
    info.GetReturnValue().Set(CharTov8String(rtn));
    return;
}

NAN_METHOD(machineState::GetKeystateJSON)
{
    machineState * ms = Nan::ObjectWrap::Unwrap<machineState>(info.This());
    if (!ms || !(ms->_ms)) return;
    if (!info[0]->IsUndefined()) return; //This function takes no arguments.
    ms->_ms->GetDeltaJSON(true);
    char* rtn = ms->_ms->strbuff()->ro_str();
    info.GetReturnValue().Set(CharTov8String(rtn));
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

NAN_MODULE_INIT(machineState::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("machineState").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "AdvanceState", AdvanceState);
    Nan::SetPrototypeMethod(tpl, "GetGeometryJSON", GetGeometryJSON);
    Nan::SetPrototypeMethod(tpl, "GetDeltaJSON", GetDeltaJSON);
    Nan::SetPrototypeMethod(tpl, "GetKeystateJSON", GetKeystateJSON);
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
    constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("machineState").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());

    MachineState::init();
}

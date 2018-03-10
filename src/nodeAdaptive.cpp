//
// Copyright (c) 1991-2017 by STEP Tools Inc.
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
// Author: David Loffredo (loffredo@steptools.com)
//

#include "nodeAdaptive.h"
#include "nodeUtils.h"

#include <StixCtlCursor.h>
#include <stncapt/Cursor.h>	// Maker cursor class keeps the default design
#include <stncapt/Trace.h>
#include <stncapt/Id_manager.h>
#include <stncapt/save.h>

static TraceContext tc("Adaptive");


//==================================================
// Global object for CtlEvent enumeration
//
v8::Local<v8::Object> CtlEventEnum::singleton()
{
    v8::Local<v8::ObjectTemplate> target = Nan::New<v8::ObjectTemplate>();
    target->SetInternalFieldCount(1);

    Nan::SetMethod(target, "Name", Name);

    // Declare from last to first.  When printed, properties show up
    // in reverse of the order that they are declared.
    //
    ENUM_PROPERTY("LAST_EVENT", STIXCTL_LAST_EVENT);
    ENUM_PROPERTY("CURVE_END", STIXCTL_CURVE_END);
    ENUM_PROPERTY("CURVE_START", STIXCTL_CURVE_START);
    ENUM_PROPERTY("TOOLPATH_END", STIXCTL_TOOLPATH_END);
    ENUM_PROPERTY("TOOLPATH_START", STIXCTL_TOOLPATH_START);
    ENUM_PROPERTY("OPERATION_END", STIXCTL_OPERATION_END);
    ENUM_PROPERTY("OPERATION_NEXTPATH", STIXCTL_OPERATION_NEXTPATH);
    ENUM_PROPERTY("OPERATION_START", STIXCTL_OPERATION_START);
    ENUM_PROPERTY("EXEC_NCFUN", STIXCTL_EXEC_NCFUN);
    ENUM_PROPERTY("EXEC_OTHER_END", STIXCTL_EXEC_OTHER_END);
    ENUM_PROPERTY("EXEC_OTHER_START", STIXCTL_EXEC_OTHER_START);
    ENUM_PROPERTY("EXEC_WORKSTEP_END", STIXCTL_EXEC_WORKSTEP_END);
    ENUM_PROPERTY("EXEC_WORKSTEP_START", STIXCTL_EXEC_WORKSTEP_START);
    ENUM_PROPERTY("EXEC_SELECT_END", STIXCTL_EXEC_SELECT_END);
    ENUM_PROPERTY("EXEC_SELECT_NEXT", STIXCTL_EXEC_SELECT_NEXT);
    ENUM_PROPERTY("EXEC_SELECT_START", STIXCTL_EXEC_SELECT_START);
    ENUM_PROPERTY("EXEC_WORKPLAN_END", STIXCTL_EXEC_WORKPLAN_END);
    ENUM_PROPERTY("EXEC_WORKPLAN_NEXT", STIXCTL_EXEC_WORKPLAN_NEXT);
    ENUM_PROPERTY("EXEC_WORKPLAN_START", STIXCTL_EXEC_WORKPLAN_START);
    ENUM_PROPERTY("SETUP_END", STIXCTL_SETUP_END);
    ENUM_PROPERTY("SETUP_START", STIXCTL_SETUP_START);
    ENUM_PROPERTY("PROJECT_END", STIXCTL_PROJECT_END);
    ENUM_PROPERTY("PROJECT_START", STIXCTL_PROJECT_START);
    ENUM_PROPERTY("TOOL_CHANGE", STIXCTL_TOOL_CHANGE);
    ENUM_PROPERTY("MOVE", STIXCTL_MOVE);
    ENUM_PROPERTY("ERROR", STIXCTL_ERROR);
    ENUM_PROPERTY("DONE", STIXCTL_DONE);

    // create an instance on the stack.  Trying to wrap a static
    // object seems to fail an IsNearDeath assertion when the static
    // constructor fires.
    CtlEventEnum * foo = new CtlEventEnum;
    v8::Local<v8::Object> obj = target->NewInstance();
    foo->Wrap(obj);
    return obj;
}

// return string constants for name
NAN_METHOD(CtlEventEnum::Name)
{
    Trace t(tc, "CtlEvent::Name");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlEvent u = (StixCtlEvent) Nan::To<int32_t>(info[0]).FromJust();
    const char * nm;
    switch (u) {
    case STIXCTL_DONE: nm = "DONE"; break;
    case STIXCTL_ERROR: nm = "ERROR"; break;
    case STIXCTL_MOVE: nm = "MOVE"; break;
    case STIXCTL_TOOL_CHANGE: nm = "TOOL_CHANGE"; break;
    case STIXCTL_PROJECT_START: nm = "PROJECT_START"; break;
    case STIXCTL_PROJECT_END: nm = "PROJECT_END"; break;
    case STIXCTL_SETUP_START: nm = "SETUP_START"; break;
    case STIXCTL_SETUP_END: nm = "SETUP_END"; break;
    case STIXCTL_EXEC_WORKPLAN_START: nm = "EXEC_WORKPLAN_START"; break;
    case STIXCTL_EXEC_WORKPLAN_NEXT: nm = "EXEC_WORKPLAN_NEXT"; break;
    case STIXCTL_EXEC_WORKPLAN_END: nm = "EXEC_WORKPLAN_END"; break;
    case STIXCTL_EXEC_SELECT_START: nm = "EXEC_SELECT_START"; break;
    case STIXCTL_EXEC_SELECT_NEXT: nm = "EXEC_SELECT_NEXT"; break;
    case STIXCTL_EXEC_SELECT_END: nm = "EXEC_SELECT_END"; break;
    case STIXCTL_EXEC_WORKSTEP_START: nm = "EXEC_WORKSTEP_START"; break;
    case STIXCTL_EXEC_WORKSTEP_END: nm = "EXEC_WORKSTEP_END"; break;
    case STIXCTL_EXEC_OTHER_START: nm = "EXEC_OTHER_START"; break;
    case STIXCTL_EXEC_OTHER_END: nm = "EXEC_OTHER_END"; break;
    case STIXCTL_EXEC_NCFUN: nm = "EXEC_NCFUN"; break;
    case STIXCTL_OPERATION_START: nm = "OPERATION_START"; break;
    case STIXCTL_OPERATION_NEXTPATH: nm = "OPERATION_NEXTPATH"; break;
    case STIXCTL_OPERATION_END: nm = "OPERATION_END"; break;
    case STIXCTL_TOOLPATH_START: nm = "TOOLPATH_START"; break;
    case STIXCTL_TOOLPATH_END: nm = "TOOLPATH_END"; break;
    case STIXCTL_CURVE_START: nm = "CURVE_START"; break;
    case STIXCTL_CURVE_END: nm = "CURVE_END"; break;
    case STIXCTL_LAST_EVENT: nm = "LAST_EVENT"; break;
    default: nm = "unknown"; break;
    }
    
    info.GetReturnValue().Set(CharTov8String(nm));
}

//==================================================
// Global object for CtlType enumeration
//
v8::Local<v8::Object> CtlTypeEnum::singleton()
{
    v8::Local<v8::ObjectTemplate> target = Nan::New<v8::ObjectTemplate>();
    target->SetInternalFieldCount(1);

    Nan::SetMethod(target, "Name", Name);

    // Declare from last to first.  When printed, properties show up
    // in reverse of the order that they are declared.
    //
    ENUM_PROPERTY("LAST_TYPE", STIXCTL_LAST_TYPE);

    ENUM_PROPERTY("MOVE_HELIX", STIXCTL_TYPE_MOVE_HELIX);	
    ENUM_PROPERTY("MOVE_ARC", STIXCTL_TYPE_MOVE_ARC);	
    ENUM_PROPERTY("MOVE", STIXCTL_TYPE_MOVE);	

    ENUM_PROPERTY("CURVE", STIXCTL_TYPE_CURVE);

    ENUM_PROPERTY("TP_CONDIR", STIXCTL_TYPE_TP_CONDIR);	
    ENUM_PROPERTY("TP_CONSEC", STIXCTL_TYPE_TP_CONSEC); 	
    ENUM_PROPERTY("TP_TAN", STIXCTL_TYPE_TP_TAN); 	
    ENUM_PROPERTY("TP_ANGLE", STIXCTL_TYPE_TP_ANGLE); 	
    ENUM_PROPERTY("TP_AXIS", STIXCTL_TYPE_TP_AXIS); 	
    ENUM_PROPERTY("TP_CUTCON", STIXCTL_TYPE_TP_CUTCON); 	
    ENUM_PROPERTY("TP_CUTLOC", STIXCTL_TYPE_TP_CUTLOC); 	
    ENUM_PROPERTY("TP_FEEDSTOP", STIXCTL_TYPE_TP_FEEDSTOP); 
    ENUM_PROPERTY("TP", STIXCTL_TYPE_TP);

    ENUM_PROPERTY("OP_PROBE_TRAD", STIXCTL_TYPE_OP_PROBE_TRAD);
    ENUM_PROPERTY("OP_PROBE_TLEN", STIXCTL_TYPE_OP_PROBE_TLEN);
    ENUM_PROPERTY("OP_PROBE_COMPLETE", STIXCTL_TYPE_OP_PROBE_COMPLETE);
    ENUM_PROPERTY("OP_PROBE", STIXCTL_TYPE_OP_PROBE);

    ENUM_PROPERTY("OP_RAPID", STIXCTL_TYPE_OP_RAPID);
    ENUM_PROPERTY("OP_TAP", STIXCTL_TYPE_OP_TAP);
    ENUM_PROPERTY("OP_BACK_BORE", STIXCTL_TYPE_OP_BACK_BORE);
    ENUM_PROPERTY("OP_BORE", STIXCTL_TYPE_OP_BORE);
    ENUM_PROPERTY("OP_DRILL", STIXCTL_TYPE_OP_DRILL);
    ENUM_PROPERTY("OP_TURN", STIXCTL_TYPE_OP_TURN);
    ENUM_PROPERTY("OP_MILL", STIXCTL_TYPE_OP_MILL);
    ENUM_PROPERTY("OP", STIXCTL_TYPE_OP);

    ENUM_PROPERTY("EXEC_OP_COMBO", STIXCTL_TYPE_EXEC_OP_COMBO);
    ENUM_PROPERTY("EXEC_NCFUN", STIXCTL_TYPE_EXEC_NCFUN);
    ENUM_PROPERTY("EXEC_WORKSTEP", STIXCTL_TYPE_EXEC_WORKSTEP);
    ENUM_PROPERTY("EXEC_WORKPLAN", STIXCTL_TYPE_EXEC_WORKPLAN);
    ENUM_PROPERTY("EXEC_WHILE", STIXCTL_TYPE_EXEC_WHILE);
    ENUM_PROPERTY("EXEC_SELECT", STIXCTL_TYPE_EXEC_SELECT);
    ENUM_PROPERTY("EXEC_PARALLEL", STIXCTL_TYPE_EXEC_PARALLEL);
    ENUM_PROPERTY("EXEC_NONSEQ", STIXCTL_TYPE_EXEC_NONSEQ);
    ENUM_PROPERTY("EXEC_IF", STIXCTL_TYPE_EXEC_IF);
    ENUM_PROPERTY("EXEC_ASSIGN", STIXCTL_TYPE_EXEC_ASSIGN);
    ENUM_PROPERTY("EXEC", STIXCTL_TYPE_EXEC);
    ENUM_PROPERTY("PROJECT", STIXCTL_TYPE_PROJECT);
    ENUM_PROPERTY("UNKNOWN", STIXCTL_TYPE_UNKNOWN);

    // create an instance on the stack.  Trying to wrap a static
    // object seems to fail an IsNearDeath assertion when the static
    // constructor fires.
    CtlTypeEnum * foo = new CtlTypeEnum;
    v8::Local<v8::Object> obj = target->NewInstance();
    foo->Wrap(obj);
    return obj;
}


NAN_METHOD(CtlTypeEnum::Name)
{
    Trace t(tc, "CtlType::Name");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlType u = (StixCtlType) Nan::To<int32_t>(info[0]).FromJust();
    const char * nm;
    switch (u) {
    case STIXCTL_TYPE_UNKNOWN: nm = "UNKNOWN"; break;
    case STIXCTL_TYPE_PROJECT: nm = "PROJECT"; break;
    case STIXCTL_TYPE_EXEC: nm = "EXEC"; break;
    case STIXCTL_TYPE_EXEC_ASSIGN: nm = "EXEC_ASSIGN"; break;
    case STIXCTL_TYPE_EXEC_IF: nm = "EXEC_IF"; break;
    case STIXCTL_TYPE_EXEC_NONSEQ: nm = "EXEC_NONSEQ"; break;
    case STIXCTL_TYPE_EXEC_PARALLEL: nm = "EXEC_PARALLEL"; break;
    case STIXCTL_TYPE_EXEC_SELECT: nm = "EXEC_SELECT"; break;
    case STIXCTL_TYPE_EXEC_WHILE: nm = "EXEC_WHILE"; break;
    case STIXCTL_TYPE_EXEC_WORKPLAN: nm = "EXEC_WORKPLAN"; break;
    case STIXCTL_TYPE_EXEC_WORKSTEP: nm = "EXEC_WORKSTEP"; break;
    case STIXCTL_TYPE_EXEC_NCFUN: nm = "EXEC_NCFUN"; break;
    case STIXCTL_TYPE_EXEC_OP_COMBO: nm = "EXEC_OP_COMBO"; break;

    case STIXCTL_TYPE_OP: nm = "OP"; break;
    case STIXCTL_TYPE_OP_MILL: nm = "OP_MILL"; break;
    case STIXCTL_TYPE_OP_TURN: nm = "OP_TURN"; break;
    case STIXCTL_TYPE_OP_DRILL: nm = "OP_DRILL"; break;
    case STIXCTL_TYPE_OP_BORE: nm = "OP_BORE"; break;
    case STIXCTL_TYPE_OP_BACK_BORE: nm = "OP_BACK_BORE"; break;
    case STIXCTL_TYPE_OP_TAP: nm = "OP_TAP"; break;
    case STIXCTL_TYPE_OP_RAPID: nm = "OP_RAPID"; break;

    case STIXCTL_TYPE_OP_PROBE: nm = "OP_PROBE"; break;
    case STIXCTL_TYPE_OP_PROBE_COMPLETE: nm = "OP_PROBE_COMPLETE"; break;
    case STIXCTL_TYPE_OP_PROBE_TLEN: nm = "OP_PROBE_TLEN"; break;
    case STIXCTL_TYPE_OP_PROBE_TRAD: nm = "OP_PROBE_TRAD"; break;

    case STIXCTL_TYPE_TP: nm = "TP"; break;
    case STIXCTL_TYPE_TP_FEEDSTOP: nm = "TP_FEEDSTOP"; break; 
    case STIXCTL_TYPE_TP_CUTLOC: nm = "TP_CUTLOC"; break; 	
    case STIXCTL_TYPE_TP_CUTCON: nm = "TP_CUTCON"; break; 	
    case STIXCTL_TYPE_TP_AXIS: nm = "TP_AXIS"; break; 	
    case STIXCTL_TYPE_TP_ANGLE: nm = "TP_ANGLE"; break; 	
    case STIXCTL_TYPE_TP_TAN: nm = "TP_TAN"; break; 	
    case STIXCTL_TYPE_TP_CONSEC: nm = "TP_CONSEC"; break; 	
    case STIXCTL_TYPE_TP_CONDIR: nm = "TP_CONDIR"; break;	

    case STIXCTL_TYPE_CURVE: nm = "CURVE"; break;

    case STIXCTL_TYPE_MOVE: nm = "MOVE"; break;	
    case STIXCTL_TYPE_MOVE_ARC: nm = "MOVE_ARC"; break;	
    case STIXCTL_TYPE_MOVE_HELIX: nm = "MOVE_HELIX"; break;	
    default: nm = "unknown"; break;
    }
    
    info.GetReturnValue().Set(CharTov8String(nm));
}



//==================================================
// Global object for CtlCsys enumeration
//
v8::Local<v8::Object> CtlCsysEnum::singleton()
{
    v8::Local<v8::ObjectTemplate> target = Nan::New<v8::ObjectTemplate>();
    target->SetInternalFieldCount(1);

    Nan::SetMethod(target, "Name", Name);

    // Declare from last to first.  When printed, properties show up
    // in reverse of the order that they are declared.
    //
    ENUM_PROPERTY("RAW", STIXCTL_CSYS_RAW);
    ENUM_PROPERTY("PART", STIXCTL_CSYS_PART);
    ENUM_PROPERTY("WCS", STIXCTL_CSYS_WCS);

    // create an instance on the stack.  Trying to wrap a static
    // object seems to fail an IsNearDeath assertion when the static
    // constructor fires.
    CtlCsysEnum * foo = new CtlCsysEnum;
    v8::Local<v8::Object> obj = target->NewInstance();
    foo->Wrap(obj);
    return obj;
}


NAN_METHOD(CtlCsysEnum::Name)
{
    Trace t(tc, "CtlType::Name");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlCsys u = (StixCtlCsys) Nan::To<int32_t>(info[0]).FromJust();
    const char * nm;
    switch (u) {
    case STIXCTL_CSYS_WCS:  nm = "WCS"; break;
    case STIXCTL_CSYS_PART: nm = "PART"; break;
    case STIXCTL_CSYS_RAW:  nm = "RAW"; break;
    default: nm = "unknown"; break;
    }
    
    info.GetReturnValue().Set(CharTov8String(nm));
}



//==================================================
// Global object for CtlCsys enumeration
//
v8::Local<v8::Object> CtlStatusEnum::singleton()
{
    v8::Local<v8::ObjectTemplate> target = Nan::New<v8::ObjectTemplate>();
    target->SetInternalFieldCount(1);

    // Declare from last to first.  When printed, properties show up
    // in reverse of the order that they are declared.
    //
    ENUM_PROPERTY("ERROR", STIXCTL_STATUS_ERROR);
    ENUM_PROPERTY("END", STIXCTL_STATUS_END);
    ENUM_PROPERTY("END_BODY", STIXCTL_STATUS_END_BODY);
    ENUM_PROPERTY("END_STEP", STIXCTL_STATUS_END_STEP);
    ENUM_PROPERTY("WORKING", STIXCTL_STATUS_WORKING);
    ENUM_PROPERTY("START_STEP", STIXCTL_STATUS_START_STEP);
    ENUM_PROPERTY("START_BODY", STIXCTL_STATUS_START_BODY);
    ENUM_PROPERTY("START", STIXCTL_STATUS_START);
    ENUM_PROPERTY("UNSEEN", STIXCTL_STATUS_UNSEEN);

    // create an instance on the stack.  Trying to wrap a static
    // object seems to fail an IsNearDeath assertion when the static
    // constructor fires.
    CtlStatusEnum * foo = new CtlStatusEnum;
    v8::Local<v8::Object> obj = target->NewInstance();
    foo->Wrap(obj);
    return obj;
}



//==================================================
// Global object for RoseUnit enumeration
//
v8::Local<v8::Object> RoseUnitEnum::singleton()
{
    v8::Local<v8::ObjectTemplate> target = Nan::New<v8::ObjectTemplate>();
    target->SetInternalFieldCount(1);

    Nan::SetMethod(target, "Name", Name);
    Nan::SetMethod(target, "FullName", FullName);

    // Declare from last to first.  When printed, properties show up
    // in reverse of the order that they are declared.
    //
    ENUM_PROPERTY("MAX_VALUE", ROSEUNIT_MAX_VALUE);

    ENUM_PROPERTY("tooth", roseunit_tooth);
    ENUM_PROPERTY("revolution", roseunit_revolution);
    ENUM_PROPERTY("ratio", roseunit_ratio);
    ENUM_PROPERTY("parameter", roseunit_parameter);
    ENUM_PROPERTY("count", roseunit_count);
    
    ENUM_PROPERTY("rankine", roseunit_rankine);
    ENUM_PROPERTY("fahrenheit", roseunit_fahrenheit);
    ENUM_PROPERTY("kelvin", roseunit_kelvin); 
    ENUM_PROPERTY("celsius", roseunit_celsius); 		

    ENUM_PROPERTY("pound_foot", roseunit_pound_foot);	
    ENUM_PROPERTY("newton_meter", roseunit_newton_meter);	

    ENUM_PROPERTY("hp", roseunit_hp);	
    ENUM_PROPERTY("kw", roseunit_kw);	
    ENUM_PROPERTY("watt", roseunit_watt);	

    ENUM_PROPERTY("lbf", roseunit_lbf);	
    ENUM_PROPERTY("newton", roseunit_newton);	

    ENUM_PROPERTY("psi", roseunit_psi);	
    ENUM_PROPERTY("mpa", roseunit_mpa);	
    ENUM_PROPERTY("kpa", roseunit_kpa);	
    ENUM_PROPERTY("pa", roseunit_pa);	

    ENUM_PROPERTY("rpm", roseunit_rpm);	
    ENUM_PROPERTY("hertz", roseunit_hertz);	

    ENUM_PROPERTY("iptooth", roseunit_iptooth);	
    ENUM_PROPERTY("mmptooth", roseunit_mmptooth);	

    ENUM_PROPERTY("iprev", roseunit_iprev);	
    ENUM_PROPERTY("mmprev", roseunit_mmprev);	

    ENUM_PROPERTY("fpm", roseunit_fpm);	
    ENUM_PROPERTY("fps", roseunit_fps);	
    ENUM_PROPERTY("ipm", roseunit_ipm);	
    ENUM_PROPERTY("ips", roseunit_ips);	
    ENUM_PROPERTY("mps", roseunit_mps);	
    ENUM_PROPERTY("cmps", roseunit_cmps);	
    ENUM_PROPERTY("mmpm", roseunit_mmpm);	
    ENUM_PROPERTY("mmps", roseunit_mmps);	

    ENUM_PROPERTY("hour", roseunit_hour);	
    ENUM_PROPERTY("min", roseunit_min);	
    ENUM_PROPERTY("sec", roseunit_sec);	

    ENUM_PROPERTY("steradian", roseunit_steradian);	

    ENUM_PROPERTY("rad", roseunit_rad); 	
    ENUM_PROPERTY("deg", roseunit_deg);	

    ENUM_PROPERTY("ft3", roseunit_ft3);	
    ENUM_PROPERTY("in3", roseunit_in3);	
    ENUM_PROPERTY("m3", roseunit_m3);	
    ENUM_PROPERTY("cm3", roseunit_cm3);	
    ENUM_PROPERTY("mm3", roseunit_mm3);	

    ENUM_PROPERTY("ft2", roseunit_ft2);	
    ENUM_PROPERTY("in2", roseunit_in2);	
    ENUM_PROPERTY("m2", roseunit_m2);	
    ENUM_PROPERTY("cm2", roseunit_cm2);	
    ENUM_PROPERTY("mm2", roseunit_mm2);	

    ENUM_PROPERTY("microinch", roseunit_microinch);	
    ENUM_PROPERTY("milliinch", roseunit_milliinch);      
    ENUM_PROPERTY("nanometre", roseunit_nanometre);	
    ENUM_PROPERTY("micrometre", roseunit_micrometre);	
    ENUM_PROPERTY("ft", roseunit_ft); 	
    ENUM_PROPERTY("inch", roseunit_in);	
    ENUM_PROPERTY("m", roseunit_m);	
    ENUM_PROPERTY("cm", roseunit_cm);	
    ENUM_PROPERTY("mm", roseunit_mm);	

    ENUM_PROPERTY("as_is", roseunit_as_is);	
    ENUM_PROPERTY("unknown", roseunit_unknown);

    // create an instance on the stack.  Trying to wrap a static
    // object seems to fail an IsNearDeath assertion when the static
    // constructor fires.
    RoseUnitEnum * foo = new RoseUnitEnum;
    v8::Local<v8::Object> obj = target->NewInstance();
    foo->Wrap(obj);
    return obj;
}

// return string constants for name
NAN_METHOD(RoseUnitEnum::Name)
{
    Trace t(tc, "Unit::Name");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    RoseUnit u = (RoseUnit) Nan::To<int32_t>(info[0]).FromJust();
    info.GetReturnValue().Set(CharTov8String(rose_get_unit_name(u)));
}
NAN_METHOD(RoseUnitEnum::FullName)
{
    Trace t(tc, "Unit::FullName");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    RoseUnit u = (RoseUnit) Nan::To<int32_t>(info[0]).FromJust();
    info.GetReturnValue().Set(CharTov8String(rose_get_unit_fullname(u)));
}



//==================================================
// Global object for Adaptive object
//
Adaptive::Adaptive()
{
    f_ctl = new StixCtlCursor();
}

Adaptive::~Adaptive()
{
    delete f_ctl;
}


NAN_METHOD(Adaptive::New)
{
    if (info.IsConstructCall())
    {
	if (!info[0]->IsUndefined())
	    return;

	Adaptive * ctl = new Adaptive();
	ctl->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
    }
}

NAN_MODULE_INIT(Adaptive::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("Adaptive").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "Reset", Reset);
    Nan::SetPrototypeMethod(tpl, "StartProject", StartProject);
    Nan::SetPrototypeMethod(tpl, "StartExec", StartExec);

    Nan::SetPrototypeMethod(tpl, "SetVisitAllExecs", SetVisitAllExecs);
    Nan::SetPrototypeMethod(tpl, "GetVisitAllExecs", GetVisitAllExecs);
   
    Nan::SetPrototypeMethod(tpl, "GetActiveProject", GetActiveProject);
    Nan::SetPrototypeMethod(tpl, "GetActiveExec", GetActiveExec);
    Nan::SetPrototypeMethod(tpl, "GetActiveWorkplan", GetActiveWorkplan);
    Nan::SetPrototypeMethod(tpl, "GetActiveWorkingstep", GetActiveWorkingstep);
    Nan::SetPrototypeMethod(tpl, "GetActiveFeature", GetActiveFeature);
    Nan::SetPrototypeMethod(tpl, "GetActiveOperation", GetActiveOperation);
    Nan::SetPrototypeMethod(tpl, "GetActiveToolpath", GetActiveToolpath);
    Nan::SetPrototypeMethod(tpl, "GetActiveTool", GetActiveTool);
    Nan::SetPrototypeMethod(tpl, "GetActiveTech", GetActiveTech);
    Nan::SetPrototypeMethod(tpl, "GetActiveMfun", GetActiveMfun);
    Nan::SetPrototypeMethod(tpl, "GetActiveObj", GetActiveObj);
    Nan::SetPrototypeMethod(tpl, "GetActiveAux", GetActiveAux);
    Nan::SetPrototypeMethod(tpl, "GetActiveParam", GetActiveParam);
    Nan::SetPrototypeMethod(tpl, "GetActiveType", GetActiveType);
    Nan::SetPrototypeMethod(tpl, "GetActiveStatus", GetActiveStatus);
    Nan::SetPrototypeMethod(tpl, "GetActiveXform", GetActiveXform);
    Nan::SetPrototypeMethod(tpl, "GetActiveLenUnit", GetActiveLenUnit);
    Nan::SetPrototypeMethod(tpl, "GetActiveAngUnit", GetActiveAngUnit);
    Nan::SetPrototypeMethod(tpl, "GetActivePos", GetActivePos);
    Nan::SetPrototypeMethod(tpl, "GetLastPos", GetLastPos);
    Nan::SetPrototypeMethod(tpl, "GetLastRawPos", GetLastRawPos);

    Nan::SetPrototypeMethod(tpl, "SetWantedAll", SetWantedAll);
    Nan::SetPrototypeMethod(tpl, "SetWanted", SetWanted);
    Nan::SetPrototypeMethod(tpl, "GetWanted", GetWanted);

    Nan::SetPrototypeMethod(tpl, "Next", Next);
    Nan::SetPrototypeMethod(tpl, "Event", Event);
    Nan::SetPrototypeMethod(tpl, "ErrorMsg", ErrorMsg);

    Nan::SetPrototypeMethod(tpl, "GetMoveStart", GetMoveStart);
    Nan::SetPrototypeMethod(tpl, "GetMoveEnd", GetMoveEnd);
    Nan::SetPrototypeMethod(tpl, "GetMoveArc", GetMoveArc);
    Nan::SetPrototypeMethod(tpl, "GetMoveProbe", GetMoveProbe);

    Nan::SetPrototypeMethod(tpl, "GetMoveFeed", GetMoveFeed);
    Nan::SetPrototypeMethod(tpl, "GetMoveSpindle", GetMoveSpindle);
    Nan::SetPrototypeMethod(tpl, "GetMoveFeedUnit", GetMoveFeedUnit);
    Nan::SetPrototypeMethod(tpl, "GetMoveSpindleUnit", GetMoveSpindleUnit);
    Nan::SetPrototypeMethod(tpl, "GetMoveIsRapid", GetMoveIsRapid);
    Nan::SetPrototypeMethod(tpl, "GetMoveIsCoolant", GetMoveIsCoolant);
    Nan::SetPrototypeMethod(tpl, "GetMoveIsMistCoolant", GetMoveIsMistCoolant);
    Nan::SetPrototypeMethod(tpl, "GetMoveIsThruCoolant", GetMoveIsThruCoolant);

    Nan::SetPrototypeMethod(tpl, "GetPosAll", GetPosAll);
    Nan::SetPrototypeMethod(tpl, "GetPosXYZ", GetPosXYZ);
    Nan::SetPrototypeMethod(tpl, "GetPosDirZ", GetPosDirZ);
    Nan::SetPrototypeMethod(tpl, "GetPosDefaultDirZ", GetPosDefaultDirZ);
    Nan::SetPrototypeMethod(tpl, "GetPosDirX", GetPosDirX);
    Nan::SetPrototypeMethod(tpl, "GetPosDefaultDirX", GetPosDefaultDirX);
    Nan::SetPrototypeMethod(tpl, "GetPosDirSnorm", GetPosDirSnorm);
    Nan::SetPrototypeMethod(tpl, "GetPosDirMove", GetPosDirMove);
    Nan::SetPrototypeMethod(tpl, "GetPosSpeedRatio", GetPosSpeedRatio);
    Nan::SetPrototypeMethod(tpl, "GetPosXsectParms", GetPosXsectParms);
	
    Nan::SetPrototypeMethod(tpl, "GetPosXYZObj", GetPosXYZObj);
    Nan::SetPrototypeMethod(tpl, "GetPosDirZObj", GetPosDirZObj);
    Nan::SetPrototypeMethod(tpl, "GetPosDirXObj", GetPosDirXObj);
    Nan::SetPrototypeMethod(tpl, "GetPosDirSnormObj", GetPosDirSnormObj);
    Nan::SetPrototypeMethod(tpl, "GetPosSpeedRatioObj", GetPosSpeedRatioObj);
    Nan::SetPrototypeMethod(tpl, "GetPosXsectObj", GetPosXsectObj);

    Nan::SetPrototypeMethod(tpl, "GetPosLenUnit", GetPosLenUnit);
    Nan::SetPrototypeMethod(tpl, "GetPosAngUnit", GetPosAngUnit);
    Nan::SetPrototypeMethod(tpl, "GetPosCsys", GetPosCsys);
    Nan::SetPrototypeMethod(tpl, "GetPosType", GetPosType);
    Nan::SetPrototypeMethod(tpl, "GetPosParam", GetPosParam);
    Nan::SetPrototypeMethod(tpl, "SetPosParam", SetPosParam);
    Nan::SetPrototypeMethod(tpl, "GetPosIsEqual", GetPosIsEqual);

    Nan::SetPrototypeMethod(tpl, "GetArcAll", GetArcAll);
    Nan::SetPrototypeMethod(tpl, "GetArcCenter", GetArcCenter);
    Nan::SetPrototypeMethod(tpl, "GetArcAxis", GetArcAxis);
    Nan::SetPrototypeMethod(tpl, "GetArcRadius", GetArcRadius);
    Nan::SetPrototypeMethod(tpl, "GetArcAngle", GetArcAngle);
    Nan::SetPrototypeMethod(tpl, "GetArcHeight", GetArcHeight);
    Nan::SetPrototypeMethod(tpl, "GetArcIsCW", GetArcIsCW);
    Nan::SetPrototypeMethod(tpl, "GetArcIsOver180", GetArcIsOver180);
    Nan::SetPrototypeMethod(tpl, "GetArcIsFullCircle", GetArcIsFullCircle);

    Nan::SetPrototypeMethod(tpl, "GetProbeDirection", GetProbeDirection);
    Nan::SetPrototypeMethod(tpl, "GetProbeDirectionObj", GetProbeDirectionObj);
    Nan::SetPrototypeMethod(tpl, "GetProbeEnd", GetProbeEnd);
    Nan::SetPrototypeMethod(tpl, "GetProbeExpected", GetProbeExpected);
    Nan::SetPrototypeMethod(tpl, "GetProbeExpectedObj", GetProbeExpectedObj);
    Nan::SetPrototypeMethod(tpl, "GetProbeStart", GetProbeStart);
    Nan::SetPrototypeMethod(tpl, "GetProbeStartObj", GetProbeStartObj);
    Nan::SetPrototypeMethod(tpl, "GetProbeVar", GetProbeVar);
    Nan::SetPrototypeMethod(tpl, "GetProbeVarObj", GetProbeVarObj);
    Nan::SetPrototypeMethod(tpl, "GetProbeWorkpiece", GetProbeWorkpiece);

    Nan::SetPrototypeMethod(tpl, "GetStackSize", GetStackSize);
    Nan::SetPrototypeMethod(tpl, "GetStackPosOfType", GetStackPosOfType);
    Nan::SetPrototypeMethod(tpl, "GetFrameObj", GetFrameObj);
    Nan::SetPrototypeMethod(tpl, "GetFrameAux", GetFrameAux);
    Nan::SetPrototypeMethod(tpl, "GetFrameParam", GetFrameParam);
    Nan::SetPrototypeMethod(tpl, "GetFrameType", GetFrameType);
    Nan::SetPrototypeMethod(tpl, "GetFrameStatus", GetFrameStatus);
    Nan::SetPrototypeMethod(tpl, "GetFrameXform", GetFrameXform);
    Nan::SetPrototypeMethod(tpl, "GetFrameLenUnit", GetFrameLenUnit);
    Nan::SetPrototypeMethod(tpl, "GetFrameAngUnit", GetFrameAngUnit);
    Nan::SetPrototypeMethod(tpl, "GetFramePos", GetFramePos);
    Nan::SetPrototypeMethod(tpl, "GetFrameTech", GetFrameTech);
    Nan::SetPrototypeMethod(tpl, "GetFrameMfun", GetFrameMfun);

// boilerplate for construction
    constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("Adaptive").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());

}


NAN_METHOD(Adaptive::Reset)
{
    Trace t(tc, "Reset");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    
    ao->f_ctl->reset();
}

// void StartProject();	// use finder design
NAN_METHOD(Adaptive::StartProject)
{
    Trace t(tc, "StartProject");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    if (info.Length() == 0)
    {
	ao->f_ctl->startProject(the_cursor->des);
    }
}
	
// do entire project or specific item
// void StartExec(long mpe);
NAN_METHOD(Adaptive::StartExec)
{
    Trace t(tc, "StartExec");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    if (info.Length() == 1 && info[0]->IsNumber())
    {
	long eid = Nan::To<int32_t>(info[0]).FromJust();
	ao->f_ctl->startExec(ROSE_CAST(stp_machining_process_executable,
				       find_by_eid(the_cursor->des, eid)));
    }
}

// void SetVisitAllExecs(bool yn);
NAN_METHOD(Adaptive::SetVisitAllExecs)
{
    Trace t(tc, "SetVisitAllExecs");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    
    if (info.Length() == 1)
    {
	bool flg = Nan::To<bool>(info[0]).FromJust();
	ao->f_ctl->setVisitAllExecs(flg);
    }
}

// bool GetVisitAllExecs();
NAN_METHOD(Adaptive::GetVisitAllExecs)
{
    Trace t(tc, "GetVisitAllExecs");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    info.GetReturnValue().Set(ao->f_ctl->getVisitAllExecs() != 0);
}

NAN_METHOD(Adaptive::GetActiveProject)
{
    Trace t(tc, "GetActiveProject");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    RoseObject * obj = ao->f_ctl->getActiveProject();
    info.GetReturnValue().Set((int32_t)(obj? obj->entity_id(): 0));
}

NAN_METHOD(Adaptive::GetActiveExec)
{
    Trace t(tc, "GetActiveExec");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    RoseObject * obj = ao->f_ctl->getActiveExec();
    info.GetReturnValue().Set((int32_t)(obj? obj->entity_id(): 0));
}

NAN_METHOD(Adaptive::GetActiveWorkplan)
{
    Trace t(tc, "GetActiveWorkplan");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    RoseObject * obj = ao->f_ctl->getActiveWorkplan();
    info.GetReturnValue().Set((int32_t)(obj? obj->entity_id(): 0));
}

NAN_METHOD(Adaptive::GetActiveWorkingstep)
{
    Trace t(tc, "GetActiveWorkingstep");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    RoseObject * obj = ao->f_ctl->getActiveWorkingstep();
    info.GetReturnValue().Set((int32_t)(obj? obj->entity_id(): 0));
}

NAN_METHOD(Adaptive::GetActiveFeature)
{
    Trace t(tc, "GetActiveFeature");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    RoseObject * obj = ao->f_ctl->getActiveFeature();
    info.GetReturnValue().Set((int32_t)(obj? obj->entity_id(): 0));
}

NAN_METHOD(Adaptive::GetActiveOperation)
{
    Trace t(tc, "GetActiveOperation");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    RoseObject * obj = ao->f_ctl->getActiveOperation();
    info.GetReturnValue().Set((int32_t)(obj? obj->entity_id(): 0));
}

NAN_METHOD(Adaptive::GetActiveToolpath)
{
    Trace t(tc, "GetActiveToolpath");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    RoseObject * obj = ao->f_ctl->getActiveToolpath();
    info.GetReturnValue().Set((int32_t)(obj? obj->entity_id(): 0));
}

NAN_METHOD(Adaptive::GetActiveTool)
{
    Trace t(tc, "GetActiveTool");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    RoseObject * obj = ao->f_ctl->getActiveTool();
    info.GetReturnValue().Set((int32_t)(obj? obj->entity_id(): 0));
}

NAN_METHOD(Adaptive::GetActiveTech)
{
    Trace t(tc, "GetActiveTech");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    RoseObject * obj = ao->f_ctl->getActiveTech();
    info.GetReturnValue().Set((int32_t)(obj? obj->entity_id(): 0));
}

NAN_METHOD(Adaptive::GetActiveMfun)
{
    Trace t(tc, "GetActiveMfun");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    RoseObject * obj = ao->f_ctl->getActiveMfun();
    info.GetReturnValue().Set((int32_t)(obj? obj->entity_id(): 0));
}



// Values from the top of the process stack.   
// long GetActiveObj();
NAN_METHOD(Adaptive::GetActiveObj)
{
    Trace t(tc, "GetActiveObj");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    RoseObject * obj = ao->f_ctl->getActiveObj();
    info.GetReturnValue().Set((int32_t)(obj? obj->entity_id(): 0));
}

// long GetActiveAux (long num);
NAN_METHOD(Adaptive::GetActiveAux)
{
    Trace t(tc, "GetActiveAux");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    int idx = 0;
    if (info.Length() > 0) {
	idx = Nan::To<int32_t>(info[0]).FromJust();
    }

    RoseObject * obj = ao->f_ctl->getActiveAux(idx);
    info.GetReturnValue().Set((int32_t)(obj? obj->entity_id(): 0));
}

// double GetActiveParam();
NAN_METHOD(Adaptive::GetActiveParam)
{
    Trace t(tc, "GetActiveMfun");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    double val = ao->f_ctl->getActiveParam();
    if (!ROSE_FLOAT_IS_NULL(val)) {
	info.GetReturnValue().Set(val);
    }
}

// CtlType GetActiveType();
NAN_METHOD(Adaptive::GetActiveType) {
    Trace t(tc, "GetActiveType");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    info.GetReturnValue().Set((int32_t)ao->f_ctl->getActiveType());
}


// CtlStatus GetActiveStatus();
NAN_METHOD(Adaptive::GetActiveStatus) {
    Trace t(tc, "GetActiveStatus");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    info.GetReturnValue().Set((int32_t)ao->f_ctl->getActiveStatus());
}


// double[16] GetActiveXform();
NAN_METHOD(Adaptive::GetActiveXform)
{
    Trace t(tc, "GetActiveXform");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    const double * xf = ao->f_ctl->getActiveXform();

    v8::Local<v8::Array> gcxf = Nan::New<v8::Array>(16);
    for (unsigned i=0; i<16; i++)
	gcxf->Set(i, Nan::New(xf[i]));
    
    info.GetReturnValue().Set(gcxf);
}



// RoseUnit GetActiveLenUnit();
NAN_METHOD(Adaptive::GetActiveLenUnit)
{
    Trace t(tc, "GetActiveLenUnit");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    info.GetReturnValue().Set((int32_t)ao->f_ctl->getActiveLenUnit());
}

// RoseUnit GetActiveAngUnit()
NAN_METHOD(Adaptive::GetActiveAngUnit)
{
    Trace t(tc, "GetActiveAngUnit");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    info.GetReturnValue().Set((int32_t)ao->f_ctl->getActiveAngUnit());
}


// CtlPos GetActivePos(CtlPosType t, CtlCsys cs)
NAN_METHOD(Adaptive::GetActivePos)
{
    Trace t(tc, "GetActivePos");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    if (info.Length() == 2) {
	int typ = Nan::To<int32_t>(info[0]).FromJust();
	int cs =  Nan::To<int32_t>(info[1]).FromJust();
	info.GetReturnValue().Set(
	    (int32_t)ao->f_ctl->getActivePos(typ,(StixCtlCsys)cs)
	    );
    }
}



// // Final position in last move event, in WCS
// CtlPos GetLastPos()
NAN_METHOD(Adaptive::GetLastPos)
{
    Trace t(tc, "GetLastPos");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    info.GetReturnValue().Set((int32_t)ao->f_ctl->getLastPos());
}


// CtlPos GetLastRawPos()
NAN_METHOD(Adaptive::GetLastRawPos)
{
    Trace t(tc, "GetLastRawPos");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    info.GetReturnValue().Set((int32_t)ao->f_ctl->getLastRawPos());
}



// void SetWantedAll(bool val);
NAN_METHOD(Adaptive::SetWantedAll)
{
    Trace t(tc, "SetWantedAll");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    
    if (info.Length() == 1)
    {
	bool flg = Nan::To<bool>(info[0]).FromJust();
	ao->f_ctl->setWantedAll(flg);
    }
}
    
// void SetWanted(CtlEvent e, bool val);
// void SetWanted(CtlEvent e) { SetWanted(e, true); }
NAN_METHOD(Adaptive::SetWanted)
{
    Trace t(tc, "SetWanted");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    if (info.Length() > 0)
    {
	StixCtlEvent e = (StixCtlEvent) Nan::To<int32_t>(info[0]).FromJust();
	bool val = true;   // default value

	if (info.Length() == 2)
	    val = Nan::To<bool>(info[1]).FromJust();
	
	ao->f_ctl->setWanted(e, (int)val);
    }
}
	
// bool GetWanted(CtlEvent e);
NAN_METHOD(Adaptive::GetWanted)
{
    Trace t(tc, "GetWanted");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    if (info.Length() == 1)
    {
	StixCtlEvent e = (StixCtlEvent) Nan::To<int32_t>(info[0]).FromJust();
	info.GetReturnValue().Set(ao->f_ctl->getWanted(e) != 0);
    }
}

// CtlEvent Next();
NAN_METHOD(Adaptive::Next)
{
    Trace t(tc, "Next");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    info.GetReturnValue().Set((int32_t)ao->f_ctl->next());
}

// CtlEvent Event();
NAN_METHOD(Adaptive::Event)
{
    Trace t(tc, "Event");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    info.GetReturnValue().Set((int32_t)ao->f_ctl->event());
}

// message if in error event
// string ErrorMsg();
NAN_METHOD(Adaptive::ErrorMsg)
{
    Trace t(tc, "ErrorMsg");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    info.GetReturnValue().Set(CharTov8String(ao->f_ctl->errorMsg()));
}



// CtlPos GetMoveStart (CtlCsys cs);
// CtlPos GetMoveStart() { return GetMoveStart(CtlCsys::WCS); }
NAN_METHOD(Adaptive::GetMoveStart)
{
    Trace t(tc, "GetMoveStart");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    StixCtlCsys cs = STIXCTL_CSYS_WCS;
    if (info.Length() > 0) {
	cs = (StixCtlCsys) Nan::To<int32_t>(info[0]).FromJust();
    }
    
    info.GetReturnValue().Set((int32_t)ao->f_ctl->getMoveStart(cs));
}


// CtlPos GetMoveEnd (CtlCsys cs);    
// CtlPos GetMoveEnd() { return GetMoveEnd(CtlCsys::WCS); }
NAN_METHOD(Adaptive::GetMoveEnd)
{
    Trace t(tc, "GetMoveEnd");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    StixCtlCsys cs = STIXCTL_CSYS_WCS;
    if (info.Length() > 0) {
	cs = (StixCtlCsys) Nan::To<int32_t>(info[0]).FromJust();
    }
    
    info.GetReturnValue().Set((int32_t)ao->f_ctl->getMoveEnd(cs));
}
	
// CtlPos GetMoveArc (CtlCsys cs);
// CtlPos GetMoveArc() { return GetMoveArc(CtlCsys::WCS); }
NAN_METHOD(Adaptive::GetMoveArc)
{
    Trace t(tc, "GetMoveArc");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    StixCtlCsys cs = STIXCTL_CSYS_WCS;
    if (info.Length() > 0) {
	cs = (StixCtlCsys) Nan::To<int32_t>(info[0]).FromJust();
    }
    
    info.GetReturnValue().Set((int32_t)ao->f_ctl->getMoveArc(cs));
}


// CtlPos GetMoveProbe (CtlCsys cs);
// CtlPos GetMoveProbe() { return GetMoveProbe(CtlCsys::WCS); }
NAN_METHOD(Adaptive::GetMoveProbe)
{
    Trace t(tc, "GetMoveProbe");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    StixCtlCsys cs = STIXCTL_CSYS_WCS;
    if (info.Length() > 0) {
	cs = (StixCtlCsys) Nan::To<int32_t>(info[0]).FromJust();
    }
    
    info.GetReturnValue().Set((int32_t)ao->f_ctl->getMoveProbe(cs));
}


// // process parameters
// double GetMoveFeed (RoseUnit u);
// double GetMoveFeed() { return GetMoveFeed(RoseUnit::as_is) }
NAN_METHOD(Adaptive::GetMoveFeed)
{
    Trace t(tc, "GetMoveFeed");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    RoseUnit u = roseunit_as_is;
    if (info.Length() > 0) {
	u = (RoseUnit) Nan::To<int32_t>(info[0]).FromJust();
    }
    info.GetReturnValue().Set(ao->f_ctl->getMoveFeed(u));
}


// double GetMoveSpindle (RoseUnit u)
// double GetMoveSpindle() { return GetMoveSpindle(RoseUnit::as_is) }
NAN_METHOD(Adaptive::GetMoveSpindle)
{
    Trace t(tc, "GetMoveSpindle");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    RoseUnit u = roseunit_as_is;
    if (info.Length() > 0) {
	u = (RoseUnit) Nan::To<int32_t>(info[0]).FromJust();
    }
    info.GetReturnValue().Set(ao->f_ctl->getMoveSpindle(u));
}


// RoseUnit GetMoveFeedUnit()
NAN_METHOD(Adaptive::GetMoveFeedUnit)
{
    Trace t(tc, "GetMoveFeedUnit");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    info.GetReturnValue().Set((int32_t)ao->f_ctl->getMoveFeedUnit());
}

// RoseUnit GetMoveSpindleUnit()
NAN_METHOD(Adaptive::GetMoveSpindleUnit)
{
    Trace t(tc, "GetMoveSpindleUnit");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    info.GetReturnValue().Set((int32_t)ao->f_ctl->getMoveSpindleUnit());
}




// bool GetMoveIsRapid()
NAN_METHOD(Adaptive::GetMoveIsRapid)
{
    Trace t(tc, "GetMoveIsRapid");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    info.GetReturnValue().Set(ao->f_ctl->getMoveIsRapid() != 0);
}
// bool GetMoveIsCoolant()
NAN_METHOD(Adaptive::GetMoveIsCoolant)
{
    Trace t(tc, "GetMoveIsCoolant");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    info.GetReturnValue().Set(ao->f_ctl->getMoveIsCoolant() != 0);
}

// bool GetMoveIsMistCoolant()
NAN_METHOD(Adaptive::GetMoveIsMistCoolant)
{
    Trace t(tc, "GetMoveIsMistCoolant");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    info.GetReturnValue().Set(ao->f_ctl->getMoveIsMistCoolant() != 0);
}


// bool GetMoveIsThruCoolant()
NAN_METHOD(Adaptive::GetMoveIsThruCoolant)
{
    Trace t(tc, "GetMoveIsThruCoolant");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    info.GetReturnValue().Set(ao->f_ctl->getMoveIsThruCoolant() != 0);
}



// object GetPosAll (int pos)
NAN_METHOD(Adaptive::GetPosAll)
{
    Trace t(tc, "GetPosAll");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    RoseUnit u = roseunit_as_is;
    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();

    if (info.Length() > 1) {
	u = (RoseUnit) Nan::To<int32_t>(info[1]).FromJust();
    }

    RoseObject * obj;
    double vals[7];

    v8::Local<v8::Object> ret = Nan::New<v8::Object>();
    v8::Local<v8::Value> att;

    Nan::Set(ret, CharTov8String("Type"), Nan::New((int32_t)ao->f_ctl->getPosType(pos)));
    Nan::Set(ret, CharTov8String("Csys"), Nan::New((int32_t)ao->f_ctl->getPosCsys(pos)));    

    // ------------------------------
    if (ao->f_ctl->getPosXYZ(vals, pos, u)) {
	v8::Local<v8::Array> arr = Nan::New<v8::Array>(3);
	arr->Set(0, Nan::New(vals[0]));
	arr->Set(1, Nan::New(vals[1]));
	arr->Set(2, Nan::New(vals[2]));
	att = arr;
    }
    else {
        att = Nan::Undefined();
    }
    Nan::Set(ret, CharTov8String("XYZ"), att);

    obj = ao->f_ctl->getPosXYZObj(pos);
    Nan::Set(
	ret, CharTov8String("XYZObj"),
	Nan::New((int32_t)(obj? obj->entity_id(): 0))
	);
    
    // ------------------------------
    if (ao->f_ctl->getPosDirZ(vals, pos)) {
	v8::Local<v8::Array> arr = Nan::New<v8::Array>(3);
	arr->Set(0, Nan::New(vals[0]));
	arr->Set(1, Nan::New(vals[1]));
	arr->Set(2, Nan::New(vals[2]));
	att = arr;
    }
    else {
        att = Nan::Undefined();
    }
    Nan::Set(ret, CharTov8String("DirZ"), att);

    obj = ao->f_ctl->getPosDirZObj(pos);
    Nan::Set(
	ret, CharTov8String("DirZObj"),
	Nan::New((int32_t)(obj? obj->entity_id(): 0))
	);

    // ------------------------------
    if (ao->f_ctl->getPosDirX(vals, pos)) {
	v8::Local<v8::Array> arr = Nan::New<v8::Array>(3);
	arr->Set(0, Nan::New(vals[0]));
	arr->Set(1, Nan::New(vals[1]));
	arr->Set(2, Nan::New(vals[2]));
	att = arr;
    }
    else {
        att = Nan::Undefined();
    }
    Nan::Set(ret, CharTov8String("DirX"), att);

    obj = ao->f_ctl->getPosDirXObj(pos);
    Nan::Set(
	ret, CharTov8String("DirXObj"),
	Nan::New((int32_t)(obj? obj->entity_id(): 0))
	);
    
    // ------------------------------
    if (ao->f_ctl->getPosDirSnorm(vals, pos)) {
	v8::Local<v8::Array> arr = Nan::New<v8::Array>(3);
	arr->Set(0, Nan::New(vals[0]));
	arr->Set(1, Nan::New(vals[1]));
	arr->Set(2, Nan::New(vals[2]));
	att = arr;
    }
    else {
        att = Nan::Undefined();
    }
    Nan::Set(ret, CharTov8String("DirSnorm"), att);

    obj = ao->f_ctl->getPosDirSnormObj(pos);
    Nan::Set(
	ret, CharTov8String("DirSnormObj"),
	Nan::New((int32_t)(obj? obj->entity_id(): 0))
	);
    
    // ------------------------------
    if (ao->f_ctl->getPosDirMove(vals, pos)) {
	v8::Local<v8::Array> arr = Nan::New<v8::Array>(3);
	arr->Set(0, Nan::New(vals[0]));
	arr->Set(1, Nan::New(vals[1]));
	arr->Set(2, Nan::New(vals[2]));
	att = arr;
    }
    else {
        att = Nan::Undefined();
    }
    Nan::Set(ret, CharTov8String("DirMove"), att);


    // ------------------------------
    if (ao->f_ctl->getPosSpeedRatio(vals[0], pos)) {
	att = Nan::New(vals[0]);
    }
    else {
        att = Nan::Undefined();
    }
    Nan::Set(ret, CharTov8String("SpeedRatio"), att);
	
    obj = ao->f_ctl->getPosSpeedRatioObj(pos);
    Nan::Set(
	ret, CharTov8String("SpeedRatioObj"),
	Nan::New((int32_t)(obj? obj->entity_id(): 0))
	);

    // ------------------------------
    if (ao->f_ctl->getPosXsectParms(vals, pos, u))
    {
	// isnt there something about templates which would make this faster?
	v8::Local<v8::Object> att = Nan::New<v8::Object>();
	Nan::Set(att, CharTov8String("admax"), Nan::New(vals[0]));
	Nan::Set(att, CharTov8String("rdmax"), Nan::New(vals[1]));
	Nan::Set(att, CharTov8String("xmaxofs"), Nan::New(vals[2]));
	Nan::Set(att, CharTov8String("ymaxofs"), Nan::New(vals[3]));
	Nan::Set(att, CharTov8String("csa"), Nan::New(vals[4]));
	Nan::Set(att, CharTov8String("xcgofs"), Nan::New(vals[5]));
	Nan::Set(att, CharTov8String("ycgofs"), Nan::New(vals[6]));
    }
    else {
        att = Nan::Undefined();
    }
    Nan::Set(ret, CharTov8String("XsectParms"), att);
	
    obj = ao->f_ctl->getPosSpeedRatioObj(pos);
    Nan::Set(
	ret, CharTov8String("XsectParmsObj"),
	Nan::New((int32_t)(obj? obj->entity_id(): 0))
	);

    
    // ------------------------------
    vals[0] = ao->f_ctl->getPosParam(pos);
    if (!ROSE_FLOAT_IS_NULL(vals[0])) {
	att = Nan::New(vals[0]);
    }
    else {
        att = Nan::Undefined();
    }
    Nan::Set(ret, CharTov8String("Param"), att);

    if (u == roseunit_as_is) u = ao->f_ctl->getPosLenUnit(pos);
    Nan::Set(ret, CharTov8String("LenUnit"), Nan::New((int32_t)u));
	
    Nan::Set(ret, CharTov8String("AngUnit"), Nan::New((int32_t)ao->f_ctl->getPosAngUnit(pos)));    
    
    info.GetReturnValue().Set(ret);
}


// object GetPosAll (int pos)
NAN_METHOD(Adaptive::GetArcAll)
{
    Trace t(tc, "GetArcAll");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    RoseUnit u = roseunit_as_is;
    RoseUnit au = roseunit_deg;
    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();

    if (info.Length() > 1) {
	u = (RoseUnit) Nan::To<int32_t>(info[1]).FromJust();
    }
    if (info.Length() > 2) {
	au = (RoseUnit) Nan::To<int32_t>(info[2]).FromJust();
    }

    double vals[3];
    v8::Local<v8::Object> ret = Nan::New<v8::Object>();
    v8::Local<v8::Value> att;

    Nan::Set(ret, CharTov8String("Type"), Nan::New((int32_t)ao->f_ctl->getPosType(pos)));
    Nan::Set(ret, CharTov8String("Csys"), Nan::New((int32_t)ao->f_ctl->getPosCsys(pos)));    

    // ------------------------------
    if (ao->f_ctl->getArcCenter(vals, pos, u)) {
	v8::Local<v8::Array> arr = Nan::New<v8::Array>(3);
	arr->Set(0, Nan::New(vals[0]));
	arr->Set(1, Nan::New(vals[1]));
	arr->Set(2, Nan::New(vals[2]));
	att = arr;
    }
    else {
        att = Nan::Undefined();
    }
    Nan::Set(ret, CharTov8String("Center"), att);
    
    // ------------------------------
    if (ao->f_ctl->getArcAxis(vals, pos)) {
	v8::Local<v8::Array> arr = Nan::New<v8::Array>(3);
	arr->Set(0, Nan::New(vals[0]));
	arr->Set(1, Nan::New(vals[1]));
	arr->Set(2, Nan::New(vals[2]));
	att = arr;
    }
    else {
        att = Nan::Undefined();
    }
    Nan::Set(ret, CharTov8String("Axis"), att);

    
    // ------------------------------
    vals[0] = ao->f_ctl->getArcRadius(pos, u);
    if (!ROSE_FLOAT_IS_NULL(vals[0])) {
	att = Nan::New(vals[0]);
    }
    else {
        att = Nan::Undefined();
    }
    Nan::Set(ret, CharTov8String("Radius"), att);


    
    // ------------------------------
    vals[0] = ao->f_ctl->getArcAngle(pos, au);
    if (!ROSE_FLOAT_IS_NULL(vals[0])) {
	att = Nan::New(vals[0]);
    }
    else {
        att = Nan::Undefined();
    }
    Nan::Set(ret, CharTov8String("Angle"), att);

    
    // ------------------------------
    vals[0] = ao->f_ctl->getArcHeight(pos, u);
    if (!ROSE_FLOAT_IS_NULL(vals[0])) {
	att = Nan::New(vals[0]);
    }
    else {
        att = Nan::Undefined();
    }
    Nan::Set(ret, CharTov8String("Height"), att);

    // ------------------------------
    Nan::Set(
	ret, CharTov8String("IsCW"),
	Nan::New(ao->f_ctl->getArcIsCW(pos) != 0)
	);

    Nan::Set(
	ret, CharTov8String("IsFullCircle"),
	Nan::New(ao->f_ctl->getArcIsFullCircle(pos) != 0)
	);

    Nan::Set(
	ret, CharTov8String("IsOver180"),
	Nan::New(ao->f_ctl->getArcIsOver180(pos) != 0)
	);

    if (u == roseunit_as_is) u = ao->f_ctl->getPosLenUnit(pos);
    Nan::Set(ret, CharTov8String("LenUnit"), Nan::New((int32_t)u));
	
    if (au == roseunit_as_is) au = ao->f_ctl->getPosAngUnit(pos);
    Nan::Set(ret, CharTov8String("AngUnit"), Nan::New((int32_t)au));

    info.GetReturnValue().Set(ret);
}




// double[3] GetPosXYZ(CtlPos p, optional RoseUnit u);
NAN_METHOD(Adaptive::GetPosXYZ)
{
    Trace t(tc, "GetPosXYZ");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    RoseUnit u = roseunit_as_is;
    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();

    if (info.Length() > 1) {
	u = (RoseUnit) Nan::To<int32_t>(info[1]).FromJust();
    }

    double vals[3];
    if (ao->f_ctl->getPosXYZ(vals, pos, u)) {
	v8::Local<v8::Array> ret = Nan::New<v8::Array>(3);
	ret->Set(0, Nan::New(vals[0]));
	ret->Set(1, Nan::New(vals[1]));
	ret->Set(2, Nan::New(vals[2]));
    
	info.GetReturnValue().Set(ret);
    }
}


// double[3] GetPosDirZ(CtlPos p);
NAN_METHOD(Adaptive::GetPosDirZ)
{
    Trace t(tc, "GetPosDirZ");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();
    double vals[3];
    if (ao->f_ctl->getPosDirZ(vals, pos)) {
	v8::Local<v8::Array> ret = Nan::New<v8::Array>(3);
	ret->Set(0, Nan::New(vals[0]));
	ret->Set(1, Nan::New(vals[1]));
	ret->Set(2, Nan::New(vals[2]));
    
	info.GetReturnValue().Set(ret);
    }
}

// double[3] GetPosDefaultDirZ(CtlPos p);
NAN_METHOD(Adaptive::GetPosDefaultDirZ)
{
    Trace t(tc, "GetPosDefaultDirZ");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();
    double vals[3];
    if (ao->f_ctl->getPosDefaultDirZ(vals, pos)) {
	v8::Local<v8::Array> ret = Nan::New<v8::Array>(3);
	ret->Set(0, Nan::New(vals[0]));
	ret->Set(1, Nan::New(vals[1]));
	ret->Set(2, Nan::New(vals[2]));
    
	info.GetReturnValue().Set(ret);
    }
}



// double[3] GetPosDirX(CtlPos p);
NAN_METHOD(Adaptive::GetPosDirX)
{
    Trace t(tc, "GetPosDirX");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();
    double vals[3];
    if (ao->f_ctl->getPosDirX(vals, pos)) {
	v8::Local<v8::Array> ret = Nan::New<v8::Array>(3);
	ret->Set(0, Nan::New(vals[0]));
	ret->Set(1, Nan::New(vals[1]));
	ret->Set(2, Nan::New(vals[2]));
    
	info.GetReturnValue().Set(ret);
    }
}

// double[3] GetPosDefaultDirX(CtlPos p);
NAN_METHOD(Adaptive::GetPosDefaultDirX)
{
    Trace t(tc, "GetPosDefaultDirX");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();
    double vals[3];
    if (ao->f_ctl->getPosDefaultDirX(vals, pos)) {
	v8::Local<v8::Array> ret = Nan::New<v8::Array>(3);
	ret->Set(0, Nan::New(vals[0]));
	ret->Set(1, Nan::New(vals[1]));
	ret->Set(2, Nan::New(vals[2]));
    
	info.GetReturnValue().Set(ret);
    }
}


// double[3] GetPosDirSnorm(CtlPos p);
NAN_METHOD(Adaptive::GetPosDirSnorm)
{
    Trace t(tc, "GetPosDirSnorm");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();
    double vals[3];
    if (ao->f_ctl->getPosDirSnorm(vals, pos)) {
	v8::Local<v8::Array> ret = Nan::New<v8::Array>(3);
	ret->Set(0, Nan::New(vals[0]));
	ret->Set(1, Nan::New(vals[1]));
	ret->Set(2, Nan::New(vals[2]));
    
	info.GetReturnValue().Set(ret);
    }
}


// double[3] GetPosDirMove(CtlPos p);
NAN_METHOD(Adaptive::GetPosDirMove)
{
    Trace t(tc, "GetPosDirMove");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();
    double vals[3];
    if (ao->f_ctl->getPosDirMove(vals, pos)) {
	v8::Local<v8::Array> ret = Nan::New<v8::Array>(3);
	ret->Set(0, Nan::New(vals[0]));
	ret->Set(1, Nan::New(vals[1]));
	ret->Set(2, Nan::New(vals[2]));
    
	info.GetReturnValue().Set(ret);
    }
}


// double GetPosSpeedRatio (CtlPos p);
NAN_METHOD(Adaptive::GetPosSpeedRatio)
{
    Trace t(tc, "GetPosSpeedRatio");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();
    double val;
    if (ao->f_ctl->getPosSpeedRatio(val, pos)) {
	info.GetReturnValue().Set(val);
    }
}


// only one version of this.  Pass in AS is to Get data units
// object GetPosXsectParms(	CtlPos p, RoseUnit u );
NAN_METHOD(Adaptive::GetPosXsectParms)
{
    Trace t(tc, "GetPosXsectParms");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    RoseUnit u = roseunit_as_is;
    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();

    if (info.Length() > 1) {
	u = (RoseUnit) Nan::To<int32_t>(info[1]).FromJust();
    }

    double vals[7];
    if (ao->f_ctl->getPosXsectParms(vals, pos, u))
    {
	// isnt there something about templates which would make this faster?
	v8::Local<v8::Object> obj = Nan::New<v8::Object>();
	Nan::Set(obj, CharTov8String("admax"), Nan::New(vals[0]));
	Nan::Set(obj, CharTov8String("rdmax"), Nan::New(vals[1]));
	Nan::Set(obj, CharTov8String("xmaxofs"), Nan::New(vals[2]));
	Nan::Set(obj, CharTov8String("ymaxofs"), Nan::New(vals[3]));
	Nan::Set(obj, CharTov8String("csa"), Nan::New(vals[4]));
	Nan::Set(obj, CharTov8String("xcgofs"), Nan::New(vals[5]));
	Nan::Set(obj, CharTov8String("ycgofs"), Nan::New(vals[6]));

	info.GetReturnValue().Set(obj);
    }
}


// long GetPosXYZObj(CtlPos p)
NAN_METHOD(Adaptive::GetPosXYZObj)
{
    Trace t(tc, "GetPosXYZObj");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();

    RoseObject * obj = ao->f_ctl->getPosXYZObj(pos);
    info.GetReturnValue().Set((int32_t)(obj? obj->entity_id(): 0));
}


// long GetPosDirZObj(CtlPos p)
NAN_METHOD(Adaptive::GetPosDirZObj)
{
    Trace t(tc, "GetPosDirZObj");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();

    RoseObject * obj = ao->f_ctl->getPosDirZObj(pos);
    info.GetReturnValue().Set((int32_t)(obj? obj->entity_id(): 0));
}

// long GetPosDirXObj(CtlPos p)
NAN_METHOD(Adaptive::GetPosDirXObj)
{
    Trace t(tc, "GetPosDirXObj");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();

    RoseObject * obj = ao->f_ctl->getPosDirXObj(pos);
    info.GetReturnValue().Set((int32_t)(obj? obj->entity_id(): 0));
}

// long GetPosDirSnormObj(CtlPos p)
NAN_METHOD(Adaptive::GetPosDirSnormObj)
{
    Trace t(tc, "GetPosDirSnormObj");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();

    RoseObject * obj = ao->f_ctl->getPosDirSnormObj(pos);
    info.GetReturnValue().Set((int32_t)(obj? obj->entity_id(): 0));
}

// long GetPosSpeedRatioObj(CtlPos p)
NAN_METHOD(Adaptive::GetPosSpeedRatioObj)
{
    Trace t(tc, "GetPosSpeedRatioObj");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();

    RoseObject * obj = ao->f_ctl->getPosSpeedRatioObj(pos);
    info.GetReturnValue().Set((int32_t)(obj? obj->entity_id(): 0));
}

// long GetPosXsectObj(CtlPos p)
NAN_METHOD(Adaptive::GetPosXsectObj)
{
    Trace t(tc, "GetPosXsectObj");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();

    RoseObject * obj = ao->f_ctl->getPosXsectObj(pos);
    info.GetReturnValue().Set((int32_t)(obj? obj->entity_id(): 0));
}


// RoseUnit GetPosLenUnit(CtlPos p);
NAN_METHOD(Adaptive::GetPosLenUnit)
{
    Trace t(tc, "GetPosLenUnit");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();

    info.GetReturnValue().Set((int32_t)ao->f_ctl->getPosLenUnit(pos));
}

// RoseUnit GetPosAngUnit(CtlPos p);
NAN_METHOD(Adaptive::GetPosAngUnit)
{
    Trace t(tc, "GetPosAngUnit");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();

    info.GetReturnValue().Set((int32_t)ao->f_ctl->getPosAngUnit(pos));
}


// CtlCsys GetPosCsys(CtlPos p);
NAN_METHOD(Adaptive::GetPosCsys)
{
    Trace t(tc, "GetPosCsys");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();

    info.GetReturnValue().Set((int32_t)ao->f_ctl->getPosCsys(pos));
}

// int GetPosType(CtlPos p);
NAN_METHOD(Adaptive::GetPosType)
{
    Trace t(tc, "GetPosType");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();

    info.GetReturnValue().Set((int32_t)ao->f_ctl->getPosType(pos));
}

// double GetPosParam(CtlPos p);
NAN_METHOD(Adaptive::GetPosParam)
{
    Trace t(tc, "GetPosParam");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();
    double val = ao->f_ctl->getPosParam(pos);
    if (!ROSE_FLOAT_IS_NULL(val)) {
	info.GetReturnValue().Set(val);
    }
}

// void SetPosParam(CtlPos p, double val);
NAN_METHOD(Adaptive::SetPosParam)
{
    Trace t(tc, "SetPosParam");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 2) return;

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();
    double val = Nan::To<double>(info[1]).FromJust();
    // convert undefined to rose null real
    ao->f_ctl->setPosParam(pos, val);
}


// compare two positions to see if they are equal.  Only compares
// the position, zdir and xdir.
// bool GetPosIsEqual (CtlPos p1, CtlPos p2);
NAN_METHOD(Adaptive::GetPosIsEqual)
{
    Trace t(tc, "GetPosIsEqual");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 2) return;

    StixCtlPos p1 = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();
    StixCtlPos p2 = (StixCtlPos) Nan::To<int32_t>(info[1]).FromJust();

    info.GetReturnValue().Set(ao->f_ctl->getPosIsEqual(p1,p2) != 0);
}


// Arc parameters - Use with the GetMoveArc() position to Get
// curve parameters.
// double[3] GetArcCenter (CtlPos p, RoseUnit u)
NAN_METHOD(Adaptive::GetArcCenter)
{
    Trace t(tc, "GetArcCenter");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    RoseUnit u = roseunit_as_is;
    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();

    if (info.Length() > 1) {
	u = (RoseUnit) Nan::To<int32_t>(info[1]).FromJust();
    }

    double vals[3];
    if (ao->f_ctl->getArcCenter(vals, pos, u)) {
	v8::Local<v8::Array> ret = Nan::New<v8::Array>(3);
	ret->Set(0, Nan::New(vals[0]));
	ret->Set(1, Nan::New(vals[1]));
	ret->Set(2, Nan::New(vals[2]));
    
	info.GetReturnValue().Set(ret);
    }
}

// double[3] GetArcAxis (CtlPos p)
NAN_METHOD(Adaptive::GetArcAxis)
{
    Trace t(tc, "GetArcAxis");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();
    double vals[3];
    if (ao->f_ctl->getArcAxis(vals, pos)) {
	v8::Local<v8::Array> ret = Nan::New<v8::Array>(3);
	ret->Set(0, Nan::New(vals[0]));
	ret->Set(1, Nan::New(vals[1]));
	ret->Set(2, Nan::New(vals[2]));
    
	info.GetReturnValue().Set(ret);
    }
}

// double GetArcRadius  (CtlPos p, RoseUnit u)
NAN_METHOD(Adaptive::GetArcRadius)
{
    Trace t(tc, "GetArcRadius");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    RoseUnit u = roseunit_as_is;
    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();

    if (info.Length() > 1) {
	u = (RoseUnit) Nan::To<int32_t>(info[1]).FromJust();
    }
    double val = ao->f_ctl->getArcRadius(pos, u);
    info.GetReturnValue().Set(val);
}

// double GetArcAngle  (CtlPos p, RoseUnit u)
NAN_METHOD(Adaptive::GetArcAngle)
{
    Trace t(tc, "GetArcAngle");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    RoseUnit u = roseunit_deg;
    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();

    if (info.Length() > 1) {
	u = (RoseUnit) Nan::To<int32_t>(info[1]).FromJust();
    }
    double val = ao->f_ctl->getArcAngle(pos, u);
    info.GetReturnValue().Set(val);
}


// double GetArcHeight  (CtlPos p, RoseUnit u)
NAN_METHOD(Adaptive::GetArcHeight)
{
    Trace t(tc, "GetArcHeight");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    RoseUnit u = roseunit_as_is;
    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();

    if (info.Length() > 1) {
	u = (RoseUnit) Nan::To<int32_t>(info[1]).FromJust();
    }
    double val = ao->f_ctl->getArcHeight(pos, u);
    if (!ROSE_FLOAT_IS_NULL(val)) {
	info.GetReturnValue().Set(val);
    }
}

// bool GetArcIsCW  (CtlPos p)
NAN_METHOD(Adaptive::GetArcIsCW)
{
    Trace t(tc, "GetArcIsCW");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();
    info.GetReturnValue().Set(ao->f_ctl->getArcIsCW(pos) != 0);
}

// bool GetArcIsOver180  (CtlPos p)
NAN_METHOD(Adaptive::GetArcIsOver180)
{
    Trace t(tc, "GetArcIsOver180");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();
    info.GetReturnValue().Set(ao->f_ctl->getArcIsOver180(pos) != 0);
}

// bool GetArcIsFullCircle  (CtlPos p)
NAN_METHOD(Adaptive::GetArcIsFullCircle)
{
    Trace t(tc, "GetArcIsFullCircle");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();
    info.GetReturnValue().Set(ao->f_ctl->getArcIsFullCircle(pos) != 0);
}


// double[3] GetProbeDirection (CtlPos p);
NAN_METHOD(Adaptive::GetProbeDirection)
{
    Trace t(tc, "GetProbeDirection");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();
    double vals[3];
    if (ao->f_ctl->getProbeDirection(vals, pos)) {
	v8::Local<v8::Array> ret = Nan::New<v8::Array>(3);
	ret->Set(0, Nan::New(vals[0]));
	ret->Set(1, Nan::New(vals[1]));
	ret->Set(2, Nan::New(vals[2]));
    
	info.GetReturnValue().Set(ret);
    }
}

// double[3] GetProbeEnd (CtlPos p, RoseUnit u);
NAN_METHOD(Adaptive::GetProbeEnd)
{
    Trace t(tc, "GetProbeEnd");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    RoseUnit u = roseunit_as_is;
    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();

    if (info.Length() > 1) {
	u = (RoseUnit) Nan::To<int32_t>(info[1]).FromJust();
    }

    double vals[3];
    if (ao->f_ctl->getProbeEnd(vals, pos, u)) {
	v8::Local<v8::Array> ret = Nan::New<v8::Array>(3);
	ret->Set(0, Nan::New(vals[0]));
	ret->Set(1, Nan::New(vals[1]));
	ret->Set(2, Nan::New(vals[2]));
    
	info.GetReturnValue().Set(ret);
    }
}

// double GetProbeExpected (CtlPos p, RoseUnit u);
NAN_METHOD(Adaptive::GetProbeExpected)
{
    Trace t(tc, "GetProbeExpected");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    RoseUnit u = roseunit_as_is;
    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();

    if (info.Length() > 1) {
	u = (RoseUnit) Nan::To<int32_t>(info[1]).FromJust();
    }
    double val = ao->f_ctl->getProbeExpected(pos, u);
    info.GetReturnValue().Set(val);
}


// double[3] GetProbeStart (CtlPos p, RoseUnit u);
NAN_METHOD(Adaptive::GetProbeStart)
{
    Trace t(tc, "GetProbeStart");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    RoseUnit u = roseunit_as_is;
    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();

    if (info.Length() > 1) {
	u = (RoseUnit) Nan::To<int32_t>(info[1]).FromJust();
    }

    double vals[3];
    if (ao->f_ctl->getProbeStart(vals, pos, u)) {
	v8::Local<v8::Array> ret = Nan::New<v8::Array>(3);
	ret->Set(0, Nan::New(vals[0]));
	ret->Set(1, Nan::New(vals[1]));
	ret->Set(2, Nan::New(vals[2]));
    
	info.GetReturnValue().Set(ret);
    }
}


// string GetProbeVar(CtlPos p);
NAN_METHOD(Adaptive::GetProbeVar)
{
    Trace t(tc, "GetProbeVar");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();

    const char * val = ao->f_ctl->getProbeVar(pos);
    info.GetReturnValue().Set(CharTov8String(val));
}


// long GetProbeDirectionObj(CtlPos p);
NAN_METHOD(Adaptive::GetProbeDirectionObj)
{
    Trace t(tc, "GetProbeDirectionObj");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();

    RoseObject * obj = ao->f_ctl->getProbeDirectionObj(pos);
    info.GetReturnValue().Set((int32_t)(obj? obj->entity_id(): 0));
}



// long GetProbeExpectedObj(CtlPos p);
NAN_METHOD(Adaptive::GetProbeExpectedObj)
{
    Trace t(tc, "GetProbeExpectedObj");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();

    RoseObject * obj = ao->f_ctl->getProbeExpectedObj(pos);
    info.GetReturnValue().Set((int32_t)(obj? obj->entity_id(): 0));
}


// long GetProbeStartObj(CtlPos p);
NAN_METHOD(Adaptive::GetProbeStartObj)
{
    Trace t(tc, "GetProbeStartObj");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();

    RoseObject * obj = ao->f_ctl->getProbeStartObj(pos);
    info.GetReturnValue().Set((int32_t)(obj? obj->entity_id(): 0));
}

// long GetProbeVarObj(CtlPos p);
NAN_METHOD(Adaptive::GetProbeVarObj)
{
    Trace t(tc, "GetProbeVarObj");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();

    RoseObject * obj = ao->f_ctl->getProbeVarObj(pos);
    info.GetReturnValue().Set((int32_t)(obj? obj->entity_id(): 0));
}


// long GetProbeWorkpiece(CtlPos p);
NAN_METHOD(Adaptive::GetProbeWorkpiece)
{
    Trace t(tc, "GetProbeWorkpiece");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[0]).FromJust();

    RoseObject * obj = ao->f_ctl->getProbeWorkpiece(pos);
    info.GetReturnValue().Set((int32_t)(obj? obj->entity_id(): 0));
}




// long GetStackSize()
NAN_METHOD(Adaptive::GetStackSize)
{
    Trace t(tc, "GetStackSize");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    info.GetReturnValue().Set((int32_t)ao->f_ctl->getStackSize());
}

// long GetStackPosOfType(CtlType t);
NAN_METHOD(Adaptive::GetStackPosOfType)
{
    Trace t(tc, "GetStackPosOfType");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    StixCtlType u = (StixCtlType) Nan::To<int32_t>(info[0]).FromJust();

    info.GetReturnValue().Set((int32_t)ao->f_ctl->getStackPosOfType(u));
}

// long GetFrameObj (long stack_pos)
NAN_METHOD(Adaptive::GetFrameObj)
{
    Trace t(tc, "GetFrameObj");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    int pos = Nan::To<int32_t>(info[0]).FromJust();
    RoseObject * obj = ao->f_ctl->getFrameObj(pos);
    info.GetReturnValue().Set((int32_t)(obj? obj->entity_id(): 0));
}

// long GetFrameAux (long stack_pos, long num)
NAN_METHOD(Adaptive::GetFrameAux)
{
    Trace t(tc, "GetFrameAux");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 2) return;

    int pos = Nan::To<int32_t>(info[0]).FromJust();
    int num = Nan::To<int32_t>(info[1]).FromJust();
    RoseObject * obj = ao->f_ctl->getFrameAux(pos,num);
    info.GetReturnValue().Set((int32_t)(obj? obj->entity_id(): 0));
}
		      
// double GetFrameParam (long stack_pos)
NAN_METHOD(Adaptive::GetFrameParam)
{
    Trace t(tc, "GetFrameParam");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    int pos = Nan::To<int32_t>(info[0]).FromJust();
    double val = ao->f_ctl->getFrameParam(pos);
    if (!ROSE_FLOAT_IS_NULL(val)) {
	info.GetReturnValue().Set(val);
    }
}

// CtlType GetFrameType (long stack_pos)
NAN_METHOD(Adaptive::GetFrameType)
{
    Trace t(tc, "GetFrameType");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    int pos = Nan::To<int32_t>(info[0]).FromJust();
    info.GetReturnValue().Set((int32_t)ao->f_ctl->getFrameType(pos));
}


// CtlStatus GetFrameStatus (long stack_pos)
NAN_METHOD(Adaptive::GetFrameStatus)
{
    Trace t(tc, "GetFrameStatus");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    int pos = Nan::To<int32_t>(info[0]).FromJust();
    info.GetReturnValue().Set((int32_t)ao->f_ctl->getFrameStatus(pos));
}


// double[16] GetFrameXform (long stack_pos)
NAN_METHOD(Adaptive::GetFrameXform)
{
    Trace t(tc, "GetFrameXform");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    int pos = Nan::To<int32_t>(info[0]).FromJust();
    const double * xf = ao->f_ctl->getFrameXform(pos);

    v8::Local<v8::Array> gcxf = Nan::New<v8::Array>(16);
    for (unsigned i=0; i<16; i++)
	gcxf->Set(i, Nan::New(xf[i]));
    
    info.GetReturnValue().Set(gcxf);
}



// RoseUnit GetFrameLenUnit (long stack_pos)
NAN_METHOD(Adaptive::GetFrameLenUnit)
{
    Trace t(tc, "GetFrameLenUnit");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    int pos = Nan::To<int32_t>(info[0]).FromJust();
    info.GetReturnValue().Set((int32_t)ao->f_ctl->getFrameLenUnit(pos));
}


// RoseUnit GetFrameAngUnit (long stack_pos)
NAN_METHOD(Adaptive::GetFrameAngUnit)
{
    Trace t(tc, "GetFrameAngUnit");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    int pos = Nan::To<int32_t>(info[0]).FromJust();
    info.GetReturnValue().Set((int32_t)ao->f_ctl->getFrameAngUnit(pos));
}


// // position information
// CtlPos GetFramePos(long stack_pos, CtlPosType t, CtlCsys cs)
NAN_METHOD(Adaptive::GetFramePos)
{
    Trace t(tc, "GetFramePos");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 3) return;

    int pos = Nan::To<int32_t>(info[0]).FromJust();
    int typ = Nan::To<int32_t>(info[1]).FromJust();
    StixCtlCsys cs =  (StixCtlCsys) Nan::To<int32_t>(info[2]).FromJust();
    info.GetReturnValue().Set((int32_t)ao->f_ctl->getFramePos(pos, typ, cs));
}



// long GetFrameTech (long stack_pos)
NAN_METHOD(Adaptive::GetFrameTech)
{
    Trace t(tc, "GetFrameTech");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    int pos = Nan::To<int32_t>(info[0]).FromJust();
    RoseObject * obj = ao->f_ctl->getFrameTech(pos);
    info.GetReturnValue().Set((int32_t)(obj? obj->entity_id(): 0));
}


// long GetFrameMfun (long stack_pos)
NAN_METHOD(Adaptive::GetFrameMfun)
{
    Trace t(tc, "GetFrameMfun");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    if (!info.Length()) return;

    int pos = Nan::To<int32_t>(info[0]).FromJust();
    RoseObject * obj = ao->f_ctl->getFrameMfun(pos);
    info.GetReturnValue().Set((int32_t)(obj? obj->entity_id(): 0));
}



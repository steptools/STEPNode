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

    Nan::SetPrototypeMethod(tpl, "GetMoveFeed", GetMoveFeed);
    Nan::SetPrototypeMethod(tpl, "GetMoveSpindle", GetMoveSpindle);
    Nan::SetPrototypeMethod(tpl, "GetMoveFeedUnit", GetMoveFeedUnit);
    Nan::SetPrototypeMethod(tpl, "GetMoveSpindleUnit", GetMoveSpindleUnit);
    Nan::SetPrototypeMethod(tpl, "GetMoveIsRapid", GetMoveIsRapid);
    Nan::SetPrototypeMethod(tpl, "GetMoveIsCoolant", GetMoveIsCoolant);
    Nan::SetPrototypeMethod(tpl, "GetMoveIsMistCoolant", GetMoveIsMistCoolant);
    Nan::SetPrototypeMethod(tpl, "GetMoveIsThruCoolant", GetMoveIsThruCoolant);

    Nan::SetPrototypeMethod(tpl, "GetPosXYZ", GetPosXYZ);
    Nan::SetPrototypeMethod(tpl, "GetPosDirZ", GetPosDirZ);
    Nan::SetPrototypeMethod(tpl, "GetPosDirX", GetPosDirX);
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
    Nan::SetPrototypeMethod(tpl, "GetArcCenter", GetArcCenter);
    Nan::SetPrototypeMethod(tpl, "GetArcAxis", GetArcAxis);
    Nan::SetPrototypeMethod(tpl, "GetArcRadius", GetArcRadius);
    Nan::SetPrototypeMethod(tpl, "GetArcAngle", GetArcAngle);
    Nan::SetPrototypeMethod(tpl, "GetArcHeight", GetArcHeight);
    Nan::SetPrototypeMethod(tpl, "GetArcIsCW", GetArcIsCW);
    Nan::SetPrototypeMethod(tpl, "GetArcIsOver180", GetArcIsOver180);
    Nan::SetPrototypeMethod(tpl, "GetArcIsFullCircle", GetArcIsFullCircle);

    Nan::SetPrototypeMethod(tpl, "GetStackSize", GetStackSize);
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

    info.GetReturnValue().Set(ao->f_ctl->getActiveParam());
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
	int cs =  Nan::To<int32_t>(info[0]).FromJust();
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

    info.GetReturnValue().Set((int32_t)ao->f_ctl->getPosParam(pos));
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

    ao->f_ctl->setPosParam(pos, val);
}


// compare two positions to see if they are equal.  Only compares
// the position, zdir and xdir.
// bool GetPosIsEqual (CtlPos p1, CtlPos p2);
NAN_METHOD(Adaptive::GetPosIsEqual)
{
    Trace t(tc, "GetPosParam");
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
    if (!info.Length()) return;

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
    info.GetReturnValue().Set(val);
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


// long GetStackSize()
NAN_METHOD(Adaptive::GetStackSize)
{
    Trace t(tc, "GetStackSize");
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception

    info.GetReturnValue().Set((int32_t)ao->f_ctl->getStackSize());
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
    info.GetReturnValue().Set(ao->f_ctl->getFrameParam(pos));
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

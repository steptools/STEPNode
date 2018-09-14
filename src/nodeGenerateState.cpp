//
// Copyright (c) 1991-2018 by STEP Tools Inc.
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

#include "nodeGenerateState.h"
#include "nodeAdaptive.h"
#include "nodeUtils.h"

#include <stixctl.h>
#include <stncapt/Cursor.h>	// Maker cursor class keeps the default design
#include <stncapt/Trace.h>
#include <stncapt/Id_manager.h>
#include <stncapt/save.h>

static TraceContext tc("GenerateState");


//==================================================
// Global object for GenerateState object
//
GenerateState::GenerateState()
{
    f_vars = new StixCtlGenerateState();
}

GenerateState::~GenerateState()
{
    delete f_vars;
}


NAN_METHOD(GenerateState::New)
{
    if (info.IsConstructCall())
    {
	if (!info[0]->IsUndefined())
	    return;

	GenerateState * ctl = new GenerateState();
	ctl->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
    }
}

NAN_MODULE_INIT(GenerateState::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("GenerateState").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "Reset", Reset);

    Nan::SetPrototypeMethod(tpl, "GetXpos", GetXpos);
    Nan::SetPrototypeMethod(tpl, "GetYpos", GetYpos);
    Nan::SetPrototypeMethod(tpl, "GetZpos", GetZpos);
    Nan::SetPrototypeMethod(tpl, "GetXYZpos", GetXYZpos);

    Nan::SetPrototypeMethod(tpl, "SetXpos", SetXpos);
    Nan::SetPrototypeMethod(tpl, "SetYpos", SetYpos);
    Nan::SetPrototypeMethod(tpl, "SetZpos", SetZpos);
    Nan::SetPrototypeMethod(tpl, "SetXYZpos", SetXYZpos);

    Nan::SetPrototypeMethod(tpl, "IsChangedXYZpos", IsChangedXYZpos);
    Nan::SetPrototypeMethod(tpl, "IsUnknownXYZpos", IsUnknownXYZpos);

    Nan::SetPrototypeMethod(tpl, "GetIpos", GetIpos);
    Nan::SetPrototypeMethod(tpl, "GetJpos", GetJpos);
    Nan::SetPrototypeMethod(tpl, "GetKpos", GetKpos);
    Nan::SetPrototypeMethod(tpl, "GetIJKpos", GetIJKpos);

    Nan::SetPrototypeMethod(tpl, "SetIpos", SetIpos);
    Nan::SetPrototypeMethod(tpl, "SetJpos", SetJpos);
    Nan::SetPrototypeMethod(tpl, "SetKpos", SetKpos);
    Nan::SetPrototypeMethod(tpl, "SetIJKpos", SetIJKpos);

    Nan::SetPrototypeMethod(tpl, "IsChangedIJKpos", IsChangedIJKpos);
    Nan::SetPrototypeMethod(tpl, "IsChangedIJKposAssume3axis", IsChangedIJKposAssume3axis);
    Nan::SetPrototypeMethod(tpl, "IsUnknownIJKpos", IsUnknownIJKpos);

    Nan::SetPrototypeMethod(tpl, "GetApos", GetApos);
    Nan::SetPrototypeMethod(tpl, "GetBpos", GetBpos);
    Nan::SetPrototypeMethod(tpl, "GetCpos", GetCpos);

    Nan::SetPrototypeMethod(tpl, "SetApos", SetApos);
    Nan::SetPrototypeMethod(tpl, "SetBpos", SetBpos);
    Nan::SetPrototypeMethod(tpl, "SetCpos", SetCpos);

    Nan::SetPrototypeMethod(tpl, "GetFeed", GetFeed);
    Nan::SetPrototypeMethod(tpl, "SetFeed", SetFeed);

    Nan::SetPrototypeMethod(tpl, "GetSpindle", GetSpindle);
    Nan::SetPrototypeMethod(tpl, "SetSpindle", SetSpindle);

    Nan::SetPrototypeMethod(tpl, "GetCoolant", GetCoolant);
    Nan::SetPrototypeMethod(tpl, "SetCoolant", SetCoolant);

    Nan::SetPrototypeMethod(tpl, "GetCoolantMist", GetCoolantMist);
    Nan::SetPrototypeMethod(tpl, "SetCoolantMist", SetCoolantMist);

    Nan::SetPrototypeMethod(tpl, "GetCoolantThru", GetCoolantThru);
    Nan::SetPrototypeMethod(tpl, "SetCoolantThru", SetCoolantThru);

    Nan::SetPrototypeMethod(tpl, "GetMovemode", GetMovemode);
    Nan::SetPrototypeMethod(tpl, "SetMovemode", SetMovemode);

    Nan::SetPrototypeMethod(tpl, "ClearPosition", ClearPosition);
    Nan::SetPrototypeMethod(tpl, "ClearFeed", ClearFeed);
    Nan::SetPrototypeMethod(tpl, "ClearSpindle", ClearSpindle);
    Nan::SetPrototypeMethod(tpl, "ClearCoolant", ClearCoolant);
    Nan::SetPrototypeMethod(tpl, "ClearMovemode", ClearMovemode);
    Nan::SetPrototypeMethod(tpl, "ClearRefpoint", ClearRefpoint);

    Nan::SetPrototypeMethod(tpl, "IsRefpointCenter", IsRefpointCenter);
    Nan::SetPrototypeMethod(tpl, "IsRefpointContact", IsRefpointContact);
    Nan::SetPrototypeMethod(tpl, "SetRefpointCenter", SetRefpointCenter);
    Nan::SetPrototypeMethod(tpl, "SetRefpointContact", SetRefpointContact);

    Nan::SetPrototypeMethod(tpl, "IsRefpointLeft", IsRefpointLeft);
    Nan::SetPrototypeMethod(tpl, "IsRefpointRight", IsRefpointRight);
    Nan::SetPrototypeMethod(tpl, "SetRefpointLeft", SetRefpointLeft);
    Nan::SetPrototypeMethod(tpl, "SetRefpointRight", SetRefpointRight);

    Nan::SetPrototypeMethod(tpl, "GetNextBlocknum", GetNextBlocknum);
    Nan::SetPrototypeMethod(tpl, "GetLastBlocknum", GetLastBlocknum);
    Nan::SetPrototypeMethod(tpl, "SetBlocknum", SetBlocknum);

    Nan::SetPrototypeMethod(tpl, "GetMovePrefix", GetMovePrefix);
    Nan::SetPrototypeMethod(tpl, "AddMovePrefix", AddMovePrefix);
    Nan::SetPrototypeMethod(tpl, "ClearMovePrefix", ClearMovePrefix);

    Nan::SetPrototypeMethod(tpl, "GetMoveComment", GetMoveComment);
    Nan::SetPrototypeMethod(tpl, "AddMoveComment", AddMoveComment);
    Nan::SetPrototypeMethod(tpl, "ClearMoveComment", ClearMoveComment);

    Nan::SetPrototypeMethod(tpl, "SetProgramStats", SetProgramStats);
    Nan::SetPrototypeMethod(tpl, "ClearProgramStats", ClearProgramStats);

    Nan::SetPrototypeMethod(tpl, "GetProgramHas5axis", GetProgramHas5axis);
    Nan::SetPrototypeMethod(tpl, "SetProgramHas5axis", SetProgramHas5axis);

    Nan::SetPrototypeMethod(tpl, "GetProgramHasProbes", GetProgramHasProbes);
    Nan::SetPrototypeMethod(tpl, "GetProbeCount", GetProbeCount);
    Nan::SetPrototypeMethod(tpl, "SetProbeCount", SetProbeCount);

    Nan::SetPrototypeMethod(tpl, "GetProbeIndex", GetProbeIndex);
    Nan::SetPrototypeMethod(tpl, "GetNextProbeIndex", GetNextProbeIndex);
    Nan::SetPrototypeMethod(tpl, "SetProbeIndex", SetProbeIndex);

    Nan::SetPrototypeMethod(tpl, "GetOtherObj", GetOtherObj);
    Nan::SetPrototypeMethod(tpl, "SetOtherObj", SetOtherObj);

    // boilerplate for construction
    constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("GenerateState").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());

}


NAN_METHOD(GenerateState::Reset)
{
    Trace t(tc, "Reset");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    
    ao->f_vars->reset();
}


// double GetXpos();
// double GetYpos();
// double GetZpos();

NAN_METHOD(GenerateState::GetXpos)
{
    Trace t(tc, "GetXpos");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_vars->getXpos());
}


NAN_METHOD(GenerateState::GetYpos)
{
    Trace t(tc, "GetYpos");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_vars->getYpos());
}


NAN_METHOD(GenerateState::GetZpos)
{
    Trace t(tc, "GetZpos");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_vars->getZpos());
}

// double[3] GetXYZpos();
NAN_METHOD(GenerateState::GetXYZpos)
{
    Trace t(tc, "GetXYZpos");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception

    v8::Local<v8::Array> ret = Nan::New<v8::Array>(3);
    ret->Set(0, Nan::New(ao->f_vars->getXpos()));
    ret->Set(1, Nan::New(ao->f_vars->getYpos()));
    ret->Set(2, Nan::New(ao->f_vars->getZpos()));
    info.GetReturnValue().Set(ret);
}



// void SetXpos (double s);
// void SetYpos (double s);
// void SetZpos (double s);

NAN_METHOD(GenerateState::SetXpos)
{
    Trace t(tc, "SetXpos");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;
    ao->f_vars->setXpos(Nan::To<double>(info[0]).FromJust());
}


NAN_METHOD(GenerateState::SetYpos)
{
    Trace t(tc, "SetYpos");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;
    ao->f_vars->setYpos(Nan::To<double>(info[0]).FromJust());
}

NAN_METHOD(GenerateState::SetZpos)
{
    Trace t(tc, "SetZpos");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;
    ao->f_vars->setZpos(Nan::To<double>(info[0]).FromJust());
}

// void SetXYZpos (double x, double y, double z);
NAN_METHOD(GenerateState::SetXYZpos)
{
    Trace t(tc, "SetXYZpos");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception

    if (info.Length() == 1 && info[0]->IsArray())
    {
	v8::Local<v8::Array> a1 = v8::Local<v8::Array>::Cast(info[0]);

	ao->f_vars->setXpos(Nan::To<double>(a1->Get(0)).FromJust());
	ao->f_vars->setYpos(Nan::To<double>(a1->Get(1)).FromJust());
	ao->f_vars->setZpos(Nan::To<double>(a1->Get(2)).FromJust());
    }
    else if (info.Length() == 3)
    {
	ao->f_vars->setXpos(Nan::To<double>(info[0]).FromJust());
	ao->f_vars->setYpos(Nan::To<double>(info[1]).FromJust());
	ao->f_vars->setZpos(Nan::To<double>(info[2]).FromJust());
    }
}

// bool IsChangedXYZpos (double x, double y, double z);
NAN_METHOD(GenerateState::IsChangedXYZpos)
{
    Trace t(tc, "IsChangedXYZpos");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception

    RosePoint pt;
    if (info.Length() == 1 && info[0]->IsArray())
    {
	v8::Local<v8::Array> a1 = v8::Local<v8::Array>::Cast(info[0]);

	pt.m[0] = Nan::To<double>(a1->Get(0)).FromJust();
	pt.m[1] = Nan::To<double>(a1->Get(1)).FromJust();
	pt.m[2] = Nan::To<double>(a1->Get(2)).FromJust();
    }
    else if (info.Length() == 3)
    {
	pt.m[0] = Nan::To<double>(info[0]).FromJust();
	pt.m[1] = Nan::To<double>(info[1]).FromJust();
	pt.m[2] = Nan::To<double>(info[2]).FromJust();
    }
    else return;
    
    info.GetReturnValue().Set(ao->f_vars->isChangedXYZpos(pt) != 0);
}


// bool IsUnknownXYZpos();
NAN_METHOD(GenerateState::IsUnknownXYZpos)
{
    Trace t(tc, "IsUnknownXYZpos");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_vars->isUnknownXYZpos() != 0);
}



// double GetIpos();
// double GetJpos();
// double GetKpos();
// double[3] GetIJKpos();
NAN_METHOD(GenerateState::GetIpos)
{
    Trace t(tc, "GetIpos");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_vars->getIpos());
}


NAN_METHOD(GenerateState::GetJpos)
{
    Trace t(tc, "GetJpos");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_vars->getJpos());
}


NAN_METHOD(GenerateState::GetKpos)
{
    Trace t(tc, "GetKpos");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_vars->getKpos());
}

// double[3] GetIJKpos();
NAN_METHOD(GenerateState::GetIJKpos)
{
    Trace t(tc, "GetIJKpos");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception

    v8::Local<v8::Array> ret = Nan::New<v8::Array>(3);
    ret->Set(0, Nan::New(ao->f_vars->getIpos()));
    ret->Set(1, Nan::New(ao->f_vars->getJpos()));
    ret->Set(2, Nan::New(ao->f_vars->getKpos()));
    info.GetReturnValue().Set(ret);
}



// void SetIpos (double s);
// void SetJpos (double s);
// void SetKpos (double s);
// void SetIJKpos (double i, double j, double k);


NAN_METHOD(GenerateState::SetIpos)
{
    Trace t(tc, "SetIpos");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;
    ao->f_vars->setIpos(Nan::To<double>(info[0]).FromJust());
}


NAN_METHOD(GenerateState::SetJpos)
{
    Trace t(tc, "SetJpos");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;
    ao->f_vars->setJpos(Nan::To<double>(info[0]).FromJust());
}

NAN_METHOD(GenerateState::SetKpos)
{
    Trace t(tc, "SetKpos");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;
    ao->f_vars->setKpos(Nan::To<double>(info[0]).FromJust());
}

// void SetIJKpos (double x, double y, double z);
NAN_METHOD(GenerateState::SetIJKpos)
{
    Trace t(tc, "SetIJKpos");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception

    if (info.Length() == 1 && info[0]->IsArray())
    {
	v8::Local<v8::Array> a1 = v8::Local<v8::Array>::Cast(info[0]);

	ao->f_vars->setIpos(Nan::To<double>(a1->Get(0)).FromJust());
	ao->f_vars->setJpos(Nan::To<double>(a1->Get(1)).FromJust());
	ao->f_vars->setKpos(Nan::To<double>(a1->Get(2)).FromJust());
    }
    else if (info.Length() == 3)
    {
	ao->f_vars->setIpos(Nan::To<double>(info[0]).FromJust());
	ao->f_vars->setJpos(Nan::To<double>(info[1]).FromJust());
	ao->f_vars->setKpos(Nan::To<double>(info[2]).FromJust());
    }
}


// bool IsChangedIJKpos (double i, double j, double k);
// bool IsChangedIJKposAssume3axis(double i, double j, double k);
// bool IsUnknownIJKpos();
NAN_METHOD(GenerateState::IsChangedIJKpos)
{
    Trace t(tc, "IsChangedIJKpos");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception

    RoseDirection dir;
    if (info.Length() == 1 && info[0]->IsArray())
    {
	v8::Local<v8::Array> a1 = v8::Local<v8::Array>::Cast(info[0]);

	dir.m[0] = Nan::To<double>(a1->Get(0)).FromJust();
	dir.m[1] = Nan::To<double>(a1->Get(1)).FromJust();
	dir.m[2] = Nan::To<double>(a1->Get(2)).FromJust();
    }
    else if (info.Length() == 3)
    {
	dir.m[0] = Nan::To<double>(info[0]).FromJust();
	dir.m[1] = Nan::To<double>(info[1]).FromJust();
	dir.m[2] = Nan::To<double>(info[2]).FromJust();
    }
    else return;
    
    info.GetReturnValue().Set(ao->f_vars->isChangedIJKpos(dir) != 0);
}

NAN_METHOD(GenerateState::IsChangedIJKposAssume3axis)
{
    Trace t(tc, "IsChangedIJKposAssume3axis");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception

    RoseDirection dir;
    if (info.Length() == 1 && info[0]->IsArray())
    {
	v8::Local<v8::Array> a1 = v8::Local<v8::Array>::Cast(info[0]);

	dir.m[0] = Nan::To<double>(a1->Get(0)).FromJust();
	dir.m[1] = Nan::To<double>(a1->Get(1)).FromJust();
	dir.m[2] = Nan::To<double>(a1->Get(2)).FromJust();
    }
    else if (info.Length() == 3)
    {
	dir.m[0] = Nan::To<double>(info[0]).FromJust();
	dir.m[1] = Nan::To<double>(info[1]).FromJust();
	dir.m[2] = Nan::To<double>(info[2]).FromJust();
    }
    else return;

    info.GetReturnValue().Set(ao->f_vars->isChangedIJKposAssume3axis(dir) != 0);
}


// bool IsUnknownIJKpos();
NAN_METHOD(GenerateState::IsUnknownIJKpos)
{
    Trace t(tc, "IsUnknownIJKpos");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_vars->isUnknownIJKpos() != 0);
}






// double GetApos();
// double GetBpos();
// double GetCpos();

NAN_METHOD(GenerateState::GetApos)
{
    Trace t(tc, "GetApos");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_vars->getApos());
}


NAN_METHOD(GenerateState::GetBpos)
{
    Trace t(tc, "GetBpos");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_vars->getBpos());
}


NAN_METHOD(GenerateState::GetCpos)
{
    Trace t(tc, "GetCpos");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_vars->getCpos());
}


// void SetApos (double s);
// void SetBpos (double s);
// void SetCpos (double s);

NAN_METHOD(GenerateState::SetApos)
{
    Trace t(tc, "SetApos");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;
    ao->f_vars->setApos(Nan::To<double>(info[0]).FromJust());
}


NAN_METHOD(GenerateState::SetBpos)
{
    Trace t(tc, "SetBpos");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;
    ao->f_vars->setBpos(Nan::To<double>(info[0]).FromJust());
}

NAN_METHOD(GenerateState::SetCpos)
{
    Trace t(tc, "SetCpos");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;
    ao->f_vars->setCpos(Nan::To<double>(info[0]).FromJust());
}





// double GetFeed();
// void SetFeed (double s);

NAN_METHOD(GenerateState::GetFeed)
{
    Trace t(tc, "GetFeed");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_vars->getFeed());
}

NAN_METHOD(GenerateState::SetFeed)
{
    Trace t(tc, "SetFeed");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;
    ao->f_vars->setFeed(Nan::To<double>(info[0]).FromJust());
}




// double GetSpindle();
// void SetSpindle (double s);

NAN_METHOD(GenerateState::GetSpindle)
{
    Trace t(tc, "GetSpindle");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_vars->getSpindle());
}

NAN_METHOD(GenerateState::SetSpindle)
{
    Trace t(tc, "SetSpindle");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;
    ao->f_vars->setSpindle(Nan::To<double>(info[0]).FromJust());
}


// bool GetCoolant();
// void SetCoolant (bool yn);
NAN_METHOD(GenerateState::GetCoolant)
{
    Trace t(tc, "GetCoolant");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_vars->getCoolant() != 0);
}

NAN_METHOD(GenerateState::SetCoolant)
{
    Trace t(tc, "SetCoolant");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;

    bool val = Nan::To<bool>(info[0]).FromJust();
    ao->f_vars->setCoolant((int)val);
}


// bool GetCoolantMist();
// void SetCoolantMist (bool yn);
NAN_METHOD(GenerateState::GetCoolantMist)
{
    Trace t(tc, "GetCoolantMist");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_vars->getCoolantMist() != 0);
}

NAN_METHOD(GenerateState::SetCoolantMist)
{
    Trace t(tc, "SetCoolantMist");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;

    bool val = Nan::To<bool>(info[0]).FromJust();
    ao->f_vars->setCoolantMist((int)val);
}



// bool GetCoolantThru();
// void SetCoolantThru (bool yn);
NAN_METHOD(GenerateState::GetCoolantThru)
{
    Trace t(tc, "GetCoolantThru");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_vars->getCoolantThru() != 0);
}

NAN_METHOD(GenerateState::SetCoolantThru)
{
    Trace t(tc, "SetCoolantThru");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;

    bool val = Nan::To<bool>(info[0]).FromJust();
    ao->f_vars->setCoolantThru((int)val);
}

// int GetMovemode();
// void SetMovemode (int m);
NAN_METHOD(GenerateState::GetMovemode)
{
    Trace t(tc, "GetMovemode");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_vars->getMovemode());
}

NAN_METHOD(GenerateState::SetMovemode)
{
    Trace t(tc, "SetMovemode");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;

    int val = Nan::To<int32_t>(info[0]).FromJust();
    ao->f_vars->setMovemode(val);
}

// void ClearPosition();
NAN_METHOD(GenerateState::ClearPosition)
{
    Trace t(tc, "ClearPosition");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (ao) ao->f_vars->clearPosition();
}

// void ClearFeed();
NAN_METHOD(GenerateState::ClearFeed)
{
    Trace t(tc, "ClearFeed");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (ao) ao->f_vars->clearFeed();
}

// void ClearSpindle();
NAN_METHOD(GenerateState::ClearSpindle)
{
    Trace t(tc, "ClearSpindle");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (ao) ao->f_vars->clearSpindle();
}

// void ClearCoolant();
NAN_METHOD(GenerateState::ClearCoolant)
{
    Trace t(tc, "ClearCoolant");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (ao) ao->f_vars->clearCoolant();
}

// void ClearMovemode();
NAN_METHOD(GenerateState::ClearMovemode)
{
    Trace t(tc, "ClearMovemode");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (ao) ao->f_vars->clearMovemode();
}

// void ClearRefpoint();
NAN_METHOD(GenerateState::ClearRefpoint)
{
    Trace t(tc, "ClearRefpoint");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (ao) ao->f_vars->clearRefpoint();
}

// bool IsRefpointCenter();
NAN_METHOD(GenerateState::IsRefpointCenter)
{
    Trace t(tc, "IsRefpointCenter");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_vars->isRefpointCenter() != 0);
}
// bool IsRefpointContact();
NAN_METHOD(GenerateState::IsRefpointContact)
{
    Trace t(tc, "IsRefpointContact");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_vars->isRefpointContact() != 0);
}

// void SetRefpointCenter();
NAN_METHOD(GenerateState::SetRefpointCenter)
{
    Trace t(tc, "SetRefpointCenter");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (ao) ao->f_vars->setRefpointCenter();
}
// void SetRefpointContact();
NAN_METHOD(GenerateState::SetRefpointContact)
{
    Trace t(tc, "SetRefpointContact");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (ao) ao->f_vars->setRefpointContact();
}

// bool IsRefpointLeft();
NAN_METHOD(GenerateState::IsRefpointLeft)
{
    Trace t(tc, "IsRefpointLeft");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_vars->isRefpointLeft() != 0);
}
// bool IsRefpointRight();
NAN_METHOD(GenerateState::IsRefpointRight)
{
    Trace t(tc, "IsRefpointRight");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_vars->isRefpointRight() != 0);
}

// void SetRefpointLeft();
NAN_METHOD(GenerateState::SetRefpointLeft)
{
    Trace t(tc, "SetRefpointLeft");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (ao) ao->f_vars->setRefpointLeft();
}
// void SetRefpointRight();
NAN_METHOD(GenerateState::SetRefpointRight)
{
    Trace t(tc, "SetRefpointRight");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (ao) ao->f_vars->setRefpointRight();
}


// int GetNextBlocknum();
// int GetLastBlocknum();
// void SetBlocknum(int num);
NAN_METHOD(GenerateState::GetNextBlocknum)
{
    Trace t(tc, "GetNextBlocknum");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_vars->getNextBlocknum());
}

NAN_METHOD(GenerateState::GetLastBlocknum)
{
    Trace t(tc, "GetLastBlocknum");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_vars->getLastBlocknum());
}

NAN_METHOD(GenerateState::SetBlocknum)
{
    Trace t(tc, "SetBlocknum");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;

    int val = Nan::To<int32_t>(info[0]).FromJust();
    ao->f_vars->setBlocknum(val);
}


// // prefix codes for next move, many can be added
// string GetMovePrefix();
NAN_METHOD(GenerateState::GetMovePrefix)
{
    Trace t(tc, "GetMovePrefix");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception

    info.GetReturnValue().Set(CharTov8String(ao->f_vars->getMovePrefix()));
}

// void AddMovePrefix (string f);
NAN_METHOD(GenerateState::AddMovePrefix)
{
    Trace t(tc, "AddMovePrefix");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception

    if (info.Length() != 1) return;
    if (!info[0]->IsString()) return;
    RoseStringObject str = v8StringToRose(info[0]);
    ao->f_vars->addMovePrefix(str);
}
// void ClearMovePrefix();
NAN_METHOD(GenerateState::ClearMovePrefix)
{
    Trace t(tc, "ClearMovePrefix");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (ao) ao->f_vars->clearMovePrefix();
}






// // comments for next move, many can be added
// string GetMoveComment();
NAN_METHOD(GenerateState::GetMoveComment)
{
    Trace t(tc, "GetMoveComment");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception

    info.GetReturnValue().Set(CharTov8String(ao->f_vars->getMoveComment()));
}


// void AddMoveComment (string f);
NAN_METHOD(GenerateState::AddMoveComment)
{
    Trace t(tc, "AddMoveComment");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception

    if (info.Length() != 1) return;
    if (!info[0]->IsString()) return;
    RoseStringObject str = v8StringToRose(info[0]);
    ao->f_vars->addMoveComment(str);
}

// void ClearMoveComment();
NAN_METHOD(GenerateState::ClearMoveComment)
{
    Trace t(tc, "ClearMoveComment");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (ao) ao->f_vars->clearMoveComment();
}


// void SetProgramStats(Adaptive ctl);
NAN_METHOD(GenerateState::SetProgramStats)
{
    Trace t(tc, "SetProgramStats");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception

    if (info.Length() != 1) return;
    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    if (maybe1.IsEmpty()) return;

    Adaptive *ctl = Nan::ObjectWrap::Unwrap<Adaptive>(maybe1.ToLocalChecked());
    if (!ctl) return; // exception

    ao->f_vars->setProgramStats(*(ctl->asUnmanaged()));
}

// void ClearProgramStats();
NAN_METHOD(GenerateState::ClearProgramStats)
{
    Trace t(tc, "ClearProgramStats");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (ao) ao->f_vars->clearProgramStats();
}


// bool GetProgramHas5axis();
// void SetProgramHas5axis(bool yn);
NAN_METHOD(GenerateState::GetProgramHas5axis)
{
    Trace t(tc, "GetProgramHas5axis");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_vars->getProgramHas5axis() != 0);
}

NAN_METHOD(GenerateState::SetProgramHas5axis)
{
    Trace t(tc, "SetProgramHas5axis");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;

    bool val = Nan::To<bool>(info[0]).FromJust();
    ao->f_vars->setProgramHas5axis((int)val);
}

// bool GetProgramHasProbes();
NAN_METHOD(GenerateState::GetProgramHasProbes)
{
    Trace t(tc, "GetProgramHasProbes");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_vars->getProgramHasProbes() != 0);
}


// int GetProbeCount();
NAN_METHOD(GenerateState::GetProbeCount)
{
    Trace t(tc, "GetProbeCount");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_vars->getProbeCount());
}

// void SetProbeCount(int d);
NAN_METHOD(GenerateState::SetProbeCount)
{
    Trace t(tc, "SetProbeCount");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;

    int val = Nan::To<int32_t>(info[0]).FromJust();
    ao->f_vars->setProbeCount(val);
}


// int GetProbeIndex();
NAN_METHOD(GenerateState::GetProbeIndex)
{
    Trace t(tc, "GetProbeIndex");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_vars->getProbeIndex());
}

// int GetNextProbeIndex();
NAN_METHOD(GenerateState::GetNextProbeIndex)
{
    Trace t(tc, "GetNextProbeIndex");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_vars->getNextProbeIndex());
}

// void SetProbeIndex(int d);
NAN_METHOD(GenerateState::SetProbeIndex)
{
    Trace t(tc, "SetProbeIndex");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;

    int val = Nan::To<int32_t>(info[0]).FromJust();
    ao->f_vars->setProbeIndex(val);
}

// int GetOtherObj(string nm);
NAN_METHOD(GenerateState::GetOtherObj)
{
    Trace t(tc, "GetOtherObj");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception

    if (info.Length() != 1) return;
    if (!info[0]->IsString()) return;

    RoseStringObject str = v8StringToRose(info[0]);
    RoseObject * obj = ao->f_vars->getOtherObj(str);
    info.GetReturnValue().Set((int)(obj? obj->entity_id(): 0));
}



// void SetOtherObj(string nm, int id);
NAN_METHOD(GenerateState::SetOtherObj)
{
    Trace t(tc, "SetOtherObj");
    GenerateState* ao = Nan::ObjectWrap::Unwrap<GenerateState>(info.This());
    if (!ao) return; // exception

    if (info.Length() != 2) return;
    if (!info[0]->IsString()) return;

    RoseStringObject str = v8StringToRose(info[0]);
    int id = Nan::To<int32_t>(info[1]).FromJust();

    ao->f_vars->setOtherObj(str, find_by_eid(the_cursor->des, (unsigned)id));
}

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

#include "nodeGenerate.h"
#include "nodeGenerateState.h"
#include "nodeAdaptive.h"
#include "nodeUtils.h"

#include <stixctl.h>
#include <stncapt/Cursor.h>	// Maker cursor class keeps the default design
#include <stncapt/Trace.h>
#include <stncapt/Id_manager.h>
#include <stncapt/save.h>

static TraceContext tc("Generate");


//==================================================
// Global object for Generate object
//
Generate::Generate()
{
    f_fmt = new StixCtlGenerate();
}

Generate::~Generate()
{
    delete f_fmt;
}


NAN_METHOD(Generate::New)
{
    if (info.IsConstructCall())
    {
	if (!info[0]->IsUndefined())
	    return;

	Generate * ctl = new Generate();
	ctl->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
    }
}

NAN_MODULE_INIT(Generate::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("Generate").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "Reset", Reset);
    Nan::SetPrototypeMethod(tpl, "SetStyle", SetStyle);
    Nan::SetPrototypeMethod(tpl, "FormatEvent", FormatEvent);
    Nan::SetPrototypeMethod(tpl, "FormatType", FormatType);
    Nan::SetPrototypeMethod(tpl, "FormatOther", FormatOther);
    
// boilerplate for construction
    constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("Generate").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());

}


NAN_METHOD(Generate::Reset)
{
    Trace t(tc, "Reset");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    
    ao->f_fmt->reset();
}


NAN_METHOD(Generate::SetStyle)
{
    Trace t(tc, "SetStyle");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception

    if (info.Length() != 1) return;
    if (!info[0]->IsString()) return;

    RoseStringObject nm = v8StringToRose(info[0]);
    info.GetReturnValue().Set(ao->f_fmt->setStyle(nm) != 0);
}


// string FormatEvent (GenerateState vars, Adaptive cursor);
NAN_METHOD(Generate::FormatEvent)
{
    Trace t(tc, "FormatEvent");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception

    if (info.Length() != 2) return;

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    if (maybe1.IsEmpty() || maybe2.IsEmpty()) return;

    GenerateState* vars =
	Nan::ObjectWrap::Unwrap<GenerateState>(maybe1.ToLocalChecked());
    Adaptive *ctl =
	Nan::ObjectWrap::Unwrap<Adaptive>(maybe2.ToLocalChecked());
    if (!vars || !ctl) return; // exception

    RoseStringObject ret = ao->f_fmt->formatEvent(
	*(vars->asUnmanaged()), *(ctl->asUnmanaged())
	);

    info.GetReturnValue().Set(CharTov8String(ret));
}


// string FormatType (GenerateState vars, Adaptive cursor);
NAN_METHOD(Generate::FormatType)
{
    Trace t(tc, "FormatType");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception

    if (info.Length() != 2) return;

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    if (maybe1.IsEmpty() || maybe2.IsEmpty()) return;

    GenerateState* vars =
	Nan::ObjectWrap::Unwrap<GenerateState>(maybe1.ToLocalChecked());
    Adaptive *ctl =
	Nan::ObjectWrap::Unwrap<Adaptive>(maybe2.ToLocalChecked());
    if (!vars || !ctl) return; // exception

    RoseStringObject ret = ao->f_fmt->formatType(
	*(vars->asUnmanaged()), *(ctl->asUnmanaged())
	);

    info.GetReturnValue().Set(CharTov8String(ret));
}


// string FormatOther (GenerateState vars, Adaptive cursor, string name);
NAN_METHOD(Generate::FormatOther)
{
    Trace t(tc, "FormatOther");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception

    if (info.Length() != 3) return;
    if (!info[2]->IsString()) return;

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    RoseStringObject nm = v8StringToRose(info[2]);
    if (maybe1.IsEmpty() || maybe2.IsEmpty()) return;

    GenerateState* vars =
	Nan::ObjectWrap::Unwrap<GenerateState>(maybe1.ToLocalChecked());
    Adaptive *ctl =
	Nan::ObjectWrap::Unwrap<Adaptive>(maybe2.ToLocalChecked());
    if (!vars || !ctl) return; // exception

    RoseStringObject ret = ao->f_fmt->formatOther(
	*(vars->asUnmanaged()), *(ctl->asUnmanaged()), nm
	);

    info.GetReturnValue().Set(CharTov8String(ret));
}

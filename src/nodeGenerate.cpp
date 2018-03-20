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
    
    Nan::SetPrototypeMethod(tpl, "FormatBlock", FormatBlock);
    Nan::SetPrototypeMethod(tpl, "FormatBlockNonum", FormatBlockNonum);
    Nan::SetPrototypeMethod(tpl, "FormatComment", FormatComment);
    Nan::SetPrototypeMethod(tpl, "FormatMoveXYZ", FormatMoveXYZ);
    Nan::SetPrototypeMethod(tpl, "FormatMoveXYZ_IJK", FormatMoveXYZ_IJK);
    Nan::SetPrototypeMethod(tpl, "FormatRapidXYZ", FormatRapidXYZ);
    Nan::SetPrototypeMethod(tpl, "FormatRapidXYZ_IJK", FormatRapidXYZ_IJK);

    Nan::SetPrototypeMethod(tpl, "CatSpace", CatSpace);
    Nan::SetPrototypeMethod(tpl, "CatRequiredSpace", CatRequiredSpace);
    Nan::SetPrototypeMethod(tpl, "CatNumber", CatNumber);
    Nan::SetPrototypeMethod(tpl, "CatParam", CatParam);
    Nan::SetPrototypeMethod(tpl, "IsFormattedNumber", IsFormattedNumber);
    Nan::SetPrototypeMethod(tpl, "IsFormattedXYZ", IsFormattedXYZ);
    Nan::SetPrototypeMethod(tpl, "IsFormattedIJK", IsFormattedIJK);
	
    Nan::SetPrototypeMethod(tpl, "GetOutXYZ", GetOutXYZ);
    Nan::SetPrototypeMethod(tpl, "GetOutDirZ", GetOutDirZ);
    Nan::SetPrototypeMethod(tpl, "GetOutDirX", GetOutDirX);
    Nan::SetPrototypeMethod(tpl, "GetOutDirSnorm", GetOutDirSnorm);
    Nan::SetPrototypeMethod(tpl, "GetOutDirMove", GetOutDirMove);
    Nan::SetPrototypeMethod(tpl, "GetOutArcCenter", GetOutArcCenter);
    Nan::SetPrototypeMethod(tpl, "GetOutArcAxis", GetOutArcAxis);
    Nan::SetPrototypeMethod(tpl, "GetOutXformedPoint", GetOutXformedPoint);
    Nan::SetPrototypeMethod(tpl, "GetOutXformedDir", GetOutXformedDir);

    Nan::SetPrototypeMethod(tpl, "GetTraceComments", GetTraceComments);
    Nan::SetPrototypeMethod(tpl, "SetTraceComments", SetTraceComments);

    Nan::SetPrototypeMethod(tpl, "GetFileExt", GetFileExt);
    Nan::SetPrototypeMethod(tpl, "SetFileExt", SetFileExt);

    Nan::SetPrototypeMethod(tpl, "GetDigits", GetDigits);
    Nan::SetPrototypeMethod(tpl, "SetDigits", SetDigits);
    Nan::SetPrototypeMethod(tpl, "GetMinDigits", GetMinDigits);
    Nan::SetPrototypeMethod(tpl, "SetMinDigits", SetMinDigits);

    Nan::SetPrototypeMethod(tpl, "GetSpindleDigits", GetSpindleDigits);
    Nan::SetPrototypeMethod(tpl, "SetSpindleDigits", SetSpindleDigits);
    Nan::SetPrototypeMethod(tpl, "GetSpindleMinDigits", GetSpindleMinDigits);
    Nan::SetPrototypeMethod(tpl, "SetSpindleMinDigits", SetSpindleMinDigits);

    Nan::SetPrototypeMethod(tpl, "GetFeedDigits", GetFeedDigits);
    Nan::SetPrototypeMethod(tpl, "SetFeedDigits", SetFeedDigits);
    Nan::SetPrototypeMethod(tpl, "GetFeedMinDigits", GetFeedMinDigits);
    Nan::SetPrototypeMethod(tpl, "SetFeedMinDigits", SetFeedMinDigits);

    Nan::SetPrototypeMethod(tpl, "GetUseXform", GetUseXform);
    Nan::SetPrototypeMethod(tpl, "SetUseXform", SetUseXform);
    Nan::SetPrototypeMethod(tpl, "GetDstXform", GetDstXform);
    Nan::SetPrototypeMethod(tpl, "SetDstXform", SetDstXform);

    Nan::SetPrototypeMethod(tpl, "GetDstXformIsLeft", GetDstXformIsLeft);
    Nan::SetPrototypeMethod(tpl, "GetProgramNumber", GetProgramNumber);
    Nan::SetPrototypeMethod(tpl, "SetProgramNumber", SetProgramNumber);
    Nan::SetPrototypeMethod(tpl, "GetProgramUnit", GetProgramUnit);
    Nan::SetPrototypeMethod(tpl, "SetProgramUnit", SetProgramUnit);
    Nan::SetPrototypeMethod(tpl, "SetUnitSystem", SetUnitSystem);
    Nan::SetPrototypeMethod(tpl, "GetLenUnit", GetLenUnit);
    Nan::SetPrototypeMethod(tpl, "SetLenUnit", SetLenUnit);
    Nan::SetPrototypeMethod(tpl, "GetFeedUnit", GetFeedUnit);
    Nan::SetPrototypeMethod(tpl, "SetFeedUnit", SetFeedUnit);
    Nan::SetPrototypeMethod(tpl, "GetSpindleUnit", GetSpindleUnit);
    Nan::SetPrototypeMethod(tpl, "SetSpindleUnit", SetSpindleUnit);

    Nan::SetPrototypeMethod(tpl, "GetWorkOffsetFrame", GetWorkOffsetFrame);
    Nan::SetPrototypeMethod(tpl, "SetWorkOffsetFrame", SetWorkOffsetFrame);
    Nan::SetPrototypeMethod(tpl, "SetFeedStandalone", SetFeedStandalone);
    Nan::SetPrototypeMethod(tpl, "SetFeedInline", SetFeedInline);
    Nan::SetPrototypeMethod(tpl, "GetFeedIsStandalone", GetFeedIsStandalone);
    Nan::SetPrototypeMethod(tpl, "GetStopAfterWorkingstep", GetStopAfterWorkingstep);
    Nan::SetPrototypeMethod(tpl, "SetStopAfterWorkingstep", SetStopAfterWorkingstep);
    Nan::SetPrototypeMethod(tpl, "GetSupressXpos", GetSupressXpos);
    Nan::SetPrototypeMethod(tpl, "SetSupressXpos", SetSupressXpos);
    Nan::SetPrototypeMethod(tpl, "GetSupressYpos", GetSupressYpos);
    Nan::SetPrototypeMethod(tpl, "SetSupressYpos", SetSupressYpos);
    Nan::SetPrototypeMethod(tpl, "GetSupressZpos", GetSupressZpos);
    Nan::SetPrototypeMethod(tpl, "SetSupressZpos", SetSupressZpos);
    Nan::SetPrototypeMethod(tpl, "GetUseBlocknums", GetUseBlocknums);
    Nan::SetPrototypeMethod(tpl, "SetUseBlocknums", SetUseBlocknums);
    Nan::SetPrototypeMethod(tpl, "GetBlocknumLimit", GetBlocknumLimit);
    Nan::SetPrototypeMethod(tpl, "SetBlocknumLimit", SetBlocknumLimit);
    Nan::SetPrototypeMethod(tpl, "GetUseWhitespace", GetUseWhitespace);
    Nan::SetPrototypeMethod(tpl, "SetUseWhitespace", SetUseWhitespace);
    
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


// string FormatBlock(GenerateState, string str);
NAN_METHOD(Generate::FormatBlock)
{
    Trace t(tc, "FormatBlock");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception

    if (info.Length() != 2) return;
    if (!info[1]->IsString()) return;

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    RoseStringObject str = v8StringToRose(info[1]);
    if (maybe1.IsEmpty()) return;

    GenerateState* vars =
	Nan::ObjectWrap::Unwrap<GenerateState>(maybe1.ToLocalChecked());
    if (!vars) return; // exception

    RoseStringObject ret = ao->f_fmt->formatBlock(*(vars->asUnmanaged()), str);
    info.GetReturnValue().Set(CharTov8String(ret));
}





// string FormatBlockNonum(GenerateState, string str);
NAN_METHOD(Generate::FormatBlockNonum)
{
    Trace t(tc, "FormatBlockNonum");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception

    if (info.Length() != 2) return;
    if (!info[1]->IsString()) return;

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    RoseStringObject str = v8StringToRose(info[1]);
    if (maybe1.IsEmpty()) return;

    GenerateState* vars =
	Nan::ObjectWrap::Unwrap<GenerateState>(maybe1.ToLocalChecked());
    if (!vars) return; // exception

    RoseStringObject ret = ao->f_fmt->formatBlockNonum(
	*(vars->asUnmanaged()), str
	);
    info.GetReturnValue().Set(CharTov8String(ret));
}



// string FormatComment(GenerateState, string str);
// string FormatComment(GenerateState, string header, string str);
NAN_METHOD(Generate::FormatComment)
{
    Trace t(tc, "FormatComment");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception

    if (info.Length() == 2) {
	if (!info[1]->IsString()) return;
    }
    else if (info.Length() == 3) {
	if (!info[1]->IsString()) return;
	if (!info[2]->IsString()) return;
    }
    else return;

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    if (maybe1.IsEmpty()) return;
    GenerateState* vars =
	Nan::ObjectWrap::Unwrap<GenerateState>(maybe1.ToLocalChecked());
    if (!vars) return; // exception

    if (info.Length() == 2) {
	RoseStringObject str = v8StringToRose(info[1]);
	RoseStringObject ret = ao->f_fmt->formatComment(
	    *(vars->asUnmanaged()), str
	    );
	info.GetReturnValue().Set(CharTov8String(ret));
    }
    if (info.Length() == 3) {
	RoseStringObject head = v8StringToRose(info[1]);
	RoseStringObject str = v8StringToRose(info[2]);
	RoseStringObject ret = ao->f_fmt->formatComment(
	    *(vars->asUnmanaged()), head, str
	    );
	info.GetReturnValue().Set(CharTov8String(ret));
    }
}



// string FormatMoveXYZ (GenerateState, Adaptive, double x,y,z);
NAN_METHOD(Generate::FormatMoveXYZ)
{
    Trace t(tc, "FormatMoveXYZ");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception

    if (info.Length() != 5) return;

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    if (maybe1.IsEmpty() || maybe2.IsEmpty()) return;

    GenerateState* vars =
	Nan::ObjectWrap::Unwrap<GenerateState>(maybe1.ToLocalChecked());
    Adaptive *ctl =
	Nan::ObjectWrap::Unwrap<Adaptive>(maybe2.ToLocalChecked());
    if (!vars || !ctl) return; // exception

    RosePoint pt(
	Nan::To<double>(info[2]).FromJust(),
	Nan::To<double>(info[3]).FromJust(),
	Nan::To<double>(info[4]).FromJust()
	);

    RoseStringObject ret = ao->f_fmt->formatMoveXYZ(
	*(vars->asUnmanaged()), *(ctl->asUnmanaged()), pt
	);

    info.GetReturnValue().Set(CharTov8String(ret));
}



// string FormatMoveXYZ_IJK (GenerateState, Adaptive, double x,y,z, i,j,k);
NAN_METHOD(Generate::FormatMoveXYZ_IJK)
{
    Trace t(tc, "FormatMoveXYZ_IJK");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception

    if (info.Length() != 8) return;

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    if (maybe1.IsEmpty() || maybe2.IsEmpty()) return;

    GenerateState* vars =
	Nan::ObjectWrap::Unwrap<GenerateState>(maybe1.ToLocalChecked());
    Adaptive *ctl =
	Nan::ObjectWrap::Unwrap<Adaptive>(maybe2.ToLocalChecked());
    if (!vars || !ctl) return; // exception

    RosePoint pt(
	Nan::To<double>(info[2]).FromJust(),
	Nan::To<double>(info[3]).FromJust(),
	Nan::To<double>(info[4]).FromJust()
	);
    RoseDirection dir(
	Nan::To<double>(info[5]).FromJust(),
	Nan::To<double>(info[6]).FromJust(),
	Nan::To<double>(info[7]).FromJust()
	);

    RoseStringObject ret = ao->f_fmt->formatMoveXYZ_IJK(
	*(vars->asUnmanaged()), *(ctl->asUnmanaged()), pt, dir
	);

    info.GetReturnValue().Set(CharTov8String(ret));
}



// string FormatRapidXYZ (GenerateState, Adaptive, double x, y, z);
NAN_METHOD(Generate::FormatRapidXYZ)
{
    Trace t(tc, "FormatRapidXYZ");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception

    if (info.Length() != 5) return;

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    if (maybe1.IsEmpty() || maybe2.IsEmpty()) return;

    GenerateState* vars =
	Nan::ObjectWrap::Unwrap<GenerateState>(maybe1.ToLocalChecked());
    Adaptive *ctl =
	Nan::ObjectWrap::Unwrap<Adaptive>(maybe2.ToLocalChecked());
    if (!vars || !ctl) return; // exception

    RosePoint pt(
	Nan::To<double>(info[2]).FromJust(),
	Nan::To<double>(info[3]).FromJust(),
	Nan::To<double>(info[4]).FromJust()
	);

    RoseStringObject ret = ao->f_fmt->formatRapidXYZ(
	*(vars->asUnmanaged()), *(ctl->asUnmanaged()), pt
	);

    info.GetReturnValue().Set(CharTov8String(ret));
}


// string FormatRapidXYZ_IJK (GenerateState, Adaptive, double x,y,z, i,j,k);
NAN_METHOD(Generate::FormatRapidXYZ_IJK)
{
    Trace t(tc, "FormatRapidXYZ_IJK");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception

    if (info.Length() != 8) return;

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);
    if (maybe1.IsEmpty() || maybe2.IsEmpty()) return;

    GenerateState* vars =
	Nan::ObjectWrap::Unwrap<GenerateState>(maybe1.ToLocalChecked());
    Adaptive *ctl =
	Nan::ObjectWrap::Unwrap<Adaptive>(maybe2.ToLocalChecked());
    if (!vars || !ctl) return; // exception

    RosePoint pt(
	Nan::To<double>(info[2]).FromJust(),
	Nan::To<double>(info[3]).FromJust(),
	Nan::To<double>(info[4]).FromJust()
	);
    RoseDirection dir(
	Nan::To<double>(info[5]).FromJust(),
	Nan::To<double>(info[6]).FromJust(),
	Nan::To<double>(info[7]).FromJust()
	);

    RoseStringObject ret = ao->f_fmt->formatRapidXYZ_IJK(
	*(vars->asUnmanaged()), *(ctl->asUnmanaged()), pt, dir
	);

    info.GetReturnValue().Set(CharTov8String(ret));
}


// string CatSpace (string s); 
NAN_METHOD(Generate::CatSpace)
{
    Trace t(tc, "CatSpace");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception

    if (info.Length() != 1) return;
    if (!info[0]->IsString()) return;

    RoseStringObject ret = v8StringToRose(info[0]);
    ao->f_fmt->catSpace(ret);
    info.GetReturnValue().Set(CharTov8String(ret));
}

// string CatRequiredSpace (string s);
NAN_METHOD(Generate::CatRequiredSpace)
{
    Trace t(tc, "CatRequiredSpace");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception

    if (info.Length() != 1) return;
    if (!info[0]->IsString()) return;

    RoseStringObject ret = v8StringToRose(info[0]);
    ao->f_fmt->catRequiredSpace(ret);
    info.GetReturnValue().Set(CharTov8String(ret));
}


// string CatNumber(string s, double num);
// string CatNumber(string s, double num, int max_digits, int min_digits);
NAN_METHOD(Generate::CatNumber)
{
    Trace t(tc, "CatNumber");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception

    if (info.Length() < 2) return;
    if (!info[0]->IsString()) return;

    RoseStringObject ret = v8StringToRose(info[0]);
    double num = Nan::To<double>(info[1]).FromJust();

    if (info.Length() == 2) {
	ao->f_fmt->catNumber(ret, num);
    }
    else {
	int maxdig = Nan::To<int32_t>(info[2]).FromJust();
	int mindig = -1;

	if (info.Length() > 3) {
	    mindig = Nan::To<int32_t>(info[3]).FromJust();
	}
	ao->f_fmt->catNumber(ret, num, maxdig, mindig);
    }	

    info.GetReturnValue().Set(CharTov8String(ret));
}



// string CatParam(string s, string param);
// string CatParam(string s, string param, double num);
// string CatParam(string s, string param, double num, int max, min_digits);
NAN_METHOD(Generate::CatParam)
{
    Trace t(tc, "CatParam");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception

    if (info.Length() < 2) return;
    if (!info[0]->IsString()) return;
    if (!info[1]->IsString()) return;

    RoseStringObject ret = v8StringToRose(info[0]);
    RoseStringObject param = v8StringToRose(info[1]);

    if (info.Length() == 2) {
	ao->f_fmt->catParam(ret, param);
    }
    else if (info.Length() == 3) {
	double num = Nan::To<double>(info[2]).FromJust();
	ao->f_fmt->catParam(ret, param, num);
    }
    else {
	double num = Nan::To<double>(info[2]).FromJust();
	int maxdig = Nan::To<int32_t>(info[3]).FromJust();
	int mindig = -1;

	if (info.Length() > 4) {
	    mindig = Nan::To<int32_t>(info[4]).FromJust();
	}
	ao->f_fmt->catParam(ret, param, num, maxdig, mindig);
    }	

    info.GetReturnValue().Set(CharTov8String(ret));
}

// bool IsFormattedNumber(double num1, double num2);
// bool IsFormattedNumber(double num1, double num2, int max_digits);
NAN_METHOD(Generate::IsFormattedNumber)
{
    Trace t(tc, "IsFormattedNumber");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception

    if (info.Length() < 2) return;
    double num1 = Nan::To<double>(info[0]).FromJust();
    double num2 = Nan::To<double>(info[1]).FromJust();

    if (info.Length() == 2) {
	info.GetReturnValue().Set(
	    ao->f_fmt->isFormattedNumber(num1, num2) != 0
	    );
    }
    else {
	int maxdig = Nan::To<int32_t>(info[2]).FromJust();
	info.GetReturnValue().Set(
	    ao->f_fmt->isFormattedNumber(num1, num2, maxdig) != 0
	    );
    }
}





// bool IsFormattedXYZ(double x1, y1, z1, double x2, y2, z2);
NAN_METHOD(Generate::IsFormattedXYZ)
{
    Trace t(tc, "IsFormattedXYZ");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception

    if (info.Length() != 6) return;
    double x1 = Nan::To<double>(info[0]).FromJust();
    double y1 = Nan::To<double>(info[1]).FromJust();
    double z1 = Nan::To<double>(info[2]).FromJust();
    double x2 = Nan::To<double>(info[3]).FromJust();
    double y2 = Nan::To<double>(info[4]).FromJust();
    double z2 = Nan::To<double>(info[5]).FromJust();
    info.GetReturnValue().Set(
	ao-> f_fmt->isFormattedXYZ(
	    RosePoint(x1,y1,z1), RosePoint(x2,y2,z2)
	    ) != 0
	);
}




// bool IsFormattedIJK(double i1, j1, k1, double i2, j2, k2);
NAN_METHOD(Generate::IsFormattedIJK)
{
    Trace t(tc, "IsFormattedIJK");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception

    if (info.Length() != 6) return;
    double i1 = Nan::To<double>(info[0]).FromJust();
    double j1 = Nan::To<double>(info[1]).FromJust();
    double k1 = Nan::To<double>(info[2]).FromJust();
    double i2 = Nan::To<double>(info[3]).FromJust();
    double j2 = Nan::To<double>(info[4]).FromJust();
    double k2 = Nan::To<double>(info[5]).FromJust();
    info.GetReturnValue().Set(
	ao-> f_fmt->isFormattedIJK(
	    RoseDirection(i1,j1,k1), RoseDirection(i2,j2,k2)
	    ) != 0
	);
}
	


// ------------------------------
// Get transformed positions and directions

// double[3] GetOutXYZ(Adaptive, CtlPos p, RoseUnit u = as_is);
NAN_METHOD(Generate::GetOutXYZ)
{
    Trace t(tc, "GetOutXYZ");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    if (info.Length() < 2) return;

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    if (maybe1.IsEmpty()) return;
    Adaptive *ctl = Nan::ObjectWrap::Unwrap<Adaptive>(maybe1.ToLocalChecked());
    if (!ctl) return; // exception

    RoseUnit u = roseunit_as_is;
    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[1]).FromJust();

    if (info.Length() > 2) {
	u = (RoseUnit) Nan::To<int32_t>(info[2]).FromJust();
    }

    double vals[3];
    ao->f_fmt->getOutXYZ(*(ctl->asUnmanaged()), vals, pos, u);
    v8::Local<v8::Array> ret = Nan::New<v8::Array>(3);
    ret->Set(0, Nan::New(vals[0]));
    ret->Set(1, Nan::New(vals[1]));
    ret->Set(2, Nan::New(vals[2]));
    
    info.GetReturnValue().Set(ret);
}

// double[3] GetOutDirZ(Adaptive, CtlPos p);
NAN_METHOD(Generate::GetOutDirZ)
{
    Trace t(tc, "GetOutDirZ");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    if (info.Length() == 2) return;

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    if (maybe1.IsEmpty()) return;

    Adaptive *ctl = Nan::ObjectWrap::Unwrap<Adaptive>(maybe1.ToLocalChecked());
    if (!ctl) return; // exception

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[1]).FromJust();
    double vals[3];
    ao->f_fmt->getOutDirZ(*(ctl->asUnmanaged()), vals, pos);

    v8::Local<v8::Array> ret = Nan::New<v8::Array>(3);
    ret->Set(0, Nan::New(vals[0]));
    ret->Set(1, Nan::New(vals[1]));
    ret->Set(2, Nan::New(vals[2]));
    
    info.GetReturnValue().Set(ret);
}



// double[3] GetOutDirX(Adaptive, CtlPos p);
NAN_METHOD(Generate::GetOutDirX)
{
    Trace t(tc, "GetOutDirX");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    if (info.Length() == 2) return;

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    if (maybe1.IsEmpty()) return;

    Adaptive *ctl = Nan::ObjectWrap::Unwrap<Adaptive>(maybe1.ToLocalChecked());
    if (!ctl) return; // exception

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[1]).FromJust();
    double vals[3];
    ao->f_fmt->getOutDirX(*(ctl->asUnmanaged()), vals, pos);

    v8::Local<v8::Array> ret = Nan::New<v8::Array>(3);
    ret->Set(0, Nan::New(vals[0]));
    ret->Set(1, Nan::New(vals[1]));
    ret->Set(2, Nan::New(vals[2]));
    
    info.GetReturnValue().Set(ret);
}



// double[3] GetOutDirSnorm(Adaptive, CtlPos p);
NAN_METHOD(Generate::GetOutDirSnorm)
{
    Trace t(tc, "GetOutDirSnorm");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    if (info.Length() == 2) return;

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    if (maybe1.IsEmpty()) return;

    Adaptive *ctl = Nan::ObjectWrap::Unwrap<Adaptive>(maybe1.ToLocalChecked());
    if (!ctl) return; // exception

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[1]).FromJust();
    double vals[3];

    if (ao->f_fmt->getOutDirSnorm(*(ctl->asUnmanaged()), vals, pos) != 0)
    {
	v8::Local<v8::Array> ret = Nan::New<v8::Array>(3);
	ret->Set(0, Nan::New(vals[0]));
	ret->Set(1, Nan::New(vals[1]));
	ret->Set(2, Nan::New(vals[2]));
    
	info.GetReturnValue().Set(ret);
    }
}



// double[3] GetOutDirMove(Adaptive, CtlPos p);
NAN_METHOD(Generate::GetOutDirMove)
{
    Trace t(tc, "GetOutDirMove");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    if (info.Length() == 2) return;

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    if (maybe1.IsEmpty()) return;

    Adaptive *ctl = Nan::ObjectWrap::Unwrap<Adaptive>(maybe1.ToLocalChecked());
    if (!ctl) return; // exception

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[1]).FromJust();
    double vals[3];

    if (ao->f_fmt->getOutDirMove(*(ctl->asUnmanaged()), vals, pos) != 0)
    {
	v8::Local<v8::Array> ret = Nan::New<v8::Array>(3);
	ret->Set(0, Nan::New(vals[0]));
	ret->Set(1, Nan::New(vals[1]));
	ret->Set(2, Nan::New(vals[2]));
    
	info.GetReturnValue().Set(ret);
    }
}

// double[3] GetOutArcCenter(Adaptive, CtlPos p, RoseUnit u = as_is);
NAN_METHOD(Generate::GetOutArcCenter)
{
    Trace t(tc, "GetOutArcCenter");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    if (info.Length() < 2) return;
	
    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    if (maybe1.IsEmpty()) return;
    Adaptive *ctl = Nan::ObjectWrap::Unwrap<Adaptive>(maybe1.ToLocalChecked());
    if (!ctl) return; // exception

    RoseUnit u = roseunit_as_is;
    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[1]).FromJust();

    if (info.Length() > 2) {
	u = (RoseUnit) Nan::To<int32_t>(info[2]).FromJust();
    }

    double vals[3];
    ao->f_fmt->getOutArcCenter(*(ctl->asUnmanaged()), vals, pos, u);
    v8::Local<v8::Array> ret = Nan::New<v8::Array>(3);
    ret->Set(0, Nan::New(vals[0]));
    ret->Set(1, Nan::New(vals[1]));
    ret->Set(2, Nan::New(vals[2]));
    
    info.GetReturnValue().Set(ret);
}



// double[3] GetOutArcAxis(Adaptive, CtlPos p);
NAN_METHOD(Generate::GetOutArcAxis)
{
    Trace t(tc, "GetOutArcAxis");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    if (info.Length() == 2) return;

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    if (maybe1.IsEmpty()) return;

    Adaptive *ctl = Nan::ObjectWrap::Unwrap<Adaptive>(maybe1.ToLocalChecked());
    if (!ctl) return; // exception

    StixCtlPos pos = (StixCtlPos) Nan::To<int32_t>(info[1]).FromJust();
    double vals[3];
    ao->f_fmt->getOutArcAxis(*(ctl->asUnmanaged()), vals, pos);

    v8::Local<v8::Array> ret = Nan::New<v8::Array>(3);
    ret->Set(0, Nan::New(vals[0]));
    ret->Set(1, Nan::New(vals[1]));
    ret->Set(2, Nan::New(vals[2]));
    
    info.GetReturnValue().Set(ret);
}

// double[3] GetOutXformedPoint (double in_x, double in_y, double in_z);
NAN_METHOD(Generate::GetOutXformedPoint)
{
    Trace t(tc, "GetOutXformedPoint");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception

    if (info.Length() != 3) return;
    double vals[3], in[3];
    in[0] = Nan::To<double>(info[0]).FromJust(); 
    in[1] = Nan::To<double>(info[1]).FromJust();
    in[2] = Nan::To<double>(info[2]).FromJust();
    
    ao-> f_fmt->getOutXformedPoint(vals, in);
    
    v8::Local<v8::Array> ret = Nan::New<v8::Array>(3);
    ret->Set(0, Nan::New(vals[0]));
    ret->Set(1, Nan::New(vals[1]));
    ret->Set(2, Nan::New(vals[2]));
    info.GetReturnValue().Set(ret);
}


// double[3] GetOutXformedDir(double in_i, double in_j, double in_k);
NAN_METHOD(Generate::GetOutXformedDir)
{
    Trace t(tc, "GetOutXformedDir");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception

    if (info.Length() != 3) return;
    double vals[3], in[3];
    in[0] = Nan::To<double>(info[0]).FromJust(); 
    in[1] = Nan::To<double>(info[1]).FromJust();
    in[2] = Nan::To<double>(info[2]).FromJust();
    
    ao-> f_fmt->getOutXformedDir(vals, in);
    
    v8::Local<v8::Array> ret = Nan::New<v8::Array>(3);
    ret->Set(0, Nan::New(vals[0]));
    ret->Set(1, Nan::New(vals[1]));
    ret->Set(2, Nan::New(vals[2]));
    info.GetReturnValue().Set(ret);
}


	
// TraceComments strings:
// none,
// workplan,	// before each workplan
// workingstep,	// before each workingstep
// toolpath,	// before each toolpath
// point, 	// at each point.
// all 		// all possible comments.
//
// string GetTraceComments();
NAN_METHOD(Generate::GetTraceComments)
{
    Trace t(tc, "GetTraceComments");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception

    switch (ao->f_fmt->getTraceComments()) {
    case StixCtlGenerate::TraceComments_workplan:
	info.GetReturnValue().Set(CharTov8String("workplan"));
	break;

    case StixCtlGenerate::TraceComments_workingstep:
	info.GetReturnValue().Set(CharTov8String("workingstep"));
	break;

    case StixCtlGenerate::TraceComments_toolpath:
	info.GetReturnValue().Set(CharTov8String("toolpath"));
	break;

    case StixCtlGenerate::TraceComments_point:
	info.GetReturnValue().Set(CharTov8String("point"));
	break;

    case StixCtlGenerate::TraceComments_all:
	info.GetReturnValue().Set(CharTov8String("all"));
	break;

    default:
	info.GetReturnValue().Set(CharTov8String("none"));
	break;
    }
}


// void SetTraceComments (string t);
NAN_METHOD(Generate::SetTraceComments)
{
    Trace t(tc, "SetTraceComments");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception

    if (info.Length() != 1) return;
    if (!info[0]->IsString()) return;
    RoseStringObject str = v8StringToRose(info[0]);
    

    if (str.is_empty() || !rose_strcasecmp(str, "none")) {
	ao->f_fmt->setTraceComments(StixCtlGenerate::TraceComments_none);
	return;
    }

    if (!rose_strcasecmp(str, "all")) {
	ao->f_fmt->setTraceComments(StixCtlGenerate::TraceComments_all);
	return;
    }

    if (!rose_strcasecmp(str, "point")) {
	ao->f_fmt->setTraceComments(StixCtlGenerate::TraceComments_point);
	return;
    }

    if (!rose_strcasecmp(str, "toolpath")) {
	ao->f_fmt->setTraceComments(StixCtlGenerate::TraceComments_toolpath);
	return;
    }

    if (!rose_strcasecmp(str, "workinstep") ) {
	ao->f_fmt->setTraceComments(StixCtlGenerate::TraceComments_workingstep);
	return;
    }

    if (!rose_strcasecmp(str, "workplan")) {
	ao->f_fmt->setTraceComments(StixCtlGenerate::TraceComments_workplan);
	return;
    }
    ao->f_fmt->setTraceComments(StixCtlGenerate::TraceComments_none);
}


// string  GetFileExt();
NAN_METHOD(Generate::GetFileExt)
{
    Trace t(tc, "GetFileExt");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception

    info.GetReturnValue().Set(CharTov8String(ao->f_fmt->getFileExt()));
}

// void SetFileExt (string s);
NAN_METHOD(Generate::SetFileExt)
{
    Trace t(tc, "SetFileExt");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception

    if (info.Length() != 1) return;
    if (!info[0]->IsString()) return;
    RoseStringObject str = v8StringToRose(info[0]);
    
    ao->f_fmt->setFileExt(str);
}



// int GetDigits();
NAN_METHOD(Generate::GetDigits)
{
    Trace t(tc, "GetDigits");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_fmt->getDigits());
}

// void SetDigits (int d);
NAN_METHOD(Generate::SetDigits)
{
    Trace t(tc, "SetDigits");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;

    int val = Nan::To<int32_t>(info[0]).FromJust();
    ao->f_fmt->setDigits(val);
}

// int GetMinDigits();
NAN_METHOD(Generate::GetMinDigits)
{
    Trace t(tc, "GetMinDigits");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_fmt->getMinDigits());
}

// void SetMinDigits (int d);
NAN_METHOD(Generate::SetMinDigits)
{
    Trace t(tc, "SetMinDigits");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;

    int val = Nan::To<int32_t>(info[0]).FromJust();
    ao->f_fmt->setMinDigits(val);
}


// int GetSpindleDigits();
NAN_METHOD(Generate::GetSpindleDigits)
{
    Trace t(tc, "GetSpindleDigits");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_fmt->getSpindleDigits());
}

// void SetSpindleDigits (int d);
NAN_METHOD(Generate::SetSpindleDigits)
{
    Trace t(tc, "SetSpindleDigits");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;

    int val = Nan::To<int32_t>(info[0]).FromJust();
    ao->f_fmt->setSpindleDigits(val);
}




// int GetSpindleMinDigits();
NAN_METHOD(Generate::GetSpindleMinDigits)
{
    Trace t(tc, "GetSpindleMinDigits");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_fmt->getSpindleMinDigits());
}

// void SetSpindleMinDigits (int d);
NAN_METHOD(Generate::SetSpindleMinDigits)
{
    Trace t(tc, "SetSpindleMinDigits");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;

    int val = Nan::To<int32_t>(info[0]).FromJust();
    ao->f_fmt->setSpindleMinDigits(val);
}



// int GetFeedDigits();
NAN_METHOD(Generate::GetFeedDigits)
{
    Trace t(tc, "GetFeedDigits");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_fmt->getFeedDigits());
}

// void SetFeedDigits (int d);
NAN_METHOD(Generate::SetFeedDigits)
{
    Trace t(tc, "SetFeedDigits");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;

    int val = Nan::To<int32_t>(info[0]).FromJust();
    ao->f_fmt->setFeedDigits(val);
}


// int GetFeedMinDigits();
NAN_METHOD(Generate::GetFeedMinDigits)
{
    Trace t(tc, "GetFeedMinDigits");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_fmt->getFeedMinDigits());
}

// void SetFeedMinDigits (int d);
NAN_METHOD(Generate::SetFeedMinDigits)
{
    Trace t(tc, "SetFeedMinDigits");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;

    int val = Nan::To<int32_t>(info[0]).FromJust();
    ao->f_fmt->setFeedMinDigits(val);
}

// bool GetUseXform();
// void SetUseXform(bool yn);
NAN_METHOD(Generate::GetUseXform)
{
    Trace t(tc, "GetUseXform");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_fmt->getUseXform() != 0);
}

NAN_METHOD(Generate::SetUseXform)
{
    Trace t(tc, "SetUseXform");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;

    bool val = Nan::To<bool>(info[0]).FromJust();
    ao->f_fmt->setUseXform((int)val);
}

// double[16] GetDstXform();
NAN_METHOD(Generate::GetDstXform)
{
    Trace t(tc, "GetDstXform");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception

    const double * xf = ao->f_fmt->getDstXform();
    v8::Local<v8::Array> ret = Nan::New<v8::Array>(16);
    for (unsigned i=0; i<16; i++)
	ret->Set(i, Nan::New(xf[i]));

    info.GetReturnValue().Set(ret);
}


// void SetDstXform(double[16])
NAN_METHOD(Generate::SetDstXform)
{
    Trace t(tc, "SetDstXform");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;
    if (!info[0]->IsArray()) return;

    // Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    // if (maybe1.IsEmpty()) return;
    
    // v8::Local<v8::Array> xf = maybe1.ToLocalChecked().As<v8::Array>();
    // if (xf->Length() != 16) return;

    v8::Local<v8::Array> xf = v8::Local<v8::Array>::Cast(info[0]);
    if (xf->Length() != 16) return;
    
    double val[16];
    for (unsigned i=0; i<16; i++)
	val[i] = Nan::To<double>(xf->Get(i)).FromJust();
    
    ao->f_fmt->setDstXform(val);
}



// bool GetDstXformIsLeft();
NAN_METHOD(Generate::GetDstXformIsLeft)
{
    Trace t(tc, "GetDstXformIsLeft");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_fmt->getDstXformIsLeft() != 0);
}


// int GetProgramNumber();
// void SetProgramNumber (int d);
NAN_METHOD(Generate::GetProgramNumber)
{
    Trace t(tc, "GetProgramNumber");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_fmt->getProgramNumber());
}

NAN_METHOD(Generate::SetProgramNumber)
{
    Trace t(tc, "SetProgramNumber");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;

    int val = Nan::To<int32_t>(info[0]).FromJust();
    ao->f_fmt->setProgramNumber(val);
}

// Preferred length unit to use when generating code.

// RoseUnit GetProgramUnit();
// void SetProgramUnit (RoseUnit u);
NAN_METHOD(Generate::GetProgramUnit)
{
    Trace t(tc, "GetProgramUnit");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set((int32_t)ao->f_fmt->getProgramUnit());
}

NAN_METHOD(Generate::SetProgramUnit)
{
    Trace t(tc, "SetProgramUnit");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;

    RoseUnit u = (RoseUnit) Nan::To<int32_t>(info[0]).FromJust();
    ao->f_fmt->setProgramUnit(u);
}




// unit system to match the program unit or in the case of
// as-is, to match the toolpath units used by the stepnc
// process.
// void SetUnitSystem(Adaptive ctl);
NAN_METHOD(Generate::SetUnitSystem)
{
    Trace t(tc, "SetUnitSystem");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception

    if (info.Length() != 1) return;

    Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
    if (maybe1.IsEmpty()) return;
    Adaptive *ctl = Nan::ObjectWrap::Unwrap<Adaptive>(maybe1.ToLocalChecked());
    if (!ctl) return; // exception

    ao->f_fmt->setUnitSystem(*(ctl->asUnmanaged()));
}



// RoseUnit GetLenUnit();
// void SetLenUnit(RoseUnit u);
NAN_METHOD(Generate::GetLenUnit)
{
    Trace t(tc, "GetLenUnit");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set((int32_t)ao->f_fmt->getLenUnit());
}

NAN_METHOD(Generate::SetLenUnit)
{
    Trace t(tc, "SetLenUnit");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;

    RoseUnit u = (RoseUnit) Nan::To<int32_t>(info[0]).FromJust();
    ao->f_fmt->setLenUnit(u);
}

// RoseUnit GetFeedUnit();
// void SetFeedUnit(RoseUnit u);
NAN_METHOD(Generate::GetFeedUnit)
{
    Trace t(tc, "GetFeedUnit");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set((int32_t)ao->f_fmt->getFeedUnit());
}

NAN_METHOD(Generate::SetFeedUnit)
{
    Trace t(tc, "SetFeedUnit");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;

    RoseUnit u = (RoseUnit) Nan::To<int32_t>(info[0]).FromJust();
    ao->f_fmt->setFeedUnit(u);
}



// RoseUnit GetSpindleUnit();
// void SetSpindleUnit(RoseUnit u);

NAN_METHOD(Generate::GetSpindleUnit)
{
    Trace t(tc, "GetSpindleUnit");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set((int32_t)ao->f_fmt->getSpindleUnit());
}

NAN_METHOD(Generate::SetSpindleUnit)
{
    Trace t(tc, "SetSpindleUnit");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;

    RoseUnit u = (RoseUnit) Nan::To<int32_t>(info[0]).FromJust();
    ao->f_fmt->setSpindleUnit(u);
}




// Preferred work offset frame to use when generating code.
// Offset -1 means "as-is", do not change any offset settings.
// Offset 0 is treated as no work offset, 1 is the first on the
// machine, and so on.
// int GetWorkOffsetFrame();
// void SetWorkOffsetFrame (int d);
NAN_METHOD(Generate::GetWorkOffsetFrame)
{
    Trace t(tc, "GetWorkOffsetFrame");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set((int32_t)ao->f_fmt->getWorkOffsetFrame());
}

NAN_METHOD(Generate::SetWorkOffsetFrame)
{
    Trace t(tc, "SetWorkOffsetFrame");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;

    int val = (int) Nan::To<int32_t>(info[0]).FromJust();
    ao->f_fmt->setWorkOffsetFrame(val);
}


// void SetFeedStandalone();
NAN_METHOD(Generate::SetFeedStandalone)
{
    Trace t(tc, "SetFeedStandalone");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    ao->f_fmt->setFeedStandalone();
}

// void SetFeedInline();
NAN_METHOD(Generate::SetFeedInline)
{
    Trace t(tc, "SetFeedInline");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    ao->f_fmt->setFeedInline();
}

// bool GetFeedIsStandalone();
NAN_METHOD(Generate::GetFeedIsStandalone)
{
    Trace t(tc, "GetFeedIsStandalone");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception

    info.GetReturnValue().Set(ao->f_fmt->getFeedIsStandalone() != 0);
}


// /* Do an optional stop after every workingstep */
// bool GetStopAfterWorkingstep();
NAN_METHOD(Generate::GetStopAfterWorkingstep)
{
    Trace t(tc, "GetStopAfterWorkingstep");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception

    info.GetReturnValue().Set(ao->f_fmt->getStopAfterWorkingstep() != 0);
}

// void SetStopAfterWorkingstep (bool yn);
NAN_METHOD(Generate::SetStopAfterWorkingstep)
{
    Trace t(tc, "SetStopAfterWorkingstep");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;

    bool val = Nan::To<bool>(info[0]).FromJust();
    ao->f_fmt->setStopAfterWorkingstep((int)val);
}


// bool GetSupressXpos();
// void SetSupressXpos (bool yn);
NAN_METHOD(Generate::GetSupressXpos)
{
    Trace t(tc, "GetSupressXpos");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_fmt->getSupressXpos() != 0);
}

NAN_METHOD(Generate::SetSupressXpos)
{
    Trace t(tc, "SetSupressXpos");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;

    bool val = Nan::To<bool>(info[0]).FromJust();
    ao->f_fmt->setSupressXpos((int)val);
}


// bool GetSupressYpos();
// void SetSupressYpos (bool yn);
NAN_METHOD(Generate::GetSupressYpos)
{
    Trace t(tc, "GetSupressYpos");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_fmt->getSupressYpos() != 0);
}

NAN_METHOD(Generate::SetSupressYpos)
{
    Trace t(tc, "SetSupressYpos");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;

    bool val = Nan::To<bool>(info[0]).FromJust();
    ao->f_fmt->setSupressYpos((int)val);
}
// bool GetSupressZpos(); 	
// void SetSupressZpos (bool yn);
NAN_METHOD(Generate::GetSupressZpos)
{
    Trace t(tc, "GetSupressZpos");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_fmt->getSupressZpos() != 0);
}

NAN_METHOD(Generate::SetSupressZpos)
{
    Trace t(tc, "SetSupressZpos");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;

    bool val = Nan::To<bool>(info[0]).FromJust();
    ao->f_fmt->setSupressZpos((int)val);
}


// bool  GetUseBlocknums();
// void SetUseBlocknums (bool yn);
NAN_METHOD(Generate::GetUseBlocknums)
{
    Trace t(tc, "GetUseBlocknums");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_fmt->getUseBlocknums() != 0);
}

NAN_METHOD(Generate::SetUseBlocknums)
{
    Trace t(tc, "SetUseBlocknums");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;

    bool val = Nan::To<bool>(info[0]).FromJust();
    ao->f_fmt->setUseBlocknums((int)val);
}

// Maximum permissible block number, or zero for no limit.  After
// the limit is reached, the block number wraps around to 1.
// 
// int GetBlocknumLimit();
// void SetBlocknumLimit (int max);
NAN_METHOD(Generate::GetBlocknumLimit)
{
    Trace t(tc, "GetBlocknumLimit");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set((int32_t)ao->f_fmt->getBlocknumLimit());
}

NAN_METHOD(Generate::SetBlocknumLimit)
{
    Trace t(tc, "SetBlocknumLimit");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;

    int val = (int) Nan::To<int32_t>(info[0]).FromJust();
    ao->f_fmt->setBlocknumLimit(val);
}


// bool  GetUseWhitespace();
// void SetUseWhitespace (bool yn);
NAN_METHOD(Generate::GetUseWhitespace)
{
    Trace t(tc, "GetUseWhitespace");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    info.GetReturnValue().Set(ao->f_fmt->getUseWhitespace() != 0);
}

NAN_METHOD(Generate::SetUseWhitespace)
{
    Trace t(tc, "SetUseWhitespace");
    Generate* ao = Nan::ObjectWrap::Unwrap<Generate>(info.This());
    if (!ao) return; // exception
    if (info.Length() != 1) return;

    bool val = Nan::To<bool>(info[0]).FromJust();
    ao->f_fmt->setUseWhitespace((int)val);
}


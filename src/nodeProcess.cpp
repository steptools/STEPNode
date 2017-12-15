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

#include "nodeProcess.h"
#include "nodeUtils.h"

static TraceContext tc("Process");

#define THROW_ERROR(t) return;
// { t.error(); throw gcnew InvalidOperationException(); }


Process * Process::_singleton = nullptr;
NAN_METHOD(Process::New)
{
    if (info.IsConstructCall())
    {
	if (!info[0]->IsUndefined())
	{
	    return;
	}
	if (_singleton == nullptr)
	    _singleton = new Process();
	_singleton->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
    }
    else
    {
	return;
    }
}

NAN_MODULE_INIT(Process::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("Process").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "PlaneFinishMilling", PlaneFinishMilling);
    Nan::SetPrototypeMethod(tpl, "PlaneRoughMilling", PlaneRoughMilling);
    Nan::SetPrototypeMethod(tpl, "SetToolCoolantThroughTool", SetToolCoolantThroughTool);
    Nan::SetPrototypeMethod(tpl, "SetToolCornerRadius", SetToolCornerRadius);
    Nan::SetPrototypeMethod(tpl, "SetToolCurrentCornerRadius", SetToolCurrentCornerRadius);
    Nan::SetPrototypeMethod(tpl, "SetToolCurrentDiameter", SetToolCurrentDiameter);
    Nan::SetPrototypeMethod(tpl, "SetToolCurrentLength", SetToolCurrentLength);
    Nan::SetPrototypeMethod(tpl, "SetToolCuttingEdgeAngle", SetToolCuttingEdgeAngle);
    Nan::SetPrototypeMethod(tpl, "SetToolCuttingEdgeAngleLowerUpper", SetToolCuttingEdgeAngleLowerUpper);
    Nan::SetPrototypeMethod(tpl, "SetToolDiameter", SetToolDiameter);
    Nan::SetPrototypeMethod(tpl, "SetToolDiameterLowerUpper", SetToolDiameterLowerUpper);
    Nan::SetPrototypeMethod(tpl, "SetToolExpectedLife", SetToolExpectedLife);
    Nan::SetPrototypeMethod(tpl, "SetToolExpectedLifeLowerUpper", SetToolExpectedLifeLowerUpper);
    Nan::SetPrototypeMethod(tpl, "SetToolFluteCount", SetToolFluteCount);
    Nan::SetPrototypeMethod(tpl, "SetToolFluteLength", SetToolFluteLength);
    Nan::SetPrototypeMethod(tpl, "SetToolFluteLengthLowerUpper", SetToolFluteLengthLowerUpper);
    Nan::SetPrototypeMethod(tpl, "SetToolHandOfCut", SetToolHandOfCut);
    Nan::SetPrototypeMethod(tpl, "SetToolLength", SetToolLength);
    Nan::SetPrototypeMethod(tpl, "SetToolLengthLowerUpper", SetToolLengthLowerUpper);
    Nan::SetPrototypeMethod(tpl, "SetToolMaterial", SetToolMaterial);
    Nan::SetPrototypeMethod(tpl, "SetToolMaterialStandard", SetToolMaterialStandard);
    Nan::SetPrototypeMethod(tpl, "SetToolOverallAssemblyLength", SetToolOverallAssemblyLength);
    Nan::SetPrototypeMethod(tpl, "SetToolOverallAssemblyLengthLowerUpper", SetToolOverallAssemblyLengthLowerUpper);
    Nan::SetPrototypeMethod(tpl, "SetToolRadiusLowerUpper", SetToolRadiusLowerUpper);
    Nan::SetPrototypeMethod(tpl, "SetToolRecommendedFeed", SetToolRecommendedFeed);
    Nan::SetPrototypeMethod(tpl, "SetToolRecommendedFeedLowerUpper", SetToolRecommendedFeedLowerUpper);
    Nan::SetPrototypeMethod(tpl, "SetToolRecommendedSpeed", SetToolRecommendedSpeed);
    Nan::SetPrototypeMethod(tpl, "SetToolRecommendedSpeedLowerUpper", SetToolRecommendedSpeedLowerUpper);
    Nan::SetPrototypeMethod(tpl, "SetToolTipAngle", SetToolTipAngle);
    Nan::SetPrototypeMethod(tpl, "SetToolTipAngleLowerUpper", SetToolTipAngleLowerUpper);
    
    constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("Process").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());

}

// void PlaneFinishMilling ( int ws_id, double allowance, axial_depth );
NAN_METHOD(Process::PlaneFinishMilling)
{
    Trace t(tc, "PlaneFinishMilling");
    Process* pro = Nan::ObjectWrap::Unwrap<Process>(info.This());
    if (!pro) return;

    if (info.Length() != 3) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsNumber()) return;
    if (!info[2]->IsNumber()) return;
	
    int wsid = Nan::To<int32_t>(info[0]).FromJust(); 
    double allowance = Nan::To<double>(info[1]).FromJust(); 
    double axial_depth = Nan::To<double>(info[2]).FromJust(); 

    int ok = pro->_process-> plane_finish_milling(wsid, allowance, axial_depth);
    if (!ok) {
	THROW_ERROR(t);
    }
}



// void PlaneRoughMilling ( int ws_id, double allowance, axial_depth );
NAN_METHOD(Process::PlaneRoughMilling)
{
    Trace t(tc, "PlaneRoughMilling");
    Process* pro = Nan::ObjectWrap::Unwrap<Process>(info.This());
    if (!pro) return;

    if (info.Length() != 3) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsNumber()) return;
    if (!info[2]->IsNumber()) return;
	
    int wsid = Nan::To<int32_t>(info[0]).FromJust(); 
    double allowance = Nan::To<double>(info[1]).FromJust(); 
    double axial_depth = Nan::To<double>(info[2]).FromJust(); 

    int ok = pro->_process-> plane_rough_milling(wsid, allowance, axial_depth);
    if (!ok) {
	THROW_ERROR(t);
    }
}



// void SetToolCoolantThroughTool ( int tl_id, int on_off );
NAN_METHOD(Process::SetToolCoolantThroughTool)
{
    Trace t(tc, "SetToolCoolantThroughTool");
    Process* pro = Nan::ObjectWrap::Unwrap<Process>(info.This());
    if (!pro) return;

    if (info.Length() != 2) return;
    if (!info[0]->IsInt32()) return;
	
    int tlid = Nan::To<int32_t>(info[0]).FromJust(); 
    int on_off = Nan::To<int32_t>(info[0]).FromJust(); 

    int ok = pro->_process-> set_tool_coolant_through_tool(tlid, on_off);
    if (!ok) {
	THROW_ERROR(t);
    }
}


// void SetToolCornerRadius ( int tl_id, double radius );
NAN_METHOD(Process::SetToolCornerRadius)
{
    Trace t(tc, "SetToolCornerRadius");
    Process* pro = Nan::ObjectWrap::Unwrap<Process>(info.This());
    if (!pro) return;

    if (info.Length() != 2) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsNumber()) return;
	
    int tlid = Nan::To<int32_t>(info[0]).FromJust(); 
    double rad = Nan::To<double>(info[1]).FromJust(); 

    int ok = pro->_process-> set_tool_radius(tlid, rad);
    if (!ok) {
	THROW_ERROR(t);
    }
}

// void SetToolCurrentCornerRadius ( int tl_id, double current_corner_radius );
NAN_METHOD(Process::SetToolCurrentCornerRadius)
{
    Trace t(tc, "SetToolCurrentCornerRadius");
    Process* pro = Nan::ObjectWrap::Unwrap<Process>(info.This());
    if (!pro) return;

    if (info.Length() != 2) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsNumber()) return;
	
    int tlid = Nan::To<int32_t>(info[0]).FromJust(); 
    double rad = Nan::To<double>(info[1]).FromJust(); 

    int ok = pro->_process-> tool_current_radius(tlid, rad);
    if (!ok) {
	THROW_ERROR(t);
    }
}

// void SetToolCurrentDiameter ( int tl_id, double current_diameter );
NAN_METHOD(Process::SetToolCurrentDiameter)
{
    Trace t(tc, "SetToolCurrentDiameter");
    Process* pro = Nan::ObjectWrap::Unwrap<Process>(info.This());
    if (!pro) return;

    if (info.Length() != 2) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsNumber()) return;
	
    int tlid = Nan::To<int32_t>(info[0]).FromJust(); 
    double dia = Nan::To<double>(info[1]).FromJust(); 

    int ok = pro->_process-> tool_current_diameter(tlid, dia);
    if (!ok) {
	THROW_ERROR(t);
    }
}

// void SetToolCurrentLength ( int tl_id, double current_length );
NAN_METHOD(Process::SetToolCurrentLength)
{
    Trace t(tc, "SetToolCurrentLength");
    Process* pro = Nan::ObjectWrap::Unwrap<Process>(info.This());
    if (!pro) return;

    if (info.Length() != 2) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsNumber()) return;
	
    int tlid = Nan::To<int32_t>(info[0]).FromJust(); 
    double len = Nan::To<double>(info[1]).FromJust(); 

    int ok = pro->_process-> tool_current_functional_length(tlid, len);
    if (!ok) {
	THROW_ERROR(t);
    }
}

// void SetToolCuttingEdgeAngle ( int tl_id, double angle );
NAN_METHOD(Process::SetToolCuttingEdgeAngle)
{
    Trace t(tc, "SetToolCuttingEdgeAngle");
    Process* pro = Nan::ObjectWrap::Unwrap<Process>(info.This());
    if (!pro) return;

    if (info.Length() != 2) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsNumber()) return;
	
    int tlid = Nan::To<int32_t>(info[0]).FromJust(); 
    double ang = Nan::To<double>(info[1]).FromJust(); 

    int ok = pro->_process-> set_tool_taper_angle(tlid, ang);
    if (!ok) {
	THROW_ERROR(t);
    }
}

// void SetToolCuttingEdgeAngleLowerUpper ( int tl_id, double value, lower, string lreason, double upper, string ureason );
NAN_METHOD(Process::SetToolCuttingEdgeAngleLowerUpper)
{
    Trace t(tc, "SetToolCuttingEdgeAngleLowerUpper");
    Process* pro = Nan::ObjectWrap::Unwrap<Process>(info.This());
    if (!pro) return;

    if (info.Length() != 6) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsNumber()) return;
    if (!info[2]->IsNumber()) return;
    if (!info[3]->IsString()) return;
    if (!info[4]->IsNumber()) return;
    if (!info[5]->IsString()) return;
	
    int tlid = Nan::To<int32_t>(info[0]).FromJust(); 
    double val = Nan::To<double>(info[1]).FromJust(); 
    double lower = Nan::To<double>(info[2]).FromJust(); 
    double upper = Nan::To<double>(info[4]).FromJust(); 
    char * lreason = 0;
    char * ureason = 0;
    v8StringToChar(info[3], lreason);
    v8StringToChar(info[5], ureason);
    int ok = pro->_process-> set_tool_taper_angle_lower_and_upper (
	tlid, val, lower, lreason, upper, ureason
	);
    delete [] lreason;
    delete [] ureason;
    
    if (!ok) {
	THROW_ERROR(t);
    }
}

// void SetToolDiameter ( int tl_id, double diameter );
NAN_METHOD(Process::SetToolDiameter)
{
    Trace t(tc, "SetToolDiameter");
    Process* pro = Nan::ObjectWrap::Unwrap<Process>(info.This());
    if (!pro) return;

    if (info.Length() != 2) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsNumber()) return;
	
    int tlid = Nan::To<int32_t>(info[0]).FromJust(); 
    double val = Nan::To<double>(info[1]).FromJust(); 

    int ok = pro->_process-> set_tool_diameter(tlid, val);
    if (!ok) {
	THROW_ERROR(t);
    }
}

// void SetToolDiameterLowerUpper ( int tl_id, double value, lower, string lreason, double upper, string ureason );
NAN_METHOD(Process::SetToolDiameterLowerUpper)
{
    Trace t(tc, "SetToolDiameterLowerUpper");
    Process* pro = Nan::ObjectWrap::Unwrap<Process>(info.This());
    if (!pro) return;

    if (info.Length() != 6) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsNumber()) return;
    if (!info[2]->IsNumber()) return;
    if (!info[3]->IsString()) return;
    if (!info[4]->IsNumber()) return;
    if (!info[5]->IsString()) return;
	
    int tlid = Nan::To<int32_t>(info[0]).FromJust(); 
    double val = Nan::To<double>(info[1]).FromJust(); 
    double lower = Nan::To<double>(info[2]).FromJust(); 
    double upper = Nan::To<double>(info[4]).FromJust(); 
    char * lreason = 0;
    char * ureason = 0;
    v8StringToChar(info[3], lreason);
    v8StringToChar(info[5], ureason);
    int ok = pro->_process-> set_tool_diameter_lower_and_upper (
	tlid, val, lower, lreason, upper, ureason
	);
    delete [] lreason;
    delete [] ureason;
    
    if (!ok) {
	THROW_ERROR(t);
    }
}


// void SetToolExpectedLife ( int tl_id, double minutes );
NAN_METHOD(Process::SetToolExpectedLife)
{
    Trace t(tc, "SetToolExpectedLife");
    Process* pro = Nan::ObjectWrap::Unwrap<Process>(info.This());
    if (!pro) return;

    if (info.Length() != 2) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsNumber()) return;
	
    int tlid = Nan::To<int32_t>(info[0]).FromJust(); 
    double val = Nan::To<double>(info[1]).FromJust(); 

    int ok = pro->_process-> set_tool_expected_life(tlid, val);
    if (!ok) {
	THROW_ERROR(t);
    }
}



// void SetToolExpectedLifeLowerUpper ( int tl_id, double value, lower, string lreason, double upper, string ureason );
NAN_METHOD(Process::SetToolExpectedLifeLowerUpper)
{
    Trace t(tc, "SetToolExpectedLifeLowerUpper");
    Process* pro = Nan::ObjectWrap::Unwrap<Process>(info.This());
    if (!pro) return;

    if (info.Length() != 6) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsNumber()) return;
    if (!info[2]->IsNumber()) return;
    if (!info[3]->IsString()) return;
    if (!info[4]->IsNumber()) return;
    if (!info[5]->IsString()) return;
	
    int tlid = Nan::To<int32_t>(info[0]).FromJust(); 
    double val = Nan::To<double>(info[1]).FromJust(); 
    double lower = Nan::To<double>(info[2]).FromJust(); 
    double upper = Nan::To<double>(info[4]).FromJust(); 
    char * lreason = 0;
    char * ureason = 0;
    v8StringToChar(info[3], lreason);
    v8StringToChar(info[5], ureason);
    int ok = pro->_process-> set_tool_expected_life_lower_and_upper (
	tlid, val, lower, lreason, upper, ureason
	);
    delete [] lreason;
    delete [] ureason;
    
    if (!ok) {
	THROW_ERROR(t);
    }
}


// void SetToolFluteCount ( int tl_id, double flute_count );
NAN_METHOD(Process::SetToolFluteCount)
{
    Trace t(tc, "SetToolFluteCount");
    Process* pro = Nan::ObjectWrap::Unwrap<Process>(info.This());
    if (!pro) return;

    if (info.Length() != 2) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsNumber()) return;
	
    int tlid = Nan::To<int32_t>(info[0]).FromJust(); 
    double val = Nan::To<double>(info[1]).FromJust(); 

    int ok = pro->_process-> set_tool_number_of_flutes(tlid, val);
    if (!ok) {
	THROW_ERROR(t);
    }
}


// void SetToolFluteLength ( int tl_id, double flute_length );
NAN_METHOD(Process::SetToolFluteLength)
{
    Trace t(tc, "SetToolExpectedLife");
    Process* pro = Nan::ObjectWrap::Unwrap<Process>(info.This());
    if (!pro) return;

    if (info.Length() != 2) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsNumber()) return;
	
    int tlid = Nan::To<int32_t>(info[0]).FromJust(); 
    double val = Nan::To<double>(info[1]).FromJust(); 

    int ok = pro->_process-> set_tool_flute_length(tlid, val);
    if (!ok) {
	THROW_ERROR(t);
    }
}


// void SetToolFluteLengthLowerUpper ( int tl_id, double value, lower, string lreason, double upper, string ureason );
NAN_METHOD(Process::SetToolFluteLengthLowerUpper)
{
    Trace t(tc, "SetToolFluteLengthLowerUpper");
    Process* pro = Nan::ObjectWrap::Unwrap<Process>(info.This());
    if (!pro) return;

    if (info.Length() != 6) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsNumber()) return;
    if (!info[2]->IsNumber()) return;
    if (!info[3]->IsString()) return;
    if (!info[4]->IsNumber()) return;
    if (!info[5]->IsString()) return;
	
    int tlid = Nan::To<int32_t>(info[0]).FromJust(); 
    double val = Nan::To<double>(info[1]).FromJust(); 
    double lower = Nan::To<double>(info[2]).FromJust(); 
    double upper = Nan::To<double>(info[4]).FromJust(); 
    char * lreason = 0;
    char * ureason = 0;
    v8StringToChar(info[3], lreason);
    v8StringToChar(info[5], ureason);
    int ok = pro->_process-> set_tool_flute_length_lower_and_upper(
	tlid, val, lower, lreason, upper, ureason
	);
    delete [] lreason;
    delete [] ureason;
    
    if (!ok) {
	THROW_ERROR(t);
    }
}


// void SetToolHandOfCut ( int tl_id, string left_neutral_right );
NAN_METHOD(Process::SetToolHandOfCut)
{
    Trace t(tc, "SetToolHandOfCut");
    Process* pro = Nan::ObjectWrap::Unwrap<Process>(info.This());
    if (!pro) return;

    if (info.Length() != 2) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsString()) return;
	
    int tlid = Nan::To<int32_t>(info[0]).FromJust(); 
    char * hand = 0;
    v8StringToChar(info[1], hand);
    int ok = pro->_process-> set_tool_hand_of_cut(tlid,hand);
    delete [] hand;
    
    if (!ok) {
	THROW_ERROR(t);
    }
}
    


// void SetToolLength ( int tl_id, double length );
NAN_METHOD(Process::SetToolLength)
{
    Trace t(tc, "SetToolLength");
    Process* pro = Nan::ObjectWrap::Unwrap<Process>(info.This());
    if (!pro) return;

    if (info.Length() != 2) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsNumber()) return;
	
    int tlid = Nan::To<int32_t>(info[0]).FromJust(); 
    double val = Nan::To<double>(info[1]).FromJust(); 

    int ok = pro->_process-> set_tool_functional_length(tlid, val);
    if (!ok) {
	THROW_ERROR(t);
    }
}


// void SetToolLengthLowerUpper ( int tl_id, double value, lower, string lreason, double upper, string ureason );
NAN_METHOD(Process::SetToolLengthLowerUpper)
{
    Trace t(tc, "SetToolLengthLowerUpper");
    Process* pro = Nan::ObjectWrap::Unwrap<Process>(info.This());
    if (!pro) return;

    if (info.Length() != 6) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsNumber()) return;
    if (!info[2]->IsNumber()) return;
    if (!info[3]->IsString()) return;
    if (!info[4]->IsNumber()) return;
    if (!info[5]->IsString()) return;
	
    int tlid = Nan::To<int32_t>(info[0]).FromJust(); 
    double val = Nan::To<double>(info[1]).FromJust(); 
    double lower = Nan::To<double>(info[2]).FromJust(); 
    double upper = Nan::To<double>(info[4]).FromJust(); 
    char * lreason = 0;
    char * ureason = 0;
    v8StringToChar(info[3], lreason);
    v8StringToChar(info[5], ureason);
    int ok = pro->_process-> set_tool_functional_length_lower_and_upper (
	tlid, val, lower, lreason, upper, ureason
	);
    delete [] lreason;
    delete [] ureason;
    
    if (!ok) {
	THROW_ERROR(t);
    }
}



// void SetToolMaterial ( int tl_id, string material );
NAN_METHOD(Process::SetToolMaterial)
{
    Trace t(tc, "SetToolMaterial");
    Process* pro = Nan::ObjectWrap::Unwrap<Process>(info.This());
    if (!pro) return;

    if (info.Length() != 2) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsString()) return;
	
    int tlid = Nan::To<int32_t>(info[0]).FromJust(); 
    char * val = 0;
    v8StringToChar(info[1], val);
    int ok = pro->_process-> set_tool_cutting_material(tlid,val);
    delete [] val;
    
    if (!ok) {
	THROW_ERROR(t);
    }
}



// void SetToolMaterialStandard ( int tl_id, string standard );
NAN_METHOD(Process::SetToolMaterialStandard)
{
    Trace t(tc, "SetToolMaterialStandard");
    Process* pro = Nan::ObjectWrap::Unwrap<Process>(info.This());
    if (!pro) return;

    if (info.Length() != 2) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsString()) return;
	
    int tlid = Nan::To<int32_t>(info[0]).FromJust(); 
    char * val = 0;
    v8StringToChar(info[1], val);
    int ok = pro->_process-> set_tool_cutting_material_standard(tlid,val);
    delete [] val;
    
    if (!ok) {
	THROW_ERROR(t);
    }
}


// void SetToolOverallAssemblyLength ( int tl_id, double length );
NAN_METHOD(Process::SetToolOverallAssemblyLength)
{
    Trace t(tc, "SetToolOverallAssemblyLength");
    Process* pro = Nan::ObjectWrap::Unwrap<Process>(info.This());
    if (!pro) return;

    if (info.Length() != 2) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsNumber()) return;
	
    int tlid = Nan::To<int32_t>(info[0]).FromJust(); 
    double val = Nan::To<double>(info[1]).FromJust(); 

    int ok = pro->_process-> set_tool_overall_length(tlid, val);
    if (!ok) {
	THROW_ERROR(t);
    }
}

// void SetToolOverallAssemblyLengthLowerUpper ( int tl_id, double value, lower, string lreason, double upper, string ureason );
NAN_METHOD(Process::SetToolOverallAssemblyLengthLowerUpper)
{
    Trace t(tc, "SetToolOverallAssemblyLengthLowerUpper");
    Process* pro = Nan::ObjectWrap::Unwrap<Process>(info.This());
    if (!pro) return;

    if (info.Length() != 6) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsNumber()) return;
    if (!info[2]->IsNumber()) return;
    if (!info[3]->IsString()) return;
    if (!info[4]->IsNumber()) return;
    if (!info[5]->IsString()) return;
	
    int tlid = Nan::To<int32_t>(info[0]).FromJust(); 
    double val = Nan::To<double>(info[1]).FromJust(); 
    double lower = Nan::To<double>(info[2]).FromJust(); 
    double upper = Nan::To<double>(info[4]).FromJust(); 
    char * lreason = 0;
    char * ureason = 0;
    v8StringToChar(info[3], lreason);
    v8StringToChar(info[5], ureason);
    int ok = pro->_process-> set_tool_overall_assembly_length_lower_and_upper(
	tlid, val, lower, lreason, upper, ureason
	);
    delete [] lreason;
    delete [] ureason;
    
    if (!ok) {
	THROW_ERROR(t);
    }
}



// void SetToolRadiusLowerUpper ( int tl_id, double value, lower, string lreason, double upper, string ureason );
NAN_METHOD(Process::SetToolRadiusLowerUpper)
{
    Trace t(tc, "SetToolRadiusLowerUpper");
    Process* pro = Nan::ObjectWrap::Unwrap<Process>(info.This());
    if (!pro) return;

    if (info.Length() != 6) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsNumber()) return;
    if (!info[2]->IsNumber()) return;
    if (!info[3]->IsString()) return;
    if (!info[4]->IsNumber()) return;
    if (!info[5]->IsString()) return;
	
    int tlid = Nan::To<int32_t>(info[0]).FromJust(); 
    double val = Nan::To<double>(info[1]).FromJust(); 
    double lower = Nan::To<double>(info[2]).FromJust(); 
    double upper = Nan::To<double>(info[4]).FromJust(); 
    char * lreason = 0;
    char * ureason = 0;
    v8StringToChar(info[3], lreason);
    v8StringToChar(info[5], ureason);
    int ok = pro->_process-> set_tool_radius_lower_and_upper(
	tlid, val, lower, lreason, upper, ureason
	);
    delete [] lreason;
    delete [] ureason;
    
    if (!ok) {
	THROW_ERROR(t);
    }
}


// void SetToolRecommendedFeed ( int tl_id, double feedrate );
NAN_METHOD(Process::SetToolRecommendedFeed)
{
    Trace t(tc, "SetToolRecommendedFeed");
    Process* pro = Nan::ObjectWrap::Unwrap<Process>(info.This());
    if (!pro) return;

    if (info.Length() != 2) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsNumber()) return;
	
    int tlid = Nan::To<int32_t>(info[0]).FromJust(); 
    double val = Nan::To<double>(info[1]).FromJust(); 

    int ok = pro->_process-> set_tool_recommended_feed(tlid, val);
    if (!ok) {
	THROW_ERROR(t);
    }
}


// void SetToolRecommendedFeedLowerUpper ( int tl_id, double value, lower, string lreason, double upper, string ureason );
NAN_METHOD(Process::SetToolRecommendedFeedLowerUpper)
{
    Trace t(tc, "SetToolRecommendedFeedLowerUpper");
    Process* pro = Nan::ObjectWrap::Unwrap<Process>(info.This());
    if (!pro) return;

    if (info.Length() != 6) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsNumber()) return;
    if (!info[2]->IsNumber()) return;
    if (!info[3]->IsString()) return;
    if (!info[4]->IsNumber()) return;
    if (!info[5]->IsString()) return;
	
    int tlid = Nan::To<int32_t>(info[0]).FromJust(); 
    double val = Nan::To<double>(info[1]).FromJust(); 
    double lower = Nan::To<double>(info[2]).FromJust(); 
    double upper = Nan::To<double>(info[4]).FromJust(); 
    char * lreason = 0;
    char * ureason = 0;
    v8StringToChar(info[3], lreason);
    v8StringToChar(info[5], ureason);
    int ok = pro->_process-> set_tool_recommended_feed_lower_and_upper(
	tlid, val, lower, lreason, upper, ureason
	);
    delete [] lreason;
    delete [] ureason;
    
    if (!ok) {
	THROW_ERROR(t);
    }
}



// void SetToolRecommendedSpeed ( int tl_id, double spindle_speed );
NAN_METHOD(Process::SetToolRecommendedSpeed)
{
    Trace t(tc, "SetToolRecommendedSpeed");
    Process* pro = Nan::ObjectWrap::Unwrap<Process>(info.This());
    if (!pro) return;

    if (info.Length() != 2) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsNumber()) return;
	
    int tlid = Nan::To<int32_t>(info[0]).FromJust(); 
    double val = Nan::To<double>(info[1]).FromJust(); 

    int ok = pro->_process-> set_tool_recommended_speed(tlid, val);
    if (!ok) {
	THROW_ERROR(t);
    }
}


// void SetToolRecommendedSpeedLowerUpper ( int tl_id, double value, lower, string lreason, double upper, string ureason );
NAN_METHOD(Process::SetToolRecommendedSpeedLowerUpper)
{
    Trace t(tc, "SetToolRecommendedSpeedLowerUpper");
    Process* pro = Nan::ObjectWrap::Unwrap<Process>(info.This());
    if (!pro) return;

    if (info.Length() != 6) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsNumber()) return;
    if (!info[2]->IsNumber()) return;
    if (!info[3]->IsString()) return;
    if (!info[4]->IsNumber()) return;
    if (!info[5]->IsString()) return;
	
    int tlid = Nan::To<int32_t>(info[0]).FromJust(); 
    double val = Nan::To<double>(info[1]).FromJust(); 
    double lower = Nan::To<double>(info[2]).FromJust(); 
    double upper = Nan::To<double>(info[4]).FromJust(); 
    char * lreason = 0;
    char * ureason = 0;
    v8StringToChar(info[3], lreason);
    v8StringToChar(info[5], ureason);
    int ok = pro->_process-> set_tool_recommended_speed_lower_and_upper(
	tlid, val, lower, lreason, upper, ureason
	);
    delete [] lreason;
    delete [] ureason;
    
    if (!ok) {
	THROW_ERROR(t);
    }
}


// void SetToolTipAngle ( int tl_id, double angle );
NAN_METHOD(Process::SetToolTipAngle)
{
    Trace t(tc, "SetToolTipAngle");
    Process* pro = Nan::ObjectWrap::Unwrap<Process>(info.This());
    if (!pro) return;

    if (info.Length() != 2) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsNumber()) return;
	
    int tlid = Nan::To<int32_t>(info[0]).FromJust(); 
    double val = Nan::To<double>(info[1]).FromJust(); 

    int ok = pro->_process-> set_tool_tip_angle(tlid, val);
    if (!ok) {
	THROW_ERROR(t);
    }
}


// void SetToolTipAngleLowerUpper ( int tl_id, double value, lower, string lreason, double upper, string ureason );
NAN_METHOD(Process::SetToolTipAngleLowerUpper)
{
    Trace t(tc, "SetToolTipAngleLowerUpper");
    Process* pro = Nan::ObjectWrap::Unwrap<Process>(info.This());
    if (!pro) return;

    if (info.Length() != 6) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsNumber()) return;
    if (!info[2]->IsNumber()) return;
    if (!info[3]->IsString()) return;
    if (!info[4]->IsNumber()) return;
    if (!info[5]->IsString()) return;
	
    int tlid = Nan::To<int32_t>(info[0]).FromJust(); 
    double val = Nan::To<double>(info[1]).FromJust(); 
    double lower = Nan::To<double>(info[2]).FromJust(); 
    double upper = Nan::To<double>(info[4]).FromJust(); 
    char * lreason = 0;
    char * ureason = 0;
    v8StringToChar(info[3], lreason);
    v8StringToChar(info[5], ureason);
    int ok = pro->_process-> set_tool_tip_angle_lower_and_upper (
	tlid, val, lower, lreason, upper, ureason
	);
    delete [] lreason;
    delete [] ureason;
    
    if (!ok) {
	THROW_ERROR(t);
    }
}



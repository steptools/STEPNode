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
// Author: Samson Bonfante (bonfante@steptools.com)
//

#include "nodeAptStepMaker.h"
#include "nodeUtils.h"

#include <stncapt/Trace.h>

static TraceContext tc("AptStepMaker");

#define THROW_ERROR(t) return;
// { t.error(); throw gcnew InvalidOperationException(); }


AptStepMaker* AptStepMaker::_singleton = nullptr;

apt2step* AptStepMaker::getApt() {
    if (_singleton == nullptr)
	_singleton = new AptStepMaker();
    return _singleton->_apt;
}

NAN_METHOD(AptStepMaker::New)
{

    if (info.IsConstructCall())
    {
	if (!info[0]->IsUndefined())
	{
	    return;
	}
	if (_singleton == nullptr)
	    _singleton = new AptStepMaker();
	_singleton->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
    }
    else
    {
	return;
    }
}

NAN_MODULE_INIT(AptStepMaker::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("AptStepMaker").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "ArcXYPlane", ArcXYPlane);
    Nan::SetPrototypeMethod(tpl, "ArcYZPlane", ArcYZPlane);
    Nan::SetPrototypeMethod(tpl, "ArcZXPlane", ArcZXPlane);
    Nan::SetPrototypeMethod(tpl, "CamModeOff", CamModeOff);
    Nan::SetPrototypeMethod(tpl, "CamModeOn", CamModeOn);
    Nan::SetPrototypeMethod(tpl, "CoolantMist", CoolantMist);
    Nan::SetPrototypeMethod(tpl, "CoolantOff", CoolantOff);
    Nan::SetPrototypeMethod(tpl, "CoolantOn", CoolantOn);
    Nan::SetPrototypeMethod(tpl, "CoolantThru", CoolantThru);
    Nan::SetPrototypeMethod(tpl, "DefineTool", DefineTool);
    Nan::SetPrototypeMethod(tpl, "ExecutableToSelective", ExecutableToSelective);
    Nan::SetPrototypeMethod(tpl, "ExecutableWorkpieceAsIs", ExecutableWorkpieceAsIs);
    Nan::SetPrototypeMethod(tpl, "ExecutableWorkpieceRemoval", ExecutableWorkpieceRemoval);
    Nan::SetPrototypeMethod(tpl, "ExecutableWorkpieceReuseAsIs", ExecutableWorkpieceReuseAsIs);
    Nan::SetPrototypeMethod(tpl, "ExecutableWorkpieceReuseRemoval", ExecutableWorkpieceReuseRemoval);
    Nan::SetPrototypeMethod(tpl, "ExecutableWorkpieceReuseToBe", ExecutableWorkpieceReuseToBe);
    Nan::SetPrototypeMethod(tpl, "ExecutableWorkpieceToBe", ExecutableWorkpieceToBe);
    Nan::SetPrototypeMethod(tpl, "Feedrate", Feedrate);
    Nan::SetPrototypeMethod(tpl, "FeedrateUnit", FeedrateUnit);
    Nan::SetPrototypeMethod(tpl, "Fixture", Fixture);
    Nan::SetPrototypeMethod(tpl, "GenerateToolGeometry", GenerateToolGeometry);
    Nan::SetPrototypeMethod(tpl, "GeometryForTool", GeometryForTool);
    Nan::SetPrototypeMethod(tpl, "GeometryForToolNumber", GeometryForToolNumber);
    Nan::SetPrototypeMethod(tpl, "GetCurrentFixture", GetCurrentFixture);
    Nan::SetPrototypeMethod(tpl, "GetCurrentFunction", GetCurrentFunction);
    Nan::SetPrototypeMethod(tpl, "GetCurrentRawpiece", GetCurrentRawpiece);
    Nan::SetPrototypeMethod(tpl, "GetCurrentTech", GetCurrentTech);
    Nan::SetPrototypeMethod(tpl, "GetCurrentTool", GetCurrentTool);
    Nan::SetPrototypeMethod(tpl, "GetCurrentToolpath", GetCurrentToolpath);
    Nan::SetPrototypeMethod(tpl, "GetCurrentWorkingstep", GetCurrentWorkingstep);
    Nan::SetPrototypeMethod(tpl, "GetCurrentWorkpiece", GetCurrentWorkpiece);
    Nan::SetPrototypeMethod(tpl, "GetCurrentWorkplan", GetCurrentWorkplan);
    Nan::SetPrototypeMethod(tpl, "GetExecutableWorkpieceAsIs", GetExecutableWorkpieceAsIs);
    Nan::SetPrototypeMethod(tpl, "GetExecutableWorkpieceFixture", GetExecutableWorkpieceFixture);
    Nan::SetPrototypeMethod(tpl, "GetExecutableWorkpieceRemoval", GetExecutableWorkpieceRemoval);
    Nan::SetPrototypeMethod(tpl, "GetExecutableWorkpieceToBe", GetExecutableWorkpieceToBe);
    Nan::SetPrototypeMethod(tpl, "GetIDFromUUID", GetIDFromUUID);
    Nan::SetPrototypeMethod(tpl, "GetToolEID", GetToolEID);
    Nan::SetPrototypeMethod(tpl, "GetToolIdentifier", GetToolIdentifier);
    Nan::SetPrototypeMethod(tpl, "GetToolNumber", GetToolNumber);
    Nan::SetPrototypeMethod(tpl, "GetUUID", GetUUID);
    Nan::SetPrototypeMethod(tpl, "GetWorkpieceExecutableAll", GetWorkpieceExecutableAll);
    Nan::SetPrototypeMethod(tpl, "GetWorkpiecePlacement", GetWorkpiecePlacement);
    Nan::SetPrototypeMethod(tpl, "GetWorkplanSetup", GetWorkplanSetup);
    Nan::SetPrototypeMethod(tpl, "GoToXYZ", GoToXYZ);
    Nan::SetPrototypeMethod(tpl, "GoToXYZ_ABC", GoToXYZ_ABC);
    Nan::SetPrototypeMethod(tpl, "GoToXYZ_IJK", GoToXYZ_IJK);
    Nan::SetPrototypeMethod(tpl, "GoToXYZ_IJK_ABC", GoToXYZ_IJK_ABC);
    Nan::SetPrototypeMethod(tpl, "GoToXYZ_IJK_REF_ABC", GoToXYZ_IJK_REF_ABC);
    Nan::SetPrototypeMethod(tpl, "Inches", Inches);
    Nan::SetPrototypeMethod(tpl, "IsToolDefined", IsToolDefined);
    Nan::SetPrototypeMethod(tpl, "LoadTool", LoadTool);
    Nan::SetPrototypeMethod(tpl, "MakeRawBox", MakeRawBox);
    Nan::SetPrototypeMethod(tpl, "Millimeters", Millimeters);
    Nan::SetPrototypeMethod(tpl, "NewProject", NewProject);
    Nan::SetPrototypeMethod(tpl, "OpenProject", OpenProject);
    Nan::SetPrototypeMethod(tpl, "OpenSTEP", OpenSTEP);
    Nan::SetPrototypeMethod(tpl, "PartNo", PartNo);
    Nan::SetPrototypeMethod(tpl, "PutWorkpiecePlacement", PutWorkpiecePlacement);
    Nan::SetPrototypeMethod(tpl, "PutWorkplanSetup", PutWorkplanSetup);
    Nan::SetPrototypeMethod(tpl, "Rapid", Rapid);
    Nan::SetPrototypeMethod(tpl, "Rawpiece", Rawpiece);
    Nan::SetPrototypeMethod(tpl, "Reset", Reset);
    Nan::SetPrototypeMethod(tpl, "SELCTLTool", SELCTLTool);
    Nan::SetPrototypeMethod(tpl, "SaveAsModules", SaveAsModules);
    Nan::SetPrototypeMethod(tpl, "SaveAsP21", SaveAsP21);
    Nan::SetPrototypeMethod(tpl, "SetCNCexportExecDisabled", SetCNCexportExecDisabled);
    Nan::SetPrototypeMethod(tpl, "SetCNCexportExecEnabled", SetCNCexportExecEnabled);
    Nan::SetPrototypeMethod(tpl, "SetName", SetName);
    Nan::SetPrototypeMethod(tpl, "SetNameGet", SetNameGet);
    Nan::SetPrototypeMethod(tpl, "SetToolIdentifier", SetToolIdentifier);
    Nan::SetPrototypeMethod(tpl, "SetToolNumber", SetToolNumber);
    Nan::SetPrototypeMethod(tpl, "SpindleSpeed", SpindleSpeed);
    Nan::SetPrototypeMethod(tpl, "SpindleSpeedUnit", SpindleSpeedUnit);
    Nan::SetPrototypeMethod(tpl, "ToolGeometry", ToolGeometry);
    Nan::SetPrototypeMethod(tpl, "Workingstep", Workingstep);
    Nan::SetPrototypeMethod(tpl, "WorkingstepAfter", WorkingstepAfter);
    Nan::SetPrototypeMethod(tpl, "WorkingstepAddPropertyCountMeasure", WorkingstepAddPropertyCountMeasure);
    Nan::SetPrototypeMethod(tpl, "WorkingstepAddPropertyDescriptiveMeasure", WorkingstepAddPropertyDescriptiveMeasure);
    Nan::SetPrototypeMethod(tpl, "WorkingstepAddPropertyLengthMeasure", WorkingstepAddPropertyLengthMeasure);
    Nan::SetPrototypeMethod(tpl, "WorkingstepToolpathOrientation", WorkingstepToolpathOrientation);    
    Nan::SetPrototypeMethod(tpl, "Workpiece", Workpiece);
    Nan::SetPrototypeMethod(tpl, "WorkplanSetup", WorkplanSetup);
    Nan::SetPrototypeMethod(tpl, "WorkplanSetupDelete", WorkplanSetupDelete);

    constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("AptStepMaker").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());

}


NAN_METHOD(AptStepMaker::ArcXYPlane)
{
    Trace t(tc, "ArcXYPlane");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 9) return;
    if (!info[0]->IsString()) return;

    double dstx = Nan::To<double>(info[1]).FromJust(); 
    double dsty = Nan::To<double>(info[2]).FromJust();  
    double dstz = Nan::To<double>(info[3]).FromJust(); 
    double ctrx = Nan::To<double>(info[4]).FromJust();
    double ctry = Nan::To<double>(info[5]).FromJust();
    double ctrz = Nan::To<double>(info[6]).FromJust();
    double rad = Nan::To<double>(info[7]).FromJust();
    bool ccw = Nan::To<bool>(info[8]).FromJust();

    char * label = 0;
    v8StringToChar(info[0], label);
    int ok = apt->_apt->xy_arc(
	label, dstx,dsty,dstz, ctrx,ctry,ctrz, rad, ccw
	);
    delete [] label;

    if (!ok) {
	THROW_ERROR(t);
    }
}


NAN_METHOD(AptStepMaker::ArcYZPlane)
{
    Trace t(tc, "ArcYZPlane");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 9) return;
    if (!info[0]->IsString()) return;

    double dstx = Nan::To<double>(info[1]).FromJust(); 
    double dsty = Nan::To<double>(info[2]).FromJust();  
    double dstz = Nan::To<double>(info[3]).FromJust(); 
    double ctrx = Nan::To<double>(info[4]).FromJust();
    double ctry = Nan::To<double>(info[5]).FromJust();
    double ctrz = Nan::To<double>(info[6]).FromJust();
    double rad = Nan::To<double>(info[7]).FromJust();
    bool ccw = Nan::To<bool>(info[8]).FromJust();

    char * label = 0;
    v8StringToChar(info[0], label);
    int ok = apt->_apt->yz_arc(
	label, dstx,dsty,dstz, ctrx,ctry,ctrz, rad, ccw
	);
    delete [] label;

    if (!ok) {
	THROW_ERROR(t);
    }
}


NAN_METHOD(AptStepMaker::ArcZXPlane)
{
    Trace t(tc, "ArcZXPlane");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 9) return;
    if (!info[0]->IsString()) return;

    double dstx = Nan::To<double>(info[1]).FromJust(); 
    double dsty = Nan::To<double>(info[2]).FromJust();  
    double dstz = Nan::To<double>(info[3]).FromJust(); 
    double ctrx = Nan::To<double>(info[4]).FromJust();
    double ctry = Nan::To<double>(info[5]).FromJust();
    double ctrz = Nan::To<double>(info[6]).FromJust();
    double rad = Nan::To<double>(info[7]).FromJust();
    bool ccw = Nan::To<bool>(info[8]).FromJust();

    char * label = 0;
    v8StringToChar(info[0], label);
    int ok = apt->_apt->zx_arc(
	label, dstx,dsty,dstz, ctrx,ctry,ctrz, rad, ccw
	);
    delete [] label;

    if (!ok) {
	THROW_ERROR(t);
    }
}



NAN_METHOD(AptStepMaker::CamModeOn)
{
    Trace t(tc, "CamModeOn");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    int ok = apt->_apt->cam_mode_on();
    if (!ok) {
	THROW_ERROR(t);
    }
}


NAN_METHOD(AptStepMaker::CamModeOff)
{
    Trace t(tc, "CamModeOff");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    int ok = apt->_apt->cam_mode_off();
    if (!ok) {
	THROW_ERROR(t);
    }
}



NAN_METHOD(AptStepMaker::CoolantOn)
{
    Trace t(tc, "CoolantOn");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;
    
    int ok = apt->_apt->coolant_on();
    if (!ok) {
	THROW_ERROR(t);
    }
}

NAN_METHOD(AptStepMaker::CoolantOff)
{
    Trace t(tc, "CoolantOff");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;
    
    int ok = apt->_apt->coolant_off();
    if (!ok) {
	THROW_ERROR(t);
    }
}

NAN_METHOD(AptStepMaker::CoolantMist)
{
    Trace t(tc, "CoolantMist");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;
    
    int ok = apt->_apt->coolant_mist();
    if (!ok) {
	THROW_ERROR(t);
    }
}


NAN_METHOD(AptStepMaker::CoolantThru)
{
    Trace t(tc, "CoolantThru");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;
    
    int ok = apt->_apt->coolant_thru();
    if (!ok) {
	THROW_ERROR(t);
    }
}


NAN_METHOD(AptStepMaker::DefineTool)
{
    Trace t(tc, "DefineTool");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length()<7) return;
    double tool_diameter = Nan::To<double>(info[0]).FromJust();
    double tool_radius   = Nan::To<double>(info[1]).FromJust();
    double horizontal_distance  = Nan::To<double>(info[2]).FromJust();
    double vertical_distance  = Nan::To<double>(info[3]).FromJust();
    double unused  = Nan::To<double>(info[4]).FromJust();
    double angle   = Nan::To<double>(info[5]).FromJust();
    double height  = Nan::To<double>(info[6]).FromJust();
    
    int ok = apt->_apt->tool_apt(
	tool_diameter, tool_radius, 
	horizontal_distance, vertical_distance,
	unused, angle, height
	);
    
    if (!ok) {
	THROW_ERROR(t);
    }
}

// int ExecutableToSelective(int id)
NAN_METHOD(AptStepMaker::ExecutableToSelective)
{
    Trace t(tc, "ExecutableToSelective");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 1) return;
    if (!info[0]->IsInt32()) return;

    int id = Nan::To<int32_t>(info[0]).FromJust(); 
    int sel_id; 
    int ok = apt->_apt->selectivate_exe (id, sel_id);
    if (!ok) {
	THROW_ERROR(t);
    }
    info.GetReturnValue().Set(sel_id);
}


// void ExecutableWorkpieceAsIs(int id, string filename)
NAN_METHOD(AptStepMaker::ExecutableWorkpieceAsIs)
{
    Trace t(tc, "ExecutableWorkpieceAsIs");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 2) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsString()) return;

    int id = Nan::To<int32_t>(info[0]).FromJust(); 
    char * filenm = 0;
    v8StringToChar(info[1], filenm);
    int ok = apt->_apt->as_is_geometry (id, filenm);
    delete [] filenm;

    if (!ok) {
	THROW_ERROR(t);
    }
}

// void ExecutableWorkpieceRemoval(int id, string filename)
NAN_METHOD(AptStepMaker::ExecutableWorkpieceRemoval)
{
    Trace t(tc, "ExecutableWorkpieceRemoval");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 2) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsString()) return;

    int id = Nan::To<int32_t>(info[0]).FromJust(); 
    char * filenm = 0;
    v8StringToChar(info[1], filenm);
    int ok = apt->_apt->removal_geometry (id, filenm);
    delete [] filenm;

    if (!ok) {
	THROW_ERROR(t);
    }
}


// ExecutableWorkpieceReuse*(int id, int other_id)
NAN_METHOD(AptStepMaker::ExecutableWorkpieceReuseAsIs)
{
    Trace t(tc, "ExecutableWorkpieceReuseAsIs");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 2) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsInt32()) return;

    int id = Nan::To<int32_t>(info[0]).FromJust(); 
    int other_id = Nan::To<int32_t>(info[0]).FromJust(); 
    int ok = apt->_apt->as_is_geometry (id, other_id);

    if (!ok) {
	THROW_ERROR(t);
    }
}


NAN_METHOD(AptStepMaker::ExecutableWorkpieceReuseRemoval)
{
    Trace t(tc, "ExecutableWorkpieceReuseAsIs");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 2) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsInt32()) return;

    int id = Nan::To<int32_t>(info[0]).FromJust(); 
    int other_id = Nan::To<int32_t>(info[0]).FromJust(); 
    int ok = apt->_apt->removal_geometry (id, other_id);

    if (!ok) {
	THROW_ERROR(t);
    }
}

NAN_METHOD(AptStepMaker::ExecutableWorkpieceReuseToBe)
{
    Trace t(tc, "ExecutableWorkpieceReuseAsIs");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 2) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsInt32()) return;

    int id = Nan::To<int32_t>(info[0]).FromJust(); 
    int other_id = Nan::To<int32_t>(info[0]).FromJust(); 
    int ok = apt->_apt->to_be_geometry (id, other_id);

    if (!ok) {
	THROW_ERROR(t);
    }
}

// void ExecutableWorkpieceToBe(int id, string filename)
NAN_METHOD(AptStepMaker::ExecutableWorkpieceToBe)
{
    Trace t(tc, "ExecutableWorkpieceToBe");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 2) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsString()) return;

    int id = Nan::To<int32_t>(info[0]).FromJust(); 
    char * filenm = 0;
    v8StringToChar(info[1], filenm);
    int ok = apt->_apt->to_be_geometry (id, filenm);
    delete [] filenm;

    if (!ok) {
	THROW_ERROR(t);
    }
}


// void Feedrate (double feed)
NAN_METHOD(AptStepMaker::Feedrate)
{
    Trace t(tc, "Feedrate");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 1) return;
    if (!info[0]->IsNumber()) return;

    double f = Nan::To<double>(info[0]).FromJust();
    int ok = apt->_apt->set_feedrate(f);
    if (!ok) {
	THROW_ERROR(t);
    }
}
    

NAN_METHOD(AptStepMaker::FeedrateUnit)
{
    Trace t(tc, "FeedrateUnit");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 1) return;
    if (!info[0]->IsString()) return;

    char * nm = 0;
    v8StringToChar(info[0], nm);
    int ok = apt->_apt->set_feedrate_units(nm);
    delete [] nm;

    if (!ok) {
	THROW_ERROR(t);
    }
}



// void Fixture (string filename)
// void Fixture (string filename, int wplan_id)
NAN_METHOD(AptStepMaker::Fixture)
{
    Trace t(tc, "Fixture");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;
    
    if (info.Length() != 1 && info.Length() != 2) return;
    if (!info[0]->IsString()) return;
    if (info.Length() == 1) {
	char * fname = 0;
	v8StringToChar(info[0], fname);
	int ok = apt->_apt->fixture(fname);
	delete [] fname;

	if (!ok) {
	    THROW_ERROR(t);
	}
    }
    else {
	if (!info[1]->IsInt32()) return;

	char * fname = 0;
	v8StringToChar(info[0], fname);
	int planid = Nan::To<int32_t>(info[1]).FromJust(); 
	int ok = apt->_apt->setup_fixture_geometry(planid, fname);
	delete [] fname;

	if (!ok) {
	    THROW_ERROR(t);
	}
    }
}



NAN_METHOD(AptStepMaker::GenerateToolGeometry)
{
    Trace t(tc, "GenerateToolGeometry");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 1) return;
    if (!info[0]->IsInt32()) return;

    int id = Nan::To<int32_t>(info[0]).FromJust(); 
    int ok = apt->_apt->generate_tool_geometry(id);
    if (!ok) {
	THROW_ERROR(t);
    }
}

// void GeometryForTool (int id, string filename)
NAN_METHOD(AptStepMaker::GeometryForTool)
{
    Trace t(tc, "GeometryForTool");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 2) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsString()) return;

    int id = Nan::To<int32_t>(info[0]).FromJust(); 
    char * filenm = 0;
    v8StringToChar(info[1], filenm);
    int ok = apt->_apt->tool_geometry (filenm, id);
    delete [] filenm;

    if (!ok) {
	THROW_ERROR(t);
    }
}


// void GeometryForToolNumber (string filename, int number)
NAN_METHOD(AptStepMaker::GeometryForToolNumber)
{
    Trace t(tc, "GeometryForToolNumber");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 2) return;
    if (!info[0]->IsString()) return;
    if (!info[1]->IsInt32()) return;

    int num = Nan::To<int32_t>(info[1]).FromJust(); 
    char * filenm = 0;
    v8StringToChar(info[0], filenm);
    int ok = apt->_apt->geometry_for_tool_number (filenm, num);
    delete [] filenm;

    if (!ok) {
	THROW_ERROR(t);
    }
}

NAN_METHOD(AptStepMaker::GetCurrentFunction)
{
    Trace t(tc, "GetCurrentFunction");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;
    int id_ws, id_wp, id_tp, id_tech, id_fun;

    int ok = apt->_apt->current_ids(id_ws, id_wp, id_tp, id_tech, id_fun);
    if (!ok) {
	THROW_ERROR(t);
    }
    info.GetReturnValue().Set(id_fun);
}

NAN_METHOD(AptStepMaker::GetCurrentFixture)
{
    Trace t(tc, "GetCurrentFixture");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;
	
    int id_pj, id_wp, id_rp, id_fx, id_tl;
    int ok = apt->_apt->more_current_ids(id_pj, id_wp, id_rp, id_fx, id_tl);
    if (!ok) {
	THROW_ERROR(t);
    }
    info.GetReturnValue().Set(id_fx);
}


NAN_METHOD(AptStepMaker::GetCurrentRawpiece)
{
    Trace t(tc, "GetCurrentRawpiece");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;
	
    int id_pj, id_wp, id_rp, id_fx, id_tl;
    int ok = apt->_apt->more_current_ids(id_pj, id_wp, id_rp, id_fx, id_tl);
    if (!ok) {
	THROW_ERROR(t);
    }
    info.GetReturnValue().Set(id_rp);
}


NAN_METHOD(AptStepMaker::GetCurrentTech)
{
    Trace t(tc, "GetCurrentTech");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;
    int id_ws, id_wp, id_tp, id_tech, id_fun;

    int ok = apt->_apt->current_ids(id_ws, id_wp, id_tp, id_tech, id_fun);
    if (!ok) {
	THROW_ERROR(t);
    }
    info.GetReturnValue().Set(id_tech);
}


NAN_METHOD(AptStepMaker::GetCurrentTool)
{
    Trace t(tc, "GetCurrentTool");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;
	
    int id_pj, id_wp, id_rp, id_fx, id_tl;
    int ok = apt->_apt->more_current_ids(id_pj, id_wp, id_rp, id_fx, id_tl);
    if (!ok) {
	THROW_ERROR(t);
    }
    info.GetReturnValue().Set(id_tl);
}
    

NAN_METHOD(AptStepMaker::GetCurrentToolpath)
{
    Trace t(tc, "GetCurrentToolpath");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;
    int id_ws, id_wp, id_tp, id_tech, id_fun;

    int ok = apt->_apt->current_ids(id_ws, id_wp, id_tp, id_tech, id_fun);
    if (!ok) {
	THROW_ERROR(t);
    }
    info.GetReturnValue().Set(id_tp);
}


NAN_METHOD(AptStepMaker::GetCurrentWorkingstep)
{
    Trace t(tc, "GetCurrentWorkingstep");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;
    int id_ws, id_wp, id_tp, id_tech, id_fun;

    int ok = apt->_apt->current_ids(id_ws, id_wp, id_tp, id_tech, id_fun);
    if (!ok) {
	THROW_ERROR(t);
    }
    info.GetReturnValue().Set(id_ws);
}


NAN_METHOD(AptStepMaker::GetCurrentWorkpiece)
{
    Trace t(tc, "GetCurrentWorkpiece");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;
	
    int id_pj, id_wp, id_rp, id_fx, id_tl;
    int ok = apt->_apt->more_current_ids(id_pj, id_wp, id_rp, id_fx, id_tl);
    if (!ok) {
	THROW_ERROR(t);
    }
    info.GetReturnValue().Set(id_wp);
}

NAN_METHOD(AptStepMaker::GetCurrentWorkplan)
{
    Trace t(tc, "GetCurrentWorkplan");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;
    int id_ws, id_wp, id_tp, id_tech, id_fun;

    int ok = apt->_apt->current_ids(id_ws, id_wp, id_tp, id_tech, id_fun);
    if (!ok) {
	THROW_ERROR(t);
    }
    info.GetReturnValue().Set(id_wp);
}

NAN_METHOD(AptStepMaker::GetToolEID)
{
    Trace t(tc, "GetToolIdentifier");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 1) return;
    if (!info[0]->IsString()) return;

    int toolEID;
    char * toolNum = 0;
    v8StringToChar(info[0], toolNum);
    int ok = apt->_apt->get_tool_id(toolNum, toolEID);
    delete [] toolNum;

    if (!ok) {
	THROW_ERROR(t);
    }
    info.GetReturnValue().Set(toolEID);

}

NAN_METHOD(AptStepMaker::GetToolIdentifier)
{
    Trace t(tc, "GetToolIdentifier");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 1) return;
    if (!info[0]->IsString()) return;

    char * toolNum = 0;
    const char * toolID = 0;
    v8StringToChar(info[0], toolNum);
    int ok = apt->_apt->get_tool_identifier(toolNum, toolID);
    delete [] toolNum;

    if (!ok) {
	THROW_ERROR(t);
    }
    info.GetReturnValue().Set(CharTov8String(toolID));
}

NAN_METHOD(AptStepMaker::GetToolNumber)
{
    Trace t(tc, "GetToolNumber");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 1) return;
    if (!info[0]->IsInt32()) return;

    Nan::Maybe<int32_t> id = Nan::To<int32_t>(info[0]);
    const char * tlNum = 0;
    int ok = apt->_apt->get_tool_number(id.FromJust(), tlNum);
    if (!ok) {
	THROW_ERROR(t);
    }
    info.GetReturnValue().Set(CharTov8String(tlNum));
}

NAN_METHOD(AptStepMaker::GetUUID)
{
    Trace t(tc, "GetUUID");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 1) return;
    if (!info[0]->IsInt32()) return;

    Nan::Maybe<int32_t> eid = Nan::To<int32_t>(info[0]);
    const char * uuid;
    int ok = apt->_apt->get_uuid(eid.FromJust(), uuid);
    if (!ok) {
	THROW_ERROR(t);
    }
    info.GetReturnValue().Set(CharTov8String(uuid));
}

NAN_METHOD(AptStepMaker::GetIDFromUUID)
{
    Trace t(tc, "GetIDFromUUID");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 1)return;
    if (!info[0]->IsString()) return;

    int EID;
    char * UUID = 0;
    v8StringToChar(info[0], UUID);
    int ok = apt->_apt->get_id_from_uuid(UUID,EID);
    delete [] UUID;

    if (!ok) {
	THROW_ERROR(t);
    }
    info.GetReturnValue().Set(EID);
}

NAN_METHOD(AptStepMaker::GetWorkpieceExecutableAll)
{
    AptStepMaker * apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (apt == 0) //Throw Exception
	return;
    if (info.Length() != 1) //Function should get one argument.
	return;
    if (!info[0]->IsInt32())
	return;

    Nan::Maybe<int32_t> wpid = Nan::To<int32_t>(info[0]);
    int count = 0;
    if (!apt->_apt->workpiece_executable_count(wpid.FromJust(), count)) //Throw Exception
	return;
    
    v8::Local<v8::Array> array = Nan::New<v8::Array>();
    for (int i = 0; i < count; i++) {
        int exe_id = 0;
        if (!apt->_apt->workpiece_executable_next(wpid.FromJust(), i, exe_id)) //Throw Exception
            return;
        else
            array->Set(i, Nan::New(exe_id));
    }

    info.GetReturnValue().Set(array);
    return;
}

NAN_METHOD(AptStepMaker::GetWorkpiecePlacement) {
    AptStepMaker * apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (apt == 0) //Throw Exception
	return;
    if (info.Length() != 1) //Function should get one argument.
	return;
    if (!info[0]->IsInt32())
	return;
	
    Nan::Maybe<int32_t> wpid = Nan::To<int32_t>(info[0]);
    double x;
    double y;
    double z;
    double i;
    double j;
    double k;
    double a;
    double b;
    double c;
	
    if (!apt->_apt->get_workpiece_placement(wpid.FromJust(), x, y, z, i, j, k, a, b, c)) //TODO: Handle error
	return;
		
    v8::Local<v8::Array> array = Nan::New<v8::Array>();
    array->Set(0, Nan::New(x));
    array->Set(1, Nan::New(y));
    array->Set(2, Nan::New(z));
    array->Set(3, Nan::New(i));
    array->Set(4, Nan::New(j));
    array->Set(5, Nan::New(k));
    array->Set(6, Nan::New(a));
    array->Set(7, Nan::New(b));
    array->Set(8, Nan::New(c));
	
    info.GetReturnValue().Set(array);
    return;
}

NAN_METHOD(AptStepMaker::GetExecutableWorkpieceAsIs)
{
    Trace t(tc, "GetExecutableWorkpieceAsIs");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 1) return;
    if (!info[0]->IsInt32()) return;
	
    int wsid = Nan::To<int32_t>(info[0]).FromJust(); 
    int wpid;
	
    int ok = apt->_apt->executable_as_is_workpiece(wsid, wpid);
    if (!ok) {
	THROW_ERROR(t);
    }

    info.GetReturnValue().Set(wpid);
}

NAN_METHOD(AptStepMaker::GetExecutableWorkpieceFixture)
{
    Trace t(tc, "GetExecutableWorkpieceFixture");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 1) return;
    if (!info[0]->IsInt32()) return;
	
    int wsid = Nan::To<int32_t>(info[0]).FromJust(); 
    int wpid;
	
    int ok = apt->_apt->executable_fixture_workpiece(wsid, wpid);
    if (!ok) {
	THROW_ERROR(t);
    }

    info.GetReturnValue().Set(wpid);
}

NAN_METHOD(AptStepMaker::GetExecutableWorkpieceRemoval)
{
    Trace t(tc, "GetExecutableWorkpieceRemoval");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 1) return;
    if (!info[0]->IsInt32()) return;
	
    int wsid = Nan::To<int32_t>(info[0]).FromJust(); 
    int wpid;
	
    int ok = apt->_apt->executable_removal_workpiece(wsid, wpid);
    if (!ok) {
	THROW_ERROR(t);
    }

    info.GetReturnValue().Set(wpid);
}

NAN_METHOD(AptStepMaker::GetExecutableWorkpieceToBe)
{
    Trace t(tc, "GetExecutableWorkpieceToBe");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 1) return;
    if (!info[0]->IsInt32()) return;
	
    int wsid = Nan::To<int32_t>(info[0]).FromJust(); 
    int wpid;
	
    int ok = apt->_apt->executable_to_be_workpiece(wsid, wpid);
    if (!ok) {
	THROW_ERROR(t);
    }

    info.GetReturnValue().Set(wpid);
}


NAN_METHOD(AptStepMaker::GetWorkplanSetup)
{
    Trace t(tc, "GetWorkplanSetup");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 1) return;
    if (!info[0]->IsInt32()) return;
	
    int wpid = Nan::To<int32_t>(info[0]).FromJust(); 
    double x,y,z,i,j,k,a,b,c;
	
    int ok = apt->_apt->workplan_setup_get(wpid, x,y,z, i,j,k, a,b,c);
    if (!ok) {
	THROW_ERROR(t);
    }

    v8::Local<v8::Array> array = Nan::New<v8::Array>();
    array->Set(0, Nan::New(x));
    array->Set(1, Nan::New(y));
    array->Set(2, Nan::New(z));
    array->Set(3, Nan::New(i));
    array->Set(4, Nan::New(j));
    array->Set(5, Nan::New(k));
    array->Set(6, Nan::New(a));
    array->Set(7, Nan::New(b));
    array->Set(8, Nan::New(c));
	
    info.GetReturnValue().Set(array);
}


NAN_METHOD(AptStepMaker::GoToXYZ)
{
    Trace t(tc, "GoToXYZ");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 4) return;
    if (!info[0]->IsString()) return;

    double x = Nan::To<double>(info[1]).FromJust(); 
    double y = Nan::To<double>(info[2]).FromJust();  
    double z = Nan::To<double>(info[3]).FromJust(); 

    char * label = 0;
    v8StringToChar(info[0], label);
    int ok = apt->_apt->goto_xyz(label, x, y, z);
    delete [] label;

    if (!ok) {
	THROW_ERROR(t);
    }
}


NAN_METHOD(AptStepMaker::GoToXYZ_IJK)
{
    Trace t(tc, "GoToXYZ_IJK");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 7) return;
    if (!info[0]->IsString()) return;

    double x = Nan::To<double>(info[1]).FromJust(); 
    double y = Nan::To<double>(info[2]).FromJust();  
    double z = Nan::To<double>(info[3]).FromJust(); 
    double i = Nan::To<double>(info[4]).FromJust();
    double j = Nan::To<double>(info[5]).FromJust();
    double k = Nan::To<double>(info[6]).FromJust();

    char * label = 0;
    v8StringToChar(info[0], label);
    int ok = apt->_apt->goto_xyz_ijk(label, x,y,z, i,j,k);
    delete [] label;

    if (!ok) {
	THROW_ERROR(t);
    }
}

NAN_METHOD(AptStepMaker::GoToXYZ_ABC)
{
    Trace t(tc, "GoToXYZ_ABC");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 7) return;
    if (!info[0]->IsString()) return;

    double x = Nan::To<double>(info[1]).FromJust(); 
    double y = Nan::To<double>(info[2]).FromJust();  
    double z = Nan::To<double>(info[3]).FromJust(); 
    double a = Nan::To<double>(info[4]).FromJust();
    double b = Nan::To<double>(info[5]).FromJust();
    double c = Nan::To<double>(info[6]).FromJust();

    char * label = 0;
    v8StringToChar(info[0], label);
    int ok = apt->_apt->goto_xyz_abc(label, x,y,z, a,b,c);
    delete [] label;

    if (!ok) {
	THROW_ERROR(t);
    }
}

NAN_METHOD(AptStepMaker::GoToXYZ_IJK_ABC)
{
    Trace t(tc, "GoToXYZ_IJK_ABC");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 10) return;
    if (!info[0]->IsString()) return;

    double x = Nan::To<double>(info[1]).FromJust(); 
    double y = Nan::To<double>(info[2]).FromJust();  
    double z = Nan::To<double>(info[3]).FromJust(); 
    double i = Nan::To<double>(info[4]).FromJust();
    double j = Nan::To<double>(info[5]).FromJust();
    double k = Nan::To<double>(info[6]).FromJust();
    double a = Nan::To<double>(info[7]).FromJust();
    double b = Nan::To<double>(info[8]).FromJust();
    double c = Nan::To<double>(info[9]).FromJust();

    char * label = 0;
    v8StringToChar(info[0], label);
    int ok = apt->_apt->goto_xyz_ijk_abc(label, x,y,z, i,j,k, a,b,c);
    delete [] label;

    if (!ok) {
	THROW_ERROR(t);
    }
}


NAN_METHOD(AptStepMaker::GoToXYZ_IJK_REF_ABC)
{
    Trace t(tc, "GoToXYZ_IJK_REF_ABC");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 10) return;
    if (!info[0]->IsString()) return;

    double x = Nan::To<double>(info[1]).FromJust(); 
    double y = Nan::To<double>(info[2]).FromJust();  
    double z = Nan::To<double>(info[3]).FromJust(); 
    double i = Nan::To<double>(info[4]).FromJust();
    double j = Nan::To<double>(info[5]).FromJust();
    double k = Nan::To<double>(info[6]).FromJust();
    double a = Nan::To<double>(info[7]).FromJust();
    double b = Nan::To<double>(info[8]).FromJust();
    double c = Nan::To<double>(info[9]).FromJust();

    char * label = 0;
    v8StringToChar(info[0], label);
    int ok = apt->_apt->goto_xyz_ijk_ref_abc(label, x,y,z, i,j,k, a,b,c);
    delete [] label;

    if (!ok) {
	THROW_ERROR(t);
    }
}


NAN_METHOD(AptStepMaker::Inches)
{
    Trace t(tc, "Inches");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    int ok = apt->_apt->inches();
    if (!ok) {
	THROW_ERROR(t);
    }
}


// bool IsToolDefined(int num)
NAN_METHOD(AptStepMaker::IsToolDefined)
{
    Trace t(tc, "IsToolDefined");
    AptStepMaker * apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 1) return;
    if (!info[0]->IsInt32()) return;

    int num = Nan::To<int32_t>(info[0]).FromJust();
    info.GetReturnValue().Set((apt->_apt->is_tool_defined(num) != 0));
}



// void LoadTool(int num);
NAN_METHOD(AptStepMaker::LoadTool)
{
    Trace t(tc, "LoadTool");
    AptStepMaker * apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 1) return;
    if (!info[0]->IsInt32()) return;

    int num = Nan::To<int32_t>(info[0]).FromJust();
    int ok = apt-> _apt->load_tool(num);
    if (!ok) {
	THROW_ERROR(t);
    }
}

NAN_METHOD(AptStepMaker::MakeRawBox)
{
    Trace t(tc, "MakeRawBox");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 7) return;
    if (!info[0]->IsInt32()) return;

    int wpid = Nan::To<int32_t>(info[0]).FromJust(); 
    double x_min = Nan::To<double>(info[1]).FromJust(); 
    double y_min = Nan::To<double>(info[2]).FromJust();  
    double z_min = Nan::To<double>(info[3]).FromJust(); 
    double x_max = Nan::To<double>(info[4]).FromJust(); 
    double y_max = Nan::To<double>(info[5]).FromJust(); 
    double z_max = Nan::To<double>(info[6]).FromJust();

    int ok = apt->_apt->make_raw_box(wpid, x_min, y_min, z_min, x_max, y_max, z_max);
    if (!ok) {
	THROW_ERROR(t);
    }
}


NAN_METHOD(AptStepMaker::Millimeters)
{
    Trace t(tc, "Millimeters");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    int ok = apt->_apt->millimeters();
    if (!ok) {
	THROW_ERROR(t);
    }
}



NAN_METHOD(AptStepMaker::NewProject)
{
    Trace t(tc, "NewProject");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;
    
    if (info.Length() != 1) return;
    if (!info[0]->IsString()) return;

    char * fname = 0;
    v8StringToChar(info[0], fname);
    int ok = apt->_apt->new_project(fname);
    delete [] fname;

    if (!ok) {
	THROW_ERROR(t);
    }
}

NAN_METHOD(AptStepMaker::OpenProject)
{
    Trace t(tc, "OpenProject");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;
    
    if (info.Length() != 1) return;
    if (!info[0]->IsString()) return;

    char * fname = 0;
    v8StringToChar(info[0], fname);
    int ok = apt->_apt->read_238_file(fname);
    delete [] fname;

    if (!ok) {
	THROW_ERROR(t);
    }
}

NAN_METHOD(AptStepMaker::OpenSTEP)
{
    Trace t(tc, "OpenSTEP");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;
    
    if (info.Length() != 1) return;
    if (!info[0]->IsString()) return;

    char * fname = 0;
    v8StringToChar(info[0], fname);
    int ok = apt->_apt->read_203_file(fname);
    delete [] fname;

    if (!ok) {
	THROW_ERROR(t);
    }
}



NAN_METHOD(AptStepMaker::PartNo)
{
    Trace t(tc, "PartNo");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (apt == 0) return;  //Throw Exception
    
    if (info.Length() != 1) //Function should get one argument.
	return;
    if (!info[0]->IsString())
	return;

    char * pname = 0;
    v8StringToChar(info[0], pname);
    int ok = apt->_apt->partno(pname);
    delete [] pname;

    if (!ok) {
	THROW_ERROR(t);
    }
}

NAN_METHOD(AptStepMaker::PutWorkpiecePlacement)
{
    Trace t(tc, "PutWorkpiecePlacement");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 10) return;
    if (!info[0]->IsInt32()) return;
    for (int tmp=1; tmp<10; tmp++) {
        if (info[tmp]->IsUndefined()) return;
	if (!info[tmp]->IsNumber()) return;
    }
	
    int wpid = Nan::To<int32_t>(info[0]).FromJust(); 
    double x = Nan::To<double>(info[1]).FromJust();
    double y = Nan::To<double>(info[2]).FromJust();
    double z = Nan::To<double>(info[3]).FromJust();
    double i = Nan::To<double>(info[4]).FromJust();
    double j = Nan::To<double>(info[5]).FromJust();
    double k = Nan::To<double>(info[6]).FromJust();
    double a = Nan::To<double>(info[7]).FromJust();
    double b = Nan::To<double>(info[8]).FromJust();
    double c = Nan::To<double>(info[9]).FromJust();

    int ok = apt->_apt->put_workpiece_placement(wpid, x,y,z, i,j,k, a,b,c);
    if (!ok) {
	THROW_ERROR(t);
    }
}

NAN_METHOD(AptStepMaker::PutWorkplanSetup)
{
    Trace t(tc, "PutWorkplanSetup");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 10) return;
    if (!info[0]->IsInt32()) return;
    for (int tmp=1; tmp<10; tmp++) {
        if (info[tmp]->IsUndefined()) return;
	if (!info[tmp]->IsNumber()) return;
    }
	
    int wpid = Nan::To<int32_t>(info[0]).FromJust(); 
    double x = Nan::To<double>(info[1]).FromJust();
    double y = Nan::To<double>(info[2]).FromJust();
    double z = Nan::To<double>(info[3]).FromJust();
    double i = Nan::To<double>(info[4]).FromJust();
    double j = Nan::To<double>(info[5]).FromJust();
    double k = Nan::To<double>(info[6]).FromJust();
    double a = Nan::To<double>(info[7]).FromJust();
    double b = Nan::To<double>(info[8]).FromJust();
    double c = Nan::To<double>(info[9]).FromJust();

    int ok = apt->_apt->workplan_setup_put(wpid, x,y,z, i,j,k, a,b,c);
    if (!ok) {
	THROW_ERROR(t);
    }
}


NAN_METHOD(AptStepMaker::Rapid)
{
    Trace t(tc, "Rapid");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;
    
    int ok = apt->_apt->rapid();
    if (!ok) {
	THROW_ERROR(t);
    }
}


NAN_METHOD(AptStepMaker::Rawpiece)
{
    Trace t(tc, "Rawpiece");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;
    
    if (info.Length() != 1) return;
    if (!info[0]->IsString()) return;

    char * fname = 0;
    v8StringToChar(info[0], fname);
    int ok = apt->_apt->rawpiece(fname);
    delete [] fname;

    if (!ok) {
	THROW_ERROR(t);
    }
}

NAN_METHOD(AptStepMaker::Reset)
{
    Trace t(tc, "Reset");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    int ok = apt->_apt->reset();
    if (!ok) {
	THROW_ERROR(t);
    }
}





NAN_METHOD(AptStepMaker::SaveAsModules)
{
    Trace t(tc, "SaveAsModules");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;
    
    if (info.Length() != 1) return;
    if (!info[0]->IsString()) return;

    char * fname = 0;
    v8StringToChar(info[0], fname);
    int ok = apt->_apt->save_file(fname, true);
    delete [] fname;

    if (!ok) {
	THROW_ERROR(t);
    }
}


NAN_METHOD(AptStepMaker::SaveAsP21)
{
    Trace t(tc, "SaveAsP21");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;
    
    if (info.Length() != 1) return;
    if (!info[0]->IsString()) return;

    char * fname = 0;
    v8StringToChar(info[0], fname);
    int ok = apt->_apt->save_file(fname, false);
    delete [] fname;

    if (!ok) {
	THROW_ERROR(t);
    }
}

// void SELCTLTool(int num);
NAN_METHOD(AptStepMaker::SELCTLTool)
{
    Trace t(tc, "SELCTLTool");
    AptStepMaker * apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 1) return;
    if (!info[0]->IsInt32()) return;

    int num = Nan::To<int32_t>(info[0]).FromJust();
    int ok = apt-> _apt->selctl_tool(num);
    if (!ok) {
	THROW_ERROR(t);
    }
}


// void SetCNCexportExecEnabled(int wsid);
NAN_METHOD(AptStepMaker::SetCNCexportExecEnabled)
{
    AptStepMaker * apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return; //Throw Exception
    if (info.Length() == 0) return;
    
    int ws = Nan::To<int32_t>(info[0]).FromJust();
    if (!apt-> _apt->set_exec_enabled(ws))
	return;  // error
}

// void SetCNCexportExecDisabled(int wsid);
NAN_METHOD(AptStepMaker::SetCNCexportExecDisabled)
{
    AptStepMaker * apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return; //Throw Exception
    if (info.Length() == 0) return;
    
    int ws = Nan::To<int32_t>(info[0]).FromJust();
    if (!apt-> _apt->set_exec_disabled(ws))
	return;  // error
}


NAN_METHOD(AptStepMaker::SetName)
{
    Trace t(tc, "SetName");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length()!=2) return;
    if (!info[1]->IsString()) return;

    int ws = Nan::To<int32_t>(info[0]).FromJust();
    char * nm = 0;
    v8StringToChar(info[1], nm);
    
    int ok = apt->_apt->set_name (ws, nm);
    delete [] nm;
    if (!ok) {
	THROW_ERROR(t);
    }
}


NAN_METHOD(AptStepMaker::SetNameGet)
{
    AptStepMaker * apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (apt == 0) //Throw Exception
	return;
    if (info.Length() != 1) //Function should get one argument.
	return;
    if (!info[0]->IsInt32())
	return;
    Nan::Maybe<int32_t> eid = Nan::To<int32_t>(info[0]);
    const char * szName;
    if (!apt->_apt->get_name(eid.FromJust(), szName)) //TODO: Handle error
	return;
    info.GetReturnValue().Set(CharTov8String((char *)szName));

}


NAN_METHOD(AptStepMaker::SetToolIdentifier)
{
    Trace t(tc, "SetToolIdentifier");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 2) return;
    if (!info[0]->IsString()) return;
    if (!info[1]->IsString()) return;

    char * tool_number = 0;
    char * identifier = 0;
    v8StringToChar(info[0], tool_number);
    v8StringToChar(info[1], identifier);
    int ok = apt->_apt->set_tool_identifier(tool_number, identifier);
    delete[] tool_number;
    delete[] identifier;
    if (!ok) {
	THROW_ERROR(t);
    }
}


NAN_METHOD(AptStepMaker::SetToolNumber)
{
    Trace t(tc, "SetToolNumber");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 2) return;
    if (!info[0]->IsString()) return;
    if (!info[1]->IsString()) return;

    char * old_num = 0;
    char * new_num = 0;
    v8StringToChar(info[0], old_num);
    v8StringToChar(info[1], new_num);
    int ok = apt->_apt->set_tool_number(old_num, new_num);
    delete[] old_num;
    delete[] new_num;
    if (!ok) {
	THROW_ERROR(t);
    }
}



// void SpindleSpeed (double feed)
NAN_METHOD(AptStepMaker::SpindleSpeed)
{
    Trace t(tc, "SpindleSpeed");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 1) return;
    if (!info[0]->IsNumber()) return;

    double f = Nan::To<double>(info[0]).FromJust();
    int ok = apt->_apt->set_spindle_speed(f);
    if (!ok) {
	THROW_ERROR(t);
    }
}
    

NAN_METHOD(AptStepMaker::SpindleSpeedUnit)
{
    Trace t(tc, "SpindleSpeedUnit");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 1) return;
    if (!info[0]->IsString()) return;

    char * nm = 0;
    v8StringToChar(info[0], nm);
    int ok = apt->_apt->set_spindle_speed_units(nm);
    delete [] nm;

    if (!ok) {
	THROW_ERROR(t);
    }
}


// void ToolGeometry(string file_name, string tool_ident);    
NAN_METHOD(AptStepMaker::ToolGeometry)
{
    Trace t(tc, "ToolGeometry");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 2) return;
    if (!info[0]->IsString()) return;
    if (!info[1]->IsString()) return;

    char * filenm = 0;
    char * toolid = 0;
    v8StringToChar(info[0], filenm);
    v8StringToChar(info[1], toolid);
    int ok = apt->_apt->tool_geometry (filenm, toolid, NULL);
    delete [] filenm;
    delete [] toolid;

    if (!ok) {
	THROW_ERROR(t);
    }
}


// void Workingstep (string label)
NAN_METHOD(AptStepMaker::Workingstep)
{
    Trace t(tc, "Workingstep");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 1) return;
    if (!info[0]->IsString()) return;

    char * label = 0;
    v8StringToChar(info[0], label);
    int ok = apt->_apt->workingstep (label);
    delete [] label;

    if (!ok) {
	THROW_ERROR(t);
    }
}


// int WorkingstepAfter (string label, int idx, int wp_id)
NAN_METHOD(AptStepMaker::WorkingstepAfter)
{
    Trace t(tc, "WorkingstepAfter");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 3) return;
    if (!info[0]->IsString()) return;
    if (!info[1]->IsInt32()) return; 
    if (!info[2]->IsInt32()) return;

    int wpid = Nan::To<int32_t>(info[2]).FromJust(); 
    int idx =  Nan::To<int32_t>(info[1]).FromJust();
    int new_ws_id;

    char * label = 0;
    v8StringToChar(info[0], label);
    int ok = apt->_apt->workingstep_after(label, idx, wpid, new_ws_id);
    delete [] label;

    if (!ok) {
	THROW_ERROR(t);
    }
    info.GetReturnValue().Set(new_ws_id);
}



NAN_METHOD(AptStepMaker::WorkingstepAddPropertyCountMeasure)
{
    Trace t(tc, "WorkingstepAddPropertyCountMeasure");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 3) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsString()) return;
    if (!info[2]->IsInt32()) return;

    int wsid = Nan::To<int32_t>(info[0]).FromJust(); 
    int val =  Nan::To<int32_t>(info[2]).FromJust();

    char * nm = 0;
    v8StringToChar(info[1], nm);
    int ok = apt->_apt->workingstep_count_measure_property (wsid, nm, val);
    delete [] nm;

    if (!ok) {
	THROW_ERROR(t);
    }
}


NAN_METHOD(AptStepMaker::WorkingstepAddPropertyDescriptiveMeasure)
{
    Trace t(tc, "WorkingstepAddPropertyDescriptiveMeasure");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 3) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsString()) return;
    if (!info[2]->IsString()) return;

    int wsid = Nan::To<int32_t>(info[0]).FromJust(); 

    char * nm = 0;
    char * val = 0;
    v8StringToChar(info[1], nm);
    v8StringToChar(info[2], val);
    int ok = apt->_apt->workingstep_descriptive_measure_property (wsid, nm, val);
    delete [] nm;
    delete [] val;

    if (!ok) {
	THROW_ERROR(t);
    }
}


NAN_METHOD(AptStepMaker::WorkingstepAddPropertyLengthMeasure)
{
    Trace t(tc, "WorkingstepAddPropertyLengthMeasure");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 3) return;
    if (!info[0]->IsInt32()) return;
    if (!info[1]->IsString()) return;
    if (!info[2]->IsNumber()) return;

    int wsid = Nan::To<int32_t>(info[0]).FromJust(); 
    double val = Nan::To<double>(info[2]).FromJust();

    char * nm = 0;
    v8StringToChar(info[1], nm);
    int ok = apt->_apt->workingstep_length_measure_property (wsid, nm, val);
    delete [] nm;

    if (!ok) {
	THROW_ERROR(t);
    }
}

// void WorkingstepToolpathOrientation(x,y,z, i,j,k, a,b,c);
NAN_METHOD(AptStepMaker::WorkingstepToolpathOrientation)
{
    Trace t(tc, "WorkingstepToolpathOrientation");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 9) return;
    for (int tmp=0; tmp<9; tmp++) {
        if (info[tmp]->IsUndefined()) return;
	if (!info[tmp]->IsNumber()) return;
    }
	
    double x = Nan::To<double>(info[0]).FromJust();
    double y = Nan::To<double>(info[1]).FromJust();
    double z = Nan::To<double>(info[2]).FromJust();
    double i = Nan::To<double>(info[3]).FromJust();
    double j = Nan::To<double>(info[4]).FromJust();
    double k = Nan::To<double>(info[5]).FromJust();
    double a = Nan::To<double>(info[6]).FromJust();
    double b = Nan::To<double>(info[7]).FromJust();
    double c = Nan::To<double>(info[8]).FromJust();

    int ok = apt->_apt->ws_toolpath_orientation (x,y,z, i,j,k, a,b,c);
    if (!ok) {
	THROW_ERROR(t);
    }
}



NAN_METHOD(AptStepMaker::Workpiece)
{
    Trace t(tc, "Workpiece");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;
    
    if (info.Length() != 1) return;
    if (!info[0]->IsString()) return;

    char * fname = 0;
    v8StringToChar(info[0], fname);
    int ok = apt->_apt->workpiece(fname);
    delete [] fname;

    if (!ok) {
	THROW_ERROR(t);
    }
}

NAN_METHOD(AptStepMaker::WorkplanSetup)
{
    Trace t(tc, "WorkplanSetup");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 10) return;
    if (!info[0]->IsInt32()) return;
    for (int tmp=1; tmp<10; tmp++) {
        if (info[tmp]->IsUndefined()) return;
	if (!info[tmp]->IsNumber()) return;
    }
	
    int wpid = Nan::To<int32_t>(info[0]).FromJust(); 
    double x = Nan::To<double>(info[1]).FromJust();
    double y = Nan::To<double>(info[2]).FromJust();
    double z = Nan::To<double>(info[3]).FromJust();
    double i = Nan::To<double>(info[4]).FromJust();
    double j = Nan::To<double>(info[5]).FromJust();
    double k = Nan::To<double>(info[6]).FromJust();
    double a = Nan::To<double>(info[7]).FromJust();
    double b = Nan::To<double>(info[8]).FromJust();
    double c = Nan::To<double>(info[9]).FromJust();

    int ok = apt->_apt->workplan_setup(wpid, x,y,z, i,j,k, a,b,c);
    if (!ok) {
	THROW_ERROR(t);
    }
}

NAN_METHOD(AptStepMaker::WorkplanSetupDelete)
{
    Trace t(tc, "WorkplanSetupDelete");
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt) return;

    if (info.Length() != 1) return;
    if (!info[0]->IsInt32()) return;
	
    int wpid = Nan::To<int32_t>(info[0]).FromJust(); 

    int ok = apt->_apt->workplan_setup_delete(wpid);
    if (!ok) {
	THROW_ERROR(t);
    }
}

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

#include "nodeFinder.h"
#include "nodeUtils.h"
Finder *Finder::_singleton = nullptr;

NAN_METHOD(Finder::New)
{
	if (info.IsConstructCall())
	{
		if (!info[0]->IsUndefined())
		{
			return;
		}
		if (_singleton == nullptr)
			_singleton = new Finder();
		_singleton->Wrap(info.This());
		info.GetReturnValue().Set(info.This());
	}
	else
	{
		return;
	}
}

NAN_MODULE_INIT(Finder::Init)
{
	v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
	tpl->SetClassName(Nan::New("Finder").ToLocalChecked());
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	Nan::SetPrototypeMethod(tpl, "APIUnitsInch", APIUnitsInch);
	Nan::SetPrototypeMethod(tpl, "APIUnitsMM", APIUnitsMM);
	Nan::SetPrototypeMethod(tpl, "APIUnitsNative", APIUnitsNative);
	Nan::SetPrototypeMethod(tpl, "APIUnitsFeed", APIUnitsFeed);
	Nan::SetPrototypeMethod(tpl, "APIUnitsSpeed", APIUnitsSpeed);
	Nan::SetPrototypeMethod(tpl, "GetCompoundFeatureCount", GetCompoundFeatureCount);
    Nan::SetPrototypeMethod(tpl, "GetExecutableBaseTime", GetExecutableBaseTime);
    Nan::SetPrototypeMethod(tpl, "GetExecutableContainer" GetExecutableContainer);
	Nan::SetPrototypeMethod(tpl, "GetExecutableDistance", GetExecutableDistance);
	Nan::SetPrototypeMethod(tpl, "GetExecutableDistanceUnit", GetExecutableDistanceUnit);
	Nan::SetPrototypeMethod(tpl, "GetExecutableName", GetExecutableName);
    Nan::SetPrototypeMethod(tpl, "GetExecutableTimeUnit", GetExecutableTimeUnit);
	Nan::SetPrototypeMethod(tpl, "GetExecutableType", GetExecutableType);
	Nan::SetPrototypeMethod(tpl, "GetExecutableWorkpieceAsIs", GetExecutableWorkpieceAsIs);
	Nan::SetPrototypeMethod(tpl, "GetExecutableWorkpieceAsIsLocal", GetExecutableWorkpieceAsIsLocal);
	Nan::SetPrototypeMethod(tpl, "GetExecutableWorkpieceRemoval", GetExecutableWorkpieceRemoval);
	Nan::SetPrototypeMethod(tpl, "GetExecutableWorkpieceRemovalLocal", GetExecutableWorkpieceRemovalLocal);
	Nan::SetPrototypeMethod(tpl, "GetExecutableWorkpieceToBe", GetExecutableWorkpieceToBe);
	Nan::SetPrototypeMethod(tpl, "GetExecutableWorkpieceToBeLocal", GetExecutableWorkpieceToBeLocal);
	Nan::SetPrototypeMethod(tpl, "GetFaceEdgeCount", GetFaceEdgeCount);
	Nan::SetPrototypeMethod(tpl, "GetFaceEdgeNextPoint", GetFaceEdgeCount);
	Nan::SetPrototypeMethod(tpl, "GetFeatureID", GetFeatureID);
	Nan::SetPrototypeMethod(tpl, "GetFeatureName", GetFeatureName);
	Nan::SetPrototypeMethod(tpl, "GetFeatureOutsideProfileClosedCircular", GetFeatureOutsideProfileClosedCircular);
	Nan::SetPrototypeMethod(tpl, "GetMainWorkplan", GetMainWorkplan);
	Nan::SetPrototypeMethod(tpl, "GetMaterialName", GetMaterialName);
	Nan::SetPrototypeMethod(tpl, "GetNestedExecutableAll", GetNestedExecutableAll);
	Nan::SetPrototypeMethod(tpl, "GetNestedExecutableAllEnabled", GetNestedExecutableAllEnabled);
	Nan::SetPrototypeMethod(tpl, "GetNestedExecutableCount", GetNestedExecutableCount);
	Nan::SetPrototypeMethod(tpl, "GetNestedExecutableNext", GetNestedExecutableNext);
	Nan::SetPrototypeMethod(tpl, "GetProcessFeed", GetProcessFeed);
	Nan::SetPrototypeMethod(tpl, "GetProcessFeedUnit", GetProcessFeedUnit);
	Nan::SetPrototypeMethod(tpl, "GetProjectName", GetProjectName);
    Nan::SetPrototypeMethod(tpl, "GetSelectiveExecutableAll", GetSelectiveExecutableAll);
    Nan::SetPrototypeMethod(tpl, "GetSelectiveExecutableAllEnabled", GetSelectiveExecutableAllEnabled);
    Nan::SetPrototypeMethod(tpl, "GetSelectiveExecutableCount", GetSelectiveExecutableCount);
    Nan::SetPrototypeMethod(tpl, "GetSelectiveExecutableNext", GetSelectiveExecutableNext);
    Nan::SetPrototypeMethod(tpl, "GetToolAll", GetToolAll);
    Nan::SetPrototypeMethod(tpl, "GetToolCornerRadius", GetToolCornerRadius);
    Nan::SetPrototypeMethod(tpl, "GetToolCornerRadiusUnit", GetToolCornerRadiusUnit);
    Nan::SetPrototypeMethod(tpl, "GetToolCurrentLength", GetToolCurrentLength);
    Nan::SetPrototypeMethod(tpl, "GetToolDiameter", GetToolDiameter);
    Nan::SetPrototypeMethod(tpl, "GetToolDiameterUnit", GetToolDiameterUnit);
    Nan::SetPrototypeMethod(tpl, "GetToolFluteLength", GetToolFluteLength);
    Nan::SetPrototypeMethod(tpl, "GetToolFluteLengthUnit", GetToolFluteLengthUnit);
	Nan::SetPrototypeMethod(tpl, "GetToolIdentifier", GetToolIdentifier);
    Nan::SetPrototypeMethod(tpl, "GetToolLength", GetToolLength);
    Nan::SetPrototypeMethod(tpl, "GetToolLengthUnit", GetToolLengthUnit);
    Nan::SetPrototypeMethod(tpl, "GetToolMaterial", GetToolMaterial);
	Nan::SetPrototypeMethod(tpl, "GetToolNumber", GetToolNumber);
	Nan::SetPrototypeMethod(tpl, "GetToolNumberAsNumber", GetToolNumberAsNumber);
    Nan::SetPrototypeMethod(tpl, "GetToolOverallAssemblyLength", GetToolOverallAssemblyLength);
    Nan::SetPrototypeMethod(tpl, "GetToolOverallAssemblyLengthUnit", GetToolOverallAssemblyLengthUnit);
	Nan::SetPrototypeMethod(tpl, "GetToolPartName", GetToolPartName);
	Nan::SetPrototypeMethod(tpl, "GetToolProductID", GetToolProductID);
    Nan::SetPrototypeMethod(tpl, "GetToolRadiusLower", GetToolRadiusLower);
    Nan::SetPrototypeMethod(tpl, "GetToolRadiusLowerReason", GetToolRadiusLowerReason);
    Nan::SetPrototypeMethod(tpl, "GetToolRadiusUpper", GetToolRadiusUpper);
    Nan::SetPrototypeMethod(tpl, "GetToolRadiusUpperReason", GetToolRadiusUpperReason);
	Nan::SetPrototypeMethod(tpl, "GetToolReferenceDataName", GetToolReferenceDataName);
    Nan::SetPrototypeMethod(tpl, "GetToolType", GetToolType);
	Nan::SetPrototypeMethod(tpl, "GetToolUsingNumber", GetToolUsingNumber);
	Nan::SetPrototypeMethod(tpl, "GetWorkingstep", GetWorkingstep);
	Nan::SetPrototypeMethod(tpl, "GetWorkingstepName", GetWorkingstepName);
	Nan::SetPrototypeMethod(tpl, "GetWorkingstepTool", GetWorkingstepTool);
    Nan::SetPrototypeMethod(tpl, "GetWorkpieceAll", GetWorkpieceAll);
    Nan::SetPrototypeMethod(tpl, "GetWorkpieceAsIsOfMain", GetWorkpieceAsIsOfMain);
    Nan::SetPrototypeMethod(tpl, "GetWorkpieceToBeOfMain", GetWorkpieceToBeOfMain);
    Nan::SetPrototypeMethod(tpl, "GetWorkpieceDeltaOfMain", GetWorkpieceDeltaOfMain);
    Nan::SetPrototypeMethod(tpl, "GetWorkpieceFixtureOfMain", GetWorkpieceFixtureOfMain);
    Nan::SetPrototypeMethod(tpl, "GetWorkpieceName", GetWorkpieceName);
    Nan::SetPrototypeMethod(tpl, "GetWorkpieceType", GetWorkpieceType);
    Nan::SetPrototypeMethod(tpl, "GetWorkpieceUnits", GetWorkpieceUnits);
	Nan::SetPrototypeMethod(tpl, "GetWorkplanExecutableAll", GetWorkplanExecutableAll);
	Nan::SetPrototypeMethod(tpl, "GetWorkplanExecutableAllEnabled", GetWorkplanExecutableAllEnabled);
	Nan::SetPrototypeMethod(tpl, "GetWorkplanName", GetWorkplanName);
	Nan::SetPrototypeMethod(tpl, "GetWorkplanProcessFeatureCount", GetWorkplanProcessFeatureCount);
	Nan::SetPrototypeMethod(tpl, "GetWorkplanProcessFeatureNext", GetWorkplanProcessFeatureNext);
	Nan::SetPrototypeMethod(tpl, "GetWorkplanSize", GetWorkplanSize);
    Nan::SetPrototypeMethod(tpl, "GetWorkplanToolAll", GetWorkplanToolAll);
    Nan::SetPrototypeMethod(tpl, "GetWorkplanToolCount", GetWorkplanToolCount);
    Nan::SetPrototypeMethod(tpl, "GetWorkplanToolNext", GetWorkplanToolNext);
	Nan::SetPrototypeMethod(tpl, "IsEnabled", IsEnabled);
	Nan::SetPrototypeMethod(tpl, "IsSelective", IsSelective);
	Nan::SetPrototypeMethod(tpl, "IsWorkingstep", IsWorkingstep);
	Nan::SetPrototypeMethod(tpl, "IsWorkplan", IsWorkplan);
	Nan::SetPrototypeMethod(tpl, "IsWorkplanWIthSetupAndFixture", IsWorkplanWIthSetupAndFixture);
	Nan::SetPrototypeMethod(tpl, "IsWorkplanWithSetup", IsWorkplanWithSetup);
	Nan::SetPrototypeMethod(tpl, "IsWorkplanWithSetupAndFixtureMount", IsWorkplanWithSetupAndFixtureMount);
	Nan::SetPrototypeMethod(tpl, "IsWorkplanWithSetupAndWorkpieceMount", IsWorkplanWithSetupAndWorkpieceMount);
	Nan::SetPrototypeMethod(tpl, "OpenProject", OpenProject);
	Nan::SetPrototypeMethod(tpl, "SaveAsModules", SaveAsModules);
	Nan::SetPrototypeMethod(tpl, "SaveAsP21", SaveAsP21);
	constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
	Nan::Set(target, Nan::New("Finder").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(Finder::APIUnitsFeed) {
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (!find) //Throw Exception
	return;
    if (info.Length() != 1) //Function takes one argument
	return;
    if (info[0]->IsUndefined()) //Argument should exist
	return;
    if (!info[0]->IsString()) //Throw Exception
	return;
    char * b;
    v8StringToChar(info[0], b);
    if (!find->_find->api_unit_feed(b)) //Throw Exception
	return;
    delete[] b;
}
NAN_METHOD(Finder::APIUnitsInch) {

    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) {
	return; // Throw Exception
    }
    if (!(info[0]->IsUndefined())) { // function has 0 arguements
	return; //Throw Exeption
    }
    if (!find->_find->api_unit_inch()) {
	return; //throw error
    }
    return;

}

NAN_METHOD(Finder::APIUnitsMM) {

    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (find == 0) {
	return; // Throw Exception
    }
    if (!(info[0]->IsUndefined())) { // function has 0 arguements
	return; //Throw Exeption
    }
    if (!find->_find->api_unit_mm()) {
	return; //throw error
    }
    return;
}

NAN_METHOD(Finder::APIUnitsNative) {

    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (find == 0) {
	return; // Throw Exception
    }
    if (!(info[0]->IsUndefined())) { // function has 0 arguements
	return; //Throw Exeption
    }
    if (!find->_find->api_unit_native()) {
	return; //throw error
    }
    return;
}

NAN_METHOD(Finder::APIUnitsSpeed) {
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (!find) //Throw Exception
	return;
    if (info.Length() != 1) //Function takes one argument
	return;
    if (info[0]->IsUndefined()) //Argument should exist
	return;
    if (!info[0]->IsString()) //Throw Exception
	return;
    char * b;
    v8StringToChar(info[0], b);
    if (!find->_find->api_unit_speed(b)) //Throw Exception
	return;
    delete[] b;
}



NAN_METHOD(Finder::GetCompoundFeatureCount) {

    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) {
	return; //Throw an exception
    }
    if (info.Length() != 1) { // Needs one argument
	return; // Throw an exception
    }
    if (!info[0]->IsNumber()) { // argument of wrong type
	return; //Throw exception
    }
    int size = 0;
    int feature_id = 0;
    double x;
    double y;
    double z;

    if (!find->_find->first_feature_in_compound(Nan::To<int32_t>(info[0]).FromJust(), feature_id, size, x, y, z)) {
	return; //throw Error
    }

    info.GetReturnValue().Set(size);
    return;
}

NAN_METHOD(Finder::GetExecutableBaseTime)
{
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) // Throw exception
    return;

    if (info.Length() != 1) // incorrect number of arguments
    return;

    if (!info[0]->IsInt32()) // invalid argument
    return;

    // get this executable's id
    Nan::Maybe<int32_t> exe_id = Nan::To<int32_t>(info[0]);

    double time = 0.0;
    double over_time, distance;

    const char *str1, *str2;

    if (!find->_find->compute_best_feed_time(
    exe_id.FromJust(), distance, time, over_time, str1, str2
    ))  // cpp error
    return;

    info.GetReturnValue().Set(time);
    return;
}

NAN_METHOD(Finder::GetExecutableContainer)
{
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) // Throw exception
    return;

    if (info.Length() != 1) // incorrect number of arguments
    return;

    if (!info[0]->IsInt32()) // invalid argument
    return;

    Nan::Maybe<int32_t> exe_id = Nan::To<int32_t>(info[0]);

    int wp_id = 0;

    if (!find->_find->executable_container((int)exe_id, wp_id)) return;

    info.GetReturnValue().Set(wp_id);
    return;
}

NAN_METHOD(Finder::GetExecutableDistance)
{
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) // Throw exception
	return;

    if (info.Length() != 1) // incorrect number of arguments
	return;

    if (!info[0]->IsInt32()) // invalid argument
	return;

    // get this executable's id
    Nan::Maybe<int32_t> exe_id = Nan::To<int32_t>(info[0]);

    double distance = 0.0;
    double over_time, base_time;

    const char *str1, *str2;

    if (!find->_find->compute_best_feed_time(
	exe_id.FromJust(), distance, base_time, over_time, str1, str2
	))	// cpp error
	return;

    info.GetReturnValue().Set(distance);
    return;
}

NAN_METHOD(Finder::GetExecutableDistanceUnit)
{
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) // Throw exception
	return;

    if (info.Length() != 1) // incorrect number of arguments
	return;

    if (!info[0]->IsInt32()) // invalid argument
	return;

    // get this executable's id
    Nan::Maybe<int32_t> exe_id = Nan::To<int32_t>(info[0]);

    const char *dist_unit = 0;
    double over_time, base_time, distance;
    const char *str2;

    if (!find->_find->compute_best_feed_time(
	exe_id.FromJust(), distance, base_time, over_time, dist_unit, str2
	))
	return;
    if(dist_unit){
    info.GetReturnValue().Set(CharTov8String((char*) dist_unit));
}
    else{
        info.GetReturnValue().Set(0);
    }

    return;
}

NAN_METHOD(Finder::GetExecutableName) {
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) // Throw exception
	return;

    if (info.Length() != 1) // incorrect number of arguments
	return;

    if (!info[0]->IsInt32()) // invalid argument
	return;

    const char * name = 0;
    Nan::Maybe<int32_t> t = Nan::To<int32_t>(info[0]);
    if (!find->_find->executable_name(t.FromJust(), name))
	return;

    info.GetReturnValue().Set(CharTov8String((char *)name));
    return;
}

NAN_METHOD(Finder::GetExecutableTimeUnit)
{
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) // Throw exception
    return;

    if (info.Length() != 1) // incorrect number of arguments
    return;

    if (!info[0]->IsInt32()) // invalid argument
    return;

    // get this executable's id
    Nan::Maybe<int32_t> exe_id = Nan::To<int32_t>(info[0]);

    const char *time_unit = 0;
    double over_time, base_time, distance;
    const char *str1;

    if (!find->_find->compute_best_feed_time(
    exe_id.FromJust(), distance, base_time, over_time, str1, time_unit
    ))
    return;


    if(time_unit){
        info.GetReturnValue().Set(CharTov8String((char*) time_unit));
    }
    else{
        info.GetReturnValue().Set(0);
    }

    return;
}

NAN_METHOD(Finder::GetExecutableType) {
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) // Throw exception
	return;

    if (info.Length() != 1) // incorrect number of arguments
	return;

    if (!info[0]->IsInt32()) // invalid argument
	return;

    const char * type = 0;
    Nan::Maybe<int32_t> t = Nan::To<int32_t>(info[0]);
    if (!find->_find->executable_type(t.FromJust(), type))
	return;

    info.GetReturnValue().Set(CharTov8String((char *)type));
    return;
}

NAN_METHOD(Finder::GetExecutableWorkpieceAsIs)
{
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) // Throw exception
	return;

    if (info.Length() != 1) // incorrect number of arguments
	return;


    if (!info[0]->IsInt32())// invalid argument
	return;

    Nan::Maybe<int32_t> exe_id = Nan::To<int32_t>(info[0]);
    int wp_id = 0;

    if (!find->_find->executable_as_is_workpiece(exe_id.FromJust(), wp_id))// error in cpp
	return;

    info.GetReturnValue().Set(wp_id);
    return;
}

NAN_METHOD(Finder::GetExecutableWorkpieceAsIsLocal)
{
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) // Throw exception
	return;

    if (info.Length() != 1) // incorrect number of arguments
	return;


    if (!info[0]->IsInt32())// invalid argument
	return;

    Nan::Maybe<int32_t> exe_id = Nan::To<int32_t>(info[0]);
    int wp_id = 0;

    if (!find->_find->local_executable_as_is_workpiece(exe_id.FromJust(), wp_id))// error in cpp
	return;

    info.GetReturnValue().Set(wp_id);
    return;
}

NAN_METHOD(Finder::GetExecutableWorkpieceRemoval)
{
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) // Throw exception
	return;

    if (info.Length() != 1) // incorrect number of arguments
	return;


    if (!info[0]->IsInt32())	// invalid argument
	return;

    Nan::Maybe<int32_t> exe_id = Nan::To<int32_t>(info[0]);

    int wp_id = 0;

    if (!find->_find->executable_removal_workpiece(exe_id.FromJust(), wp_id))    // error in cpp
	return;

    info.GetReturnValue().Set(wp_id);

    return;
}

NAN_METHOD(Finder::GetExecutableWorkpieceRemovalLocal)
{
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) // Throw exception
	return;

    if (info.Length() != 1) // incorrect number of arguments
	return;


    if (!info[0]->IsInt32())	// invalid argument
	return;

    Nan::Maybe<int32_t> exe_id = Nan::To<int32_t>(info[0]);

    int wp_id = 0;

    if (!find->_find->local_executable_removal_workpiece(exe_id.FromJust(), wp_id))    // error in cpp
	return;

    info.GetReturnValue().Set(wp_id);

    return;
}

NAN_METHOD(Finder::GetExecutableWorkpieceToBe) {
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) // Throw exception
	return;

    if (info.Length() != 1) // incorrect number of arguments
	return;


    if (!info[0]->IsInt32())// invalid argument
	return;

    Nan::Maybe<int32_t> exe_id = Nan::To<int32_t>(info[0]);
    int wp_id = 0;

    if (!find->_find->executable_to_be_workpiece(exe_id.FromJust(), wp_id))// error in cpp
	return;

    info.GetReturnValue().Set(wp_id);
    return;
}

NAN_METHOD(Finder::GetExecutableWorkpieceToBeLocal) {
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) // Throw exception
	return;

    if (info.Length() != 1) // incorrect number of arguments
	return;


    if (!info[0]->IsInt32())// invalid argument
	return;

    Nan::Maybe<int32_t> exe_id = Nan::To<int32_t>(info[0]);
    int wp_id = 0;

    if (!find->_find->local_executable_to_be_workpiece(exe_id.FromJust(), wp_id))// error in cpp
	return;

    info.GetReturnValue().Set(wp_id);
    return;
}

NAN_METHOD(Finder::GetFaceEdgeCount)
{
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
	return;

    if (info.Length() != 1)
	return;

    if (info[0]->IsUndefined()) //Needs one arg
	return;

    int count = 0;
    double dummy1, dummy2, dummy3;
    if (!find->_find->first_face_edge_point(Nan::To<int32_t>(info[0]).FromJust(), count, dummy1, dummy2, dummy3))
	return;

    info.GetReturnValue().Set(count);
    return;
}

//{ret_x1:double, ret_y1:double, ret_z1:double, ret_x2:double, ret_y2:double, ret_z2:double}
NAN_METHOD(Finder::GetFaceEdgeNextPoint)
{
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
	return;
    if (info.Length() != 2) //Needs 2 args
	return;

    double x1 = 0.0;
    double y1 = 0.0;
    double z1 = 0.0;
    double x2 = 0.0;
    double y2 = 0.0;
    double z2 = 0.0;

    if (!find->_find->next_face_edge_point(Nan::To<int32_t>(info[0]).FromJust(),
	Nan::To<int32_t>(info[1]).FromJust(), x1, y1, z1, x2, y2, z2)) //Throw Exception
	return;

    v8::Local<v8::Object> jsonReturn = Nan::New<v8::Object>();
    Nan::Set(jsonReturn, CharTov8String("ret_x1"), Nan::New(x1));
    Nan::Set(jsonReturn, CharTov8String("ret_y1"), Nan::New(y1));
    Nan::Set(jsonReturn, CharTov8String("ret_z1"), Nan::New(z1));
    Nan::Set(jsonReturn, CharTov8String("ret_x2"), Nan::New(x2));
    Nan::Set(jsonReturn, CharTov8String("ret_y2"), Nan::New(y2));
    Nan::Set(jsonReturn, CharTov8String("ret_z2"), Nan::New(z2));

    info.GetReturnValue().Set(jsonReturn);
    return;
}

NAN_METHOD(Finder::GetFeatureID) {
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (info.Length() != 1)
	return;
    if (info[0]->IsUndefined())
	return;
    if (!info[0]->IsInt32())
	return;

    int feature_id = 0;

    Nan::Maybe<int32_t> t = Nan::To<int32_t>(info[0]);

    if (!find->_find->feature_id(t.FromJust(), feature_id))
	return;

    info.GetReturnValue().Set(feature_id);
    return;
}

NAN_METHOD(Finder::GetFeatureName) {
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (info.Length() != 1)
	return;
    if (info[0]->IsUndefined())
	return;
    if (!info[0]->IsInt32())
	return;

    const char * name = 0;
    Nan::Maybe<int32_t> t = Nan::To<int32_t>(info[0]);
    if (!find->_find->feature_name(t.FromJust(), name))
	return;

    info.GetReturnValue().Set(CharTov8String((char *)name));
    return;
}

//{rtn: bool, profile_id: long, depth: double, diameter: double, x: double, y: double, z: double}
NAN_METHOD(Finder::GetFeatureOutsideProfileClosedCircular) {
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (info.Length() != 1)
	return;
    if (info[0]->IsUndefined())
	return;
    if (!info[0]->IsInt32())
	return;
    Nan::Maybe<int32_t> t = Nan::To<int32_t>(info[0]);
    int profile_id = 0;
    double depth = 0.0;
    double diameter = 0.0;
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;


    if (!find->_find->is_circular_outside_profile(t.FromJust(), profile_id, depth, diameter, x, y, z))
	return;

    v8::Local<v8::Object> obj = Nan::New<v8::Object>();
    Nan::Set(obj, CharTov8String("rtn"), Nan::New(true)); //Add case to check if profile_id was found
    Nan::Set(obj, CharTov8String("profile_id"), Nan::New(profile_id));
    Nan::Set(obj, CharTov8String("depth"), Nan::New(depth));
    Nan::Set(obj, CharTov8String("diameter"), Nan::New(diameter));
    Nan::Set(obj, CharTov8String("x"), Nan::New(x));
    Nan::Set(obj, CharTov8String("y"), Nan::New(y));
    Nan::Set(obj, CharTov8String("z"), Nan::New(z));

    info.GetReturnValue().Set(obj);
}

NAN_METHOD(Finder::GetMainWorkplan) {
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
	    return;
    if (!info[0]->IsUndefined()) //Function shouldn't get any arguments.
	    return;
    int rtn = 0;
    int sz;
    if (!find->_find->main(rtn, sz))
	    return;//Error in c++ code
    info.GetReturnValue().Set(rtn);
    return;
}

NAN_METHOD(Finder::GetMaterialName)
{
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
    return;

    if (info.Length() != 1)
    return;

    if (info[0]->IsUndefined()) //Needs one arg
    return;

    if (!info[0]->IsInt32())
    return;

    const char* name = 0;
    if (!find->_find->material(Nan::To<int32_t>(info[0]).FromJust(), name)) //Throw Exception
    return;


    info.GetReturnValue().Set(CharTov8String((char *)name));
    return;
}

NAN_METHOD(Finder::GetNestedExecutableAll)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
	return;
    if (info.Length() != 1) //This function should get one argument.
	return;
    if (!info[0]->IsInt32())
	return;
    Nan::Maybe<int32_t> wp_id = Nan::To<int32_t>(info[0]);
    v8::Local<v8::Array> exes = Nan::New<v8::Array>();
    rose_uint_vector tmp;
    if (!find->_find->nested_executable_all(wp_id.FromJust(), tmp)) //TODO: Handle error
	return;
    for (unsigned i = 0; i < tmp.size(); i++)
    {
	int pt = tmp.get(i);
	exes->Set(i, Nan::New(pt));
    }
    info.GetReturnValue().Set(exes);
    return;
}

NAN_METHOD(Finder::GetNestedExecutableAllEnabled)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0)  //Throw Exception
	return;
    if (info.Length() != 1) //This function should get one argument
	return;
    if (!info[0]->IsInt32())
	return;
    Nan::Maybe<int32_t> wp_id = Nan::To<int32_t>(info[0]);
    v8::Local<v8::Array> exes = Nan::New<v8::Array>();
    rose_uint_vector tmp;
    if (!find->_find->nested_executable_all_enabled(wp_id.FromJust(), tmp)) //TODO: Handle error
	return;
    for (unsigned i = 0; i < tmp.size(); i++)
    {
	int pt = tmp.get(i);
	exes->Set(i, Nan::New(pt));
    }
    info.GetReturnValue().Set(exes);
    return;
}

NAN_METHOD(Finder::GetNestedExecutableCount)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
	return;
    if (info.Length() != 1) //This function should get one argument.
	return;
    if (!info[0]->IsInt32())
	return;
    Nan::Maybe<int32_t> exe_id = Nan::To<int32_t>(info[0]);
    int count = 0;
    if (!find->_find->nested_executable_count(exe_id.FromJust(), count)) //TODO: Handle error
	return;
    info.GetReturnValue().Set(count);
    return;
}

NAN_METHOD(Finder::GetNestedExecutableNext)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0)  //Throw Exception
	return;
    if (info.Length() != 2) //This function should get two arguments.
	return;
    if (!info[0]->IsInt32())
	return;
    if (!info[1]->IsInt32())
	return;
    Nan::Maybe<int32_t> wp_id = Nan::To<int32_t>(info[0]);
    Nan::Maybe<int32_t> index = Nan::To<int32_t>(info[1]);
    int exe_id = 0;
    if (!find->_find->nested_executable_next(wp_id.FromJust(), index.FromJust(), exe_id))
	return;
    info.GetReturnValue().Set(exe_id);
    return;
}

NAN_METHOD(Finder::GetProcessFeed) {
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (info.Length() != 1) //Throw Exception
	return;
    if (info[0]->IsUndefined()) //Throw Exception
	return;
    if (!info[0]->IsInt32()) //Throw Exception
	return;
    double feed = 0.0;
    double dummy;
    Nan::Maybe<int32_t> ws_id = Nan::To<int32_t>(info[0]);
    if (!find->_find->feed_speed(ws_id.FromJust(), feed, dummy)) //Throw Exception
	return;
    info.GetReturnValue().Set(feed);
    return;
}

NAN_METHOD(Finder::GetProcessFeedUnit) {
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (info.Length() != 1) //Throw Exception
	return;
    if (info[0]->IsUndefined()) //Throw Exception
	return;
    if (!info[0]->IsInt32()) //Throw Exception
	return;
    const char* unit = 0;
    const char* dummy = 0;
    Nan::Maybe<int32_t> ws_id = Nan::To<int32_t>(info[0]);
    if (!find->_find->feed_speed_unit(ws_id.FromJust(), unit, dummy)) //Throw Exception
	return;
    info.GetReturnValue().Set(CharTov8String((char *)unit));
    return;
}

NAN_METHOD(Finder::GetProjectName) {
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) {
	return; //throw exception
    }
    if (!info[0]->IsUndefined()) {
	return; //throw exception
    }
    const char * prj_name = 0;
    const char * szWP;

    if (!(find->_find->project(prj_name, szWP))) {
	return; //Throw Error
    }

    info.GetReturnValue().Set(CharTov8String((char *)prj_name));
    return;
}

NAN_METHOD(Finder::GetSelectiveExecutableAll) {
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) {
    return; //throw exception
    }
    if (info.Length() != 1) {
    return; //throw exception
    }
    if (!info[0]->IsNumber()) {
    return; // Throw exception
    }
    Nan::Maybe<int32_t> wp_id = Nan::To<int32_t>(info[0]);
    v8::Local<v8::Array> exes = Nan::New<v8::Array>();
    rose_uint_vector tmp;
    if (!find->_find->selective_executable_all(wp_id.FromJust(), tmp)) {
    return; //Throw error
    }
    for (unsigned i = 0; i < tmp.size(); i++) {
    int pt = tmp.get(i);
    exes->Set(i, Nan::New(pt));
    }

    info.GetReturnValue().Set(exes);
    return;
}

NAN_METHOD(Finder::GetSelectiveExecutableAllEnabled)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0)
    return; //throw exception

    if (info.Length() != 1)
    return; // invalid num of args

    if (!info[0]->IsNumber())
    return; // invalid argument

    Nan::Maybe<int32_t> wp_id = Nan::To<int32_t>(info[0]);
    v8::Local<v8::Array> exes = Nan::New<v8::Array>();

    rose_uint_vector tmp;
    if (!find->_find->selective_executable_all_enabled(wp_id.FromJust(), tmp))
    return; //Throw error

    for (unsigned i = 0; i < tmp.size(); i++) {
    int pt = tmp.get(i);
    exes->Set(i, Nan::New(pt));
    }

    info.GetReturnValue().Set(exes);
    return;
}

NAN_METHOD(Finder::GetSelectiveExecutableCount) {

    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) {
    return; //throw exception
    }
    if (info.Length() != 1) {
    return; //throw exception
    }
    if (!info[0]->IsNumber()) {
    return; // Throw exception
    }
    int count = 0;
    if (!(find->_find->selective_executable_count(Nan::To<int32_t>(info[0]).FromJust(), count))) {
    return; // throw error
    }
    info.GetReturnValue().Set(count);
    return;
}

NAN_METHOD(Finder::GetSelectiveExecutableNext) {
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) {
    return; //throw exception
    }
    if (info.Length() != 2) {
    return; //throw exception
    }
    if (!info[0]->IsNumber()) {
    return; // Throw exception
    }
    if (!info[1]->IsNumber()) {
    return; // Throw exception
    }

    int exe_id = 0;
    if (!(find->_find->selective_executable_next(Nan::To<int32_t>(info[0]).FromJust(), Nan::To<int32_t>(info[1]).FromJust(), exe_id))) {
    return; //Throw Error
    }
    info.GetReturnValue().Set(exe_id);
}

NAN_METHOD(Finder::GetToolAll)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
    return;

    if (info.Length() != 0)
    return;

    int size = 0;
    if(!find->_find->tool_count(size))
    return;

    v8::Local<v8::Array> array = Nan::New<v8::Array>();
    for (int i = 0; i < size; i++) {
        int tl_id = 0;
        if (!find->_find->tool_next(i, tl_id)) //Throw Exception
            return;
        else
            array->Set(i, Nan::New(tl_id));
    }

    info.GetReturnValue().Set(array);
    return;
}

NAN_METHOD(Finder::GetToolCornerRadius)
{
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (info.Length() != 1)
    return;
    if (info[0]->IsUndefined())
    return;
    if (!info[0]->IsInt32())
    return;

    Nan::Maybe<int32_t> t = Nan::To<int32_t>(info[0]);

    double radius = 0.0;
    double dummy;
    if (!find->_find->tool_current(t.FromJust(), dummy, radius, dummy, dummy, dummy, dummy))
    return;

    info.GetReturnValue().Set(radius);
    return;
}

NAN_METHOD(Finder::GetToolCornerRadiusUnit)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (find == 0)
    return; //throw exception

    if (info.Length() != 1)
    return; //throw exception

    if (!info[0]->IsInt32())
    return; //  invalid argument

    Nan::Maybe<int32_t> ws_id = Nan::To<int32_t>(info[0]);
    const char * unit = 0;
    const char * dummy;

    if (!find->_find->tool_current_unit(ws_id.FromJust(), dummy, unit, dummy))
    return; // error in cpp

    if (!(unit && *unit))
    return; // value not set, return undefined

    info.GetReturnValue().Set(CharTov8String((char *)unit));
    return;
}

NAN_METHOD(Finder::GetToolCurrentLength){
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
    return;
    if (info.Length() != 1) //Throw Exception
    return;
    if (!info[0]->IsInt32()) //Throw Exception
        return;

    Nan::Maybe<int32_t> tl_id = Nan::To<int32_t>(info[0]);

    double nominal_value = 0.0; //If nominal value is needed it can be added to return
    double current_value = 0.0;
    double dummy;

    if (!find->_find->tool_current(
        tl_id.FromJust(), dummy, dummy, nominal_value, dummy, dummy, current_value
    ))
        return;

    info.GetReturnValue().Set(current_value);
    return;
}

NAN_METHOD(Finder::GetToolDiameter) {
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (info.Length() != 1)
    return;
    if (info[0]->IsUndefined())
    return;
    if (!info[0]->IsInt32())
    return;

    Nan::Maybe<int32_t> t = Nan::To<int32_t>(info[0]);

    double diam = 0.0;
    double dummy;
    if (!find->_find->tool_current(t.FromJust(), diam, dummy, dummy, dummy, dummy, dummy))
    return;

    info.GetReturnValue().Set(diam);
    return;
}

NAN_METHOD(Finder::GetToolDiameterUnit) {
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (find == 0)
    return; //throw exception

    if (info.Length() != 1)
    return; //throw exception

    if (!info[0]->IsInt32())
    return; //  invalid argument

    Nan::Maybe<int32_t> ws_id = Nan::To<int32_t>(info[0]);
    const char * unit = 0;
    const char * dummy;

    if (!find->_find->tool_current_unit(ws_id.FromJust(), unit, dummy, dummy))
    return; // error in cpp

    info.GetReturnValue().Set(CharTov8String((char *) unit));
    return;
}

NAN_METHOD(Finder::GetToolFluteLength)
{
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (info.Length() != 1)
    return;
    if (info[0]->IsUndefined())
    return;
    if (!info[0]->IsInt32())
    return;

    Nan::Maybe<int32_t> t = Nan::To<int32_t>(info[0]);

    double flute_length = 0.0;
    if (!find->_find->tool_flute_length(t.FromJust(), flute_length))
    return;

    info.GetReturnValue().Set(flute_length);
    return;
}

NAN_METHOD(Finder::GetToolFluteLengthUnit)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (find == 0)
    return; //throw exception

    if (info.Length() != 1)
    return; //throw exception

    if (!info[0]->IsInt32())
    return; //  invalid argument

    Nan::Maybe<int32_t> ws_id = Nan::To<int32_t>(info[0]);
    const char * unit = 0;

    if (!find->_find->tool_flute_length_unit(ws_id.FromJust(), unit))
    return; // error in cpp

    info.GetReturnValue().Set(CharTov8String((char *) unit));
    return;
}

NAN_METHOD(Finder::GetToolIdentifier)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (find == 0)
	return; //throw exception

    if (info.Length() != 1)
	return; //throw exception

    if (!info[0]->IsInt32())
	return;	//  invalid argument

    Nan::Maybe<int32_t> ws_id = Nan::To<int32_t>(info[0]);
    const char * name = 0;

    if (!find->_find->tool_reference_data_name(ws_id.FromJust(), name))
	return;	// error in cpp

    info.GetReturnValue().Set(CharTov8String((char *) name));
    return;
}

NAN_METHOD(Finder::GetToolLength) {
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
        return;
    if (info.Length() != 1) //Throw Exception
        return;

    Nan::Maybe<int32_t> tl_id = Nan::To<int32_t>(info[0]);
    printf("%d\n", (int)tl_id.FromJust());
    double length = 0.0;
    double dummy;


    if (!find->_find->tool_current(
        tl_id.FromJust(), length, dummy, dummy, dummy, dummy, dummy
        )
    )
        return;
    info.GetReturnValue().Set(length);
}

NAN_METHOD(Finder::GetToolLengthUnit) {
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
        return;
    if (info.Length() != 1) //Throw Exception
        return;

    Nan::Maybe<int32_t> tl_id = Nan::To<int32_t>(info[0]);
    const char * unit = 0;
    const char * dummy = 0;

    if (!find->_find->tool_current_unit((int)tl_id.FromJust(), unit, dummy, dummy))
        return;

    info.GetReturnValue().Set(CharTov8String((char *)unit));
}

NAN_METHOD(Finder::GetToolMaterial) {
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0)
        return;
    if (info.Length() != 1)
        return;

    Nan::Maybe<int32_t> tl_id = Nan::To<int32_t>(info[0]);
    const char * material = 0;
    const char * szName1;

    if (!find->_find->tool_material((int)tl_id.FromJust(), material, szName1))
        return;

    info.GetReturnValue().Set(CharTov8String((char *)material));
}

NAN_METHOD(Finder::GetToolNumber)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (find == 0)
	return; //throw exception

    if (info.Length() != 1)
	return; //throw exception

    if (!info[0]->IsInt32())
	return;	//  invalid argument

    Nan::Maybe<int32_t> ws_id = Nan::To<int32_t>(info[0]);
    const char * its_id = 0;

    if (!find->_find->tool_number_as_id(ws_id.FromJust(), its_id))
	return;	// error in cpp

    if (!(its_id && *its_id))
	return;	// value not set, return undefined

    info.GetReturnValue().Set(CharTov8String((char *)its_id));
    return;
}

NAN_METHOD(Finder::GetToolNumberAsNumber)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (find == 0)
	return; //throw exception

    if (info.Length() != 1)
	return; //throw exception

    if (!info[0]->IsInt32())
	return;	//  invalid argument

    Nan::Maybe<int32_t> ws_id = Nan::To<int32_t>(info[0]);
    int toolno = 0;

    if (!find->_find->tool_number(ws_id.FromJust(), toolno))
	return;	// error in cpp

    if (toolno == 0)
	return;	// value not set, return undefined

    info.GetReturnValue().Set(toolno);
    return;
}

NAN_METHOD(Finder::GetToolOverallAssemblyLength)
{
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (info.Length() != 1)
    return;
    if (info[0]->IsUndefined())
    return;
    if (!info[0]->IsInt32())
    return;

    Nan::Maybe<int32_t> t = Nan::To<int32_t>(info[0]);

    double length = 0.0;
    if (!find->_find->tool_overall_assembly_length(t.FromJust(), length))
    return;

    info.GetReturnValue().Set(length);
    return;
}

NAN_METHOD(Finder::GetToolOverallAssemblyLengthUnit)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (find == 0)
	return; //throw exception

    if (info.Length() != 1)
	return; //throw exception

    if (!info[0]->IsInt32())
	return;	//  invalid argument

    Nan::Maybe<int32_t> ws_id = Nan::To<int32_t>(info[0]);
    const char * unit = 0;

    if (!find->_find->tool_overall_assembly_length_unit(ws_id.FromJust(), unit))
	return;	// error in cpp

    if (!(unit && *unit))
	return;	// value not set, return undefined

    info.GetReturnValue().Set(CharTov8String((char *)unit));
    return;
}

NAN_METHOD(Finder::GetToolPartName)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (find == 0)
	return; //throw exception

    if (info.Length() != 1)
	return; //throw exception

    if (!info[0]->IsInt32())
	return;	//  invalid argument

    Nan::Maybe<int32_t> ws_id = Nan::To<int32_t>(info[0]);
    const char * name = 0;
    int pd_id;

    if (!find->_find->tool_part_name(ws_id.FromJust(), pd_id, name))
	return; // error in cpp

    info.GetReturnValue().Set(CharTov8String((char*)name));
    return;
}

NAN_METHOD(Finder::GetToolProductID)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (find == 0)
	return; //throw exception

    if (info.Length() != 1)
	return; //throw exception

    if (!info[0]->IsInt32())
	return;	//  invalid argument

    Nan::Maybe<int32_t> tl_id = Nan::To<int32_t>(info[0]);

    const char* szPN;
    int pd_id = 0;

    if (!find->_find->tool_part_name(tl_id.FromJust(), pd_id, szPN))
	return; // error in cpp

    info.GetReturnValue().Set(pd_id);

    return;
}

NAN_METHOD(Finder::GetToolRadiusLower)
{
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (info.Length() != 1)
    return;
    if (info[0]->IsUndefined())
    return;
    if (!info[0]->IsInt32())
    return;

    Nan::Maybe<int32_t> t = Nan::To<int32_t>(info[0]);

    double value = 0.0;
    double dummy;
    const char *s1, *s2;
    if (!find->_find->tool_radius_lower_upper(t.FromJust(), dummy, value, s1, dummy, s2))
    return;

    info.GetReturnValue().Set(value);
    return;
}

NAN_METHOD(Finder::GetToolRadiusLowerReason)
{
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (info.Length() != 1)
    return;
    if (info[0]->IsUndefined())
    return;
    if (!info[0]->IsInt32())
    return;

    Nan::Maybe<int32_t> t = Nan::To<int32_t>(info[0]);

    double dummy;
    const char *s1, *s2;
    if (!find->_find->tool_radius_lower_upper(t.FromJust(), dummy, dummy, s1, dummy, s2))
    return;

    info.GetReturnValue().Set(CharTov8String((char*)s1));
    return;
}

NAN_METHOD(Finder::GetToolRadiusUpper)
{
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (info.Length() != 1)
    return;
    if (info[0]->IsUndefined())
    return;
    if (!info[0]->IsInt32())
    return;

    Nan::Maybe<int32_t> t = Nan::To<int32_t>(info[0]);

    double value = 0.0;
    double dummy;
    const char *s1, *s2;
    if (!find->_find->tool_radius_lower_upper(t.FromJust(), dummy, dummy, s1, value, s2))
    return;

    info.GetReturnValue().Set(value);
    return;
}

NAN_METHOD(Finder::GetToolRadiusUpperReason)
{
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (info.Length() != 1)
    return;
    if (info[0]->IsUndefined())
    return;
    if (!info[0]->IsInt32())
    return;

    Nan::Maybe<int32_t> t = Nan::To<int32_t>(info[0]);

    double dummy;
    const char *s1, *s2;
    if (!find->_find->tool_radius_lower_upper(t.FromJust(), dummy, dummy, s1, dummy, s2))
    return;

    info.GetReturnValue().Set(CharTov8String((char*)s2));
    return;
}

NAN_METHOD(Finder::GetToolReferenceDataName)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (find == 0)
	return; //throw exception

    if (info.Length() != 1)
	return; //throw exception

    if (!info[0]->IsInt32())
	return;	//  invalid argument

    Nan::Maybe<int32_t> ws_id = Nan::To<int32_t>(info[0]);

    const char* name = 0;

    if (!find->_find->tool_reference_data_name(ws_id.FromJust(), name))
	return;

    if (!name || !(*name))   // if we got no return value
	return;	// return undefined

    info.GetReturnValue().Set(CharTov8String((char*)name));

    return;
}

NAN_METHOD(Finder::GetToolType) {
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
        return;
    if (info.Length() != 1) //Throw Exception
        return;

    Nan::Maybe<int32_t> ws_id = Nan::To<int32_t>(info[0]);
    const char * type = 0;

    if (!find->_find->tool_type((int)ws_id.FromJust(), type))
        return;

    info.GetReturnValue().Set(CharTov8String((char *)type));
}

NAN_METHOD(Finder::GetToolUsingNumber)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (find == 0)
	return; //throw exception

    if (info.Length() != 1)
	return; //throw exception

    if (!info[0]->IsString())
	return;	//  invalid argument

    int tool_id = 0;
    char* id = 0;
    v8StringToChar(info[0], id);

    if (!find->_find->find_tool_using_its_id(id, tool_id))
	return; // error in cpp

    info.GetReturnValue().Set(tool_id);

    delete[] id;

    return;
}

NAN_METHOD(Finder::GetWorkingstep) {
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
	return;
    if (info.Length() != 2) //Throw Exception
	return;
    if (!info[0]->IsInt32()) //Throw Exception
	return;
    if (!info[1]->IsInt32())
	return;

    Nan::Maybe<int32_t> wp_id = Nan::To<int32_t>(info[0]);
    Nan::Maybe<int32_t> index = Nan::To<int32_t>(info[1]);
    int exe_id = 0;
    const char* name = 0;
    if (!find->_find->is_workingstep(wp_id.FromJust(), index.FromJust(), exe_id, name))
	return;
    info.GetReturnValue().Set(exe_id);
    return;
}

NAN_METHOD(Finder::GetWorkingstepName) {
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (info.Length() != 1)
	return;
    if (info[0]->IsUndefined())
	return;
    if (!info[0]->IsInt32())
	return;

    const char * name = 0;
    Nan::Maybe<int32_t> t = Nan::To<int32_t>(info[0]);
    if (!find->_find->workingstep_name(t.FromJust(), name))
	return;

    info.GetReturnValue().Set(CharTov8String((char *)name));
    return;
}

NAN_METHOD(Finder::GetWorkingstepTool)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (find == 0)  // throw exception
	return;

    if (info.Length() != 1) // throw exception
	return;

    if (!info[0]->IsInt32())	// invalid argument
	return;

    Nan::Maybe<int32_t> ws_id = Nan::To<int32_t>(info[0]);

    int tl_id = 0;

    if (!find->_find->tool_from_ws(ws_id.FromJust(), tl_id))
	return; // error in cpp

    info.GetReturnValue().Set(tl_id);
    return;
}

NAN_METHOD(Finder::GetWorkpieceAll)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
    return;
    if (info.Length() != 0) //Throw Exception
    return;
    int count = 0;
    if (!find->_find->workpiece_count(count)) //Throw Exception
    return;

    v8::Local<v8::Array> array = Nan::New<v8::Array>();
    for (int i = 0; i < count; i++) {
        int wp_id = 0;
        if (!find->_find->workpiece_next(i, wp_id)) //Throw Exception
            return;
        else
            array->Set(i, Nan::New(wp_id));
    }

    info.GetReturnValue().Set(array);
    return;
}

NAN_METHOD(Finder::GetWorkpieceAsIsOfMain)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (find == 0)  // throw exception
    return;

    if (info.Length() != 0) // throw exception
    return;

    int wp_id = 0;

    if (!find->_find->asis_of_main(wp_id))
    return; // error in cpp

    info.GetReturnValue().Set(wp_id);
    return;
}

NAN_METHOD(Finder::GetWorkpieceToBeOfMain)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (find == 0)  // throw exception
    return;

    if (info.Length() != 0) // throw exception
    return;

    int wp_id = 0;

    if (!find->_find->tobe_of_main(wp_id))
    return; // error in cpp

    info.GetReturnValue().Set(wp_id);
    return;
}

NAN_METHOD(Finder::GetWorkpieceDeltaOfMain)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (find == 0)  // throw exception
    return;

    if (info.Length() != 0) // throw exception
    return;

    int wp_id = 0;

    if (!find->_find->delta_of_main(wp_id))
    return; // error in cpp

    info.GetReturnValue().Set(wp_id);
    return;
}

NAN_METHOD(Finder::GetWorkpieceFixtureOfMain)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (find == 0)  // throw exception
    return;

    if (info.Length() != 0) // throw exception
    return;

    int wp_id = 0;

    if (!find->_find->fixture_of_main(wp_id))
    return; // error in cpp

    info.GetReturnValue().Set(wp_id);
    return;
}

NAN_METHOD(Finder::GetWorkpieceName) {
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (info.Length() != 1)
    return;
    if (info[0]->IsUndefined())
    return;
    if (!info[0]->IsInt32())
    return;

    const char * name = 0;
    Nan::Maybe<int32_t> t = Nan::To<int32_t>(info[0]);
    if (!find->_find->workpiece_any_name(t.FromJust(), name))
    return;

    info.GetReturnValue().Set(CharTov8String((char *)name));
    return;
}

NAN_METHOD(Finder::GetWorkpieceType) {
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (info.Length() != 1)
    return;
    if (info[0]->IsUndefined())
    return;
    if (!info[0]->IsInt32())
    return;

    const char * type = 0;
    Nan::Maybe<int32_t> t = Nan::To<int32_t>(info[0]);
    if (!find->_find->workpiece_any_classification(t.FromJust(), type))
    return;

    info.GetReturnValue().Set(CharTov8String((char *)type));
    return;
}

NAN_METHOD(Finder::GetWorkpieceUnits) {
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (info.Length() != 1)
    return;
    if (info[0]->IsUndefined())
    return;
    if (!info[0]->IsInt32())
    return;

    const char * unit = 0;
    Nan::Maybe<int32_t> t = Nan::To<int32_t>(info[0]);
    if (!find->_find->workpiece_any_units(t.FromJust(), unit))
    return;

    info.GetReturnValue().Set(CharTov8String((char *)unit));
    return;
}

NAN_METHOD(Finder::GetWorkplanExecutableAll)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (find == 0)  // throw exception
	return;

    if (info.Length() != 1) // throw exception
	return;

    if (!info[0]->IsInt32())	// invalid argument
	return;

    Nan::Maybe<int32_t> wp_id = Nan::To<int32_t>(info[0]);
    v8::Local<v8::Array> exes = Nan::New<v8::Array>();

    rose_uint_vector tmp;

    if (!find->_find->workplan_executable_all(wp_id.FromJust(), tmp))
	return; // error in cpp

    for (uint i = 0; i < tmp.size(); i++)
    {
	int pt = tmp.get(i);
	exes->Set(i, Nan::New(pt));
    }

    info.GetReturnValue().Set(exes);

    return;
}

NAN_METHOD(Finder::GetWorkplanExecutableAllEnabled)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());

    if (find == 0)  // throw exception
	return;

    if (info.Length() != 1) // throw exception
	return;

    if (!info[0]->IsInt32())	// invalid argument
	return;

    Nan::Maybe<int32_t> wp_id = Nan::To<int32_t>(info[0]);
    v8::Local<v8::Array> exes = Nan::New<v8::Array>();

    rose_uint_vector tmp;

    if (!find->_find->workplan_executable_all_enabled(wp_id.FromJust(), tmp))
	return; // error in cpp

    for (uint i = 0; i < tmp.size(); i++)
    {
	int pt = tmp.get(i);
	exes->Set(i, Nan::New(pt));
    }

    info.GetReturnValue().Set(exes);

    return;
}

NAN_METHOD(Finder::GetWorkplanName) {
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
	return;
    if (info.Length() != 1) //Throw Exception
	return;
    if (!info[0]->IsInt32()) //Throw Exception
	return;

    const char  * wp_name = 0;
    int nSize;
    Nan::Maybe<int32_t> tl_id = Nan::To<int32_t>(info[0]);
    if (!find->_find->workplan(tl_id.FromJust(), nSize, wp_name)) //Throw Exception
	return;
    info.GetReturnValue().Set(CharTov8String((char *)wp_name));
    return;
}

NAN_METHOD(Finder::GetWorkplanProcessFeatureCount) {
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
	return;
    if (info.Length() != 1) //Throw Exception
	return;
    if (!info[0]->IsInt32()) //Throw Exception
	return;

    int size = 0;
    Nan::Maybe<int32_t> wp_id = Nan::To<int32_t>(info[0]);
    if (!find->_find->wp_process_feature_count(wp_id.FromJust(), size)) //Throw Exception
	return;
    info.GetReturnValue().Set(size);
    return;
}

NAN_METHOD(Finder::GetWorkplanProcessFeatureNext) {
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
	return;
    if (info.Length() != 2) //Throw Exception
	return;
    if (!info[0]->IsInt32()) //Throw Exception
	return;
    if (!info[1]->IsInt32()) //Throw Exception
	return;

    int fe_id = 0;
    Nan::Maybe<int32_t> wp_id = Nan::To<int32_t>(info[0]);
    Nan::Maybe<int32_t> index = Nan::To<int32_t>(info[1]);
    if (!find->_find->wp_process_feature_next(wp_id.FromJust(), index.FromJust(), fe_id)) //Throw Exception
	return;
    info.GetReturnValue().Set(fe_id);
    return;
}

NAN_METHOD(Finder::GetWorkplanSize) {
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
	return;
    if (info.Length() != 1) //Throw Exception
	return;
    if (!info[0]->IsInt32()) //Throw Exception
	return;

    int size = 0;
    const char* szName;
    Nan::Maybe<int32_t> wp_id = Nan::To<int32_t>(info[0]);
    if (!find->_find->workplan(wp_id.FromJust(), size, (const char*&)szName))
	return;
    info.GetReturnValue().Set(size);
    return;
}

NAN_METHOD(Finder::GetWorkplanToolAll) {
	Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
    return;
    if (info.Length() != 1) //Throw Exception
    return;
    if (!info[0]->IsInt32()) //Throw Exception
    return;
    Nan::Maybe<int32_t> wp_id = Nan::To<int32_t>(info[0]);
	int size = 0;
    if (!find->_find->wp_tool_count(wp_id.FromJust(), size)) //Throw Exception
    return;

	v8::Local<v8::Array> array = Nan::New<v8::Array>();
	for (int i = 0; i < size; i++) {
		int tl_id = 0;
		if (!find->_find->wp_tool_next(wp_id.FromJust(), i, tl_id)) //Throw Exception
		    return;
		else
			array->Set(i, Nan::New(tl_id));
	}

	info.GetReturnValue().Set(array);
	return;
}

NAN_METHOD(Finder::GetWorkplanToolCount) {
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
	return;
    if (info.Length() != 1) //Throw Exception
	return;
    if (!info[0]->IsInt32()) //Throw Exception
	return;

    int size = 0;
    Nan::Maybe<int32_t> wp_id = Nan::To<int32_t>(info[0]);
    if (!find->_find->wp_tool_count(wp_id.FromJust(), size)) //Throw Exception
	return;
    info.GetReturnValue().Set(size);
    return;
}

NAN_METHOD(Finder::GetWorkplanToolNext) {
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
	return;
    if (info.Length() != 2) //Throw Exception
	return;
    if (!info[0]->IsInt32()) //Throw Exception
	return;
    if (!info[1]->IsInt32()) //Throw Exception
	return;

    int tl_id = 0;
    Nan::Maybe<int32_t> wp_id = Nan::To<int32_t>(info[0]);
    Nan::Maybe<int32_t> index = Nan::To<int32_t>(info[1]);
    if (!find->_find->wp_tool_next(wp_id.FromJust(), index.FromJust(), tl_id)) //Throw Exception
	return;
    info.GetReturnValue().Set(tl_id);
    return;
}

NAN_METHOD(Finder::IsEnabled) {

    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (!find) //Throw Exception
	return;
    if (info.Length() != 1) //Throw Exception
	return;
    if (!info[0]->IsInt32()) //Throw Exception
	return;

    int flag = 0;

    Nan::Maybe<int32_t> exe_id = Nan::To<int32_t>(info[0]);

    if (!find->_find->is_enabled(exe_id.FromJust(), flag)) //Throw Exception
	return;
    info.GetReturnValue().Set((flag != 0));
}

NAN_METHOD(Finder::IsSelective)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
	return;

    if (info.Length() != 1)
	return;

    if (info[0]->IsUndefined())
	return;

    if (!info[0]->IsInt32())
	return;

    int flag = 0;

    if (!find->_find->is_selective(Nan::To<int32_t>(info[0]).FromJust(), flag)) //Throw Exception
	return;

    info.GetReturnValue().Set((flag != 0));
    return;
}

NAN_METHOD(Finder::IsWorkingstep)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
	return;

    if (info.Length() != 1)
	return;

    if (info[0]->IsUndefined())
	return;

    if (!info[0]->IsInt32())
	return;

    int flag = 0;

    if (!find->_find->is_workingstep(Nan::To<int32_t>(info[0]).FromJust(), flag)) //Throw Exception
	return;

    info.GetReturnValue().Set((flag != 0));
    return;
}

NAN_METHOD(Finder::IsWorkplan)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
	return;

    if (info.Length() != 1)
	return;

    if (info[0]->IsUndefined())
	return;

    if (!info[0]->IsInt32())
	return;

    int flag = 0;

    if (!find->_find->is_workplan(Nan::To<int32_t>(info[0]).FromJust(), flag)) //Throw Exception
	return;

    info.GetReturnValue().Set((flag != 0));
    return;
}

NAN_METHOD(Finder::IsWorkplanWIthSetupAndFixture)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
	return;

    if (info.Length() != 1)
	return;

    if (info[0]->IsUndefined())
	return;

    if (!info[0]->IsInt32())
	return;

    int flag = 0;

    if (!find->_find->is_workplan_with_setup_and_fixture(Nan::To<int32_t>(info[0]).FromJust(), flag)) //Throw Exception
	return;

    info.GetReturnValue().Set((flag != 0));
    return;
}

NAN_METHOD(Finder::IsWorkplanWithSetup)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
	return;

    if (info.Length() != 1)
	return;

    if (info[0]->IsUndefined())
	return;

    if (!info[0]->IsInt32())
	return;

    int flag = 0;

    if (!find->_find->is_workplan_with_setup(Nan::To<int32_t>(info[0]).FromJust(), flag)) //Throw Exception
	return;

    info.GetReturnValue().Set((flag != 0));
    return;
}

NAN_METHOD(Finder::IsWorkplanWithSetupAndFixtureMount)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
	return;

    if (info.Length() != 1)
	return;

    if (info[0]->IsUndefined())
	return;

    if (!info[0]->IsInt32())
	return;

    int flag = 0;

    if (!find->_find->is_workplan_with_setup_and_fixture_mount(Nan::To<int32_t>(info[0]).FromJust(), flag)) //Throw Exception
	return;

    info.GetReturnValue().Set((flag != 0));
    return;
}

NAN_METHOD(Finder::IsWorkplanWithSetupAndWorkpieceMount)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
	return;

    if (info.Length() != 1)
	return;

    if (info[0]->IsUndefined())
	return;

    if (!info[0]->IsInt32())
	return;

    int flag = 0;

    if (!find->_find->is_workplan_with_setup_and_workpiece_mount(Nan::To<int32_t>(info[0]).FromJust(), flag)) //Throw Exception
	return;

    info.GetReturnValue().Set((flag != 0));
    return;
}

NAN_METHOD(Finder::OpenProject) {
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
	    return;
    if (info.Length() != 1) //Function should get one argument.
	    return;
    if (!info[0]->IsString())
	    return;
    char * fname = 0;
    v8StringToChar(info[0], fname);
    if(!find->_find->search(fname)) //TODO: Handle Error.
	    return;
    return; //Success finding, return.
}

NAN_METHOD(Finder::SaveAsModules)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
	return;

    if (info.Length() != 1)
	return;

    if (info[0]->IsUndefined())
	return;

    if (!info[0]->IsString())
	return;

    char* file_name_utf8;
    v8StringToChar(info[0], file_name_utf8);


    if (!find->_find->save_file(file_name_utf8, true)) //Throw Exception
	return;
}

NAN_METHOD(Finder::SaveAsP21)
{
	Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
	if (find == 0) //Throw Exception
		return;

	if (info.Length() != 1)
	    return;

	if (info[0]->IsUndefined())
		return;

	if (!info[0]->IsString())
		return;

	char* file_name_utf8;
	v8StringToChar(info[0], file_name_utf8);


	if (!find->_find->save_file(file_name_utf8, false)) //Throw Exception
		return;
}

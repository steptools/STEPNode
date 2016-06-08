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
	Nan::SetPrototypeMethod(tpl, "GetExecutableDistance", GetExecutableDistance);
	Nan::SetPrototypeMethod(tpl, "GetExecutableDistanceUnit", GetExecutableDistanceUnit);
	Nan::SetPrototypeMethod(tpl, "GetExecutableName", GetExecutableName);
	Nan::SetPrototypeMethod(tpl, "GetExecutableType", GetExecutableType);
	Nan::SetPrototypeMethod(tpl, "GetExecutableWorkpieceRemoval", GetExecutableWorkpieceRemoval);
	Nan::SetPrototypeMethod(tpl, "GetFaceEdgeCount", GetFaceEdgeCount);
	Nan::SetPrototypeMethod(tpl, "GetFaceEdgeNextPoint", GetFaceEdgeCount);
	Nan::SetPrototypeMethod(tpl, "GetFeatureID", GetFeatureID);
	Nan::SetPrototypeMethod(tpl, "GetFeatureName", GetFeatureName);
	Nan::SetPrototypeMethod(tpl, "GetFeatureOutsideProfileClosedCircular", GetFeatureOutsideProfileClosedCircular);
	Nan::SetPrototypeMethod(tpl, "GetMainWorkplan", GetMainWorkplan);
	Nan::SetPrototypeMethod(tpl, "GetProcessFeed", GetProcessFeed);
	Nan::SetPrototypeMethod(tpl, "GetProcessFeedUnit", GetProcessFeedUnit);
	Nan::SetPrototypeMethod(tpl, "GetProjectName", GetProjectName);
<<<<<<< HEAD
	Nan::SetPrototypeMethod(tpl, "GetWorkplanName", GetWorkplanName);
=======
	Nan::SetPrototypeMethod(tpl, "GetSelectiveExecutableCount", GetSelectiveExecutableCount);
>>>>>>> refs/remotes/origin/master
	Nan::SetPrototypeMethod(tpl, "IsEnabled", IsEnabled);
	Nan::SetPrototypeMethod(tpl, "IsSelective", IsSelective);
	Nan::SetPrototypeMethod(tpl, "IsWorkingstep", IsWorkingstep);
	Nan::SetPrototypeMethod(tpl, "IsWorkplan", IsWorkplan);
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
    size_t len = v8StringToChar(info[0], b);
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
    size_t len = v8StringToChar(info[0], b);
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

    info.GetReturnValue().Set(CharTov8String((char*) dist_unit));

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

NAN_METHOD(Finder::GetFaceEdgeCount)
{
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
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
    if (info.Length() < 8) //Needs 8 arg
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
    jsonReturn->Set(CharTov8String("ret_x1"), info[2]);
    jsonReturn->Set(CharTov8String("ret_y1"), info[3]);
    jsonReturn->Set(CharTov8String("ret_z1"), info[4]);
    jsonReturn->Set(CharTov8String("ret_x2"), info[5]);
    jsonReturn->Set(CharTov8String("ret_y2"), info[6]);
    jsonReturn->Set(CharTov8String("ret_z2"), info[7]);

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
}

NAN_METHOD(Finder::GetProcessFeedUnit) {
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (info.Length() != 1) //Throw Exception
	return;
    if (info[0]->IsUndefined()) //Throw Exception
	return;
    if (!info[0]->IsInt32()) //Throw Exception
	return;
    const char* unit = "";
    const char* dummy = "";
    Nan::Maybe<int32_t> ws_id = Nan::To<int32_t>(info[0]);
    if (!find->_find->feed_speed_unit(ws_id.FromJust(), (const char*&)unit, (const char*&)dummy)) //Throw Exception
	return;
    info.GetReturnValue().Set(CharTov8String((char *)unit));
}

NAN_METHOD(Finder::GetProjectName) {
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) {
	return; //throw exception
    }
    if (info[0]->IsUndefined()) {
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

NAN_METHOD(Finder::GetWorkplanName) {
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
	return;
    if (info.Length() != 1) //Throw Exception
	return;
    
    const char  * wp_name = "";
    int nSize;
    Nan::Maybe<int32_t> wp_id = Nan::To<int32_t>(info[0]);
    if (!find->_find->workplan(wp_id.FromJust(), nSize, (const char*&)wp_name)) //Throw Exception
	return;
    info.GetReturnValue().Set(CharTov8String((char *)wp_name));
}

NAN_METHOD(Finder::IsEnabled)
{
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

NAN_METHOD(Finder::OpenProject) {
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
	    return;
    if (info.Length() != 1) //Function should get one argument.
	    return;
    if (!info[0]->IsString())
	    return;
    char * fname = 0;
    ssize_t fnamelen = v8StringToChar(info[0], fname);
    if(!find->_find->search(fname)) //TODO: Handle Error.
	    return;
    return; //Success finding, return.
}

NAN_METHOD(Finder::SaveAsModules)
{
    Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
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

	if (info[0]->IsUndefined())
		return;

	if (!info[0]->IsString())
		return;

	char* file_name_utf8;
	v8StringToChar(info[0], file_name_utf8);


	if (!find->_find->save_file(file_name_utf8, false)) //Throw Exception
		return;
}
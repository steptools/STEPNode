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

	Nan::SetPrototypeMethod(tpl, "APIUnitsFeed", APIUnitsFeed);
	Nan::SetPrototypeMethod(tpl, "APIUnitsSpeed", APIUnitsSpeed);
	Nan::SetPrototypeMethod(tpl, "GetExecutableDistance", GetExecutableDistance);
	Nan::SetPrototypeMethod(tpl, "GetFaceEdgeCount", GetFaceEdgeCount);
	Nan::SetPrototypeMethod(tpl, "GetFeatureID", GetFeatureID);
	Nan::SetPrototypeMethod(tpl, "GetFeatureName", GetFeatureName);
	Nan::SetPrototypeMethod(tpl, "GetMainWorkplan", GetMainWorkplan);
	Nan::SetPrototypeMethod(tpl, "GetProcessFeed", GetProcessFeed);
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

NAN_METHOD(Finder::GetExecutableDistance)
{
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) // Throw exception
	return;
    
    if (info.Length() != 1) // incorrect number of arguments
	return;

    if (!info[0]->IsNumber()) // invalid argument
	return;

    // get this executable's id
    int64_t exe_id = info[0]->IntegerValue();

    // keep a total value
    double rtn_distance = 0.0;

    // get the nested executables
    rose_uint_vector nested_list;
    if (!find->_find->nested_executable_all_enabled(exe_id, nested_list))   // error in cpp
	return;

    for (uint i = 0; i < nested_list.size(); i++)
    {
	// check if the executable is a workingstep
	int is_ws;
	if (!find->_find->is_workingstep(nested_list[i], is_ws))    // error in cpp
	    return;

	int is_enabled;
	if (!find->_find->is_enabled(nested_list[i], is_enabled))    // error in cpp
	    return;
	
	// for non-workingsteps, continue iterating through sublists
	if (!is_ws && is_enabled)
	{
	    v8::Local<v8::Value> argv = Nan::New<v8::Number>(nested_list[i]);

	    // recursively call GetExecutableDistance for the nested executable
	    // and store the value so we can add it to our total
	    double subDist = Nan::MakeCallback(info.This(), "GetExecutableDistance", 1, &argv)->NumberValue();

	    rtn_distance += subDist;
	}
	else if (is_enabled)
	{
	    // get all paths in workstep and calculate distance
	    rose_uint_vector path_list;
	    if (!find->_find->all_path(nested_list[i], path_list))  // error in cpp
		return;

	    for (uint j = 0; j < path_list.size(); j++)
	    {
		// iterate over all curves in each path
		rose_uint_vector curve_list;
		if (!find->_find->all_curve(path_list[i], curve_list))	// error in cpp
		    return;

		for (uint k = 0; k < curve_list.size() - 1; k++)
		{
		    RoseReal3DArray point_list;
		    if (!find->_find->all_points(curve_list[i], point_list))	// error in cpp
			return;

		    // calculate distance between points and add to running total
		    RosePoint point_a = point_list.as_point(k);
		    RosePoint point_b = point_list.as_point(k+1);

		    rtn_distance += rose_pt_distance(point_a, point_b);
		}

		// TODO: figure out if we need to add distance between curves
	    }
	}
    }

    // now set return value as total distance
    info.GetReturnValue().Set(rtn_distance);

    return;
}

NAN_METHOD(Finder::GetFaceEdgeCount)
{
    Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
    if (find == 0) //Throw Exception
	return;
    if (!info[0]->IsUndefined()) //Needs one arg
	return;

    int count = 0;
    double dummy1, dummy2, dummy3;
    if (!find->_find->first_face_edge_point(info[0]->Int32Value(), count, dummy1, dummy2, dummy3))
	return;

    info.GetReturnValue().Set(count);
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

    if (!find->_find->feature_id(info[0]->Int32Value(), feature_id))
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

    if (!find->_find->feature_name(info[0]->Int32Value(), name))
	return;

    info.GetReturnValue().Set(CharTov8String((char *)name));
    return;
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
    int ws_id = info[0]->Int32Value();
    if (!find->_find->feed_speed((int)ws_id, feed, dummy)) //Throw Exception
	return;
    info.GetReturnValue().Set(feed);
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

    if (!info[0]->IsUndefined())
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

	if (!info[0]->IsUndefined())
		return;

	if (!info[0]->IsString())
		return;

	char* file_name_utf8;
	v8StringToChar(info[0], file_name_utf8);


	if (!find->_find->save_file(file_name_utf8, false)) //Throw Exception
		return;
}
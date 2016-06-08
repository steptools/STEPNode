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
#pragma once

#include <nan.h>
#include <stncapt/Find.h>

class Finder : public Nan::ObjectWrap {
private:
    finder * _find;
    static Finder* _singleton;
    static NAN_METHOD(New);
    static inline Nan::Persistent<v8::Function> & constructor() {
	static Nan::Persistent<v8::Function> my_constructor;
	return my_constructor;
    }
    Finder() { _find = new finder(); };
    ~Finder() { delete _find; };
public:
    static NAN_MODULE_INIT(Init);

    //void APIUnitsFeed(System::String^ units);
    static NAN_METHOD(APIUnitsFeed);

    //void APIUnitsInch();
    static NAN_METHOD(APIUnitsInch);

    //void APIUnitsMM();
    static NAN_METHOD(APIUnitsMM);

    //void APIUnitsNative();
    static NAN_METHOD(APIUnitsNative);

    //void APIUnitsSpeed(System::String^ units);
    static NAN_METHOD(APIUnitsSpeed);
    
    //System::int64 GetCompoundFeatureCount(system::int64 compound_id)'
    static NAN_METHOD(GetCompoundFeatureCount);

    // double GetExecutableDistance(int exe_id)
    static NAN_METHOD(GetExecutableDistance);

    // string GetExecutableDistanceUnit(int exe_id)
    static NAN_METHOD(GetExecutableDistanceUnit);

    // string GetExecutableName(int exe_id)
    static NAN_METHOD(GetExecutableName);

    //int GetMainWorkplan();
    static NAN_METHOD(GetMainWorkplan);

    //long GetFaceEdgeCount(long face_id);
    static NAN_METHOD(GetFaceEdgeCount);

    //void GetFaceEdgeNextPoint(int face_id, int index, double %ret_x1, double %ret_y1, double %ret_z1, double %ret_x2, double %ret_y2, double %ret_z2);
    static NAN_METHOD(GetFaceEdgeNextPoint);

    //string GetFeatureName(long id)
    static NAN_METHOD(GetFeatureName);

    //long GetFeatureID(long ws_id);
    static NAN_METHOD(GetFeatureID);

    //int GetNestedExecutableCount (int exe_id);
    static NAN_METHOD(GetNestedExecutableCount);

    //int GetNestedExecutableNext (int wp_id, int index);
    static NAN_METHOD(GetNestedExecutableNext);

    //double GetProcessFeed (int ws_id);
    static NAN_METHOD(GetProcessFeed);

    //string GetProcessFeedUnit (int ws_id);
    static NAN_METHOD(GetProcessFeedUnit);

    //string GetProjectName();
    static NAN_METHOD(GetProjectName);

    //bool IsSelective(long exe_id);
    static NAN_METHOD(IsSelective);

    //bool IsSelective(long exe_id);
    static NAN_METHOD(IsWorkingstep);

    //void Open238(String file_name);
    static NAN_METHOD(OpenProject);

    //void SaveAsModules(v8::String file_name);
    static NAN_METHOD(SaveAsModules);

    //void SaveAsP21(v8::String file_name);
    static NAN_METHOD(SaveAsP21);

    //bool GetFeatureOutsideProfileClosedCircular(feature_id, prof_id, depth, diameter, x,y,z)
    static NAN_METHOD(GetFeatureOutsideProfileClosedCircular);
};
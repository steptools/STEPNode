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
    
    //long GetCompoundFeatureCount(long compound_id)
    static NAN_METHOD(GetCompoundFeatureCount);

    // double GetExecutableDistance(int exe_id)
    static NAN_METHOD(GetExecutableDistance);

    // string GetExecutableDistanceUnit(int exe_id)
    static NAN_METHOD(GetExecutableDistanceUnit);

    // string GetExecutableName(int exe_id)
    static NAN_METHOD(GetExecutableName);

    // string GetExecutableType(int exe_id)
    static NAN_METHOD(GetExecutableType);

    // int GetExecutableWorkpieceAsIs(int exe_id)
    static NAN_METHOD(GetExecutableWorkpieceAsIs);

    // int GetExecutableWorkpieceAsIsLocal(int exe_id)
    static NAN_METHOD(GetExecutableWorkpieceAsIsLocal);

    // int GetExecutableWorkpieceRemoval(int exe_id)
    static NAN_METHOD(GetExecutableWorkpieceRemoval);

    // int GetExecutableWorkpieceRemovalLocal(int exe_id)
    static NAN_METHOD(GetExecutableWorkpieceRemovalLocal);

    // int GetExecutableWorkpieceToBe(int exe_id)
    static NAN_METHOD(GetExecutableWorkpieceToBe);

    // int GetExecutableWorkpieceToBeLocal(int exe_id)
    static NAN_METHOD(GetExecutableWorkpieceToBeLocal);

    //int GetMainWorkplan();
    static NAN_METHOD(GetMainWorkplan);

    //string GetMaterialName(long wp_id);
    static NAN_METHOD(GetMaterialName);

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

    //string GetWorkplanName();
    static NAN_METHOD(GetWorkplanName);

    //int GetWorkplanProcessFeatureCount();
    static NAN_METHOD(GetWorkplanProcessFeatureCount);

    //int GetWorkplanProcessFeatureNext();
    static NAN_METHOD(GetWorkplanProcessFeatureNext);

    //int GetWorkplanSize();
    static NAN_METHOD(GetWorkplanSize);

    //int[] GetSelectiveExecutableAll( int wp_id)
    static NAN_METHOD(GetSelectiveExecutableAll);

    //int GetSelectiveExecutableCount( int sl_id)
    static NAN_METHOD(GetSelectiveExecutableCount);
    
    //int GetSelectiveExecutableNext(int wp_id, int index)
    static NAN_METHOD(GetSelectiveExecutableNext);

    //int GetWorkplanToolCount();
    static NAN_METHOD(GetWorkplanToolCount);

    //int GetWorkplanToolNext();
    static NAN_METHOD(GetWorkplanToolNext);
    
    //bool IsEnabled(int exe_id);
    static NAN_METHOD(IsEnabled);

    //bool IsSelective(long exe_id);
    static NAN_METHOD(IsSelective);

    //bool IsWorkingstep(long exe_id);
    static NAN_METHOD(IsWorkingstep);

    //bool IsWorkplan(long exe_id);
    static NAN_METHOD(IsWorkplan);

    //bool IsWorkplanWIthSetupAndFixture(long exe_id);
    static NAN_METHOD(IsWorkplanWIthSetupAndFixture);

    //bool IsWorkplanWithSetup(long exe_id);
    static NAN_METHOD(IsWorkplanWithSetup);

    //bool IsWorkplanWithSetupAndFixtureMount(long exe_id);
    static NAN_METHOD(IsWorkplanWithSetupAndFixtureMount);

    //bool IsWorkplanWithSetupAndWorkpieceMount(long exe_id);
    static NAN_METHOD(IsWorkplanWithSetupAndWorkpieceMount);

    //void Open238(String file_name);
    static NAN_METHOD(OpenProject);

    //void SaveAsModules(v8::String file_name);
    static NAN_METHOD(SaveAsModules);

    //void SaveAsP21(v8::String file_name);
    static NAN_METHOD(SaveAsP21);

    //bool GetFeatureOutsideProfileClosedCircular(feature_id, prof_id, depth, diameter, x,y,z)
    static NAN_METHOD(GetFeatureOutsideProfileClosedCircular);
};
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
//
// Author: Samson Bonfante (bonfante@steptools.com)
//


#pragma once

#include <nan.h>
#include <stncapt/Find.h>
#include <stncapt/message.h>
class Finder : public Nan::ObjectWrap {
private:
    finder * _find;
    static Finder* _singleton;
    static NAN_METHOD(New);
    static inline Nan::Persistent<v8::Function> & constructor() {
	static Nan::Persistent<v8::Function> my_constructor;
	return my_constructor;
    }
    Finder() {
	report_via_printf();
	_find = new finder(); 
    };
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

    //long GetCompoundFeatureCount(long compound_id)
    static NAN_METHOD(GetCompoundFeatureCount);

    // double GetExecutableBaseTime(int exe_id)
    static NAN_METHOD(GetExecutableBaseTime);

    // double GetExecutableBaseTime(int exe_id)
    static NAN_METHOD(GetExecutableContainer);

    // double GetExecutableDistance(int exe_id)
    static NAN_METHOD(GetExecutableDistance);

    // string GetExecutableDistanceUnit(int exe_id)
    static NAN_METHOD(GetExecutableDistanceUnit);

    // string GetExecutableName(int exe_id)
    static NAN_METHOD(GetExecutableName);

    // string GetExecutableTimeUnit(int exe_id)
    static NAN_METHOD(GetExecutableTimeUnit);

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

    //long GetFaceEdgeCount(long face_id);
    static NAN_METHOD(GetFaceEdgeCount);

    //void GetFaceEdgeNextPoint(int face_id, int index, double %ret_x1, double %ret_y1, double %ret_z1, double %ret_x2, double %ret_y2, double %ret_z2);
    static NAN_METHOD(GetFaceEdgeNextPoint);

    //string GetFeatureName(long id)
    static NAN_METHOD(GetFeatureName);

    //bool GetFeatureOutsideProfileClosedCircular(feature_id, prof_id, depth, diameter, x,y,z)
    static NAN_METHOD(GetFeatureOutsideProfileClosedCircular);

    //int GetMainWorkplan();
    static NAN_METHOD(GetMainWorkplan);

    //string GetMaterialName(long wp_id);
    static NAN_METHOD(GetMaterialName);

    //long GetFeatureID(long ws_id);
    static NAN_METHOD(GetFeatureID);

    //No .Net Dll implementation
    //static NAN_METHOD(GetGeometryJSON);

    //string GetJSONGeometry(string uuid, int usage)
    static NAN_METHOD(GetJSONGeometry);

    //string GetJSONProduct(int eid)
    static NAN_METHOD(GetJSONProduct);

    //int[] GetNestedExecutableAll (int wp_id);
    static NAN_METHOD(GetNestedExecutableAll);

    //int[] GetNestedExecutableAllEnabled (int wp_id);
    static NAN_METHOD(GetNestedExecutableAllEnabled);

    //int GetNestedExecutableCount (int exe_id);
    static NAN_METHOD(GetNestedExecutableCount);

    //int GetNestedExecutableNext (int wp_id, int index);
    static NAN_METHOD(GetNestedExecutableNext);

    //double GetProcessFeed (int ws_id);
    static NAN_METHOD(GetProcessFeed);

    //string GetProcessFeedUnit (int ws_id);
    static NAN_METHOD(GetProcessFeedUnit);

    //double GetProcessSpeed (int ws_id);
    static NAN_METHOD(GetProcessSpeed);

    //string GetProcessSpeedUnit (int ws_id);
    static NAN_METHOD(GetProcessSpeedUnit);

    //string GetProjectName();
    static NAN_METHOD(GetProjectName);

    //int[] GetSelectiveExecutableAll( int wp_id)
    static NAN_METHOD(GetSelectiveExecutableAll);

    //int[] GetSelectiveExecutableAllEnabled( int wp_id)
    static NAN_METHOD(GetSelectiveExecutableAllEnabled);

    //int GetSelectiveExecutableCount( int sl_id)
    static NAN_METHOD(GetSelectiveExecutableCount);

    //int GetSelectiveExecutableNext(int wp_id, int index)
    static NAN_METHOD(GetSelectiveExecutableNext);

    //New Function for NodeJS using gettoolcount and gettoolall
    static NAN_METHOD(GetToolAll);

    //double GetToolCornerRadius (int ws_id, bool %ret_value_set)
    static NAN_METHOD(GetToolCornerRadius);

    //string GetToolCornerRadiusUnit (int ws_id)
    static NAN_METHOD(GetToolCornerRadiusUnit);

    //double GetToolCurrentLength (int tl_id, bool nominal_set, bool current_set, double nominal_value)
    static NAN_METHOD(GetToolCurrentLength);

    //double GetToolDiameter (int ws_id, bool %ret_value_set)
    static NAN_METHOD(GetToolDiameter);

    //string GetToolDiameterUnit (int ws_id)
    static NAN_METHOD(GetToolDiameterUnit);

    //double GetToolFluteLength (int ws_id)
    static NAN_METHOD(GetToolFluteLength);

    //string GetToolFluteLengthUnit (int ws_id)
    static NAN_METHOD(GetToolFluteLengthUnit);

    //string GetToolIdentifier(int ws_id)
    static NAN_METHOD(GetToolIdentifier);

    //double GetToolLength (int tl_id)
    static NAN_METHOD(GetToolLength);

    //double GetToolLengthUnit (int tl_id)
    static NAN_METHOD(GetToolLengthUnit);

    //string GetToolMaterial(int tl_id)
    static NAN_METHOD(GetToolMaterial);

    //string GetToolNumber(int ws_id)
    static NAN_METHOD(GetToolNumber);

    //int GetToolNumberAsNumber(int ws_id)
    static NAN_METHOD(GetToolNumberAsNumber);

    //double GetToolOverallAssemblyLength(int ws_id)
    static NAN_METHOD(GetToolOverallAssemblyLength);

    //string GetToolOverallAssemblyLengthUnit(int ws_id)
    static NAN_METHOD(GetToolOverallAssemblyLengthUnit);

    //string GetToolPartName(int ws_id)
    static NAN_METHOD(GetToolPartName);

    //int GetToolProductID(int tl_id)
    static NAN_METHOD(GetToolProductID);

    //double GetToolRadiusLower(int ws_id)
    static NAN_METHOD(GetToolRadiusLower);

    //string GetToolRadiusLowerReason(int ws_id)
    static NAN_METHOD(GetToolRadiusLowerReason);

    //double GetToolRadiusUpper(int ws_id)
    static NAN_METHOD(GetToolRadiusUpper);

    //string GetToolRadiusUpperReason(int ws_id)
    static NAN_METHOD(GetToolRadiusUpperReason);

    //string GetToolReferenceDataName(int ws_id)
    static NAN_METHOD(GetToolReferenceDataName);

    //int GetToolUsingNumber(string id)
    static NAN_METHOD(GetToolUsingNumber);

    //string GetToolType (int ws_id)
    static NAN_METHOD(GetToolType);

    //int GetToolWorkpiece (int e_id)
    static NAN_METHOD(GetToolWorkpiece);

    //int GetWorkingstep(int wp_id, int index)
    static NAN_METHOD(GetWorkingstep);

    //string GetWorkingstepName(int ws_id)
    static NAN_METHOD(GetWorkingstepName);

    //int GetWorkingstepTool(int ws_id)
    static NAN_METHOD(GetWorkingstepTool);

    //int[] GetWorkpieceAll()
    static NAN_METHOD(GetWorkpieceAll);

    //int GetWorkpieceAsIsOfMain()
    static NAN_METHOD(GetWorkpieceAsIsOfMain);

    //int[] GetWorkpieceImmediateSubAssemblyAll
    static NAN_METHOD(GetWorkpieceImmediateSubAssemblyAll);

    //int[] GetWorkpieceSubAssemblyAll
    static NAN_METHOD(GetWorkpieceSubAssemblyAll);

    //int GetWorkpieceToBeOfMain()
    static NAN_METHOD(GetWorkpieceToBeOfMain);

    //int GetWorkpieceDeltaOfMain()
    static NAN_METHOD(GetWorkpieceDeltaOfMain);

    //int GetWorkpieceFixtureOfMain()
    static NAN_METHOD(GetWorkpieceFixtureOfMain);

    //string GetWorkpieceName(int wp_id)
    static NAN_METHOD(GetWorkpieceName);

    //string GetWorkpieceType(int wp_id)
    static NAN_METHOD(GetWorkpieceType);

    //string GetWorkpieceUnits(int wp_id)
    static NAN_METHOD(GetWorkpieceUnits);

    //int[] GetWorkplanExecutableAll(int wp_id);
    static NAN_METHOD(GetWorkplanExecutableAll);

    //int[] GetWorkplanExecutableAllEnabled(int wp_id);
    static NAN_METHOD(GetWorkplanExecutableAllEnabled);

    //string GetWorkplanName();
    static NAN_METHOD(GetWorkplanName);

    //int GetWorkplanProcessFeatureCount();
    static NAN_METHOD(GetWorkplanProcessFeatureCount);

    //int GetWorkplanProcessFeatureNext();
    static NAN_METHOD(GetWorkplanProcessFeatureNext);

    //int GetWorkplanSize();
    static NAN_METHOD(GetWorkplanSize);

    //New Function for NodeJS using getworkplantoolcount and getworkplantoolall
    static NAN_METHOD(GetWorkplanToolAll);

    //int GetWorkplanToolCount();
    static NAN_METHOD(GetWorkplanToolCount);

    //int GetWorkplanToolNext();
    static NAN_METHOD(GetWorkplanToolNext);

    //void Open238(String file_name);
    static NAN_METHOD(OpenProject);

    //void SaveAsModules(v8::String file_name);
    static NAN_METHOD(SaveAsModules);

    //void SaveAsP21(v8::String file_name);
    static NAN_METHOD(SaveAsP21);
};

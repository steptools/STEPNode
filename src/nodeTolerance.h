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
// Author: Samson Bonfante (bonfante@steptools.com)
//

#pragma once
#include <nan.h>
#include <stncapt/Tolerance.h>
#include "nodeAptStepMaker.h"
#include <stncapt/message.h>
class Tolerance : public Nan::ObjectWrap {
private:
    static Tolerance* _singleton;
    tolerance * _tol;
    static NAN_METHOD(New);
    static inline Nan::Persistent<v8::Function> & constructor() {
	static Nan::Persistent<v8::Function> my_constructor;
	return my_constructor;
    }
    ~Tolerance() { delete _tol; };
    Tolerance() { 
        report_via_printf();
        _tol = new tolerance(AptStepMaker::getApt());

    };
public:
    static NAN_MODULE_INIT(Init);

    //int[] GetDatumFaceAll()
    static NAN_METHOD(GetDatumFaceAll);

    //char * GetDatumLabel()
    static NAN_METHOD(GetDatumLabel);

    // string GetFaceMeasureGeometryType(int face_id)
    static NAN_METHOD(GetFaceMeasureGeometryType);

    //string[] GetProbeResults()
    static NAN_METHOD(GetProbeResults);

    //int GetToleranceAllCount()
    static NAN_METHOD(GetToleranceAllCount);

    //int GetToleranceAllNext(int index)
    static NAN_METHOD(GetToleranceAllNext);

    //New Function for NodeJS using GetToleranceAllCount and GetToleranceAllNext
    static NAN_METHOD(GetToleranceAll);

    //char *[] GetToleranceDatumAll(int id)
    static NAN_METHOD(GetToleranceDatumAll);

    // int[] GetToleranceFaceAll()
    static NAN_METHOD(GetToleranceFaceAll);

    // char[] GetToleranceModifierAll()
    static NAN_METHOD(GetToleranceModifierAll);

    // bool GetTolerancePlusMinus(int TolId)
    static NAN_METHOD(GetTolerancePlusMinus);

    // string GetToleranceStatus(int TolId)
    static NAN_METHOD(GetToleranceStatus); //TODO: IMPLEMENT ME tolerance_status (int tol_id, const char * &grade);

    //string GetToleranceType(int TolId)
    static NAN_METHOD(GetToleranceType);

    //string GetToleranceUnit(int TolId)
    static NAN_METHOD(GetToleranceUnit);

    //double GetToleranceValue(int TolId)
    static NAN_METHOD(GetToleranceValue);

    //int[] GetWorkingstepToleranceAll(int ws)
    static NAN_METHOD(GetWorkingstepToleranceAll);

    //int GetWorkpieceOfTolerance(int wp_id)
    static NAN_METHOD(GetWorkpieceOfTolerance);

    //int[] GetWorkpieceToleranceAll(int wp_id)
    static NAN_METHOD(GetWorkpieceToleranceAll);

    //int[] GetWorkpieceDatumAllAll(int dat_id)
    static NAN_METHOD(GetWorkpieceDatumAllAll);

	//int[] NavigateToleranceToWorkingstepAll(int TolId)
	static NAN_METHOD(NavigateToleranceToWorkingstepAll);

    //void ResetAllToleranceMeasuredValue()
    static NAN_METHOD(ResetAllToleranceMeasuredValue);

    //void SetToleranceMeasuredValue(string tolUUID, double val)
    static NAN_METHOD(SetToleranceMeasuredValue);

    /*void WorkpiecePlacementUsingFaces(
        int wp_id,
        int face1a_id,
        int face1b_id,
        int face1c_id,
        int face2a_id,
        int face2b_id,
        int face2c_id
    )*/
    static NAN_METHOD(WorkpiecePlacementUsingFaces);

    /*void WorkplanSetupPlacementUsingFaces(
        int plan_id,
        int faceA_id,
        int faceB_id,
        int faceC_id
    )*/
    static NAN_METHOD(WorkplanSetupPlacementUsingFaces);
};

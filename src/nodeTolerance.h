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
#include <stncapt/Tolerance.h>
#include "nodeAptStepMaker.h"

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
    Tolerance() { _tol = new tolerance(AptStepMaker::getApt()); };
public:
    static NAN_MODULE_INIT(Init);

    //int GetToleranceAllCount()
    static NAN_METHOD(GetToleranceAllCount);

    //int GetToleranceAllNext(int index)
    static NAN_METHOD(GetToleranceAllNext);

    //New Function for NodeJS using GetToleranceAllCount and GetToleranceAllNext
    static NAN_METHOD(GetToleranceAll);

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
};

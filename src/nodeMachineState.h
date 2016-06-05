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
#include <stncapt/MachineState.h>

class machineState : public Nan::ObjectWrap {
private:
    MachineState * _ms;
    //var ms = new StepNC.machineState(string file);
    static NAN_METHOD(New);
    static inline Nan::Persistent<v8::Function> & constructor() {
	    static Nan::Persistent<v8::Function> my_constructor;
	    return my_constructor;
    }
    ~machineState() {};
public:
    static NAN_MODULE_INIT(Init);

    //Load a machine model from a file. 
    //void LoadMachine(string file);
    static NAN_METHOD(LoadMachine);
    
    //void nextWS();
    static NAN_METHOD(NextWS);
    
    //int AdvanceState();
    static NAN_METHOD(AdvanceState);

    //String GetGeometryJSON() //Get all Geometry
    //String GetGeometryJSON(string id,string typ) //Get a specific piece of geometry data. types are "NONE" "MESH" and "POLYLINE"
    static NAN_METHOD(GetGeometryJSON);
    //String GetDeltaJSON(); //Get changed geometry
    static NAN_METHOD(GetDeltaJSON);
    //String GetKeystateJSON(); //Get All keyframe geometry.
    static NAN_METHOD(GetKeystateJSON);
};



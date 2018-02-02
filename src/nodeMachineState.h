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

#pragma once
#include <nan.h>
#include <stncapt/MachineState.h>
#include <stncapt/message.h>
#include <uv.h>
class machineState : public Nan::ObjectWrap {
private:
    MachineState * _ms;
    //var ms = new StepNC.machineState(string file);
    static NAN_METHOD(New);
    static inline Nan::Persistent<v8::Function> & constructor() {
        report_via_printf();
	static Nan::Persistent<v8::Function> my_constructor;
	return my_constructor;
    }
    // initialize and clean up private data
    machineState() { _ms=0; }
    ~machineState() { delete _ms; };
    uv_async_t async;
    uv_thread_t waitqueue;
    uv_thread_t resetthread;
	bool BCMode = false;
public:
    void Wait();
	void ToleranceResetThread(Nan::Global<v8::Promise::Resolver>* promiseContainer);
    static NAN_MODULE_INIT(Init);

    //void WorkingstepTransitionDisableToolMove();
    static NAN_METHOD(WorkingstepTransitionDisableToolMove);

    //void nextWS();
    static NAN_METHOD(NextWS);

    //void PrevWS();
    static NAN_METHOD(PrevWS);

    //int AdvanceState();
    static NAN_METHOD(AdvanceState);

    //int AdvanceStateByT(double t);
    static NAN_METHOD(AdvanceStateByT);

    //int switchWS(int wsid)
    static NAN_METHOD(GoToWS);

    //int GetEIDfromUUID(int uuid);
    static NAN_METHOD(GetEIDfromUUID);

    //String GetGeometryJSON(string id) //Get a specific piece of geometry data.
    static NAN_METHOD(GetGeometryJSON);
    //String GetDynamicGeometryJSON(unsigned prev); //Get the geometry associated with the inprocess geometry.
    static NAN_METHOD(GetDynamicGeometryJSON);
    //void WriteDynamicGeometrySTEP(string fname); //Save a STEP file containing the geometry associated with the inprocess geometry.
    static NAN_METHOD(WriteDynamicGeometrySTEP);
    //int GetDynamicGeometryVersion();
    static NAN_METHOD(GetDynamicGeometryVersion);
    //void ResetDynamicGeometry(); //Reset the inprocess geometry.
    static NAN_METHOD(ResetDynamicGeometry);

    //Get the geometry associated with the inprocess geometry, 
    //with a 'heatmap' showing how close the facets are to tolerance on the to-be.
    //String GetToleranceGeometryJSON(); 
    static NAN_METHOD(GetToleranceGeometryJSON);
    //void ResetToleranceGeometry(); //Call to instantiate the Tolerance Geometry (for above function)
    static NAN_METHOD(ResetToleranceGeometry);
    
    //String GetDeltaStateJSON(); //Get changed geometry
    static NAN_METHOD(GetDeltaStateJSON);
    //String GetKeyStateJSON(); //Get All keyframe geometry.
    static NAN_METHOD(GetKeyStateJSON);

    //int GetPrevWSID()
    static NAN_METHOD(GetPrevWSID);

    //int GetWSID()
    static NAN_METHOD(GetWSID);

    //int GetNextWSID
    static NAN_METHOD(GetNextWSID);

    //0xRRGGBB GetWSColor(int wsid)
    static NAN_METHOD(GetWSColor);
    
    //0xRRGGBB GetCurrentWSColor(int wsid)
    static NAN_METHOD(GetCurrentWSColor);

    //double GetCurrentFeedrate
    static NAN_METHOD(GetCurrentFeedrate);

    //double GetCurrentSpindleSpeed
    static NAN_METHOD(GetCurrentSpindleSpeed);

    //void SetDumpDir(string dir)
    static NAN_METHOD(SetDumpDir);

    // void SetToolPosition(double x,double y,double z,double i,double j,double k);
    // void SetToolPosition(double x,double y,double z,double a(b),double c);
    static NAN_METHOD(SetToolPosition);

	// If true then SetToolPosition will act as BC machine instead of AC machine
	// void SetBCMode(bool en);
	static NAN_METHOD(SetBCMode);

    // void Update();
    //If the workingsteps are manipulated (E.G. selective enabled/disabled)
    //We need to call this update to fix the MachineState's WS cache.
    static NAN_METHOD(Update);
};



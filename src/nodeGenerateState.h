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
// Author: David Loffredo (loffredo@steptools.com)
//


#pragma once

#include <nan.h>

class StixCtlGenerateState;

class GenerateState : public Nan::ObjectWrap {
private:
    StixCtlGenerateState * f_vars;
    static NAN_METHOD(New);

    static inline Nan::Persistent<v8::Function> & constructor() {
	static Nan::Persistent<v8::Function> my_constructor;
	return my_constructor;
    }
    // initialize and clean up private data
    GenerateState();
    ~GenerateState();

public:
    StixCtlGenerateState * asUnmanaged() { return f_vars; }

    static NAN_MODULE_INIT(Init);

    //void Reset();
    static NAN_METHOD(Reset);

    // double GetXpos();
    // double GetYpos();
    // double GetZpos();
    // double[3] GetXYZpos();
    static NAN_METHOD(GetXpos);
    static NAN_METHOD(GetYpos);
    static NAN_METHOD(GetZpos);
    static NAN_METHOD(GetXYZpos);

    // void SetXpos (double s);
    // void SetYpos (double s);
    // void SetZpos (double s);
    // void SetXYZpos (double x, double y, double z);
    static NAN_METHOD(SetXpos);
    static NAN_METHOD(SetYpos);
    static NAN_METHOD(SetZpos);
    static NAN_METHOD(SetXYZpos);

    // bool IsChangedXYZpos (double x, double y, double z);
    // bool IsUnknownXYZpos();
    static NAN_METHOD(IsChangedXYZpos);
    static NAN_METHOD(IsUnknownXYZpos);

    // double GetIpos();
    // double GetJpos();
    // double GetKpos();
    // double[3] GetIJKpos();
    static NAN_METHOD(GetIpos);
    static NAN_METHOD(GetJpos);
    static NAN_METHOD(GetKpos);
    static NAN_METHOD(GetIJKpos);


    // void SetIpos (double s);
    // void SetJpos (double s);
    // void SetKpos (double s);
    // void SetIJKpos (double i, double j, double k);
    static NAN_METHOD(SetIpos);
    static NAN_METHOD(SetJpos);
    static NAN_METHOD(SetKpos);
    static NAN_METHOD(SetIJKpos);


    // bool IsChangedIJKpos (double i, double j, double k);
    // bool IsChangedIJKposAssume3axis(double i, double j, double k);
    // bool IsUnknownIJKpos();
    static NAN_METHOD(IsChangedIJKpos);
    static NAN_METHOD(IsChangedIJKposAssume3axis);
    static NAN_METHOD(IsUnknownIJKpos);


    // double GetApos();
    // double GetBpos();
    // double GetCpos();
    static NAN_METHOD(GetApos);
    static NAN_METHOD(GetBpos);
    static NAN_METHOD(GetCpos);

    // void SetApos (double s);
    // void SetBpos (double s);
    // void SetCpos (double s);
    static NAN_METHOD(SetApos);
    static NAN_METHOD(SetBpos);
    static NAN_METHOD(SetCpos);



    // double GetFeed();
    // void SetFeed (double s);
    static NAN_METHOD(GetFeed);
    static NAN_METHOD(SetFeed);

    // double GetSpindle();
    // void SetSpindle (double s);
    static NAN_METHOD(GetSpindle);
    static NAN_METHOD(SetSpindle);

    // bool GetCoolant();
    // void SetCoolant (bool yn);
    static NAN_METHOD(GetCoolant);
    static NAN_METHOD(SetCoolant);


    // bool GetCoolantMist();
    // void SetCoolantMist (bool yn);
    static NAN_METHOD(GetCoolantMist);
    static NAN_METHOD(SetCoolantMist);

    // bool GetCoolantThru();
    // void SetCoolantThru (bool yn);
    static NAN_METHOD(GetCoolantThru);
    static NAN_METHOD(SetCoolantThru);

    // int GetMovemode();
    // void SetMovemode (int m);
    static NAN_METHOD(GetMovemode);
    static NAN_METHOD(SetMovemode);

    // void ClearPosition();
    static NAN_METHOD(ClearPosition);

    // void ClearFeed();
    static NAN_METHOD(ClearFeed);

    // void ClearSpindle();
    static NAN_METHOD(ClearSpindle);

    // void ClearCoolant();
    static NAN_METHOD(ClearCoolant);

    // void ClearMovemode();
    static NAN_METHOD(ClearMovemode);

    // void ClearRefpoint();
    static NAN_METHOD(ClearRefpoint);

    // bool IsRefpointCenter();
    // bool IsRefpointContact();
    static NAN_METHOD(IsRefpointCenter);
    static NAN_METHOD(IsRefpointContact);

    // void SetRefpointCenter();
    // void SetRefpointContact();
    static NAN_METHOD(SetRefpointCenter);
    static NAN_METHOD(SetRefpointContact);

    // bool IsRefpointLeft();
    // bool IsRefpointRight();
    static NAN_METHOD(IsRefpointLeft);
    static NAN_METHOD(IsRefpointRight);

    // void SetRefpointLeft();
    // void SetRefpointRight();
    static NAN_METHOD(SetRefpointLeft);
    static NAN_METHOD(SetRefpointRight);

    // int GetNextBlocknum();
    // int GetLastBlocknum();
    // void SetBlocknum(int num);
    static NAN_METHOD(GetNextBlocknum);
    static NAN_METHOD(GetLastBlocknum);
    static NAN_METHOD(SetBlocknum);

    // // prefix codes for next move, many can be added
    // string GetMovePrefix();
    static NAN_METHOD(GetMovePrefix);
    // void AddMovePrefix (string f);
    static NAN_METHOD(AddMovePrefix);
    // void ClearMovePrefix();
    static NAN_METHOD(ClearMovePrefix);



    // // comments for next move, many can be added
    // string GetMoveComment();
    static NAN_METHOD(GetMoveComment);
    // void AddMoveComment (string f);
    static NAN_METHOD(AddMoveComment);
    // void ClearMoveComment();
    static NAN_METHOD(ClearMoveComment);

    // void SetProgramStats(Adaptive ctl);
    static NAN_METHOD(SetProgramStats);

    // void ClearProgramStats();
    static NAN_METHOD(ClearProgramStats);

    // bool GetProgramHas5axis();
    // void SetProgramHas5axis(bool yn);
    static NAN_METHOD(GetProgramHas5axis);
    static NAN_METHOD(SetProgramHas5axis);

    // bool GetProgramHasProbes();
    static NAN_METHOD(GetProgramHasProbes);
    // int GetProbeCount();
    static NAN_METHOD(GetProbeCount);
    // void SetProbeCount(int d);
    static NAN_METHOD(SetProbeCount);


    // int GetProbeIndex();
    static NAN_METHOD(GetProbeIndex);
    // int GetNextProbeIndex();
    static NAN_METHOD(GetNextProbeIndex);
    // void SetProbeIndex(int d);
    static NAN_METHOD(SetProbeIndex);


    // int GetOtherObj(string nm);
    static NAN_METHOD(GetOtherObj);
    // void SetOtherObj(string nm, int id);
    static NAN_METHOD(SetOtherObj);
};

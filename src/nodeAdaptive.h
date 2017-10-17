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
// Author: David Loffredo (loffredo@steptools.com)
//


#pragma once

#include <nan.h>

class StixCtlCursor;

class Adaptive : public Nan::ObjectWrap {
private:
    StixCtlCursor * f_ctl;
    static NAN_METHOD(New);

    static inline Nan::Persistent<v8::Function> & constructor() {
	static Nan::Persistent<v8::Function> my_constructor;
	return my_constructor;
    }
    // initialize and clean up private data
    Adaptive();
    ~Adaptive();

public:
    static NAN_MODULE_INIT(Init);

    //void Reset();
    static NAN_METHOD(Reset);

    // void StartProject();	// use finder design
    static NAN_METHOD(StartProject);

    // do entire project or specific item
    // void StartExec(long mpe);
    static NAN_METHOD(StartExec);

    // When true, the cursor visits all executables reachable from the
    // starting object, including all members of a selective and any
    // exec that is disabled by use of the "enabled" flag.
    //
    // When false (the default) the cursor skips executables that are
    // disabled by use of the "enabled" flag.  It only visits a single
    // member of a selective - it will pick one if multiple elements
    // are enabled.
    //
    // void SetVisitAllExecs(bool yn);
    static NAN_METHOD(SetVisitAllExecs);
    // bool GetVisitAllExecs();
    static NAN_METHOD(GetVisitAllExecs);


    // long GetActiveProject();
    static NAN_METHOD(GetActiveProject);
    // long GetActiveExec();
    static NAN_METHOD(GetActiveExec);
    // long GetActiveWorkplan();
    static NAN_METHOD(GetActiveWorkplan);
    // long GetActiveWorkingstep();
    static NAN_METHOD(GetActiveWorkingstep);
    // long GetActiveOperation();
    static NAN_METHOD(GetActiveOperation);
    // long GetActiveToolpath();
    static NAN_METHOD(GetActiveToolpath);
    // long GetActiveTool();
    static NAN_METHOD(GetActiveTool);
    // long GetActiveTech();
    static NAN_METHOD(GetActiveTech);
    // long GetActiveMfun();
    static NAN_METHOD(GetActiveMfun);

    // Values from the top of the process stack.
    // long GetActiveObj();
    static NAN_METHOD(GetActiveObj);
    // long GetActiveAux (long num);
    static NAN_METHOD(GetActiveAux);
    // double GetActiveParam();
    static NAN_METHOD(GetActiveParam);

    // CtlType GetActiveType();
    static NAN_METHOD(GetActiveType);
    // CtlStatus GetActiveStatus();
    static NAN_METHOD(GetActiveStatus);

    // double[16] GetActiveXform();
    static NAN_METHOD(GetActiveXform);

    // RoseUnit GetActiveLenUnit();
    static NAN_METHOD(GetActiveLenUnit);
    // RoseUnit GetActiveAngUnit();
    static NAN_METHOD(GetActiveAngUnit);

    // CtlPos GetActivePos(CtlPosType t, CtlCsys cs);
    static NAN_METHOD(GetActivePos);

    // // Final position in last move event, in WCS
    // CtlPos GetLastPos();
    static NAN_METHOD(GetLastPos);
    // CtlPos GetLastRawPos();
    static NAN_METHOD(GetLastRawPos);

    // returns zero to signal end of process, nonzero otherwise
    // CtlEvent Next();
    static NAN_METHOD(Next);
    // CtlEvent Event();
    static NAN_METHOD(Event);

    // message if in error event
    // string ErrorMsg();
    static NAN_METHOD(ErrorMsg);

    // --------------------
    // EVENTS - The cursor defaults to MOVE events, but you can reset
    // and change the events.  The events are integer values given by
    // the fields of the CtlEvent object
    //
    // void SetWantedAll(bool val);
    static NAN_METHOD(SetWantedAll);

    // void SetWanted(CtlEvent e, bool val);
    // void SetWanted(CtlEvent e) { SetWanted(e, true); }
    static NAN_METHOD(SetWanted);

    // bool GetWanted(CtlEvent e);
    static NAN_METHOD(GetWanted);

    // --------------------
    // POSITIONS -
    //
    // CtlPos GetMoveStart (CtlCsys cs);
    // CtlPos GetMoveStart() { return GetMoveStart(CtlCsys::WCS); }
    static NAN_METHOD(GetMoveStart);

    // CtlPos GetMoveEnd (CtlCsys cs);
    // CtlPos GetMoveEnd() { return GetMoveEnd(CtlCsys::WCS); }
    static NAN_METHOD(GetMoveEnd);

    // CtlPos GetMoveArc (CtlCsys cs);
    // CtlPos GetMoveArc() { return GetMoveArc(CtlCsys::WCS); }
    static NAN_METHOD(GetMoveArc);

    // // process parameters
    // double GetMoveFeed (RoseUnit u);
    // double GetMoveFeed() { return GetMoveFeed(RoseUnit::as_is); }
    static NAN_METHOD(GetMoveFeed);
    // double GetMoveSpindle (RoseUnit u);
    // double GetMoveSpindle() { return GetMoveSpindle(RoseUnit::as_is); }
    static NAN_METHOD(GetMoveSpindle);

    // RoseUnit GetMoveFeedUnit();
    static NAN_METHOD(GetMoveFeedUnit);
    // RoseUnit GetMoveSpindleUnit();
    static NAN_METHOD(GetMoveSpindleUnit);

    // bool GetMoveIsRapid();
    static NAN_METHOD(GetMoveIsRapid);
    // bool GetMoveIsCoolant();
    static NAN_METHOD(GetMoveIsCoolant);
    // bool GetMoveIsMistCoolant();
    static NAN_METHOD(GetMoveIsMistCoolant);
    // bool GetMoveIsThruCoolant();
    static NAN_METHOD(GetMoveIsThruCoolant);

    // Components of a position.  The Get functions return undefined
    // if the value is null.
    // double[3] GetPosXYZ(CtlPos p, optional RoseUnit u);
    static NAN_METHOD(GetPosXYZ);

    // double[3] GetPosDirZ(CtlPos p);
    static NAN_METHOD(GetPosDirZ);

    // double[3] GetPosDirX(CtlPos p);
    static NAN_METHOD(GetPosDirX);

    // double[3] GetPosDirSnorm(CtlPos p);
    static NAN_METHOD(GetPosDirSnorm);
    
    // DIRECTION OF MOTION - the travel direction is used with the
    // surface normal direction to know if the tool will contact on
    // the left or right.
    // double[3] GetPosDirMove(CtlPos p);
    static NAN_METHOD(GetPosDirMove);

    // double GetPosSpeedRatio (CtlPos p);
    static NAN_METHOD(GetPosSpeedRatio);


    // only one version of this.  Pass in AS is to Get data units
    // object GetPosXsectParms(	CtlPos p, RoseUnit u );
    static NAN_METHOD(GetPosXsectParms);


    // STEP objects can be associated with a position
    // long GetPosXYZObj(CtlPos p);
    static NAN_METHOD(GetPosXYZObj);
    // long GetPosDirZObj(CtlPos p);
    static NAN_METHOD(GetPosDirZObj);
    // long GetPosDirXObj(CtlPos p);
    static NAN_METHOD(GetPosDirXObj);
    // long GetPosDirSnormObj(CtlPos p);
    static NAN_METHOD(GetPosDirSnormObj);
    // long GetPosSpeedRatioObj(CtlPos p);
    static NAN_METHOD(GetPosSpeedRatioObj);
    // long GetPosXsectObj(CtlPos p);
    static NAN_METHOD(GetPosXsectObj);

    // RoseUnit GetPosLenUnit(CtlPos p);
    static NAN_METHOD(GetPosLenUnit);
    // RoseUnit GetPosAngUnit(CtlPos p);
    static NAN_METHOD(GetPosAngUnit);

    // CtlCsys GetPosCsys(CtlPos p);
    static NAN_METHOD(GetPosCsys);
    // int GetPosType(CtlPos p);
    static NAN_METHOD(GetPosType);

    // double GetPosParam(CtlPos p);
    static NAN_METHOD(GetPosParam);
    // void SetPosParam(CtlPos p, double val);
    static NAN_METHOD(SetPosParam);

    // compare two positions to see if they are equal.  Only compares
    // the position, zdir and xdir.
    // bool GetPosIsEqual (CtlPos p1, CtlPos p2);
    static NAN_METHOD(GetPosIsEqual);

    // Arc parameters - Use with the GetMoveArc() position to Get
    // curve parameters.
    // double[3] GetArcCenter (CtlPos p, RoseUnit u);
    static NAN_METHOD(GetArcCenter);
    // double[3] GetArcAxis (CtlPos p);
    static NAN_METHOD(GetArcAxis);

    // double GetArcRadius  (CtlPos p, RoseUnit u);
    static NAN_METHOD(GetArcRadius);
    // double GetArcAngle  (CtlPos p, RoseUnit u);
    static NAN_METHOD(GetArcAngle);
    // double GetArcHeight  (CtlPos p, RoseUnit u);
    static NAN_METHOD(GetArcHeight);

    // bool GetArcIsCW  (CtlPos p);
    static NAN_METHOD(GetArcIsCW);
    // bool GetArcIsOver180  (CtlPos p);
    static NAN_METHOD(GetArcIsOver180);
    // bool GetArcIsFullCircle  (CtlPos p);
    static NAN_METHOD(GetArcIsFullCircle);

    //--------------------
    // PROCESS STACK FRAMES - Get values for a specific position on
    // the process stack
    //
    // long GetStackSize();
    static NAN_METHOD(GetStackSize);
		      
    // long GetFrameObj (long stack_pos);
    static NAN_METHOD(GetFrameObj);
    // long GetFrameAux (long stack_pos, long num);
    static NAN_METHOD(GetFrameAux);
		      
    // double GetFrameParam (long stack_pos);
    static NAN_METHOD(GetFrameParam);
    // CtlType GetFrameType (long stack_pos);
    static NAN_METHOD(GetFrameType);
    // CtlStatus GetFrameStatus (long stack_pos);
    static NAN_METHOD(GetFrameStatus);
    // double[16] GetFrameXform (long stack_pos);
    static NAN_METHOD(GetFrameXform);
    // RoseUnit GetFrameLenUnit (long stack_pos);
    static NAN_METHOD(GetFrameLenUnit);
    // RoseUnit GetFrameAngUnit (long stack_pos);
    static NAN_METHOD(GetFrameAngUnit);
    // // position information
    // CtlPos GetFramePos(long stack_pos, CtlPosType t, CtlCsys cs);
    static NAN_METHOD(GetFramePos);
    // long GetFrameTech (long stack_pos);
    static NAN_METHOD(GetFrameTech);
    // long GetFrameMfun (long stack_pos);
    static NAN_METHOD(GetFrameMfun);
};

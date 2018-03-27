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

class StixCtlGenerate;

class Generate : public Nan::ObjectWrap {
private:
    StixCtlGenerate * f_fmt;
    static NAN_METHOD(New);

    static inline Nan::Persistent<v8::Function> & constructor() {
	static Nan::Persistent<v8::Function> my_constructor;
	return my_constructor;
    }
    // initialize and clean up private data
    Generate();
    ~Generate();

public:
    StixCtlGenerate * asUnmanaged() { return f_fmt; }

    static NAN_MODULE_INIT(Init);

    //void Reset();
    static NAN_METHOD(Reset);

    // configure for a built-in style
    // bool SetStyle (string name);
    static NAN_METHOD(SetStyle);

    // Data Formatting Functions
    // string FormatEvent (GenerateState vars, Adaptive cursor);
    // string FormatType (GenerateState vars, Adaptive cursor);
    // string FormatOther (GenerateState vars, Adaptive cursor, string name);
    static NAN_METHOD(FormatEvent);
    static NAN_METHOD(FormatType);
    static NAN_METHOD(FormatOther);

    // String Formatting Functions
    // string FormatBlock(GenerateState, string str);
    // string FormatBlockNonum(GenerateState, string str);
    // string FormatComment(GenerateState, string str);
    // string FormatComment(GenerateState, string header, string str);
    static NAN_METHOD(FormatBlock);
    static NAN_METHOD(FormatBlockNonum);
    static NAN_METHOD(FormatComment);
	
    // Move to an arbitrary XYZ/IJK position in the program units.
    // string FormatMoveXYZ (GenerateState, Adaptive, double x,y,z);
    // string FormatMoveXYZ_IJK (GenerateState, Adaptive, double x,y,z, i,j,k);
    // string FormatRapidXYZ (GenerateState, Adaptive, double x, y, z);
    // string FormatRapidXYZ_IJK (GenerateState, Adaptive, double x,y,z, i,j,k);
    static NAN_METHOD(FormatMoveXYZ);
    static NAN_METHOD(FormatMoveXYZ_IJK);
    static NAN_METHOD(FormatRapidXYZ);
    static NAN_METHOD(FormatRapidXYZ_IJK);

    // --------------------
    // STRING BUILDING AND NUMBER HANDLING -- 
    //
    // string CatSpace (string s); 
    // string CatRequiredSpace (string s);
    static NAN_METHOD(CatSpace);
    static NAN_METHOD(CatRequiredSpace);

    // string CatNumber(string s, double num);
    // string CatNumber(string s, double num, int max_digits, int min_digits);
    static NAN_METHOD(CatNumber);

    // string CatParam(string s, string param);
    // string CatParam(string s, string param, double num);
    // string CatParam(string s, string param, double num, int max, min_digits);
    static NAN_METHOD(CatParam);

    // bool IsFormattedNumber(double num1, double num2);
    // bool IsFormattedNumber(double num1, double num2, int max_digits);
    static NAN_METHOD(IsFormattedNumber);

    // bool IsFormattedXYZ(double x1, y1, z1, double x2, y2, z2);
    // bool IsFormattedIJK(double i1, j1, k1, double i2, j2, k2);
    static NAN_METHOD(IsFormattedXYZ);
    static NAN_METHOD(IsFormattedIJK);
	

    // ------------------------------
    // Get transformed positions and directions

    // double[3] GetOutXYZ(Adaptive, CtlPos p, RoseUnit u = as_is);
    static NAN_METHOD(GetOutXYZ);
    // double[3] GetOutDirZ(Adaptive, CtlPos p);
    static NAN_METHOD(GetOutDirZ);
    // double[3] GetOutDirX(Adaptive, CtlPos p);
    static NAN_METHOD(GetOutDirX);
    // double[3] GetOutDirSnorm(Adaptive, CtlPos p);
    static NAN_METHOD(GetOutDirSnorm);
    // double[3] GetOutDirMove(Adaptive, CtlPos p);
    static NAN_METHOD(GetOutDirMove);
    // double[3] GetOutArcCenter(Adaptive, CtlPos p, RoseUnit u = as_is);
    static NAN_METHOD(GetOutArcCenter);
    // double[3] GetOutArcAxis(Adaptive, CtlPos p);
    static NAN_METHOD(GetOutArcAxis);

    // double[3] GetOutXformedPoint (double in_x, double in_y, double in_z);
    // double[3] GetOutXformedDir(double in_i, double in_j, double in_k);
    static NAN_METHOD(GetOutXformedPoint);
    static NAN_METHOD(GetOutXformedDir);
	
    // --------------------
    // Formatting Customization Parameters
    // enum class TraceComments {
    // 	none = 0,
    // 	workplan = 1,	// before each workplan
    // 	workingstep = 2,	// before each workingstep
    // 	toolpath = 3,	// before each toolpath
    // 	point = 4, 	// at each point.
    // 	all = 5 		// all possible comments.
    // };

    // TraceComments GetTraceComments();
    // void SetTraceComments (TraceComments t);
    static NAN_METHOD(GetTraceComments);
    static NAN_METHOD(SetTraceComments);

    // string  GetFileExt();
    // void SetFileExt (string s);
    static NAN_METHOD(GetFileExt);
    static NAN_METHOD(SetFileExt);

    // int GetDigits();
    // void SetDigits (int d);
    // int GetMinDigits();
    // void SetMinDigits (int d); 
    static NAN_METHOD(GetDigits);
    static NAN_METHOD(SetDigits);
    static NAN_METHOD(GetMinDigits);
    static NAN_METHOD(SetMinDigits);

    // int GetSpindleDigits();
    // void SetSpindleDigits (int d);
    // int GetSpindleMinDigits();
    // void SetSpindleMinDigits (int d);
    static NAN_METHOD(GetSpindleDigits);
    static NAN_METHOD(SetSpindleDigits);
    static NAN_METHOD(GetSpindleMinDigits);
    static NAN_METHOD(SetSpindleMinDigits);

    // int GetFeedDigits();
    // void SetFeedDigits (int d);
    // int GetFeedMinDigits();
    // void SetFeedMinDigits (int d);
    static NAN_METHOD(GetFeedDigits);
    static NAN_METHOD(SetFeedDigits);
    static NAN_METHOD(GetFeedMinDigits);
    static NAN_METHOD(SetFeedMinDigits);

    // bool GetUseXform();
    // void SetUseXform(bool yn);
    static NAN_METHOD(GetUseXform);
    static NAN_METHOD(SetUseXform);

    // double[16] GetDstXform();
    // void SetDstXform(double[16]);
    static NAN_METHOD(GetDstXform);
    static NAN_METHOD(SetDstXform);

    // bool GetDstXformIsLeft();
    static NAN_METHOD(GetDstXformIsLeft);

    // int GetProgramNumber();
    // void SetProgramNumber (int d);
    static NAN_METHOD(GetProgramNumber);
    static NAN_METHOD(SetProgramNumber);

    // Preferred length unit to use when generating code.
    // RoseUnit GetProgramUnit();
    // void SetProgramUnit (RoseUnit u);
    static NAN_METHOD(GetProgramUnit);
    static NAN_METHOD(SetProgramUnit);


    // unit system to match the program unit or in the case of
    // as-is, to match the toolpath units used by the stepnc
    // process.
    // void SetUnitSystem(Adaptive ctl);
    static NAN_METHOD(SetUnitSystem);

    // RoseUnit GetLenUnit();
    // void SetLenUnit(RoseUnit u);
    static NAN_METHOD(GetLenUnit);
    static NAN_METHOD(SetLenUnit);

    // RoseUnit GetFeedUnit();
    // void SetFeedUnit(RoseUnit u);
    static NAN_METHOD(GetFeedUnit);
    static NAN_METHOD(SetFeedUnit);

    // RoseUnit GetSpindleUnit();
    // void SetSpindleUnit(RoseUnit u);
    static NAN_METHOD(GetSpindleUnit);
    static NAN_METHOD(SetSpindleUnit);


    // Preferred work offset frame to use when generating code.
    // Offset -1 means "as-is", do not change any offset settings.
    // Offset 0 is treated as no work offset, 1 is the first on the
    // machine, and so on.
    // int GetWorkOffsetFrame();
    // void SetWorkOffsetFrame (int d);
    static NAN_METHOD(GetWorkOffsetFrame);
    static NAN_METHOD(SetWorkOffsetFrame);

    // void SetFeedStandalone();
    // void SetFeedInline();
    // bool GetFeedIsStandalone();
    static NAN_METHOD(SetFeedStandalone);
    static NAN_METHOD(SetFeedInline);
    static NAN_METHOD(GetFeedIsStandalone);


    // /* Do an optional stop after every workingstep */
    // bool GetStopAfterWorkingstep();
    // void SetStopAfterWorkingstep (bool yn);
    static NAN_METHOD(GetStopAfterWorkingstep);
    static NAN_METHOD(SetStopAfterWorkingstep);

    // /* supress mention of particular axes for 2d output, lathes */
    // bool GetSupressXpos();
    // bool GetSupressYpos();
    // bool GetSupressZpos(); 	
    // void SetSupressXpos (bool yn);
    // void SetSupressYpos (bool yn);
    // void SetSupressZpos (bool yn);
    static NAN_METHOD(GetSupressXpos);
    static NAN_METHOD(SetSupressXpos);
    static NAN_METHOD(GetSupressYpos);
    static NAN_METHOD(SetSupressYpos);
    static NAN_METHOD(GetSupressZpos);
    static NAN_METHOD(SetSupressZpos);

    // --------------------
    // CLEAR STATE INFORMATION -- like the current position, feedrate,
    // spindle, etc.  This is useful when you do a tool change or
    // other such thing, to force the output of new codes even if the
    // associated values have not changed.
    //
    // bool  GetUseBlocknums();
    // void SetUseBlocknums (bool yn);
    static NAN_METHOD(GetUseBlocknums);
    static NAN_METHOD(SetUseBlocknums);

    // Maximum permissible block number, or zero for no limit.  After
    // the limit is reached, the block number wraps around to 1.
    // 
    // int GetBlocknumLimit();
    // void SetBlocknumLimit (int max);
    static NAN_METHOD(GetBlocknumLimit);
    static NAN_METHOD(SetBlocknumLimit);

    // bool  GetUseWhitespace();
    // void SetUseWhitespace (bool yn);
    static NAN_METHOD(GetUseWhitespace);
    static NAN_METHOD(SetUseWhitespace);
};


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
#include <stncapt/APT.h>
#include <stncapt/message.h>
class AptStepMaker : public Nan::ObjectWrap {
private:
    apt2step * _apt;
    static AptStepMaker* _singleton;
    static NAN_METHOD(New);
    static inline Nan::Persistent<v8::Function> & constructor() {
	static Nan::Persistent<v8::Function> my_constructor;
	return my_constructor;
    }
    AptStepMaker() { 
        report_via_printf();
        _apt = new apt2step(); 
    };
    ~AptStepMaker() { delete _apt; };
public:
    static apt2step* getApt();
    static NAN_MODULE_INIT(Init);
		
    // void ArcXYPlane(string label, double x,y,z, cx,cy,cz, rad, bool ccw);
    // void ArcYZPlane(string label, double x,y,z, cx,cy,cz, rad, bool ccw);
    // void ArcZXPlane(string label, double x,y,z, cx,cy,cz, rad, bool ccw);
    static NAN_METHOD(ArcXYPlane);
    static NAN_METHOD(ArcYZPlane);
    static NAN_METHOD(ArcZXPlane);

    // void CamModeOn/Off()
    static NAN_METHOD(CamModeOn);
    static NAN_METHOD(CamModeOff);

    // void CoolantOn/Off()
    static NAN_METHOD(CoolantOn);
    static NAN_METHOD(CoolantOff);
    static NAN_METHOD(CoolantMist);
    static NAN_METHOD(CoolantThru);
    
    // void DefineTool(
    // 	double tool_diameter
    // 	double tool_radius 
    // 	double horizontal_distance
    // 	double vertical_distance
    // 	double unused
    // 	double angle
    // 	double height
    // 	)
    static NAN_METHOD(DefineTool);

    // void ExecutableToSelective(int id)
    static NAN_METHOD(ExecutableToSelective);

    // void ExecutableWorkpieceAsIs(int id, string filename)
    static NAN_METHOD(ExecutableWorkpieceAsIs);

    // void ExecutableWorkpieceRemoval(int id, string filename)
    static NAN_METHOD(ExecutableWorkpieceRemoval);

    // ExecutableWorkpieceReuse*(int id, int other_id)
    static NAN_METHOD(ExecutableWorkpieceReuseAsIs);
    static NAN_METHOD(ExecutableWorkpieceReuseRemoval);
    static NAN_METHOD(ExecutableWorkpieceReuseToBe);

    // void ExecutableWorkpieceToBe(int id, string filename)
    static NAN_METHOD(ExecutableWorkpieceToBe);
    
    // void Feedrate (double feed)
    static NAN_METHOD(Feedrate);

    // void FeedrateUnit (string name)
    static NAN_METHOD(FeedrateUnit);

    // void Fixture (string filename)
    // void Fixture (string filename, int wplan_id)
    static NAN_METHOD(Fixture);

    // void GenerateToolGeometry(int tl_or_ws_id);    
    static NAN_METHOD(GenerateToolGeometry);

    // void GeometryForTool (int id, string filename)
    static NAN_METHOD(GeometryForTool);

    // void GeometryForToolNumber (string filename, int number)
    static NAN_METHOD(GeometryForToolNumber);
     
    // int GetCurrentFunction();
    static NAN_METHOD(GetCurrentFunction);

    // int GetCurrentFixture();
    static NAN_METHOD(GetCurrentFixture);

    // int GetCurrentRawpiece();
    static NAN_METHOD(GetCurrentRawpiece);

    // int GetCurrentTech();
    static NAN_METHOD(GetCurrentTech);
    
    // int GetCurrentTool();
    static NAN_METHOD(GetCurrentTool);
    
    // int GetCurrentToolpath();
    static NAN_METHOD(GetCurrentToolpath);

    // int GetCurrentWorkingstep();
    static NAN_METHOD(GetCurrentWorkingstep);

    // int GetCurrentWorkpiece();
    static NAN_METHOD(GetCurrentWorkpiece);

    // int GetCurrentWorkplan();
    static NAN_METHOD(GetCurrentWorkplan);

    // int GetExecutableWorkpieceAsIs(int wsid);
    static NAN_METHOD(GetExecutableWorkpieceAsIs);
	
    // int GetExecutableWorkpieceFixture(int wsid);
    static NAN_METHOD(GetExecutableWorkpieceFixture);
    
    // int GetExecutableWorkpieceRemoval(int wsid);
    static NAN_METHOD(GetExecutableWorkpieceRemoval);
    
    // int GetExecutableWorkpieceToBe(int wsid);
    static NAN_METHOD(GetExecutableWorkpieceToBe);

    //string GetIDFromUUID(string UUID)
    static NAN_METHOD(GetIDFromUUID);

    //int GetToolEID(string tool_number)
    static NAN_METHOD(GetToolEID);

    //string GetToolIdentifier(string tool_number)
    static NAN_METHOD(GetToolIdentifier);

    //string GetToolNumber(int id)
    static NAN_METHOD(GetToolNumber);

    //int[] GetWorkpieceExecutableAll(int wp_id)
    static NAN_METHOD(GetWorkpieceExecutableAll);

    //double[9] GetWorkpiecePlacement(int wp_id);
    static NAN_METHOD(GetWorkpiecePlacement);
    
    //double[9] GetWorkplanSetup(int wp_id);
    static NAN_METHOD(GetWorkplanSetup);

    // void GoToXYZ(string label, double x,y,z);
    static NAN_METHOD(GoToXYZ);

    // void GoToXYZ_IJK(string label, double x,y,z, i,j,k);
    static NAN_METHOD(GoToXYZ_IJK);

    // void GoToXYZ_ABC(string label, double x,y,z, a,b,c);
    static NAN_METHOD(GoToXYZ_ABC);

    // void GoToXYZ_IJK_ABC(string label, double x,y,z, i,j,k, a,b,c);
    static NAN_METHOD(GoToXYZ_IJK_ABC);

    // void GoToXYZ_IJK_REF_ABC(string label, double x,y,z, i,j,k, a,b,c);
    static NAN_METHOD(GoToXYZ_IJK_REF_ABC);

    //string GetUUID(int EID)
    static NAN_METHOD(GetUUID);

    // void Inches()
    static NAN_METHOD(Inches);

    // bool IsToolDefined(int num)
    static NAN_METHOD(IsToolDefined);
    
    // void LoadTool(int num);
    static NAN_METHOD(LoadTool);

    // void MakeRawBox(int wp_id, double x,y,z, x_width, y_width, z_width);
    static NAN_METHOD(MakeRawBox);

    // void Millimeters()
    static NAN_METHOD(Millimeters);

    // void NewProject(string project_name)
    static NAN_METHOD(NewProject);

    // void OpenProject(string file_name)
    static NAN_METHOD(OpenProject);

    // void OpenSTEP (string file_name)
    static NAN_METHOD(OpenSTEP);

    // void PartNo (string partname)
    static NAN_METHOD(PartNo);
	
    //void PutWorkpiecePlacement(int wp_id, double x,y,z,i,j,k,a,b,c);
    static NAN_METHOD(PutWorkpiecePlacement);

    //void PutWorkplanSetup(int wp_id, double x,y,z,i,j,k,a,b,c);
    static NAN_METHOD(PutWorkplanSetup);

    // void Rapid()
    static NAN_METHOD(Rapid);

    // void Rawpiece(string name)
    static NAN_METHOD(Rawpiece);

    // void Reset()
    static NAN_METHOD(Reset);

    //void SaveAsModules(string file_name);
    static NAN_METHOD(SaveAsModules);

    //void SaveAsP21(string file_name);
    static NAN_METHOD(SaveAsP21);

    // void SELCTLTool(int num);
    static NAN_METHOD(SELCTLTool);

    // void SetCNCexportExecEnabled(int wsid);
    static NAN_METHOD(SetCNCexportExecEnabled);

    // void SetCNCexportExecDisabled(int wsid);
    static NAN_METHOD(SetCNCexportExecDisabled);

    // void SetName(int ent_id, string nm);
    static NAN_METHOD(SetName);

    // string SetNameGet(int ent_id);
    static NAN_METHOD(SetNameGet);

    // void SetToolIdentifier(string tool_number, string identifier)
    static NAN_METHOD(SetToolIdentifier);

    // void SetToolNumber(string old_num, string new_num)
    static NAN_METHOD(SetToolNumber);

    // void SpindleSpeed (double feed)
    static NAN_METHOD(SpindleSpeed);

    // void SpindleSpeedUnit (string name)
    static NAN_METHOD(SpindleSpeedUnit);

    // void ToolGeometry(string file_name, string tool_ident);    
    static NAN_METHOD(ToolGeometry);

    // void Workingstep (string label)
    static NAN_METHOD(Workingstep);

    // int WorkingstepAfter (string label, int idx, int wp_id)
    static NAN_METHOD(WorkingstepAfter);

    // WorkingstepAddPropertyCountMeasure(int wsid, string propname, int val);
    static NAN_METHOD(WorkingstepAddPropertyCountMeasure);

    // WorkingstepAddPropertyDescriptiveMeasure(int wsid, string propname, string val);
    static NAN_METHOD(WorkingstepAddPropertyDescriptiveMeasure);

    // WorkingstepAddPropertyLengthMeasure(int wsid, string propname, double val);
    static NAN_METHOD(WorkingstepAddPropertyLengthMeasure);
    
    // void WorkingstepToolpathOrientation(x,y,z, i,j,k, a,b,c);
    static NAN_METHOD(WorkingstepToolpathOrientation);

    // void Workpiece(string filename)
    static NAN_METHOD(Workpiece);

    //void WorkplanSetup(int plan_id, double x,y,z,i,j,k,a,b,c);
    static NAN_METHOD(WorkplanSetup);

    //void WorkplanSetupDelete(int plan_id);
    static NAN_METHOD(WorkplanSetupDelete);
};

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
#include <stncapt/Process.h>
#include "nodeAptStepMaker.h"
#include <stncapt/message.h>
class Process : public Nan::ObjectWrap {
private:
    static Process* _singleton;
    process * _process;
    static NAN_METHOD(New);
    static inline Nan::Persistent<v8::Function> & constructor() {
	static Nan::Persistent<v8::Function> my_constructor;
	return my_constructor;
    }
    ~Process() { delete _process; };
    Process() { 
        report_via_printf();
        _process = new process(AptStepMaker::getApt());
    };

    // void Boring ( int ws_id, double cutting_depth, dwell_time_bottom, feed_on_retract, previous_diameter, bool spindle_stop_at_bottom, waiting_x, waiting_y, waiting_z, depth_of_test_cut );
    // void BottomSideFinishMilling ( int ws_id, double side_allowance, bottom_allowance, radial_depth, axial_depth );
    // void BottomSideRoughMilling ( int ws_id, double side_allowance, bottom_allowance, radial_depth, axial_depth );
    // void ClearancePlane ( int ws_id, double z );
    // void CoolantMist ( int ws_id );
    // void CoolantOff ( int ws_id );
    // void CoolantOn ( int ws_id );
    // void DrillPointAdd ( int ws_id, double x, y, double z );
    // void DrillWorkingstepAdd ( int ws_id, double x, y, z );
    // void Drilling ( int ws_id, double cutting_depth, dwell_time_bottom, feed_on_retract, previous_diameter );
    // void DrillingStrategy ( int ws_id, double reduced_cut_at_start, reduced_feed_at_start, depth_of_start, reduced_cut_at_end, reduced_feed_at_end, depth_of_end );
    // int FindOrMakeTechologyCSS ( double feed, speed, max_speed );

    // int GetToolISO13399AssemblyCount ( int tool_id );
    // string GetToolISO13399AssemblyName ( int definition_id );
    // int GetToolISO13399AssemblyNext ( int tool_id, int index );
    // int GetToolISO13399AssemblyNumericAttributeCount ( int definition_id );
    // int GetToolISO13399AssemblyStringAttributeCount ( int definition_id );
    // string GetToolISO13399AssemblyStringAttributeNext ( int definition_id, int index, OUT int %string_id, OUT string %name );
    // int GetToolISO13399ItemCount ( int tool_id );
    // string GetToolISO13399ItemName ( int instance_id );
    // int GetToolISO13399ItemNext ( int tool_id, int index );
    // int GetToolISO13399ItemNumericAttributeCount ( int instance_id );
    // int GetToolISO13399ItemStringAttributeCount ( int instance_id );
    // string GetToolISO13399ItemStringAttributeNext ( int instance_id, int index, OUT int %string_id, OUT string %name );
    // string GetToolISO13399ItemType ( int instance_id );
    // string GetToolISO13399NumericValue ( int numeric_id, string desired_unit, OUT string %name, OUT string %unit );
    // string GetToolISO13399StringValue ( int string_id, OUT string %name );
    // string GetToolReferenceDataName ( int ws_id, OUT bool %value_set );
    // string GetToolReferenceDataSTRL ( int ws_id, OUT bool %value_set );

    // void InitializeOverrides ( int wp_ws_tp_id, double initial_value, int only_cross );
    // void LoadISO13399Schema ( string directory );
    // void Material ( int wp_id, string name );
    
    // void MillingStrategyApproachAirAngle ( int ws_id, double angle, travel_length );
    // void MillingStrategyApproachAirTangent ( int ws_id, double radius );
    // void MillingStrategyApproachPlungeHelix ( int ws_id, double radius, angle );
    // void MillingStrategyApproachPlungeRamp ( int ws_id, double angle );
    // void MillingStrategyApproachPlungeToolaxis ( int ws_id );
    // void MillingStrategyApproachPlungeZigzag ( int ws_id, double angle, width );
    // void MillingStrategyRetractAirAngle ( int ws_id, double angle, travel_length );
    // void MillingStrategyRetractAirTangent ( int ws_id, double radius );
    // void MillingStrategyRetractPlungeHelix ( int ws_id, double radius, angle );
    // void MillingStrategyRetractPlungeRamp ( int ws_id, double angle );
    // void MillingStrategyRetractPlungeToolaxis ( int ws_id );
    // void MillingStrategyRetractPlungeZigzag ( int ws_id, double angle, width );
    // void MillingStrategyTwo5dBidirectional ( int ws_id, string stepover_direction, string stroke_connection_strategy, double fi, fj, fk );
    // void MillingStrategyTwo5dBidirectionalContour ( int ws_id, string spiral_cutmode, string rotation_direction, string stepover_direction, double fi, fj, fk );
    // void MillingStrategyTwo5dCenterMilling ( int ws_id );
    // void MillingStrategyTwo5dContourBidirectional ( int ws_id, string spiral_cutmode, string rotation_direction, string stepover_direction, double fi, fj, fk );
    // void MillingStrategyTwo5dContourParallel ( int ws_id, string cutmode, string rotation_direction );
    // void MillingStrategyTwo5dContourSpiral ( int ws_id, string cutmode, string rotation_direction );
    // void MillingStrategyTwo5dExplicitStrategy ( int ws_id );
    // void MillingStrategyTwo5dUnidirectional ( int ws_id, string cutmode, double fi, fj, double fk );
    // void MultistepDrilling ( int ws_id, double cutting_depth, depth_of_step, first_depth, retract_distance, dwell_time_bottom, feed_on_retract, dwell_time_step, previous_diameter );
    // int OptimizeFeedsUsingCrossSectionParameters ( int exe_id, double max_feed, int set_override );
    // void PlaneFinishMilling ( int ws_id, double allowance, axial_depth );
    static NAN_METHOD(PlaneFinishMilling);
    
    // void PlaneRoughMilling ( int ws_id, double allowance, axial_depth );
    static NAN_METHOD(PlaneRoughMilling);

    // string Process::GetToolISO13399AssemblyNumericAttributeNext ( int definition_id, int index, string desired_unit, OUT int %numeric_id, OUT string %ret_name, OUT string %ret_unit );
    // string Process::GetToolISO13399ItemNumericAttributeNext ( int instance_id, int index, string desired_unit, OUT int %numeric_id, OUT string %ret_name, OUT string %ret_unit );
    // int ReadCrossSectionData ( string file_name, int exe_id );
    // void Reaming ( int ws_id, double cutting_depth, dwell_time_bottom, feed_on_retract, previous_diameter, bool spindle_stop_at_bottom, double waiting_x, waiting_y, waiting_z, depth_of_test_cut );
    // void RetractPlane ( int ws_id, double z );
    // void SaveISO13399Data ( string out_directory );
    // int SecondWorkingstep ( int first_ws_id );
    // void SetMachineParametersDelete ( int wp_id );
    // void SetMachineParametersMachineName ( int wp_id, string name );
    // void SetMachineParametersSpeedFeed ( int wp_id, double feed, spindle_power, spindle_speed, spindle_torque );
    // void SetOverride ( int pt_id, double value );
    // void SetPathDepth ( int path_id, double depth );
    // void SetPathOvercut ( int path_id, double overcut );
    // void SetSurfacePropertyForWorkingstep ( int ws_id, string val );
    // void SetSurfacePropertyForWorkpiece ( int wp_id, string value );
    // int SetTechnolgyConstChipModeIsOn ();
    // void SetTechnolgyConstChipModeOff ();
    // void SetTechnolgyConstChipModeOn ();
    // void SetTechnologyFeed ( int tech_id, double feedrate );
    // int SetTechnologyFeedInTool ( int tool_id, int tech_id, double feedrate );
    // int SetTechnologyFeedInWorkingstep ( int ws_id, int tech_id, double feedrate );
    // void SetTechnologyForPath ( int path_id, int tech_id );
    // void SetTechnologySpeed ( int tech_id, double spindle_speed );
    // int SetTechnologySpeedInTool ( int tool_id, int tech_id, double spindle_speed );
    // int SetTechologySpeedInWorkingstep ( int ws_id, int tech_id, double spindle_speed );


    // void SetToolCoolantThroughTool ( int tl_id, int on_off );
    static NAN_METHOD(SetToolCoolantThroughTool);
    
    // void SetToolCornerRadius ( int tl_id, double radius );
    static NAN_METHOD(SetToolCornerRadius);

    // void SetToolCurrentCornerRadius ( int tl_id, double current_corner_radius );
    static NAN_METHOD(SetToolCurrentCornerRadius);

    // void SetToolCurrentDiameter ( int tl_id, double current_diameter );
    static NAN_METHOD(SetToolCurrentDiameter);

    // void SetToolCurrentLength ( int tl_id, double current_length );
    static NAN_METHOD(SetToolCurrentLength);

    // void SetToolCuttingEdgeAngle ( int tl_id, double angle );
    static NAN_METHOD(SetToolCuttingEdgeAngle);

    // void SetToolCuttingEdgeAngleLowerUpper ( int tl_id, double value, lower, string lreason, double upper, string ureason );
    static NAN_METHOD(SetToolCuttingEdgeAngleLowerUpper);

    // void SetToolDiameter ( int tl_id, double diameter );
    static NAN_METHOD(SetToolDiameter);
    
    // void SetToolDiameterLowerUpper ( int tl_id, double value, lower, string lreason, double upper, string ureason );
    static NAN_METHOD(SetToolDiameterLowerUpper);

    // void SetToolExpectedLife ( int tl_id, double minutes );
    static NAN_METHOD(SetToolExpectedLife);

    // void SetToolExpectedLifeLowerUpper ( int tl_id, double value, lower, string lreason, double upper, string ureason );
    static NAN_METHOD(SetToolExpectedLifeLowerUpper);

    // void SetToolFluteCount ( int tl_id, double flute_count );
    static NAN_METHOD(SetToolFluteCount);

    // void SetToolFluteLength ( int tl_id, double flute_length );
    static NAN_METHOD(SetToolFluteLength);

    // void SetToolFluteLengthLowerUpper ( int tl_id, double value, lower, string lreason, double upper, string ureason );
    static NAN_METHOD(SetToolFluteLengthLowerUpper);

    // void SetToolHandOfCut ( int tl_id, string left_neutral_right );
    static NAN_METHOD(SetToolHandOfCut);
    
    // void SetToolLength ( int tl_id, double length );
    static NAN_METHOD(SetToolLength);

    // void SetToolLengthLowerUpper ( int tl_id, double value, lower, string lreason, double upper, string ureason );
    static NAN_METHOD(SetToolLengthLowerUpper);

    // void SetToolMaterial ( int tl_id, string material );
    static NAN_METHOD(SetToolMaterial);
    
    // void SetToolMaterialStandard ( int tl_id, string standard );
    static NAN_METHOD(SetToolMaterialStandard);

    // void SetToolOverallAssemblyLength ( int tl_id, double length );
    static NAN_METHOD(SetToolOverallAssemblyLength);

    // void SetToolOverallAssemblyLengthLowerUpper ( int tl_id, double value, lower, string lreason, double upper, string ureason );
    static NAN_METHOD(SetToolOverallAssemblyLengthLowerUpper);
    
    // void SetToolRadiusLowerUpper ( int tl_id, double value, lower, string lreason, double upper, string ureason );
    static NAN_METHOD(SetToolRadiusLowerUpper);

    // void SetToolRecommendedFeed ( int tl_id, double feedrate );
    static NAN_METHOD(SetToolRecommendedFeed);

    // void SetToolRecommendedFeedLowerUpper ( int tl_id, double value, lower, string lreason, double upper, string ureason );
    static NAN_METHOD(SetToolRecommendedFeedLowerUpper);

    // void SetToolRecommendedSpeed ( int tl_id, double spindle_speed );
    static NAN_METHOD(SetToolRecommendedSpeed);

    // void SetToolRecommendedSpeedLowerUpper ( int tl_id, double value, lower, string lreason, double upper, string ureason );
    static NAN_METHOD(SetToolRecommendedSpeedLowerUpper);

    // void SetToolReferenceDataName ( int tl_id, string name );
    // void SetToolReferenceDataSTRL ( int tl_id, string strl );
    // void SetToolTaperThreadCount ( int tl_id, double count );
    // void SetToolThreadFormType ( int tl_id, string form_type );
    // void SetToolThreadPitch ( int tl_id, double pitch );
    // void SetToolThreadPitchLowerUpper ( int tl_id, double value, lower, string lreason, double upper, string ureason );
    // void SetToolThreadSize ( int tl_id, double size );
    // void SetToolThreadSizeLowerUpper ( int tl_id, double value, lower, string lreason, double upper, string ureason );

    // void SetToolTipAngle ( int tl_id, double angle );
    static NAN_METHOD(SetToolTipAngle);

    // void SetToolTipAngleLowerUpper ( int tl_id, double value, lower, string lreason, double upper, string ureason );
    static NAN_METHOD(SetToolTipAngleLowerUpper);


    // void SideFinishMilling ( int ws_id, double side_allowance, radial_depth, axial_depth );
    // void SideRoughMilling ( int ws_id, double side_allowance, radial_depth, axial_depth );
    // void Tapping ( int ws_id, double cutting_depth, bool compensation_chuck_required, double dwell_time_bottom, feed_on_retract, previous_diameter );
    // double ToolAssemblyUsingISO13399Data ( int tl_id, OUT bool %has_13399_data, OUT bool %tool_assembled );
    // void ToolAssemblyUsingISO13399DataChangeFilename ( int tl_id, string file_name, bool force_load );
    // void ToolAssemblyUsingISO13399DataChangeToolFunctionalLength ( int tl_id, double change_length, OUT bool %new_length_set, OUT double %new_length  );
    // bool ToolAssemblyUsingISO13399DataHasAssembly ( int tl_id );
    // double ToolAssemblyUsingISO13399DataRecommendedValues ( int tl_id, OUT double %low_value, OUT bool %low_set, OUT double %high_value, OUT bool %high_set );
    // void ToolIdentifier ( int ws_id, string identifier );
    
public:
    static NAN_MODULE_INIT(Init);
};

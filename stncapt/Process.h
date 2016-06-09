/* $RCSfile: Process.h,v $
 * $Revision: 1.54 $$Date: 2016/06/07 18:22:12 $
 * Auth: Martin Hardwick (hardwick@steptools.com)
 *
 * 	Copyright (c) 1991-2016 by STEP Tools Inc.
 * 	All Rights Reserved
 * 
 * 	This software is furnished under a license and may be used and
 * 	copied only in accordance with the terms of such license and with
 * 	the inclusion of the above copyright notice.  This software and
 * 	accompanying written materials or any other copies thereof may
 * 	not be provided or otherwise made available to any other person.
 * 	No title to or ownership of the software is hereby transferred.
 * 
 * 		----------------------------------------
 */

/*
 * Header for library to define process parameters
 */

#ifndef process_h
#define process_h

//  #include <afx.h>
//  #include <afxwin.h>

#include "rose.h"
//#include "module_support.h"
#include <stp_schema.h>

// utiltiy functions
#include "Units.h"
#include "Geometry.h"
#include "Contexts.h"

// module files
//#include "register.h"

#include "APT.h"
#include "Trace.h"

class process
{
    TraceContext tc;
    
public:

    process (apt2step *aptin);
    ~process ();

    RoseBoolean reset ();

    RoseBoolean inches ();
    RoseBoolean millimeters ();

    /* plane rough milling operation */
    RoseBoolean plane_rough_milling (int ws_id, double allowance,
				     double axial_depth = 0);

    /* plane finish milling operation */
    RoseBoolean plane_finish_milling (int ws_id, double allowance = 0,
				      double axial_depth = 0);

    /* bottom and side rough milling operation */
    RoseBoolean bottom_and_side_rough_milling
    (int ws_id, double side_allowance, double bottom_allowance,
     double radial_depth = 0, double axial_depth = 0);

    /* bottom and side finish milling operation */
    RoseBoolean bottom_and_side_finish_milling
    (int ws_id, double side_allowance = 0, double bottom_allowance = 0,
     double radial_depth = 0, double axial_depth = 0);

    /* side rough milling operation */
    RoseBoolean side_rough_milling
    (int ws_id, double side_allowance,
     double radial_depth = 0, double axial_depth = 0);

    /* side finish milling operation */
    RoseBoolean side_finish_milling
    (int ws_id, double side_allowance = 0, double radial_depth = 0,
     double axial_depth = 0);
    
    /* multi-step drilling operation */
    RoseBoolean multistep_drilling
    (int ws_id,  double cutting_depth, double depth_of_step,
     double first_depth = 0, double retract_distance = 0,
     double dwell_time_bottom = 0, double feed_on_retract = 0,
     double dwell_time_step = 0, double previous_diameter = 0);

    /* drilling operation */
    RoseBoolean drilling
    (int ws_id,  double cutting_depth, double dwell_time_bottom = 0,
     double feed_on_retract = 0, double previous_diameter = 0);

    /* tapping operation */
    RoseBoolean tapping
    (int ws_id,  double cutting_depth,
     RoseBoolean compensation_chuck_required = ROSE_TRUE,
     double dwell_time_bottom = 0, double feed_on_retract = 0,
     double previous_diameter = 0);

    /* reaming operation */
    RoseBoolean reaming
    (int ws_id,  double cutting_depth, double dwell_time_bottom,
     double feed_on_retract, double previous_diameter,
     RoseBoolean spindle_stop_at_bottom, double waiting_position_x=0,
     double waiting_position_y=0, double waiting_position_z=0,
     double depth_of_test_cut = 0);

    /* Boring operation */
    RoseBoolean boring
    (int ws_id,  double cutting_depth, double dwell_time_bottom,
     double feed_on_retract, double previous_diameter,
     RoseBoolean spindle_stop_at_bottom, double waiting_position_x=0,
     double waiting_position_y=0, double waiting_position_z=0,
     double depth_of_test_cut = 0);

    /* TURNING contouring */
    RoseBoolean contouring_rough_turning (int ws_id, double allowance = 0);

    /* retract plane for CAM operations */
    RoseBoolean retract (int ws_id, double z);

    /* clearance/security plane for CAM operations */
    RoseBoolean clearance (int ws_id, double z);
    
    /* material of rawpiece */
    RoseBoolean material (int wp_id, char * name);

    /* Define rawpiece with block geometry */
    /* length is Z for block and cylindrical, width is X */
    /* block origin is center of bottom face (as per 224) */
    RoseBoolean block_rawpiece (char * name, double x, double y, double z,
			 double length, double width, double height);

    /* Define rawpiece with block geometry */
    RoseBoolean cylinder_rawpiece (char * name, double x, double y, double z,
			    double length, double diameter);

    /* define the identifier of a tool for CAM's that want to do look-up */
    RoseBoolean tool_identifier (int ws_id, const char * name);

    /* second point for drilling operation. Convert feature to general pattern
       if necessary */
    RoseBoolean add_drilling_point (int ws_id, double x, double y, double z);
    
    /* second point for drilling operation by creating a new workingstep */
    RoseBoolean add_drilling_ws (int ws_id, double x, double y, double z);
 
    /* create second workingstep with the same feature */
    RoseBoolean second_workingstep (int first_ws_id, int &second_ws_id);
    
    // set coolant for an operation
    RoseBoolean coolant_on (int ws_id); 
    RoseBoolean coolant_off (int ws_id); 
    RoseBoolean coolant_mist (int ws_id); 

    // read an AP-224 file anc create a default manufacturing process
    RoseBoolean read_and_populate_224_file (const char *file_name);

    // if on then recalculate speed when feed changes and vice versa for speed
    RoseBoolean constant_chip_mode_on ();
    RoseBoolean constant_chip_mode_off ();
    RoseBoolean constant_chip_mode_is_on (int &mode);

    // find or make technology
    RoseBoolean find_or_make_technology (int &tech_id, double feed_value, double speed_value, double max_speed = 0);

    // set a tool path to a technology
    RoseBoolean set_technology (int path_id, int tech_id);
    RoseBoolean set_technology_feed (int tech_id, double feed);
    RoseBoolean set_technology_speed (int tech_id, double speed);

    RoseBoolean set_technology_feed_in_executable (int exe_id, int tech_id, int &new_tech_id, double feed);
    RoseBoolean set_technology_speed_in_executable (int exe_id, int tech_id, int &new_tech_id, double feed);

    RoseBoolean set_technology_feed_in_tool (int tl_id, int tech_id, int &new_tech_id, double feed);
    RoseBoolean set_technology_speed_in_tool (int tl_id, int tech_id, int &new_tech_id, double feed);

    // set the (default) surface property of a workpiece
    RoseBoolean set_surface_property_workpiece (int wp_id, char * value);

    // set the (default) surface property of a workpiece
    RoseBoolean set_surface_property_workingstep (int ws_id, char * value);

    // set machine parameters of a workplan
    RoseBoolean set_feed_speed_machine_parameters (int wp_id, double feed, double spindle_power, 
							double spindle_speed, double spindle_torque);

    // set the machine of a workplan (using a backdoor)
    RoseBoolean set_machine_name (int wp_id, const char *machine_name);

    // delete the machine parameters
    RoseBoolean set_machine_delete (int wp_id);

    // name and location of tool referenc (ISO 13399) data
    RoseBoolean set_tool_reference_id (int ws_id, const char *id);
    RoseBoolean set_tool_reference_strl (int ws_id, const char *strl);

    // set material, life and feed speed recommendations for first cutting_component
    RoseBoolean set_tool_expected_life (int ws_id, double life_in_minutes);
    RoseBoolean set_tool_cutting_material (int ws_id, const char *material);
    RoseBoolean set_tool_cutting_material_standard (int ws_id, const char *material);
    RoseBoolean set_tool_functional_length (int ws_id, double length);
    RoseBoolean set_tool_recommended_speed (int ws_id, double spindle_speed);
    RoseBoolean set_tool_recommended_feed (int ws_id, double feedrate);

    // set tool parameters with limits
    RoseBoolean set_tool_expected_life_lower_and_upper (int ws_id, double life_in_minutes, double lower, const char * lreason, double upper, const char * ureason);
    RoseBoolean set_tool_functional_length_lower_and_upper (int ws_id, double length, double lower, const char * lreason, double upper, const char * ureason);
    RoseBoolean set_tool_recommended_speed_lower_and_upper (int ws_id, double spindle_speed, double lower, const char * lreason, double upper, const char * ureason);
    RoseBoolean set_tool_recommended_feed_lower_and_upper (int ws_id, double feedrate, double lower, const char * lreason, double upper, const char * ureason);

    // set number of cutting components
    RoseBoolean set_tool_number_of_flutes (int ws_id, double flute_count);

    // set tool parameters individually
    RoseBoolean set_tool_overall_length (int ws_id, double length);
    RoseBoolean set_tool_flute_length (int ws_id, double length);
    RoseBoolean set_tool_diameter (int ws_id, double diameter);
    RoseBoolean set_tool_radius (int ws_id, double radius);
    RoseBoolean set_tool_taper_angle (int ws_id, double angle);
    RoseBoolean set_tool_tip_angle (int ws_id, double angle);

    // set tool parameters with limits
    RoseBoolean set_tool_overall_assembly_length_lower_and_upper (int ws_id, double length, double lower, const char * lreason, double upper, const char * ureason);
    RoseBoolean set_tool_flute_length_lower_and_upper (int ws_id, double length, double lower, const char * lreason, double upper, const char * ureason);
    RoseBoolean set_tool_diameter_lower_and_upper (int ws_id, double diameter, double lower, const char * lreason, double upper, const char * ureason);
    RoseBoolean set_tool_radius_lower_and_upper  (int ws_id, double radius, double lower, const char * lreason, double upper, const char * ureason);
    RoseBoolean set_tool_taper_angle_lower_and_upper  (int ws_id, double angle, double lower, const char * lreason, double upper, const char * ureason);
    RoseBoolean set_tool_tip_angle_lower_and_upper  (int ws_id, double angle, double lower, const char * lreason, double upper, const char * ureason);

    RoseBoolean set_tool_hand_of_cut (int ws_id, const char* left_neutral_right);
    RoseBoolean set_tool_coolant_through_tool (int ws_id, int on_off);

    // apt specific
    RoseBoolean set_tool_corner_radius_center_vertical (int ws_id, double dist);
    RoseBoolean set_tool_corner_radius_center_horizontal (int ws_id, double dist);

    // Tapping tool specific
    RoseBoolean set_tool_thread_form_type (int ws_id, const char *form_type);
    RoseBoolean set_tool_thread_size (int ws_id, double size);
    RoseBoolean set_tool_thread_pitch (int ws_id, double pitch);
    RoseBoolean set_tool_taper_thread_count (int ws_id, double count);

    // Tool parameters with limits
    RoseBoolean set_tool_thread_size_lower_and_upper (int ws_id, double size, double lower, const char * lreason, double upper, const char * ureason);
    RoseBoolean set_tool_thread_pitch_lower_and_upper (int ws_id, double pitch, double lower, const char * lreason, double upper, const char * ureason);
    RoseBoolean set_tool_taper_thread_count_lower_and_upper (int ws_id, double count, double lower, const char * lreason, double upper, const char * ureason);

    // set current values for tool parameters when these can vary at run time
    RoseBoolean tool_current_functional_length (int ws_id, double current_length);
    RoseBoolean tool_current_diameter (int ws_id, double current_diameter);
    RoseBoolean tool_current_radius (int ws_id, double current_radius);

    // set tool path depth
    RoseBoolean set_path_depth (int path_id, double depth);

    // set tool path overcut
    RoseBoolean set_path_overcut (int path_id, double depth);

    // tool-workpiece cross section area parameters
    RoseBoolean cross_section (const char *cross_file_name, const char *code_file_name, int e_id, int &code_count, int &store_count);

    // display the tool paths 
    RoseBoolean draw_cross_section (const char *cross_file_name, int &code_count);
    RoseBoolean draw_automated_dynamics (const char *cross_file_name, int &code_count);

    // curve to set speed override values after feed-speed optimization
    RoseBoolean override (int e_id, double initial_value, int only_cross);

    // set the override using an id found using finder
    RoseBoolean set_override_value (int pt_id, double new_value);


    // Strategy methods added for NIST starting in July 08
    RoseBoolean drilling_strategy (int ws_id,  double reduced_cut_at_start, double reduced_feed_at_start, 
			      double depth_of_start, double reduced_cut_at_end, double reduced_feed_at_end, 
			      double depth_of_end);

    RoseBoolean approach_plunge_toolaxis_strategy (int ws_id);
    RoseBoolean retract_plunge_toolaxis_strategy (int ws_id);
    RoseBoolean approach_plunge_ramp_strategy (int ws_id, double angle);
    RoseBoolean retract_plunge_ramp_strategy (int ws_id, double angle);
    RoseBoolean approach_plunge_zigzag_strategy (int ws_id, double angle, double width);
    RoseBoolean retract_plunge_zigzag_strategy (int ws_id, double angle, double width);
    RoseBoolean approach_plunge_helix_strategy (int ws_id, double radius, double angle);
    RoseBoolean retract_plunge_helix_strategy (int ws_id, double radius, double angle);

    RoseBoolean approach_air_retract_angle_strategy (int ws_id, double angle, double travel_length);
    RoseBoolean retract_air_retract_angle_strategy (int ws_id, double angle, double travel_length);
    RoseBoolean approach_air_retract_tangent_strategy (int ws_id, double radius);
    RoseBoolean retract_air_retract_tangent_strategy (int ws_id, double radius);

    RoseBoolean center_milling_strategy (int ws_id);
    RoseBoolean explicit_milling_strategy (int ws_id);
    RoseBoolean contour_spiral_milling_strategy (int ws_id, const char *cutmode, const char *rot_direction);
    RoseBoolean contour_parallel_milling_strategy (int ws_id, const char *cutmode, const char *rot_direction);
    RoseBoolean contour_bidirectional_milling_strategy (int ws_id, const char *spiral_cutmode, 
	double fi, double fj, double fk, const char *rot_direction, const char * stepover_direction);
    RoseBoolean bidirectional_milling_strategy (int ws_id, double fi, double fj, double fk,
	const char *stepover_direction, const char *connection_strategy);
    RoseBoolean bidirectional_contour_milling_strategy (int ws_id, const char *spiral_cutmode, double fi, double fj, double fk,
	const char *rot_direction, const char * stepover_direction);
    RoseBoolean unidirectional_milling_strategy (int ws_id, const char *cutmode, double fi, double fj, double fk);

    // calls same function in cursor
    RoseBoolean read_cross_section_data (int &flag, const char *file_name, int exe_id); 
    RoseBoolean optimize_using_cross_section_data (int &flag,int exe_id, double fmax, int set_override); 

    // read ISO 13399 data for tools
    RoseBoolean load_13399_schema();
    RoseBoolean save_13399_data (const char *out_directory);

    // explicitly load a ISO 13399 file
    RoseBoolean load_ISO_13399_file (int tl_id, const char *file_name, int force_load);

    // detect if the tool has ISO 13399 data that can be used for assembly
    RoseBoolean tool_has_13399_assembly (int tl_id, int &has_assembly);

    // Use STRL and ISO 13399 data for assembly
    RoseBoolean tool_direct_assembly_from_13399_data (int tl_id, int &has_iso13399_data, int &tool_assembled, double &new_length);

    // assemble a tool from its 13399 data
    RoseBoolean tool_change_assembly_length_using_13399_data (int tl_id, double change_length, double &new_length);

    // Get actual and recommended clamping values for tool assembly from ISO 13399 data
    RoseBoolean tool_assembly_recommended_tool_length_values (int tl_id, double &length_value, double &length_low, double &length_high, int &low_set, int &high_set);

    // ISO 13399 URL
    RoseBoolean get_tool_reference_data_name (int ws_id, const char * &identifier);    
    RoseBoolean get_tool_reference_data_strl (int ws_id, const char * &identifier_strl);    
    RoseBoolean put_tool_reference_data_name (int ws_id, const char * identifier_strl);
    RoseBoolean put_tool_reference_data_strl (int ws_id, const char * identifier_strl);

    // new two level method
    RoseBoolean tool_13399_item_instance_count (int ws_id, int &count);
    RoseBoolean tool_13399_item_instance_next (int ws_id, int index, int &item_instance_id);
    RoseBoolean tool_13399_assembly_definition_count (int ws_id, int &count);
    RoseBoolean tool_13399_assembly_definition_next (int ws_id, int index, int &assembly_instance_id);
    RoseBoolean tool_13399_item_in_assembly_instance_count (int assembly_id, int &count);
    RoseBoolean tool_13399_item_in_assembly_instance_next (int assembly_id, int index, int &item_instance_id);

    RoseBoolean tool_13399_item_instance_details (int item_instance_id, const char * &instance_id, const char * &definition_id, const char * &version_id, const char * &item_id);
    RoseBoolean tool_13399_assembly_definition_details (int assembly_definition_id,  const char * &definition_id, const char * &version_id, const char * &item_id);

    RoseBoolean tool_13399_item_external_step_file (int item_id, const char * &file_name, const char * &url_name);

    RoseBoolean tool_13399_item_instance_numeric_count (int item_id, int &count);
    RoseBoolean tool_13399_item_instance_string_count (int item_id, int &count);
    RoseBoolean tool_13399_item_instance_numeric_next (int item_id, int index, const char * desired_unit, int &numeric_instance_id, const char * &name, const char * &value, const char *&unit);
    RoseBoolean tool_13399_item_instance_string_next (int item_id, int index, int &string_instance_id, const char * &name, const char * &value);

    RoseBoolean tool_13399_assembly_definition_numeric_count (int item_id, int &count);
    RoseBoolean tool_13399_assembly_definition_string_count (int item_id, int &count);
    RoseBoolean tool_13399_assembly_definition_numeric_next (int item_id, int index, const char * desired_unit, int &numeric_instance_id, const char * &name, const char * &value, const char *&unit);
    RoseBoolean tool_13399_assembly_definition_string_next (int item_id, int index, int &string_instance_id, const char * &name, const char * &value);

    RoseBoolean get_iso_13399_numerical_value (int numeric_id, const char * desired_unit, const char * &name, const char * &value, const char *&unit);
    RoseBoolean get_iso_13399_string_value (int string_id, const char * &name, const char * &value);

    RoseBoolean put_iso_13399_numerical_value (int numeric_id, const char * value);
    RoseBoolean put_iso_13399_string_value (int string_id, const char * value); 

private:
    apt2step * apt;

    // schema for ISO 13399 data
    RoseDesign *cutting_schema_design;

    int const_chip_on;

    // used by coolant functions
    RoseBoolean set_machine_functions (RoseObject *fn, int ws_id);

    // intialize the override curve
    RoseBoolean add_override_values (int num_points, stp_polyline *new_poly, double initial_value);

    // used in traversal of workplans and workingsteps by cross_section_area and override
    Trajectory_IF *get_next_path_in_ws (Machining_workingstep * &ws, int &ws_index); 
    Machining_workingstep *get_next_ws_in_wp (Workplan * &wp, int &wp_index);
    RoseBoolean open_cross_file (const char *file_name);

    Workplan *cross_section_wp_stack[100];
    int cross_section_wp_index_stack[100];
    int cross_section_stack_count;

    // add point to cross section
    RoseBoolean add_path_cross_section (stp_polyline *old_poly, stp_polyline *new_poly, 
	RoseBoolean is_composite, int &code_count, RoseXform M);

    // read next line of cross section data
    RoseBoolean next_cross_section (int &code_count);

    // code to read tool paths from automated dynamics file
    RoseBoolean next_dynamics_line (int &code_count);

    // version that does not use g-code
    RoseBoolean next_cross_section2 (int &code_count);

    // values polulated by next_cross_section()
    int line_num, line_type;
    float RC_max, AC_max, X_offset, Y_offset, RD_max, RD_avg, RD_offset;
    float new_x, new_y, new_z;
    float new_i, new_j, new_k;	    // used for automated dynamics
    float new_a, new_b, new_c;	    // used for automated dynamics

    // file and status variables for next_cross_section
    FILE *dynamics_file;
    FILE *cross_file;
    FILE *code_file;
    int end_of_file_found;
    int not_found;

    // last values read from cross_section file
    int last_line_num;

    // the empty value for cross section area
    stp_cartesian_point *air_cross;
    RoseDesign *air_cross_des;
    
    stp_cartesian_point *exceed_cross;
    RoseDesign *exceed_cross_des;

    stp_cartesian_point *none_cross;
    RoseDesign *none_cross_des;

    int cross_rapid_flag;
    /* last entity id given to new data */
//	unsigned last_id;

    // feed speed editing helper functions
    Milling_technology *milling_technology_new_feed_old_speed (Milling_technology* mtech, double feed);
    Turning_technology *turning_technology_new_feed_old_speed (Turning_technology* ttech, double feed);
    Milling_technology *milling_technology_old_feed_new_speed (Milling_technology* mtech, double speed);
    Turning_technology *turning_technology_old_feed_new_speed (Turning_technology* ttech, double speed);

    int update_workingstep_technology (Machining_workingstep *ws, Technology_IF *old_tech, Technology_IF *new_tech); 
    int update_workplan_technology (Workplan *wp, Technology_IF *old_tech, Technology_IF *new_tech);
    int update_selective_technology (Selective *sl, Technology_IF *old_tech, Technology_IF *new_tech);

    // functions to get ISO13399 data
    // new method has two levels - items and assemblies then numeric and string
    RoseDesign *iso13399_design;
    void internal_iso13399_items_and_assemblies (int ws_id);
    int iso13399_assembly_signature;
    int iso13399_item_signature;
    RoseUnit iso13399_desired_unit;
    ListOfRoseObject iso13399_item_instance;
    ListOfdouble iso13399_item_z_position;
    ListOfRoseObject iso13399_assembly_definition;

    // second path to items via assembly
    void internal_iso13399_items_in_assembly (int assembly_id);

    void internal_iso13399_item_attributes (int item_id);
    int iso13399_item_attribute_signature;
    ListOfRoseObject iso13399_item_numeric_attribute;
    ListOfRoseObject iso13399_item_string_attribute;

    void internal_iso13399_assembly_attributes (int assembly_id);
    int iso13399_assembly_attribute_signature;
    ListOfRoseObject iso13399_assembly_numeric_attribute;
    ListOfRoseObject iso13399_assembly_string_attribute;


};


#endif

/* $RCSfile: Find.h,v $
 * $Revision: 1.126 $ $Date: 2016/06/07 20:24:08 $
 * Auth: Jochen Fritz (jfritz@steptools.com)
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
 * Header for Finder class
 */

#ifndef finder_h
#define finder_h
#include "Project.h"
#include "Trace.h"
#include <stp_schema.h>
#include <stix_unit.h>
#include "Cursor.h"

class finder
{

    TraceContext tc;
    
public:

    finder ();
    ~finder ();

    // set interface units
    RoseBoolean api_unit_native (); 
    RoseBoolean api_unit_mm ();
    RoseBoolean api_unit_inch ();
    RoseBoolean api_unit_feed (const char *unit);
    RoseBoolean api_unit_speed (const char *unit);

    RoseBoolean set_use_stix_transform_on ();
    RoseBoolean set_use_stix_transform_off();
    RoseBoolean stix_transform_available(int &yn);

    // global function to test whole program, also need functions for wp and ws
    RoseBoolean contains_turning (int &flag);
    RoseBoolean contains_milling (int &flag);

    RoseBoolean search (const char * name);
    RoseBoolean new_search (const char * name);
    RoseBoolean search224 (const char * name);
    RoseBoolean current_design (RoseDesign* &design);
    RoseBoolean current_design_name (const char * &path);

    // refresh by force reading a file read
    RoseBoolean refresh ();

    // get values in the STRL in the file if it has one
    RoseBoolean decode_strl (int &flag, int &wp_id, int &ws_id, int &tp_id, double &d);

    RoseBoolean reset (RoseBoolean shutdown = ROSE_FALSE);

    // return name of project and workpiece
    RoseBoolean project (const char* &prj_name, const char* &wpk_name);

    // return id and size of main workplan
    RoseBoolean main (int &wp_id, int &size);

    // return size and name of a workplan
    RoseBoolean workplan (int wp_id, int &size, const char * &name);

    // functions for traversing structure
    RoseBoolean workplan_executable_count (int wp_id, int &size);
    RoseBoolean workplan_executable_next (int wp_id, int index, int &exe_id);
    RoseBoolean workplan_executable_all (int wp_id, rose_uint_vector &tmp);
    RoseBoolean workplan_executable_all_enabled (int wp_id, rose_uint_vector &tmp);
    RoseBoolean selective_executable_count (int sl_id, int &size);
    RoseBoolean selective_executable_next (int sl_id, int index, int &exe_id);
    RoseBoolean selective_executable_all (int wp_id, rose_uint_vector &tmp);
    RoseBoolean selective_executable_all_enabled (int wp_id, rose_uint_vector &tmp);

    RoseBoolean nested_executable_count (int own_id, int &size);
    RoseBoolean nested_executable_next (int own_id, int index, int &exe_id);
    RoseBoolean nested_executable_all (int own_id, rose_uint_vector &tmp);
    RoseBoolean nested_executable_all_enabled (int own_id, rose_uint_vector &tmp);

    // flag set to true if executable is enabled
    RoseBoolean is_enabled (int exe_id, int &flag);

    // return the id of the workingstep at give index or 0 if not a workingstep
    RoseBoolean is_workingstep (int wp_id, int index, int &ws_id,
				const char * &name);

    // return the id of the workingstep at give index or 0 if not a workingstep
    RoseBoolean workingstep_name (int ws_id, const char * &name);

    // return the path orientation of a workingstep
    RoseBoolean workingstep_path_orientation (int ws_id, int &is_set, 
			    double &x, double &y, double &z, double &i, double &j, double &k,
			    double &a, double &b, double &c);

    // return tool paths in a workingstep
    RoseBoolean first_path (int ws_id, int &size, int &path_id,
			    RoseBoolean &is_contact);
    RoseBoolean next_path (int ws_id, int index, int &path_id,
			   RoseBoolean &is_contact);
    RoseBoolean all_path (int ws_id, rose_uint_vector &paths);

    RoseBoolean path_contact_type (int path_id, RoseBoolean &is_contact);
    RoseBoolean path_center_type (int path_id, RoseBoolean &is_center);

    // contact, center or connector
    RoseBoolean path_type (int &path_id, const char * &type);

    RoseBoolean path_rapid (int path_id, RoseBoolean &is_rapid);

    RoseBoolean first_curve (int path_id, int &size, int &curve_id,
			     RoseBoolean &is_arc);
    
    RoseBoolean next_curve (int path_id, int index, int &curve_id,
			    RoseBoolean &is_arc);

    RoseBoolean all_curve (int path_id, rose_uint_vector &curves);

    RoseBoolean first_axis (int path_id, int &size);    
    RoseBoolean next_axis (int path_id, int index, int &curve_id);
    RoseBoolean all_axis (int path_id, rose_uint_vector &axes);

    RoseBoolean first_direction (int path_id, int &size);    
    RoseBoolean next_direction (int path_id, int index, int &curve_id);
    RoseBoolean all_direction (int path_id, rose_uint_vector &directions);

    RoseBoolean first_area (int path_id, int &size);
    RoseBoolean next_area (int path_id, int index, int &area_id);
    RoseBoolean all_area (int path_id, rose_uint_vector &curves);

    RoseBoolean first_override (int path_id, int &size);
    RoseBoolean next_override (int path_id, int index, int &override_id);
    RoseBoolean all_override (int path_id, rose_uint_vector &overrides);

    // first point in curve regardless of polyline or trimmed
    RoseBoolean start_point (int curve_id, double &x, double &y, double &z);

    // type of a curve
    RoseBoolean curve_type (int curve_id, const char * &type);

    // Units of a curve
    RoseBoolean path_units(int curve_id, const char * &type);

    // return points in a polyline curve
    RoseBoolean first_point (int curve_id, int &size);
    RoseBoolean next_point (int curve_id, int index, double &x, double &y,
			    double &z);
    RoseBoolean all_points (int curve_id, RoseReal3DArray& result);
    RoseBoolean next_point_id (int curve_id, int index, int &point_id);

    // return axis points
    RoseBoolean first_axis_point (int curve_id, int &size);
    RoseBoolean next_axis_point (int curve_id, int index, double &i, double &j, double &k);
    RoseBoolean all_axis_points (int curve_id, RoseReal3DArray& result);

    // return direction points
    RoseBoolean first_direction_point (int curve_id, int &size);
    RoseBoolean next_direction_point (int curve_id, int index, double &i, double &j, double &k);
    RoseBoolean all_direction_points (int curve_id, RoseReal3DArray& result);

    // return points in a polyline area curve
    RoseBoolean first_area_point (int curve_id, int &size);
    RoseBoolean next_area_point (int curve_id, int index, const char *&type, double &RC_max, double &AC_max, 
							double &X_offset, double &Y_offset, double &RD_max, 
							double &RD_avg, double &RD_offset);
    RoseBoolean all_area_points (int curve_id, rose_real_vector &result);

    // return 1-dimensional points in an override curve
    RoseBoolean first_override_point (int curve_id, int &size);
    RoseBoolean next_override_point (int curve_id, int index, double &override_value);
    RoseBoolean all_override_points (int curve_id, rose_real_vector &result);

    // arc in a curve
    RoseBoolean arc(int curve_id, double &new_x, double &new_y, double &new_z, 
		    double &cx, double &cy, double &cz, double &radius,
		    int &ccw);
    RoseBoolean arc_axis(int curve_id, double &cx, double &cy, double &cz, double &ci, double &cj, double &ck);


    // closest face (geometrically) to a workingstep
    // this version uses Joe's code
    // other version moved to tolerance
    RoseBoolean closest_face2 (int ws_id, double threshold, int &face_id);

    // collission between face and toolpath in workingstep
    RoseBoolean collission_face (int ws_id, double threshold, int &face_id);

    // summary information about technology of path -- coolant on does not work for performance reasone
    RoseBoolean path_technology (int path_id, double &feed, double &speed, RoseBoolean &is_rapid, RoseBoolean &coolant_on);
    RoseBoolean path_technology_id (int path_id, int &tech_id);

    // This function needs more parameters
    RoseBoolean path_functions (int path_id, RoseBoolean &coolant_on);

    // path depth
    RoseBoolean path_depth (int path_id, double &depth);

    // path depth
    RoseBoolean path_overcut (int path_id, double &overcut);

    // number of tools in the database
    RoseBoolean tool_count (int &count);
    RoseBoolean tool_next (int index, int &tl_id); 
 
    // Count the number of similar tools to a tool
    RoseBoolean similar_tool_count (int tl_id, int type, int diameter, int length, int radius, int flute_count, int manufacturer, int &count);
    RoseBoolean similar_tool_next (int tl_id, int index, int &similar_tl_id);
    
    // number of tools in workplan
    RoseBoolean wp_tool_count (int wp_id, int &size);
    RoseBoolean wp_tool_next (int wp_id, int index, int &tl_id);

    // id of tool found using its_id (tool number) 
    RoseBoolean find_tool_using_its_id (const char *its_id, int &tl_id);
 
    // id of tool found using tool number (calls tool_id)
    RoseBoolean find_tool_using_number (int number, int &tl_id);
 
    // id of tool found using identifier (unique)
    RoseBoolean find_tool_using_its_identifier (const char *identifier, int &tl_id);

    // type (module name) for a tool
    RoseBoolean tool_type (int tl_or_ws_id, const char * &its_type);

    // information found using the the e-id of the tool or the e-id of a
    // workingstep
    RoseBoolean tool_apt (int ws_id, const char * &its_id, double &tool_diameter, double &tool_radius,
		   double &horizontal_distance, double &vertical_distance,
		   double &tip_angle, double &taper_angle, double &height);

    RoseBoolean tool_apt_unit (int ws_id, const char * &tool_diameter, const char * &tool_radius,
			      const char * &horizontal_distance, const char * &vertical_distance,
			      const char * &tip_angle, const char * &taper_angle, const char * &height);

    // Tapping tool information
    RoseBoolean tool_tap (int ws_id, const char * &its_id, const char * &thread_form_type, double &thread_pitch, double &thread_size,
			      double &taper_thread_count);
    RoseBoolean tool_tap_unit (int ws_id, const char * &thread_pitch, const char * &thread_size);
    RoseBoolean tool_thread_pitch_lower_upper (int ws_id, double &value, double &lower, const char * &lreason, double &upper, const char *&ureason);
    RoseBoolean tool_thread_size_lower_upper (int ws_id, double &value, double &lower, const char * &lreason, double &upper, const char *&ureason);

    // current tool values set during closed loop programming
    RoseBoolean tool_current (int tl_or_ws_id, double &tool_diameter, double &tool_radius,
			      double &tool_length, double &tool_current_diameter, 
			      double &tool_current_radius, double &tool_current_length);

    RoseBoolean tool_current_unit (int tl_or_ws_id, const char * &tool_diameter, const char * &tool_radius,
			      const char * &tool_length);

    RoseBoolean tool_effective_cutting_diameter_lower_upper (int tl_or_ws_id, double &value, double &lower, const char * &lreason, double &upper, const char *&ureason);
    RoseBoolean tool_radius_lower_upper (int tl_or_ws_id, double &value, double &lower, const char * &lreason, double &upper, const char *&ureason);

    // cutting edge (taper) on facemills, endmills and APT
    RoseBoolean tool_cutting_edge_angle (int tl_or_ws_id, double &tool_cutting_angle);
    RoseBoolean tool_cutting_edge_angle_unit (int tl_or_ws_id, const char * &tool_cutting_angle);
    RoseBoolean tool_cutting_edge_angle_lower_upper (int tl_or_ws_id, double &value, double &lower, const char * &lreason, double &upper, const char *&ureason);

    // return the its_id as a tool number
    RoseBoolean tool_number (int tl_or_ws_id, int &its_num);

    // return the its_id as defined in STEP-NC
    RoseBoolean tool_number_as_id (int tl_or_ws_id, const char * &its_num);
  
   // ISO 13399 and ISO 10303 product model data for a tool 
    RoseBoolean tool_part_name (int ws_id, int &pd_id, const char * &part_name);    
    RoseBoolean tool_reference_data_name (int ws_id, const char * &identifier);    
    RoseBoolean tool_reference_data_strl (int ws_id, const char * &identifier_strl);    
    
    // cutting component information set by process
    RoseBoolean tool_process (int ws_id, double &expected_life, const char * &material);
    RoseBoolean tool_process_unit (int ws_id, const char * &expected_life);
    RoseBoolean tool_expected_life_lower_upper (int ws_id, double &value, double &lower, const char * &lreason, double &upper, const char *&ureason);

    // cutting component information set by process
    RoseBoolean tool_number_of_flutes (int ws_id, double &flute_count);

    // tool overall assembly length information
    RoseBoolean tool_overall_assembly_length (int ws_id, double &length);
    RoseBoolean tool_overall_assembly_length_unit (int ws_id, const char * &length);
    RoseBoolean tool_overall_assembly_length_lower_upper (int ws_id, double &value, double &lower, const char * &lreason, double &upper, const char *&ureason);

    // tool functional length information
    RoseBoolean tool_functional_length (int ws_id, double &length);
    RoseBoolean tool_functional_length_unit (int ws_id, const char * &length);
    RoseBoolean tool_functional_length_lower_upper (int ws_id, double &value, double &lower, const char * &lreason, double &upper, const char *&ureason);

    // tool flute length (max depth of cut) information
    RoseBoolean tool_flute_length (int ws_id, double &length);
    RoseBoolean tool_flute_length_unit (int ws_id, const char * &length);
    RoseBoolean tool_flute_length_lower_upper (int ws_id, double &value, double &lower, const char * &lreason, double &upper, const char *&ureason);

    // unit used by tool product model
    RoseBoolean tool_geometry_length_unit (int ws_id, const char * &unit);

    // tool hand of cut for tools with thread?
    RoseBoolean tool_hand_of_cut (int ws_id, const char * &hand);

    // Coolant through tool
    RoseBoolean tool_coolant_through_tool (int ws_id, int &flag);

    // tip angle for drills
    RoseBoolean tool_tip_angle (int tl_or_ws_id, double &tool_tip_angle);
    RoseBoolean tool_tip_angle_unit (int tl_or_ws_id, const char * &tool_tip_angle);
    RoseBoolean tool_tip_angle_lower_upper (int tl_or_ws_id, double &value, double &lower, const char * &lreason, double &upper, const char *&ureason);

    // Cutting component material
    RoseBoolean tool_material (int tl_or_ws_id, const char * &standard_id, const char *&material_id);

    // Cutting component recommended feed and speed
    RoseBoolean tool_recommended_feed_speed (int tl_or_ws_id, double &feed_rate, double &spindle_speed);
    RoseBoolean tool_recommended_feed_speed_units (int tl_or_ws_id, const char * &feed_unit, const char *&speed_unit);
    RoseBoolean tool_recommended_feed_lower_upper (int tl_or_ws_id, double &value, double &lower, const char * &lreason, double &upper, const char *&ureason);
    RoseBoolean tool_recommended_speed_lower_upper (int tl_or_ws_id, double &value, double &lower, const char * &lreason, double &upper, const char *&ureason);

    // get tool id from workingstep, returns 0 if not tool found
    RoseBoolean tool_from_ws (int ws_id, int &tl_id);

    // ISO 13399 database contains numeric values and string values
    RoseBoolean tool_13399_numeric_attribute_count (int ws_id, int &count);
    RoseBoolean tool_13399_numeric_attribute_next (int ws_id, int index, const char *desired_unit, const char * &name, const char * &value, const char * &unit);

    RoseBoolean tool_13399_string_attribute_count (int ws_id, int &count);
    RoseBoolean tool_13399_string_attribute_next (int ws_id, int index, const char * &name, const char * &value);

    RoseBoolean tool_13399_organization_attributes (int ws_id, int &is_set, const char * &company_name, const char * &address1, const char * &address2);

    // return if this is a nested workplan
    RoseBoolean is_nested_workplan (int wp_id, int index, int &wp2_id,
				    const char * &name);

    RoseBoolean is_nested_selective (int wp_id, int index, int &wp_id2,
					const char * &name);
    
    // depracated for functionality in tolerance
    RoseBoolean probe_result
    (int ws_id, const char * &name, double &x, double &y, double &z,
     double &i, double &j, double &k, double &expected_value,
     double &measured_value);

    // depracated as bad style return if this is a display function
    RoseBoolean is_display_function (int wp_id, int index, int &dm_id, 
				     const char * &name, const char * &msg);
    RoseBoolean display_function (int exe_id, const char * &name, const char * &msg);

    RoseBoolean index_table (int exe_id, const char * &name, int &index_value);
    RoseBoolean extended_nc_function(int exe_id, const char * &desc);
    
    /* get a list of the faces on a workingstep feature */
    RoseBoolean first_face (int ws_id, int &size);
    RoseBoolean next_face (int ws_id, int index, int &face_id);

    RoseBoolean location (int feature_id, int &ax_id, double &x, double &y,
			  double &z);

    RoseBoolean feature_workpiece (int fea_id, int &wp_id);

//      /* closed pocket */
    RoseBoolean is_closed_pocket
    (int feature_id, int &profile_id, double &depth, 
     double &x, double &y, double &z, int &num_boss);

    RoseBoolean is_closed_rectangular_pocket
    (int feature_id, int &profile_id, double &depth, 
     double &length, double &width, 
     double &orthogonal_radius, double &x, double &y, double &z);
    
    RoseBoolean is_closed_circular_pocket
    (int feature_id, int &profile_id, double &depth, 
     double &diameter, double &x, double &y, double &z);
      RoseBoolean is_closed_path_pocket (int feature_id, int &profile_id, double &depth, 
  				double &x, double &y, double &z);

    // type of the pocket bottom
    RoseBoolean pocket_bottom_type (int feature_id, const char * &type);

    // pocket bottom (open and closed)
    RoseBoolean is_pocket_flat_bottom (int feature_id, int &bottom_id,
				       double &planar_radius);
    RoseBoolean is_pocket_radiused_bottom
    (int feature_id, int &bottom_id, double &radius, double &x, double &y,
     double &z);
    
    RoseBoolean is_pocket_through_bottom (int feature_id, int &bottom_id);

    // open pocket
    RoseBoolean is_open_pocket
    (int feature_id, int &profile_id, double &depth, 
     double &x, double &y, double &z, int &num_boss);
    
    // seems to be 224 only
    RoseBoolean is_open_rectangular_pocket (int feature_id, int &profile_id, double &depth,
					      double &length, double &width, 
					      double &orthogonal_radius, double &x, double &y, double &z);

    RoseBoolean is_open_path_pocket
    (int feature_id, int &profile_id, double &depth, 
     double &x, double &y, double &z);
    
    RoseBoolean is_open_partial_circular_pocket
    (int feature_id, int &profile_id, double &depth, 
     double &radius, double &sweep_angle, double &x, double &y, double &z);

    // slot is AP-238 and AP-224 but is read_only for the library
    RoseBoolean is_slot (int feature_id, int &profile_id, int &start_id, int &end_id, double &depth, 
					      double &x, double &y, double &z);

    RoseBoolean is_square_u_profile (int profile_id, 
	    double &width, double &first_radius, double &first_angle,
	    double &second_radius, double &second_angle);

    RoseBoolean is_rounded_u_profile (int profile_id, double &width);

    RoseBoolean is_slot_end (int end_id, const char * &type, double &first_radius, double &second_radius);

    // Chamfer is AP-238 and AP-224 but is read_only for the library
    // Chamfer is a transition feature, not a regular feature
    RoseBoolean is_chamfer (int feature_id, int &chamfer_face_id, double &first_face_offset, double &first_face_angle, 
						int &first_face_id, int &second_face_id);
    
    // Edge round is AP-238 and AP-224 but is read_only for the library
    // Edge round is a transition feature, not a regular feature
    RoseBoolean is_edge_round (int feature_id, int &edge_round_face_id, double &radius,
				   double &first_face_offset, int &first_face_id, 
				   double &second_face_offset, int &second_face_id);

    // Functions to get the edges on a face
    RoseBoolean first_face_edge_point (int face_id, int & size, double &x, double &y, double &z);
    RoseBoolean next_face_edge_point (int face_id, int index, double &x1, double &y1, double &z1, double &x2, double &y2, double &z2);
    RoseBoolean is_planar_face (int face_id, bool &is_ok, bool &is_plane, int &loop_count,
				    double &x, double &y, double &z, double &i, double &j, double &k,
				    double &a, double &b, double &c);

    // helper functions for edge round
    RoseBoolean is_cylindrical_face (int face_id, bool &is_ok, bool &is_cyl, int &loop_count,
				    double &x, double &y, double &z, double &i, double &j, double &k,
				    double &a, double &b, double &c);
    RoseBoolean is_cylindrical_edges (int face_id, double radius, bool &is_ok, double &x1, double &y1, double &z1,
					  double &x2, double &y2, double &z2, double &x3, double &y3, double &z3,
					  double &x4, double &y4, double &z4);

    // step is AP-238 and AP-224 but is read_only for the library
    RoseBoolean is_step (int feature_id, int &profile_id, double &profile_angle, double &profile_radius, double &tilt_angle,  
					      double &depth, double &x, double &y, double &z);

    /* round hole */
    RoseBoolean is_round_hole (int feature_id, int &profile_id, double &depth, 
     double &diameter, double &x, double &y, double &z);
    RoseBoolean hole_taper_angle (int hole_id, double &angle);

    RoseBoolean is_countersunk_hole (int feature_id, int &constant_hole_id,
				   int &taper_hole_id, double &x, double &y, double &z);
    RoseBoolean is_counterbore_hole (int feature_id, int &small_hole_id,
				   int &large_hole_id, double &x, double &y, double &z);

    RoseBoolean is_hole_through_bottom (int feature_id, int &bottom_id);
    RoseBoolean is_hole_flat_bottom (int feature_id, int &bottom_id);
    RoseBoolean is_hole_flat_with_radius_bottom (int feature_id, int &bottom_id, double &corner_radius);
    RoseBoolean is_hole_spherical_bottom (int feature_id, int &bottom_id,
					  double &radius);
    RoseBoolean is_hole_conical_bottom (int feature_id, int &bottom_id,
					double &tip_angle, double &tip_radius);
    
    /* outside profile */
    RoseBoolean is_outside_profile
    (int feature_id, int &path_id,
     double &depth, double &x, double &y, double &z);
    
    RoseBoolean is_rectangular_outside_profile
    (int feature_id, int &profile_id, double &depth,
     double &length, double &width, 
     double &x, double &y, double &z);

    RoseBoolean is_circular_outside_profile
    (int feature_id, int &profile_id, double &depth,
     double &diameter,  double &x, double &y, double &z);
    
    // hononym for circular outside profile except for addition of taper
    RoseBoolean is_outer_diameter (int feature_id, int &profile_id, double &depth,
						 double &diameter, 
						 double &x, double &y, double &z, double &taper);
    RoseBoolean is_closed_path_outside_profile
    (int feature_id, int &profile_id, double &depth,
     double &x, double &y, double &z);

    RoseBoolean is_open_path_outside_profile
    (int feature_id, int &profile_id, double &depth,
     double &x, double &y, double &z);
    
    RoseBoolean is_linear_outside_profile
    (int feature_id, int &profile_id, double &depth,
     double &length, double &x, double &y, double &z);
    
    RoseBoolean is_partial_circular_outside_profile
    (int feature_id, int &profile_id, double &depth,
     double &radius, double &sweep_angle,
     double &x, double &y, double &z);

    // rounded end is homonym for partial circular
    RoseBoolean is_rounded_end (int feature_id, int &profile_id, double &depth,
							 double &radius, double &sweep_angle,
							 double &x, double &y, double &z);

    // boss data from a feature or using boss_id
    RoseBoolean boss_type (int feature_id, int index, const char * &type);
    RoseBoolean is_rectangular_boss (int feature_id, int index, int &profile_id, double &height, 
			      double &length, double &width, double &x, double &y, double &z);
    RoseBoolean is_circular_boss (int feature_id, int index, int &profile_id, double &height,
			   double &diameter, double &x, double &y, double &z);
    RoseBoolean is_path_boss (int feature_id, int index, int &profile_id, double &height,
		       double &x, double &y, double &z);

    
    /* planar face */
    RoseBoolean is_planar_face (int feature_id, int &profile_id, double &depth,
				double &length, double &width, 
				double &x, double &y, double &z);

    /* planar face */
    RoseBoolean is_general_revolution (int feature_id, int &profile_id, double &radius,
							  double &x, double &y, double &z);

    // description of what is in a workplan slot- can be workingstep, workplan or NC function
    RoseBoolean operation_type (int wp_id, int index, const char * &type);

    RoseBoolean is_nc_function (int exe_id, int &flag);
    RoseBoolean is_workingstep (int exe_id, int &flag);
    RoseBoolean is_compensation_workingstep (int exe_id, int &flag);
    RoseBoolean is_probing_workingstep (int exe_id, int &flag);
    RoseBoolean is_program_structure (int exe_id, int &flag);
    RoseBoolean is_workplan (int exe_id, int &flag);
    RoseBoolean is_selective (int exe_id, int &flag);
    RoseBoolean is_workplan_with_setup (int exe_id, int &flag);
    RoseBoolean is_workplan_with_setup_and_fixture (int exe_id, int &flag);
    RoseBoolean is_workplan_with_setup_and_fixture_mount (int exe_id, int &flag);
    RoseBoolean is_workplan_with_setup_and_workpiece_mount (int exe_id, int &flag);

    // executable description
    RoseBoolean executable_type (int exe_id, const char * &type);
    RoseBoolean executable_name (int exe_id, const char * &name);
    RoseBoolean executable_container (int ws_id, int &wp_id);

    // description of what is in a workingstep
    RoseBoolean workingstep_type (int ws_id, const char * &type);

    // description of operation parameters
    RoseBoolean milling_type (int ws_id, const char * &type);
    RoseBoolean turning_type (int ws_id, const char * &type);
    RoseBoolean is_finish_or_rough (int ws_id, int &is_finish, int &is_rough);


    // description of milling parameters
    RoseBoolean milling_parameters (int ws_id, double &bottom_allowance,
			     double &side_allowance,
			     double &axial_depth, double &radial_depth);
 

    // return milling parameters if any
    RoseBoolean is_freeform_milling_operation (int ws_id, int &is_milling);

    // return milling parameters if any
    RoseBoolean is_planar_milling_operation
    (int ws_id, int &is_milling, 
     int &is_rough, double &bottom_allowance, double &axial_depth);

    // return milling parameters if any
    RoseBoolean is_bottom_and_side_milling_operation
    (int ws_id, int &is_milling, 
     int &is_rough, double &bottom_allowance, double &side_allowance,
     double &axial_depth, double &radial_depth);

    // return milling parameters if any
    RoseBoolean is_side_milling_operation
    (int ws_id, int &is_milling, 
     int &is_rough, double &side_allowance,
     double &axial_depth, double &radial_depth);

    // return drilling parameters if any
    RoseBoolean is_drilling_operation
    (int ws_id, int &is_drilling, 
     double &cutting_depth, double &dwell_time_bottom, double &feed_on_retract,
     double &previous_diameter);

    // return multistep drilling parameters if any
    RoseBoolean is_multistep_drilling_operation
    (int ws_id, int &is_multistep_drilling, 
     double &cutting_depth, double &dwell_time_bottom, double &feed_on_retract,
     double &previous_diameter, double &depth_of_step, double &first_depth,
     double &retract_distance, double &dwell_time_step);
    
    // return tapping parameters if any
    RoseBoolean is_tapping_operation
    (int ws_id, int &is_tapping, double &cutting_depth, 
     int &compensation_chuck_required,
     double &dwell_time_bottom, double &feed_on_retract,
     double &previous_diameter);

    // return boring parameters if any
    RoseBoolean is_boring_operation
    (int ws_id, int &is_boring, double &cutting_depth,
     double &dwell_time_bottom, double &feed_on_retract,
     double &previous_diameter, double &waiting_x, double &waiting_y,
     double &waiting_z, double &depth_of_test_cut);

    // return reaming parameters if any
    RoseBoolean is_reaming_operation
    (int ws_id, int &is_reaming,
     double &cutting_depth, double &dwell_time_bottom, double &feed_on_retract,
     double &previous_diameter, double &waiting_x, double &waiting_y,
     double &waiting_z, double &depth_of_test_cut);

    // return contouring turning parameters if any
    RoseBoolean is_contouring_operation (int ws_id, int &is_turning, 
					       int &is_rough, double &allowance);

    // spindle speed, feed for a workingstep operation
    RoseBoolean feed_speed (int ws_id, double &feed, double &speed);
    RoseBoolean feed_speed_unit (int ws_id, const char * &feed_unit, const char * &speed_unit);

    // CSS versions must be used if CSS speed
    RoseBoolean feed_is_css (int ws_id, int &flag);
    RoseBoolean feed_speed_css (int ws_id, double &feed, double &speed, double &max);
    RoseBoolean feed_speed_css_unit (int ws_id, const char * &feed_unit, const char * &speed_unit, const char * &max_unit);

    // spindle speed, feed and coolant for a workingstep operation
    RoseBoolean coolant (int ws_id, const char * &coolant);
    
    // security plane Z value
    RoseBoolean security_plane (int ws_id, double &z_value);

    // retract plane value
    RoseBoolean retract_plane (int ws_id, double &value);

    // rawpiece parameters
    RoseBoolean is_block_workpiece
    (int wp_id, int &flag, double &x, double &y, double &z,
     double &length, double &width, double &height);
    
    RoseBoolean is_shape_workpiece
    (int wp_id, int &flag, double &x, double &y, double &z,
     double &length, double &width, double &height);

    RoseBoolean is_cylinder_workpiece
    (int wp_id, int &flag, double &x, double &y, double &z,
     double &length, double &diameter);

    // some CAM systems cannot process cylinder workpieces
    RoseBoolean is_cylinder_as_block_workpiece
    (int wp_id, int &flag, double &x, double &y, double &z,
     double &length, double &width, double &height);

    // material returns the main (or first) material, count and index allow access to the alternates
    RoseBoolean material (int wp_id, const char * &name);
    RoseBoolean material_count (int &count);
    RoseBoolean material_index (int index, const char * &name, int &wp_id);

    // traverse all the workpieces
    RoseBoolean workpiece_count (int &count);
    RoseBoolean workpiece_next (int index, int &wp_id);
    RoseBoolean workpiece_any_name (int wp_id, const char * &name);
    RoseBoolean workpiece_any_units (int wp_id, const char * &name);
    RoseBoolean workpiece_any_classification (int wp_id, const char * &name);

    // Children subassemblies
    RoseBoolean workpiece_immediate_sub_assembly_count (int wp_id, int &count);
    RoseBoolean workpiece_immediate_sub_assembly_next (int wp_id, int index, int &sub_id);

    // is a piece an assembly or a primitive part
    RoseBoolean workpiece_assembly_count (int wp_id, int &count);
    RoseBoolean workpiece_assembly_next (int wp_id, int index, int &sub_id);

    // the products list in the project
    RoseBoolean finalpiece_count (int &count);
    RoseBoolean finalpiece_next (int index, int &wp_id);

    // generic functions for workpiece that do not get data from the project
    RoseBoolean workpiece_of_workplan_count (int plan_id, const char *&name, int &count);
    RoseBoolean workpiece_of_workplan_next (int plan_id, int index, int &wp_id, 
							double &x, double &y, double &z,
							double &i, double &j, double &k,
							double &a, double &b, double &c); 
    RoseBoolean rawpiece_of_workpiece (int wp_id, int &rwp_id);

    RoseBoolean asis_of_main (int &wp_id);
    RoseBoolean tobe_of_main (int &wp_id);
    RoseBoolean delta_of_main (int &wp_id);
    RoseBoolean fixture_of_main (int &wp_id);

    // product id's for workingstep as-is, to-be and removal models
    RoseBoolean executable_as_is_workpiece (int ws_id, int &wp_id);
    RoseBoolean executable_to_be_workpiece (int ws_id, int &wp_id);
    RoseBoolean executable_removal_workpiece (int ws_id, int &wp_id);
    RoseBoolean executable_fixture_workpiece (int ws_id, int &wp_id);

    // product id's for workpieces actually defined on this executable
    RoseBoolean local_executable_as_is_workpiece (int ws_id, int &wp_id);
    RoseBoolean local_executable_to_be_workpiece (int ws_id, int &wp_id);
    RoseBoolean local_executable_removal_workpiece (int ws_id, int &wp_id);
    RoseBoolean local_executable_fixture_workpiece (int ws_id, int &wp_id);

    // functions to find all features
    RoseBoolean first_feature (int &feature_id, int & size);
    RoseBoolean next_feature (int &feature_id, int index);

    RoseBoolean ws_process_feature (int ws_id, int &fe_id);
    RoseBoolean ws_final_feature_count (int ws_id, int &size);
    RoseBoolean ws_final_feature_next (int ws_id, int index, int &fe_id);

    RoseBoolean wp_process_feature_count (int wp_id, int &size);
    RoseBoolean wp_process_feature_next (int wp_id, int index, int &fe_id);

    RoseBoolean wp_final_feature_count (int wp_id, int &size);
    RoseBoolean wp_final_feature_next (int wp_id, int index, int &fe_id);

    // find workplans that contain an executable - workplans must be connected to main_workplan
    RoseBoolean navigate_executable_to_workplan_count (int ex_id, int &count);
    RoseBoolean navigate_executable_to_workplan_next (int ex_id, int index, int &wp_id);

    // functions to find all drill points in a pattern
    RoseBoolean first_drill_point (int feature_id, int &size, double &x, double &y, double &z);
    RoseBoolean next_drill_point (int feature_id, unsigned index, double &x,
				  double &y, double &z);
    
    // functions to find all feature in a compound feature
    RoseBoolean first_feature_in_compound (int compound_id, int &feature_id, int &size, double &x, double &y, double &z);
    RoseBoolean next_feature_in_compound (int compound_id, int index, int &feature_id);
    
    // description of a feature
    RoseBoolean feature_type (int ws_id, const char * &type);

    // description of a bottom
    RoseBoolean hole_bottom_type (int feature_id, const char * &type);

    // placement (location, direction, ref_direction) of a feature
    RoseBoolean placement (int feature_id, double &x, double &y, double &z, 
		    double &i, double &j, double &k,
		    double &a, double &b, double &c);
    
    // number of bosses on feature 0 if feature does not have bosses
    RoseBoolean number_of_bosses (int ws_id, int &number);

    // number of bosses on feature 0 if feature does not have bosses
    RoseBoolean feature_depth (int ws_id, double &depth);
 
    // id of the boundary profile if it has one 0 otherwise
    RoseBoolean feature_path_profile (int ws_id, int &profile_id);
 
    // z_coordinate of profile does some checking to make sure all Z's are same
    RoseBoolean profile_z_coordinate (int profile_id, double &z_value);
 
    // feature id 
    RoseBoolean feature_id (int ws_id, int &feature_id);   

    // feature its_id()
    RoseBoolean feature_name (int ws_or_fe_id, const char * &name);

    // flag set in some AP-224 features to show profile at the other end
    RoseBoolean is_profile_at_start (int feature_id, int &profile_at_start);

    // flag set to show measurements are at other end
    RoseBoolean is_profile_at_end (int feature_id, int &profile_at_end);

    // direction vector on the linear path for an entity
    RoseBoolean path_direction (int ws_id, int &path_id, double &i, double &j, double &k);

    // find technology by value
    RoseBoolean technology_by_value (int &tech_id, double feed_value, double speed_value);

    // number of technologies
    RoseBoolean technology_count (int &count);
    RoseBoolean next_technology (int index, int &id, double &feed, double &speed);

    // by workingstep
    RoseBoolean ws_technology_next (int ws_id, int index, int &tech_id);
    RoseBoolean ws_technology_count (int ws_id, int &count);

    // inverses tech to we
    RoseBoolean technology_ws_count (int tech_id, int &count);
    RoseBoolean technology_ws_next (int tech_id, int index, int &ws_id);

    // default technology for paths without any defined
    RoseBoolean ws_technology_default (int ws_id, int &tech_id);

    // by workplan
    RoseBoolean wp_technology_count (int wp_id, int &count);
    RoseBoolean wp_technology_next (int wp_id, int index, int &tech_id);

    // by workplan or workingstep
    RoseBoolean executable_technology_count (int exe_id, int &count);
    RoseBoolean executable_technology_next (int exe_id, int index, int &tech_id);

    // by tool
    RoseBoolean tool_technology_count (int tl_id, int &count);
    RoseBoolean tool_technology_next (int tl_id, int index, int &tech_id);

    // set surface property of workingstep or workpiece
    RoseBoolean surface_property_workingstep (int ws_id, const char * &val);
    RoseBoolean surface_property_workpiece (const char * &val);

    // machine parameters required by a workplan
    RoseBoolean feed_speed_machine_parameters (int wp_id, double &feed, double &spindle_power, 
						   double &spindle_speed, double &spindle_torque);

    RoseBoolean feed_speed_machine_parameters_units (int wp_id, const char * &feed_unit, const char * &spindle_power_unit, 
						   const char * &spindle_speed_unit, const char * &spindle_torque_unit);

    // get the name of the machine assigned to a workplan (using backdoor)
    RoseBoolean machine_name (int wp_id, const char * &name);

    // compute the feed time for the tool paths in an executable using best feed (regular or override)
    RoseBoolean compute_best_feed_time (int exe_id, double &distance, double &base_time, double &over_time, const char * &dist_unit, const char * &time_unit);

    // Strategy parameters for NIST project starting in July 08
    RoseBoolean drilling_strategy (int ws_id, int &has_strategy, double &reduced_cut_at_start, 
				double &reduced_feed_at_start, double &depth_of_start, 
				double &reduced_cut_at_end, double &reduced_feed_at_end, double &depth_of_end);

    RoseBoolean approach_plunge_toolaxis_strategy (int ws_id, int &has_strategy);
    RoseBoolean retract_plunge_toolaxis_strategy (int ws_id, int &has_strategy);
    RoseBoolean approach_plunge_ramp_strategy (int ws_id, int &has_strategy, double &angle);
    RoseBoolean retract_plunge_ramp_strategy (int ws_id, int &has_strategy, double &angle);
    RoseBoolean approach_plunge_zigzag_strategy (int ws_id, int &has_strategy, double &angle, double &width);
    RoseBoolean retract_plunge_zigzag_strategy (int ws_id, int &has_strategy, double &angle, double &width);
    RoseBoolean approach_plunge_helix_strategy (int ws_id, int &has_strategy, double &radius, double &angle);
    RoseBoolean retract_plunge_helix_strategy (int ws_id, int &has_strategy, double &radius, double &angle);

    RoseBoolean approach_air_retract_angle_strategy (int ws_id, int &has_strategy, double &angle, double &travel_length);
    RoseBoolean retract_air_retract_angle_strategy (int ws_id, int &has_strategy, double &angle, double &travel_length);
    RoseBoolean approach_air_retract_tangent_strategy (int ws_id, int &has_strategy, double &radius);
    RoseBoolean retract_air_retract_tangent_strategy (int ws_id, int &has_strategy, double &radius);

    RoseBoolean center_milling_strategy (int ws_id, int &has_strategy);
    RoseBoolean explicit_milling_strategy (int ws_id, int &has_strategy);
    RoseBoolean contour_spiral_milling_strategy (int ws_id, int &has_strategy, const char *&cutmode, const char *&rot_direction);
    RoseBoolean contour_parallel_milling_strategy (int ws_id, int &has_strategy, const char *&cutmode, const char *&rot_direction);
    RoseBoolean contour_bidirectional_milling_strategy (int ws_id, int &has_strategy, const char *&spiral_cutmode, 
	double &fi, double &fj, double &fk, const char *&rot_direction, const char * &stepover_direction);
    RoseBoolean bidirectional_milling_strategy (int ws_id, int &has_strategy, double &fi, double &fj, double &fk,
	const char *&stepover_direction, const char *&connection_strategy);
    RoseBoolean bidirectional_contour_milling_strategy (int ws_id, int &has_strategy, const char *&spiral_cutmode, double &fi, double &fj, double &fk,
	const char *&rot_direction, const char * &stepover_direction);
    RoseBoolean unidirectional_milling_strategy (int ws_id, int &has_strategy, const char *&cutmode, double &fi, double &fj, double &fk);

    // so we can use finder to format data
    RoseBoolean save_file (const char * filename, RoseBoolean asModules);

    // for navigating between designs connected by the cursor
    RoseBoolean has_left (int &flag);
    RoseBoolean has_right (int &flag);
    RoseBoolean go_left (int &flag);
    RoseBoolean go_right (int &flag);
    RoseBoolean cursor_count (int &size);
    RoseBoolean cursor_index (int &index);
    RoseBoolean cursor_move_to (int &flag, int index);
    RoseBoolean cursor_design_name_at (int index, const char * &name);
    RoseBoolean cursor_design_modified_at (int index, int &flag);

    // XML generators
    RoseBoolean project_xml (FILE *file);
    RoseBoolean workplan_xml (Workplan *wp, FILE *file);
    RoseBoolean selective_xml (Selective *sl, FILE *file);
    RoseBoolean workingstep_xml (Machining_workingstep *ws, FILE *file);
    RoseBoolean tool_xml (Machining_tool_IF *tool,FILE *file);
    RoseBoolean operation_xml (Operation_IF *op, FILE *file);
    RoseBoolean feature_xml (Manufacturing_feature_IF *fe, FILE *file);
    RoseBoolean profile_xml (Profile_IF *profile, FILE *file);

private:



//    RoseDesign * des;
//    Project * pject;
//    int pject_design_counter;
    RoseUnit geometry_context;

    // NEEDS TO BE GLOBAL SO ALL INSTANCES OF FINDER DO THE SAME THING
    // transform tool paths using stix transform or not
    static RoseBoolean use_stix_transform_flag;

    // see if can find feature from Workingstep
    RoseObject * step_to_feature (RoseObject * obj);
    RoseObject * step_to_boss (RoseObject * obj, int index);
    stp_machining_technology* get_tech_of_op (RoseObject *path);
    stp_machining_functions* get_funs_of_op (RoseObject *path);

    // function to decode meaning of an operation
    RoseBoolean operation_decode (RoseObject *obj, const char * &type);

    // functions for scoping current workpieces
    RoseBoolean executable_workpieces ();
    RoseBoolean workplan_workpieces (Workplan *plan, RoseObject *asis, RoseObject *tobe, RoseObject *delta, RoseObject *fix);
    RoseBoolean selective_workpieces (Selective *plan, RoseObject *asis, RoseObject *tobe, RoseObject *delta, RoseObject *fix);
    void find_first_workplan_workpiece (Workplan *plan, RoseObject * &as_is); 
    void find_last_workplan_workpiece (Workplan *plan, RoseObject * &to_be);
    void find_first_selective_workpiece (Selective *plan, RoseObject * &as_is); 
    void find_last_selective_workpiece (Selective *plan, RoseObject * &to_be);
    ListOfInteger asis_id;
    ListOfInteger tobe_id;
    ListOfInteger delta_id;
    ListOfInteger fix_id;
    ListOfInteger workpieces_id;
    int workpieces_design_counter;

    // workpiece traversal functions for find_count and find_next
    void internal_workpiece ();
    ListOfInteger workpiece_iterator;
    ListOfString workpiece_class_iterator;
    int workpiece_counter;

    // traversal functions for assembly management
    void internal_workpiece_assembly (Workpiece *piece);
    ListOfInteger workpiece_assembly_iterator;
    int workpiece_assembly_signature;	   
    int workpiece_assembly_design_counter;

    // workplan traversal functions for find_count and find_next
    void internal_wp_tool (Workplan *wp, ListOfInteger &tool_bag);
    void internal_sl_tool (Selective *sl, ListOfInteger &tool_bag);
    ListOfInteger wp_tool_iterator;
    int wp_tool_signature;
    int wp_tool_counter;

    // traversal functions for find_similar_tool_count and find_similar_tool_next
    ListOfInteger similar_tool_iterator;
    int similar_tool_signature;
    int similar_tool_counter;

    void internal_wp_process_feature (Workplan *wp, ListOfInteger &feature_bag);
    void internal_sl_process_feature (Selective *sl, ListOfInteger &feature_bag);
    ListOfInteger wp_process_iterator;
    int wp_process_signature;
    int wp_process_counter;

    void internal_wp_final_feature (Workplan *wp, ListOfInteger &feature_bag);
    void internal_sl_final_feature (Selective *sl, ListOfInteger &feature_bag);
    ListOfInteger wp_final_iterator;
    int wp_final_signature;
    int wp_final_counter;

    // cache function works in both directions tech -> ws, ws ->tech
    void internal_ws_technology ();
    int ws_technology_counter;
    ListOfInteger technology_iterator;

    void internal_wp_technology (Workplan *wp);
    void internal_sl_technology (Selective *sl);
    int wp_technology_counter;
    int wp_technology_signature;
    ListOfInteger wp_technology_iterator;

    void internal_tool_technology (Machining_tool_IF *tl);
    int tool_technology_counter;
    int tool_technology_signature;
    ListOfInteger tool_technology_iterator;

    // cache functions for ISO 13399 tool data
    void internal_iso13399_attributes (int ws_id);
    ListOfRoseObject iso13399_numeric_attribute;
    ListOfRoseObject iso13399_string_attribute;
    RoseUnit iso13399_desired_unit;
    int iso13399_signature;

    void internal_executable_to_workplan (Workplan *wp, Executable_IF *ex);
    void internal_executable_to_workplan (Selective *sl, Executable_IF *ex);
    ListOfInteger executable_to_workplan_iterator;
    int executable_to_workplan_signature;
    int executable_to_workplan_counter;

    // used in recursive descents to find faces
    RoseBoolean internal_workplan_face_count (int wp_id, int &size);
    RoseBoolean internal_workplan_face_next (int wp_id, int index, int &face_id);
    ListOfInteger workplan_face_iterator;
    int workplan_face_signature;
    int workplan_face_counter;
    void internal_workplan_face (Workplan * wp, ListOfInteger &face_bag);
    void internal_selective_face (Selective * sl, ListOfInteger &face_bag);

    RoseBoolean internal_workingstep_face_count (int ws_id, int &size);
    RoseBoolean internal_workingstep_face_next (int ws_id, int index, int &face_id);
    ListOfInteger workingstep_face_iterator;
    int workingstep_face_signature;
    int workingstep_face_counter;
    void internal_workingstep_face (Machining_workingstep *ws, ListOfInteger &face_bag);

    // cache the polylines as quickly as possible for a new path to reduce searches
    void center_path_cache (Cutter_location_trajectory *center);

    int current_path_id;
    int current_path_is_main_case;
    int current_path_poly_size;

    int last_next_point_curve_id;
    stp_polyline *last_next_point_poly;

    int last_next_axis_curve_id;
    stp_polyline *last_next_axis_poly;

    int last_next_area_curve_id;
    stp_polyline *last_next_area_poly;

    int last_next_override_curve_id;
    stp_polyline *last_next_override_poly;

    int last_next_point_id_curve_id;
    stp_polyline *last_next_point_id_poly;

    int last_next_direction_curve_id;
    stp_polyline *last_next_direction_poly;

    // executable times and distance
    RoseBoolean compute_best_feed_time (Machining_tool_IF *tl, double &distance, double &base_time, double &over_time, 
					    const char * &dist_unit, const char * &time_unit);
    RoseBoolean compute_best_feed_time (Workplan *wp, double &distance, double &base_time, double &over_time, 
					    const char * &dist_unit, const char * &time_unit);
    RoseBoolean compute_best_feed_time (Selective *sl, double &distance, double &base_time, double &over_time, 
					    const char * &dist_unit, const char * &time_unit);
    RoseBoolean compute_best_feed_time (Machining_workingstep *ws, double &distance, double &base_time, double &over_time, 
					    const char * &dist_unit, const char * &time_unit);
    RoseBoolean compute_best_feed_time (Trajectory_IF *path, Machining_workingstep *ws, double &distance, double &base_time, double &over_time, 
					    const char * &dist_unit, const char * &time_unit);


};

RoseBoolean feature_type_name (RoseObject * obj, const char * &type);



#endif

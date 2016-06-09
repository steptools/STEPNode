/* $RCSfile: Cursor.h,v $
 * $Revision: 1.37 $ $Date: 2016/06/07 20:24:07 $
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
 * Header for Cursor class - this class used to find points and traverse toolpaths
 */

#ifndef cursor_h
#define cursor_h

#include "Project.h"
#include "Workplan.h"
#include "Machining_workingstep.h"
#include "Trajectory_IF.h"

#include "Trace.h"
#include <stp_schema.h>
#include <rose_xform.h>

class cursor
{

    TraceContext tc;
    
public:

    cursor ();
    ~cursor ();

    // important current variables
    char url[300];

    RoseDesign * des;
    Project *pj;
    Workplan * wp;
    Selective * sl;
    Machining_workingstep * ws;
    Machining_operation_IF *op;
    Trajectory_IF *tp;

    int found_styled_orphans;
    int saved_styled_orphans;

    // list of cursors in memory
    cursor *left;
    cursor *right;

    RoseBoolean search (int &flag, const char * name);
    RoseBoolean new_search (int &flag, const char * name);

    RoseBoolean reset ();

    /* decide if there is data in the project */
    RoseBoolean project_has_data ();

    // trace processing of data
    RoseBoolean trace_processing ();
    RoseBoolean no_trace_processing ();

    // use or ignore workingstep placement transform
    RoseBoolean use_placements ();
    RoseBoolean ignore_placements ();

    // use or ignore workplan setup transform
    RoseBoolean use_setups ();
    RoseBoolean ignore_setups ();

    // use or ignore STEP-NC Explorer enabled selections 
    RoseBoolean use_enableds ();
    RoseBoolean ignore_enableds ();

    // set cursor to start of main workplan
    RoseBoolean main ();

    // start cursor at a workplan, workingstep or toolpath
    RoseBoolean find_workplan (int &flag, const char *name);
    RoseBoolean find_workingstep (int &flag, const char *name);
    RoseBoolean find_workingstep_in_workplan (int &flag, const char *name);
    RoseBoolean find_toolpath (int &flag, const char *name);
    RoseBoolean find_toolpath_in_workingstep (int &flag, const char *name);
    RoseBoolean find_toolpath_in_workplan (int &flag, const char *name);

    // start cursor at a point
    RoseBoolean find_tolerance (double value);
    RoseBoolean find_xyz (int &flag, int &visits, int limit, double x, double y, double z);
    RoseBoolean find_xyz_in_toolpath (int &flag, int &visits, int limit, double x, double y, double z);
    RoseBoolean find_xyz_in_workingstep (int &flag, int &visits, int limit, double x, double y, double z);
    RoseBoolean find_xyz_in_workplan (int &flag, int &visits, int limit, double x, double y, double z);

    // find using a distance (path length)
    RoseBoolean find_d (int &flag, int &visits, int limit, double distance, double &last_computed_distance);
    RoseBoolean find_d_in_toolpath (int &flag, int &visits, int limit, double distance, double &last_computed_distance);
    RoseBoolean find_d_in_workingstep (int &flag, int &visits, int limit, double distance, double &last_computed_distance);
    RoseBoolean find_d_in_workplan (int &flag, int &visits, int limit, double distance, double &last_computed_distance);

    RoseBoolean current_workplan_name (const char * &name);
    RoseBoolean current_workingstep_name (const char * &name);
    RoseBoolean current_toolpath_name (const char * &name);

    // move to next point in program
    RoseBoolean next_point (int &flag);
    RoseBoolean next_point_in_toolpath (int &flag);
    RoseBoolean next_point_in_workingstep (int &flag);
    RoseBoolean next_point_in_workplan (int &flag);
    
    // other moves
    RoseBoolean next_toolpath (int &flag);
    RoseBoolean next_toolpath_in_workingstep (int &flag);
    RoseBoolean next_workingstep (int &flag);
    RoseBoolean next_workingstep_in_workplan (int &flag);

    // unit for XYZ values
    RoseBoolean get_length_unit (int &flag, const char *&length_unit);

    // get values at current point
    RoseBoolean get_xyz (int &flag, double &x, double &y, double &z);
    RoseBoolean get_ijk (int &flag, double &i, double &j, double &k);

    // get cross section data
    RoseBoolean get_cross_section (int &flag, const char * &type, double &Crs_area, double &RD_max, double &AD_max, double &RD_X_offset, double &RD_Y_offset, double &CG_X_offset, double &CG_Y_offset);

    RoseBoolean put_cross_section (int &flag, int line_num, double Crs_area, double RD_max, double AD_max, double RD_X_offset, double RD_Y_offset, double CG_X_offset, double CG_Y_offset);
    RoseBoolean put_cross_section_air_milling (int &flag);
    RoseBoolean put_cross_section_exceeds_limits (int &flag);

    RoseBoolean clear_workingstep_cross_section_data (Machining_workingstep *ws);

    // Feed override data
    RoseBoolean get_feed_speed_override (int &flag, double &override);
    RoseBoolean put_feed_speed_override (int &flag, double override);

    // curve axial depth data
    RoseBoolean put_axial_depth_override (int &flag, double override);
    RoseBoolean get_axial_depth_override (int &flag, double &override);

    // curve axial depth data
    RoseBoolean put_radial_overcut_override (int &flag, double override);
    RoseBoolean get_radial_overcut_override (int &flag, double &override);

    RoseBoolean is_contact (int &flag);
    RoseBoolean is_center (int &flag);

    RoseBoolean is_arc (int &flag);
    RoseBoolean is_line (int &flag);
    RoseBoolean is_helix (int &flag);

    RoseBoolean is_via_arc (int &flag);
    RoseBoolean is_via_helix (int &flag);

    RoseBoolean is_full_circle (int &flag);
    RoseBoolean is_full_helix (int &flag);

    RoseBoolean is_via_full_circle (int &flag);
    RoseBoolean is_via_full_helix (int &flag);

    RoseBoolean get_arc (int &flag, int &ccw, double &radius, double &cx, double &cy, double &cz);
    RoseBoolean get_helix (int &flag, int &ccw, double &radius, double &cx, double &cy, double &cz, double &depth);

    RoseBoolean is_rapid (int &flag);
    RoseBoolean get_feed (int &flag, double &feed, const char *&feed_unit);
    RoseBoolean get_speed (int &flag, double &speed, const char *&speed_unit);

    RoseBoolean put_feed (int &flag, double feed);
    RoseBoolean put_feed_in_workingstep (int &flag, double feed);
    RoseBoolean put_feed_in_project (int &flag, double speed);

    RoseBoolean put_speed (int &flag, double speed);
    RoseBoolean put_speed_in_workingstep (int &flag, double speed);
    RoseBoolean put_speed_in_project (int &flag, double speed);

    RoseBoolean get_axial_depth (int &flag, double &depth, const char *&depth_unit);
    RoseBoolean put_axial_depth (int &flag, double depth);

    RoseBoolean get_radial_overcut (int &flag, double &overcut, const char *&overcut_unit);
    RoseBoolean put_radial_overcut (int &flag, double overcut);

    RoseBoolean get_tool_number (int &flag, const char *&number);
    RoseBoolean get_tool_usage (int &flag, const char *&usage);

    RoseBoolean get_tool_length (int &flag, double &length, const char *&length_unit);
    RoseBoolean get_tool_diameter (int &flag, double &diameter, const char *&diameter_unit);
    RoseBoolean get_tool_radius (int &flag, double &radius, const char *&radius_unit);

    RoseBoolean put_tool_usage (int &flag, const char *usage);
    RoseBoolean put_tool_length (int &flag, double length);
    RoseBoolean put_tool_diameter (int &flag, double diameter);
    RoseBoolean put_tool_radius (int &flag, double radius);

    /* Save stepfile */
    RoseBoolean save_file (int &flag, const char * fileName, RoseBoolean asModules = ROSE_TRUE);

    /* save current address */
    RoseBoolean save_strl (int &flag, const char *file_name);
    RoseBoolean open_strl (int &flag, const char * file_name);
    RoseBoolean create_strl (int &flag, const char *&result);

    void save_with_strl ( RoseDesign *des, 
			    Workplan *wp, Selective *sl, Machining_workingstep *ws, Trajectory_IF *tp, double distance,
			    RoseBoolean asModules);


    // Make STRL
    void create_strl_for_position ( 
	const char *path, 
	Workplan *wp, Selective *sl, 
	Machining_workingstep *ws, 
	Trajectory_IF *tp, 
	double distance,
	const char * &result
	);
    char *make_strl_query_part (Workplan *wp, Selective *sl, Machining_workingstep *ws, Trajectory_IF *tp, double distance);

    RoseBoolean decode_strl ();
    RoseBoolean decode_strl_query (const char *buf);
    RoseBoolean has_strl ();

    Workplan *current_strl_wp ();
    Selective *current_strl_sl ();
    Machining_workingstep *current_strl_ws ();
    Trajectory_IF *current_strl_tp ();
    double current_strl_pt ();

    int current_workplan_id ();
    int current_selective_id ();
    int current_workingstep_id ();
    int current_toolpath_id ();

    void set_current_url (const char * url);
    void set_current_strl_wp (Workplan *wp);
    void set_current_strl_sl (Selective *sl);
    void set_current_strl_ws (Machining_workingstep *ws);
    void set_current_strl_tp (Trajectory_IF *tp);
    void set_current_strl_pt (double pt);

    void workplan_stack_push ();
    void workplan_stack_pop ();
    void workplan_stack_reset ();
    RoseBoolean workplan_stack_ok ();
    RoseBoolean workplan_stack_empty ();

    RoseBoolean read_cross_section_data (int &flag, const char *file_name, int exe_id); 
    RoseBoolean optimize_using_cross_section_data (int &flag, int exe_id, double Fmax, int set_override);


private:

    int wp_index;
    int wp_limit;

    int tp_index;
    int tp_limit;

    stp_cartesian_point *pt;

    RoseObject * basic_curve;
    stp_polyline * poly;

    int pt_index;
    int pt_limit;

    RoseObject * composite_base;
    int composite_index;
    int composite_limit;

    stp_polyline * axis_poly;
    stp_polyline * axis_friend;

    stp_polyline * cross_poly;
    stp_polyline * cross_friend;

    stp_polyline * over_poly;
    stp_polyline * over_friend;

    stp_polyline * axial_poly;
    stp_polyline * axial_friend;

    stp_polyline * radial_poly;
    stp_polyline * radial_friend;

    RoseObject * wp_stack[100];
    int wp_index_stack[100];
    int wp_stack_count;
    int wp_stack_limit;

    Workplan *get_next_wp ();
    Machining_workingstep *get_next_ws ();
    Trajectory_IF *get_next_tp ();
    stp_cartesian_point *get_next_pt ();

    RoseBoolean find_ws_of_tp ();

    RoseBoolean get_next_after_via ();
    RoseBoolean get_via_arc (int &flag, int &ccw, double &radius, double &cx, double &cy, double &cz);
    RoseBoolean get_via_helix (int &flag, int &ccw, double &radius, double &cx, double &cy, double &cz, double &depth);

    RoseBoolean get_raw_ijk (int &flag, double &x, double &y, double &z);

    FILE * open_cross_section_file (const char *cross_file_name, int &first_line_number);

    stp_bounded_curve *initialize_crosses (stp_bounded_curve *curve);
    RoseDesign *none_des;
    stp_cartesian_point *none_cross;
    RoseDesign *air_des;
    stp_cartesian_point *air_cross;
    RoseDesign *exceeds_des;
    stp_cartesian_point *exceeds_cross;

    stp_bounded_curve *initialize_overrides (stp_bounded_curve *curve);
    RoseDesign *none_over_des;
    stp_cartesian_point *none_over;

    stp_bounded_curve *initialize_axials (stp_bounded_curve *curve);
    RoseDesign *none_axial_des;
    stp_cartesian_point *none_axial;

    stp_bounded_curve *initialize_radials (stp_bounded_curve *curve);
    RoseDesign *none_radial_des;
    stp_cartesian_point *none_radial;

    RoseBoolean use_setup_flag;
    RoseBoolean use_placement_flag;
    RoseXform wp_placement;
    RoseXform ws_placement;

    RoseBoolean use_enabled_flag;
    RoseBoolean trace_processing_flag;

    RoseXform get_setup (Workplan *wp);

    // tolerance for find functions
    double tol;

    RoseBoolean single_step;
    RoseBoolean single_plan;
    RoseBoolean single_path;

    // flag to visit first point in a new path
    RoseBoolean very_first;

    // STRL resource locators
    double rl_pt_count;

    Workplan * strl_wp;
    Selective * strl_sl;
    Machining_workingstep * strl_ws;
    Trajectory_IF *strl_tp;
    double strl_pt;
    };

#endif



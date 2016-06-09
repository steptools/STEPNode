/* $RCSfile: Tolerance.h,v $
 * $Revision: 1.115 $ $Date: 2016/06/07 21:01:43 $
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
 * Header for Tolerance maker
 * This class is modal
 */

#ifndef tolerance_h
#define tolerance_h

#include <rose.h>
#include <stp_schema.h>

// utilty functions
#include "Units.h"
#include "Geometry.h"
#include "Contexts.h"
#include "Trace.h"

// GL graphics functions
#include <rose_bounds.h>

// ARM objects
#include "Workpiece.h"
#include "Datum_reference.h"
#include "Position_tolerance.h"
#include "Diameter_size_dimension.h"
#include "Touch_probe.h"

// Non AP ARM objects
#include "Scra_feature_face.h"
#include "Datum_defined_by_feature.h"

#include "Cache_manager.h"


#include "APT.h"


// module files
//#include "register.h"

#include "ap238_Reader.h"
#include "ap224_Reader.h"

/* This is in stix.h as 1e-15 -- could be a problem */
#define TOL_EPSILON 1e-3

#define TOL_FLOAT_EQUAL(a,b)           TOL_FLOAT_ZERO((a)-(b))
#define TOL_FLOAT_NOT_EQUAL(a,b)       TOL_FLOAT_NOT_ZERO((a)-(b))
#define TOL_FLOAT_ZERO(a)              (fabs(a) < TOL_EPSILON)
#define TOL_FLOAT_NOT_ZERO(a)          (fabs(a) > TOL_EPSILON)


class tolerance
{
    TraceContext tc;
	
public:

    tolerance (apt2step *the_apt);
    ~tolerance ();
    RoseBoolean reset ();
    RoseBoolean tool_reset ();
    RoseBoolean tolerance_reset ();

    // temp
    void test_spline_curves ();
    void test_spline_surfaces ();

    RoseBoolean tolerance_on (int &flag);

    // switch between probing along surface normal or probing using x, y, z
    RoseBoolean fix_z_axis ();
    RoseBoolean use_normal ();
    RoseBoolean use_x_or_y_axis();
    RoseBoolean use_x_and_y_axis();

    // switch between using clear for start and end point and clear for every point
    RoseBoolean clear_at_start_and_end ();
    RoseBoolean clear_every_time ();

    // switch run time monitoring of tool status on and off
    RoseBoolean compute_tool_advice_on ();
    RoseBoolean compute_tool_advice_is_on (int &flag);
    RoseBoolean compute_tool_advice_off ();

    // set start and clearance values for probing
    RoseBoolean probe_start_and_clear (double start, double clear);

    // set start and clearance values for probing
    RoseBoolean probe_delta_u_and_v (double du, double dv);

    RoseBoolean feature_count (int &size);
    RoseBoolean feature_next (int index, int &fe_id);

    RoseBoolean feature_face_count (int fe_id, int &size);
    RoseBoolean feature_face_next (int fe_id, int index, int &face_id);

    // build shape aspect containing a set of faces for tolerancing
    RoseBoolean basic_callout (int face_id, int &call_id);
    RoseBoolean apex_callout (int face_id, int &call_id);
    RoseBoolean center_of_symmetry_callout (int face_id, int &call_id);
    RoseBoolean perpendicular_to_callout (int face_id, int &call_id);
    RoseBoolean tangent_callout (int face_id, int &call_id);
    RoseBoolean extension_callout (int face_id, int &call_id);
    RoseBoolean geometric_alignment_callout (int face_id, int &call_id);
    RoseBoolean parallel_offset_callout (int face_id, double offset, int &call_id);
    RoseBoolean composite_callout (int first_face_id, int &call_id);
    RoseBoolean composite_callout_add_related_callout (int composite_callout_id, int related_callout_id);

    // Add face to callout
    RoseBoolean tolerance_callout_add_face (int call_id, int face_id);

    // number of tols in project
    RoseBoolean tolerance_count (int &size);
    RoseBoolean tolerance_next (int index, int &tol_id);

    // number of semantic tols in specific part
    RoseBoolean wp_tolerance_count (int wp_id, int &count);
    RoseBoolean wp_tolerance_next (int wp_id, int index, int &tol_id);

    // number of presentation tols in specific part
    RoseBoolean wp_draughting_count (int wp_id, int &count);
    RoseBoolean wp_draughting_next (int wp_id, int index, int &dra_id);

    // number of callouts in specific part (use if tols are both zero)
    RoseBoolean wp_callout_count (int wp_id, int &count);
    RoseBoolean wp_callout_next (int wp_id, int index, const char* &name, int & cal_id);

    // callout that do not have a semantic tolerance defined
    RoseBoolean wp_unused_callout_count (int wp_id, int &count);
    RoseBoolean wp_unused_callout_next (int wp_id, int index, const char* &name, int & cal_id);

    // number of tools in project
    RoseBoolean tool_count (int &size);
    RoseBoolean tool_next (int index, int &tl_id);

    // advice about values to fix
    RoseBoolean tool_advice (int tool_id, double &length_advice, 
					      double &diameter_advice, double &radius_advice);

    // accept all the suggested tool offsets
    RoseBoolean take_tool_advice ();

    // none means no advice necessary
    // green means suggested value has been accepted
    // red means suggested value has not been accepted or adjusted
    // yellow means suggested value has been adjusted to something other than the suggested value
    RoseBoolean tool_advice_status (int tool_id, const char * &length_status, 
					      const char *&diameter_status, const char * &radius_status);

    // decide the best order for fixing the tolerances
    RoseBoolean tolerance_stack ();

    // test for the major types of tolerances
    RoseBoolean is_geometric_tolerance (int tol_id, int &flag);
    RoseBoolean is_size_dimension (int tol_id, int &flag);
    RoseBoolean is_location_dimension (int tol_id, int &flag);
    RoseBoolean is_surface_texture_parameter (int tol_id, int &flag);

    // tolerance generic access functions
    RoseBoolean tolerance_type (int tol_id, const char * &type);
    RoseBoolean tolerance_value (int tol_id, double &value);
    RoseBoolean tolerance_unit (int tol_id, const char * &unit);
    RoseBoolean tolerance_applied_to (int tol_id, int &fe_id);
    RoseBoolean tolerance_lower_and_upper (int tol_id, int &flag, double &lower, double &upper);

    RoseBoolean tolerance_max (int tol_id, int &is_set, double &val);
    RoseBoolean tolerance_unequal (int tol_id, int &is_set, double &val);
    RoseBoolean tolerance_defined_unit (int tol_id, int &is_set, double &val);
    RoseBoolean tolerance_defined_area_unit (
	int tol_id, int &is_set, double &val1, double &val2, const char * &area_type
	);

    RoseBoolean set_tolerance_max (int tol_id, double val);
    RoseBoolean set_tolerance_unequal (int tol_id, double val);
    RoseBoolean set_tolerance_defined_unit (int tol_id, double val);
    RoseBoolean set_tolerance_defined_area_unit (
	int tol_id, double val1, double val2, const char * area_type
	);
    RoseBoolean set_tolerance_defined_rectangular_unit ( int tol_id, double val1, double val2 );
    RoseBoolean set_tolerance_defined_square_unit ( int tol_id, double val1 );
    RoseBoolean set_tolerance_defined_circular_unit ( int tol_id, double val1 );

    
    // location dimensions only
    RoseBoolean tolerance_applied_to_origin (int tol_id, int &fe_id);
    RoseBoolean tolerance_applied_to_target (int tol_id, int &fe_id);

    // functons to define a current value for the tolerance
    RoseBoolean tolerance_current_value (int tol_id, double &nominal_value, double &current_value);
    RoseBoolean set_tolerance_current_value (int tol_id, double current_value);

    // tolerance specific access functions
    RoseBoolean get_position_tolerance (int tol_id, int &datumA, int &datumB, int &datumC);

    // the faces in a tolerance
    RoseBoolean tolerance_draughting_count (int tol_id, int &count);
    RoseBoolean tolerance_draughting_next (int tol_id, int index, int &dra_id);
    RoseBoolean tolerance_draughting_local_count (int tol_id, int &count);
    RoseBoolean tolerance_draughting_local_next (int tol_id, int index, int &dra_id);

    // the faces in a tolerance
    RoseBoolean tolerance_face_count (int tol_id, int &count);
    RoseBoolean tolerance_face_next (int tol_id, int index, int &face_id);
    RoseBoolean tolerance_face_local_count (int tol_id, int &count);
    RoseBoolean tolerance_face_local_next (int tol_id, int index, int &face_id);

    // new property of AP242
    RoseBoolean related_tolerance_count (int tol_id, int &count);
    RoseBoolean related_tolerance_next (int tol_id, int next, int &rel_tol_id);

    // for finding faces at source or target for location dimensions
    RoseBoolean tolerance_origin_face_count (int tol_id, int &count);
    RoseBoolean tolerance_origin_face_next (int tol_id, int index, int &face_id);
    RoseBoolean tolerance_target_face_count (int tol_id, int &count);
    RoseBoolean tolerance_target_face_next (int tol_id, int index, int &face_id);

    // legacy versions from before traversal of callouts
    RoseBoolean tolerance_origin_face_local_count (int tol_id, int &count);
    RoseBoolean tolerance_origin_face_local_next (int tol_id, int index, int &face_id);
    RoseBoolean tolerance_target_face_local_count (int tol_id, int &count);
    RoseBoolean tolerance_target_face_local_next (int tol_id, int index, int &face_id);

    // the face geometry in a tolerance
    RoseBoolean tolerance_geometry_count (int tol_id, int &count);
    RoseBoolean tolerance_geometry_next (int tol_id, int index, int &geometry_id);

    // delete a tolerance stuff
    RoseBoolean delete_tolerance (int tol_id);
    RoseBoolean delete_datum (int dat_id);
    RoseBoolean delete_datum_target (int tag_id);

    // functions to make the tolerances.  The with_flags version takes
    // a StixTolType bitflag that indicates any extra parameters, like
    // area unit or modifiers, to support.  These extras are specified
    // at create time because they affect the class used.  The with
    // modifier version is deprecated.

    RoseBoolean geometric_tolerance (int fea_id, const char *datums, double value, StixTolType flags, int &tol_id);
    
    RoseBoolean position_tolerance (int fea_id, const char *datums, double value, int &tol_id);
    RoseBoolean position_tolerance_with_flags (int fea_id, const char *datums, double value, StixTolType flags, int &tol_id);

    RoseBoolean angularity_tolerance (int fea_id,  const char *datums, double value, int &tol_id);
    RoseBoolean angularity_tolerance_with_flags (int fea_id,  const char *datums, double value, StixTolType flags, int &tol_id);

    RoseBoolean circular_runout_tolerance (int fea_id, const char *datums, double value, int &tol_id);
    RoseBoolean circular_runout_tolerance_with_flags (int fea_id, const char *datums, double value, StixTolType flags, int &tol_id);

    RoseBoolean coaxiality_tolerance (int fea_id, const char *datums, double value, int &tol_id);
    RoseBoolean coaxiality_tolerance_with_flags (int fea_id, const char *datums, double value, StixTolType flags, int &tol_id);
    RoseBoolean concentricity_tolerance (int fea_id, const char *datums, double value, int &tol_id);
    RoseBoolean concentricity_tolerance_with_flags (int fea_id, const char *datums, double value, StixTolType flags, int &tol_id);
    RoseBoolean line_profile_tolerance (int fea_id, const char *datums, double value, int &tol_id);
    RoseBoolean line_profile_tolerance_with_flags (int fea_id, const char *datums, double value, StixTolType flags, int &tol_id);
    RoseBoolean parallelism_tolerance (int fea_id, const char *datums, double value, int &tol_id);
    RoseBoolean parallelism_tolerance_with_flags (int fea_id, const char *datums, double value, StixTolType flags, int &tol_id);
    RoseBoolean perpendicularity_tolerance (int fea_id,  const char *datums, double value, int &tol_id);
    RoseBoolean perpendicularity_tolerance_with_flags (int fea_id,  const char *datums, double value, StixTolType flags, int &tol_id);
    RoseBoolean surface_profile_tolerance (int fea_id, const char *datums, double value, int &tol_id);
    RoseBoolean surface_profile_tolerance_with_flags (int fea_id, const char *datums, double value, StixTolType flags, int &tol_id);
    RoseBoolean symmetry_tolerance (int fea_id, const char *datums, double value, int &tol_id);
    RoseBoolean symmetry_tolerance_with_flags (int fea_id, const char *datums, double value, StixTolType flags, int &tol_id);
    RoseBoolean total_runout_tolerance (int fea_id, const char *datums, double value, int &tol_id);
    RoseBoolean total_runout_tolerance_with_flags (int fea_id, const char *datums, double value, StixTolType flags, int &tol_id);

    RoseBoolean cylindricity_tolerance (int fea_id, double value, int &tol_id);
    RoseBoolean cylindricity_tolerance_with_flags (int fea_id, double value, StixTolType flags, int &tol_id);
    RoseBoolean flatness_tolerance (int fea_id, double value, int &tol_id);
    RoseBoolean flatness_tolerance_with_flags (int fea_id, double value, StixTolType flags, int &tol_id);
    RoseBoolean roundness_tolerance (int fea_id, double value, int &tol_id);
    RoseBoolean roundness_tolerance_with_flags (int fea_id, double value, StixTolType flags, int &tol_id);
    RoseBoolean straightness_tolerance (int fea_id, double value, int &tol_id);
    RoseBoolean straightness_tolerance_with_flags (int fea_id, double value, StixTolType flags, int &tol_id);

    RoseBoolean diameter_size_tolerance (int fea_id, double value, int &tol_id);
    // with lower and upper limits
    RoseBoolean diameter_size_tolerance (int fea_id, double value, double lower, double upper, int &tol_id);
    RoseBoolean angular_size_tolerance (int fea_id, double value, double lower, double upper, int &tol_id);
    RoseBoolean curved_size_tolerance (int fea_id, double value, double lower, double upper, int &tol_id);
    RoseBoolean height_size_tolerance (int fea_id, double value, double lower, double upper, int &tol_id);
    RoseBoolean width_size_tolerance (int fea_id, double value, double lower, double upper, int &tol_id);
    RoseBoolean length_size_tolerance (int fea_id, double value, double lower, double upper, int &tol_id);
    RoseBoolean radial_size_tolerance (int fea_id, double value, double lower, double upper, int &tol_id);
    RoseBoolean thickness_size_tolerance (int fea_id, double value, double lower, double upper, int &tol_id);

    RoseBoolean linear_distance_tolerance (int source_id, int target_id, double value, int &tol_id);
    // with lower and upper limits
    RoseBoolean linear_distance_tolerance (int source_id, int target_id, double value, double lower, double upper, int &tol_id);
    RoseBoolean curved_distance_tolerance (int source_id, int target_id, double value, double lower, double upper, int &tol_id);
    RoseBoolean angular_location_tolerance (int source_id, int target_id, double value, double lower, double upper, int &tol_id);

    // surface texture parameter
    RoseBoolean surface_texture_parameter (int face_id, char * parameter_name, double value, char *measuring_method, int &surf_id);
    RoseBoolean get_surface_texture_parameter (int face_id, const char * &parameter_name, double &value, const char * &value_unit, const char * &measuring_method);

    // get all the faces that have a tolerance
    RoseBoolean workpiece_tolerance_face_count (int wp_id, int &count);
    RoseBoolean workpiece_tolerance_face_next (int wp_id, int index, int &face_id);

    // get all the faces
    RoseBoolean workpiece_face_count (int wp_id, int &count);
    RoseBoolean workpiece_face_next (int wp_id, int index, int &face_id);

    // functions to find tolerances that apply to workingsteps and workplans
    RoseBoolean workingstep_tolerance_count (int ws_id, int &count);
    RoseBoolean workingstep_tolerance_next (int ws_id, int index, int &tol_id);
    RoseBoolean workplan_tolerance_count (int wp_id, int &count);
    RoseBoolean workplan_tolerance_next (int wp_id, int index, int &tol_id);

    // functions to find faces in the process feature (only) of workingsteps and workplans
    RoseBoolean workingstep_face_count (int ws_id, int &count);
    RoseBoolean workingstep_face_next (int ws_id, int index, int &face_id);
    RoseBoolean workplan_face_count (int wp_id, int &count);
    RoseBoolean workplan_face_next (int wp_id, int index, int &face_id);

    // datums
    RoseBoolean make_face_datum (const char * label, int face_id, int &data_id);
    RoseBoolean make_target_datum (const char * label, int target_id, int &data_id);
    RoseBoolean find_datum (const char * label, int &dat_id, const char* &modifier);

    // get all the datums
    RoseBoolean get_datum_count (int &count);
    RoseBoolean get_datum_next (int index, const char * &label, const char * &modifier, int &dat_id);
    RoseBoolean get_datum_type (int dat_id, const char * &type);
    RoseBoolean get_datum_label (int dat_id, const char *&label);

    // number of datums in specific part
    RoseBoolean wp_datum_count (int wp_id, int &count);
    RoseBoolean wp_datum_next (int wp_id, int index, const char *&label, const char *&modifier, int &dat_id);

    // number of datums in specific part including datums on subassemblies
    RoseBoolean wp_all_datum_count (int wp_id, int &count);
    RoseBoolean wp_all_datum_next (int wp_id, int index, const char *&label, const char *&modifier, int &dat_id);

    // use datums to orient workpieces
    RoseBoolean establish_datum_reference_frame (int wp_id, const char *datum_select, RoseXform &result);
    RoseBoolean workpiece_placement_using_datums (int ref_part_id, const char *select_1, int moving_part_id,  const char * select_2);

    // use three faces to set origin of setup
    RoseBoolean setup_placement_using_faces (int wp_id, int face1a_id, int face1b_id, int face1c_id);
    RoseBoolean setup_placement_using_faces_and_measurements (Workplan *plan,  Workpiece *measure, int face1a_id, int face1b_id, int face1c_id);

    // use three faces to orient workpieces
    RoseBoolean establish_face_reference_frame (int facea_id, int faceb_id, int facec_id, RoseXform &result);
    RoseBoolean workpiece_placement_using_faces (int wp_id, int face1a_id, int face1b_id, int face1c_id, int face2a_id, int face2b_id, int face2c_id);

    // compensation operation
    RoseBoolean setup_compensation_workingstep (int wp_id, int index, const char *nme, int setup_id, int frame_id, int face_a, int face_b, int face_c, int &new_id);

    // Frame definition operation
    RoseBoolean frame_definition_workingstep (int wp_id, int index, const char *nme, int face_a, int face_b, int face_c, int &new_id);

    // change the nominal faces being measured in a compensation workingstep or frame definition
    RoseBoolean change_nominal_faces (int ws_id, int face_a, int face_b, int face_c, int &new_id);

    RoseBoolean apply_compensation (int ws_id);
    RoseBoolean unapply_compensation (int ws_id);
    RoseBoolean is_applied_compensation (int ws_id, int &flag);

    // helpers
    RoseBoolean apply_frame_definition_workingstep (Frame_definition_workingstep *fd);
    RoseBoolean unapply_frame_definition_workingstep (Frame_definition_workingstep *fd);
    RoseBoolean is_applied_frame_definition_workingstep (Frame_definition_workingstep *fd, int &flag);

    RoseBoolean apply_compensation_workingstep (Compensation_workingstep *cws);
    RoseBoolean unapply_compensation_workingstep (Compensation_workingstep *cws);
    RoseBoolean is_applied_compensation_workingstep (Compensation_workingstep *cws, int &flag);

    // helpers
    RoseBoolean frame_definition_resolve_workpiece_faces_for_three_face_corner (Workpiece *new_as, Three_face_corner_measurement *tfc, RoseBoolean raw);
    RoseBoolean compensation_workingstep_resolve_workpiece_faces_for_three_face_corner (Compensation_workingstep *comp, Workpiece *new_as, Three_face_corner_measurement *tfc, RoseBoolean raw);
    Three_face_corner_measurement *make_three_face_corner_nominal (Executable_IF *ex, stp_advanced_face *facea, stp_advanced_face *face_b, stp_advanced_face *face_c);
    Three_face_corner_measurement *make_three_face_corner_evaluated (stp_plane *facea, stp_plane *face_b, stp_plane *face_c);
    Three_face_corner_measurement *make_three_face_corner_empty ();

    Three_face_corner_measurement *add_three_face_corner_evaluated (Three_face_corner_measurement * mt, stp_plane *facea, stp_plane *faceb, stp_plane *facec); 
    Three_face_corner_measurement *add_three_face_corner_nominal (Executable_IF *ex, Three_face_corner_measurement * mt, stp_advanced_face *facea, stp_advanced_face *faceb, stp_advanced_face *facec); 
    void get_measurement_workpiece_faces (Measurement_evaluation_IF * mea, ListOfRoseObject *face_bag);

    // Functions to get the faces
    RoseBoolean get_three_face_corner_nominal_faces (int ws_id, int &face_a, int &face_b, int &face_c);
    RoseBoolean get_three_face_corner_evaluated_faces (int ws_id, int &face_a, int &face_b, int &face_c);
    RoseBoolean get_three_face_corner_frame_nominal_faces (int ws_id, int &face_a, int &face_b, int &face_c);
    RoseBoolean get_three_face_corner_frame_evaluated_faces (int ws_id, int &face_a, int &face_b, int &face_c);

    // compensation workpiece
    RoseBoolean put_measurement_workpiece (int ws_id, const char *file_name, RoseBoolean raw = ROSE_FALSE);

    RoseBoolean get_measurement_workpiece (int ws_id, int &wp_id);
    RoseBoolean get_measurement_workpiece_face_count (int ws_id, int &count);
    RoseBoolean get_measurement_workpiece_face_next (int ws_id, int index, int &face_id);

    // compensation workingstep parameters if any
    RoseBoolean is_compensation_workingstep (int ws_id, int &is_compensation, int &measurement_id, int &compensation_id, int &lower_error_id, int &upper_error_id, int &pass_id);
    RoseBoolean is_three_face_corner_measurement (int ws_id, int &flag, int &face_a, int &face_b, int &face_c);
    RoseBoolean is_measurement_target (int tg_id, int &flag, int &nominal_face_id, int &measured_face_id, int &assume_nominal_correct, const char * &nominal_type, const char * &measured_type);
    RoseBoolean is_setup_correction (int cd_id, int &flag, int &setup_id);

    // Paramaters for single pass
    RoseBoolean is_single_pass_correction (int ps_id, int &flag, double &ratio);

    // Draughting in a datum
    RoseBoolean get_datum_draughting_count (int dat_id, int &count);
    RoseBoolean get_datum_draughting_next (int dat_id, int index, int &dra_id);
    RoseBoolean get_datum_draughting_local_count (int dat_id, int &count);
    RoseBoolean get_datum_draughting_local_next (int dat_id, int index, int &dra_id);

    // faces in a datum
    RoseBoolean get_datum_face_count (int dat_id, int &count);
    RoseBoolean get_datum_face_next (int dat_id, int index, int &face_id);
    RoseBoolean get_datum_face_local_count (int dat_id, int &count);
    RoseBoolean get_datum_face_local_next (int dat_id, int index, int &face_id);

    // targets in a detum
    RoseBoolean get_datum_target_count (int dat_id, int &count);
    RoseBoolean get_datum_target_next (int dat_id, int index, int &target_id);
    RoseBoolean get_datum_target_type (int target_id, const char* &type, const char *&id);
    RoseBoolean get_datum_target_point (int target_id, int &success, double &x,  double &y, double &z);
    RoseBoolean get_datum_target_straight_line (int target_id, int &success, double &length, double &x,  double &y, double &z, double &i,  double &j, double &k);
    RoseBoolean get_datum_target_circle (int target_id, int &success, double &diameter, double &x,  double &y, double &z, double &i,  double &j, double &k);
    RoseBoolean get_datum_target_rectangle (int target_id, int &success, double &length, double &width, double &x,  double &y, double &z, 
						double &i,  double &j, double &k, double &a,  double &b, double &c);

    // create the different types of datum targets
    RoseBoolean point_target (int wp_id, double x, double y, double z, int &target_id);
    RoseBoolean straight_line_target (int wp_id, double length, double x, double y, double z, double i, double j, double k, int &target_id);
    RoseBoolean circle_target (int wp_id, double diameter, double x, double y, double z, double i, double j, double k, int &target_id);
    RoseBoolean rectangle_target (int wp_id, double length, double width, double x, double y, double z, double i, double j, double k, double a, double b, double c, int &target_id);

    // functions to add targets to datums
    RoseBoolean add_target (int dat_id, int target_id);
    RoseBoolean remove_target (int dat_id, int target_id);
    RoseBoolean remove_all_target (int dat_id);

    // functions to add datum's to tolerances
    RoseBoolean add_datum (int tol_id, const char *label);
    RoseBoolean add_datum (int tol_id, int dat_id);
    RoseBoolean remove_datum (int tol_id, const char *label);
    RoseBoolean remove_datum (int tol_id, int dat_id);
    RoseBoolean remove_all_datum (int tol_id);

    RoseBoolean add_datum_modifier (int tol_id, const char *label, const char *modifier);
    RoseBoolean add_datum_modifier (int tol_id, int dat_id, const char *modifier);
    RoseBoolean remove_datum_modifier (int tol_id, int dat_id, const char *modifier);
    RoseBoolean remove_all_datum_modifier (int tol_id, int dat_id);

    // add a modifier to a tolerance
    RoseBoolean add_tolerance_modifier (int tol_id, const char *modifier);
    RoseBoolean remove_tolerance_modifier (int tol_id, const char *modifier);
    RoseBoolean remove_all_tolerance_modifier (int tol_id);

    // modifiers of a tolerance
    RoseBoolean num_tolerance_modifier (int tol_id, int &count);
    RoseBoolean next_tolerance_modifier (int tol_id, int index, const char* &modifier);

    // datums of a tolerance
    RoseBoolean num_tolerance_datum (int tol_id, int &count);
    RoseBoolean next_tolerance_datum (int tol_id, int index, int &dat_id,  const char * &label);

    // modifiers of a tolerance
    RoseBoolean num_datum_modifier (int tol_id, int dat_id, int &count);
    RoseBoolean next_datum_modifier (int tol_id, int dat_id, int index, const char* &modifier);

    // surface used in a datum
    // depracated
    RoseBoolean get_datum_surface(int datum_ref_id, int &surface_id);

    // evaluate tolerance status (red, green, yellow) using probe points
    RoseBoolean evaluate_tolerance_status (int tol_id);

    // status as tolerance red, tolerance yellow, green or unknown
    RoseBoolean face_status (int face_id, const char * &code);

    // list of faces with status that are not none
    RoseBoolean face_status_count (int &count);
    RoseBoolean face_status_next (int index, int &face_id, const char * &code);

    // status as tolerance red, tolerance yellow, green or unknown
    RoseBoolean tool_face_status (int tool_id, int face_id, const char * &code);
    RoseBoolean tolerance_face_status (int tol_id, int face_id, const char * &code);

    // iterator functions to get all the faces machined by a tool
    RoseBoolean tool_to_face_count (int tool_id, int &count); 
    RoseBoolean tool_to_face_next (int tool_id, int index, int &face_id);

    // iterator functions to get all the faces machined by a tool
    RoseBoolean tolerance_and_tool_to_face_count (int tol_id, int tool_id, int &count); 
    RoseBoolean tolerance_and_tool_to_face_next (int tol_id, int tool_id, int index, int &face_id);

    // iterator functions to get all the features that use a tolerance
    RoseBoolean tolerance_to_feature_count (int tol_id, int &count); 
    RoseBoolean tolerance_to_feature_next (int tol_id, int index, int &fea_id);

    // iterator functions to get all the tolerances on a feature
    RoseBoolean feature_to_tolerance_count (int fea_id, int &count); 
    RoseBoolean feature_to_tolerance_next (int fea_id, int index, int &tol_id);

    // iterator functions to get all the workingsteps that use a feature
    RoseBoolean feature_to_workingstep_count (int fea_id, int &count); 
    RoseBoolean feature_to_workingstep_next (int fea_id, int index, int &ws_id);

    // iterator functions to get all the workingsteps that use a feature
    RoseBoolean feature_to_tool_count (int fea_id, int &count); 
    RoseBoolean feature_to_tool_next (int fea_id, int index, int &tl_id);

    // iterator functions to get all the tolerances applied to a face
    RoseBoolean face_to_tolerance_count (int face_id, int &count); 
    RoseBoolean face_to_tolerance_next (int face_id, int index, int &tol_id);

    // iterator functions to get all the callouts applied to a face
    RoseBoolean face_to_callout_count (int face_id, int &count); 
    RoseBoolean face_to_callout_next (int face_id, int index, int &call_id);

    // iterator functions to get all the tolerances applied to a face
    RoseBoolean face_to_feature_count (int face_id, int &count); 
    RoseBoolean face_to_feature_next (int face_id, int index, int &tol_id);

    // iterator functions to get all the tools that machine a face
    RoseBoolean face_to_tool_count (int face_id, int &count); 
    RoseBoolean face_to_tool_next (int face_id, int index, int &tol_id);

    // iterator functions to get all the tools that machine a face
    RoseBoolean face_to_workingstep_count (int face_id, int &count); 
    RoseBoolean face_to_workingstep_next (int face_id, int index, int &tol_id);

    // iterator functions to get all the probing operations that touch a face
    RoseBoolean face_to_probing_count (int face_id, int &count); 
    RoseBoolean face_to_probing_next (int face_id, int index, int &tol_id);

    // iterator functions to get all the faces for face status
    RoseBoolean face_count (int &count); 
    RoseBoolean face_next (int index, int &face_id);

    // face_geometry type
    RoseBoolean face_measure_geometry (int face_id, int &geometry_id);
    RoseBoolean face_measure_geometry_type (int face_id, const char * &type);
    RoseBoolean face_placement_xyz (int face_id, int &flag, 
					double &raw_x, double &raw_y, double &raw_z,
					double &transform_x, double &transform_y, double &transform_z);

    // Face placement at location determined by setup of current workplan
    RoseBoolean face_placement_xyz_in_wcs (int ex_id, int face_id, int &flag, double &wcs_x, double &wcs_y, double &wcs_z);

    // get all the geometry that needs to be measured
    RoseBoolean measure_geometry_count (int &count);
    RoseBoolean measure_geometry_next (int index, int &geo_id);

    // geometry that can be measured
    RoseBoolean measure_geometry_type (int face_id, const char * &type);
    RoseBoolean measure_geometry_face_count (int geometry_id, int &count);
    RoseBoolean measure_geometry_face_next (int geometry_id, int index, int &face_id);

    RoseBoolean measure_geometry_surface_placement (int geo_id, double &x, double &y, double &z,
						   double &i, double &j, double &k,
						   double &a, double &b, double &c, int &axis_id);   
    RoseBoolean measure_geometry_cylinder_radius (int geo_id, double &radius);

    // workpiece that owns a piece of tolerance data
    RoseBoolean tolerance_workpiece (int tol_id, int &wp_id);
    RoseBoolean datum_workpiece (int dat_id, int &wp_id);

    // probe point accepts ws_id or fe_id
    RoseBoolean get_probe_surface_position_and_direction (int ws_id, const char * &label, 
						 double &x, double &y, double &z, double &i, double &j, double &k);
    RoseBoolean get_probe_start_position_and_direction (int ws_id, const char * &label, double &x, double &y, double &z,
			    double &i, double &j, double &k);
    RoseBoolean get_probe_expected_value_and_measured_result (int ws_id, double &expected_value, 
									   double &measured_result);
    RoseBoolean get_probe_expected_touch_point (int ws_id, double &x, double &y, double &z);
    RoseBoolean get_probe_actual_touch_point (int ws_id, double &x, double &y, double &z);

    // functions to compute coordinates on geometry
    RoseBoolean point_on_circle (int edge_id, double angle, double &new_x, double &new_y, double &new_z);
    RoseBoolean point_on_line (int edge_id, double distance, double &new_x, double &new_y, double &new_z);
    RoseBoolean point_on_plane (int face_id, double u, double v, double &new_x, double &new_y, double &new_z);

    // is this one useful
    RoseBoolean point_on_plane (int face_id, double du, double dv, double old_x, double old_y, double old_z, double &new_x, double &new_y, double &new_z);

    // plan probing of a plane
    RoseBoolean plan_cylinder_probing (int wp_id, int index, const char *nme, int tol_id, int num_u_points,
						int num_v_points, int &new_wp_id, int &last_ws_id);

    // Post Sandvik probing
    RoseBoolean plan_one_point_probing (
	int wp_id, int index, const char *nme, int tol_id,
	double x, double y, double z, double i, double j, double k,
	int &new_ws_id);

    // Plan probing of a plane
    RoseBoolean plan_plane_probing (
	int wp_id, int index, const char *nme, int tol_id, int num_u_points,
	int num_v_points, int &new_wp_id, int &last_ws_id);

    RoseBoolean plan_plane_3_point_probing (
	int wp_id, int index, const char *nme, int tol_id, 
	double space_a, double space_b, int reverse_ab, 
	int &new_wp_id, int &last_ws_id);

    RoseBoolean add_point_to_plane_probe (
	int before_ws_id, char *name, double x, double y, double z, 
	int &new_ws_id);

    // plan probing of a hole
    RoseBoolean plan_hole_probing (int wp_id, int index, const char *nme, int tol_id, int num_points, 
			double depth, int &new_wp_id, int &last_ws_id);
    RoseBoolean add_point_to_cylinder_probe (int before_ws_id, char *name, double angle, int &new_ws_id);

    // plan probing of an edge
    RoseBoolean plan_edge_probing (int wp_id, int index, const char *nme, int tol_id, int edge_id, int num_points,
			double depth, int &new_wp_id, int &last_ws_id);
    RoseBoolean add_point_to_edge_probe (int before_ws_id, char *name, double distance, int &new_ws_id);

    // plan probing of an spline
    RoseBoolean plan_spline_surface_probing (int wp_id, int index, const char *nme, int tol_id, 
			int num_u_points, int num_v_points, int &new_wp_id, int &last_ws_id);

    // plane probing of the vertex points on a spline surface
    RoseBoolean plan_spline_vertex_probing (int wp_id, int index, const char *nme, int tol_id, 
			int &new_wp_id, int &last_ws_id);

    // plan probing of points in a geometric set using a surface
    RoseBoolean plan_point_on_spline_probing (int wp_id, int index, const char *nme, int set_id, 
			int surface_id, int &new_wp_id, int &last_ws_id, int &fea_id);

    // create a workpiece complete operation that references up to three probing workplans
    RoseBoolean plan_workpiece_complete_operation (int wp_id, int index, int &new_ws_id);

    // execute workpiece complete to determine a transformation matrix
    RoseBoolean external_execute_workpiece_complete_probing (int wp_id, int ws_id);

    // transform new coordinates using workpiece transformation
    RoseBoolean plan_using_workpiece_coordinates_on();
    RoseBoolean plan_using_workpiece_coordinates_off();

    // count number of probing operations
    RoseBoolean workplan_probe_count (int wp_id, int fe_id, int &count, RoseBoolean descent);

    // enter measured value for a probing operation
    RoseBoolean workplan_probe_result (int wp_id, int fe_id, int index, double value);
    RoseBoolean workplan_probe_result_xyz (int wp_id, int fe_id, int index, double x, double y, double z, int second);
    RoseBoolean workplan_probe_result_x (int wp_id, int fe_id, int index, double x, int second);
    RoseBoolean workplan_probe_result_y (int wp_id, int fe_id, int index, double y, int second);
    RoseBoolean workplan_probe_result_z (int wp_id, int fe_id, int index, double z, int second);
    RoseBoolean workplan_probe_id (int wp_id, int fe_id, int index, int &pb_id); // redundant

    // write to a probes CSV file
    RoseBoolean export_probe_initial_data (const char *file_name, const char *unitsys);

    // read probe values from a CSV file
    RoseBoolean import_probe_result_data (const char *file_name, const char *unitsys);

    // write to a MAX5 dat file
    RoseBoolean export_probe_result_data (const char *file_name, const char *unitsys);
    
    // if wp_id = 0 use main workplan
    // if fe_id = 0 get information for all features 
    // Get all probing operations in a workplan
    RoseBoolean workplan_probe_workingstep (int wp_id, int fe_id, int index, int &ws_id, int &probe_id, int &fea_id);

    // measure a feature against all applicable probess usings its tols etc
    RoseBoolean feature_grade (int fe_id, const char * &grade);

    // meaure tolerance, dimension or location against all applicable probing operations
    RoseBoolean tolerance_grade (int tol_id, const char * &grade);

    // measure workingstep features against all applicable probes
    RoseBoolean workingstep_feature_grade (int ws_id, const char * &grade);

    // measure one probe against all workingstep features
    RoseBoolean workingstep_probe_grade (int ws_id, const char * &grade);

    // find all probing operations that apply to a feature, tolerance or dimension
    RoseBoolean get_probe_count (int fe_id, int &count);
    RoseBoolean get_probe_next (int fe_id, int index, int &ws_id);

    // face "touched" by a probing operation
    RoseBoolean probe_face (int ws_id, int &face_id);

    // add face to something- ws, feature, tolerance, callout
    RoseBoolean add_face (int ent_id, int face_id);
    RoseBoolean remove_face (int ent_id, int face_id);
    RoseBoolean remove_all_face (int ent_id);
    RoseBoolean count_face (int ent_id, int &count);
    RoseBoolean next_face (int ent_id, int index, int &face_id);

    // specific to location dimension
    RoseBoolean add_face_target (int ent_id, int face_id);
    RoseBoolean add_face_origin (int ent_id, int face_id);
    RoseBoolean remove_face_origin (int ent_id, int face_id);
    RoseBoolean remove_face_target (int ent_id, int face_id);
    RoseBoolean remove_all_face_origin (int ent_id);
    RoseBoolean remove_all_face_target (int ent_id);
    RoseBoolean count_face_target (int ent_id, int &count);
    RoseBoolean count_face_origin (int ent_id, int &count);
    RoseBoolean next_face_target (int ent_id, int index, int &face_id);
    RoseBoolean next_face_origin (int ent_id, int index, int &face_id);

    // draughting counts for callouts
    RoseBoolean count_draughting (int ent_id, int &count);
    RoseBoolean next_draughting (int ent_id, int index, int &dra_id);
    RoseBoolean count_draughting_target (int ent_id, int &count);
    RoseBoolean count_draughting_origin (int ent_id, int &count);
    RoseBoolean next_draughting_target (int ent_id, int index, int &dra_id);
    RoseBoolean next_draughting_origin (int ent_id, int index, int &dra_id);

    // return the type of a callout Perpendicular to, tangent, extension, center of symmetry etc
    RoseBoolean callout_type (int ent_id, const char* &type);

    // add all the faces within the threshold to the workingstep feature
    RoseBoolean closest_face_add (int ws_id, double threshold_side, double threshold_bot, double threshold_radius);

    // find normal for a given tool path segment
    RoseBoolean pick_toolpath (int ws_id, int tp_id, double ws_param, double tp_param, double x, double y, double z);

    // add faces found in an external file to the workingstep feature
    RoseBoolean add_removal_faces_to_feature (int ws_id, int wp_id);

    // navigation functions
    RoseBoolean tool_to_tolerance_count (int tool_id, int &count);
    RoseBoolean tool_to_tolerance_next (int tool_id, int index, int &tol_id);

    RoseBoolean tool_to_workingstep_count (int tool_id, int &count);
    RoseBoolean tool_to_workingstep_next (int tool_id, int index, int &ws_id);

    RoseBoolean tolerance_to_tool_count (int tol_id, int &count);
    RoseBoolean tolerance_to_tool_next (int tol_id, int index, int &tool_id);

    RoseBoolean tolerance_to_workingstep_count (int tol_id, int &count);
    RoseBoolean tolerance_to_workingstep_next (int tol_id, int index, int &ws_id);

    RoseBoolean tolerance_and_tool_to_workingstep_count (int tol_id, int tool_id, int &count);
    RoseBoolean tolerance_and_tool_to_workingstep_next (int tol_id, int tool_id, int index, int &ws_id);

    // utility functions to find cylindrical surfaces
    RoseBoolean cylinder_surface_count (int &count); 
    RoseBoolean cylinder_surface_next (int index, int &face_id);

    // utility functions to find b_spline surfaces
    RoseBoolean plane_surface_count (int &count); 
    RoseBoolean plane_surface_next (int index, int &face_id);
    
    // utility functions to find b_spline surfaces
    RoseBoolean bspline_surface_count (int &count); 
    RoseBoolean bspline_surface_next (int index, int &face_id); 

    // special utility functions to find b_spline surfaces in geometric set
    RoseBoolean geometry_set_bspline_surface_count (int &count); 
    RoseBoolean geometry_set_bspline_surface_next (int index, int &face_id);
    
    // functions to manipulate geometric sets
    RoseBoolean geometric_set_count (int wp_id, int &count); 
    RoseBoolean geometric_set_next (int wp_id, int index, int &set_id); 
    RoseBoolean geometric_set_point_count (int set_id, int &count); 
    RoseBoolean geometric_set_point_next (int set_id, int index, double &x, double &y, double &z, const char * &name); 

    // utility functions to find faces
    RoseBoolean top (int wp_id, int &face_id);
    RoseBoolean bottom (int wp_id, int &face_id);
    RoseBoolean front (int wp_id, int &face_id);
    RoseBoolean back (int wp_id, int &face_id);
    RoseBoolean left (int wp_id, int &face_id);
    RoseBoolean right (int wp_id, int &face_id);

    // utility functions to find edges on a face
    RoseBoolean top_edge (int face_id, int &edge_id);
    RoseBoolean bottom_edge (int face_id, int &edge_id);
    RoseBoolean front_edge (int face_id, int &edge_id);
    RoseBoolean back_edge (int face_id, int &edge_id);
    RoseBoolean left_edge (int face_id, int &edge_id);
    RoseBoolean right_edge (int face_id, int &edge_id);

    // functions to find planes and cylinders
    RoseBoolean find_planar_face (int piece_id, double x, double y, double z, double i, double j, double k, int &count, int &face_id, int&surface_id);
    RoseBoolean find_cylindrical_face (int piece_id, double x, double y, double z, double i, double j, double k, double radius, int &count, int &face_id, int&surface_id);

    // function to find features using their placement and if necessary their type
    RoseBoolean find_feature (double x, double y, double z, double i, double j, double k, const char *type, int &fe_id);

    // DEPRACATED FUNCTIONS FROM FIRST ITERATION

    // legacy create a round hole probing operation
    RoseBoolean plan_hole_probing (int fe_id, const char *nme, double x, double y, double z);

    RoseBoolean hole_dimension_position_grade (int fe_id, const char * &grade);

    /* define position and diameter of a hole */
    RoseBoolean create_hole_position_and_diameter_tolerance (int face_id, double pos_tol, double dia_tol);
    RoseBoolean modify_hole_position_and_diameter_tolerance (int tol_id, double pos_tol, double dia_tol);

    /* get all the hole dimension features */
    RoseBoolean get_hole_dimension_position_feature_count (int &count);
    RoseBoolean get_hole_dimension_position_feature_next (int count, int &fe_id);

    // closest means same x y location
    RoseBoolean get_closest_hole_dimension_position_feature (int &fe_id, double x, double y, double z); 

    RoseBoolean get_hole_dimension_position_feature (int tol_id, const char * &label, double &x, double &y, double &z, 
					double &radius, double &diameter_tol, double &position_tol);
    RoseBoolean get_hole_dimension_position_feature_probe_count (int fe_id, int &count);
    RoseBoolean get_hole_dimension_position_feature_probe_next (int fe_id, int index, int &ws_id);

    // stuff for second NIST demo
    RoseBoolean workpiece_complete_probing (); 

    // save data that connects features to tolerances
    RoseBoolean save_configuration_data (const char *config_file_name, const char *stepnc_file_name, const char *directory_name);

    // read data that connects features to tolerances
    RoseBoolean load_configuration_data (const char * config_file_name, char * &stepnc_file_name);

    // write an XML file with the current status of each tool
    RoseBoolean save_tool_status_data (const char *status_file_name = NULL);

    // duplicate of routine in Finder
    // added to tolerance because of all the tool/tolerance stack code
    RoseBoolean tool_current (int ws_id, double &tool_diameter, double &tool_radius,
			      double &tool_length, double &tool_current_diameter, 
			      double &tool_current_radius, double &tool_current_length);

    // set current values for tool parameters when these can vary at run time
    RoseBoolean set_tool_current_length (int ws_id, double current_length);
    RoseBoolean set_tool_current_diameter (int ws_id, double current_diameter);
    RoseBoolean set_tool_current_radius (int ws_id, double current_radius);


private:

    apt2step *my_apt;

    // used to determine where to start probing operation and where to go for clearance
    double start_value;
    double clear_value;
    RoseBoolean use_z;
    RoseBoolean use_x_or_y;
    RoseBoolean clear_always;
    double probe_delta_u;
    double probe_delta_v;

    // start and stop run time computations
    RoseBoolean compute_tool_advice;

    RoseDesign *tool_des;

    /* used to determine transformation to be used for new coordinates */
    RoseBoolean plan_using_workpiece;

    // transformation function
    RoseBoolean transform_using_workpiece (RoseXform M, double &x, double &y, double &z, double &i, double &j, double &k);

    // make a datum defined by a face
    Datum_defined_by_feature *internal_make_face_datum (const char * label, int face_id, int none_max_least);

    // make a datum defined by a target
    Datum_defined_by_targets *internal_make_target_datum (const char * label, int target_id, int none_max_least);

    // find a datum plane
    stp_datum * find_datum (const char * label);

    // find the callouts that can be reached from a callout (recursive, uses cache_manager to stop infinite recursion)
    int find_related_callouts (Composite_callout *compy, Composite_group_callout *groupy);

    // Then find and cache all the faces and draughting items
    int find_callout_gri_and_dra (Callout_IF *cally);

    // find and remove datum in list for the different kind of tolerances
    RoseBoolean internal_remove_datum (RoseObject * gtobj, RoseObject * datobj);

    // properties of a datum
    int internal_get_tolerance_datum_values (Single_datum_IF *df, const char *&label, const char *&modifier, int &dat_id);

    /* current values for principle objects */
    Touch_probe *touch_probe;

    // find the probes that are currently ticked
    void internal_find_active_probes (Workplan *wp, ListOfRoseObject *bag);
    void internal_find_active_probes (Selective *sl, ListOfRoseObject *bag);

    // lis of probes sent out by last export and to be updated by next import
    ListOfRoseObject actives;

    // if necessary change units of probe result
    RoseBoolean convert_probe_result_unit (double &x, double &y, double &z, Workpiece_probing *probing);

    // compute status of a feature against all applicable tolerances, dimensions and probing operations
    const char * get_feature_status (Manufacturing_feature_IF *fea);

    // compute status of a geometric tolerance against all applicable probing operations
    const char * get_tolerance_status (Geometric_tolerance_IF *tolly);

    // compute status of a dimension against all applicable probing operations
    const char * get_dimension_status (Size_dimension_IF *dimmy);

    // compute status of a location tolerance against all applicable probing operations
    const char * get_location_status (Location_dimension_IF *locy);

    // compute status of a location tolerance against all applicable probing operations
    const char * get_texture_status (Surface_texture_parameter_IF *pammy);

    // compute status of one probe against all applicable tolerances and dimensions
    const char * get_feature_one_probe_status (Machining_workingstep *ws);

    // compute new color when new tolerance status found
    const char * internal_tolerance_color_algorithm (const char *new_code, const char *code); 

/*    RoseBoolean internal_add_plane_probe_point (Manufacturing_feature_IF *fea, double x, double y, double z);
    RoseBoolean internal_add_cylinder_probe_point (Manufacturing_feature_IF *fea, double angle, 
					    double distance);
    RoseBoolean internal_add_edge_probe_point (Manufacturing_feature_IF *fea, double distance);	*/
    
    // used by planning functions to add a probe point to a workplan
    RoseBoolean internal_add_probe_point_at_z (RoseXform M, const char *buf, Manufacturing_feature_IF *fea, stp_axis2_placement_3d * start_position, RoseBoolean first_point, RoseBoolean last_point, RoseXform P);
    RoseBoolean internal_add_probe_point_at_normal (RoseXform M, const char *buf, Manufacturing_feature_IF *fea, stp_axis2_placement_3d * start_position, RoseBoolean first_point, RoseBoolean last_point);

    // compare faces from two sources for equality
    RoseBoolean internal_compare_face (stp_advanced_face *face1, stp_advanced_face *face2);

    // used in recursive descents
    ListOfRoseObject workplan_probe_result_iterator;
    int workplan_probe_result_signature;
    int workplan_probe_result_counter;
    void internal_workplan_probe_result (Workplan *wp, int fe_id, RoseBoolean descent);
    void internal_selective_probe_result (Selective *sl, int fe_id, RoseBoolean descent);

    int internal_workplan_probe_workingstep (Workplan *wp, int fe_id, int count, int index, int &ws_id, int &prb_id, int &fea_id);
    int internal_selective_probe_workingstep (Selective *sl, int fe_id, int count, int index, int &ws_id, int &prb_id, int &fea_id);

    // gets all the faces and draughting items that can be reached from a datum including compound datums 
    RoseBoolean internal_datum_face_and_draughting (RoseObject *obj);

    ListOfInteger workplan_tolerance_iterator;
    int workplan_tolerance_design_counter;
    int workplan_tolerance_signature;
    void internal_workplan_tolerance (Workplan * wp, ListOfInteger *tol_bag, ListOfInteger *fea_bag);
    void internal_selective_tolerance (Selective * sl, ListOfInteger *tol_bag, ListOfInteger *fea_bag);

    ListOfInteger workingstep_tolerance_iterator;
    int workingstep_tolerance_design_counter;
    int workingstep_tolerance_signature;
    void internal_workingstep_tolerance2 (Machining_workingstep *ws, ListOfInteger *tol_bag, ListOfInteger *fea_bag);

    ListOfInteger workplan_face_iterator;
    int workplan_face_design_counter;
    int workplan_face_signature;
    void internal_workplan_face (Workplan * wp, ListOfInteger *face_bag);
    void internal_selective_face (Selective * sl, ListOfInteger *face_bag);

    ListOfInteger workingstep_face_iterator;
    int workingstep_face_design_counter;
    int workingstep_face_signature;
    void internal_workingstep_face (Machining_workingstep *ws, ListOfInteger *face_bag);

    ListOfInteger tolerance_face_iterator;
    int tolerance_face_design_counter;
    int tolerance_face_signature;
    void internal_tolerance_face (RoseObject * obj);

    ListOfInteger tolerance_origin_face_iterator;
    int tolerance_origin_face_design_counter;
    int tolerance_origin_face_signature;
    void internal_tolerance_origin_face (RoseObject * obj);

    ListOfInteger tolerance_target_face_iterator;
    int tolerance_target_face_design_counter;
    int tolerance_target_face_signature;
    void internal_tolerance_target_face (RoseObject * obj);

    ListOfInteger tolerance_geometry_iterator;
    int tolerance_geometry_design_counter;
    int tolerance_geometry_signature;
    void internal_tolerance_geometry (RoseObject * obj);

    // list of all workingsteps that use a tool
    void internal_tolerance_and_tool_to_face (int tol_id, int tool_id);
    ListOfInteger tolerance_and_tool_to_face_iterator;
    int tolerance_and_tool_to_face_signature1;	    // tol_id
    int tolerance_and_tool_to_face_signature2;	    // tool_id
    int tolerance_and_tool_to_face_design_counter;

    // faces in a feature
    ListOfInteger feature_face_iterator;
    int feature_face_design_counter;
    int feature_face_signature;
    void internal_feature_face (RoseObject * obj);

    int datum_design_counter;

    // list of all inspection points in a workpiece
    void internal_inspection_point (stp_geometric_set *set);
    ListOfRoseObject inspection_point_iterator;
    RoseXform inspection_point_matrix;
    int inspection_point_signature;		    // set_id
    int inspection_point_design_counter;

    // evaluation functions for b_spline_surfaces
    const char *evaluate_b_spline_position (double tolerance, int count, double expected_bag[], 
	double measured_bag[]);
    const char *evaluate_b_spline_surface_profile (double tolerance, int count, double expected_bag[], 
	double measured_bag[]);

    // evaluation functions for cylinders
    const char *evaluate_cylinder_position (double tolerance, int count, double expected_bag[], 
	double measured_bag[]);
    const char *evaluate_cylinder_diameter (double tolerance, int count, double expected_bag[], 
	double measured_bag[]);
    const char *evaluate_cylinder_perpendicularity (double tolerance, int count, double expected_bag[], 
	double measured_bag[]);

    // evaluation functions for planes
    const char *evaluate_plane_position (double tolerance, int count, double expected_bag[], 
	double measured_bag[]);
    const char *evaluate_plane_flatness (double tolerance, int count, double expected_bag[], 
	double measured_bag[]);

    // evaluation for size dimensions
    const char *evaluate_diameter_size (double tolerance, int count, double expected_bag[], double measured_bag[]);

    // evaluation for tolerances (sets the measured value for the tolerance)
    void evaluate_surface_profile_tolerance (Geometric_tolerance_IF *tolly, 
					ListOfdouble *expected_value, ListOfdouble *measured_value);

    
    // find face set for a tolerance or feature
    stp_shape_aspect *find_aspect (RoseObject *obj); 

    // make or return the default probe
    Touch_probe *default_probe ();

    // test to see if workingstep references a feature
    RoseBoolean feature_of (Machining_workingstep *ws, unsigned fe_id);

    // create workplan for new probing operations
    RoseBoolean internal_nest_workplan_after (const char *name, stp_machining_process_executable *plan_obj, int index, Workpiece *piece);

    // hunt for the coordinates of the last point to get continuity between operations
    Operation_IF *internal_set_last_point (Workplan *wp, stp_machining_process_executable *exe, RoseBoolean nested);
    Operation_IF *internal_set_last_point (Selective *sl, stp_machining_process_executable *exe, RoseBoolean nested);

    // hunt for first point in a workplan and use it to set the start point for any new WS
    RoseBoolean internal_set_first_point (Workplan *wp);

    // stuff for second NIST demo
    RoseBoolean duplicate_compute_workplan_probe_plane (RoseXform M, Workplan *copy_plan, 
		    Workplan *big_plan, Machining_workingstep *wpc, int index);  
    RoseBoolean internal_duplicate_workpiece_complete_probing_3d (Workplan *wp, Machining_workingstep *ws, 
	RoseXform M);

    // serach for product definition. Most of algorithm is in Geometry.cxx
    // this function simply search the workpiece, rawpiece and fixture in turn
    stp_product_definition *search_for_pd (stp_geometric_representation_item *fce);

    // look for workpiece in database
    Workpiece *search_for_workpiece (RoseXform &M, stp_geometric_representation_item *adf);

    // find placement coordinates of an item that may be in workpiee, rawpiece, etc
    void transform_coords (stp_advanced_face *adf, double raw_x, double raw_y, double raw_z, 
	double &transform_x, double &transform_y, double &transform_z);

    // compute world coordinates of an axis2_placement
    void transform_axis (stp_advanced_face *adf, stp_axis2_placement_3d *axis, double &transform_x, double &transform_y, double &transform_z, 
	double &transform_i, double &transform_j, double &transform_k);

    // write feature data for a workpiece to the configuration file
    RoseBoolean save_configuration_feature_data (FILE *file, Workpiece *piece);
    RoseBoolean save_configuration_workplan_data (FILE *file, Workplan *plan);

    // internal forms of closest face functions
    RoseBoolean closest_face_add (Machining_workingstep *ws, double threshold_side, double threshold_bot, double threshold_radius); 
    RoseBoolean closest_face_add (Workplan *wp, double threshold_side, double threshold_bot, double threshold_radius); 

    // find point closest point on face
    RoseBoolean closest_face_find (Machining_workingstep *ws, double x, double y, double z, 
					  double threshold_side, double threshold_bot, double threshold_radius);
    // v2 using facet manager
    void closest_face_bottom (
	RoseObject * solid, double threshold_bot,
	Workpiece *piece, stp_representation *desRep, double tool_half_diameter,
	RoseXform MWorldSpace, RoseXform MPartSpace,
	RosePoint Point, RosePoint PointBefore, RosePoint PointAfter,
	RoseDirection axis,
	Toolpath_feature *tp, stp_advanced_face * &last_face,
	RoseBoolean &first);

    void closest_face_bottom (
	double threshold_bot,
	Workpiece *piece, stp_representation *desRep, double tool_half_diameter,
	RoseXform MWorldSpace, RoseXform MPartSpace,
	RosePoint Point, RosePoint PointBefore, RosePoint PointAfter,
	RoseDirection axis,
	Toolpath_feature *tp, stp_advanced_face * &last_face,
	RoseBoolean &first);
    
    void closest_face_side (
	/*ListOfRoseObject *bag2, */
	RoseObject * solid,
	double threshold_side,
	Workpiece *piece, stp_representation *desRep, double tool_half_diameter,
	RoseXform MWorldSpace, RoseXform MPartSpace,
	RosePoint Point, RosePoint PointBefore, RosePoint PointAfter,
	RoseDirection axis,
	Toolpath_feature *tp, stp_advanced_face * &last_face,
	RoseBoolean &first);

    void closest_face_side (
	double threshold_side,
	Workpiece *piece, stp_representation *desRep, double tool_half_diameter,
	RoseXform MWorldSpace, RoseXform MPartSpace,
	RosePoint Point, RosePoint PointBefore, RosePoint PointAfter,
	RoseDirection axis,
	Toolpath_feature *tp, stp_advanced_face * &last_face,
	RoseBoolean &first);
    
    void closest_face_radius (
	RoseObject * solid, double threshold_radius,
	Workpiece *piece, stp_representation *desRep, double tool_radius,
	RoseXform MWorldSpace, RoseXform MPartSpace,
	RosePoint Point, RosePoint PointBefore, RosePoint PointAfter,
	Toolpath_feature *tp, stp_advanced_face * &last_face,
	RoseBoolean &first);

    void closest_face_radius (
	double threshold_radius,
	Workpiece *piece, stp_representation *desRep, double tool_radius,
	RoseXform MWorldSpace, RoseXform MPartSpace,
	RosePoint Point, RosePoint PointBefore, RosePoint PointAfter,
	Toolpath_feature *tp, stp_advanced_face * &last_face,
	RoseBoolean &first);
    
    void add_face_to_feature (Toolpath_feature *tp, stp_advanced_face *face, stp_advanced_face * &last_face);

    // original closest face algorithm - planes and cylinders only - before facets
    RoseBoolean closest_face_original (Machining_workingstep *ws, double threshold_side, double threshold_bot);

    // list of all the faces that have a tolerance
    void internal_unused_callout (int wp_id);
    ListOfInteger workpiece_unused_callout_iterator;
    int workpiece_unused_callout_design_counter;
    int workpiece_unused_callout_signature;

    // list of all the faces that have a tolerance
    void internal_workpiece_face (int wp_id);
    ListOfInteger workpiece_face_iterator;
    int workpiece_face_design_counter;
    int workpiece_face_signature;

    // list of all the faces that have a tolerance
    void internal_workpiece_tolerance_face (int wp_id);
    ListOfInteger tolerance_workpiece_face_iterator;
    int tolerance_workpiece_face_design_counter;
    int tolerance_workpiece_face_signature;

    // list of all the faces that have a tolerance
    void internal_measure_geometry ();
    ListOfInteger measure_geometry_iterator;
    int measure_geometry_design_counter;

    // list of all tolerances that depend on a cutting tool
    void internal_tool_to_tolerance ();
    int tool_to_tolerance_design_counter;

    // list of all workingsteps that use a tool
    void internal_tolerance_and_tool_to_workingstep (int tol_id, int tool_id);
    ListOfInteger tolerance_and_tool_to_workingstep_iterator;
    int tolerance_and_tool_to_workingstep_signature1;	    // tol_id
    int tolerance_and_tool_to_workingstep_signature2;	    // tool_id
    int tolerance_and_tool_to_workingstep_design_counter;

    // list of all tolerances applied to a face or connected to a workingstep or tool
    // also all features applies to a face
    void internal_face_to_tolerance ();
    int face_to_tolerance_design_counter;
    int face_to_feature_design_counter;
    int tolerance_to_tool_design_counter;
    int tolerance_to_workingstep_design_counter;	   

    // Current color of a face
    void internal_face_status ();
    int face_status_design_counter;
    ListOfInteger face_status_set;

    // list of all features that use a tolerance
    void internal_tolerance_to_feature ();
    int tolerance_to_feature_design_counter;

    // list of all tolerances and surface textures for whole model and each workpiece
    void internal_tolerance ();
    ListOfRoseObject tolerance_iterator;
    int tolerance_design_counter;

    // list of all tools in a model
    void internal_tool ();
    ListOfRoseObject tool_iterator;
    int tool_design_counter;

    // list of all tolerances on a feature
    void internal_feature_to_tolerance ();
    int feature_to_tolerance_design_counter;

    // called from tolerance stack but may be called from tolerance advice
    // sets all the stuff below
    RoseBoolean internal_tool_advice (TFCacheManager *mgr, RoseObject *obj);
    RoseBoolean tool_for_face (stp_advanced_face *face, TFCacheManager *&mgr, RoseObject *&obj); 

    int tolerance_stack_design_counter;

};

// NOT IN CLASS SO CAN BE CALLED FROM APT
// evaluate functions for workpiece probing
RoseBoolean dumb_find_and_execute_workpiece_complete_probing (Workplan *wp, RoseXform &M, RoseDesign *des); 

// 2D algorithm
RoseBoolean internal_execute_workpiece_complete_probing (Workplan *wp, Machining_workingstep *ws, RoseXform &M); 
RoseBoolean internal_compute_workplan_probe_vector (
    Workplan *wp, RoseBoolean &success, 
    RosePoint &fnd_vec, RosePoint &exp_vec, 
    double &fnd_x, double &fnd_y, double &fnd_z,
    double &exp_x, double &exp_y, double &exp_z);

RoseBoolean internal_workplan_probe_for_feature_add_to_bag (Workplan *wp, 
			ListOfdouble *expected_bag, ListOfdouble *found_bag, 
			ListOfstp_cartesian_point *point_bag,
			ListOfstp_direction *direction_bag,
			ListOfstp_direction *start_axis_bag,
			Manufacturing_feature_IF **fea,
			double *clear);

// 3d algorithm
RoseBoolean internal_execute_workpiece_complete_probing_3d (Workplan *wp, Machining_workingstep *ws, RoseXform &M);
RoseBoolean internal_compute_workplan_probe_plane (
    Workplan *wp, RoseBoolean &success, 
    RosePlaneABCD &fnd_plane, RosePlaneABCD &exp_plane);

// also called from process
// list of all workingsteps that use a feature
// function also find tools that apply to a workingstep
// function also finds faces that are machined by a tool
// function also finds workingstep that use a face
// function also finds tools that machine a face
void internal_feature_to_workingstep ();

// list of all features in a model
void internal_feature ();



#endif

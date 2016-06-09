/* $RCSfile: Feature.h,v $
 * $Revision: 1.14 $$Date: 2016/01/29 22:19:38 $
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
 * Header for library to make features
 */

#ifndef feature_h
#define feature_h

//#include <afx.h>
//#include <afxwin.h>

#include "rose.h"
#include "ARM.h"
//#include "module_support.h"
#include <stp_schema.h>


// utiltiy functions
#include "Units.h"
#include "Geometry.h"
#include "Contexts.h"

// module files
//#include "register.h"
#include "Trace.h"

class feature
{
    TraceContext tc;
    
public:

    feature ();
    ~feature ();
    RoseBoolean open_workpiece (char * file_name);
    RoseBoolean open_specific_workpiece (char * file_name, char *piece_name);
    RoseBoolean change_workpiece (char *piece_name);

    RoseBoolean reset(RoseBoolean shutdown = ROSE_FALSE);
    RoseBoolean inches ();
    RoseBoolean millimeters ();
    RoseBoolean add_face (int ws_id, int face_id);
    RoseBoolean remove_face (int ws_id, int face_id);

    /* following two functions set values also used by apt2step */
    RoseBoolean set_direction (double i, double j, double k, double a, double b, double c);
    RoseBoolean set_location (double x, double y, double z = 0);

    /* functions to create general profile */
    RoseBoolean xyz(const char * label, double x, double y, double z = 0);
    RoseBoolean arc(const char * label, double new_x, double new_y, double new_z,
		    double cx, double cy, double cz, double radius, int ccw);
	
    /* define closed pockets */
    RoseBoolean closed_rectangular_pocket (int &pocket_id, int ws_id,  char * nme, double depth,
					   double length, double width, double orthogonal_radius = 0);
    RoseBoolean closed_circular_pocket (int &pocket_id, int ws_id, char * nme,  double depth,
					double diameter);
    RoseBoolean closed_path_pocket (int &pocket_id, int ws_id, char * nme, double depth);

    /* define open pockets */
    RoseBoolean open_partial_circular_pocket (int &pocket_id, int ws_id, char * nme,  double depth,
					      double radius, double sweep_angle);
    RoseBoolean open_path_pocket (int &pocket_id, int ws_id, char * nme, double depth);

    /* define bottom condition */
    RoseBoolean pocket_flat_bottom (int &bot_id, int feature_id, double planar_radius = 0);
    RoseBoolean pocket_radiused_bottom (int &bot_id, int feature_id, double radius, double x, double y, double z);
    RoseBoolean pocket_through_bottom (int &thru_id, int feature_id);

    /* round hole */
    RoseBoolean round_hole (int &hole_id, int ws_id, char * nme, double depth, double diameter); 

    /* define bottom condition */
    RoseBoolean hole_flat_bottom (int &bot_id, int feature_id);
    RoseBoolean hole_conical_bottom (int &bot_id, int feature_id, double tip_angle, double tip_radius = 0);
    RoseBoolean hole_flat_with_radius_bottom (int &bot_id, int feature_id, double corner_radius);
    RoseBoolean hole_spherical_bottom (int &bot_id, int feature_id, double radius);

    /* outside profile */
    RoseBoolean closed_rectangular_outside_profile (int &outside_id, int ws_id,
						    char * nme,  double depth,
						    double length, double width);
    RoseBoolean closed_circular_outside_profile (int &outside_id, int ws_id,
						 char * nme,  double depth, double diameter);
    RoseBoolean partial_circular_outside_profile (int &outside_id, int ws_id,
						  char * nme,  double depth, double radius, double sweep_angle);
    RoseBoolean linear_path_outside_profile (int &outside_id, int ws_id,
					     char * nme,  double depth, double length);
    RoseBoolean closed_path_outside_profile (int &outside_id, int ws_id,
					     char * nme,  double depth);
    RoseBoolean open_path_outside_profile (int &outside_id, int ws_id,
					   char * nme,  double depth);

    /* define bosses */
    RoseBoolean rectangular_boss (int &boss_id, int feature_id, char * nme, 
				  double height, double length, double width);
    RoseBoolean circular_boss (int &boss_id, int feature_id, char * nme, 
			       double height, double diameter);
    RoseBoolean path_boss (int &boss_id, int feature_id, char * nme,
			   double height);

    /* define planar face */
    RoseBoolean planar_face (int &planar_id, int feature_id, char * nme,
			     double depth,
			     double length, double width);

    /* compound feature */
    RoseBoolean compound_feature (int &compound_id, int ws_id, char * nme); 
    RoseBoolean add_feature (int compound_id, int feature_id); 
    
    /* add tolerances to parameters */
    RoseBoolean qualify_depth (int pocket_id, double lower, double upper);

    /* plane rough milling operation */
    RoseBoolean plane_milling (int &ws_id, double allowance, double axial_depth = 0);

    /* make feature (usually AP-224) one of the final features (purpose) of a workinstep */
    RoseBoolean add_final_feature (int ws_id, int feature_id); 

    /* turning feature */
    RoseBoolean general_revolution (int &outside_id, int ws_id,
						char * nme,  double radius);

    /* duplicate of method in APT */
    RoseBoolean save_file (const char * filename, RoseBoolean asModules = ROSE_TRUE);

private:

    Workpiece *piece;
    stp_cartesian_point *last_point;		// last point made
    stp_cartesian_point *first_point;		// first point in closed curve
    stp_polyline * profile_curve;
    stp_composite_curve * composite_profile;

    // add toolpath feature when workingstep is empty
    Toolpath_feature * new_tp_feature (const char * id);

    // common to all closed pockets
    RoseBoolean closed_pocket (int &pocket_id, int ws_id, char * nme, double depth); 

    // common to all open pockets
    RoseBoolean open_pocket (int &pocket_id, int ws_id, char * nme, double depth); 

    // common to all outside profiles
    RoseBoolean outside_profile (int &outside_id, int ws_id, char * nme, double depth);

    // common to all bosses
    RoseBoolean boss (int &boss_id, int feature_id, char * nme, double height);

    // close profile and add last point if necessary
    RoseBoolean close_profile ();

    // close profile with not last point because curve is open
    RoseBoolean open_profile ();

    // transfer faces from old feature to new
    RoseBoolean transfer_faces (Manufacturing_feature_IF *old_fea, Manufacturing_feature_IF *new_fea);


    RoseBoolean rule_britannia;

};


#endif

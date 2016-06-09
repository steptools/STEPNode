/* $RCSfile: Geometry.h,v $
 * $Revision: 1.77 $ $Date: 2016/03/24 15:00:09 $
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
#ifndef MAKER_GEOMETRY_H
#define MAKER_GEOMETRY_H

#include <stp_schema.h>
#include <rose_xform.h>
#include <stix_asm.h>
#include "Workpiece.h"
#include "Machining_tool_IF.h"


// Simple array to hold components of the equation of a plane.
// The scalar equation of plane is a(x-x0) + b(y-y0) + c(z-z0) = 0,
// where a,b,c are the components of the normal.   Also written as
//
//  ax +by +cz = d    where d = ax0 + by0 + cz0

class RosePlaneABCD {
public:
    double m[4];

    RosePlaneABCD() {
	m[0]=0; m[1]=0; m[2]=0; m[3]=0; 
    }
    RosePlaneABCD(double a, double b, double c, double d) {
	m[0]=a; m[1]=b; m[2]=c; m[3]=d; 
    }
};


// functions that will be declared in the class libraries

/*RoseBoolean 
    identify_topmost_assembly (RoseDesign * des, int &count, int &candidate, stp_product_definition *pd_list[]);
stp_product_definition * identify_224_product (RoseDesign * des);*/

void workpiece_brep (Workpiece *work, ListOfRoseObject &bag);
RoseUnit get_workpiece_length_unit (Workpiece *piece);
RoseUnit get_tool_length_unit (Machining_tool_IF *tool);

int find_geometry_shape_rep (RoseDesign * des, stp_shape_representation * shp);

// functions to find all the vertex points in a model
void find_face (stp_shape_representation *brep, ListOfRoseObject *bag, RoseBoolean and_models = ROSE_FALSE);
void find_brep_points (stp_shape_representation *brep, ListOfRoseObject &bag);
void find_advanced_face_points (stp_advanced_face *fce, ListOfRoseObject &bag, RoseBoolean only_outer);
void find_face_surface_points (stp_face_surface *fce, ListOfRoseObject &bag, RoseBoolean only_outer);

// Get plane in a face surface or NULL
stp_plane *get_surface_plane (RoseObject *obj);

// Find a face in a workpiece and compute transformation matrix
RoseBoolean find_face_search (RoseXform &M, stp_shape_representation *brep, stp_geometric_representation_item  *adf);
RoseBoolean find_edge_search (RoseXform &M, stp_shape_representation *brep, stp_geometric_representation_item  *edg);
RoseBoolean find_tessellated_face_search (RoseXform &M, stp_tessellated_shape_representation *trep, stp_geometric_representation_item  *adf);

// transform points into XY space defined by plane
void find_face_points_as_xy (int flag, stp_advanced_face *fce, RoseXform plane, 
			     ListOfdouble *xs, ListOfdouble *ys);

// compute an axis2_placement at center of a face for use in a feature
stp_axis2_placement_3d *compute_face_axis_using_surface (stp_advanced_face *adf);
stp_axis2_placement_3d *compute_face_axis_using_loop (stp_advanced_face *adf);
void compute_face_center (stp_advanced_face *adf, double &x, double &y, double &z);

stp_axis2_placement_3d *compute_axis_from_three_surfaces (RoseDesign *des, stp_elementary_surface *surf_a, stp_elementary_surface *surf_b, stp_elementary_surface *surf_c, RoseXform &result);

// compute axis for cylinder moved down by start
void cylinder_face_axis (stp_advanced_face *adf, double start, stp_axis2_placement_3d *&pos, double &radius);

// point on an axis at distance
void point_on_axis (stp_axis2_placement_3d *pos, double dist, double &x, double &y, double &z);

// find other faces defined on a cylinder
RoseBoolean cylinder_friends (stp_advanced_face *fce, ListOfRoseObject &friends);

// calls the two functions below and delivers result to plan_cylinder probe
RoseBoolean cylinder_height_and_angle (stp_advanced_face *adf, double &minQ, double &maxQ, double &SA, double &EA);

// compute z for top and bottom of a cylinder for plan_cylinder_probe
// done before angle because need to know top to compute direction for 180 degree trims
RoseBoolean cylinder_height (RoseBoolean flag, double &min_dist, double &max_dist, RoseObject *obj, RoseXform M, RoseBoolean bound_orientation);

// compute max and min angle for a cylinder it has been transformed to coordinate system define by an axis
// used in plan_cylinder_probe to determine lower and upper bounds for u and v
RoseBoolean cylinder_angle (double top, double &s_angle, double &e_angle, RoseObject *obj, RoseXform M, RoseBoolean bound_orientation);

// test if edge is on a face
RoseBoolean edge_on_face (stp_advanced_face *fce, stp_edge_curve *ed);

stp_face_bound *find_outer_bound (stp_advanced_face *fce);
stp_face_bound *find_outer_bound2 (stp_advanced_face *fce);	// cylinders can have two
RoseBoolean outer_face_points (stp_advanced_face * adf, ListOfRoseObject &bag);
RoseBoolean face_min_max (double &min_x, double &min_y, double &min_z,
			  double &max_x, double &max_y, double &max_z, 
			  double threshold, ListOfRoseObject &bag);

RoseBoolean face_min_max_filter (stp_cartesian_point *pnt, double min_x, double min_y, double min_z,
				 double max_x, double max_y, double max_z);

// count faces in an explicit representation
int eface_count (Callout_IF *cally);
int eface_count (Manufacturing_feature_IF *fea);

// get a face in an explicit representation
int eface_next (Callout_IF *cally, int index);
int eface_next (Manufacturing_feature_IF *fea, int index);

// remove faces from an explicit representation
void face_remove (Callout_IF *cally, stp_geometric_representation_item *adf);
void face_remove (Manufacturing_feature_IF *fea, stp_geometric_representation_item *adf);

void face_all_remove (Callout_IF *cally);
void face_all_remove (Manufacturing_feature_IF *fea);

// compute matrix that will project points onto plane defined by (i, j, k)
RoseXform project_matrix (double i, double j, double k); 

// Randolph Franklin's algorithm to determine if a point is in a polygon
int pnpoly(int npol, float *xp, float *yp, float x, float y);

// Apply pnploy to a loop, plus test for cylinders (holes)
int inside_bound (stp_advanced_face *adf, stp_face_bound * bnd, double x, double y, double z, 
		  double pi, double pj, double pk);

// Compute list of bounding points for pn_poly
// written by modifying and cleaning inside_bound algorithm
RoseBoolean bound_points (stp_face_bound * bnd, float xp[], float yp[], float zp[], int limit, int &counter);

// Apply inside bound to all the bounds on a face
RoseBoolean inside_face (stp_advanced_face * adf, double x, double y, double z, double pi, double pj, double pk);

// compute list of points on outer edge loop for pnpoly
// algorithm is a cleaned version of inside_face
RoseBoolean face_points (stp_advanced_face * adf, float xp[], float yp[], float zp[], int limit, int &counter);

// Check to see if point is in one of the holes in a face
RoseBoolean inside_hole (stp_advanced_face * adf, double x, double y, double z, double pi, double pj, double pk);

// computer points on an arc
void make_arc_points (stp_oriented_edge *ed, stp_edge_curve *cu, int num_points, int bound_orientation, int flag,
		      ListOfdouble *xbag, ListOfdouble *ybag, ListOfdouble *zbag);
void make_arc_points (stp_trimmed_curve *trim, int num_points, 
		      ListOfdouble *xbag, ListOfdouble *ybag, ListOfdouble *zbag);
void make_arc_points (RoseXform axis, int ccw, stp_cartesian_point *cp, stp_cartesian_point *pnt1, stp_cartesian_point *pnt2, 
		      double radius, int num_points, ListOfdouble *xbag, ListOfdouble *ybag, ListOfdouble *zbag);

// compute points on a spline
void make_spline_points (stp_oriented_edge *o_ed, stp_edge_curve *cu, int num_points, int bound_orientation, int flag,
		      ListOfdouble *xbag, ListOfdouble *ybag, ListOfdouble *zbag);

// compute locations found for a bunch of probes using start_point, direction and measure value
void compute_found_point (stp_cartesian_point *start_point, stp_direction *direction, 
			     double measure, double &x, double &y, double &z);

// length of a polyline
double poly_dist (stp_polyline *poly, stp_polyline *axis_poly, RoseUnit actual_length_unit, RoseUnit desired_length_unit);

// time to traverse a polyline when there is an override curve
double poly_time (stp_polyline *poly, stp_polyline *axis_poly, double feed, stp_polyline *over_ride, 
		  RoseUnit actual_length_unit, RoseUnit desied_length_unit);

// lenght of a trimmed curve
double curve_dist (stp_trimmed_curve *curve);

// distance between two points
double dist (stp_cartesian_point *pt1, stp_cartesian_point *pt2);
double dist (double ax, double ay, double az, double bx, double by, double bz);

// function to find plane face being milled by a toolpath
RoseBoolean line_on_plane_in_threshold (
    double threshold, stp_advanced_face *fce, RoseXform world2path,
    int num_points, RosePoint ws_points[]);

// line intersection
RoseBoolean compute_2d_line_intersection (
    double x1, double y1, double i1, double j1, double x2, double y2,
    double i2, double j2, double &rx, double &ry);

// interesection between advanced face bound and line between two points
RoseBoolean bound_line_intersection (int counter, float * xs, float *ys, float p, float q, float x2, float y2);

// maps 3d into 2d for bound line intersection
RoseBoolean big_bad_bound_line_intersection (
    int counter, float * xs, float *ys, float *zs, 
    RosePoint start, RosePoint end, RoseDirection normal);

// check if pt is in  box defined by l and h
int in_box (double x, double y, double z, double lx, double ly, double lz, double hx, double hy, double hz);

// intersection of line and plane provided line is not on plane or parallel to plane
RosePoint point_from_line_and_plane (
    stp_plane *plane, RosePoint P1, RosePoint P2
    );

// intersection of line and circle defining ends of cylinder
RosePoint point_from_line_and_cylinder (
    stp_cylindrical_surface *cyl, RosePoint P1, RosePoint P2
    );

// ABCD from plane
void plane_coefficients (double &A, double &B, double &C, double &D, stp_plane *plane);
void plane_coefficients (double &A, double &B, double &C, double &D, RoseXform plane);

// solve ax + by + cz + d = 0 for a plane using three point in bag
void plane_coefficients (double &a, double &b, double &c, double &d, ListOfRoseObject &bag);

// alternate signature for plane_coefficients
// DTL - this is using the double[4] for abcd.  No longer supported
RosePlaneABCD compute_plane (
    double x1, double y1, double z1, double x2, double y2, double z2, 
    double x3, double y3, double z3);

double plane_z (double A, double B, double C, double D, double x, double y);
double plane_x (double A, double B, double C, double D, double y, double z);
double plane_y (double A, double B, double C, double D, double z, double x);

// interesction point of three plance
RoseBoolean compute_plane_intersection (RosePlaneABCD plane1, RosePlaneABCD plane2, RosePlaneABCD plane3, RosePoint &pnt);

// compute and return matrix describing the surfaces in a datume
RoseBoolean get_datum_surfaces (Single_datum_IF *datum, stp_advanced_face * &adf, 
				RoseXform &surf, const char * &type);

// compute and return matrix describing the surfaces in a datume
RoseBoolean get_face_surface (RoseObject *obja, stp_advanced_face * &adf, 
				RoseXform &surf, const char * &type);

// direction of a loop
RoseBoolean clockwise (double cx, double cy, double cz, double ax, double ay, double az,
		       double bx, double by, double bz, 
		       double axis_x, double axis_y, double axis_z);

// end of curve
stp_cartesian_point* end1 (stp_edge_curve *cu);
stp_cartesian_point* end2 (stp_edge_curve *cu);

// placement for feature measuring an edge curve
stp_axis2_placement_3d *compute_edge_axis (stp_advanced_face *adf, stp_edge_curve *ed, double depth);

stp_advanced_face *find_top (stp_shape_representation *brep);
stp_advanced_face *find_bottom (stp_shape_representation *brep);
stp_advanced_face *find_front (stp_shape_representation *brep);
stp_advanced_face *find_back (stp_shape_representation *brep);
stp_advanced_face *find_left (stp_shape_representation *brep);
stp_advanced_face *find_right (stp_shape_representation *brep);

stp_edge_curve *top_edge_on_face (stp_advanced_face *fce);
stp_edge_curve *bottom_edge_on_face (stp_advanced_face *fce);
stp_edge_curve *left_edge_on_face (stp_advanced_face *fce);
stp_edge_curve *right_edge_on_face (stp_advanced_face *fce);
stp_edge_curve *back_edge_on_face (stp_advanced_face *fce);
stp_edge_curve *front_edge_on_face (stp_advanced_face *fce);


// find last point in a tool path
stp_cartesian_point *find_last_point (stp_bounded_curve *curve);
stp_cartesian_point *find_first_point (stp_bounded_curve *curve);

// add a level to an assembly
stp_product_definition *create_assembly (
    RoseDesign * des, const StpAsmProductDefVec &roots);

// test shape rep for geometry
RoseBoolean is_geometry_rep (stp_representation *shp);

// fix data in an AP-203 exported to AP-238 so that it conforms to AP-203
RoseBoolean fix_203 (RoseDesign * des, RoseBoolean was_203);

// functions to return default values
stp_direction * z_direction (RoseDesign * des);
stp_direction * x_direction (RoseDesign * des);
stp_direction * y_direction (RoseDesign * des);

// functions to return made values
stp_direction * made_z_direction (RoseDesign * des);
stp_direction * made_x_direction (RoseDesign * des);
stp_direction * made_y_direction (RoseDesign * des);
stp_cartesian_point * made_axis_location (RoseDesign * des);
stp_axis2_placement_3d * made_axis(RoseDesign * des);

// make a reference direction for a given axis, any direction OK but preference given to an axis
stp_direction * invent_direction (RoseDesign * des, double i, double j, double k);
RoseDirection invent_direction (RoseDirection z);

// functions to make things
// length is Z for block and cylinder, width is X
// origin of block is bottom face, center
stp_block_shape_representation * inch_block
(RoseDesign * des, double x, double y, double z,
 double length, double width,			     
 double height, char * name);

stp_cylindrical_shape_representation * inch_cylinder
(RoseDesign * des, double x, double y, double z, 
 double length, double diameter, 
 char * name);

stp_block_shape_representation * mm_block (RoseDesign * des, double x, double y, double z,
					     double length, double width,			     
					     double height, char * name);
stp_cylindrical_shape_representation * mm_cylinder
(RoseDesign * des, double x, double y, double z, 
 double length, double diameter, 
 char * name);

stp_direction * make_direction (RoseDesign * des, double i, double j, double k);

stp_cartesian_point * make_point (RoseDesign * des, const char * nme, double x,
				  double y, double z);

stp_plane * z_security_plane (RoseDesign * des, double value);

// functions to set current values
stp_cartesian_point * make_axis_location (RoseDesign * des, double x,
					  double y, double z);
stp_direction * make_z_direction (RoseDesign * des, double i, double j, double k);
stp_direction * make_x_direction (RoseDesign * des, double i, double j, double k);
stp_direction * make_y_direction (RoseDesign * des, double i, double j, double k);

// functions to make specific kinds of axes
stp_axis2_placement_3d * make_axis (RoseDesign * des, double x, double y, double z);
stp_axis2_placement_3d * make_axis (RoseDesign * des, double x, double y, double z, double i, double j, double k);
stp_axis2_placement_3d * make_axis (RoseDesign * des, double x, double y, double z, double i, double j, double k, double a, double b, double c);
stp_axis2_placement_3d * make_y_axis (RoseDesign * des, double x, double y, double z);
stp_axis2_placement_3d * find_or_make_axis (stp_shape_representation * shape);

// function to make sure axes are normalied and orthogonal
RoseXform stix_make_normalized_matrix (double x, double y, double z, double &zi, double &zj, double &zk,double &xi, double &xj, double &xk, RoseBoolean &change);

// specific constants
stp_cartesian_point* unit_vector (RoseDesign * des);
stp_axis2_placement_3d * origin_axis (RoseDesign * des);
stp_cartesian_point * origin_point (RoseDesign * des);

stp_axis2_placement_3d *invert_axis2_placement_3d (stp_axis2_placement_3d *arg, RoseDesign * des);

// find workpiece that owns a rep, rep_item, product definition
RoseBoolean search_for_rep (RoseXform &M, Workpiece *piece, stp_representation *rep);
RoseBoolean search_for_item (RoseXform &M, Workpiece *piece, stp_geometric_representation_item *adf);
stp_product_definition *search_for_product_definition (Workpiece *piece, stp_geometric_representation_item *adf);

// Cache the product definition of each shell or face in a workpiece to enable face finds
void cache_product_definition (Workpiece *piece);

// compute most popular machining axis for a workingstep
RoseBoolean ws_machining_axis (Machining_workingstep *ws, double &wsi, double &wsj, double &wsk);

// classify distance dimension using orientation of faces
// "step"	- both have same normal
// "rib"	- normals of both pointing away from each other
// "pocket"	- normals of both pointing to each other
// "dubious"	- no classification
const char * classify_distance_dimension (Linear_distance_dimension_IF *linny);

// internal data of arc normalized to axis
RoseBoolean arc_data (stp_trimmed_curve *arc, RoseXform &M, double &radius, int &ccw,
		       double &s_angle, double &e_angle, double &k1, double &k2);

// compute arc length
double arc_length (double fx, double fy, double fz, double sx, double sy, double sz,
		   double cx, double cy, double cz, double radius, int ccw, double i, double j, double k);

// axis direction of an arc (for checking against toolaxis)
RoseDirection get_arc_axis (stp_trimmed_curve *arc);

stp_advanced_face * distance_dimension_other_face (Linear_distance_dimension_IF *linny, stp_advanced_face *known_face); 

stp_advanced_face * higher_face (stp_advanced_face *face1, stp_advanced_face *face2);

int count_ws_references_for_feature (RoseDesign *des, Machining_feature_IF *tp);

// compute center and radius of a circle using the via points
double via_arc_length (stp_polyline *poly, int index, double &radius);
double via_helix_length (stp_polyline *poly, stp_polyline *paxis, int index, double &radius, double &height);

// compute angle of a circle chord
double chord_to_angle (double distance, double radius);

// circle parameters from via data
RoseBoolean get_circle_params (double center[3], double * radius, double ax[3],
    RosePoint p1_v, RosePoint p2_v, RosePoint p3_v);

RoseBoolean get_circle_params(double center[3], double * radius, double ax[3],
    stp_cartesian_point *p1, stp_cartesian_point *p2, stp_cartesian_point *p3);


Workpiece *find_root_workpiece_for_styled_model (stp_representation * smrep);

void create_empty_product_with_geometry(stp_representation_context *ctx, stp_shape_representation *&rep, stp_product_definition *&pdef);
void make_box_shape(stp_shape_representation *shape, double x_min, double y_min, double z_min, double x_max, double y_max, double z_max);

// Finds a workpiece that has geometry that is given presentation info
// or drafting annotations by the styled_items pointed to by the rep.
// The representation should be a draughting_model or a
// mechanical_design_geometric_presentation_representation
//
// Can not be used within a ROSE.beginTraversal/endTraversal and
// requires that backpointers be present.
//
extern stp_product_definition * find_workpiece_for_styled_model(
    stp_representation * smrep
    );

#endif

/* $RCSfile: Units.h,v $
 * $Revision: 1.25 $ $Date: 2016/06/07 22:06:17 $
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
#ifndef Units_h
#define Units_h

#include <stp_schema.h>
#include <stix_unit.h>


// make items given unit type
stp_measure_representation_item *feedrate_mri(RoseDesign * des, double rate, RoseUnit unit);
stp_measure_representation_item *spindle_mri(RoseDesign * des, double speed, RoseUnit unit);

// allows reasoned lower and upper limits to be given with tool parameters
stp_qualified_measure_representation_item *reasoned_qualified_feedrate_mri(RoseDesign * des, double rate,
					  RoseUnit unit, double lower, const char *lreason, double upper, const char *ureason);
stp_qualified_measure_representation_item *reasoned_qualified_spindle_mri (RoseDesign * des, double speed,
					  RoseUnit unit, double lower, const char *lreason, double upper, const char *ureason);

stp_length_measure_representation_item* inch_quantity (
    RoseDesign * des, 
    double value, 
    const char *label
    );

stp_qualified_length_measure_representation_item* qualified_inch_quantity(
    RoseDesign * des, 
    double value, 
    const char *label, 
    double lower, 
    double higher
    );

// lets tools say why they have an upper and lower limit
stp_qualified_length_measure_representation_item* reasoned_qualified_inch_quantity(
    RoseDesign * des,
    double value, 
    const char* label, 
    double lower, 
    const char *lreason, 
    double upper, 
    const char *ureason
    );

stp_length_measure_representation_item* mm_quantity(RoseDesign * des,double value, const char *label);

stp_qualified_length_measure_representation_item* qualified_mm_quantity(
    RoseDesign * des, double value, const char* label, double lower, double upper
    );
// lets tools say why they have an upper and lower limit
stp_qualified_length_measure_representation_item* reasoned_qualified_mm_quantity(
    RoseDesign * des, double value, const char* label, double lower, const char * lreason, double upper, const char *ureason
    );

// used for surface finish measurements
stp_length_measure_representation_item *micro_meter (RoseDesign * des, double value);
stp_length_measure_representation_item *micro_inch (RoseDesign * des, double value);


stp_plane_angle_measure_representation_item* degree_quantity(
    RoseDesign * des, double value, const char *label
    );

stp_qualified_plane_angle_measure_representation_item* reasoned_qualified_degree_quantity(
    RoseDesign * des, double value, const char* label, double lower, const char *lreason, double upper, const char *ureason
    );

stp_measure_representation_item * count_quantity (RoseDesign * des, int value);
stp_time_measure_representation_item *second_quantity (RoseDesign * des, double value, const char* label);
stp_time_measure_representation_item *minute_quantity (RoseDesign * des, double value, const char* label);
stp_ratio_measure_representation_item *ratio_quantity (RoseDesign * des, double value, const char* label);

stp_qualified_time_measure_representation_item* reasoned_qualified_minute_quantity (
    RoseDesign * des, double value, const char* label, double lower, const char *lreason, double upper, const char *ureason
    );

// force
stp_measure_representation_item *killowatt_power(RoseDesign * des, double power);
stp_measure_representation_item *horse_power(RoseDesign * des, double power);

// torque
stp_measure_representation_item *newton_meter (RoseDesign * des, double torque);
stp_measure_representation_item *pound_foot (RoseDesign * des, double torque);

stp_unit *unit_ipm(RoseDesign * des);
stp_unit *unit_mmpm(RoseDesign * des);
stp_unit *unit_rpm(RoseDesign * des);
stp_unit *unit_second(RoseDesign * des);
stp_unit *unit_minute(RoseDesign * des);
stp_unit *unit_millimeter(RoseDesign * des);
stp_unit *unit_radian(RoseDesign * des);
stp_unit *unit_steradian(RoseDesign * des);
stp_unit *unit_inch(RoseDesign * des);
stp_unit *unit_degree(RoseDesign * des);
stp_unit *unit_count(RoseDesign * des);
stp_unit *unit_kwatt(RoseDesign * des);
stp_unit *unit_horse(RoseDesign * des);
stp_unit *unit_newton_meter(RoseDesign * des);
stp_unit *unit_pound_foot(RoseDesign * des);
stp_unit *unit_micro_inch (RoseDesign * des);
stp_unit *unit_micro_meter (RoseDesign * des);

// tolerance qualifier
stp_value_qualifier *qualifier (RoseDesign * des, const char *name, double value, const char *reason = "");

// make sure new units created for 2nd file
void reset_units ();
void find_units (RoseDesign * des);

// translate values into api units
double getValue(stp_measure_representation_item * obj);
double getValue(stp_measure_with_unit * obj);
const char * getUnit(stp_measure_representation_item * obj);
const char * getUnit(stp_measure_with_unit * obj);
RoseUnit getUnitType(stp_measure_representation_item * obj);
RoseUnit getUnitType(stp_measure_with_unit * obj);

// lower limit that values with tolearance
double getLower(stp_measure_with_unit * obj);
double getUpper(stp_measure_with_unit * obj);
const char * getLowerReason(stp_measure_with_unit * obj);
const char * getUpperReason(stp_measure_with_unit * obj);

// current values for qualifiers in tolerances and tools
stp_qualified_length_measure_representation_item* current_mm_quantity(
    RoseDesign * des, double nominal_value, const char* label, double current_value
    );
stp_qualified_length_measure_representation_item* current_inch_quantity(
    RoseDesign * des, double nominal_value, const char* label, double current_value
    );
stp_qualified_length_measure_representation_item* current_micrometer_quantity(
    RoseDesign * des, double nominal_value, const char* label, double current_value
    );
stp_qualified_length_measure_representation_item* current_microinch_quantity(
    RoseDesign * des, double nominal_value, const char* label, double current_value
    );

double getCurrent(stp_measure_with_unit * obj);

void use_length_unit_inch(RoseDesign * des);
void use_length_unit_mm (RoseDesign * des);

RoseBoolean using_inch_units(RoseDesign * des);
RoseBoolean using_mm_units(RoseDesign * des);

stp_representation_context * get_mm_geometric_context(RoseDesign * des);
stp_representation_context * get_inch_geometric_context(RoseDesign * des);

stp_representation_context * get_mm_geometric_context(RoseDesign * des);
stp_representation_context * get_inch_geometric_context(RoseDesign * des);

#endif

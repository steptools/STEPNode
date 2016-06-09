/* $RCSfile: TrajectoryPath.h,v $
 * $Revision: 1.16 $$Date: 2016/01/29 22:19:39 $
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

#ifndef TRAJECTORY_PATH_H
#define TRAJECTORY_PATH_H

#include "Cutter_contact_trajectory.h"
#include "Cutter_location_trajectory.h"

class TrajectoryPath {

    Cutter_contact_trajectory * cct;
    Cutter_location_trajectory * clt;
    
public:
    TrajectoryPath ();
    void newCutter_contact_trajectory(RoseDesign * des);
    void newCutter_location_trajectory(RoseDesign *des);
    
    Cutter_contact_trajectory * getCutter_contact_trajectory();

    void unset();
    RoseBoolean isSet();
    void set (Trajectory_IF *item);
    
    stp_machining_toolpath * getRoot();    

    RoseBoolean isset_surface_normal();
    
    const char * get_its_id();
    stp_bounded_curve * get_basiccurve();
    stp_bounded_curve * get_its_toolaxis();    

    void put_basiccurve(stp_bounded_curve * val);    
    void put_its_id(const char * val);
    void put_its_machine_functions(stp_machining_functions * val);
    void put_its_priority(const char * val);
    void put_its_speed_rapid ();
    void put_its_technology(stp_machining_technology * val);
    void put_its_toolaxis(stp_bounded_curve * val);
    void put_its_type(const char * val);
    void put_path_maximum_deviation(stp_measure_representation_item * val);
    void put_surface_normal(stp_bounded_curve * val);    
    void put_path_direction(stp_bounded_curve * val);

    void optimize (RoseDesign *d, int mat_on_left);
    void contact_arc_smooth ();

    // special routine to delete unused toolpath data in case of save without garbage collect
    void delete_after_optimize (stp_composite_curve * old_curve);

};

#endif

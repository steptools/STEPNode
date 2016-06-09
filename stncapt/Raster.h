/* $RCSfile: Raster.h,v $
 * $Revision: 1.7 $ $Date: 2016/01/29 22:19:39 $
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

#include <stp_schema.h>
#include "Workpiece.h"

void raster_depth_estimate (
    Workpiece *piece, 
    stp_advanced_brep_shape_representation *brep, 
    double &top, double &bot, 
    double &front, double &back, 
    double &left, double &right,
    int &top_id, int &bot_id, 
    int &front_id, int &back_id, 
    int &left_id, int &right_id
    );

/* $RCSfile: NC_registers.h,v $
 * $Revision: 1.7 $$Date: 2016/01/29 22:19:38 $
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


//#include "Nc_variable.h"
#include "Real_variable.h"
#include <stp_schema.h>

// standard registers
//Nc_variable *cutter_diameter_compensation_register();
Real_variable *cutter_diameter_compensation_register(RoseDesign * des);
//Nc_variable *cutter_length_compensation_register();
Real_variable *cutter_length_compensation_register(RoseDesign * des);

//Nc_variable *find_register (const char *nme);
Real_variable *find_register (RoseDesign * des, const char *nme);
void reset_registers ();






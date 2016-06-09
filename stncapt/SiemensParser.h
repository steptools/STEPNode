/* $RCSfile: SiemensParser.h,v $
 * $Revision: 1.5 $ $Date: 2016/01/29 22:19:39 $
 * Auth:  (jfritz@steptools.com)
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



#ifndef SIEMENS_PARSER
#define SIEMENS_PARSER

#include "APT.h"


RoseBoolean parseSiemens(apt2step * apt, FILE * in);
RoseBoolean parseSiemens(apt2step * apt, const char * fname);

#endif


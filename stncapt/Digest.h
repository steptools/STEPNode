/* $RCSfile: Digest.h,v $
 * $Revision: 1.3 $ $Date: 2016/01/29 22:19:38 $
 * Auth: Samson Bonfante (bonfante@steptools.com)
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

#ifndef digest_h
#define digest_h
#include <rose.h>

//Given a signed file, return the signatures.
void digestsignedfile (
    const char * name,
    const char * normfile,	// temp filename for normalization
    ListOfString * sigs
    );

//Find out if a design is signed, and mark a design as signed.
bool GetSignedDesign(const char* des);
bool GetSignedDesign(RoseDesign* des);
void SetSignedDesign(const char* des);
void SetSignedDesign(RoseDesign* des);
#endif

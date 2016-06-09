/* $RCSfile: CC3_Deleter.h,v $
 * $Revision: 1.7 $ $Date: 2016/01/29 22:19:37 $
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

RoseBoolean delete_other_feature (stp_instanced_feature *ft_root);
RoseBoolean cc3_delete_workplan_features (stp_machining_workplan * wp_root);
RoseBoolean cc3_delete_workingstep_feature (stp_machining_workingstep *ws_root);
RoseBoolean cc3_delete_feature_instance (stp_shape_aspect *sa_root);
RoseBoolean delete_general_pattern (stp_instanced_feature *ft_root);

#if 0
// private
#endif





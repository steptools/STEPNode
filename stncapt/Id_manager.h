/* $RCSfile: Id_manager.h,v $
 * $Revision: 1.5 $$Date: 2016/01/29 22:19:38 $
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


#include "rose.h"

class LastIdManager : public RoseManager {
public:
    unsigned    m_last;


    static LastIdManager * find_manager (RoseDesign *);
    static LastIdManager * make_manager (RoseDesign *);


    LastIdManager() : m_last(0) { }


    ROSE_DECLARE_MANAGER_COMMON();
};

unsigned get_last_id (RoseDesign * d); 
void put_last_id (RoseDesign * d, unsigned max);
void reset_last_id (RoseDesign * d);
unsigned next_id (RoseDesign * d);
RoseObject * find_by_eid(RoseDesign * d, unsigned eid);


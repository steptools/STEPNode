/* $RCSfile: save.h,v $
 * $Revision: 1.31 $ $Date: 2016/06/08 22:07:54 $
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

#ifndef MOD_SAVE_H
#define MOD_SAVE_H

#include "Workplan.h"
#include "Selective.h"
#include "Machining_workingstep.h"
#include "Trajectory_IF.h"
#include "Executable_IF.h"
#include "Cursor.h"

extern void save_as_modules(RoseDesign * des);
extern void save_as_p21(RoseDesign * des);
extern void save_as_step(RoseDesign * des);

const char *make_name_with_strl (const char *name, const char *strl);
const char *get_name_part (const char *buf); 
const char *get_strl_part (const char *buf); 
RoseBoolean has_strl_part (const char *buf); 
RoseBoolean has_url_part (const char *buf);


// replace space with %20 etc
void http_encode (const char *source, int &i1, char *buf, int &i2);
void http_decode (const char *source, int &i1, char *buf, int &i2);
const char * http_decode_string (const char *source);
const char * http_file_part (const char *source);
const char * http_query_part (const char *source);
const char * http_action_part (const char *source);

extern void do_garbage_collection(RoseBoolean gc);

extern RoseBoolean format_file(const char * inname, const char * outname);
extern RoseBoolean strip_file_comments(const char * file, const char * outname,
				       RoseBoolean renumber);

// counter incremented each time design changes to invalidate internal caches
extern int version_count (RoseDesign *des);
extern void version_increment (RoseDesign *des);
extern int global_save_counter;

// The current design
extern cursor *the_cursor;

// used to count version of design
class VersionManager : public RoseManager { 
    private:
         int  counter;
    public:     
     
         VersionManager()	    {counter = global_save_counter++;}
         int version()		    { return counter; }
         void increment ()	    { counter = global_save_counter++; }
     
	 ROSE_DECLARE_MANAGER_COMMON();
};

// finds the workplans that use (contain) a modified executable so times can be reset
void unmark_modified (RoseObject *modified);


#endif


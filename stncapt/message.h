/* $RCSfile: message.h,v $
 * $Revision: 1.11 $ $Date: 2016/01/29 22:19:39 $
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

#ifndef MESSAGE_H
#define MESSAGE_H

#include <rose.h>


#define REPORT_PRINTF      0
#define REPORT_MESSAGEBOX  1
#define REPORT_CONSOLE     2
#define REPORT_HOLD        3
#define REPORT_WINCONSOLE  4

extern void reportMessage(const char * fmt, ...);
extern void initialize();
extern void quit();

extern RoseStringObject get_error_log();
extern void clear_error_log();

extern void set_report_mode(int code);

extern int report_system_messages(int yn);
extern void report_via_printf();
extern void report_via_messagebox();
extern void report_via_console();
extern void report_via_winconsole();
extern void report_via_hold();

extern void set_message_prefix(const char * pfx);
extern RoseStringObject get_message_prefix();

extern void exit_wait();

#endif

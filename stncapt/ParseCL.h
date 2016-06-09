/* $RCSfile: ParseCL.h,v $
 * $Revision: 1.13 $ $Date: 2016/01/29 22:19:38 $
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

#ifndef PARSE_CL_H
#define PARSE_CL_H

#include "APT.h"
#include "Trace.h"

#include "rose_vector.h"

typedef const char * ParseString;
ROSE_DECLARE_VECTOR(StringVec, char );

struct ParseContext {
    FILE * fd;
    const char * fname;
    unsigned line;

    ParseContext(FILE * f, const char * fn) : fd(f), fname(fn), line(1) {}
};

class ParseCL
{
    TraceContext tc;

//    char * line_buff;
    apt2step * apt;

    RoseBoolean rapid_last;
    RoseBoolean rapid_req;

    RoseBoolean fr_unit_first;
    RoseBoolean sp_unit_first;
    RoseBoolean pt_lab_first;
    RoseBoolean reverse_sense;
    
    double feed_last;
    double feed_req;

    RoseBoolean circle_req;
    double cir_ax, cir_ay, cir_az, cir_ox, cir_oy, cir_oz, cir_rad;

    double idvx, idvy, idvz;

    StringVec tool_args;
    int prev_tool;

    void clearToolArgs();
    
public:
    ParseCL(apt2step * a, RoseBoolean fr_unit, RoseBoolean sp_unit, RoseBoolean pt_lab, RoseBoolean rev_sense);
    ~ParseCL() {clearToolArgs();}
    
    void readFile(const char * name, int tool_num = 0);
    
    
private:

    void parse_tool_path(ParseContext * in);
    void parse_tldata(ParseContext * in);	// UG
    void parse_cutter_data(ParseContext * pc, int tool_num);	// Max5
    void parse_cutter(ParseContext * in);	// ProE
    void parse_rapid(ParseContext * in);
    void parse_goto(ParseContext * in);
    void parse_circle(ParseContext * in);
    void parse_fedrat_uv(ParseContext * in);
    void parse_fedrat_vu(ParseContext * in);
    void parse_spindl_uvd(ParseContext * pc);
    void parse_spindl_vd(ParseContext * pc);	// max5 data
    
    void parse_tlon(ParseContext * in);
    void parse_ude(ParseContext * in);

    void parse_loft(ParseContext * in);
    void parse_loadtl(ParseContext * in);
    void parse_insert(ParseContext * in);
    void parse_indirv(ParseContext * in);
    void parse_from(ParseContext * in);
    void parse_autops(ParseContext * in);

    void parse_end_of_path(ParseContext * in);

    void setFeeds();

    void tldata_mill(double diam, double radius, double length, double taper,
		     double tip);
    void end_path();

    void rapid();
    void fedrat(const char * unit, double value);

    void spindl_off();
    void spindl(double val, RoseBoolean ccw, const char *unit);

    void loadtl(int idx);
    
    void cutter(double val);
    
    void goto_pos(RoseStringObject lab, double x, double y, double z);
    void goto_pos_axis(RoseStringObject lab, double x, double y, double z,
		       double i, double j, double k);
    
    void circle (double ox, double oy, double oz,
		 double ax, double ay, double az, double rad);

    void ude (const char * val);    

};

#endif

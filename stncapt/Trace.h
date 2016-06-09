/* $RCSfile: Trace.h,v $
 * $Revision: 1.12 $ $Date: 2016/06/07 20:24:08 $
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

#ifndef TRACE_H
#define TRACE_H

#include <rose.h>


class TraceContext;

/* Trace a function or method call */
class Trace
{
public:
    typedef enum {
	TRACE_NONE,
	TRACE_DEBUG,    /* Debug info */
	TRACE_CALL,     /* Method/function calls */	
	TRACE_INFO,     /* Info messages */
	TRACE_WARNING,  /* Warning messages */
	TRACE_ERROR,    /* Error messages */
	TRACE_FATAL     /* Fatal messages */
    } Level;

private:
    static RoseBoolean initialized;
    static FILE * log_file;
    static Trace::Level log_level;
    static Trace::Level report_level;

    /* The top of the trace stack.  We may want to replace this with an
       explicit stack at some point. */
    static Trace * current_trace;

    static void begin(Trace * t);
    static void end(Trace * t);    
    
    const char * name;
    RoseBoolean args_closed;
    RoseStringObject args;

    TraceContext * context;
    Trace * parent;

    /* The maximum level of problem we encountered during this call */
    Trace::Level max_level;
    
public:
    static void _init();

    Trace (const char * fn_name);
    Trace (TraceContext * ctx, const char * fn_name);
    Trace (Trace * parent, const char * fn_name);
    
    ~Trace();

    static const char * levelName(Trace::Level l);
    static FILE * getLogFile() {return log_file;}
    
private:
    void logParam(const char * name, const char * val);

public:

    /* Record the (in) parameters that were made on this call */
    Trace & addParam(const char * name, int val);
    Trace & addParam(const char * name, unsigned val);
    Trace & addParam(const char * name, double val);
    Trace & addParam(const char * name, const char * val);
    Trace & addParam(const char * name, RoseObject * val);
    Trace & addParam(const char * name, RoseBoolean val);

    void closeArgs();

    void updateLevel(Trace::Level l) {
	if (l > max_level)
	    max_level = l;

	if (current_trace && current_trace != this)
	    current_trace->updateLevel(l);
    }

    void va_report(Trace::Level lev, const char * fmt, va_list args);    
    
    void error() {updateLevel(TRACE_ERROR); }
    
    void fn_call(const char * msg, ...);
    void debug(const char * msg, ...);
    void info(const char * msg, ...);
    void warning(const char * msg, ...);
    void error(const char * msg, ...);
    void fatal(const char * msg, ...);

    /* See if a message of the corresponding severity has occurred */
    RoseBoolean hasInfo()    {return max_level >= TRACE_INFO;}
    RoseBoolean hasWarning() {return max_level >= TRACE_WARNING;}
    RoseBoolean hasError()   {return max_level >= TRACE_ERROR;}
    RoseBoolean hasFatal()   {return max_level >= TRACE_FATAL;}
};


#define PARAM(par) STRINGITIZE(par), par



/* Provide the the context (e.g. instance class) for a trace object to exist */
class TraceContext
{
    static unsigned long max_id;

    unsigned long id;
    const char * name;

    /* Was this context already reported. (we use this to allow the Trace
     * object to keep track if this TraceContext has already been reported
     */       
//    RoseBoolean reported;

private:
    /* Since TraceContext objects are intended to be used as instance variables
       of classes, it is just too easy for one of these to get created w/o a
       name, so we declare the default ctor as private.  (Should not be needed,
       but will at least point people to this comment)
    */
    TraceContext() {}

public:
    TraceContext(const char * n);
    ~TraceContext();

    const char * getName() {return name;}
    unsigned long getId();

//    void report() {reported = ROSE_TRUE;}
//    RoseBoolean wasReported() {return reported;}
};




#endif

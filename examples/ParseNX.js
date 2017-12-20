/* 
 * Copyright (c) 1991-2017 by STEP Tools Inc. 
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * Author: David Loffredo (loffredo@steptools.com)
 */

'use strict';

//======================================================================
// Command Handling
//
// The AptContext object holds state information and a dispatch table
// for the commands.  Each command handler takes two arguments: the
// context object and a string value containing any arguments split
// from the command.
//

module.exports = function AptContext(data,apt,pro) {
  this.apt = apt;
  this.pro = pro;
  
  this.cards = data.split("\n");
  this.filesz = this.cards.length;
  this.line = undefined;
  this.comment = undefined;
  
  this.op_name = undefined;
  this.tool_name = undefined;
  this.pending = undefined;
  this.lenunit = undefined;

  this.lastspin = undefined;
  this.lastfeed = undefined;
  this.lastrapid = undefined;
  this.modalrapid = true;     // rapids only affect one goto
  
  this.getLineNo = function() {
    return (this.filesz - this.cards.length);
  }
  this.getLine = function() {
    if (this.cards.length === 0) { return undefined; }
    
    // APT has an interesting comment and continuation syntax.  The $$
    // is comment to end of line, but a single $ means continue line,
    // but also treats everything after as a comment.
    this.line = this.cards.shift().trim();
    this.comment = undefined;
    if (/^REMARK\s+/.test(this.line)) {
      this.comment = this.line.replace(/^REMARK\s+/, '');
      this.line = '';
    }
    
    while (/\$/.test(this.line)) {
      let combits;
      // comment to end of line
      [this.line, ...combits] = this.line.split('$$');
      this.comment = [this.comment, combits.join(' ').trim()].join(' ').trim();
      
      // line continuation
      if (/\$/.test(this.line)) {
	[this.line, ...combits] = this.line.split('$');
	this.comment = [this.comment, combits.join(' ').trim()].join(' ').trim();
	if (this.cards.length) {
	  this.line += this.cards.shift().trim();
	}
      }
    }
    return this.line;
  }
  this.commands = {
    "CIRCLE":	command_CIRCLE,
    "COOLNT":	command_COOLNT,
    "END-OF-PATH": command_END_OF_PATH,
    "FEDRAT":	command_FEDRAT,
    "FINI":	command_FINI,
    "FROM":	command_FROM,
    "GOTO":	command_GOTO,
    "LOAD":	command_LOAD,
    "LOADTL":	command_LOADTL,
    "MSYS":	command_MSYS,
    "PPRINT":	command_PPRINT,
    "RAPID":	command_RAPID,
    "SELECT":	command_SELECT,
    "SET":      command_SET,
    "SPINDL":	command_SPINDL,
    "TLDATA":	command_TLDATA,
    "TOOL PATH": command_TOOL_PATH,
    "UNITS":	command_UNITS,
    "PAINT":	command_IGNORE,
    "DISPLY":	command_IGNORE,
  };
  
  this.generate_tool_geom = true;
  this.tools = {};
}



//----------------------------------------------------------------------
// Processing for each of the commands  
// 
function command_IGNORE(ctx, args) {}

function command_PARTNO(ctx, args) {
  // PARTNO/<part name>
  ctx.apt.PartNo(args.trim());
}

function command_TOOL_PATH(ctx, args) {
  // TOOL PATH/<operation name>, TOOL, <tool name>
  [ctx.op_name,,ctx.tool_name] = args.split(',');
  if (ctx.op_name) {
    ctx.op_name = ctx.op_name.trim();
  }
  if (ctx.tool_name) {
    ctx.tool_name = ctx.tool_name.trim();
    if (ctx.tool_name.length === 0)
      ctx.tool_name = undefined;
  }

  ctx.apt.Workingstep(ctx.op_name);
}

function command_MSYS(ctx, args) {

  // matrix which relates the coordinates of the tool path to the
  // absolute coordinate system.  The first three fields represent
  // a vector from the model space origin to the origin of the
  // Machine Coordinate System. The next six fields are the first
  // two columns of a three-by-three matrix that maps the motion
  // points described in the CLSF from the MCS to the Absolute
  // Coordinate System. The third column of this matrix is the
  // cross-product of the first two columns.
}

function command_TLDATA(ctx, args) {

  let tnum = undefined;
  let tlid = undefined;

  // name previously set via TOOL PATH or other.
  // look for reuse of a tool with the same name
  if (ctx.tool_name) {
    tlid = ctx.tools[ctx.tool_name];
    // tlid = find.GetToolUsingIdentifier(ctx.tool_name);

    if (tlid !== undefined) {
      tnum = parseInt(ctx.apt.GetToolNumber(tlid), 10);
      console.log("Reusing Tool ", ctx.tool_name, ctx.apt.GetToolNumber(tlid));
    }
    else {
      if (/^\s*T\d+\s*$/.test(ctx.tool_name)) {
	tnum = parseInt(ctx.tool_name.match (/T(\d+)/)[1],10);
	if (ctx.apt.IsToolDefined(tnum)) {
	  console.log("Duplicate Number ", ctx.tool_name, tnum);
	}
      }
    }
  }
  
  let argv = args.split(',');
  switch (argv.shift()) {
  case 'MILL': {
    // mill tools may have 5, 7, or 10 parameters, but we only
    // care about the first five.
    // TLDATA/MILL,DIAMETER,LOWER RADIUS,LENGTH,TAPER ANGLE, TIP ANGLE,
    //   X CENTER R1,Y CENTER R1,   (7 params)
    //   UPPER RADIUS,X CENTER R2,Y CENTER R2  (10 params)
    let [dia,rad,len,taper,tip,distx,disty] = argv.map(s=>parseFloat(s));

    if (distx === undefined) distx = 0;
    if (disty === undefined) disty = 0;
    
    if (tlid) {
      // could compare the values to make sure they match
      ctx.apt.LoadTool(tnum);
      return;
    }
    else {
      ctx.apt.DefineTool(dia, rad, distx, disty, tip, taper, len);
      // let tl_id = ctx.apt.GetCurrentTool();
      // pro.SetToolLength(tl_id, len);
      // pro.SetToolOverallAssemblyLength(tl_id, len);
      
    }
    break;
  }
  case 'DRILL': {
    // TLDATA/DRILL,MODULE TYPE,DIAMETER, CORNER RADIUS, LENGTH,
    //     POINT ANGLE,FLUTE LENGTH
    argv.shift();  // ditch the module type
    let [dia,rad,len,tip,flute] = argv.map(s=>parseFloat(s));

    if (tlid) {
      // could compare the values to make sure they match
      ctx.apt.LoadTool(tnum);
      return;
    }
    else {
      ctx.apt.DefineTool(dia, rad, 0,0, tip, 0, len);
      let tl_id = ctx.apt.GetCurrentTool();
      ctx.pro.SetToolFluteLength (tl_id, flute);
    }
    break;
  }

  default:
    console.log("UNSUPPORTED TOOL TYPE: " + line);
    return;
    // For Lathe Rough and Finish tool paths:
    // TOOL PATH/<operation name>, TOOL, <tool name>
    // TLDATA/TURN,TOOL ORIENTATION, TYPE OF WORK, LATHE SPINDLE AXIS,
    //   NOSE DIAMETER,HOLDER WIDTH,LEAD ANGLE,HEEL ANGLE,
    //   HOLDER HEIGHT,ORIENTATION ANGLE

    // For Lathe Groove tool paths:
    // TOOL PATH/<operation name>, TOOL, <tool name>
    // TLDATA/GROOVE,TOOL ORIENTATION,TYPE OF WORK, TRACKING SIDE,
    //   LATHE SPINDLE AXIS, INSERT WIDTH, LEFT CORNER RADIUS,
    //   RIGHT CORNER RADIUS, MAXIMUM DEPTH,LEAD ANGLE,INSERT ANGLE,
    //   HOLDER HEIGHT,HOLDER WIDTH

    // For Lathe Thread tool paths:
    // TOOL PATH/<operation name>, TOOL, <tool name>
    // TLDATA/THREAD,TOOL ORIENTATION,TYPE OF WORK, LATHE SPINDLE AXIS,
    //   MAXIMUM DEPTH, HOLDERWIDTH, RELIEF ANGLE,HEEL ANGLE,HOLDER HEIGHT
    
  }

  
  if (tnum !== undefined) {
    ctx.apt.SELCTLTool(tnum);
  }
  
  tlid = ctx.apt.GetCurrentTool();
  if (ctx.tool_name) {
    console.log ("DEFINING TOOL: ", ctx.tool_name);
    ctx.tools[ctx.tool_name] = tlid;
    ctx.apt.SetToolIdentifier(ctx.apt.GetToolNumber(tlid), ctx.tool_name);
  }
  if (ctx.generate_tool_geom) {
    ctx.apt.GenerateToolGeometry(tlid); 
  }
}      

function command_SELECT(ctx, args) {
  let [styp,numstr] = args.split(',');
  
  if (styp.trim() !== "TOOL") {
    console.warn("UNKNOWN SELECT: " + styp);
    return;
  }

  let tool_num = parseInt(numstr);
  if (isNaN(tool_num)) {
    console.warn("UNKNOWN SELECT TOOL NUMBER: " + tool_num);
    return;
  }
  ctx.apt.SELCTLTool(tool_num);
}


  
function command_LOAD(ctx, args) {
  let [styp,numstr] = args.split(',');
  
  if (styp.trim() !== "TOOL") {
    console.warn("UNKNOWN LOAD: " + styp);
    return;
  }

  let tool_num = parseInt(numstr);
  if (isNaN(tool_num)) {
    console.warn("UNKNOWN LOAD TOOL NUMBER: " + tool_num);
    return;
  }
  ctx.apt.LoadTool(tool_num);
}


function command_LOADTL(ctx, args) {
  let tool_num = parseInt(args);
  if (isNaN(tool_num)) {
    console.warn("UNKNOWN LOAD TOOL NUMBER: " + tool_num);
    return;
  }
  ctx.apt.LoadTool(tool_num);
}



function command_FROM(ctx, args) {
  let [fx,fy,fz,fi,fj,fk] = args.split(',').map(s=>parseFloat(s));
  if (fk !== 1)
  {
    let plan_id = ctx.apt.GetCurrentWorkplan();
    ctx.apt.WorkplanSetup(plan_id, fx, fy, fz, fi, fj, fk, 1, 0, 0);
  }
}




function command_GOTO(ctx, args) {
  let [x,y,z,i,j,k] = args.split(',').map(s=>parseFloat(s));
  let lab = ctx.comment;
  if (!lab) lab = '';


  if (ctx.lastrapid > 0) {
    if (ctx.lastrapid === 1 && ctx.lastfeed !== undefined)
    {
      // reset feed from rapid
      ctx.apt.Feedrate(ctx.lastfeed);
    }
    ctx.lastrapid--;
  }

  if (ctx.pending !== undefined) {
    let arc = ctx.pending;
    ctx.pending = undefined;
    ctx.apt.ArcXYPlane (lab, x,y,z, arc.cx, arc.cy, arc.cz, arc.radius, arc.ccw);
    return;
  }
  if (i === undefined) {
    ctx.apt.GoToXYZ(lab, x,y,z);
    return;
  }
  else {
    ctx.apt.GoToXYZ_IJK(lab, x,y,z, i,j,k);
    return;
  }
}



function command_CIRCLE(ctx, args) {
  let [cx,cy,cz,ci,cj,ck,radius,tol,tol2,tool_diameter,tool_radius]
      = args.split(',').map(s=>parseFloat(s));
  
  ctx.pending = {
    cx: cx,
    cy: cy,
    cz: cz,
    radius: radius,
    ccw: (ck < 0)
  };

  // set tool radius and diameter from circle data
  let tool_id = ctx.apt.GetCurrentTool();
  if (tool_radius !== undefined) {
    ctx.pro.SetToolCornerRadius(tool_id, tool_radius);
  }
  if (tool_diameter !== undefined) {
    ctx.pro.SetToolDiameter(tool_id, tool_diameter);
  }
}
 
function command_UNITS(ctx, args) {
  // save for later use if we get a permin on feedrates
  ctx.lenunit = args.trim();
  switch (ctx.lenunit) {
  case "MM":
    ctx.apt.Millimeters ();
    break;

  case "INCH":
  case "INCHES":
    ctx.apt.Inches();
    break;

  default:
    console.log("Unknown UNITS:" + ctx.lenunit);
    break;
  }
}

function command_FEDRAT(ctx, args) {
  let [ustr,valstr] = args.split(',');

  // unit omitted or order swapped
  if (/\d+/.test(ustr)) {
    let foo = valstr;
    valstr = ustr; ustr = foo;
  }
  if (ustr == undefined) ustr = '';

  switch (ustr.trim()) {
  case "IPM":
    ctx.apt.FeedrateUnit("ipm");
    break;

  case "MMPM":
    ctx.apt.FeedrateUnit("mmpm");
    break;

  case "IPR":
    ctx.apt.FeedrateUnit("iprev");
    break;

  case "MMPR":
    ctx.apt.FeedrateUnit("mmprev");
    break;
    
  case "PERMIN":
    if (ctx.lenunit === "MM")
      ctx.apt.FeedrateUnit("mmpm");
    else if (ctx.lenunit === "INCH")
      ctx.apt.FeedrateUnit("ipm");
    else {
      console.warn("UNKNOWN FEED UNIT, no length unit specified");
      return;
    }
    break;
    
  case '':
    // stay with existing unit
    break;
  }

  let val = parseFloat(valstr);
  if (isNaN(val)) {
    console.warn("COULD NOT SET FEED " + valstr);
    return;
  }

  ctx.apt.Feedrate(val);
  ctx.lastfeed = val;
  ctx.lastrapid = undefined;
}


function command_RAPID(ctx, args) {
  ctx.apt.Rapid();

  if (ctx.modalrapid) {
    ctx.lastrapid = 2;
  }
}


function command_SPINDL(ctx, args) {

  if (/^\s*OFF\s*/.test(args)) {
    ctx.apt.SpindleSpeed(0);
    return;
  }
  if (/^\s*ON\s*/.test(args)) {
    ctx.apt.SpindleSpeed(ctx.lastspin);
    return;
  }

  let [ustr,valstr,dirstr] = args.split(',');

  // unit omitted or order swapped
  if (/\d+/.test(ustr)) {
    let foo = valstr;
    valstr = ustr; ustr = foo;
  }
  if (/CCW|CLW/.test(ustr)) {
    let foo = dirstr;
    dirstr = ustr; ustr = foo;
  }

  let val = parseFloat(valstr);
  if (isNaN(val)) {
    console.warn("COULD NOT SET SPINDLE " + valstr);
    return;
  }

  if (!ustr || ustr === "RPM") {
    ctx.apt.SpindleSpeedUnit("rpm");
  }
  else {
    console.warn("UNKNOWN SPINDLE UNIT:" + ustr);
    return;
  }

  if (!dirstr) dirstr = "CCW";   // default
  dirstr = dirstr.trim();
  
  if (dirstr === "CCW") {
    // default, positive direction
  }
  else if (dirstr === "CLW") {
    val = -val;
  }
  else {
    console.warn("UNKNOWN SPINDLE DIRECTION:" + dirstr);
    return;
  }

  ctx.apt.SpindleSpeed(val);
  ctx.lastspin = val;
}


function command_COOLNT(ctx, args) {
  // COOLNT/ [ ON | OFF | MIST | FLOOD | TAP | THRU ]
  switch (args.trim()) {
  case "ON":
  case "FLOOD":
    ctx.apt.CoolantOn();
    break;

  case "OFF":
    ctx.apt.CoolantOff();
    break;
    
  case "MIST":
    ctx.apt.CoolantMist();
    break;

  case "THRU":
    ctx.apt.CoolantThru();
    break;

  case "TAP":
  default:
    console.warn("UNSUPPORTED COOLANT: ", args);
    break;
  }
}


function command_SET(ctx, args) {
  let tparms = args.split(',');
  if (tparms[0] === "MODE") {
    if (tparms[1] !== "ABSOL")
      console.log("Cannot SET/MODE:" + tparms[1]);
  }
  else
  {
    console.log("Unknown SET:" + tparms[0]);
  }
}


function command_END_OF_PATH(ctx, args) {
  ctx.lastrapid = undefined;
  ctx.lastfeed = undefined;
  ctx.pending = undefined;
  ctx.op_name = undefined;
  ctx.tool_name = undefined;
}


function command_FINI(ctx, args) {
}


function command_PPRINT(ctx, args) {
  // You could parse the args and harvest extra property information
  // embedded by other systems.
  // let ws_id = ctx.apt.GetCurrentWorkingstep();
  // ctx.apt.WorkingstepAddPropertyDescriptiveMeasure(ws_id, "name", "value");
}



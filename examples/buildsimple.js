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

// Build a full Digital Thread Model with workpiece, fixture, and
// multiple processes.


'use strict';

const fs = require('fs');
const path = require('path');
const ParseNX = require('./ParseNX.js');

const stp = require('../build/Release/StepNode');
const apt = new stp.AptStepMaker();
const pro = new stp.Process();
const tol = new stp.Tolerance();


function main(argv) {

  apt.NewProject("simple");
  apt.Millimeters();   // default to millimeters

  // Read CAM process
  ImportPaths("data/simple_block.cls");

  // Read workpiece geometry as STEP
  apt.Workpiece("data/simple_block_workpiece.stp");

  // Read rawpiece geometry as STEP
  apt.Rawpiece("data/simple_block_rawpiece.stp");
  
  apt.SaveAsModules("simple_example");

  return 0;
}



function ImportPaths(file_name)
{
  let ctx = new ParseNX(fs.readFileSync(file_name,'utf8'),apt,pro);
  while (ctx.getLine() !== undefined) {

    if (!ctx.line) {
      // Pro/E often adds comment commands embedded as $$->
      // ->CUTTER
      // ->TOOL PATH
      // UDE:
      continue;
    }

    // split out the command from the 
    let [cmd, ...combits] = ctx.line.split('/');
    let args = combits.join('/').trim();

    // Do we have a function to handle this kind of command?  Check
    // the dictionary created in the AptContext ctor.  This is more
    // customizable than a big switch because you can just register
    // your own functions, override the existing ones, and so forth.
    let cmdfn = ctx.commands[cmd.trim()];
    if (cmdfn !== undefined) {
      cmdfn(ctx, args);
      continue;
    }

    // something else perhaps?
    console.log("LINE", ctx.getLineNo(),  "UNKNOWN COMMAND: " + cmd);
  }
}


process.exit(main(process.argv));

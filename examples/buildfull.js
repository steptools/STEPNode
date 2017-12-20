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
  // start the program
  apt.PartNo("Sample part");
  //  fea.OpenNewWorkpiece("Sample part");

  // Define a tool
  apt.Millimeters();
  apt.CamModeOn();
  apt.DefineTool(0.25, 5.0, 1.0, 2.0, 3.0, 4.0, 5.0);

  // Read the first program
  ImportPaths("data/Plane_1.cldata");

  // Define feature and operation
  let ws_id = apt.GetCurrentWorkingstep();
  pro.PlaneFinishMilling(ws_id, 0, 3);
  //  fea.PlanarFace(ws_id, "first plane", 0, 40, 25);
  apt.SetName(ws_id, "First planar facing operation");
  // fea.AddFace(ws_id, 1387);   // need new functionality to identify face

  // Read the second progra
  ImportPaths("data/Plane_2.cldata");

  // Define the feature and operation
  ws_id = apt.GetCurrentWorkingstep();
  pro.PlaneFinishMilling(ws_id, 0, 3);
  //  fea.PlanarFace (ws_id, "second plane", 0, 20, 20);
  apt.SetName(ws_id, "Second planar facing operation");
  //	    fea.AddFace(ws_id, 1767);
  // 1. Find faces using a name saved by the CAD
  // 2. Find faces using an updated Threshold function

  // Read workpiece geometry as STEP
  apt.Workpiece("data/hole_model.stp");
  //  tol.AddFacesWithinThresholdToWorkingstep (ws_id, 10);

  // Make geoemtry for Rawpiece
  let wp_id = apt.GetCurrentWorkplan ();
  apt.MakeRawBox (wp_id, -50, -25, 0, 50, 25, 31);

  // Make geometry for cutter
  let tl_id = apt.GetCurrentTool ();
  pro.SetToolLength(tl_id, 100);
  apt.SetToolIdentifier(apt.GetToolNumber(tl_id), "My Cutting Tool");
  apt.GenerateToolGeometry(tl_id);
  pro.SetToolOverallAssemblyLength(tl_id, 80);

  apt.Fixture("data/vise.stp");
  let fixture_id = apt.GetCurrentFixture();
  apt.PutWorkpiecePlacement(fixture_id, 0, -25, 41.5, 0, 1, 0, 1, 0, 0);

  apt.SaveAsModules("full_example");

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

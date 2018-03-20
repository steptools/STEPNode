/* 
 * Copyright (c) 1991-2018 by STEP Tools Inc. 
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

const fs = require('fs');
const path = require('path');

const stp = require('../build/Release/StepNode');
const apt = new stp.AptStepMaker();
const finder = new stp.Finder();
const ctl = new stp.Adaptive();
const gen = new stp.Generate();
const genstate = new stp.GenerateState();

function main(argv) {
  if (argv.length !== 3)
  {
    console.log ("usage: " + argv[1] + " filename");
    return 1;
  }
  
  // Read file synchronously into an array, process line by line.
  // Things like readline work asynchronously, which is not what we
  // want.
  let file_name = argv[2];

  // Read a STEP-NC file
  finder.OpenProject(file_name);

  // Start traversing the process within the file.   
  ctl.StartProject();
  ctl.SetWantedAll(true);

  gen.SetStyle("okuma");
  gen.SetUnitSystem(ctl);

  while (ctl.Next() != stp.CtlEvent.DONE) {
    switch (ctl.Event())
    { 
      case stp.CtlEvent.PROJECT_START:
      // print a comment and follow with our logic
      // process.stdout.write(gen.FormatComment(genstate,"My great program"));
      process.stdout.write("My program start logic here\n");
      break;
      
      case stp.CtlEvent.TOOL_CHANGE:
      // print a description of the tool and follow with our logic
      process.stdout.write(gen.FormatOther(genstate,ctl,"tool-comment"));
      process.stdout.write("My tool change logic here\n");
      break;

      default:
      process.stdout.write(gen.FormatEvent(genstate,ctl));
      break;
    }
  }

  // Do our own move either with separate coords, or an array
  process.stdout.write(gen.FormatMoveXYZ(genstate,ctl,900,950,999));
  process.stdout.write(gen.FormatMoveXYZ(genstate,ctl,[1900,1950,1999]));
  
  return 0;
}


process.exit(main(process.argv));



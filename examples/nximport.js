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
const ParseNX = require('./ParseNX.js');

const stp = require('../build/Release/StepNode');
const apt = new stp.AptStepMaker();
const pro = new stp.Process();


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
  let data = fs.readFileSync(file_name, 'utf8');

  apt.NewProject(file_name);
  apt.Millimeters();   // default to millimeters
  
  ImportNXFile(data);

  // save as filename_thread.stpnc
  apt.SaveAsModules(path.parse(file_name).name + '_thread');
}



function ImportNXFile(data)
{
  let ctx = new ParseNX(data,apt,pro);
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



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

  let xf = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16];

  console.log(  gen.GetDstXform() );

  gen.SetDstXform(xf);

  console.log(  gen.GetDstXform() );
  return 0;
}


process.exit(main(process.argv));



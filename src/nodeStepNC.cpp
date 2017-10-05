//
// Copyright (c) 1991-2017 by STEP Tools Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Author: Samson Bonfante (bonfante@steptools.com)
//

#include "nodeAptStepMaker.h"
#include "nodeFinder.h"
#include "nodeTolerance.h"
#include "nodeMachineState.h"

NAN_MODULE_INIT(Init) {
    stplib_init();
    machineState::Init(target);
    Tolerance::Init(target);
    Finder::Init(target);
    AptStepMaker::Init(target);
}

NODE_MODULE(StepNC, Init)  

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
#include "nodeAdaptive.h"
#include "nodeUtils.h"

#include <StixCtlCursor.h>

// PACKAGE INIT -
// call node inits for all classes and force step c++ init
//

static CtlEventEnum foo;

NAN_GETTER(GetEventEnum) {
}

NAN_MODULE_INIT(Init) {
    stplib_init();
    machineState::Init(target);
    Tolerance::Init(target);
    Finder::Init(target);
    AptStepMaker::Init(target);
    Adaptive::Init(target);

    READ_ONLY_OBJECT("CtlEvent",CtlEventEnum::singleton());
    READ_ONLY_OBJECT("CtlType",CtlTypeEnum::singleton());
    READ_ONLY_OBJECT("CtlCsys",CtlCsysEnum::singleton());
    READ_ONLY_OBJECT("CtlStatus",CtlStatusEnum::singleton());
    READ_ONLY_OBJECT("Unit",RoseUnitEnum::singleton());

    ENUM_PROPERTY("CTL_POS_END",  STIXCTL_POS_END);
    ENUM_PROPERTY("CTL_POS_START",STIXCTL_POS_START);
    ENUM_PROPERTY("CTL_POS_ARC",  STIXCTL_POS_ARC);
    ENUM_PROPERTY("CTL_POS_VIA1",  STIXCTL_POS_VIA1);
    ENUM_PROPERTY("CTL_POS_VIA2",  STIXCTL_POS_VIA2);
}

NODE_MODULE(StepNC, Init)  


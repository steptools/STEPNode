// $RCSfile: $
// $Revision: $ $Date: $
// Auth: Samson Bonfante (bonfante@steptools.com)
// 
// Copyright (c) 1991-2016 by STEP Tools Inc. 
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

#pragma once
#include <nan.h>
#include <stncapt/APT.h>

class AptStepMaker : public Nan::ObjectWrap {
private:
    apt2step * _apt;
    static AptStepMaker* _singleton;
    static NAN_METHOD(New);
    static inline Nan::Persistent<v8::Function> & constructor() {
	static Nan::Persistent<v8::Function> my_constructor;
	return my_constructor;
    }
    AptStepMaker() { _apt = new apt2step(); };
    ~AptStepMaker() { delete _apt; };
public:
    static apt2step* getApt();
    static NAN_MODULE_INIT(Init);

    //string GetToolNumber(int id)
    static NAN_METHOD(GetToolNumber);
    static NAN_METHOD(OpenProject);

    //void SaveAsModules(v8::String file_name);
    static NAN_METHOD(SaveAsModules);

    //void SaveAsP21(v8::String file_name);
    static NAN_METHOD(SaveAsP21);
};
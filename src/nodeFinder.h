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
#include <stncapt/Find.h>

class Finder : public Nan::ObjectWrap {
private:
    finder * _find;
    static Finder* _singleton;
    static NAN_METHOD(New);
    static inline Nan::Persistent<v8::Function> & constructor() {
	static Nan::Persistent<v8::Function> my_constructor;
	return my_constructor;
    }
    Finder() { _find = new finder(); };
    ~Finder() { delete _find; };
public:
    static NAN_MODULE_INIT(Init);

    //void APIUnitsFeed(System::String^ units);
    static NAN_METHOD(APIUnitsFeed);
    static NAN_METHOD(APIUnitsInches);
    static NAN_METHOD(APIUnitsMM);
    //int GetMainWorkplan();
    static NAN_METHOD(GetMainWorkplan);
    static NAN_METHOD(APIUnitsNative);
    //long GetFeatureID(long ws_id);
    static NAN_METHOD(GetFeatureID);

    //void Open238(String file_name);
    static NAN_METHOD(OpenProject);

    //void SaveAsModules(v8::String file_name);
    static NAN_METHOD(SaveAsModules);

    //void SaveAsP21(v8::String file_name);
    static NAN_METHOD(SaveAsP21);
};
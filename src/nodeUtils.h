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

#pragma once
#include <nan.h>

#define READ_ONLY_PROPERTY(nm,fn) Nan::SetAccessor(target, Nan::New(nm).ToLocalChecked(),fn, 0, v8::Local<v8::Value>(), v8::DEFAULT, v8::ReadOnly)

#define READ_ONLY_OBJECT(nm,obj) Nan::SetAccessor(target, Nan::New(nm).ToLocalChecked(),GetterStaticVal, 0, obj, v8::DEFAULT, v8::ReadOnly)

#define ENUM_PROPERTY(nm,val) Nan::SetAccessor(target, Nan::New(nm).ToLocalChecked(), GetterStaticVal, 0, Nan::New((int32_t)val), v8::DEFAULT, v8::ReadOnly)

//NOTE: caller needs to delete[] lest we end up with a memory leak.
size_t v8StringToChar(v8::Local<v8::Value> in, char* &arr);

v8::Local<v8::Value> CharTov8String(const char* arr);

NAN_GETTER(GetterStaticVal);


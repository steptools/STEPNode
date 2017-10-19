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

#include "nodeUtils.h"

size_t v8StringToChar(v8::Local<v8::Value> in, char* &arr)
{
    ssize_t len = Nan::DecodeBytes(in, Nan::Encoding::UTF8);
    arr = new char[len + 1]();
    Nan::DecodeWrite(arr, len, in, Nan::Encoding::UTF8);
    arr[len + 1] = '\0';
    return len;
}
v8::Local<v8::Value> CharTov8String(const char* arr)
{
    return Nan::Encode(arr, strlen(arr), Nan::Encoding::UTF8);
}


NAN_GETTER(GetterStaticVal) {
    info.GetReturnValue().Set(info.Data());
}


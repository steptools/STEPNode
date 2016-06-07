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

#include "nodeFinder.h"

Finder *Finder::_singleton = nullptr;

NAN_METHOD(Finder::New)
{
    if (info.IsConstructCall())
    {
	if (!info[0]->IsUndefined())
	{
	    return;
	}
	if (_singleton == nullptr)
	    _singleton = new Finder();
	_singleton->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
    }
    else
    {
	return;
    }
}

NAN_MODULE_INIT(Finder::Init)
{
	v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
	tpl->SetClassName(Nan::New("Finder").ToLocalChecked());
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
	Nan::Set(target, Nan::New("Finder").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
	Nan::SetPrototypeMethod(tpl, "SaveAsP21", SaveAsP21);

}

NAN_METHOD(Finder::SaveAsP21)
{
	Finder * find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
	if (find == 0) //Throw Exception
		return;

	if (!info[0]->IsUndefined())
		return;

	if (!info[0]->IsString())
		return;

	v8::String file_name=(v8::String)info[0];
	char* file_name_utf8;

	v8StringToChar(file_name, file_name_utf8);

	//MARSHAL_WIDE_TO_UTF8(file_name, file_name_utf8);


	if (!find->_find->save_file(AS_UTF8(file_name), false)) //Throw Exception
		return;
}


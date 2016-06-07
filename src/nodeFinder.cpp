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
#include "nodeUtils.h"
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

	Nan::SetPrototypeMethod(tpl, "GetMainWorkplan", GetMainWorkplan);
	Nan::SetPrototypeMethod(tpl, "GetFeatureID", GetFeatureID);


    constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("Finder").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());

}

NAN_METHOD(Finder::GetMainWorkplan) {
	Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This());
	if (find == 0) //Throw Exception
		return;
	if (!info[0]->IsUndefined()) //Function shouldn't get any arguments.
		return;
	int rtn = 0;
	int sz;
	if (!find->_find->main(rtn, sz))
		return;//Error in c++ code
	info.GetReturnValue().Set(rtn);
	return;
}

NAN_METHOD(Finder::GetFeatureID){
	Finder* find = Nan::ObjectWrap::Unwrap<Finder>(info.This()); 

	if(info.Length() != 1)
		return;
	if(!info[0]->IsUndefined())
		return;
	if (!info[0]->IsInt32())
		return;

	int feature_id = 0;

	if (!find->_find->feature_id(info[0]->Int32Value(), feature_id))
		return;

	info.GetReturnValue().Set(feature_id);
	return;	
}
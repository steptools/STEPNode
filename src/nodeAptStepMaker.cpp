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

#include "nodeAptStepMaker.h"
#include "nodeUtils.h"
#include <Trace.h>

AptStepMaker* AptStepMaker::_singleton = nullptr;

apt2step* AptStepMaker::getApt() {
    if (_singleton == nullptr)
	_singleton = new AptStepMaker();
    return _singleton->_apt;
}

NAN_METHOD(AptStepMaker::New)
{
    if (info.IsConstructCall())
    {
	if (!info[0]->IsUndefined())
	{
	    return;
	}
	if (_singleton == nullptr)
	    _singleton = new AptStepMaker();
	_singleton->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
    }
    else
    {
	return;
    }
}

NAN_MODULE_INIT(AptStepMaker::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("AptStepMaker").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "OpenProject", OpenProject);

    Nan::SetPrototypeMethod(tpl, "GetToolNumber", GetToolNumber);
	
	Nan::SetPrototypeMethod(tpl, "Rapid", GetToolNumber);

    constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("AptStepMaker").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());

}

NAN_METHOD(AptStepMaker::GetToolNumber)
{
    AptStepMaker * apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (!apt || !(apt->_apt)) return;
    if (!info[0]->IsInt32())
	return; // Throw error

    int id = info[0]->Int32Value();
    const char * tlNum;

    if (!apt->_apt->get_tool_number(id, tlNum))
	return; // Throw error

    char* v8_tlNum;
    //size_t tlNum_len = v8StringToChar(, tlNum);

    //return v8_tlNum;
}

NAN_METHOD(AptStepMaker::NewProject) {
	AptStepMaker * apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
	if (apt == 0) //Throw Exception
		return;
	if (info.Length() != 1) //Requires a new project name
		return;
	if (!info[0]->IsString())
		return;
	char * projname = 0;
	ssize_t projnamelen = v8StringToChar(info[0], projname);

    if (!apt->_apt->new_project(projname)) //Throw
		return;
	return; // SUCCESS
}

NAN_METHOD(AptStepMaker::OpenProject) {
    AptStepMaker* apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
    if (apt == 0) //Throw Exception
	return;
    if (info.Length() != 1) //Function should get one argument.
	return;
    if (!info[0]->IsString())
	return;
    char * fname = 0;
    ssize_t fnamelen = v8StringToChar(info[0], fname);
    if (!apt->_apt->read_238_file(fname)) //TODO: Handle Error.
	return;
    return; //Success finding, return.
}

NAN_METHOD(AptStepMaker::Rapid) {
	AptStepMaker * apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
	if (apt == 0) //Throw Exception
		return;
	if (info.Length() != 0) //Function requires no arguments.
		return;
		
	Trace t(apt->tc, "Rapid");
    if (!apt->_apt->rapid())
		THROW_ERROR(t);
}

NAN_METHOD(AptStepMaker::Rawpiece) {
	AptStepMaker * apt = Nan::ObjectWrap::Unwrap<AptStepMaker>(info.This());
	if (apt == 0) //Throw Exception
		return;
	if (info.Length() != 1) //Function requires exactly one argument.
		return;
	if (!info[0]->IsString()) //Requires rawpiece filename
		return;
	char * filename = v8StringToChar(info[0], filename);
	MARSHAL_WIDE_TO_UTF8(filename,filename_utf8);

    Trace t(apt->tc, "Rawpiece");
    t.addParam(BPARAM(filename));

    if (!apt->m_maker->rawpiece(AS_UTF8(filename))) //Throw exception
		return;
	
}

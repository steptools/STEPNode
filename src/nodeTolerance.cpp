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
//
// Author: Samson Bonfante (bonfante@steptools.com)
//

#include "nodeTolerance.h"
#include "nodeUtils.h"

Tolerance * Tolerance::_singleton = nullptr;
NAN_METHOD(Tolerance::New)
{
    if (info.IsConstructCall())
    {
	if (!info[0]->IsUndefined())
	{
	    return;
	}
	if (_singleton == nullptr)
	    _singleton = new Tolerance();
	_singleton->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
    }
    else

    {
	return;
    }
}

NAN_MODULE_INIT(Tolerance::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("Tolerance").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "GetDatumFaceAll", GetDatumFaceAll);
    Nan::SetPrototypeMethod(tpl, "GetDatumLabel", GetDatumLabel);
    Nan::SetPrototypeMethod(tpl, "GetProbeResults", GetProbeResults);
    Nan::SetPrototypeMethod(tpl, "GetToleranceAllCount", GetToleranceAllCount);
    Nan::SetPrototypeMethod(tpl, "GetToleranceAllNext", GetToleranceAllNext);
    Nan::SetPrototypeMethod(tpl, "GetToleranceAll", GetToleranceAll);
    Nan::SetPrototypeMethod(tpl, "GetToleranceDatumAll", GetToleranceDatumAll);
    Nan::SetPrototypeMethod(tpl, "GetToleranceFaceAll", GetToleranceFaceAll);
    Nan::SetPrototypeMethod(tpl, "GetToleranceModifierAll", GetToleranceModifierAll);
    Nan::SetPrototypeMethod(tpl, "GetTolerancePlusMinus", GetTolerancePlusMinus);
    Nan::SetPrototypeMethod(tpl, "GetToleranceStatus", GetToleranceStatus);
    Nan::SetPrototypeMethod(tpl, "GetToleranceType", GetToleranceType);
    Nan::SetPrototypeMethod(tpl, "GetToleranceUnit", GetToleranceUnit);
    Nan::SetPrototypeMethod(tpl, "GetToleranceValue", GetToleranceValue);
    Nan::SetPrototypeMethod(tpl, "GetWorkpieceDatumAllAll", GetWorkpieceDatumAllAll);
    Nan::SetPrototypeMethod(tpl, "GetWorkingstepToleranceAll", GetWorkingstepToleranceAll);
    Nan::SetPrototypeMethod(tpl, "GetWorkpieceOfTolerance", GetWorkpieceOfTolerance);
    Nan::SetPrototypeMethod(tpl, "GetWorkpieceToleranceAll", GetWorkpieceToleranceAll);
    Nan::SetPrototypeMethod(tpl, "ResetAllToleranceMeasuredValue", ResetAllToleranceMeasuredValue);
    Nan::SetPrototypeMethod(tpl, "SetToleranceMeasuredValue", SetToleranceMeasuredValue);


    constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("Tolerance").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());

}

NAN_METHOD(Tolerance::GetDatumFaceAll)
{
    Tolerance * tol = Nan::ObjectWrap::Unwrap<Tolerance>(info.This());
    if (tol == 0) //Throw Exception
	return;
    if (info.Length() != 1) //Throw Exception
	return;
    if(!info[0]->IsInt32())
	return;

    Nan::Maybe<int32_t> dat_id = Nan::To<int32_t>(info[0]);

    int size = 0;
    if (!tol->_tol->get_datum_face_count(dat_id.FromJust(), size)) //Throw Exception
	return;

    // Create a new empty array.
    v8::Local<v8::Array> array = Nan::New<v8::Array>();
    int face_id = 0;
    if(size >= 0){
	for(int i = 0; i < size; i++){
	    if (!tol->_tol->get_datum_face_next(dat_id.FromJust(), i, face_id)) //Throw Exception
		return;
	    else{
		array->Set(i,Nan::New(face_id));
	    }
	}
    }

    info.GetReturnValue().Set(array);
    return;
}

NAN_METHOD(Tolerance::GetDatumLabel)
{
    Tolerance* tol = Nan::ObjectWrap::Unwrap<Tolerance>(info.This());
    if(!tol)
	return;
    if(info.Length()!=1)
	return;
    if(!info[0]->IsNumber())
	return;
    Nan::Maybe<int32_t> dat_id = Nan::To<int32_t>(info[0]);
    char * label = 0;
    if(!tol->_tol->get_datum_label(dat_id.FromJust(), (const char *&)label))
	return;
    info.GetReturnValue().Set(CharTov8String(label));
    return;
}

NAN_METHOD(Tolerance::GetProbeResults) {
	Tolerance * tol = Nan::ObjectWrap::Unwrap<Tolerance>(info.This());
	if (tol == 0)
		return;
	if (info.Length() != 4)
		return;
	char outstring[12000];
	Nan::Maybe<int32_t> wsid = Nan::To<int32_t>(info[0]);
	Nan::Maybe<double> x = Nan::To<double>(info[1]);
	Nan::Maybe<double> y = Nan::To<double>(info[2]);
	Nan::Maybe<double> z = Nan::To<double>(info[3]);
	tol->_tol->mtconnect_face_probe_result_data(wsid.FromJust(), x.FromJust(), y.FromJust(), z.FromJust(),outstring);
	info.GetReturnValue().Set(CharTov8String(outstring));
	return;
}

NAN_METHOD(Tolerance::GetToleranceAllCount)
{
    Tolerance* tol = Nan::ObjectWrap::Unwrap<Tolerance>(info.This());
    if(!tol)
	return;
    if(info.Length()!=0)
	return;
    int size = 0;
    if(!tol->_tol->tolerance_count(size))
	return;
    info.GetReturnValue().Set(size);
    return;
}

NAN_METHOD(Tolerance::GetToleranceAllNext)
{
    Tolerance* tol = Nan::ObjectWrap::Unwrap<Tolerance>(info.This());
    if(!tol)
	return;
    if(info.Length()!=1)
	return;
    if(!info[0]->IsNumber())
	return;
    int tol_id = 0;
    Nan::Maybe<int32_t> index = Nan::To<int32_t>(info[0]);
    if (!tol->_tol->tolerance_next(index.FromJust(), tol_id))
	return;
    info.GetReturnValue().Set(tol_id);
    return;
}

NAN_METHOD(Tolerance::GetToleranceAll) {
    Tolerance * tol = Nan::ObjectWrap::Unwrap<Tolerance>(info.This());
    if (tol == 0) //Throw Exception
	return;
    if (info.Length() != 0) //Throw Exception
	return;

    int size = 0;
    if (!tol->_tol->tolerance_count(size)) //Throw Exception
	return;

    // Create a new empty array.
    v8::Local<v8::Array> array = Nan::New<v8::Array>();
    int tol_id = 0;
    if(size >= 0){
        for(int i = 0; i < size; i++){
            if (!tol->_tol->tolerance_next(i, tol_id)) //Throw Exception
                return;
            else{
                array->Set(i,Nan::New(tol_id));
            }
        }
    }

    info.GetReturnValue().Set(array);
    return;
}

NAN_METHOD(Tolerance::GetToleranceDatumAll) {
    Tolerance * tol = Nan::ObjectWrap::Unwrap<Tolerance>(info.This());
    if (tol == 0) //Throw Exception
	return;
    if (info.Length() != 1) //Throw Exception
	return;
    if (!info[0]->IsNumber()) // throw exception
	return;

    Nan::Maybe<int32_t> tol_id = Nan::To<int32_t>(info[0]);

    int count = 0;
    if (!tol->_tol->num_tolerance_datum(tol_id.FromJust(), count)) //Throw Exception
	return;

    // Create a new empty array.
    v8::Local<v8::Array> array = Nan::New<v8::Array>();
    int dat = 0;
    const char * szName;
    if(count >= 0){
        for(int i = 0; i < count; i++){
            if (!tol->_tol->next_tolerance_datum(tol_id.FromJust(), i, dat, szName)) //Throw Exception
                return;
            else{
                array->Set(i,Nan::New(dat));
            }
        }
    }

    info.GetReturnValue().Set(array);
    return;
}

NAN_METHOD(Tolerance::GetToleranceFaceAll) {
    Tolerance * tol = Nan::ObjectWrap::Unwrap<Tolerance>(info.This());
    if (tol == 0) //Throw Exception
	return;
    if (info.Length() != 1) //Throw Exception
	return;
    if (!info[0]->IsNumber())	// throw exception
	return;

    Nan::Maybe<int32_t> tol_id = Nan::To<int32_t>(info[0]);

    int size = 0;
    if (!tol->_tol->tolerance_face_count(tol_id.FromJust(), size)) //Throw Exception
	return;

    // Create a new empty array.
    v8::Local<v8::Array> array = Nan::New<v8::Array>();
    int face_id = 0;
    if(size >= 0){
        for(int i = 0; i < size; i++){
            if (!tol->_tol->tolerance_face_next(tol_id.FromJust(), i, face_id)) //Throw Exception
                return;
            else{
                array->Set(i,Nan::New(face_id));
            }
        }
    }

    info.GetReturnValue().Set(array);
    return;
}

NAN_METHOD(Tolerance::GetToleranceModifierAll) {
    Tolerance * tol = Nan::ObjectWrap::Unwrap<Tolerance>(info.This());
    if (tol == 0) //Throw Exception
	return;
    if (info.Length() != 1) //Throw Exception
	return;
    if (!info[0]->IsNumber()) // throw exception
	return;

    Nan::Maybe<int32_t> tol_id = Nan::To<int32_t>(info[0]);

    int count = 0;
    if (!tol->_tol->num_tolerance_modifier(tol_id.FromJust(), count)) //Throw Exception
	return;

    // Create a new empty array.
    v8::Local<v8::Array> array = Nan::New<v8::Array>();
    char * mod = 0;
    if(count >= 0){
        for(int i = 0; i < count; i++){
            if (!tol->_tol->next_tolerance_modifier(tol_id.FromJust(), i, (const char *&)mod)) //Throw Exception
                return;
            else{
                array->Set(i,CharTov8String(mod));
            }
        }
    }

    info.GetReturnValue().Set(array);
    return;
}

NAN_METHOD(Tolerance::GetTolerancePlusMinus) {
    Tolerance * tol = Nan::ObjectWrap::Unwrap<Tolerance>(info.This());
    if (tol == 0) //Throw Exception
	return;
    if (info.Length() != 1)
	return;
    if (!info[0]->IsNumber())
	return;
    
    Nan::Maybe<int32_t> tol_id = Nan::To<int32_t>(info[0]);
    double upper = 0.0;
    double lower = 0.0;
    int flag = 0;
    if (!tol->_tol->tolerance_lower_and_upper(tol_id.FromJust(), flag, lower, upper))
	return;
    
    v8::Local<v8::Object> jsonReturn = Nan::New<v8::Object>();
    Nan::Set(jsonReturn, CharTov8String("flag"), Nan::New(flag != 0));
    Nan::Set(jsonReturn, CharTov8String("lower"), Nan::New(lower));
    Nan::Set(jsonReturn, CharTov8String("upper"), Nan::New(upper));
    
    info.GetReturnValue().Set(jsonReturn);
    return;
}

NAN_METHOD(Tolerance::GetToleranceStatus) {
    Tolerance * tol = Nan::ObjectWrap::Unwrap<Tolerance>(info.This());
    if (tol == 0) //Throw Exception
	return;
    if (info.Length() != 1)
	return;
    if (!info[0]->IsNumber())
	return;

    Nan::Maybe<int32_t> tol_id = Nan::To<int32_t>(info[0]);
    const char * rtn;
    if (!tol->_tol->tolerance_status(tol_id.FromJust(), rtn))
	return;
    info.GetReturnValue().Set(CharTov8String(rtn));
    return;
}

NAN_METHOD(Tolerance::GetToleranceType) {
    Tolerance* tol = Nan::ObjectWrap::Unwrap<Tolerance>(info.This());
    if(!tol)
	return;
    if(info.Length()!=1)
	return;
    if(!info[0]->IsNumber())
	return;
    const char * type = 0;
    Nan::Maybe<int32_t> tol_id = Nan::To<int32_t>(info[0]);
    if (!tol->_tol->tolerance_type (tol_id.FromJust(), type))
	return;
    info.GetReturnValue().Set(CharTov8String((char *)type));
    return;

}

NAN_METHOD(Tolerance::GetToleranceUnit) {
    Tolerance* tol = Nan::ObjectWrap::Unwrap<Tolerance>(info.This());
    if(!tol)
	return;
    if(info.Length()!=1)
	return;
    if(!info[0]->IsNumber())
	return;
    const char * unit = 0;
    Nan::Maybe<int32_t> tol_id = Nan::To<int32_t>(info[0]);
    if (!tol->_tol->tolerance_unit (tol_id.FromJust(), unit))
	return;
    info.GetReturnValue().Set(CharTov8String((char*) unit));
    return;
}

NAN_METHOD(Tolerance::GetToleranceValue) {
    Tolerance* tol = Nan::ObjectWrap::Unwrap<Tolerance>(info.This());
    if(!tol)
	return;
    if(info.Length()!=1)
	return;
    if(!info[0]->IsNumber())
	return;
    double value;
    Nan::Maybe<int32_t> tol_id = Nan::To<int32_t>(info[0]);
    if (!tol->_tol->tolerance_value (tol_id.FromJust(), value))
	return;
    info.GetReturnValue().Set(value);
    return;
}

NAN_METHOD(Tolerance::GetWorkpieceDatumAllAll){
    Tolerance * tol = Nan::ObjectWrap::Unwrap<Tolerance>(info.This());
    if (tol == 0) //Throw Exception
	return;
    if (info.Length() != 1) //Throw Exception
	return;
    if (!info[0]->IsNumber())
	return;

    Nan::Maybe<int32_t> wp_id = Nan::To<int32_t>(info[0]);

    int count = 0;
    if (!tol->_tol->wp_all_datum_count(wp_id.FromJust(), count)) //Throw Exception
	return;

    // Create a new empty array.
    v8::Local<v8::Array> array = Nan::New<v8::Array>();
    int dat_id = 0;
    const char *strNme1;
    const char *strNme2;
    if(count >= 0){
        for(int i = 0; i < count; i++){
            if (!tol->_tol->wp_all_datum_next(wp_id.FromJust(), i, strNme1, strNme2, dat_id)) //Throw Exception
                return;
            else{
                array->Set(i,Nan::New(dat_id));
            }
        }
    }

    info.GetReturnValue().Set(array);
    return;
}

NAN_METHOD(Tolerance::GetWorkingstepToleranceAll) {
    Tolerance * tol = Nan::ObjectWrap::Unwrap<Tolerance>(info.This());
    if (tol == 0) //Throw Exception
	return;
    if (info.Length() != 1) //Throw Exception
	return;
    if (!info[0]->IsNumber())
	return;

    Nan::Maybe<int32_t> ws = Nan::To<int32_t>(info[0]);

    rose_uint_vector tols;
    if (!tol->_tol->ws_tolerance_all(ws.FromJust(), tols)) //Throw Exception
	return;

    // Create a new empty array.
    v8::Local<v8::Array> array = Nan::New<v8::Array>();
    for (uint i = 0,sz=tols.size(); i < sz; i++) {
	array->Set(i, Nan::New(tols[i]));
    }

    info.GetReturnValue().Set(array);
    return;
}

NAN_METHOD(Tolerance::GetWorkpieceOfTolerance) {
    Tolerance * tol = Nan::ObjectWrap::Unwrap<Tolerance>(info.This());
    if (tol == 0) //Throw Exception
        return;
    if (info.Length() != 1) //Throw Exception
        return;
    if (!info[0]->IsNumber())
        return;

    Nan::Maybe<int32_t> tol_id = Nan::To<int32_t>(info[0]);

    int wp_id = 0;

    if (!tol->_tol->tolerance_workpiece (tol_id.FromJust(), wp_id))
	return; // throw exception

    info.GetReturnValue().Set(wp_id);
}

NAN_METHOD(Tolerance::GetWorkpieceToleranceAll) {
    Tolerance * tol = Nan::ObjectWrap::Unwrap<Tolerance>(info.This());
    if (tol == 0) //Throw Exception
	return;
    if (info.Length() != 1) //Throw Exception
	return;
    if (!info[0]->IsNumber())
	return;

    Nan::Maybe<int32_t> wp = Nan::To<int32_t>(info[0]);

    int size = 0;
    if (!tol->_tol->wp_extended_tolerance_count(wp.FromJust(), size)) //Throw Exception
	return;

    // Create a new empty array.
    v8::Local<v8::Array> array = Nan::New<v8::Array>();
    int tol_id = 0;
    if(size >= 0){
        for(int i = 0; i < size; i++){
            if (!tol->_tol->wp_extended_tolerance_next(wp.FromJust(), i, tol_id)) //Throw Exception
                return;
            else{
                array->Set(i,Nan::New(tol_id));
            }
        }
    }

    info.GetReturnValue().Set(array);
    return;
}
NAN_METHOD(Tolerance::ResetAllToleranceMeasuredValue) {
    Tolerance * tol = Nan::ObjectWrap::Unwrap<Tolerance>(info.This());
    if (tol == 0) //Throw Exception
	return;
    if (info.Length() != 0) //Throw Exception
	return;
    tol->_tol->reset_all_tolerance_current_value();
}

NAN_METHOD(Tolerance::SetToleranceMeasuredValue){
    Tolerance * tol = Nan::ObjectWrap::Unwrap<Tolerance>(info.This());
    if (tol == 0) //Throw Exception
	return;
    if (info.Length() != 2) //Throw Exception
	return;
    if (info[0]->IsUndefined())
	return;
    if (!info[0]->IsString())
	return;
    if (!info[1]->IsNumber())
	return;
    char * uuid;
    v8StringToChar(info[0], uuid);
    Nan::Maybe<double> value = Nan::To<double>(info[1]);
    tol->_tol->set_tolerance_current_value(uuid,value.FromJust());
    return;
}

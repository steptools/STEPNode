# Extending The STEPNode Package

The STEPNode package implements functions using [Native Abstractions
for Node](https://github.com/nodejs/nan) to simplify the interaction
with the Node API.

To add a new function to the Node Module:

- Declare C++ Function in Header
- Add the Function to the Module Initializer
- Implement the C++ Function



## Declare C++ Function in Header

The C++ function for a node method is declared as a static class
function and wrapped in the NAN_METHOD macro, which should look like
this:

``` 
//int Reset();
static NAN_METHOD(Reset);
```

Please include a comment that documents the function prototype. The
NAN_METHOD macro does not show the arguments, which are passed as a
single opaque object.  The comment is the only way that you or anyone
else can easily see how the function should be used.

All function names should be in `CamelCase`, with capitalized
abbreviations.



## Add the Function to the Module Initializer

Each class has a `MODULE_INIT` function like the following. It
registers the class and all of the member functions when the node
module is imported. Add a SetPrototypeMethod() call to the function
whenever you add a new member function. The example below declares an
AdvanceState function.

If you forget to declare the function, it won\'t be usable on the
client side. The compiler won\'t warn you if you forget to do this!

``` {.code}
NAN_MODULE_INIT(Adaptive::Init)

// add to Init function body in CPP file
Nan::SetPrototypeMethod(tpl, "Reset", Reset);
```

If you are adding a new class, you must add a call to the class Init()
to the package Init() function in `nodeStepNC.cpp`



## Implement the C++ Function

The function is implemented as a static method on the C++ class.  The
function implementation is wrapped by NAN_METHOD, as with the header
declaration.

```
NAN_METHOD(Adaptive::Reset)
{
    Adaptive* ao = Nan::ObjectWrap::Unwrap<Adaptive>(info.This());
    if (!ao) return; // exception
    
    ao->f_ctl->reset();
}
```

The function is passed a single `info` object of type
`Nan::FunctionCallbackInfo`.  The `info` object holds the pointer to
the object that the function was invoked on, all of the arguments that
were passed in, and the return value.

As you can see in the example above, the first thing that the function
does is to `Unwrap()` the This pointer into a proper C++ object
pointer, and then calls a C++ function on the object.


The info object also has a Length() function and index operator (\[\])
to get each of the parameters passed to the function.  Node functions
can take any number of arguments, and it is the responsibility of the
function to interpret them.

```
if(info.Length() > 0)		// We have an argument. 
if(!(info[0]->IsUndefined())) 	// Another way to check
```

Javascript does not have strong typing the function must confirm that
variables are the right type, and

```
if(info.Length()!=2) return; //Wrong number of arguments
if (!info[0]->IsString()) return; // must be a string
if (!info[1]->IsString()) return; // must be a string
```

The following functions convert between Javascript strings and the
UTF-8 null-terminated strings (const char*) used by STEP Tools C++
functions.  If you use v8StringToChar(), you must call delete\[\] on
the pointer before your function returns.

```
size_t v8StringToChar(v8::Local<v8::Value> in, char* &arr);	//To C++

v8::Local<v8::Value> CharTov8String(char* arr);	     		//To JS

// See below for usage in functions

```


## Arguments and Return Values

The STEPNode functions work with a small number of basic types:
strings, entity ids, numbers, and booleans. Return values are either
simple number types (bool, int, double) or objects.

The `info` object holds all of the parameters as `v8::Value`
types. The type conversions return \"maybe\" types, which have
different options for handling nothing values.  Examples for getting
and returning the different types of values are shown below:

```
// entity id arguement
long eid = Nan::To<int32_t>(info[0]).FromJust();
long eid = Nan::To<int64_t>(info[0]).FromJust();
bool flg = Nan::To<bool>(info[0]).FromJust();
double x = Nan::To<double>(info[0]).FromJust();

// string must convert from v8 to C string.  We have
// wrote these functions to wrap the nan encode/decode.
// They assume UTF8
// size_t v8StringToChar(v8::Local<v8::Value> inval, char* & cstr);
char * buf
v8StringToChar(info[0], buf);
delete[] cstr;  // clean up before returning

// Returning values
info.GetReturnValue().Set((flag != 0)); // boolean
info.GetReturnValue().Set((int32_t)eid); // entity id
info.GetReturnValue().Set((int32_t)(obj? obj->entity_id(): 0));
info.GetReturnValue().Set(x);       // double

// string must convert from C to v8 string.  Assumes UTF8
// v8::Local<v8::Value> CharTov8String(char* cstr);
info.GetReturnValue().Set(CharTov8String((char*) buf));
```


# Contributing Your Changes

Thank you for taking the time to contribute and we look forward to
your pull requests!

Your contribution must be compatible with the project license (Apache
2.0) and you must certify that you have the right to pass it on under
that license as set forth in the Developer Certificate of Origin (DCO)
shown below.

```text
Developer Certificate of Origin
Version 1.1

Copyright (C) 2004, 2006 The Linux Foundation and its contributors.
660 York Street, Suite 102,
San Francisco, CA 94110 USA

Everyone is permitted to copy and distribute verbatim copies of this
license document, but changing it is not allowed.


Developer's Certificate of Origin 1.1

By making a contribution to this project, I certify that:

(a) The contribution was created in whole or in part by me and I
    have the right to submit it under the open source license
    indicated in the file; or

(b) The contribution is based upon previous work that, to the best
    of my knowledge, is covered under an appropriate open source
    license and I have the right under that license to submit that
    work with modifications, whether created in whole or in part
    by me, under the same open source license (unless I am
    permitted to submit under a different license), as indicated
    in the file; or

(c) The contribution was provided directly to me by some other
    person who certified (a), (b) or (c) and I have not modified
    it.

(d) I understand and agree that this project and the contribution
    are public and that a record of the contribution (including all
    personal information I submit with it, including my sign-off) is
    maintained indefinitely and may be redistributed consistent with
    this project or the open source license(s) involved.
```

To indicate that you certify the above, add a line to your description
of the contribution saying "Signed-off-by:" followed by your real name
and email address.  A sample line is shown below:

```
Signed-off-by: Random J Developer <random@developer.example.org>
```

You can automatically add a Signed-off-by line at the end of your
commit log message by calling `git commit -s` or `git commit
--signoff`.

#include <napi.h>
#include <string>
#include <iostream>
#include "libCBNS.h"

using namespace Napi;

Value Add(const CallbackInfo &args){
    Env env = args.Env();
    if(args.Length() < 4){
        TypeError::New(env,"Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }       

    if(!args[0].IsNumber() || !args[1].IsNumber() || !args[2].IsNumber() || !args[3].IsNumber()){
        TypeError::New(env, "Wrong argument types").ThrowAsJavaScriptException();
        return env.Null();
    }

    float A_real = args[0].As<Number>().FloatValue();
    float A_imag = args[1].As<Number>().FloatValue();
    float B_real = args[2].As<Number>().FloatValue();
    float B_imag = args[3].As<Number>().FloatValue();

    complex<float> A(A_real, A_imag);
    complex<float> B(B_real, B_imag);

    return String::From(env,  print(A, B, addComplex(A, B), "+"));
}

Value Minus(const CallbackInfo &args){
    Env env = args.Env();
    if(args.Length() < 4){
        TypeError::New(env,"Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }       

    if(!args[0].IsNumber() || !args[1].IsNumber() || !args[2].IsNumber() || !args[3].IsNumber()){
        TypeError::New(env, "Wrong argument types").ThrowAsJavaScriptException();
        return env.Null();
    }

    float A_real = args[0].As<Number>().FloatValue();
    float A_imag = args[1].As<Number>().FloatValue();
    float B_real = args[2].As<Number>().FloatValue();
    float B_imag = args[3].As<Number>().FloatValue();

    complex<float> A(A_real, A_imag);
    complex<float> B(B_real, B_imag);

    return String::From(env,  print(A, B, subComplex(A, B), "-"));
}

Value Times(const CallbackInfo &args){
    Env env = args.Env();
    if(args.Length() < 4){
        TypeError::New(env,"Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }       

    if(!args[0].IsNumber() || !args[1].IsNumber() || !args[2].IsNumber() || !args[3].IsNumber()){
        TypeError::New(env, "Wrong argument types").ThrowAsJavaScriptException();
        return env.Null();
    }

    float A_real = args[0].As<Number>().FloatValue();
    float A_imag = args[1].As<Number>().FloatValue();
    float B_real = args[2].As<Number>().FloatValue();
    float B_imag = args[3].As<Number>().FloatValue();

    complex<float> A(A_real, A_imag);
    complex<float> B(B_real, B_imag);

    return String::From(env,  print(A, B, multiComplex(A, B), "x"));
}

Value Divide(const CallbackInfo &args){
    Env env = args.Env();
    if(args.Length() < 4){
        TypeError::New(env,"Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }       

    if(!args[0].IsNumber() || !args[1].IsNumber() || !args[2].IsNumber() || !args[3].IsNumber()){
        TypeError::New(env, "Wrong argument types").ThrowAsJavaScriptException();
        return env.Null();
    }

    float A_real = args[0].As<Number>().FloatValue();
    float A_imag = args[1].As<Number>().FloatValue();
    float B_real = args[2].As<Number>().FloatValue();
    float B_imag = args[3].As<Number>().FloatValue();

    complex<float> A(A_real, A_imag);
    complex<float> B(B_real, B_imag);

    return String::From(env,  print(A, B, divComplex(A, B), "/"));
}
    

Value toCBNS(const CallbackInfo &args){
    Env env = args.Env();
    if(args.Length() < 4){
        TypeError::New(env,"Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }       

    if(!args[0].IsNumber() || !args[1].IsNumber() || !args[2].IsNumber() || !args[3].IsNumber()){
        TypeError::New(env, "Wrong argument types").ThrowAsJavaScriptException();
        return env.Null();
    }

    // float A_real = args[0].As<Number>().FloatValue();
    // float A_imag = args[1].As<Number>().FloatValue();
    // float B_real = args[2].As<Number>().FloatValue();
    // float B_imag = args[3].As<Number>().FloatValue();
    float C_real = args[4].As<Number>().FloatValue();
    float C_imag = args[5].As<Number>().FloatValue();

    complex<float> C(C_real, C_imag);

    return String::From(env,  printToCBNS(C));
}

Value toComplex(const CallbackInfo &args){
    Env env = args.Env();
    if(args.Length() < 4){
        TypeError::New(env,"Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }       

    if(!args[0].IsNumber() || !args[1].IsNumber() || !args[2].IsNumber() || !args[3].IsNumber()){
        TypeError::New(env, "Wrong argument types").ThrowAsJavaScriptException();
        return env.Null();
    }

    // float A_real = args[0].As<Number>().FloatValue();
    // float A_imag = args[1].As<Number>().FloatValue();
    // float B_real = args[2].As<Number>().FloatValue();
    // float B_imag = args[3].As<Number>().FloatValue();
    // float C_real = args[4].As<Number>().FloatValue();
    // float C_imag = args[5].As<Number>().FloatValue();
    string str = args[6].ToString().Utf8Value();


    return String::From(env,  printToComplex(str));
}


Object Initialize(Env env, Object exports){
    exports.Set(String::New(env,"add"), Function::New(env,Add));
    exports.Set(String::New(env,"minus"), Function::New(env,Minus));
    exports.Set(String::New(env,"times"), Function::New(env,Times));
    exports.Set(String::New(env,"divide"), Function::New(env,Divide));
    exports.Set(String::New(env,"toCBNS"), Function::New(env,toCBNS));
    exports.Set(String::New(env,"toComplex"), Function::New(env,toComplex));
    return exports;
}

NODE_API_MODULE(addon, Initialize)
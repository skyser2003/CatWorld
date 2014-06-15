#include "ServerModule.h"

v8::Persistent<v8::Function> ServerModule::constructor;
ServerLib ServerModule::serverLib;


void ServerModule::Export(Handle<Object> exports)
{
	// Prepare constructor template
	auto tpl = FunctionTemplate::New(New);
	tpl->SetClassName(String::NewSymbol("Server"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Prototype
	tpl->PrototypeTemplate()->Set(String::NewSymbol("parse"),
		FunctionTemplate::New(Parse)->GetFunction());
	constructor = Persistent<Function>::New(tpl->GetFunction());
	exports->Set(String::NewSymbol("Server"), constructor);
}

Handle<Value> ServerModule::New(const Arguments& args) {
	HandleScope scope;

	if (args.IsConstructCall()) {
		// Invoked as constructor: `new MyObject(...)`
		auto* obj = new ServerModule();
		obj->Wrap(args.This());
		return args.This();
	}
	else {
		// Invoked as plain function `MyObject(...)`, turn into construct call.
		const int argc = 1;
		Local<Value> argv[argc] = { args[0] };
		return scope.Close(constructor->NewInstance(argc, argv));
	}
}

Handle<Value> ServerModule::Parse(const v8::Arguments& args)
{
	HandleScope scope;
	serverLib.Parse();

	return scope.Close(Null());
}

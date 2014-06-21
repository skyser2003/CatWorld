#include "ServerModule.h"

#include <fstream>

v8::Persistent<v8::Function> ServerModule::constructor;
ServerLib ServerModule::serverLib;
v8::Local<v8::Object> ServerModule::sendFunc;

void ServerModule::Export(Handle<Object> exports)
{
	// Prepare constructor template
	auto tpl = FunctionTemplate::New(New);
	tpl->SetClassName(String::NewSymbol("Server"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Prototype
	tpl->PrototypeTemplate()->Set(String::NewSymbol("parse"),
		FunctionTemplate::New(Parse)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("onSendMsg"),
		FunctionTemplate::New(SetSendFunction)->GetFunction());
	constructor = Persistent<Function>::New(tpl->GetFunction());
	exports->Set(String::NewSymbol("Server"), constructor);
}

Handle<Value> ServerModule::New(const Arguments& args) {
	HandleScope scope;

	if (args.IsConstructCall()) {
		serverLib.Init();

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
	int msg = args[0]->Int32Value();
	auto bufferObj = args[1]->ToObject();
	int length = bufferObj->GetIndexedPropertiesExternalArrayDataLength();
	void* buffer = static_cast<void*>(bufferObj->GetIndexedPropertiesExternalArrayData());

	serverLib.Parse(msg, length, buffer);

	return scope.Close(Null());
}

void ServerModule::Send(int msg, google::protobuf::Message& pks)
{
	void* arr = malloc(pks.ByteSize());
	pks.SerializeToArray(arr, pks.ByteSize());
	Local<Value> args[] = { Number::New(msg), External::New(arr) };
	printf("%s", sendFunc->IsExternal());
	sendFunc->CallAsFunction(Context::GetCurrent()->Global(), 2, args);
	free(arr);
}

Handle<Value> ServerModule::SetSendFunction(const v8::Arguments& args)
{
	HandleScope scope;

	sendFunc = args[0]->ToObject();

	// Set ServerLib callback
	serverLib.SetSendFunction([](int msg, google::protobuf::Message& pks)
	{
		ServerModule::Send(msg, pks);
	});

	return scope.Close(Null());
}
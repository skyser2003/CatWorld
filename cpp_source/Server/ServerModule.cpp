#include "stdafx.h"
#include "ServerModule.h"

#include "NodeCallback.h"

v8::Persistent<v8::Function> ServerModule::constructor;
ServerLibBroker ServerModule::broker;
v8::Persistent<v8::Function> ServerModule::sendFunc;
v8::Persistent<v8::Function> ServerModule::msgStructGetFunc;

void ServerModule::Export(Handle<Object> exports)
{
	// Prepare constructor template
	auto tpl = FunctionTemplate::New(New);
	tpl->SetClassName(String::NewSymbol("Server"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Prototype
	tpl->PrototypeTemplate()->Set(String::NewSymbol("init"),
		FunctionTemplate::New(Init)->GetFunction());

	tpl->PrototypeTemplate()->Set(String::NewSymbol("parse"),
		FunctionTemplate::New(Parse)->GetFunction());

	tpl->PrototypeTemplate()->Set(String::NewSymbol("onSendMsg"),
		FunctionTemplate::New(SetSendFunction)->GetFunction());

	tpl->PrototypeTemplate()->Set(String::NewSymbol("setRootPath"),
		FunctionTemplate::New(SetRootPath)->GetFunction());

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

Handle<Value> ServerModule::Init(const Arguments& args)
{
	HandleScope scope;

	broker.Init();

	return scope.Close(Undefined());
}

Handle<Value> ServerModule::Parse(const v8::Arguments& args)
{
	HandleScope scope;

	v8::String::Utf8Value param1(args[0]->ToString());
	std::string uid = *param1;
	int msg = args[1]->Int32Value();
	auto bufferObj = args[2]->ToObject();
	int length = bufferObj->GetIndexedPropertiesExternalArrayDataLength();
	void* buffer = static_cast<void*>(bufferObj->GetIndexedPropertiesExternalArrayData());

	broker.Parse(uid, msg, length, buffer);

	return scope.Close(Undefined());
}

void ServerModule::Send(int msg, google::protobuf::Message& pks)
{
	auto* nodeCallback = new NodeCallback();

	int pksLength = pks.ByteSize();
	void* arr = malloc(pksLength);
	pks.SerializeToArray(arr, pksLength);

	nodeCallback->Init([msg, arr, pksLength, nodeCallback]()
	{
		auto* buffer = node::Buffer::New(reinterpret_cast<const char*>(arr), pksLength);
		auto dummy = Local<Object>::New(buffer->handle_);

		Local<Value> args[] = { Number::New(msg), dummy };
		sendFunc->CallAsFunction(Context::GetCurrent()->Global(), 2, args);
		free(arr);
	});

	nodeCallback->Send();
}

Handle<Value> ServerModule::SetSendFunction(const v8::Arguments& args)
{
	HandleScope scope;

	sendFunc = Persistent<Function>::New(args[0].As<Function>());

	if (sendFunc->IsFunction() == false)
	{
		return scope.Close(Undefined());
	}

	// Set ServerLib callback
	broker.SetSendFunction([](int msg, google::protobuf::Message& pks)
	{
		ServerModule::Send(msg, pks);
	});

	return scope.Close(Undefined());
}

Handle<Value> ServerModule::SetRootPath(const v8::Arguments& args)
{
	HandleScope scope;

	v8::String::Utf8Value param1(args[0]->ToString());
	std::string rootPath = *param1;
	std::replace(rootPath.begin(), rootPath.end(), '\\', '/');

	broker.SetRootPath(rootPath + "/");

	return scope.Close(Undefined());
}
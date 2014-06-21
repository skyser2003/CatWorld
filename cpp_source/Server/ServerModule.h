#pragma once

#include <node.h>
#include "ServerLib.h"

using namespace v8;

class ServerModule : public node::ObjectWrap
{
public:
	static void Export(Handle<Object> exports);
private:
	static Handle<Value> New(const Arguments& args);
	static Handle<Value> Parse(const v8::Arguments& args);
	static void Send(int msg, google::protobuf::Message& pks);

	static Handle<Value> SetSendFunction(const v8::Arguments& args);
private:
	static v8::Persistent<v8::Function> constructor;

	static v8::Local<v8::Object> sendFunc;

	static ServerLib serverLib;
};
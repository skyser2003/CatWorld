#pragma once

#include "ServerLibBroker.h"

using namespace v8;

class ServerModule : public node::ObjectWrap
{
public:
	static void Export(Handle<Object> exports);
private:
	static Handle<Value> New(const Arguments& args);
	static Handle<Value> Init(const Arguments& args);
	static Handle<Value> Parse(const v8::Arguments& args);
	static void Send(int msg, google::protobuf::Message& pks);

	static Handle<Value> SetSendFunction(const v8::Arguments& args);
	static Handle<Value> SetRootPath(const v8::Arguments& args);
private:
	static v8::Persistent<v8::Function> constructor;

	static v8::Persistent<v8::Function> sendFunc;
	static v8::Persistent<v8::Function> msgStructGetFunc;

	static ServerLibBroker broker;
};
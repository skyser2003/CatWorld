#pragma once

#include <node.h>
#include "ServerLib.h"

using namespace v8;

class ServerModule : public node::ObjectWrap
{
private:
	static void Export(Handle<Object> exports);
	static Handle<Value> New(const Arguments& args);
	static Handle<Value> Parse(const v8::Arguments& args);
private:
	static v8::Persistent<v8::Function> constructor;

	static ServerLib serverLib;
};
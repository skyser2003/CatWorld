#include <node.h>

#include "ServerModule.h"
using namespace v8;

Handle<Value> Method(const Arguments& args) {
	HandleScope scope;
	return scope.Close(String::New("world"));
}

void init(Handle<Object> exports) {
	ServerModule::Export(exports);
}

NODE_MODULE(Server, init)
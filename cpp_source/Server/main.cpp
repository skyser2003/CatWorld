#include <node.h>

#include "ServerModule.h"
using namespace v8;

void init(Handle<Object> exports) {
	ServerModule::Export(exports);
}

NODE_MODULE(gameServer, init)
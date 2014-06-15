#pragma once

#include <node.h>
#include "ServerLib.h"

class ServerModule : public node::ObjectWrap
{
private:
	static void Parse(const v8::Arguments& args)
	{
		serverLib.Parse();
	}

private:
	static ServerLib serverLib;
};
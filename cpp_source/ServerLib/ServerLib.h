#pragma once

#include <map>
#include <google/protobuf/message.h>

class ServerLib
{
public:
	void Init();
	void Parse(int msg, int length, void* buffer);
private:
	std::map<int, ::google::protobuf::Message*> messageList;
};
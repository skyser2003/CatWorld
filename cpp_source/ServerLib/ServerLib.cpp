#include "ServerLib.h"

#include <iostream>
using namespace std;

#include "Autogen/Message.pb.h"
#include "Autogen/Struct.pb.h"

void ServerLib::Init()
{
	messageList[Packet::LOGIN] = new LOGIN();
	auto login = new LOGIN();
}

void ServerLib::Parse(int msg, int length, void* buffer)
{
	auto it = messageList.find(msg);
	if (it != messageList.end())
	{
		auto* packet = it->second;
		packet->Clear();
		packet->ParseFromArray(buffer, length);

		LOGIN* login = static_cast<LOGIN*>(packet);
		printf("id : %s", login->id().c_str());
	}
}
#include "ServerLib.h"

#include <iostream>
using namespace std;

#include "Autogen/Struct.pb.h"

#define RegisterPacket(name)\
{\
	std::pair<int, packetHandler> pair; \
	pair.first = Packet::name; \
	pair.second = &ServerLib::RegisterHandler<name>;\
	handlerList.insert(pair); \
}

void ServerLib::Init()
{
	RegisterPacket(LOGIN);
	RegisterPacket(CHAT);
}

void ServerLib::Parse(int msg, int length, void* buffer)
{
		LOGIN* packet = new LOGIN();
		packet->Clear();
		packet->ParseFromArray(buffer, length);
		cout<<packet->GetTypeName();

		LOGIN* login = static_cast<LOGIN*>(packet);
		printf("id : %s", login->id().c_str());
}

template <class PKS>
void ServerLib::RegisterHandler(google::protobuf::Message& pks)
{
	OnPacket(static_cast<PKS&>(pks));
}
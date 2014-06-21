#include "ServerLib.h"

#include <iostream>
using namespace std;

#include "Autogen/Struct.pb.h"

#define RegisterPacket(name)\
{\
	std::pair<int, packetHandler> pair; \
	pair.first = Packet::name; \
	pair.second = &ServerLib::RegisterHandler<name>; \
	handlerList.insert(pair); \
	\
	std::pair<int, packetGenerator> pair2; \
	pair2.first = Packet::name; \
	pair2.second = &ServerLib::GenerateHandler<name>; \
	generatorList.insert(pair2); \
	\
	std::pair<string, int> pair3; \
	pair3.first = #name; \
	pair3.second = Packet::name;\
	msgList.insert(pair3); \
}

void ServerLib::Init()
{
	RegisterPacket(LOGIN);
	RegisterPacket(CHAT);
}

void ServerLib::Parse(int msg, int length, void* buffer)
{
	auto it = generatorList.find(msg);
	auto it2 = handlerList.find(msg);

	if (it == generatorList.end() || it2 == handlerList.end())
	{
		cout << "Error!  MSG '" << msg << "' doesn't exist" << endl;
		return;
	}

	auto msgStruct = (this->*it->second)();
	msgStruct->ParseFromArray(buffer, length);

	auto handlerFunc = it2->second;
	(this->*handlerFunc)(*msgStruct.get());
}

void ServerLib::Send(MSG& pks)
{
	sendFunction(msgList[pks.GetTypeName()], pks);
}

void ServerLib::SetSendFunction(std::function<void(int, MSG&)> sendFunction)
{
	this->sendFunction = sendFunction;
}

template <class PKS>
void ServerLib::RegisterHandler(google::protobuf::Message& pks)
{
	OnPacket(static_cast<PKS&>(pks));
}

template <class PKS>
ServerLib::UPtrMessage ServerLib::GenerateHandler()
{
	return unique_ptr<PKS>(new PKS());
}

void ServerLib::CallPacketHandler(int msg)
{

}
#include "stdafx.h"
#include "ServerLib.h"

#include <iostream>
using namespace std;

#include "Autogen/Struct.pb.h"
#include "Game.h"

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

ServerLib::ServerLib()
{
	game.reset(new Game());
}

ServerLib::~ServerLib()
{

}

void ServerLib::Init()
{
	RegisterPacket(LOGIN);
	RegisterPacket(CHAT);

	game->Init();
}

void ServerLib::Destroy()
{
	game->Destroy();
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

void ServerLib::Send(int msg, MSG& pks)
{
	sendFunction(msg, pks);
}

void ServerLib::SetSendFunction(std::function<void(int, MSG&)> sendFunction)
{
	this->sendFunction = sendFunction;
	game->SetSendFunction([this](int msg, MSG& pks)
	{
		Send(msg, pks);
	});
}

void ServerLib::SetRootPath(const std::string& rootPath)
{
	game->SetRootPath(rootPath);
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
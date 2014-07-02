#include "stdafx.h"
#include "ServerLib.h"

#include <iostream>
using namespace std;

#include "Autogen/Struct.pb.h"
#include "Client.h"
#include "ClientManager.h"
#include "DBManager.h"

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
}

ServerLib::~ServerLib()
{
}

void ServerLib::Init()
{
	RegisterPacket(LOGIN);
	RegisterPacket(CHAT);
	RegisterPacket(MOVE);
	RegisterPacket(STOP);

	// Logic
	cm.reset(new ClientManager());

	db.reset(new DBManager());
	db->Init(rootPath, "db.sqlite3");
}

void ServerLib::Destroy()
{
}

void ServerLib::Parse(const std::string& uid, int msg, int length, void* buffer)
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
	(this->*handlerFunc)(uid, *msgStruct.get());
}

void ServerLib::Send(int msg, MSG& pks)
{
	sendFunction(msg, pks);
}

void ServerLib::SetSendFunction(std::function<void(int, MSG&)> sendFunction)
{
	this->sendFunction = sendFunction;
}

void ServerLib::SetRootPath(const std::string& rootPath)
{
	this->rootPath = rootPath;
}

template <class PKS>
void ServerLib::OnPacket(const std::string& uid, PKS& pks)
{
	auto client = cm->Get(uid);
	if (client != nullptr)
	{
		client->OnPacket(pks);
	}
}

template <class PKS>
void ServerLib::RegisterHandler(const std::string& uid, google::protobuf::Message& pks)
{
	OnPacket(uid, static_cast<PKS&>(pks));
}

template <class PKS>
UPtrMessage ServerLib::GenerateHandler()
{
	return unique_ptr<PKS>(new PKS());
}

// OnPacket specialization

template <>
void ServerLib::OnPacket(const std::string& uid, LOGIN& pks)
{
	auto client = cm->CreateNewClient(uid);
	client->Init(this, pks.id(), pks.pw());

	LOGIN_RESULT outPKS;
	outPKS.set_result(1);
	Send(Packet::LOGIN_RESULT, outPKS);
}
#include "stdafx.h"
#include "ServerLib.h"

#include <iostream>
using namespace std;

#include "Autogen/Struct.pb.h"
#include "Client.h"
#include "ClientManager.h"
#include "DBManager.h"
#include "FieldMapManager.h"
#include "FieldMap.h"
#include "DataManager.h"

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

	// Data
	dm.reset(new DataManager());
	dm->LoadAllFiles(rootPath + "server_data/json", true);

	// Logic
	cm.reset(new ClientManager());

	db.reset(new DBManager());
	db->Init(rootPath, "db.sqlite3");

	fm.reset(new FieldMapManager());

	// TEMP - for test
	fm->Add(shared_ptr<FieldMap>(new FieldMap()));

	// Main loop
	mainLoop = std::thread([this]()
	{
		Update();
	});
	isRunning = true;
	mainLoop.detach();
}

void ServerLib::Destroy()
{
	isRunning = false;
	mainLoop.join();
}

void ServerLib::Update()
{
	std::chrono::milliseconds dur(1);
	auto past = std::chrono::system_clock::now();

	while (isRunning)
	{
		std::this_thread::sleep_for(dur);
		auto now = chrono::steady_clock::now();
		chrono::duration<__int64, std::milli> diff = chrono::duration_cast<chrono::milliseconds>(now - past);
		past = now;

		// Packet
		receiveLock.lock();
		auto tmpQueue = receiveQueue;
		while (receiveQueue.size()) receiveQueue.pop();
		receiveLock.unlock();

		while (tmpQueue.size())
		{
			auto save = tmpQueue.back();
			tmpQueue.pop();

			(this->*save.handler)(save.uid, *save.pks.get());
		}

		// Logic
		for (auto pair : *fm.get())
		{
			auto map = pair.second;
			map->Update(diff.count());
		}
	}
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

	MsgSaver saver = { uid, (this->*it->second)(), it2->second };
	saver.pks->ParseFromArray(buffer, length);

	receiveLock.lock();
	receiveQueue.push(saver);
	receiveLock.unlock();
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
SPtrMessage ServerLib::GenerateHandler()
{
	return shared_ptr<PKS>(new PKS());
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

	// TEMP - for test
	auto map = fm->Get(0);
	auto pc = map->CreateObject();
	client->SetPC(pc);
}
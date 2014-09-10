#pragma once

#include "IServerLib.h"

class ClientManager;
class DBManager;
class FieldMapManager;
class DataManager;

class ServerLib final : public IServerLib
{
public:
	typedef void (ServerLib::*packetHandler)(const std::string&, ProtobufMSG&);
	typedef SPtrMessage(ServerLib::*packetGenerator)();
private:
	struct MsgSaver
	{
		std::string uid;
		SPtrMessage pks;
		packetHandler handler;
	};
public:
	ServerLib();
	~ServerLib();

	void Init();
	void Destroy();
	void Update();

	void Parse(const std::string& uid, int msg, int length, void* buffer);
	void Send(int msg, ProtobufMSG& pks);

	void SetSendFunction(std::function<void(int, ProtobufMSG&)> sendFunction);
	void SetRootPath(const std::string& rootPath);
private:
	template <class PKS>
	void OnPacket(const std::string& uid, PKS& pks);

	template <class PKS>
	void RegisterHandler(const std::string& uid, ProtobufMSG& pks);
	template <class PKS>
	SPtrMessage GenerateHandler();

	// Setting
	std::string rootPath;
	std::thread mainLoop;
	bool isRunning;

	// Packet
	std::mutex receiveLock, sendLock;
	std::queue<MsgSaver> receiveQueue, sendQueue;
	std::function<void(int, ProtobufMSG&)> sendFunction;

	std::unordered_map<int, packetHandler> handlerList;
	std::unordered_map<int, packetGenerator> generatorList;

	std::unordered_map<std::string, int> msgList;

	// Logic
	std::unique_ptr<ClientManager> cm;
	std::unique_ptr<DBManager> db;
	std::unique_ptr<FieldMapManager> fm;
	std::unique_ptr<DataManager> dm;
};
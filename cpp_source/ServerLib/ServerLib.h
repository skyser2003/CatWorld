#pragma once

class Game;
class ClientManager;
class DBManager;

class ServerLib
{
public:
	ServerLib();
	~ServerLib();

	typedef google::protobuf::Message MSG;
	typedef std::unique_ptr<MSG> UPtrMessage;

	typedef void (ServerLib::*packetHandler)(const std::string&, MSG&);
	typedef UPtrMessage (ServerLib::*packetGenerator)();
public:
	void Init();
	void Destroy();

	void Parse(const std::string& uid, int msg, int length, void* buffer);
	void Send(int msg, MSG& pks);

	void SetSendFunction(std::function<void(int, MSG&)> sendFunction);
	void SetRootPath(const std::string& rootPath);
private:
	template <class PKS>
	void OnPacket(const std::string& uid, PKS& pks);

	template <class PKS>
	void RegisterHandler(const std::string& uid, MSG& pks);
	template <class PKS>
	UPtrMessage GenerateHandler();

	// Setting
	std::string rootPath;

	// Packet
	std::function<void(int, MSG&)> sendFunction;

	std::unordered_map<int, packetHandler> handlerList;
	std::unordered_map<int, packetGenerator> generatorList;

	std::unordered_map<std::string, int> msgList;

	// Logic
	std::unique_ptr<ClientManager> cm;
	std::unique_ptr<DBManager> db;
};
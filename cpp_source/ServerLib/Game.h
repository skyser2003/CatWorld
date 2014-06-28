#pragma once

class Client;
class ClientManager;
class DBManager;

class Game
{
public:
	typedef google::protobuf::Message MSG;
public:
	Game();
	~Game();

	void Init();
	void Destroy();

	void SetRootPath(const std::string& rootPath);
	void SetSendFunction(std::function<void(MSG&)> sendFunc);

	void Send(MSG& pks);
	template <class PKS>
	void OnPacket(PKS& pks);
private:
	std::function<void(MSG&)> sendFunc;

	std::unique_ptr<ClientManager> cm;
	std::unique_ptr<DBManager> db;

	std::string rootPath;
};
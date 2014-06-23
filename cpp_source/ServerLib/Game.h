#pragma once

class Client;
class ClientManager;
class DBManager;

class Game
{
public:
	Game();
	~Game();

	void Init();
	void Destroy();

	template <class PKS>
	void OnPacket(PKS& pks);
private:
	std::unique_ptr<ClientManager> cm;
	std::unique_ptr<DBManager> db;
};
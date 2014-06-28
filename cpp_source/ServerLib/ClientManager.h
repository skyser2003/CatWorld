#pragma once

class Client;

class ClientManager
{
public:
	typedef std::shared_ptr<Client> SPtrClient;
public:
	ClientManager();
	~ClientManager();

	SPtrClient CreateNewClient();
private:
	std::unordered_map<int, SPtrClient> clientList;
};
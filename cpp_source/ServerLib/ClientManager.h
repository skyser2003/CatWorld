#pragma once

class Client;

class ClientManager
{
public:
	typedef std::shared_ptr<Client> SPtrClient;
public:
	ClientManager();
	~ClientManager();

	SPtrClient CreateNewClient(const std::string& uid);
	SPtrClient Get(const std::string& uid);
private:
	std::unordered_map<std::string, SPtrClient> clientList;
};
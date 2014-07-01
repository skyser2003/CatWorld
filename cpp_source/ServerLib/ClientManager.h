#pragma once

class ClientManager
{
public:
	ClientManager();
	~ClientManager();

	SPtrClient CreateNewClient(const std::string& uid);
	SPtrClient Get(const std::string& uid);
private:
	std::unordered_map<std::string, SPtrClient> clientList;
};
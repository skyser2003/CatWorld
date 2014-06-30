#include "stdafx.h"
#include "ClientManager.h"

#include "Client.h"

ClientManager::ClientManager()
{

}
ClientManager::~ClientManager()
{

}

ClientManager::SPtrClient ClientManager::CreateNewClient(const std::string& uid)
{
	SPtrClient client;
	client.reset(new Client());
	clientList.emplace(uid, client);

	return client;
}
ClientManager::SPtrClient ClientManager::Get(const std::string& uid)
{
	auto it = clientList.find(uid);
	if (it == clientList.end())
	{
		return nullptr;
	}
	else
	{
		return it->second;
	}
}
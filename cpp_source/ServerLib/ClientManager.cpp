#include "stdafx.h"
#include "ClientManager.h"

#include "Client.h"

ClientManager::ClientManager()
{

}
ClientManager::~ClientManager()
{

}

SPtrClient ClientManager::CreateNewClient(const std::string& uid)
{
	SPtrClient client;
	client.reset(new Client());
	clientList.emplace(uid, client);

	return client;
}

SPtrClient ClientManager::Get(const std::string& uid)
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

ClientManager::iterator ClientManager::begin()
{
	return clientList.begin();
}

ClientManager::iterator ClientManager::end()
{
	return clientList.end();
}

ClientManager::const_iterator ClientManager::begin() const
{
	return clientList.begin();
}

ClientManager::const_iterator ClientManager::end() const
{
	return clientList.end();
}
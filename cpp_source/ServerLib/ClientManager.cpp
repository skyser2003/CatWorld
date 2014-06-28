#include "stdafx.h"
#include "ClientManager.h"

#include "Client.h"

ClientManager::ClientManager()
{

}
ClientManager::~ClientManager()
{

}

ClientManager::SPtrClient ClientManager::CreateNewClient()
{
	SPtrClient client;
	client.reset(new Client());

	return client;
}
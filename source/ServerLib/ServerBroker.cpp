#include "stdafx.h"
#include "ServerBroker.h"

#include "ServerLib.h"

void ServerBroker::Init()
{
	serverLib.reset(new ServerLib());
}

void ServerBroker::Destroy()
{
	serverLib.reset();
}

void ServerBroker::Parse(const std::string& uid, int msg, int length, void* buffer)
{
	serverLib->Parse(uid, msg, length, buffer);
}

void ServerBroker::SetSendFunction(std::function<void(int, google::protobuf::Message&)> sendFunction)
{
	serverLib->SetSendFunction(sendFunction);
}

void ServerBroker::SetRootPath(const std::string& rootPath)
{
	serverLib->SetRootPath(rootPath);
}
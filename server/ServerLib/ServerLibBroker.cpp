#include "stdafx.h"
#include "ServerLibBroker.h"

#include "ServerLib.h"

ServerLibBroker::ServerLibBroker()
{
	serverLib.reset(new ServerLib());
}
ServerLibBroker::~ServerLibBroker()
{

}

void ServerLibBroker::Init()
{
	serverLib->Init();
}

void ServerLibBroker::Destroy()
{
	serverLib->Destroy();
}

void ServerLibBroker::Parse(const std::string& uid, int msg, int length, void* buffer)
{
	serverLib->Parse(uid, msg, length, buffer);
}

void ServerLibBroker::SetSendFunction(std::function<void(int, google::protobuf::Message&)> sendFunction)
{
	serverLib->SetSendFunction(sendFunction);
}

void ServerLibBroker::SetRootPath(const std::string& rootPath)
{
	serverLib->SetRootPath(rootPath);
}
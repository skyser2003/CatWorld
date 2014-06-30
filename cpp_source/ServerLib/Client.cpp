#include "stdafx.h"
#include "Client.h"

#include "ServerLib.h"
#include "FieldObject.h"

Client::Client()
{
}
Client::~Client()
{

}

void Client::Init(ServerLib* server, std::string id, std::string pw)
{
	this->server = server;
	this->id = id;
	this->pw = pw;

	pc.reset(new FieldObject());
}

void Client::Send(int msg, google::protobuf::Message& pks)
{
	server->Send(msg, pks);
}
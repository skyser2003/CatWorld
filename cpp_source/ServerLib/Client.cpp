#include "stdafx.h"
#include "Client.h"

Client::Client()
{

}
Client::~Client()
{

}

void Client::Init(std::string id, std::string pw)
{
	this->id = id;
	this->pw = pw;
}
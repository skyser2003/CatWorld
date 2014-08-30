#include "stdafx.h"
#include "Client.h"

#include "ServerLib.h"
#include "FieldObject.h"

#include "Autogen/Struct.pb.h"

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

	positionCooltime = 0;
}

void Client::Send(int msg, google::protobuf::Message& pks)
{
	server->Send(msg, pks);
}

void Client::SendMapEnterPacket()
{
	MAP_ENTER outPKS;
	outPKS.set_speed(pc->speed);
	Send(Packet::MAP_ENTER, outPKS);
}

void Client::Update(int dt)
{
	positionCooltime -= dt;

	if (positionCooltime <= 0)
	{
		positionCooltime += PositionPacketCooltime;

		POSITION outPKS;
		outPKS.set_x(pc->pos.x);
		outPKS.set_y(pc->pos.y);
		outPKS.set_z(pc->pos.z);

		Send(Packet::POSITION, outPKS);
	}
}
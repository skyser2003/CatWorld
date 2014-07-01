#include "stdafx.h"
#include "Client.h"

#include "Autogen/Struct.pb.h"
#include "FieldObject.h"

template <>
void Client::OnPacket(CHAT& pks)
{

}

template <>
void Client::OnPacket(MOVE& pks)
{
	pc->velocity.x = pks.x();
	pc->velocity.y = pks.y();
	pc->velocity.z = pks.z();

	pc->ChangeFSM(FieldObjectFSM::MOVE);
}

template <>
void Client::OnPacket(STOP& stop)
{
	pc->ChangeFSM(FieldObjectFSM::IDLE);
	
	POSITION outPKS;
	outPKS.set_x(pc->pos.x);
	outPKS.set_y(pc->pos.y);
	outPKS.set_z(pc->pos.z);

	Send(Packet::POSITION, outPKS);
}
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
	if (pc->GetFSMState() != FieldObjectFSM::MOVE)
	{
		pc->ChangeFSM(FieldObjectFSM::MOVE);
	}

	pc->velocity.x += pks.x();
	pc->velocity.y += pks.y();
	pc->velocity.z += pks.z();
}

template <>
void Client::OnPacket(STOP& stop)
{
	pc->velocity.x = 0;
	pc->velocity.y = 0;
	pc->velocity.z = 0;

	pc->ChangeFSM(FieldObjectFSM::IDLE);
	
	POSITION outPKS;
	outPKS.set_x(pc->pos.x);
	outPKS.set_y(pc->pos.y);
	outPKS.set_z(pc->pos.z);

	Send(Packet::POSITION, outPKS);
}
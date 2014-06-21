#include "ServerLib.h"

#include "Autogen/Struct.pb.h"

#include <iostream>

template <>
void ServerLib::OnPacket(LOGIN& pks)
{
	std::cout << pks.id() << std::endl;

	LOGIN login;
	login.set_id("skyserskyser");
	login.set_pw(55);

	Send(login);
}

template <>
void ServerLib::OnPacket(CHAT& pks)
{

}
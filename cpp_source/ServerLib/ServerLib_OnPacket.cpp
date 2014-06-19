#include "ServerLib.h"

#include "Autogen/Struct.pb.h"

#include <iostream>

template <>
void ServerLib::OnPacket(LOGIN& pks)
{
	std::cout << pks.id() << std::endl;
}

template <>
void ServerLib::OnPacket(CHAT& pks)
{

}
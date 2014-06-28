#include "stdafx.h"
#include "Game.h"

#include "Autogen/Struct.pb.h"
#include "ClientManager.h"
#include "Client.h"

void Game::Send(MSG& pks)
{
	sendFunc(pks);
}

template <>
void Game::OnPacket(LOGIN& pks)
{
	auto client = cm->CreateNewClient();
	client->Init(pks.id(), pks.pw());
}

template <>
void Game::OnPacket(CHAT& pks)
{

}
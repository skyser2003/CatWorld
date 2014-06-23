#include "stdafx.h"
#include "Game.h"

#include "ClientManager.h"
#include "DBManager.h"

Game::Game()
{

}

Game::~Game()
{

}

void Game::Init()
{
	cm.reset(new ClientManager());

	db.reset(new DBManager());
	db->Init("some_default_filename.sqlite3");
}
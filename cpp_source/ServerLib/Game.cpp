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
	db->Init(rootPath, "db.sqlite3");
}

void Game::Destroy()
{
}

void Game::SetRootPath(const std::string& rootPath)
{
	this->rootPath = rootPath;
}

void Game::SetSendFunction(std::function<void(int, MSG&)> sendFunc)
{
	this->sendFunc = sendFunc;
}
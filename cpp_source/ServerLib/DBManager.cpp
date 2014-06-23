#include "stdafx.h"
#include "DBManager.h"

void DBManager::Init(const std::string& filename)
{
	handle = sqlite3_open(filename.c_str(), &sqlite);
}

void DBManager::Destroy()
{
	sqlite3_close(sqlite);
}
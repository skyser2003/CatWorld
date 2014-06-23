#include "stdafx.h"
#include "DBManager.h"

void DBManager::Init(const std::string& filename)
{
	std::tr2::sys::path path = filename;
	bool createNewFile = std::tr2::sys::exists(path) == false;
	handle = sqlite3_open(filename.c_str(), &sqlite);

	char* errmsg = nullptr;
	if (createNewFile == true)
	{
		// Initialize schema
		sqlite3_exec(sqlite, "CREATE DATABASE test", nullptr, nullptr, &errmsg);
	}

	if (errmsg != nullptr)
	{
		printf("%s", errmsg);
	}
}

void DBManager::Destroy()
{
	sqlite3_close(sqlite);
}
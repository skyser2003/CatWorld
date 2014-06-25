#include "stdafx.h"
#include "DBManager.h"

void DBManager::Init(const std::string& rootPath, const std::string& filename)
{
	std::string fullPath = rootPath + filename;
	std::tr2::sys::path path = fullPath;
	bool createNewFile = std::tr2::sys::exists(path) == false;
	handle = sqlite3_open(fullPath.c_str(), &sqlite);

	char* errmsg = nullptr;
	if (createNewFile == true)
	{
		// Initialize schema
		std::ifstream scheme;
		std::string schemeQuery, temp;

		scheme.open(rootPath + "server_data/db_scheme.txt");
		while (scheme)
		{
			temp.clear();
			std::getline(scheme, temp);
			schemeQuery += '\n';
			schemeQuery += temp;
		}

		sqlite3_exec(sqlite, schemeQuery.c_str(), nullptr, nullptr, &errmsg);

		scheme.close();
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
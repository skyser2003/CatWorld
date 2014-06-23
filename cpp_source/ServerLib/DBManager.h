#pragma once

struct sqlite3;

class DBManager
{
public:
	void Init(const std::string& filename);
	void Destroy();
private:
	int handle;
	sqlite3* sqlite;
};
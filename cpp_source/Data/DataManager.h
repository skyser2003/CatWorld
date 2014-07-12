#pragma once

#include <string>

class DataManager
{
public:
	DataManager();
	~DataManager();

	bool LoadFile(const std::string& filename);
	bool LoadAllFiles(const std::string& path, bool isRecursive);
private:
	void AddClass(const SPtrClass& cls);
	std::unordered_map<int, SPtrClass> classList;
};
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
	void AddClass(const SPtrList& list, const SPtrClass& cls);
	void AddDataList(const SPtrList& cls);

	std::unordered_map<std::string, SPtrList> datalistList;
};
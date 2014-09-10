#pragma once

#ifdef DATAMANAGER_EXPORT
#define DATAMANAGER_API __declspec(dllexport)
#else
#define DATAMANAGER_API __declspec(dllimport)
#endif

class DataManager
{
public:
	DATAMANAGER_API DataManager();
	DATAMANAGER_API ~DataManager();

	DATAMANAGER_API bool LoadFile(const std::string& filename);
	DATAMANAGER_API bool LoadAllFiles(const std::string& path, bool isRecursive);
private:
	void AddClass(const SPtrList& list, const SPtrClass& cls);
	void AddDataList(const SPtrList& cls);

	std::unordered_map<std::string, SPtrList> datalistList;
};
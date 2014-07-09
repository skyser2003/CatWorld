#include "DataManager.h"

#include <fstream>
#include <filesystem>
using namespace std;
using namespace std::tr2;

#include "json/json.h"

DataManager::DataManager()
{

}
DataManager::~DataManager()
{

}

bool DataManager::LoadFile(const std::string& filename)
{
	ifstream input;
	string content;

	input.open(filename);

	if (input.is_open())
	{
		string temp;

		while (input)
		{
			temp.clear();
			getline(input, temp);
			content += '\n';
			content += temp;
		}
	}
	
	input.close();

	if (content.length() == 0)
	{
		return false;
	}

	Json::Reader reader;
	Json::Value root;
	bool success = reader.parse(content, root);

	return success;
}

bool DataManager::LoadAllFiles(const std::string& path, bool isRecursive)
{
	sys::path searchPath = path;

	for (sys::recursive_directory_iterator it(searchPath),
		end;
		it != end;
		++it)
	{
		auto filePath = it->path();
		if (sys::is_directory(filePath))
		{
			continue;
		}

		string filename = filePath.string();
		
		bool success = LoadFile(filename);
		if (success == false)
		{
			return false;
		}
	}

	return true;
}
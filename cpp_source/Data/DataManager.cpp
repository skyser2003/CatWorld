#include "stdafx.h"
#include "DataManager.h"

using namespace std;
using namespace std::tr2;


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

	if (success)
	{
		auto header = root["header"];
		auto data = root["data"];

		string dataSpaceName = header["name"].asString();

		for (auto it = data.begin(); it != data.end(); ++it)
		{
			auto arr = *it;
			for (auto it2 = arr.begin(); it2 != arr.end(); ++it2)
			{
				string key = it2.key().asString();
				auto val = *it2;

				switch (val.type())
				{
				case Json::ValueType::booleanValue:
				{
				}
					break;
				case Json::ValueType::intValue:
				{

				}
					break;
				case Json::ValueType::stringValue:
				{

				}
					break;
				case Json::ValueType::realValue:
				{

				}
					break;
				}
			}
		}
	}

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
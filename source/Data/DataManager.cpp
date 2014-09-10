#include "stdafx.h"
#include "DataManager.h"

using namespace std;
using namespace std::tr2;

#include "DataClass.h"
#include "DataList.h"
#include "DataProperty.h"

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

		string listName = header["name"].asString();
		SPtrList list(new DataList);
		list->SetName(listName);
		AddDataList(list);

		for (auto it = data.begin(); it != data.end(); ++it)
		{
			auto properties = *it;

			if (properties["id"].empty() == true)
			{
				// Error!  ID should exist;
				continue;
			}

			SPtrClass cls(new DataClass);
			
			for (auto it2 = properties.begin(); it2 != properties.end(); ++it2)
			{
				string key = it2.key().asString();
				auto val = *it2;

				SPtrProp prop(new DataProperty);
				prop->SetKey(key);

				switch (val.type())
				{
				case Json::ValueType::booleanValue:
				{
					prop->SetValue<BOOL>(val.asBool());
				}
					break;
				case Json::ValueType::intValue:
				{
					prop->SetValue<INT>(val.asInt());
				}
					break;
				case Json::ValueType::stringValue:
				{
					prop->SetValue<STRING>(val.asString().c_str());
				}
					break;
				case Json::ValueType::realValue:
				{
					prop->SetValue<FLOAT>(val.asFloat());
				}
					break;
				}

				cls->AddProperty(key, prop);
			}

			auto idProp = cls->GetProperty("id");
			auto nameProp = cls->GetProperty("name");
			
			cls->SetID(idProp->Get<INT>());

			// Name is optional
			if (nameProp != nullptr)
			{
				cls->SetName(nameProp->Get<STRING>());
			}

			AddClass(list, cls);
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

void DataManager::AddClass(const SPtrList& list, const SPtrClass& cls)
{
	list->AddClass(cls);
}

void DataManager::AddDataList(const SPtrList& list)
{
	if (datalistList.find(list->Name()) == datalistList.end())
	{
		datalistList.emplace(list->Name(), list);
	}
	else
	{
		// Error!
	}
}
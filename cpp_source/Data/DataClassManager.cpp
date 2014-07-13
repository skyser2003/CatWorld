#include "stdafx.h"
#include "DataClassManager.h"

#include "DataClass.h"
#include "DataProperty.h"

void DataClassManager::AddClass(const SPtrClass& cls)
{
	int id = cls->GetProperty("id")->Get<INT>();
	const char* name = cls->GetProperty("name")->Get<STRING>();

	if (classIDList.find(id) != classIDList.end()
		&& classNameList.find(name) != classNameList.end())
	{
		classIDList.emplace(id, cls);

		if (name != nullptr)
		{
			classNameList.emplace(name, cls);
		}
	}
}

SPtrClass DataClassManager::Get(int id) const
{
	auto it = classIDList.find(id);

	if (it == classIDList.end())
	{
		return nullptr;
	}
	else
	{
		return it->second;
	}
}

SPtrClass DataClassManager::Get(const std::string& name) const
{
	auto it = classNameList.find(name);

	if (it == classNameList.end())
	{
		return nullptr;
	}
	else
	{
		return it->second;
	}
}
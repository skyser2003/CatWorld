#include "stdafx.h"
#include "DataList.h"

#include "DataClass.h"
#include "DataProperty.h"

void DataList::AddClass(const SPtrClass& cls)
{
	int id = cls->GetProperty("id")->Get<INT>();
	auto name = cls->GetProperty("name");

	if (classIDList.find(id) != classIDList.end())
	{
		classIDList.emplace(id, cls);

		if(name != nullptr && classNameList.find(name->Get<STRING>()) != classNameList.end())
		{
			classNameList.emplace(name->Get<STRING>(), cls);
		}
	}
}

SPtrClass DataList::Get(int id) const
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

SPtrClass DataList::Get(const std::string& name) const
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
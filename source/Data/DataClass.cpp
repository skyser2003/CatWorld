#include "stdafx.h"
#include "DataClass.h"

#include "DataProperty.h"

void DataClass::AddProperty(const std::string& key, const SPtrProp& prop)
{
	if (propList.find(key) == propList.end())
	{
		propList.emplace(key, prop);
	}
	else
	{
		// Error!
	}
}

SPtrProp DataClass::GetProperty(const std::string& key) const
{
	auto it = propList.find(key);

	if (it == propList.end())
	{
		return SPtrProp();
	}
	else
	{
		return it->second;
	}
}

SPtrProp DataClass::GetProperty(const std::string&& key) const
{
	auto it = propList.find(key);

	if (it == propList.end())
	{
		return SPtrProp();
	}
	else
	{
		return it->second;
	}
}
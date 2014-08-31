#include "stdafx.h"
#include "FieldMapManager.h"

FieldMapManager::FieldMapManager()
{
	uid = 0;
}

void FieldMapManager::Add(SPtrMap map)
{
	mapList.emplace(GetNextUid(), map);
}
SPtrMap FieldMapManager::Get(int uid) const
{
	auto it = mapList.find(uid);
	if (it == mapList.end())
	{
		return nullptr;
	}
	else
	{
		return it->second;
	}
}

FieldMapManager::iterator FieldMapManager::begin()
{
	return mapList.begin();
}

FieldMapManager::iterator FieldMapManager::end()
{
	return mapList.end();
}

FieldMapManager::const_iterator FieldMapManager::begin() const
{
	return mapList.begin();
}

FieldMapManager::const_iterator FieldMapManager::end() const
{
	return mapList.end();
}
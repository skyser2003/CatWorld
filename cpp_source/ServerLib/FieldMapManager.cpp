#include "stdafx.h"
#include "FieldMapManager.h"

FieldMapManager::FieldMapManager()
{
	token = 0;
}

void FieldMapManager::Add(SPtrMap map)
{
	mapList.emplace(GetNextToken(), map);
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
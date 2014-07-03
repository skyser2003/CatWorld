#include "stdafx.h"
#include "FieldMapManager.h"

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
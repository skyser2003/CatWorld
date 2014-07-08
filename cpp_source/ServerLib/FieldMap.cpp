#include "stdafx.h"
#include "FieldMap.h"

#include "FieldObject.h"

void FieldMap::Init()
{
	token = 0;
}

void FieldMap::Update(int dt)
{
	for (auto pair : objectList)
	{
		pair.second->Update(dt);
	}
}

SPtrObj FieldMap::CreateObject()
{
	auto object = SPtrObj(new FieldObject());
	object->SetUid(GetNextToken());
	objectList.emplace(object->GetUid(), object);

	return object;
}
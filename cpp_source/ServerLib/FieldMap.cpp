#include "stdafx.h"
#include "FieldMap.h"

#include "FieldObject.h"

void FieldMap::Init()
{
	token = 0;
}

void FieldMap::AddNewObject(SPtrObj& object)
{
	object->SetUid(GetNextToken());
	objectList.emplace(object->GetUid(), object);
}
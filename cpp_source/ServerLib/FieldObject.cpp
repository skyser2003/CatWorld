#include "stdafx.h"
#include "FieldObject.h"

#include "FieldObjectComponent.h"

FieldObject::FieldObject()
{

}
FieldObject::~FieldObject()
{

}

void FieldObject::AddComponent(UPtrComp& component)
{
	componentList.push_back(UPtrComp(component.release()));
}
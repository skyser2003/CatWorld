#include "stdafx.h"
#include "FieldObject.h"

#include "FieldObjectComponent.h"

void FieldObject::AddComponent(UPtrComp& component)
{
	componentList.push_back(UPtrComp(component.release()));
}
#include "stdafx.h"
#include "FieldObjectFSM.h"

#include "FieldObject.h"

void FieldObjectFSM::SetFieldObject(FieldObject* owner)
{
	this->owner = owner;
}
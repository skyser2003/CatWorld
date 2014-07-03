#include "stdafx.h"
#include "FieldObjectFSM.h"

#include "FieldObject.h"

void FieldObjectFSM::SetOwner(FieldObject* owner)
{
	this->owner = owner;
}
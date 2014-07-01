#include "stdafx.h"
#include "FieldObject.h"

#include "FieldObjectComponent.h"

#include "FSM_IDLE.h"
#include "FSM_MOVE.h"

FieldObject::FieldObject()
{
	ChangeFSM(FieldObjectFSM::IDLE);
}
FieldObject::~FieldObject()
{

}

void FieldObject::AddComponent(UPtrComp& component)
{
	componentList.push_back(UPtrComp(component.release()));
}

void FieldObject::ChangeFSM(FieldObjectFSM::STATE state)
{
	if (fsm != nullptr)
	{
		fsm->onEnd();
	}

	this->state = state;

	switch (state)
	{
	case FieldObjectFSM::IDLE:
	{
		fsm.reset(new FSM_IDLE());
	}
		break;
	case FieldObjectFSM::MOVE:
	{
		fsm.reset(new FSM_MOVE());
	}
		break;
	case FieldObjectFSM::CHASE:
	{
	}
		break;
	}
}
#include "stdafx.h"
#include "FieldObject.h"

#include "FieldObjectComponent.h"

#include "FSM_IDLE.h"
#include "FSM_MOVE.h"

FieldObject::FieldObject()
{
	uid = -1;
	ChangeFSM(FieldObjectFSM::IDLE);
}
FieldObject::~FieldObject()
{

}

void FieldObject::Update(int dt)
{
	fsm->onUpdate(dt);
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
		fsm.reset(new FSM_IDLE(this));
	}
		break;
	case FieldObjectFSM::MOVE:
	{
		fsm.reset(new FSM_MOVE(this));
	}
		break;
	case FieldObjectFSM::CHASE:
	{
	}
		break;
	}
}
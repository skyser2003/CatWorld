#include "stdafx.h"
#include "FSM_MOVE.h"

#include "FieldObject.h"

FSM_MOVE::FSM_MOVE(FieldObject* owner)
{
	SetOwner(owner);
}

void FSM_MOVE::onUpdate(int dt)
{
	glm::vec3 dist;
	dist.x = owner->velocity.x * dt / 1000.0f;
	dist.y = owner->velocity.y * dt / 1000.0f;
	dist.z = owner->velocity.z * dt / 1000.0f;

	owner->pos += dist;
}
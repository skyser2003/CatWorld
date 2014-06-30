#include "stdafx.h"
#include "FSM_MOVE.h"

#include "FieldObject.h"

void FSM_MOVE::onUpdate(float dt)
{
	auto leftDistance = owner->dest - owner->pos;

	auto dd = glm::vec3(owner->velocity);
	dd.x *= 1000 / dt;
	dd.y *= 1000 / dt;
	dd.z *= 1000 / dt;

	if (leftDistance.x <= dd.x
		&& leftDistance.y <= dd.y
		&& leftDistance.z <= dd.z)
	{
		// TODO - change FSM to IDLE
	}
	else
	{
		owner->pos += dd;
	}
}
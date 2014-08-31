#pragma once

#include "FieldObjectFSM.h"

class FSM_IDLE final : public FieldObjectFSM
{
public:
	FSM_IDLE(FieldObject* owner);
};
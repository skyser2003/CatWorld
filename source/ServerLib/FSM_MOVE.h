#pragma once

#include "FieldObjectFSM.h"

class FSM_MOVE final : public FieldObjectFSM
{
public:
	FSM_MOVE(FieldObject* owner);
	void onUpdate(int dt) override;
};
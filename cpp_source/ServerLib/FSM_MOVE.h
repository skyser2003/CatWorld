#pragma once

#include "FieldObjectFSM.h"

class FSM_MOVE final : public FieldObjectFSM
{
public:
	void onUpdate(float dt) override;
};
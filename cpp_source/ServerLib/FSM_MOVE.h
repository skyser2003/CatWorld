#pragma once

#include "FieldObjectFSM.h"

class FSM_MOVE final : public FieldObjectFSM
{
public:
	void onUpdate(int dt) override;
};
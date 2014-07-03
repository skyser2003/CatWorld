#pragma once

class FieldObject;

class FieldObjectFSM
{
public:
	enum STATE
	{
		IDLE,
		MOVE,
		CHASE
	};
public:
	void SetOwner(FieldObject* owner);
	virtual void onBegin() {};
	virtual void onUpdate(int dt) {};
	virtual void onEnd() {};
protected:
	FieldObject* owner;
};
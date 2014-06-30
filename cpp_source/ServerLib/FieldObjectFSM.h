#pragma once

class FieldObject;

class FieldObjectFSM
{
public:
	enum
	{
		IDLE,
		MOVE,
		CHASE
	};
public:
	void SetFieldObject(FieldObject* owner);
	virtual void onBegin() {};
	virtual void onUpdate(float dt) {};
	virtual void onEnd() {};
protected:
	FieldObject* owner;
};
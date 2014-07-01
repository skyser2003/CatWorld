#pragma once

#include "FieldObjectFSM.h"

class FieldObject
{
public:
	glm::vec3 pos;
	glm::vec3 velocity;
public:
	FieldObject();
	~FieldObject();

	void Update(int dt);

	void SetUid(int uid) { this->uid = uid; }
	int GetUid() const{ return uid; }

	void AddComponent(UPtrComp& component);

	void ChangeFSM(FieldObjectFSM::STATE state);
private:
	int uid;
	std::list<UPtrComp> componentList;

	FieldObjectFSM::STATE state;
	UPtrFSM fsm;
};
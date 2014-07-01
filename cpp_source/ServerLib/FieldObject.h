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

	void AddComponent(UPtrComp& component);

	void ChangeFSM(FieldObjectFSM::STATE state);
private:
	std::list<UPtrComp> componentList;

	FieldObjectFSM::STATE state;
	UPtrFSM fsm;
};
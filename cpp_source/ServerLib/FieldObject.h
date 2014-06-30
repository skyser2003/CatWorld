#pragma once

class FieldObjectComponent;

class FieldObject
{
public:
	typedef std::unique_ptr<FieldObjectComponent> UPtrComp;
public:
	glm::vec3 pos;
	glm::vec3 dest;
	glm::vec3 velocity;
public:
	FieldObject();
	~FieldObject();

	void AddComponent(UPtrComp& component);
private:
	std::list<UPtrComp> componentList;
};
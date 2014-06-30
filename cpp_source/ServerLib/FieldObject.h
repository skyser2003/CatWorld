#pragma once

class FieldObjectComponent;

class FieldObject
{
public:
	typedef std::unique_ptr<FieldObjectComponent> UPtrComp;
public:
	FieldObject();
	~FieldObject();

	void AddComponent(UPtrComp& component);
private:
	glm::vec3 pos;

	std::list<UPtrComp> componentList;
};
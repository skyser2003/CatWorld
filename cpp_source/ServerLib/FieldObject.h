#pragma once

class FieldObjectComponent;

class FieldObject
{
public:
	typedef std::unique_ptr<FieldObjectComponent> UPtrComp;
public:
	void AddComponent(UPtrComp& component);
private:
	std::list<UPtrComp> componentList;
};
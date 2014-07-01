#pragma once

class FieldMap
{
public:
	void Init();

	void AddNewObject(SPtrObj& object);

	int GetNextToken() { return token++; }
private:
	int token;

	std::unordered_map<int, SPtrObj> objectList;
};
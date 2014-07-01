#pragma once

class FieldMap
{
public:
	void Init();

	void AddNewObject(SPtrObj& object);

	void Update(int dt);

	int GetNextToken() { return token++; }
private:
	int token;

	std::unordered_map<int, SPtrObj> objectList;
};
#pragma once

class FieldMap
{
public:
	void Init();
	void Update(int dt);

	SPtrObj CreateObject();
private:
	int GetNextToken() { return token++; }

	int token;

	std::unordered_map<int, SPtrObj> objectList;
};
#pragma once

class FieldMapManager
{
public:
	typedef std::unordered_map<int, SPtrMap>::iterator iterator;
	typedef std::unordered_map<int, SPtrMap>::const_iterator const_iterator;
public:
	FieldMapManager();

	void Add(SPtrMap map);

	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
private:
	int GetNextToken() { return token++; }

	int token;
	std::unordered_map<int, SPtrMap> mapList;
};
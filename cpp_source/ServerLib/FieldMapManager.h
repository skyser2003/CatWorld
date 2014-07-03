#pragma once

class FieldMapManager
{
public:
	typedef std::unordered_map<int, SPtrMap>::iterator iterator;
	typedef std::unordered_map<int, SPtrMap>::const_iterator const_iterator;
public:
	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
private:
	std::unordered_map<int, SPtrMap> mapList;
};
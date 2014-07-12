#pragma once

#include "DataType.h"

class DataProperty;

class DataClass
{
public:
	void SetID(int id) { this->id = id; }
	void SetName(const std::string& name) { this->name = name; }

	int ID() const { return id; }
	const std::string& Name() const { return name; }

	void AddProperty(const std::string& key, const SPtrProp& prop);
	SPtrProp GetProperty(const std::string& key) const;
	SPtrProp GetProperty(const std::string&& key) const;
private:
	int id;
	std::string name;
	std::unordered_map<std::string, SPtrProp> propList;
};
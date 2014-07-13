#pragma once

class DataClassManager
{
public:
	void AddClass(const SPtrClass& cls);

	SPtrClass Get(int id) const;
	SPtrClass Get(const std::string& name) const;

	void SetName(const std::string& name) { this->name = name; }
private:
	std::string name;
	std::unordered_map<int, SPtrClass> classIDList;
	std::unordered_map<std::string, SPtrClass> classNameList;
};
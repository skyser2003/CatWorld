#pragma once

class DataList
{
public:
	void AddClass(const SPtrClass& cls);

	SPtrClass Get(int id) const;
	SPtrClass Get(const std::string& name) const;

	void SetName(const std::string& name) { this->name = name; }
	const std::string& Name() const { return name; }
private:
	std::string name;
	std::unordered_map<int, SPtrClass> classIDList;
	std::unordered_map<std::string, SPtrClass> classNameList;
};
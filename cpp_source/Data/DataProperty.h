#pragma once

#include "DataType.h"

class DataProperty
{
public:
	DataProperty() : type(INT), intVal(0) {} // Default value set to int
	~DataProperty() {}

	template <DataType type>
	typename TypeStruct<type>::type Get() const;

	template <DataType type>
	void SetValue(typename TypeStruct<type>::type value);
	
	void SetKey(const std::string& key);

	DataType GetType() const;
private:
	void SetType(DataType type);

	DataType type;
	std::string key;

	union
	{
		TypeStruct<INT>::type intVal;
		TypeStruct<FLOAT>::type floatVal;
		TypeStruct<STRING>::type strVal;
		TypeStruct<BOOL>::type boolVal;
	};
};
#include "stdafx.h"
#include "DataProperty.h"

template <>
typename TypeStruct<INT>::type DataProperty::Get<INT>() const
{
	return intVal;
}

template <>
typename TypeStruct<FLOAT>::type DataProperty::Get<FLOAT>() const
{
	return floatVal;
}

template <>
typename TypeStruct<STRING>::type DataProperty::Get<STRING>() const
{
	return strVal;
}

template <>
typename TypeStruct<BOOL>::type DataProperty::Get<BOOL>() const
{
	return boolVal;
}

template <>
void DataProperty::SetValue<INT>(TypeStruct<INT>::type value)
{
	SetType(INT);
	intVal = value;
}

template <>
void DataProperty::SetValue<FLOAT>(TypeStruct<FLOAT>::type value)
{
	SetType(FLOAT);
	floatVal = value;
}

template <>
void DataProperty::SetValue<STRING>(TypeStruct<STRING>::type value)
{
	SetType(STRING);
	if (type == STRING)
	{
		delete[] strVal;
	}

	size_t strLen = strlen(value);
	strVal = new char[strLen + 1];
	strcpy_s(const_cast<char*>(strVal), strLen, value);
}

template <>
void DataProperty::SetValue<BOOL>(TypeStruct<BOOL>::type value)
{
	SetType(BOOL);
	boolVal = value;
}

void DataProperty::SetKey(const std::string& key)
{
	this->key = key;
}

DataType DataProperty::GetType() const
{
	return type;
}

void DataProperty::SetType(DataType type)
{
	this->type = type;
}
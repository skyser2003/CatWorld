#include "stdafx.h"
#include "DataType.h"

template <>
DataType GetType<int>()
{
	return INT;
}

template <>
DataType GetType<float>()
{
	return FLOAT;
}

template <>
DataType GetType<const char*>()
{
	return STRING;
}

template <>
DataType GetType<bool>()
{
	return BOOL;
}
#pragma once

enum DataType
{
	INT,
	FLOAT,
	STRING,
	BOOL
};

// Specialization only
template <DataType type>
struct TypeStruct;

template <>
struct TypeStruct < INT >
{
	typedef int type;
};

template <>
struct TypeStruct < FLOAT >
{
	typedef float type;
};

template <>
struct TypeStruct < STRING >
{
	typedef const char* type;
};

template <>
struct TypeStruct < BOOL >
{
	typedef bool type;
};


// Specialization only
template <class T>
DataType GetType();
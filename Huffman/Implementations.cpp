#include "Implementations.h"



String::String()
{
	size = 1;
	str = new char[size];
	str[0] = '\0';
}

String::String(const String& rhs)
{
	copy(rhs);
}

String::String(const char* str)
{
	if (str != NULL)
	{
		size = strlen(str) + 1;
		this->str = new (std::nothrow)char[size];
		if (this->str)
			strcpy_s(this->str, size, str);
	}
}

String& String::operator = (const String& rhs)
{
	if (this == &rhs)
		return *this;

	delete[] str;
	copy(rhs);

	return *this;
}

String::~String()
{
	delete[] str;
}

bool String::operator == (const String& rhs) const
{
	return strcmp(str, rhs.str) == 0;
}

void String::copy(const String& rhs)
{
	size = rhs.size;
	this->str = new (std::nothrow)char[size];

	if (this->str && rhs.str)
		strcpy_s(str, size, rhs.str);
}

String& String::operator += (const char* add)
{
	if (!add)
		return *this;

	size_t newSize = size + strlen(add);
	char* buffer = new char[newSize];
	strcpy_s(buffer, size, str);
	strcpy_s(buffer + size - 1, strlen(add) + 1, add);

	size = newSize;
	delete[] str;
	str = buffer;

	return *this;
}


std::istream& operator >> (std::istream& is, String& str)
{
	char buffer[4096];
	is >> buffer;

	String temp(buffer);
	str = temp;

	return is;
}

std::ostream& operator << (std::ostream& os, const String& str)
{
	if (str.str != NULL)
		os << str.str;
	return os;
}

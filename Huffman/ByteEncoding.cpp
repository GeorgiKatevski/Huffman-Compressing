
#include "ByteEncoding.h"
#include <iostream>


ByteEncoding::ByteEncoding()
{

}

ByteEncoding& ByteEncoding::operator= (const ByteEncoding& rhs)
{


	if (this == &rhs)
		return *this;

	key = rhs.key;
	codeLength = rhs.codeLength;
	code = rhs.code;

	return *this;
}

ByteEncoding::ByteEncoding(unsigned char key, size_t codeLength, unsigned short code) :
	key(key), codeLength(codeLength), code(code)
{

}

bool ByteEncoding::operator < (const ByteEncoding& rhs) const
{

	if (codeLength < rhs.codeLength)
		return true;
	else if (codeLength == rhs.codeLength)
		return key < rhs.key;

	return false;
}

bool ByteEncoding::operator >(const ByteEncoding& rhs)const
{
	return rhs < *this;
}


void ByteEncoding::print() const
{
	std::cout << key << " " << codeLength << " code: ";
	for (int i = codeLength - 1; i >= 0; i--)
	{
		std::cout << (code & 1 << i ? "1" : "0");
	}
	std::cout << std::endl;
}





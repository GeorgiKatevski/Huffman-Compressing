#pragma once
struct ByteEncoding
{
	ByteEncoding();
	ByteEncoding& operator=(const ByteEncoding& rhs);
	ByteEncoding(unsigned char key, size_t codeLength = 0, unsigned short code = 0);

	bool operator <(const ByteEncoding& rhs) const;
	bool operator >(const ByteEncoding& rhs) const;

	void print() const;

	// Symbol
	unsigned char key;
	// Code for the symbol
	unsigned short code;
	// Length of the code for the symbol
	size_t codeLength;
};

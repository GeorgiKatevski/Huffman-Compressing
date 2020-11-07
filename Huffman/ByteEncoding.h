#pragma once
struct ByteEncoding
{

	ByteEncoding();
	ByteEncoding& operator=(const ByteEncoding& rhs);
	ByteEncoding(unsigned char key, size_t codeLength = 0, unsigned short code = 0);

	bool operator <(const ByteEncoding& rhs) const;
	bool operator >(const ByteEncoding& rhs) const;

	void print() const;

	//символ 
	unsigned char key;
	//код на символа
	unsigned short code;
	//дължината на коа на символа
	size_t codeLength;

};
#pragma once
#include "State.h"
#include "ByteEncoding.h"
#include "HuffmanTable.h"
#include "Implementations.h"

class HuffmanCoding
{
public:
	
	HuffmanCoding();

	HuffmanCoding(const HuffmanCoding& rhs);

	HuffmanCoding& operator=(const HuffmanCoding& rhs);

	~HuffmanCoding();
	// Main functions
	// Archiving files
	void zip(String toPack, String toCreate, Vector<std::string> item);
	// Extracting files
	void unzip(String toUnpack, String dir);
	// Info about the given archive - shows the list of archived files
	void info(String toList);

private:
	// Encodes the content of a given file
	void encodeContent(std::ofstream& os, unsigned char* content, unsigned char* encodedContent);
	// Decodes the content of a given file
	void decodeContent(std::ostream& os, size_t bitsCount, unsigned char* content, unsigned char* decodedContent);
	// Converts from wstring to char array so it can be written to the file
	void wstringToCharArr(std::wstring ws, unsigned char* fileName);

	int	 decode(State* s, short* countArr, short* symbol);

private:
	size_t size;

	const size_t KB;

	const size_t BUFFER_SIZE;

	const size_t ENCODED_TREE_SIZE;

	HuffmanTable* huffmanTable;
	enum flag
	{
		//край на файла
		FE, 
		//съдържание
		CONTENT,
		//начало на файла
		SOF, 
		//начало на директорията
		SOD, 
		//край на директорията
		EOD,
		//празна директория 
		ED, 
	};
};
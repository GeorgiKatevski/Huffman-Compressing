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
	//основни функции
	//архивиране на файлове
	void zip(String toPack, String toCreate,Vector<std::string> item);
	//разархивиране на файлове
	void unzip(String toUnpack, String dir);
	//инфо за подаден архив-показа списъка от архивираните файлове
	void info(String toList);

private:
	//тази функцие кодира съдържанието на даден файл
	void encodeContent(std::ofstream& os, unsigned char* content, unsigned char* encodedContent);
	//тази функция декодира съдържанието  на даден файл 
	void decodeContent(std::ostream& os, size_t bitsCount, unsigned char* content, unsigned char* decodedContent);
	//конвериране от wstring kum char arr за да може да се запише на файла 
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
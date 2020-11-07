#pragma once
#include "ByteEncoding.h"
#include "MinHeap.h"

class HuffmanTable
{

public:
	HuffmanTable() {};
	HuffmanTable(const HuffmanTable& rhs) {};
	~HuffmanTable() {};

	//tazi funkciq prebroqva broq na vsichki simvoli v dadeniq tekstov fail
	void countFr(int* totalFr, size_t size, unsigned char* content);
	//tazi funkciq suzdava tablica ot 256 znaka s code code length i key
	void initTable(ByteEncoding* table);

	//с тази функция намираме броя на  различните символи в дадения файл
	void generateLength(DataNode* root, int len, ByteEncoding*& arr);


	//tazi funkciq suzdava krainata tablica koqto e napravena chrez cannonichno predstavq na huffman
	void finalTable(ByteEncoding sortedTable[], ByteEncoding finalTable[], size_t size);

	void restoreCodes(unsigned char* content, size_t size, short* countArr, short* symArr);
	
	//тази функция построява дървото
	DataNode* buildHuffmanTree(int* freq, size_t size);

	//kanonichno predstavqne na huffman
	ByteEncoding* cannonicalHuffman(DataNode* root);

	//построяване на таблица
	ByteEncoding* buildTable(unsigned char* content, size_t size);
private:
	void clear(DataNode* root);
};
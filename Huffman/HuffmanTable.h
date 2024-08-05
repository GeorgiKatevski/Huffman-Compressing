#pragma once
#include "ByteEncoding.h"
#include "MinHeap.h"

class HuffmanTable
{

public:
	HuffmanTable() {};
	HuffmanTable(const HuffmanTable& rhs) {};
	~HuffmanTable() {};

	// Counts the number of all symbols in the given text file
	void countFr(int* totalFr, size_t size, unsigned char* content);
	// Creates a table of 256 characters with code, code length, and key
	void initTable(ByteEncoding* table);

	// Find the number of different symbols in the given file
	void generateLength(DataNode* root, int len, ByteEncoding*& arr);

	// Creates the final table which is made through the canonical representation of Huffman
	void finalTable(ByteEncoding sortedTable[], ByteEncoding finalTable[], size_t size);

	void restoreCodes(unsigned char* content, size_t size, short* countArr, short* symArr);
	
	// Builds the tree
	DataNode* buildHuffmanTree(int* freq, size_t size);

	// Canonical representation of Huffman
	ByteEncoding* cannonicalHuffman(DataNode* root);

	// Building the table
	ByteEncoding* buildTable(unsigned char* content, size_t size);
private:
	void clear(DataNode* root);
};
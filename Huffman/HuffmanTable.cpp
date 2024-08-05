#include "HuffmanTable.h"
#include "MinHeap.h"
#include "Implementations.h"

// Building the table 
// Needed for the algorithm itself
// Consists of symbols and their frequency in the file 
ByteEncoding* HuffmanTable::buildTable(unsigned char* content, size_t size)
{
	int totalFr[256] = { 0, };
	countFr(totalFr, size, content);
	// Create the Huffman tree using minHeap (explained in MinHeap.h)
	// 256 are the elements in the ASCII table
	DataNode* root = buildHuffmanTree(totalFr, 256);
	// After building the tree, create the table from this tree
	ByteEncoding* table = cannonicalHuffman(root);
	clear(root);
	return table;
}

// This function counts the total occurrences of each character in the given text file
void HuffmanTable::countFr(int* totalFr, size_t size, unsigned char* content)
{
	for (size_t i = 0; i < size; i++)
	{
		totalFr[content[i]]++;
	}
}

// This function builds the Huffman tree
DataNode* HuffmanTable::buildHuffmanTree(int* freq, size_t size)
{
	MinHeap mh;
	// 256 characters in the ASCII table
	for (size_t i = 0; i < 256; i++)
	{
		if (freq[i] != 0)
		{
			// Insert symbols with their frequency in the given file
			mh.insert(new DataNode(freq[i], (unsigned char)i, false));
		}
	}

	// Create a parent whose children are the two smallest elements
	// Take them from the built minHeap tree 
	while (mh.size() != 1)
	{
		DataNode* left = mh.getMin();
		mh.removeMin();

		DataNode* right = mh.getMin();
		mh.removeMin();

		DataNode* top = new DataNode(left->frequency + right->frequency, '$', true);
		top->left = left;
		top->right = right;
		mh.insert(top);
	}

	DataNode* root = mh.getMin();
	mh.removeMin();

	if (!root->isInternal) // Special case of a single element
	{
		DataNode* top = new DataNode(root->frequency + 1, '$', true);
		top->left = root;
		return top;
	}

	return root;
}

// Constructing the tree in a canonical manner
ByteEncoding* HuffmanTable::cannonicalHuffman(DataNode* root)
{
	ByteEncoding* sortedTable = new ByteEncoding[256];
	initTable(sortedTable);
	generateLength(root, 0, sortedTable);
	quickSort(sortedTable, 256);

	int firstLetter = 0;
	while (firstLetter < 256 && sortedTable[firstLetter].codeLength == 0)
		firstLetter++;

	if (firstLetter < 256)
		sortedTable[firstLetter].code = 0;

	int last = firstLetter;
	for (size_t i = firstLetter + 1; i < 256; i++)
	{
		if (sortedTable[i].codeLength != 0)
		{
			sortedTable[i].code = sortedTable[last].code + 1;
			int diff = sortedTable[i].codeLength - sortedTable[last].codeLength;
			sortedTable[i].code <<= diff;
			last = i;
		}
	}

	ByteEncoding* table = new ByteEncoding[256];
	finalTable(sortedTable, table, 256);
	delete[] sortedTable;

	return table;
}

void HuffmanTable::clear(DataNode* root)
{
	if (!root) return;
	clear(root->left);
	clear(root->right);
	delete root;
}

void HuffmanTable::generateLength(DataNode* root, int len, ByteEncoding*& arr)
{
	if (!root)
		return;
	// If it's a parent that has combined two children
	if (!root->isInternal)
		arr[root->key].codeLength = len;

	generateLength(root->left, len + 1, arr);
	generateLength(root->right, len + 1, arr);
}

void HuffmanTable::initTable(ByteEncoding* table)
{
	for (size_t i = 0; i < 256; i++)
	{
		table[i].code = 0;
		table[i].key = (unsigned char)i;
		table[i].codeLength = 0;
	}
}

// With this function we actually form the final table
// Constructing it in a canonical manner
void HuffmanTable::finalTable(ByteEncoding sortedTable[], ByteEncoding finalTable[], size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		finalTable[sortedTable[i].key].code = sortedTable[i].code;
		finalTable[sortedTable[i].key].codeLength = sortedTable[i].codeLength;
		finalTable[sortedTable[i].key].key = sortedTable[i].key;
	}
}

/* Modifying countArr and symArr */
void HuffmanTable::restoreCodes(unsigned char* content, size_t size, short* countArr, short* symArr)
{
	ByteEncoding* basicTable = new ByteEncoding[256];
	initTable(basicTable);
	int pos = 0;
	int shiftPos = 0;
	unsigned char buffer = 0;

	/* Decode tree lengths */
	for (size_t i = 0; i < 160; i++)
	{
		size_t lengthToRead = content[i];
		for (int j = 0; j < 8; j++)
		{
			buffer = buffer | ((lengthToRead & 1) << shiftPos);
			shiftPos++;

			if (shiftPos == 5)
			{
				basicTable[pos].codeLength = (size_t)buffer;
				pos++;
				shiftPos = 0;
				buffer = 0;
			}
			lengthToRead = lengthToRead >> 1;
			shiftPos = shiftPos % 8;
		}
	}

	/* Restore tree codes */
	quickSort(basicTable, 256);
	int p = 0;
	for (size_t i = 0; i < 256; i++)
	{
		if (basicTable[i].codeLength != 0)
		{
			symArr[p] = basicTable[i].key;
			p++;
			countArr[basicTable[i].codeLength]++;
		}
	}
}

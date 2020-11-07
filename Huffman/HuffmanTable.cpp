#include "HuffmanTable.h"
#include "MinHeap.h"
#include "Implementations.h"


//построяване на таблица 
//нужна е за самият алгоритъм
// състои се от символи и тяхната честота във файла 
ByteEncoding* HuffmanTable::buildTable(unsigned char* content, size_t size)
{
	int totalFr[256] = { 0, };
	countFr(totalFr, size, content);
	//създаваме даървото на хъфман чрез minHeap-(обяснено в MinHeap.h)
	//256 са елементите в ascii таблицата
	DataNode* root = buildHuffmanTree(totalFr, 256);
	//след като построим дървото от това дърво създаваме таблица 
	ByteEncoding* table = cannonicalHuffman(root);
	clear(root);
	return table;
}
//тази функция преброява колко общо са всички срещания на буквите в дадения тексов файл
void HuffmanTable::countFr(int* totalFr, size_t size, unsigned char* content)
{
	for (size_t i = 0; i < size; i++)
	{
		totalFr[content[i]]++;
	}
}

//тази функция построява дърво на хъфман 
DataNode* HuffmanTable::buildHuffmanTree(int* freq, size_t size)
{

	MinHeap mh;
	//256 знаци в ascii таблицата
	for (size_t i = 0; i < 256; i++)
	{
	
		if (freq[i] != 0)
		{
			//инсертваме символи с тяхната честота в дадения файл
			mh.insert(new DataNode(freq[i], (unsigned char)i, false));
		}
	}

//създаваме родител чиито деца са двата най-малки елемента
//взимаме ги от построеното minHeap дърво 

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

	if (!root->isInternal) //special case of a single element
	{
		DataNode* top = new DataNode(root->frequency + 1, '$', true);
		top->left = root;
		return top;
	}

	return root;



}
//"constructing the tree in a cannonical manner"
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
	//ако е родител който е обединил две деца
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

// s tazi funkciq nie vsushtnost formirame krainata tablica
//konstruiraneto i ot kanonichen nachin
void HuffmanTable::finalTable(ByteEncoding sortedTable[], ByteEncoding finalTable[], size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		finalTable[sortedTable[i].key].code = sortedTable[i].code;
		finalTable[sortedTable[i].key].codeLength = sortedTable[i].codeLength;
		finalTable[sortedTable[i].key].key = sortedTable[i].key;
	}
}


/* modifying countArr and sym Arr */
void HuffmanTable::restoreCodes(unsigned char* content, size_t size, short* countArr, short* symArr)
{
	ByteEncoding* basicTable = new ByteEncoding[256];
	initTable(basicTable);
	int pos = 0;
	int shiftPos = 0;
	unsigned char buffer = 0;


	/* decode tree lengths */
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

	/* restore tree codes */

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
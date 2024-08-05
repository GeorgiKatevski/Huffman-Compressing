#pragma once
#include "Implementations.h"
struct DataNode
{
	// Symbol
	unsigned char key;
	// Frequency of the symbol
	int frequency;
	DataNode* left, * right;
	// isInternal is needed to check when traversing which node is a symbol with a frequency
	// because when the tree is created and two children are combined, their parent has the sum of their frequencies
	// and isInternal is false
	bool isInternal;
	DataNode(const DataNode& rhs)
	{
		key = rhs.key;
		frequency = rhs.frequency;
		left = rhs.left;
		right = rhs.right;
	}

	DataNode(int frequency, unsigned char key, bool isInternal) :
		left(nullptr), right(nullptr), key(key), frequency(frequency), isInternal(isInternal) {}

	bool operator > (const DataNode& rhs)
	{
		return frequency > rhs.frequency;
	}

};

// through this tree we implement Huffman's algorithm
// In minHeap, the symbol at the root must be the smallest among
// all keys in the Binary heap
// the same condition must be true for all nodes in the given Binary Tree
class MinHeap
{
public:
	MinHeap();
	MinHeap(const MinHeap& rhs);
	MinHeap& operator=(const MinHeap& rhs);
	~MinHeap();
	MinHeap(DataNode* arr[], size_t size);
	void insert(DataNode* val);
	// Remove the minimum element from the heap
	void removeMin();
	size_t size() const
	{
		return data.getSize();
	}
	// This function returns the root of the tree
	DataNode* getMin();
private:
	void heapify();
	void minHeapify(int indx);
	void bubbleUp(int indx);
private:
	Vector<DataNode*> data;

};
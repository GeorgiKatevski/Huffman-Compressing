#include "MinHeap.h"


MinHeap::MinHeap() : data()
{

}

MinHeap::MinHeap(const MinHeap& rhs) : data(rhs.data)
{

}
MinHeap& MinHeap::operator=(const MinHeap& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}
	data = rhs.data;
	return *this;
}
MinHeap::MinHeap(DataNode* arr[], size_t size)
{

	for (size_t i = 0; i < size; i++)
	{
		data.push_back(arr[i]);

	}

	heapify();

}
MinHeap::~MinHeap()
{

}


void MinHeap::heapify()
{

	for (int i = data.getSize() - 1; i >= 0; i--)
	{
		minHeapify(i);
	}

}

void MinHeap::minHeapify(int indx)
{
	int leftChild = 2 * indx + 1;
	int rightChild = 2 * indx + 2;
	if (leftChild >= data.getSize())
	{
		return;
	}
	int parent = indx;
	if (data[indx]->frequency > data[leftChild]->frequency)
	{
		parent = leftChild;
	}
	if (rightChild < data.getSize() && data[parent]->frequency > data[rightChild]->frequency)
	{
		parent = rightChild;
	}
	if (parent != indx)
	{
		DataNode* temp = data[indx];
		data[indx] = data[parent];
		data[parent] = temp;
		minHeapify(parent);
	}
}


DataNode* MinHeap::getMin()
{
	return data[0];
}

void MinHeap::removeMin()
{
	if (data.getSize() == 0)
		return;

	data[0] = data.back();
	data.pop_back();

	minHeapify(0);
}


void MinHeap::insert(DataNode* val)
{
	data.push_back(val);
	bubbleUp(data.getSize() - 1);
	int test = data.getSize();
}

void MinHeap::bubbleUp(int indx)
{
	if (indx == 0)
		return;

	int parent = (indx - 1) / 2;

	if (data[parent]->frequency > data[indx]->frequency)
	{
		DataNode* temp = data[parent];
		data[parent] = data[indx];
		data[indx] = temp;
		bubbleUp(parent);
	}
}





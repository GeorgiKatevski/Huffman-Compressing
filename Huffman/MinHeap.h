#pragma once
#include "Implementations.h"
struct DataNode
{
	//символ
	unsigned char key;
	//честота на символ
	int frequency;
	DataNode* left, * right;
	//isInternal ни трябва да проверява когато обхожда ме кой възел е символ с честота 
	//понеже когато се създаде дървото и някои и като се обединят две две деца родителя им е сбора от тяхните честоти 
	//и isInternal e false
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

//чрез това дърво осъществяваме алгоритъма на Хъфман
// В minHeap , символът който се намира в коранът трябва да бъде най-малкия измежду
//всички ключове в Binary heap
//същото условие да е вярно за всички node-ве в в даденото Binary Tree
class MinHeap
{
public:
	MinHeap();
	MinHeap(const MinHeap& rhs);
	MinHeap& operator=(const MinHeap& rhs);
	~MinHeap();
	MinHeap(DataNode* arr[], size_t size);
	void insert(DataNode* val);
	//премахва корена на дървото
	void removeMin();
	size_t size() const
	{
		return data.getSize();
	}
	//тази функция връща корена на дървото
	DataNode* getMin();
private:
	void heapify();
	void minHeapify(int indx);
	void bubbleUp(int indx);
private:
	Vector<DataNode*> data;

};
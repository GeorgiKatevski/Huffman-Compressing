#pragma once
#include <assert.h>
#include <iostream>
#include <new> /* nothrow */


//имплементация на вектор
template < typename T >
class Vector
{
public:
	Vector();
	Vector(const Vector& rhs);
	Vector& operator=(const Vector& rhs);
	~Vector();

	void push_back(const T& val);
	void pop_back();
	T& back() const;

	T& operator[] (size_t idx);
	T	operator[] (size_t idx) const;

	bool	isEmpty()	const { return size == 0; }
	long long	getSize()	const { return size; }

private:
	void copy(const Vector& rhs);
	void clear();
	void resize();

private:
	T* data;
	size_t	size;
	size_t	capacity;
};


template <typename T>
Vector<T>::Vector() : data(nullptr), size(0), capacity(0)
{
}

template <typename T>
Vector<T>::Vector(const Vector& rhs)
{
	copy(rhs);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhs)
{
	if (this == &rhs)
		return *this;

	clear();
	copy(rhs);

	return *this;
}

template <typename T>
Vector<T>::~Vector()
{
	clear();
}

template <typename T>
void Vector<T>::push_back(const T& val)
{
	if (size == capacity)
		resize();

	data[size++] = val;
}

template <typename T>
void Vector<T>::pop_back()
{
	assert(size > 0);
	if (size == 0)
		return;

	size--;
}

template <typename T>
T& Vector<T>::back() const
{
	assert(size > 0);
	if (size == 0)
		throw "Empty vector.\n";

	return data[size - 1];
}


template <typename T>
T& Vector<T>::operator[] (size_t idx)
{
	assert(size > 0 && (idx < size && idx >= 0));

	if (!(size > 0 && (idx < size && idx >= 0)))
		throw "Bad index\n";

	return data[idx];
}


template <typename T>
T Vector<T>::operator[] (size_t idx) const
{
	if (idx > size)
		return 0;

	return data[idx];
}

template <typename T>
void Vector<T>::copy(const Vector& rhs)
{
	size = rhs.size;
	capacity = rhs.capacity;

	data = new (std::nothrow) T[capacity];
	if (!data)
		return;

	for (size_t i = 0; i < size; i++)
	{
		data[i] = rhs.data[i];
	}
}

template <typename T>
void Vector<T>::clear()
{
	delete[] data;
}

template <typename T>
void Vector<T>::resize()
{
	if (capacity == 0)
	{
		capacity = 2;
		data = new T[capacity];
	}

	else
	{
		capacity <<= 1;
		T* temp = new (std::nothrow) T[capacity];

		if (!temp)
		{
			std::cout << "You can't add more items to the vector\n";
			return;
		}

		for (size_t i = 0; i < size; i++)
		{
			temp[i] = data[i];
		}
		delete[] data;
		data = temp;
	}
}

class String
{
	friend std::ostream& operator << (std::ostream& out, const String& s);
	friend std::istream& operator >> (std::istream& in, String& s);

public:
	String();
	String(const String& rhs);
	String(const char* str);
	String& operator= (const String& rhs);
	~String();

	bool operator == (const String& rhs) const;
	String& operator+=(const char* add);

	char* c_str()	const { return str; }
	char* getStr() const { return str; }
	size_t getLen() const { return size - 1; }

private:
	void copy(const String& rhs);

private:
	char* str;
	size_t size;
};
#include <string.h>


//имплементация на стек
template < typename T >
class Stack
{
public:
	Stack();
	Stack(const Stack& rhs);
	Stack& operator=(const Stack& rhs);
	~Stack();

	void push(const T& val);
	void pop();
	T& top() const;

	bool	isEmpty() const { return data.isEmpty(); }
	size_t	getSize() const { return data.getSize(); }

private:
	Vector<T> data;

};


template <typename T>
Stack<T>::Stack() : data()
{
}

template <typename T>
Stack<T>::Stack(const Stack& rhs) : data(rhs.data)
{
}

template <typename T>
Stack<T>& Stack<T>::operator = (const Stack<T>& rhs)
{
	if (this == &rhs)
		return *this;

	data = rhs.data;

	return *this;
}

template <typename T>
Stack<T>::~Stack()
{
}

template <typename T>
void Stack<T>::push(const T& val)
{
	data.push_back(val);
}

template <typename T>
void Stack<T>::pop()
{
	data.pop_back();
}

template <typename T>
T& Stack<T>::top() const
{
	return data.back();
}


//implementation of quicksort
#include <stdlib.h>   /* abs */
#include <algorithm> /* swap */


template <typename T>
int partition(T* data, int left, int right)
{
	int size = abs(left - right) + 1;
	if (size == 2)
	{
		if (data[left] > data[right])
			std::swap(data[left], data[right]);
		return left + 1;
	}

	int mid = left + size / 2;

	if (data[left] > data[mid])
		std::swap(data[left], data[mid]);
	if (data[mid] > data[right])
		std::swap(data[mid], data[right]);
	if (data[left] > data[mid])
		std::swap(data[left], data[mid]);

	/* puts median of tree as pivot in the right */
	std::swap(data[mid], data[right]);

	int pivot = right;
	int smaller = left - 1;

	for (int i = left; i <= right - 1; i++)
	{
		if (data[i] < data[pivot])
		{
			smaller++;
			std::swap(data[smaller], data[i]);
		}
	}

	std::swap(data[smaller + 1], data[pivot]);
	return smaller + 1;
}

template<typename T>
void quickSortStep(T* arr, int left, int right)
{
	if (left < right)
	{
		int p = partition(arr, left, right);
		quickSortStep(arr, left, p - 1);
		quickSortStep(arr, p + 1, right);
	}
}

template<typename T>
void quickSort(T* data, size_t size)
{
	quickSortStep(data, 0, size - 1);
}


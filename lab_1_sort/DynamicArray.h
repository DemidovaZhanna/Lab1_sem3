#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <iostream>
using namespace std;

template <typename T>
class DynamicArray
{
private:
	int m_size;
	int m_capacity;
	T *m_data;

public:
	DynamicArray ();
	DynamicArray (T *my_data, int index);
	DynamicArray (const DynamicArray<T> & a);
	DynamicArray (int size);

	int getLength () const noexcept {return m_size;}
	void Resize (int newSize);

	T& operator[] (const int index);
	const T& operator[] (const int index) const;
	T& GetFirst () {return operator[](0);}
	const T& GetFirst () const {return operator[](0);}
	T& GetLast () {return operator[](m_size - 1);}
	const T& GetLast () const {return operator[](m_size - 1);}

	void Set (int index, T value);
	DynamicArray& operator= (const DynamicArray<T> &array);

	~DynamicArray () {}
};

template<typename T>
DynamicArray<T>::DynamicArray() {
	m_size = 0;
	m_capacity = 0;
	m_data = NULL;
}


template<typename T>
DynamicArray<T>::DynamicArray(T *my_data, int index)
{
	m_size = index;

	if(index)
		m_data = new T[index];
	else m_data = 0;
	for (int i = 0; i < m_size; i++)
		m_data[i] = my_data[i];
}


template<typename T>
DynamicArray<T>::DynamicArray (const DynamicArray<T> &a)
{
	m_size = a.m_size;
	m_capacity = m_size;
	m_data = NULL;
	if (m_size != 0)
		m_data = new T[m_size];
	else
		m_data = 0;
	for (int i = 0; i < m_size; i++)
		m_data[i] = a.m_data[i];
}


template<typename T>
DynamicArray<T>::DynamicArray (int size)
{
	m_size = size;
	m_capacity = size;
	if (size != 0)
		m_data = new T[size];
	else
		m_data = 0;
}


template<typename T>
void DynamicArray<T>::Resize (int newSize)
{
	if (newSize > m_capacity) {
		int new_capacity = max(newSize, m_size*2);
		T *new_data = new T[new_capacity];
		for (int i = 0; i < m_size; i++)
			new_data[i] = m_data[i];
		delete[] m_data;
		m_data = new_data;
		m_capacity = new_capacity;
	}

	m_size = newSize;
}


template<typename T>
T& DynamicArray<T>::operator[] (const int i)
{
	if(i + 1 > m_size || i < 0)
		throw std::out_of_range ("Index out of range");
	else
		return m_data[i];
}

template<typename T>
const T& DynamicArray<T>::operator[] (const int i) const
{
	if(i + 1 > m_size || i < 0)
		throw std::out_of_range ("Index out of range");
	else
		return m_data[i];
}


template<typename T>
void DynamicArray<T>::Set(int index, T value)
{
	Resize(m_size + 1);

	if(index > m_size - 1 || index < 0)
		throw std::out_of_range ("Index out of range");

	for (int i = m_size; i > index; i--)
		m_data[i] = m_data[i - 1];

	m_data[index] = value;
}


template<typename T>
DynamicArray<T> &DynamicArray<T>::operator=(const DynamicArray<T> &array)
{
	if (m_size != array.m_size) {
		m_size = array.m_size;
		delete[]m_data;
		m_data = new int[m_size];
	}
	for (int i = 0; i < m_size; i++)
		m_data[i] = array.m_data[i];
}

#endif // DYNAMICARRAY_H

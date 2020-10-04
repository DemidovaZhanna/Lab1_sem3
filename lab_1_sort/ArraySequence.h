#ifndef ARRAYSEQUENCE_H
#define ARRAYSEQUENCE_H

#include "Sequence.h"
#include "DynamicArray.h"

template <typename T>
class ArraySequence : public Sequence<T>
{
public:
	ArraySequence() : _array(new DynamicArray<T>) {}
	ArraySequence (T* data, int count);
	ArraySequence (const LinkedList <T> & list);

	T& Get(int i) {return _array->operator[](i);}
	const T& Get(int i) const {return _array->operator[](i);}
	int getLength() const noexcept {return _array->getLength();}

	void Append(const T& value) {_array->Set(0, value);}
	void Prepend(const T& value) {_array->Set(getLength(), value);}
	void InsertAt(const T& value, int index) {_array->Set(index, value);}

	Sequence<T>* GetSubsequence(int startIndex, int endIndex) const;
	Sequence <T>* Concat(Sequence <T> *list) const;
	Sequence<T>* operator + (Sequence<T> *a) const {return Concat(a);}

	~ArraySequence();

private:
	DynamicArray<T> *_array;
};


template<typename T>
ArraySequence<T>::ArraySequence(T* data, int count)
{
	_array = new DynamicArray<T>(data, count);
}

template<typename T>
ArraySequence<T>::ArraySequence(const LinkedList<T> &list)
{
	_array = new DynamicArray<T>;

	while (list.head != NULL) {
		DynamicArray<T> *curr = list.head->next;
		Prepend (curr->element);
		list.head->next = curr->next;
	}
}


template<typename T>
Sequence<T>* ArraySequence<T>::GetSubsequence(int startIndex, int endIndex) const
{
	return new ArraySequence<T>(&_array->operator[](startIndex), (endIndex - startIndex));
}


template<typename T>
Sequence<T> *ArraySequence<T>::Concat(Sequence<T> *list) const
{
	int len = _array->getLength() + list->getLength();
	ArraySequence<T> *res = new ArraySequence<T>();
	res->_array->Resize(len);

	for (int i = 0; i < _array->getLength(); i++)
		res->Append(_array->operator[](i));

	for (int i = 0; i < list->getLength(); i++)
		res->Append(list->Get(i));
	return res;
}


template<typename T>
ArraySequence<T>::~ArraySequence()
{
	delete _array;
}

#endif // ARRAYSEQUENCE_H

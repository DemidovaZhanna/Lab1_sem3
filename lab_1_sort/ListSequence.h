#ifndef LISTSEQUENCE_H
#define LISTSEQUENCE_H

#include "Sequence.h"
#include "LinkedList.h"

template <typename T>
class ListSequence: public Sequence<T>
{
public:
	ListSequence() : _list(new LinkedList <T>()) {}

	ListSequence(T* data, int count);
	ListSequence (LinkedList<T>& list);

	T& GetFirst() {return _list->GetFirst();}
	T& GetLast() {return _list->GetLast();}

	T& Get(int i) {return _list->operator[](i);}
	const T& Get(int i) const {return _list->operator[](i);}

	void erase() {_list->clear();}
	void pop_front() {_list->pop_front();}
	void pop_back() {_list->pop_back();}

	Sequence<T>* GetSubsequence(int startIndex, int endIndex) const;
	Sequence<T>* Concat(Sequence <T> *seq) const;
	Sequence<T>* operator+ (Sequence<T> *a) const {return Concat(a);}

	int getLength() const {return _list->getLength();}
	void Append(const T& value) {_list->Append(value);}
	void Prepend(const T& value) {_list->Prepend(value);}
	void InsertAt(const T& value, int i) {_list->InsertAt(value, i);}

	~ListSequence();

private:
	LinkedList<T> *_list;
};

template<typename T>
ListSequence<T>::~ListSequence()
{
	delete _list;
}



template<typename T>
ListSequence<T>::ListSequence(T *data, int count)
{
	_list = new LinkedList<T>(data, count);
}

template<typename T>
ListSequence<T>::ListSequence(LinkedList<T> &list) {
	_list = new LinkedList<T>(list);
}


template<typename T>
Sequence<T> *ListSequence<T>::GetSubsequence(int startIndex, int endIndex) const
{
	if (endIndex < startIndex || startIndex < 0 || endIndex + 1 > this->getLength())
		throw std::out_of_range ("Index out of range");

	ListSequence<T> *newList = new ListSequence<T>;

	for (int i = startIndex; i <= endIndex; i++)
		newList->Prepend(this->Get(i));

	return newList;
}


template<typename T>
Sequence<T> *ListSequence<T>::Concat(Sequence<T> *seq) const
{
	ListSequence<T> *ret = new ListSequence<T>;

	for (int i = 0; i < this->getLength(); i++)
		ret->Prepend(this->Get(i));

	for (int i = 0; i < seq->getLength(); i++)
		ret->Prepend(seq->Get(i));

	return ret;

}

#endif // LISTSEQUENCE_H

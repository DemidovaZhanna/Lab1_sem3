#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

using namespace std;

template <typename T>
class LinkedList
{
public:
	LinkedList ();
	LinkedList (T* data, int count);
	LinkedList (const LinkedList <T>& list);

	T& GetFirst () {return operator[](0);}
	const T& GetFirst () const {return operator[](0);}
	T& GetLast () {return operator[](size - 1);}
	const T& GetLast () const {return operator[](size - 1);}
	T& operator[] (const int index);
	const T& operator[] (const int index) const;

	void pop_front ();
	void pop_back();
	void clear();

	void Append (const T& data);
	void Prepend (const T& data);
	void InsertAt (const T& data, int index);

	int getLength () const {return size;}
	LinkedList<T>* Concat(LinkedList<T> *list) const;
	LinkedList<T>* GetSubList (int startIndex, int endIndex) const;

	LinkedList& operator= (const LinkedList<T> &list);

	~LinkedList () {clear();}

private:
	class Node
	{
	public:
		Node *pNext;
		T data;
		Node(T data = T(), Node *pNext = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
		}
	};

	Node *head;
	int size;
};

template<typename T>
LinkedList<T>::LinkedList()
{
	size = 0;
	head = nullptr;
}


template<typename T>
void LinkedList<T>::pop_front()
{
	Node *temp = head;
	head = head->pNext;

	delete temp;
	size--;
}

template<typename T>
void LinkedList<T>::pop_back()
{
	Node *current = this->head;
	while (current->pNext != nullptr)
		current = current->pNext;
	delete current->pNext;

	current = nullptr;
	size--;
}


template<typename T>
void LinkedList<T>::clear()
{
	while (size)
		pop_front();
}

template<typename T>
LinkedList<T>::LinkedList(T *data, int count) : LinkedList()
{
	for (int i = 0; i < count; i++)
		Prepend(data[i]);
}


template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &list)
{
	Node *t = list.head->pNext;

	for (int i = 0; i < list.size; i++)
		InsertAt(t->data, i);
}


template<typename T>
void LinkedList<T>::Append(const T& data)
{
	head = new Node(data, head);
	size++;
}


template<typename T>
void LinkedList<T>::Prepend(const T& data)
{
	if (head == nullptr) {
		head = new Node(data);
		size++;
		return;
	}
	else {
		Node *current = this->head;
		while (current->pNext != nullptr)
			 current = current->pNext;
		current->pNext = new Node(data);
	}
	size++;
}


template<typename T>
void LinkedList<T>::InsertAt(const T& data, int index)
{
	if ((index + 1 > size || index < 0) && size != 1)
		throw std::out_of_range ("Index out of range");

	if (index == 0)
		Append(data);

	else {
		Node *previous = this->head;

		for (int i = 0; i < index - 1; i++)
			previous = previous->pNext;

		previous->pNext = new Node(data, previous->pNext);

		size++;
	}
}


template<typename T>
T &LinkedList<T>::operator[](const int index)
{
	if ((index + 1 > size || index < 0) && size != 1)
		throw std::out_of_range ("Index out of range");

	Node *current = this->head;
	int i = 0;
	while (current != nullptr) {
		if (i == index)
			return current->data;
		else {
			current = current->pNext;
			i++;
		}
	}
}


template<typename T>
const T &LinkedList<T>::operator[](const int index) const
{
	if ((index + 1 > size || index < 0) && size != 1)
		throw std::out_of_range ("Index out of range");

	Node *current = this->head;
	int i = 0;
	while (current != nullptr) {
		if (i == index)
			return current->data;
		else {
			current = current->pNext;
			i++;
		}
	}
}

template<typename T>
LinkedList<T>* LinkedList<T>::Concat(LinkedList<T> *list) const
{
	LinkedList<T> *newList = new LinkedList<T>;
	typename LinkedList<T>::Node *t;

	t = this->head;
	while(t != nullptr){
		newList->Append(t->data);
		t = t->pNext;
	}
	t = list->head;
	while(t != nullptr){
		newList->Append(t->data);
		t = t->pNext;
	}
	return newList;
}

template<typename T>
LinkedList<T> *LinkedList<T>::GetSubList(int startIndex, int endIndex) const
{
	if (endIndex < startIndex || startIndex < 0 || endIndex + 1 > size)
		throw std::out_of_range ("Index out of range");

	LinkedList<T> *newList = new LinkedList<T>;
	Node *current = this->head;

	int i = 0;
	while (i != startIndex) {
		current = current->pNext;
		i++;
	}

	for (; i <= endIndex; i++) {
		newList->Prepend(current->data);
		current = current->pNext;
	}

	return newList;
}

template<typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &list)
{
	clear();
	for(Node *t = list.head; t != nullptr; t = t->pNext)
			Append(t->data);
}

#endif // LINKEDLIST_H

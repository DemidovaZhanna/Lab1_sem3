#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "LinkedList.h"

template <typename T>
class Sequence
{
public:
	virtual T& GetFirst() {return Get(0);}
	virtual T& GetLast() {return Get(getLength() - 1);}
	virtual T& Get(int index) = 0;

	virtual const T& GetFirst() const {return Get(0);}
	virtual const T& GetLast() const {return Get(getLength() - 1);}
	virtual const T& Get(int index) const = 0;

	virtual int getLength() const = 0;
	virtual void Append(const T& item) = 0;
	virtual void Prepend(const T& item) = 0;
	virtual void InsertAt(const T& item, int index) = 0;

	virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;
	virtual Sequence<T>* Concat(Sequence<T> *list) const = 0;
	virtual Sequence<T>* operator +(Sequence<T> *a) const = 0;

	virtual bool operator==(const Sequence<T> &list) const;
	virtual bool operator!=(const Sequence<T> &list) const {return !(list == *this);}

};

template<typename T>
bool Sequence<T>::operator==(const Sequence<T> &list) const
{
	int flag = -1;
		if (this->getLength() == list.getLength()) {
			flag = 0;
			for (int i = 0; i < list.getLength(); i++) {
				if (this->Get(i) == list.Get(i))
					flag++;
			}
		}

		return flag == list.getLength();
}

#endif // SEQUENCE_H



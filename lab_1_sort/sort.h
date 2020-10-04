#ifndef SORT_H
#define SORT_H

#include <chrono>
#include "ArraySequence.h"

template <typename T>
inline void replacing_neighbors(Sequence<T>* seq, size_t first, size_t last) {
	T k = seq->Get(first);
	seq->Get(first) = seq->Get(last);
	seq->Get(last) = k;
}

template <typename T, typename Func>
void heapify(Sequence<T> *seq, int heap_size, int i, Func cmp) {
	int largest = i;

	int l = 2*i + 1;
	int r = 2*i + 2;

	if (l < heap_size && cmp(seq, largest, l))
		largest = l;

	if (r < heap_size && cmp(seq, largest, r))
		largest = r;

	if (largest != i) { //если самый большой элемент не корень
		replacing_neighbors(seq, i, largest);
		heapify(seq, heap_size, largest, cmp);
	}
}


template <typename T, typename Func>
class Sort
{
public:
	Sort(){}

	Sequence<T>* shell_sort(Sequence<T> *seq, Func cmp = [](auto a, auto b){
		return a < b;
	});
	Sequence<T>* heap_sort(Sequence<T> *seq, Func cmp = [](auto a, auto b){
		return a < b;
	});
	Sequence<T>* quick_sort(Sequence<T> *seq, Func cmp = [](auto a, auto b){
		return a < b;
	});
	Sequence<T>* _quick_sort(Sequence<T> *seq, int begin, int end, Func cmp);
};


template<typename T, typename Func>
Sequence<T> *Sort<T, Func>::shell_sort(Sequence<T> *seq, Func cmp)
{
	int step;

	for (step = seq->getLength()/2; step > 0; step /= 2)
		for (int i = step; i < seq->getLength(); i++)
			for (int j = i - step; j >= 0 && cmp(seq, j+step, j); j -= step)
				replacing_neighbors(seq, j, j + step);

	return seq;
}

template<typename T, typename Func>
Sequence<T> *Sort<T, Func>::heap_sort(Sequence<T> *seq, Func cmp)
{
	ArraySequence<T> *arr = new ArraySequence<T>();

	for (int i = 0; i < seq->getLength(); i++)
		arr->Prepend(seq->Get(i));

	//строим кучу(перегруппировав массив)
	for (int i = arr->getLength()/2 - 1; i >= 0; i--)
		heapify(arr, arr->getLength(), i, cmp);

	for (int i = arr->getLength() - 1; i >= 0; i--) {
		replacing_neighbors(arr, i, 0);
		heapify(arr, i, 0, cmp);
	}

	return arr;
}

template<typename T, typename Func>
Sequence<T> *Sort<T, Func>::quick_sort(Sequence<T> *seq, Func cmp)
{
	return _quick_sort(seq, 0, seq->getLength() - 1, cmp);
}

template<typename T, typename Func>
Sequence<T>* Sort<T, Func>::_quick_sort(Sequence<T> *seq, int begin, int end, Func cmp)
{
	int b = begin,
		e = end;
	int kon = (begin + end) / 2;

	do {
		while (cmp(seq, begin, kon))
			begin++;
		while(cmp(seq,kon, end))
			end--;
		if (begin <= end) {
			replacing_neighbors(seq, begin, end);
			begin++;
			end--;
		}
	} while (begin <= end);

	if (b < end)
		seq = _quick_sort(seq, b, end, cmp);
	if (begin < e)
		seq = _quick_sort(seq, begin, e, cmp);

	return seq;
}

#endif // SORT_H

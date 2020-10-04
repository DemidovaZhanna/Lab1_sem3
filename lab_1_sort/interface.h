#ifndef INTERFACE_H
#define INTERFACE_H

#include <ctime>
#include <functional>
#include <random>

#include "ArraySequence.h"
#include "sort.h"
#include "time_measurement.h"

using namespace std;
typedef unsigned long long ull;

template<typename T>
class Interface
{
public:
	Interface();

	Sequence<T>* sort();
	void start();

//	void to_type(std::string str, T& val);

private:
	Sequence<T>* Ar_s;

};

template<typename T>
Interface<T>::Interface()
{}

/*
//template <typename T>
//void Interface<T>::to_type(std::string str, T& val)
//{
////	val = str;
//}

//template <>
//void Interface<double>::to_type(std::string str, double& val)
//{
////	val = stod(str);
//}

//template <>
//void Interface<int>::to_type(std::string str, int& val)
//{
////	val = stoi(str);
//}
*/

template<typename T>
Sequence<T> *Interface<T>::sort()
{
	int choose;

	cout << "Select the sorting type: (click the number of the selected sort) " << endl;
	cout << "1. Shellsort" << endl << "2. Heapsort" << endl;
	cout << "3. Quick sort" << endl;
	cin >> choose;

	auto sort = Sort<T, std::function<bool(Sequence<T>*, int, int)>>();

	auto less = [](Sequence<T>* Ar_s, int first, int last){
		return Ar_s->Get(first) < Ar_s->Get(last);
	};

	long long time;
	switch (choose) {
	case 1:
		Ar_s = sort.shell_sort(Ar_s, less);

		time = time_measurement([&sort](auto seq, auto func) {
			return sort.shell_sort(seq, func);
		}, Ar_s, less);
		break;
	case 2:
		Ar_s = sort.heap_sort(Ar_s, less);

		time = time_measurement([&sort](auto seq, auto func) {
			return sort.heap_sort(seq, func);
		}, Ar_s, less);
		break;
	case 3:
		Ar_s = sort.quick_sort(Ar_s, less);

		time = time_measurement([&sort](auto seq, auto func) {
			return sort.quick_sort(seq, func);
		}, Ar_s, less);
		break;

	}
	cout << "A sorted sequence: ";

	for (int i = 0; i < Ar_s->getLength(); i++)
		cout << Ar_s->Get(i) << " ";

	cout << "\nElapsed time: " << time;
}

template<typename T>
void Interface<T>::start()
{
	int choose;
	int data = -1;
	while (data < 0) {
		cout << "Write down size of sequence: ";
		cin >> data;
	}
	cout << endl;
	T *a = new T[(ull)data];

	cout << "Enter '1' to fill in the sequence manually" << endl;
	cout << "Enter '2' to fill in the sequence with random values ";
	cin >> choose;

	switch(choose) {
	case 1:
		cout << "Enter the values of the sequence: ";
		for (int i = 0; i < data; i++) {
			cin >> a[i];

//			while(1)
//				try {
//					to_type(a[i], ress[i]);
//					break;
//				}
//				catch (std::invalid_argument&) {
//					cout << "The value was entered incorrectly. Enter this value again" << endl;
//					cin >> a[i];
//				}
		}
		break;
	case 2:
		int min, max;
		cout << "Min and max: ";
		cin >> min >> max;

		std::random_device rnd_device;
		std::mt19937 mersenne_engine {rnd_device()};
		std::uniform_int_distribution<int> dist{min, max};
		for(size_t i = 0; i < data; i++){
			a[i] = dist(mersenne_engine);
		}
		break;
	}
	Ar_s = new ArraySequence<T>(a, data);
	sort();
}

#endif // INTERFACE_H

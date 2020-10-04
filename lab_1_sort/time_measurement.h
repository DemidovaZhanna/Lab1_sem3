#ifndef TIME_MEASUREMENT_H
#define TIME_MEASUREMENT_H

#include <vector>
#include <algorithm>
#include <random>
#include "sort.h"

//template<typename T>
//long long time_measurement (T func) {

//	size_t N = 30000;

//	ios_base::sync_with_stdio(false);

//	Sequence<int>* seq;
//	vector<int> elements(N);
//	std::iota(elements.begin(), elements.end(), 1);
//	std::shuffle(elements.begin(), elements.end(), std::default_random_engine((unsigned int)time(nullptr)));

//	for (size_t i = 0; i < N; i++)
//		seq->Append(elements[i]);

//	auto start = chrono::high_resolution_clock::now();

//	func(seq);

//	auto stop = chrono::high_resolution_clock::now();
//	long long time = chrono::duration_cast<chrono::microseconds>(stop - start).count();

//	return time;
//}


template<typename T>
long long time_measurement (T func, Sequence<int>* seq) {

	ios_base::sync_with_stdio(false);
	auto start = chrono::high_resolution_clock::now();

	func(seq);

	auto stop = chrono::high_resolution_clock::now();
	long long time = chrono::duration_cast<chrono::microseconds>(stop - start).count();

	return time;
}

#endif // TIME_MEASUREMENT_H

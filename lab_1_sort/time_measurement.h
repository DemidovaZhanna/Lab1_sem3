#ifndef TIME_MEASUREMENT_H
#define TIME_MEASUREMENT_H

#include <vector>
#include <algorithm>
#include <random>
#include "sort.h"


template<typename T, typename Func, typename K>
long long time_measurement (T func, Sequence<K>* seq, Func cmp) {

	ios_base::sync_with_stdio(false);
	auto start = chrono::high_resolution_clock::now();

	func(seq, cmp);

	auto stop = chrono::high_resolution_clock::now();
	long long time = chrono::duration_cast<chrono::microseconds>(stop - start).count();

	return time;
}

#endif // TIME_MEASUREMENT_H

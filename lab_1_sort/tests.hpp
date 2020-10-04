#ifndef TESTS_HPP
#define TESTS_HPP

#include <sstream>
#include <functional>

#include "ArraySequence.h"
#include "ListSequence.h"
#include "sort.h"

using namespace std;


template<typename T>
ostream& operator<< (ostream & out, const Sequence<T>& a)
{
	for (int i = 0; i < a.getLength(); ++i)
		out << a.Get(i) << " ";
	return out;
}

template<class T, class U, class F=std::function<bool(const T&, const U&)>>
void AssertEqual(const T& t, const U& u, const string& hint,
				 F cmp = [](const T& t, const U& u){return t == u;})
{
  if (!cmp(t, u)) {
	ostringstream os;
	os << "Assertion failed: " << t << " != " << u << " hint: " << hint;
	throw runtime_error(os.str());
  }
}

class TestRunner
{
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name) {
		try {
			func();
			cout << test_name << " OK" << endl;
		} catch (runtime_error& e) {
			++fail_count;
			cout << test_name << " fail: " << e.what() << endl;
		}
	}

	~TestRunner() {
		if (fail_count > 0) {
			cout << fail_count << " unit tests failed. Terminate" << endl;
			exit(1);
		}
	}
private:
	int fail_count = 0;
};


void test_array_sequence() {
	AssertEqual(ArraySequence<int>().getLength(), 0, "The length is 0");

	int a[] = {1, 2, 3, 4, 6, 7, 8, 4};
	auto ar = ArraySequence<int>(a, 8);
	AssertEqual(ar.getLength(), 8, "The length is 8");
	AssertEqual(ar.Get(3), 4, "Get");

	ar.Append(9);

	int res[] = {9, 1, 2, 3, 4, 6, 7, 8, 4};
	auto Res = ArraySequence<int>(res, 9);
	AssertEqual(ar, Res, "Append");
}


void tests_list_sequence() {

	int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
	auto err = ListSequence<int>(a, 8);
	auto err2 = ListSequence<int>(a, 8);

	AssertEqual(err.GetFirst(), 1, "The first element is 1");

	err.Append(0);
	err.Prepend(9);

	int ar[10];
	for (int i = 0; i < 10; i++)
		ar[i] = i;
	auto li = ListSequence<int>(ar, 10);

	AssertEqual(err, li, "Append, Prepend and equality");

	li.pop_front();
	li.pop_back();

	AssertEqual(li, err2, "pop_front and pop_back");

	li.erase();
	AssertEqual(li.getLength(), ListSequence<int>().getLength(), "erase");
}

void tests_sort_array() {

	int a[] = {8, 7234, 3, 389, 1, 90, 32, 2};
	auto err = new ArraySequence<int>(a, 8);
	auto list = new ListSequence<int>(a, 8);

	int res[] = {1, 2, 3, 8, 32, 90, 389, 7234};
	auto res1 = new ArraySequence<int>(res, 8);
	auto res2 = new ListSequence<int>(res, 8);

	auto sort = Sort<int, std::function<bool(Sequence<int>*, int, int)>>();

	auto less = [](Sequence<int>* seq, int first, int last){
		return seq->Get(first) < seq->Get(last);
	};
	auto cmp = 	[](Sequence<int> *t, Sequence<int> *p) {
		return *t == *p;
	};

	auto sorter_shell = sort.shell_sort(err, less);
	auto sorter_hoap = sort.heap_sort(list, less);
	auto sorter_quick = sort.quick_sort(err, less);

	AssertEqual(res1, sorter_shell, "Shell sort", cmp);
	AssertEqual(res2, sorter_hoap, "Hoap sort", cmp);
	AssertEqual(res1, sorter_quick, "Quick sort", cmp);
}

#endif // TESTS_HPP

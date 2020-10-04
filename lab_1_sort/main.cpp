#include "Sequence.h"
#include "tests.hpp"
#include "interface.h"

int main()
{
	TestRunner runner;
	runner.RunTest(test_array_sequence, "test_array_sequence");
	runner.RunTest(tests_list_sequence, "tests_list_sequence");
	runner.RunTest(tests_sort_array, "tests_sort_array");

	cout << endl;
	interface_sort();

	return 0;
}

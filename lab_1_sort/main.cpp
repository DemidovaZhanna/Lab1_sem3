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

	cout << "Choose a type of sequence: Integer / Real / String" << endl;
	string cmd;
	cin >> cmd;

	while ( cmd != "Integer" && cmd != "Real" && cmd != "String") {
		cout << "Invalid keyword. Try again: ";
		cin >> cmd;
	}

	if (cmd == "Integer"){
		Interface<int> inter;
		inter.start();
	}
	else if (cmd == "Real"){
		Interface<double> inter;
		inter.start();
	}
	else {
		Interface<string> inter;
		inter.start();
	}



	return 0;
}

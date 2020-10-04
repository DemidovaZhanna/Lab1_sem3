#include <ctime>
#include "interface.h"
#include "ArraySequence.h"
#include "time_measurement.h"
#include "sort.h"

typedef unsigned long long ull;
void interface_sort() {

	int choose;
	cout << "Choose a type of sequence: Integer / Real / String" << endl;
	string cmd;
	cin >> cmd;

	while ( cmd != "Integer" && cmd != "Real" && cmd != "String") {
		cout << "Invalid keyword. Try again: ";
		cin >> cmd;
	}

	int data = -1;
	while (data < 0) {
		cout << "Write down size of sequence: ";
		cin >> data;
	}
	cout << endl;
	string *a = new string[(ull)data];
	int *ress = new int[(ull)data];
	double *doub = new double[(ull)data];

	cout << "Enter '1' to fill in the sequence manually" << endl;
	cout << "Enter '2' to fill in the sequence with random values ";
	cin >> choose;

	switch(choose) {
	case 1:
		cout << "Enter the values of the sequence: ";
		for (int i = 0; i < data; i++) {
			cin >> a[i];

			while(1)
				try {
					if (cmd == "Integer")
						ress[i] = stoi(a[i]);
					if (cmd == "Real")
						doub[i] = stod(a[i]);
					break;
				}
				catch (std::invalid_argument&) {
					cout << "The value was entered incorrectly. Enter this value again" << endl;
					cin >> a[i];
				}
		}
		break;

	case 2:
		srand((unsigned int)time(nullptr));
		for (int i = 0; i < data; i++)
			a[i] = (char)rand();
		for (int i = 0; i < data; i++)
			cout << a[i];
		break;
	default:
		break;
	}
	cout << endl;

	auto Int = new ArraySequence<int>(ress, data);
//	auto Real = new ArraySequence<double>(doub, data);
//	auto Str = new ArraySequence<string>(a, data);

	cout << "Select the sorting type: (click the number of the selected sort) " << endl;
	cout << "1. Shellsort" << endl << "2. Heapsort" << endl;
	cout << "3. Quick sort" << endl << "4. The insertion sort" << endl;
	cin >> choose;

	Sort<int, bool> sort;

	switch (choose) {
	case 1:
		auto Int_sort = sort.shell_sort(Int);
		cout << "A sorted sequence: ";

		for (int i = 0; i < Int_sort->getLength(); i++)
			cout << Int_sort->Get(i) << " ";

		long long time = time_measurement(sort.shell_sort, Int);
		cout << "Elapsed time: " << time;
	}
}

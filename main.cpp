#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <algorithm>

#include "sorters.h"

using namespace std;

typedef void (*sorterFunc)(std::vector<int>&);

static bool isSorted(const vector<int> &arr)
{
	for (size_t i = 1; i  < arr.size(); i++)
		if (arr[i - 1] > arr[i])
			return false;
	return true;
}

static void printVector(const vector<int> &arr)
{
	for (size_t i = 0; i < arr.size(); i++)
		cout << arr[i] << endl;
}

static int testSorter(sorterFunc f, int n, double &runningTime, const std::vector<int> &src)
{
	vector<int> arr(src);

	/* now sort the array */
	clock_t start = clock();
	if (f)
		f(arr);
	else
		std::sort(arr.begin(), arr.end());
	clock_t end = clock();
	runningTime = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;

	/* check if result is correct */
	if (!isSorted(arr))
		return -1;

	if (n < 100)
		printVector(arr);

	return 0;
}
#include "classifiers.h"
int main()
{
	srand(0);
	/* first create a random array for sorting */
	int testLen = 5000;
	std::vector<int> arr;
	for (int i = 0; i < testLen; i++)
		arr.push_back(rand() % COUNTING_SORT_MAX);
	//BuggyClassifier c;
	//arr = c.classify(testLen);
	double runningTime;
	cout << "Testing implementaions" << endl;
	cout << "Insertion sort: " << (testSorter(&Sorters::InsertionSort, testLen, runningTime, arr) ? "failed" : "passed") << endl;
	cout << "took (msec): " << runningTime << endl;
	cout << "Selection sort: " << (testSorter(&Sorters::SelectionSort, testLen, runningTime, arr) ? "failed" : "passed") << endl;
	cout << "took (msec): " << runningTime << endl;
	cout << "Merge sort: " << (testSorter(&Sorters::MergeSort, testLen, runningTime, arr) ? "failed" : "passed") << endl;
	cout << "took (msec): " << runningTime << endl;
	cout << "Quick sort: " << (testSorter(&Sorters::QuickSort, testLen, runningTime, arr) ? "failed" : "passed") << endl;
	cout << "took (msec): " << runningTime << endl;
	cout << "Counting sort: " << (testSorter(&Sorters::CountingSort, testLen, runningTime, arr) ? "failed" : "passed") << endl;
	cout << "took (msec): " << runningTime << endl;
	cout << "STL sorter: " << (testSorter(NULL, testLen, runningTime, arr) ? "failed" : "passed") << endl;
	cout << "took (msec): " << runningTime << endl;
	return 0;
}

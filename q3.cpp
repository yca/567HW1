#include "sorters.h"
#include "classifiers.h"

#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

typedef void (*sorterFunc)(std::vector<int>&);

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

static void printVector(const vector<int> &arr)
{
	for (size_t i = 0; i < arr.size(); i++)
		cout << arr[i] << endl;
}

static void printVector(const vector<double> &arr)
{
	for (size_t i = 0; i < arr.size(); i++)
		cout << arr[i] << endl;
}

static double testSorter(sorterFunc f, const std::vector<int> &src)
{
	vector<int> arr(src);

	/* now sort the array */
	clock_t start = clock();
	f(arr);
	clock_t end = clock();
	return (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
}

static std::vector<double> evalSorters(const std::vector<int> &data)
{
	std::vector<double> times;
	times.push_back(testSorter(Sorters::InsertionSort, data));
	times.push_back(testSorter(Sorters::SelectionSort, data));
	times.push_back(testSorter(Sorters::MergeSort, data));
	times.push_back(testSorter(Sorters::QuickSort, data));
	times.push_back(testSorter(Sorters::CountingSort, data));
	return times;
}

static std::vector<double> evalClassifier(BaseClassifier *c, int size)
{
	std::vector<double> times = evalSorters(c->classify(size));
	printVector(times);
	return times;
}

static void printResults(const std::vector<std::vector<double> > &comps, int p1, int p2, const char *sorter, const char *cl)
{
	cout << sorter << " - " << cl << endl;
	for (size_t i = 0; i < comps.size(); i += 3)
		cout << comps[i + p2][p1] << endl;
}

int main()
{
	/* for the sake of reproducibility we init random generator with a known seed */
	srand(0);

	size_t sizes[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000 };
	std::vector<std::vector<double> > comps;
	for (size_t i = 0; i < ARRAY_SIZE(sizes); i++) {
		cout << "---------------- random --------------------" << endl;
		RandomClassifier c1;
		comps.push_back(evalClassifier(&c1, sizes[i]));

		cout << "---------------- lazy --------------------" << endl;
		LazyClassifier c2;
		comps.push_back(evalClassifier(&c2, sizes[i]));

		cout << "---------------- buggy --------------------" << endl;
		BuggyClassifier c3;
		comps.push_back(evalClassifier(&c3, sizes[i]));

		cout << "finished " << i << " out of " << ARRAY_SIZE(sizes) << endl;
	}


	printResults(comps, 0, 0, "Insertion sort", "Random");
	printResults(comps, 0, 1, "Insertion sort", "Lazy");
	printResults(comps, 0, 2, "Insertion sort", "Buggy");
	printResults(comps, 1, 0, "Selection sort", "Random");
	printResults(comps, 1, 1, "Selection sort", "Lazy");
	printResults(comps, 1, 2, "Selection sort", "Buggy");
	printResults(comps, 2, 0, "Merge sort", "Random");
	printResults(comps, 2, 1, "Merge sort", "Lazy");
	printResults(comps, 2, 2, "Merge sort", "Buggy");
	printResults(comps, 3, 0, "Quick sort", "Random");
	printResults(comps, 3, 1, "Quick sort", "Lazy");
	printResults(comps, 3, 2, "Quick sort", "Buggy");
	printResults(comps, 4, 0, "Counting sort", "Random");
	printResults(comps, 4, 1, "Counting sort", "Lazy");
	printResults(comps, 4, 2, "Counting sort", "Buggy");

	return 0;
}

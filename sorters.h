#ifndef SORTERS_H
#define SORTERS_H

#include <vector>

#define COUNTING_SORT_MAX		1000

class Sorters
{
public:
	Sorters();

	static void InsertionSort(std::vector<int> &arr);
	static void SelectionSort(std::vector<int> &arr);
	static void MergeSort(std::vector<int> &arr);
	static void QuickSort(std::vector<int> &arr);
	static void CountingSort(std::vector<int> &arr);

protected:
	/* helper functions */
	static void CountingSort(std::vector<int> &arr, int max);
	static void QuickSort(std::vector<int> &arr, int first, int last);
	static std::vector<int> mergeVectors(const std::vector<int> &left, const std::vector<int> &right);
	static int partitionVector(std::vector<int> &arr, int first, int last);
};

#endif // SORTERS_H

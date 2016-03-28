#include "sorters.h"

#include <string.h>
#include <iostream>

using namespace std;

Sorters::Sorters()
{
}

void Sorters::InsertionSort(std::vector<int> &arr)
{
	for (size_t i = 0; i < arr.size(); i++) {
		int j = i;
		while (j > 0 && arr[j] < arr[j - 1]) {
			std::swap(arr[j], arr[j - 1]);
			j--;
		}
	}
}

void Sorters::SelectionSort(std::vector<int> &arr)
{
	for (size_t i = 0; i < arr.size() - 1; i++) {
		int k = i;
		for (size_t j = i + 1; j < arr.size(); j++) {
			if (arr[j] < arr[k])
				k = j;
		}
		std::swap(arr[k], arr[i]);
	}
}

void Sorters::MergeSort(std::vector<int> &arr)
{
	if(arr.size() == 1)
		return;

	/* find the middle element */
	std::vector<int>::iterator middle = arr.begin() + (arr.size() / 2);

	/* split left & right */
	vector<int> left(arr.begin(), middle);
	vector<int> right(middle, arr.end());

	/* sort vectors */
	MergeSort(left);
	MergeSort(right);

	/* now merge the results */
	if (1) {
		/* Normally we would use stl resource like this, but we need to implement merger as well in this hw */
		arr.clear();
		arr.reserve(left.size() + right.size());
		arr.insert(arr.end(), arr.begin(), arr.end());
		arr.insert(arr.end(), arr.begin(), arr.end());
	} else {
		/* this is our implementation of merging, but this is a little bit slower than native stl implementation */
		arr = mergeVectors(left, right);
	}
}

void Sorters::QuickSort(std::vector<int> &arr)
{
	QuickSort(arr, 0, arr.size());
}

void Sorters::CountingSort(std::vector<int> &arr)
{
	int max = COUNTING_SORT_MAX;
	int *counts = new int[max];
	memset(counts, 0, max * sizeof(int));

	for (size_t i = 0; i < arr.size(); i++)
		counts[arr[i]]++;

	for (int i = 1; i < max; i++)
		counts[i] += counts[i - 1];

	vector<int> sorted(arr.size(), 0);
	for (int i = arr.size() - 1; i >= 0; i--)
		sorted[--counts[arr[i]]] = arr[i];
	arr = sorted;

	delete counts;
}

void Sorters::QuickSort(std::vector<int> &arr, int first, int last)
{
	if (first < last) {
		int pivot = partitionVector(arr, first, last);
		QuickSort(arr, first, pivot);
		QuickSort(arr, pivot + 1, last);
	}
}

std::vector<int> Sorters::mergeVectors(const std::vector<int> &left, const std::vector<int> &right)
{
	vector<int> result;
	unsigned int leftPos = 0, rightPos = 0;
	while(leftPos < left.size() && rightPos < right.size()) {
		if(left[leftPos] < right[rightPos]) {
			result.push_back(left[leftPos]);
			leftPos++;
		} else {
			result.push_back(right[rightPos]);
			rightPos++;
		}
	}

	while(leftPos < left.size()) {
		result.push_back(left[leftPos]);
		leftPos++;
	}

	while(rightPos < right.size()) {
		result.push_back(right[rightPos]);
		rightPos++;
	}

	return result;
}

int Sorters::partitionVector(std::vector<int> &arr, int first, int last)
{
	int x = arr[first];
	int i = first;

	for (int j = first + 1; j < last; j++) {
		if(arr[j] <= x) {
			i++;
			swap(arr[i], arr[j]);
		}
	}

	swap(arr[i], arr[first]);
	return i;
}

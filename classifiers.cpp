#include "classifiers.h"
#include "sorters.h"

#include <stdlib.h>

std::vector<int> RandomClassifier::classify(int n)
{
	std::vector<int> arr;
	for (int i = 0; i < n; i++)
		arr.push_back(rand() % COUNTING_SORT_MAX);
	return arr;
}


std::vector<int> BuggyClassifier::classify(int n)
{
	std::vector<int> arr;
	for (int i = 0; i < n; i++)
		arr.push_back(0);
	return arr;
}


std::vector<int> LazyClassifier::classify(int n)
{
	std::vector<int> arr;
	int same = n / COUNTING_SORT_MAX;
	if (!same)
		same = 1;
	for (int i = 0; i < COUNTING_SORT_MAX; i++) {
		for (int j = 0; j < same; j++) {
			arr.push_back(i);
			if (arr.size() == (size_t)n)
				break;
		}
		if (arr.size() == (size_t)n)
			break;
	}
	for (int i = arr.size(); i < n; i++)
		arr.push_back(arr[arr.size() - 1]);
	return arr;
}


BaseClassifier::BaseClassifier()
{

}

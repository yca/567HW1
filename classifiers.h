#ifndef CLASSIFIERS_H
#define CLASSIFIERS_H

#include <vector>

class BaseClassifier
{
public:
	BaseClassifier();

	virtual std::vector<int> classify(int n) = 0;
};

class RandomClassifier : public BaseClassifier
{
public:
	std::vector<int> classify(int n);
};

class BuggyClassifier : public BaseClassifier
{
public:
	std::vector<int> classify(int n);
};

class LazyClassifier : public BaseClassifier
{
public:
	std::vector<int> classify(int n);
};

#endif // CLASSIFIERS_H

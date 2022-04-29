#include <vector>
#include <exception>
using namespace std;

#pragma once

enum class Iterators {
	STEP,
	VALUE,
	PREDICATE
};

class List
{
public:
	vector <int> vec;
	size_t top = 0;
public:
	friend class ListIterator;

	List(size_t aSize) {
		vec.resize(aSize);
	}

	virtual ~List() {
	}

	bool append(int a) {
		if (top == vec.size())
			return false;
		vec[top++] = a;
		return true;
	}

	bool remove() {
		if (top == 0)
			return false;
		--top;
		return true;
	}

	ListIterator* createIterator(Iterators its, const int aStep) const;

};

class ListIterator {
protected:
	friend class List;
	const List* pList;
	size_t current;
public:
	ListIterator(const List* aPList) : pList(aPList) {
	}
	virtual bool first() = 0;
	virtual bool next() = 0;
	virtual int currentItem() = 0;
};

class ListIteratorStep : public ListIterator
{
private:
	int step;
public:
	friend class List;
	ListIteratorStep(const List* aPList, int aStep = 1) : ListIterator(aPList) {
		step = aStep - 1;
	}

	bool first() override {
		current = pList->top - 1;
		for (auto i = 0; current != -1 && i < step; i++)
			current = current--;
		return current != -1;
	}

	bool next() override
	{
		current = current--;
		for (auto i = 0; current != -1 && i < step; i++)
			current = current--;
		return current != -1;
	}

	int currentItem() override
	{
		if (current == -1)
			throw exception("Can't obtain currentItem!");
		return pList->vec[current];
	}
};

////class ListIteratorPredicate : public ListIterator
////{
////private:
////	void* predicate;
////public:
////	ListIteratorPredicate(const List* aPList, void* aPredicate) : ListIterator(aPList) {
////		predicate = aPredicate;
////	}
////
////	bool first() override {
////		return true;
////	}
////	bool next() override
////	{
////		return true;
////	}
////	int currentItem() override
////	{
////		if (current == -1)
////			throw runtime_error("Can't obtain currentItem!");
////		return pList->vec[current];
////	}
////};

class ListIteratorValue : public ListIterator
{
private:
	int value;
public:
	friend class List;
	ListIteratorValue(const List* aPList, int aValue) : ListIterator(aPList) {
		value = aValue;
	}

	bool first() override {
		current = pList->top - 1;
		while (current != -1 && pList->vec[current] != value)
			current = current--;
		return current != -1;
	}
	bool next() override
	{
		current = current--;
		while (current != -1 && pList->vec[current] != value)
			current = current--;
		return current != -1;
	}
	int currentItem() override
	{
		if (current == -1)
			throw exception("Can't obtain currentItem!");
		return pList->vec[current];
	}
};

ListIterator* List::createIterator(Iterators its, const int aStep) const {
	if (its == Iterators::STEP)
		return new ListIteratorStep(this, aStep);
	if (its == Iterators::VALUE)
		return new ListIteratorValue(this, aStep);
	return nullptr;
}
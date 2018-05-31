#include <iostream>
#include <string>
#include <forward_list>
#include "sortvec.h"
#include "searchvec.h"
#include "list.h"
#include "util.h"

using namespace std;
using namespace tdc;

void showTest(const std::string& testName)
{
	static bool firstShow = true;
	std::string line(5 + testName.length(), '-');

	if (firstShow)
		firstShow = false;
	else
		cout << endl;
	cout << "test " << testName << endl;
	cout << line << endl;
}

template <class F, class T>
void testVectorSort(const std::string& funcName, F fn, std::vector<T> ary, const std::vector<T>& expected)
{
	cout << "test " << funcName << ": " << ary;
	fn(ary);
	if (ary == expected)
		cout << ", SUCCESS" << endl;
	else
		cout << ", FAILED: return " << ary << ", expected: " << expected << endl;
}

void testSorting()
{
	showTest("Sorting");

	vector<char> unsortedChars	= { 'a','i','r','p','l','a','n','e','s' };
	vector<char> sortedChars	= { 'a','a','e','i','l','n','p','r','s' };

	testVectorSort("bubbleSort<char>", bubbleSort<char>, unsortedChars, sortedChars);
	testVectorSort("selectionSort<char>", selectionSort<char>, unsortedChars, sortedChars);
	testVectorSort("insertionSort<char>", insertionSort<char>, unsortedChars, sortedChars);

	vector<int> unheaped = {3,1,4,1,5,9};
	vector<int> heaped = {9,4,5,1,1,3};
	testVectorSort("makeHeap<int>", makeHeap<int>, unheaped, heaped);
	cout << "test popHeap: before " << heaped;
	cout << ", popped " << popHeap(heaped) << ", after " << heaped << endl;

	vector<int> unsortedInts	= { 3,5,8,1,2,9,4,7,6 };
	vector<int> sortedInts		= { 1,2,3,4,5,6,7,8,9 };
	vector<int> sortedIntsR		= { 9,8,7,6,5,4,3,2,1 };
	testVectorSort("heapSort<int>", heapSort<int>, unsortedInts, sortedInts);
	testVectorSort("quickSort<int>", quickSort<int>, unsortedInts, sortedInts);
	testVectorSort("mergeSort<int,greater<int>>", mergeSort<int, greater<int>>, unsortedInts, sortedIntsR);
}

template <class F, class T>
void testVectorSearch(const std::string& funcName, F fn, std::vector<T> ary, const T& target, int expected)
{
	cout << "test " << funcName << ": " << ary;
	int r = fn(ary, target);
	if (r == expected)
		cout << ", SUCCESS" << endl;
	else
		cout << ", FAILED: return " << r << ", expected: " << expected << endl;
}

void testSearching()
{
	showTest("Searching");

	vector<int> sortedInts		= { 0,2,4,6,8,10,12,14,16 };
	vector<int> sortedIntsR		= { 16,14,12,10,8,6,4,2,0 };
	testVectorSearch("linearSearch<int>", linearSearch<int>, sortedInts, 12, 6);
	testVectorSearch("linearSearch<int>", linearSearch<int>, sortedInts, 13, -1);
	testVectorSearch("linearSearch<int>", linearSearch<int>, sortedInts, -2, -1);

	testVectorSearch("binarySearch<int>", binarySearch<int>, sortedInts, 12, 6);
	testVectorSearch("binarySearch<int>", binarySearch<int>, sortedInts, 13, -1);
	testVectorSearch("binarySearch<int>", binarySearch<int>, sortedInts, -2, -1);
	testVectorSearch("binarySearch<int,greater<int>>", binarySearch<int, greater<int>>, sortedIntsR, 12, 2);
}

template <class T>
void testListEqual(const std::string& funcName, List<T> list1, const List<T>& list2, bool expected)
{
	cout << "test " << funcName << ": " << list1 << (expected ? " == " : " != ") << list2;
	bool r = list1.equal(list2);
	if (r == expected)
		cout << ", SUCCESS" << endl;
	else
		cout << ", FAILED: return " << r << ", expected: " << expected << endl;
}

void testList()
{
	showTest("List");

	List<int> l1;
	List<int> l2 = { 1,3,5 };

	l1.push_back(1);
	l1.push_back(3);
	l1.push_back(5);
	testListEqual("1 list<int>::push_back", l1, l2, true);

	l1.push_back(7);
	testListEqual("2 list<int>::push_back", l1, l2, false);

	l1.pop_back();
	testListEqual("3 list<int>::pop_back", l1, l2, true);

	l1.pop_front();
	testListEqual("4 list<int>::pop_front", l1, l2, false);

	l1.push_front(1);
	testListEqual("5 list<int>::push_front", l1, l2, true);

	List<int>::iterator it1 = l1.begin();
	it1 = l1.insert(it1, 0);
	testListEqual("6 list<int>::insert into head", l1, l2, false);

	it1 = l1.insert(l1.begin() + 2, 2);
	testListEqual("7 list<int>::insert begin() + 2", l1, l2, false);

	cout << "test 8 list<int> iterator value: " << *it1 << endl;

	it1 = l1.erase(it1);
	it1 = l1.erase(l1.begin());
	testListEqual("9 list<int>::erase", l1, l2, true);

	List<int> l3 = l1;
	testListEqual("10 list<int>::copy", l1, l3, true);

	List<int> l4 = { -1 };
	l4 = l3;
	testListEqual("11 list<int>::assign", l3, l4, true);

	l4.clear();
	l1.clear();
	testListEqual("12 list<int>::clear", l1, l4, true);

	std::swap(l1, l3);
	testListEqual("13 list<int>::swap", l1, l2, true);
	testListEqual("14 list<int>::swap", l3, l4, true);
}

int main()
{
	testSorting();
	testSearching();
	testList();
	cout << "\nAll tests done!" << endl;
	cin.get();
}
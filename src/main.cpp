#include <iostream>
#include <string>
#include "sortvec.h"
#include "util.h"

using namespace std;

template <class F, class T>
void testVectorFunc(const std::string& funcName, F fn, std::vector<T> ary, std::vector<T> expected)
{
	cout << "test " << funcName << ": " << ary;
	fn(ary);
	if (vectorIsEqual(ary, expected))
		cout << ", SUCCESS" << endl;
	else
		cout << ", FAILED: " << ary << endl;
}

void testSorting()
{
	vector<char> unsortedChars	= {'a','i','r','p','l','a','n','e','s'};
	vector<char> sortedChars	= {'a','a','e','i','l','n','p','r','s'};
	testVectorFunc("bubbleSort<char>", bubbleSort<char>, unsortedChars, sortedChars);
	testVectorFunc("selectionSort<char>", selectionSort<char>, unsortedChars, sortedChars);
	testVectorFunc("insertionSort<char>", insertionSort<char>, unsortedChars, sortedChars);

	vector<int> unheaped = {3,1,4,1,5,9};
	vector<int> heaped = {9,4,5,1,1,3};
	testVectorFunc("makeHeap<int>", makeHeap<int>, unheaped, heaped);
	cout << "test popHeap: before " << heaped;
	cout << ", popped " << popHeap(heaped) << ", after " << heaped << endl;

	vector<int> unsortedInts	= {3,5,8,1,2,9,4,7,6};
	vector<int> sortedInts		= {1,2,3,4,5,6,7,8,9};
	vector<int> sortedIntsR		= {9,8,7,6,5,4,3,2,1};
	testVectorFunc("heapSort<int>", heapSort<int>, unsortedInts, sortedInts);
	testVectorFunc("quickSort<int>", quickSort<int>, unsortedInts, sortedInts);
	testVectorFunc("mergeSort<int,greater<int>>", mergeSort<int, greater<int>>, unsortedInts, sortedIntsR);
}

int main()
{
	testSorting();
}
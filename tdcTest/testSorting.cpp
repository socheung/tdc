#include "pch.h"
#include <vector>
#include "sortvec.h"

using namespace std;
using namespace tdc;

TEST(TestSorting, bubbleSort) {
	vector<char> testChars = { 'a','i','r','p','l','a','n','e','s' };
	vector<char> expected = { 'a','a','e','i','l','n','p','r','s' };

	bubbleSort(testChars);
	EXPECT_EQ(testChars, expected);
}

TEST(TestSorting, selectionSort) {
	vector<char> testChars = { 'a','i','r','p','l','a','n','e','s' };
	vector<char> expected = { 'a','a','e','i','l','n','p','r','s' };

	selectionSort(testChars);
	EXPECT_EQ(testChars, expected);
}

TEST(TestSorting, insertionSort) {
	vector<char> testChars = { 'a','i','r','p','l','a','n','e','s' };
	vector<char> expected = { 'a','a','e','i','l','n','p','r','s' };

	insertionSort(testChars);
	EXPECT_EQ(testChars, expected);
}

TEST(TestSorting, makeHeap) {
	vector<int> unheaped = { 3,1,4,1,5,9 };
	vector<int> heaped = { 9,4,5,1,1,3 };

	makeHeap(unheaped);
	EXPECT_EQ(unheaped, heaped);
}

TEST(TestSorting, heapSort) {
	vector<int> unsortedInts	= { 3,5,8,1,2,9,4,7,6 };
	vector<int> sortedInts		= { 1,2,3,4,5,6,7,8,9 };

	heapSort(unsortedInts);
	EXPECT_EQ(unsortedInts, sortedInts);
}

TEST(TestSorting, quickSort) {
	vector<int> unsortedInts	= { 3,5,8,1,2,9,4,7,6 };
	vector<int> sortedInts		= { 1,2,3,4,5,6,7,8,9 };

	quickSort(unsortedInts);
	EXPECT_EQ(unsortedInts, sortedInts);
}

TEST(TestSorting, mergeSort) {
	vector<int> unsortedInts	= { 3,5,8,1,2,9,4,7,6 };
	vector<int> sortedIntsR		= { 9,8,7,6,5,4,3,2,1 };

	mergeSort<int, greater<int>>(unsortedInts);
	EXPECT_EQ(unsortedInts, sortedIntsR);
}

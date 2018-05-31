#include "pch.h"
#include <vector>
#include "searchvec.h"

using namespace std;
using namespace tdc;

TEST(TestSearching, linearSearch) {
	vector<int> sortedInts		= { 0,2,4,6,8,10,12,14,16 };
	vector<int> sortedIntsR		= { 16,14,12,10,8,6,4,2,0 };

	EXPECT_EQ(linearSearch(sortedInts, 12), 6);
	EXPECT_EQ(linearSearch(sortedInts, 13), -1);
	EXPECT_EQ(linearSearch(sortedInts, -2), -1);
}

TEST(TestSearching, binarySearch) {
	vector<int> sortedInts		= { 0,2,4,6,8,10,12,14,16 };
	vector<int> sortedIntsR		= { 16,14,12,10,8,6,4,2,0 };

	EXPECT_EQ(binarySearch(sortedInts, 12), 6);
	EXPECT_EQ(binarySearch(sortedInts, 13), -1);
	EXPECT_EQ(binarySearch(sortedInts, -2), -1);
	EXPECT_EQ((binarySearch<int, greater<int>>(sortedIntsR, 12)), 2);
}

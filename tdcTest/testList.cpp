#include "pch.h"
#include <vector>
#include "list.h"

using namespace std;
using namespace tdc;

List<int> generateList()
{
	List<int> newList;

	newList.push_back(1);
	newList.push_back(3);
	newList.push_back(5);
	return newList;
}

TEST(TestList, constructor) {
	List<int> l1;						// default constructor
	List<int> l2{ 1,3,5 };				// initializer list constructor
	List<int> l3 = l2;					// copy constructor
	List<int> l4 = move(generateList());	// move constructor
	List<int> l5;

	l1 = l2;							// copy assignment
	l5 = move(generateList());			// move assignment
	EXPECT_EQ(l2, l3);
	EXPECT_EQ(l2, l4);
	EXPECT_EQ(l2, l5);
}

TEST(TestList, push_pop) {
	List<int> l1;
	List<int> l2{ 1,3,5 };

	l1.push_back(1);
	l1.push_back(3);
	l1.push_back(5);
	EXPECT_EQ(l1, l2);
	l1.push_back(7);
	EXPECT_NE(l1, l2);
	l1.pop_back();
	EXPECT_EQ(l1, l2);
	l1.pop_front();
	EXPECT_NE(l1, l2);
	l1.push_front(1);
	EXPECT_EQ(l1, l2);
}

TEST(TestList, insert_erase) {
	List<int> l1{ 1,3,5 };
	List<int> l2{ 1,3,5 };

	List<int>::iterator it1 = l1.begin();
	it1 = l1.insert(it1, 0);
	EXPECT_NE(l1, l2);
	it1 = l1.insert(l1.begin() + 2, 2);
	EXPECT_NE(l1, l2);
	it1 = l1.erase(it1);
	it1 = l1.erase(l1.begin());
	EXPECT_EQ(l1, l2);
}

TEST(TestList, copy_assign_clear) {
	List<int> l1{ 1,3,5 };
	List<int> l2 = l1;
	List<int> l3 = { -1 };
	EXPECT_EQ(l1, l2);
	l3 = l2;
	EXPECT_EQ(l2, l3);
	l2.clear();
	EXPECT_NE(l2, l3);
	l3.clear();
	EXPECT_EQ(l2, l3);
}

TEST(TestList, swap) {
	List<int> l1{ 1,3,5 };
	List<int> l2{ 1,3,5 };
	List<int> l3;

	l3.swap(l2);
	EXPECT_EQ(l1, l3);
	EXPECT_NE(l1, l2);
	EXPECT_TRUE(l2.empty());
}
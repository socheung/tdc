#pragma once

#ifndef TDC_SORTVEC_H
#define TDC_SORTVEC_H

#include <vector>
#include <utility>

// tdc namespace
namespace tdc {

template <class T, class C = std::less<T>>
void bubbleSort(std::vector<T>& ary)
{
	bool swapped = true;	// optimize to stop when no swapping
	for (std::size_t i = 0; i < ary.size() - 1 && swapped; i++)
	{
		swapped = false;
		for (std::size_t j = ary.size() - 1; j > i; j--)
		{
			if (C()(ary[j], ary[j - 1]))
			{
				std::swap(ary[j], ary[j - 1]);
				swapped = true;
			}
		}
	}
}

template <class T, class C = std::less<T>>
void selectionSort(std::vector<T>& ary)
{
	for (std::size_t i = 0; i < ary.size() - 1; i++)
	{
		for (std::size_t j = i; j < ary.size(); j++)
		{
			if (C()(ary[j], ary[i]))
				std::swap(ary[j], ary[i]);
		}
	}
}

template <class T, class C = std::less<T>>
void insertionSort(std::vector<T>& ary)
{
	for (std::size_t i = 1; i < ary.size(); i++)
		// stop insertion when right is not less than left
		for (std::size_t j = i; j > 0 && C()(ary[j], ary[j - 1]); j--)
			std::swap(ary[j], ary[j - 1]);
}

template <class T, class C = std::less<T>>
void makeHeap(std::vector<T>& ary)
{
	for (std::size_t i = 1; i < ary.size(); i++)
	{
		// shift up to compare with parent
		std::size_t j = i;
		while (j)
		{
			std::size_t p = (j - 1) / 2;	// parent heap
			if (C()(ary[p], ary[j]))		// swap when greater than parent heap
				std::swap(ary[p], ary[j]);
			j = p;
		}
	}
}

template <class T, class C = std::less<T>>
T popHeap(std::vector<T>& ary)
{
	if (ary.empty())
		return (T) 0;

	// pop largest top heap and swap with last child
	T popValue = ary.front();
	std::swap(ary.front(), ary.back());
	// shift down among children
	std::size_t i = ary.size() - 1;
	std::size_t p = 0;		// parent
	while (i > p + 1)		// last child is not left child
	{
		std::size_t lc = p + 1;	// left child
		std::size_t rc = p + 2;	// right child
		std::size_t gc = (i > rc && C()(ary[lc], ary[rc])) ? rc : lc;	// greater child
		// swap with parent when child is greater
		if (C()(ary[p], ary[gc]))
		{
			std::swap(ary[p], ary[gc]);
			p = gc;		// set next parent to greater child
		}
		else
			break;		// stop when all children are smaller than parent
	}
	ary.pop_back();

	return popValue;
}

template <class T, class C = std::less<T>>
void heapSort(std::vector<T>& ary)
{
	makeHeap<T,C>(ary);
	for (std::size_t i = ary.size() - 1; i > 0; i--)
	{
		// pop largest top heap and swap with last child
		std::swap(ary[0], ary[i]);
		// shift down among children
		std::size_t p = 0;		// parent
		while (i > p + 1)		// last child is not left child
		{
			std::size_t lc = p + 1;	// left child
			std::size_t rc = p + 2;	// right child
			std::size_t gc = (i > rc && C()(ary[lc], ary[rc])) ? rc : lc;	// greater child
			// swap with parent when child is greater
			if (C()(ary[p], ary[gc]))
			{
				std::swap(ary[p], ary[gc]);
				p = gc;		// set next parent to greater child
			}
			else
				break;		// stop when all children are smaller than parent
		}
	}
}

template <class T, class C>
void quickSortSplit(std::vector<T>& ary, std::size_t indexLeft, std::size_t indexRight)
{
	//std::cout << "quickSortSplit: " << indexLeft << ", " << indexRight << std::endl;
	std::size_t pivot = indexLeft;
	std::size_t left = indexLeft + 1;
	std::size_t right = indexRight;
	while (left < right)
	{
		// find leftmost value greater than pivot
		while (C()(ary[left], ary[pivot]) && left < indexRight)
			left++;
		// find rightmost value lesser than pivot
		while (C()(ary[pivot], ary[right]) && right > indexLeft)
			right--;
		// swap left greater with right lesser
		if (left < right)
			std::swap(ary[left], ary[right]);
	}
	// swap with pivot when left and right index equal
	if (left == right)
		std::swap(ary[left], ary[pivot]);
	// quick sort leftmost part if count is greater than 1, skip pivot point
	if (left - indexLeft > 2)
		quickSortSplit<T,C>(ary, indexLeft, left - 1);
	// quick sort rightmost part if count is greater than 1, skip pivot point
	if (indexRight - right > 2)
		quickSortSplit<T,C>(ary, right + 1, indexRight);
}

template <class T, class C = std::less<T>>
void quickSort(std::vector<T>& ary)
{
	if (ary.size() < 2) return;
	quickSortSplit<T,C>(ary, 0, ary.size() - 1);
}

template <class T, class C>
void mergeSortMerge(std::vector<T>& ary, std::size_t left, std::size_t right, std::size_t mid)
{
	std::vector<T> result(right - left + 1);	// reserve size for result 

	std::size_t i = 0;			// result index
	std::size_t li = left;		// left index
	std::size_t ri = mid;		// right index
	while (li < mid && ri <= right)
	{
		// merge by selective lesser value in leftmost or rightmost
		if (C()(ary[li], ary[ri]))
			result[i++] = ary[li++];
		else
			result[i++] = ary[ri++];
	}
	// merge from remained leftmost
	while (li < mid)
		result[i++] = ary[li++];
	// merge from remained rightmost
	while (ri <= right)
		result[i++] = ary[ri++];
	// copy sorted result back to original vector
	i = 0;
	while (left <= right)
		ary[left++] = result[i++];
}

template <class T, class C>
void mergeSortSplit(std::vector<T>& ary, std::size_t left, std::size_t right)
{
	// split list into two lists
	std::size_t mid = (left + right + 1) / 2;
	// sort leftmost
	if (mid - left > 1)
		mergeSortSplit<T,C>(ary, left, mid - 1);
	// sort rightmost
	if (right - mid > 0)
		mergeSortSplit<T,C>(ary, mid, right);
	// merge sorted leftmost and rightmost
	mergeSortMerge<T,C>(ary, left, right, mid);
}

template <class T, class C = std::less<T>>
void mergeSort(std::vector<T>& ary)
{
	if (ary.size() < 2) return;
	mergeSortSplit<T,C>(ary, 0, ary.size() - 1);
}

};	// end of tdc

#endif // TDC_SORTVEC_H
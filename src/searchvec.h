#pragma once

#ifndef TDC_SEARCHVEC_H
#define TDC_SEARCHVEC_H

#include <vector>

// tdc namespace
namespace tdc {

template <class T>
int linearSearch(std::vector<T>& ary, const T& target)
{
	for (std::size_t i = 0; i < ary.size(); i++)
	{
		if (ary[i] == target)
			return i;
	}
	return -1;
}

template <class T, class C = std::less<T>>
int binarySearch(std::vector<T>& ary, const T& target)
{
	int left = 0;
	int right = (int) ary.size() - 1;
	while (left <= right)
	{
		int i = (left + right) / 2;
		const T& v = ary[i];
		if (v == target)
			return i;
		else if (C()(v, target))
			left = i + 1;
		else
			right = i - 1;
	}
	return -1;
}

};	// end of tdc

#endif // TDC_SEARCHVEC_H
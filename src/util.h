#pragma once

#ifndef TDC_UTIL_H
#define TDC_UTIL_H

#include <iostream>
#include <vector>
#include "list.h"

namespace tdc {

// show output of vector
template<class T>
std::ostream& operator<< (std::ostream& os, const std::vector<T>& v)
{
	os << "[";
	for (std::size_t i = 0; i < v.size(); i++)
		os << (i ? "," : "") << v[i];
	os << "]";
	return os;
}

// show output of list
template<class T>
std::ostream& operator<< (std::ostream& os, const tdc::List<T>& list)
{
	int i = 0;
	os << "L" << list.size() << "[";
	for (auto v : list)
		os << (i++ ? "," : "") << v;
	os << "]";
	return os;
}

};	// end of tdc

#endif // TDC_UTIL_H
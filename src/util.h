#pragma once

#include <iostream>
#include <vector>

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

// test vector value equal
template<class T>
bool vectorIsEqual(const std::vector<T>& a, const std::vector<T>& b)
{
	if (a.size() != b.size())
		return false;
	for (size_t i = 0; i < a.size(); i++)
		if (a[i] != b[i])
			return false;
	return true;
}
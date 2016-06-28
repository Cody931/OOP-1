#pragma once

#include <vector>
#include <algorithm>


template < typename T >
bool FindMax(std::vector<T> const& arr, T& maxValue)
{
	if (arr.empty())
	{
		return false;
	}
	maxValue = *std::max_element(begin(arr), end(arr));
	return true;
}

template <>
bool FindMax <const char*> (std::vector<const char*> const& arr, const char*& maxValue)
{
	if (arr.empty())
	{
		return false;
	}
	maxValue = *std::max_element(begin(arr), end(arr), [](auto last, auto next)
	{
		return (strcmp(last, next) > 0 ? false : true);
	});
	return true;
}

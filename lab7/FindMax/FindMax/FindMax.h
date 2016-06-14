#pragma once

#include <vector>
#include <algorithm>


template <typename T>
bool FindMax(std::vector<T> const& arr, T& maxValue)
{
	if (arr.empty())
	{
		return false;
	}
	std::for_each(begin(arr), end(arr), [&](T it) {
		maxValue = (maxValue <= it ? it : maxValue);
	});
	return true;
}

/*template <typename T>
bool FindMax<const char *>(std::vector<const char*> const& arr, T& maxValue)
{

}*/

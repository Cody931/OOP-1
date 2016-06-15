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
	std::for_each(begin(arr), end(arr), [&](T it) {
		maxValue = (maxValue <= it ? it : maxValue);
	});
	return true;
}

/*ЗАДАНИЕ 
template <>
bool FindMax<const char *>(std::vector<const char*> const& arr, T& maxValue)
Внимание, необходимо обосновать предоставление Вашей реализацией функции FindMax гарантий строгой безопасности исключений, а также поддержи семантики выполнения «commit-or-rollback».
*/
template <>
bool FindMax <const char*> (std::vector<const char*> const& arr, T& maxValue)
{
	if (arr.empty())
	{
		return false;
	}
	std::for_each(begin(arr), end(arr), [&](auto it) {
		maxValue = (strcmp(maxValue, it) > 0 ? maxValue : it);
	});
	return true;
}

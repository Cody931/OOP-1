#pragma once
#include "MyArray.h"
#include <iostream>


template <typename T>
class CMyIterator : public std::iterator<std::random_access_iterator_tag, T>
{
public:
	CMyIterator(const CMyIterator &it)
		:m_itemPtr(it.m_itemPtr)
	{
	}
	CMyIterator(T * itemPtr)
		:m_itemPtr(itemPtr)
	{
	}
	CMyIterator(T * itemPtr, bool reverse)
		:m_itemPtr(itemPtr)
		,m_isReverse(reverse)
	{
	}
	T operator *() const
	{
		return *m_itemPtr;
	}

	CMyIterator & operator ++()
	{
		m_isReverse ? --m_itemPtr : ++m_itemPtr;
		return *this;
	}

	CMyIterator & operator --()
	{
		m_isReverse ? ++m_itemPtr : --m_itemPtr;
		return *this;
	}

	bool operator ==(CMyIterator<T> const& it)
	{
		return (*m_itemPtr == *it);
	}

	bool operator !=(CMyIterator<T> const& it)
	{
		return (*m_itemPtr != *it);
	}
private:
	T * m_itemPtr;
	bool m_isReverse = false;
};


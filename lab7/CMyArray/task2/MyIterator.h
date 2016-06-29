#pragma once
#include "MyArray.h"
#include <iterator>

template <typename T, bool isReverse>
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
	
	T operator *() const
	{
		return *m_itemPtr;
	}

	T & operator [](size_t index)
	{
		return m_itemPtr[index];
	}

	const T & operator [](const size_t index) const
	{
		return m_itemPtr[index];
	}

	CMyIterator operator ++(int)//постфиксный инкремент
	{
		if (isReverse)
		{
			return{ m_itemPtr-- };
		}
		return{ m_itemPtr++ };
	}

	CMyIterator operator --(int)//постфиксный динкремент
	{
		if (isReverse)
		{
			return{ m_itemPtr++ };
		}
		return { m_itemPtr-- };
	}

	T * operator ->()const
	{
		return itemPtr;
	}

	CMyIterator & operator ++()
	{
		isReverse ? --m_itemPtr : ++m_itemPtr;
		return *this;
	}

	CMyIterator & operator --()
	{
		isReverse ? ++m_itemPtr : --m_itemPtr;
		return *this;
	}

	CMyIterator & operator+=(const size_t numb)
	{
		m_itemPtr += (isReverse ? numb * (-1) : numb);
		return *this;
	}
	
	CMyIterator & operator-=(const size_t numb)
	{
		m_itemPtr -= (isReverse ? numb * (-1) : numb);
		return *this;
	}

	CMyIterator operator+(const size_t ind) const
	{
		m_itemPtr = (isReverse ? m_itemPtr + numb : m_itemPtr - numb);
	}

	

	CMyIterator operator-(const size_t numb) const
	{
		return (isReverse ? m_itemPtr + numb : m_itemPtr - numb);
	}

	bool operator ==(CMyIterator const& it)
	{
		return (*m_itemPtr == *it);
	}

	bool operator !=(CMyIterator const& it)
	{
		return (*m_itemPtr != *it);
	}

	bool operator > (CMyIterator const& it)
	{
		return *m_itemPtr > *it;
	}

	bool operator < (CMyIterator const& it)
	{
		return *m_itemPtr < *it;
	}

	bool operator <= (CMyIterator const& it)
	{
		return *m_itemPtr <= *it;
	}

	bool operator >= (CMyIterator const& it)
	{
		return *m_itemPtr >= *it;
	}
private:
	T * m_itemPtr;
};


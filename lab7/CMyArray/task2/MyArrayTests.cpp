#include "stdafx.h"
#include "MyArray.h"
#include <iostream>

using namespace std;

struct EmptyIntegerArray
{
	CMyArray<int> arr;
};

BOOST_FIXTURE_TEST_SUITE(MyArray, EmptyIntegerArray)
	BOOST_AUTO_TEST_SUITE(by_default)
		BOOST_AUTO_TEST_CASE(is_empty)
		{
			BOOST_CHECK_EQUAL(arr.GetSize(), 0u);
		}
		BOOST_AUTO_TEST_CASE(has_0_capacity)
		{
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 0u);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(after_appending_an_item)
		BOOST_AUTO_TEST_CASE(increases_its_size_and_capacity)
		{
			arr.Append(1);
			BOOST_CHECK_EQUAL(arr.GetSize(), 1u);
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 1u);
			arr.Append(2);
			BOOST_CHECK_EQUAL(arr.GetSize(), 2u);
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 2u);
			arr.Append(3);
			BOOST_CHECK_EQUAL(arr.GetSize(), 3u);
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 4u);
			arr.Append(4);
			BOOST_CHECK_EQUAL(arr.GetSize(), 4u);
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 4u);
		}
		BOOST_AUTO_TEST_CASE(it_becomes_available_at_the_back)
		{
			arr.Append(1);
			BOOST_CHECK_EQUAL(arr.GetBack(), 1);
			arr.Append(2);
			BOOST_CHECK_EQUAL(arr.GetBack(), 2);
			arr.Append(3);
			BOOST_CHECK_EQUAL(arr.GetBack(), 3);
			arr.Append(4);
			BOOST_CHECK_EQUAL(arr.GetBack(), 4);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(after_copy_construction)
		BOOST_AUTO_TEST_CASE(has_size_capacity_equal_to_size_of_original_array)
		{
			for (auto i = 0; i < 6; ++i)
			{
				arr.Append(i);
			}
			BOOST_CHECK_NE(arr.GetSize(), arr.GetCapacity());

			auto copy(arr);
			BOOST_CHECK_EQUAL(copy.GetSize(), arr.GetSize());
			BOOST_CHECK_EQUAL(copy.GetCapacity(), arr.GetSize());
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(can_be_resized)
		BOOST_AUTO_TEST_CASE(resize)
		{
			CMyArray<int> arr1 = {11, 22, 33, 44};
			arr1.Resize(2);
			BOOST_CHECK_EQUAL(arr1.GetSize(), 2u);
			BOOST_CHECK_EQUAL(arr1.GetCapacity(), 4u);

			arr1.Resize(3);
			BOOST_CHECK_EQUAL(arr1.GetSize(), 3u);
			BOOST_CHECK_EQUAL(arr1.GetCapacity(), 4u);

			arr1.Append(2);
			arr1.Append(3);
			arr1.Append(5);
			arr1.Append(6);
			BOOST_CHECK_EQUAL(arr1.GetSize(), 7u);
			BOOST_CHECK_EQUAL(arr1.GetCapacity(), 8u);

			arr1.Resize(3);
			BOOST_CHECK_EQUAL(arr1.GetSize(), 3u);
			BOOST_CHECK_EQUAL(arr1.GetCapacity(), 8u);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(can_clear_all_elements)
		BOOST_AUTO_TEST_CASE(clear)
		{
			arr.Append(0);
			arr.Append(1);
			arr.Append(2);
			BOOST_CHECK_EQUAL(arr.GetSize(), 3u);
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 4u);

			arr.Clear();
			BOOST_CHECK_EQUAL(arr.GetSize(), 0u);
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 4u);

			arr.Append(3);
			BOOST_CHECK_EQUAL(arr.GetSize(), 1u);
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 4u);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(return_element_on_the_some_position)
		BOOST_AUTO_TEST_CASE(return_element)
		{
			arr.Append(1);
			arr.Append(4);
			arr.Append(7);
			BOOST_CHECK_EQUAL(arr.GetSize(), 3u);
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 4u);
			BOOST_CHECK_EQUAL(arr[0], 1);
			BOOST_CHECK_EQUAL(arr[-1], 7);
			BOOST_CHECK_EQUAL(arr[-2], 4);
			BOOST_CHECK_THROW(arr[3], std::out_of_range);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(realize_operators)
		BOOST_AUTO_TEST_CASE(copy_assignment_operator)
		{
			CMyArray<int> arr2;
			arr = arr2;
			BOOST_CHECK_EQUAL(arr.GetSize(), 0u);
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 0u);

			arr2.Append(1);
			arr = arr2;
			BOOST_CHECK_EQUAL(arr.GetSize(), 1u);
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 1u);

			arr.Append(1);
			arr.Append(4);
			arr.Append(7);
			arr2.Append(4);
			arr = arr2;
			BOOST_CHECK_EQUAL(arr.GetSize(), 2u);
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 2u);
			CMyArray<int> arr1 = {0, 1, 2, 3, 4, 5};
			arr = arr2;
			BOOST_CHECK_EQUAL(arr.GetSize(), 2u);
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 2u);
			BOOST_CHECK_EQUAL(arr1.GetSize(), 6u);
			BOOST_CHECK_EQUAL(arr1.GetCapacity(), 6u);
		}
		BOOST_AUTO_TEST_CASE(overloading_assigment_operator)
		{
			CMyArray<int> arr2 = {1, 2, 3, 4};
			arr = std::move(arr2);

			BOOST_CHECK_EQUAL(arr.GetSize(), 4u);
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 4u);
			BOOST_CHECK_EQUAL(arr2.GetSize(), 0u);
			BOOST_CHECK_EQUAL(arr2.GetCapacity(), 0u);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(has_iterators)
		BOOST_AUTO_TEST_CASE(begin_and_end)
		{
			arr.Append(1);
			arr.Append(4);
			arr.Append(7);

			BOOST_CHECK_EQUAL(*arr.begin(), 1);
			
			CMyArray<int> arr1({ 0, 1, 2, 3 });
			int ind = 0;
			bool result = true;
			CMyIterator<int, false> iter = arr1.begin();
			for (size_t i = 0; i < arr1.GetSize(); i++, ind++)
			{
				if (iter[i] != ind)
				{
					result = !result;
				}
			}
			BOOST_CHECK(result);
			auto ptr = arr.begin();
			ptr += 1;
			BOOST_CHECK_EQUAL(*ptr, 4);
			ptr += 1;
			BOOST_CHECK_EQUAL(*ptr, 7);
			ptr -= 1;
			BOOST_CHECK_EQUAL(*ptr, 4);
		}
		BOOST_AUTO_TEST_CASE(rbegin_and_rend)
		{
			arr.Append(0);
			arr.Append(1);
			arr.Append(2);

			BOOST_CHECK_EQUAL(*arr.rbegin(), 2);
			int count = 2;
			bool result = true;
			for (auto p = arr.rbegin(); p != arr.rend(); p++, count--)
			{
				if (*p != count)
				{
					result = !result;
				}
			}
			BOOST_CHECK(result);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(has_moves_constructor)
		BOOST_AUTO_TEST_CASE(moves_constructor)
		{
			CMyArray<int> arr1 = { 0, 1, 2, 3, 4, 5 };
			CMyArray<int> arr2(std::move(arr1));
			BOOST_CHECK_EQUAL(arr1.GetSize(), 0u);
			BOOST_CHECK_EQUAL(arr2.GetSize(), 6u);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

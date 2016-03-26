#include "stdafx.h"
#include "../VectorProcessor/VectorProcessor.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(ProcessVector_function)

	BOOST_AUTO_TEST_CASE(should_make_empty_vector_from_empty_vector)
	{
		vector<double> emptyVector;
		TransformVector(emptyVector);
		BOOST_CHECK(emptyVector.empty());
	}

	BOOST_AUTO_TEST_CASE(should_multiply_each_item_by_the_minimal_item_when_minimum_is_in_the_beginning)
	{
		vector<double> checkedVector = { 2, 6, 3, 7 };
		vector<double> rightVector = { 4, 12, 6, 14 };
		TransformVector(checkedVector);
		BOOST_CHECK(checkedVector == rightVector);
	}

	BOOST_AUTO_TEST_CASE(should_multiply_each_item_by_the_minimal_item_when_minimum_is_in_the_middle)
	{
		vector<double> checkedVector = { 4, 6, 2, 3, 7 };
		vector<double> rightVector = { 4, 12, 4, 6, 14 };
		TransformVector(checkedVector);
		BOOST_CHECK(checkedVector == rightVector);
	}

	BOOST_AUTO_TEST_CASE(should_multiply_each_item_by_the_minimal_item_when_minimum_is_in_the_end)
	{
		vector<double> checkedVector = { 14, 3, 18, 2 };
		vector<double> rightVector = { 28, 6, 36, 4 };
		TransformVector(checkedVector);
		BOOST_CHECK(checkedVector == rightVector);
	}

	BOOST_AUTO_TEST_CASE(should_multiply_each_item_by_the_minimal_item_when_all_items_are_the_same)
	{
		vector<double> checkedVector = { 3, 3, 3, 3 };
		vector<double> rightVector = { 9, 9, 9, 9 };
		TransformVector(checkedVector);
		BOOST_CHECK(checkedVector == rightVector);
	}

BOOST_AUTO_TEST_SUITE_END()

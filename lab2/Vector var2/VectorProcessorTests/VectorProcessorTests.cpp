#include "stdafx.h"
#include "../VectorProcessor/VectorProcessor.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(ProcessVector_function)

	BOOST_AUTO_TEST_CASE(should_return_empty_vector)
	{
		vector<double> emptyVector;
		TransformVector(emptyVector);
		BOOST_CHECK(emptyVector.empty());
	}

	BOOST_AUTO_TEST_CASE(should_return_elements_equal_to_zero)
	{
		vector<double> checkedVector = { 7, 2, 0, 3 };
		vector<double> rightVector = { 0, 0, 0, 0 };
		TransformVector(checkedVector);
		BOOST_CHECK(checkedVector == rightVector);
	}

	BOOST_AUTO_TEST_CASE(should_return_minimum_element_the_last)
	{
		vector<double> checkedVector = { 14, 3, 18, 2 };
		vector<double> rightVector = { 28, 6, 36, 4 };
		TransformVector(checkedVector);
		BOOST_CHECK(checkedVector == rightVector);
	}

	BOOST_AUTO_TEST_CASE(should_return_minimum_element_the_first)
	{
		vector<double> checkedVector = { 2, 6, 3, 7 };
		vector<double> rightVector = { 4, 12, 6, 14 };
		TransformVector(checkedVector);
		BOOST_CHECK(checkedVector == rightVector);
	}

	BOOST_AUTO_TEST_CASE(should_return_a_vector_equal_to_the_initial)
	{
		vector<double> checkedVector = { 5, 1, 3, 2 };
		vector<double> rightVector = { 5, 1, 3, 2 };
		TransformVector(checkedVector);
		BOOST_CHECK(checkedVector == rightVector);
	}

	
BOOST_AUTO_TEST_SUITE_END()
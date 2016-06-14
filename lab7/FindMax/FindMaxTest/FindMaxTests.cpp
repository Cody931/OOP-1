#include "stdafx.h"
#include "..\FindMax\FindMax.h"
#include <string>

using namespace std;

BOOST_AUTO_TEST_SUITE(Template_FindMax)

	BOOST_AUTO_TEST_CASE(find_integer_max_element)
	{
		vector<int> a = { 0, 1, 2, 3, 4 };
		int maxValue;
		BOOST_CHECK(FindMax(a, maxValue));
		BOOST_CHECK_EQUAL(4, maxValue);
	}

	BOOST_AUTO_TEST_CASE(find_max_float_element)
	{
		vector<float> a = {-2.45f, 5.31f, 6.83f, 0.0f, 9.81f };
		float maxValue;
		BOOST_CHECK(FindMax(a, maxValue));
		BOOST_CHECK_EQUAL(9.81f, maxValue);
	}

	BOOST_AUTO_TEST_CASE(find_max_string_element)
	{
		vector<string> a = { "mom", "dad", "me", "dog" };
		string maxValue;
		BOOST_CHECK(FindMax(a, maxValue));
		BOOST_CHECK_EQUAL("mom", maxValue);
	}

	BOOST_AUTO_TEST_CASE(return_false_when_vector_is_empty)
	{
		vector<int> a;
		int maxValue;
		BOOST_CHECK(!FindMax(a, maxValue));
	}

BOOST_AUTO_TEST_SUITE_END()
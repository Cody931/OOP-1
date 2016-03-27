#include "stdafx.h"
#include "../Map_WordOccurrence/WordOccurrence.h"
#include <string>
#include <map>

BOOST_AUTO_TEST_SUITE(CalculateOccurrenceWords_function)

	BOOST_AUTO_TEST_CASE(should_make_empty_map_from_empty_string)
	{
		string emptyString;
		map<string, int> checkedMap;
		checkedMap = CalculateOccurrenceOfWords(emptyString);
		BOOST_CHECK(checkedMap.empty());
	}

	BOOST_AUTO_TEST_CASE(should_calculate_the_numb_occurrences_of_words_with_different_registers)
	{
		string inputString;
		inputString = "Hello beaUtifUl wOrld ! hELLO WorLD !";
		map<string, int> rightMap = { 
			{"hello", 2},
			{"beautiful", 1},
			{"world", 2},
			{"!", 2}};
		map<string, int> checkedMap;
		checkedMap = CalculateOccurrenceOfWords(inputString);
		BOOST_CHECK(checkedMap == rightMap);
	}
BOOST_AUTO_TEST_SUITE_END()
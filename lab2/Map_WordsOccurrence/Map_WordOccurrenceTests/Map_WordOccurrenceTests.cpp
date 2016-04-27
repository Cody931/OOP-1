#include "stdafx.h"
#include "../Map_WordOccurrence/WordOccurrence.h"
#include <string>
#include <map>

using namespace std;

BOOST_AUTO_TEST_SUITE(CalculateOccurrenceWords_function)

	BOOST_AUTO_TEST_CASE(should_make_empty_map_from_empty_string)
	{
		string emptyString;
		map<string, int> expectedMap = CalculateOccurrenceOfWords(emptyString);
		BOOST_CHECK(expectedMap.empty());
	}

	BOOST_AUTO_TEST_CASE(should_calculate_the_numb_occurrences_of_words_with_different_registers)
	{
		string inputString = "Hello beaUtifUl wOrld! hELLO WorLD!";
		map<string, int> correctMap = 
		{
			{"hello", 2},
			{"beautiful", 1},
			{"world", 2}
		};
		map<string, int> expectedMap = CalculateOccurrenceOfWords(inputString);
		BOOST_CHECK(expectedMap == correctMap);
	}

	BOOST_AUTO_TEST_CASE(should_calculate_the_numb_occurrences_of_words_with_the_same_registers)
	{
		string inputString = "HELLO   BEAUTIFUL WORLD! HELLO WORLD!";
		map<string, int> correctMap =
		{
			{ "beautiful", 1 },
			{ "hello", 2 },
			{ "world", 2 }
		};
		map<string, int> expectedMap = CalculateOccurrenceOfWords(inputString);
		BOOST_CHECK(expectedMap == correctMap);
	}

	BOOST_AUTO_TEST_CASE(should_calculate_the_numb_occurrences_words_of_multiline_raw_string)
	{
		string longText = R"***(
			There are many big and small libraries everywhere in our country. 
there are 4 big windows in it. 
The walls are light blue.
There are a lot of shelves full of books. There are books in English, too.
)***";
		map<string, int> correctMap = {
			{ "4", 1 },
			{ "a", 1 },
			{ "and", 1 },
			{ "are", 5 },
			{ "big", 2 },
			{ "blue", 1 },
			{ "books", 2 },
			{ "country", 1 },
			{ "english", 1 },
			{ "everywhere", 1 },
			{ "full", 1 },
			{ "in", 3 },
			{ "it", 1 },
			{ "libraries", 1 },
			{ "light", 1 },
			{ "lot", 1 },
			{ "many", 1 },
			{ "of", 2 },
			{ "our", 1 },
			{ "shelves", 1 },
			{ "small", 1 },
			{ "the", 1 },
			{ "there", 4 },
			{ "too", 1 },
			{ "walls", 1 },
			{ "windows", 1 }
		};
		map<string, int> expectedMap = CalculateOccurrenceOfWords(longText);
		BOOST_CHECK(expectedMap == correctMap);
	}
	
	BOOST_AUTO_TEST_CASE(should_calculate_the_numb_occurrences_of_words_with_different_dividers_in_text)
	{
		string inputString = "      HELLO     BEAUTIFUL,,WORLD! HELLO,WORLD!     ";
		map<string, int> correctMap =
		{
			{ "hello", 2 },
			{ "beautiful", 1 },
			{ "world", 2 }
		};
		map<string, int> expectedMap = CalculateOccurrenceOfWords(inputString);
		BOOST_CHECK(expectedMap == correctMap);
	}

BOOST_AUTO_TEST_SUITE_END()
#include "stdafx.h"
#include "WordOccurrence.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <boost/range/algorithm/transform.hpp>

string ReadInputData()
{
	string words;
	getline(cin, words);
	return words;
}

vector<string> SplitStringIntoVector(string const& inputText)
{
	stringstream stream(inputText);
	vector<string> words;
	string buf;
	while (stream >> buf)
	{
		words.push_back(buf);
	}
	return words;
}

map<string, int> CalculateOccurrenceOfWords(string const& text)
{
	map<string, int> wordsOccurrence;
	vector<string> inputWords = SplitStringIntoVector(text);
	
	if (inputWords.size() != 0)
	{
		for (auto word : inputWords)
		{
			boost::transform(word, word.begin(), tolower);
			if (wordsOccurrence.count(word) == 1)
				wordsOccurrence[word] += 1;
			else
				wordsOccurrence.insert(pair<string, int>(word, 1));
		}
	}
	return wordsOccurrence;
}

void PrintMap(map<string, int> const& words)
{
	for (auto word = words.begin(); word != words.end(); ++word)
	{
		cout << word->first << " : " << word->second << endl;
	}
}
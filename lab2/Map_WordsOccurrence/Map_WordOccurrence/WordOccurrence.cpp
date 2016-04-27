#include "stdafx.h"
#include "WordOccurrence.h"
#include <boost/range/algorithm/transform.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;

string ReadInputData(istream & input)
{
	string inputText;
	getline(input, inputText);
	return inputText;
}

vector<string> SplitWords(string const& inputText)
{
	vector<string> words;
	boost::split(words, inputText, boost::is_any_of(" ,.!?-\n\t"));
	words.erase(remove(words.begin(), words.end(), ""), words.end());
	return words;
}

map<string, int> CalculateOccurrenceOfWords(string const& inputText)
{
	map<string, int> wordsOccurrence;
	for (auto word : SplitWords(inputText))
	{
		boost::transform(word, word.begin(), tolower);
		if (wordsOccurrence.count(word))
		{
			wordsOccurrence[word] += 1;
		}
		else
		{
			wordsOccurrence.insert(make_pair(word, 1));
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
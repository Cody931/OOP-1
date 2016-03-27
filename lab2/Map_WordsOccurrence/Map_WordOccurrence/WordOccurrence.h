#pragma once
#include <string>
#include <vector>
#include <map>

using namespace std;

string ReadInputData();

vector<string> SplitStringIntoVector(string const& inputText);

map<string, int> CalculateOccurrenceOfWords(string const& text);

void PrintMap(map<string, int> const& words);
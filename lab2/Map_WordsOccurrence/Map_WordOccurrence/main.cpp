#include "stdafx.h"
#include <string>
#include <windows.h>
#include <iostream>
#include "WordOccurrence.h"

using namespace std;

int _tmain()
{
	string inputText;
	map<string, int> occurenceOfWords;
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	inputText = ReadInputData();
	occurenceOfWords = CalculateOccurrenceOfWords(inputText);
	PrintMap(occurenceOfWords);
	return 0;
}


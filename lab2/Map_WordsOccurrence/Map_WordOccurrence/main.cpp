#include "stdafx.h"
#include "WordOccurrence.h"

int _tmain()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	std::map<std::string, int> occurenceOfWords = CalculateOccurrenceOfWords(ReadInputData(std::cin));
	PrintMap(occurenceOfWords);
	return 0;
}


#pragma once

std::string ReadInputData(std::istream & input);

std::vector<std::string> SplitWords(std::string const& inputText);

std::map<std::string, int> CalculateOccurrenceOfWords(std::string const& inputText);

void PrintMap(std::map<std::string, int> const& words);
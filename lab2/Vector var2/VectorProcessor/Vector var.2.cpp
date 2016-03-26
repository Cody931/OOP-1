#include "stdafx.h"
#include <vector>
#include <iostream>
#include <algorithm> 
#include "VectorProcessor.h"

int _tmain()
{
	vector<double> numbers;
	std::cout << "Please enter float numbers(Example: 17.256), separated by space.\nWhen you're finished enter 'dot + Enter'\nNumbers: ";
	numbers = ReadInputDataInVector();
	TransformVector(numbers);
	sort(begin(numbers), end(numbers));
	PrintVector(numbers);
    return 0;
}


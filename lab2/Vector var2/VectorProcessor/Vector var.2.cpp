#include "stdafx.h"
#include <vector>
#include <iostream>
#include "VectorProcessor.h"

int _tmain()
{
	vector<double> numbers;
	std::cout << "Please enter float numbers(Example: 17.256), separated by space.\nWhen you're finished enter 'dot + Enter'\nNumbers: ";
	numbers = ReadInputDataInVector();
	TransformVector(numbers);
	Sort(numbers);
	PrintVector(numbers);
    return 0;
}


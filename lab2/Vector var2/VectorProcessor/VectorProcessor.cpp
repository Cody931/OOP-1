#include "stdafx.h"
#include "VectorProcessor.h"
#include <boost/range/algorithm/transform.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <iterator>
#include <algorithm> 
#include <iostream>

vector<double> ReadInputDataInVector()
{
	return{ istream_iterator<double>(cin), (istream_iterator<double>()) };
}

void TransformVector(vector<double> & numbers)
{
	if (!numbers.empty()) 
	{
		double min = *std::min_element(begin(numbers), end(numbers));
		boost::transform(numbers, numbers.begin(), [min](double numb)
		{
			return numb * min;
		});
	}
}

void PrintVector(vector<double> const& numbers)
{
	boost::copy(numbers, ostream_iterator<double>(cout, " "));
	cout << endl;
}
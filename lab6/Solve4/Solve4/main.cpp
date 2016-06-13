#include "stdafx.h"
#include "Equation.h"

using namespace std;

int main()
{
	std::vector<double> coof(istream_iterator<double>(cin), (istream_iterator<double>()));
	EquationRoot4 roots = Solve4(coof[0], coof[1], coof[2], coof[3], coof[4]);
	ShowRoots(roots);
    return 0;
}


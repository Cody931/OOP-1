#include "stdafx.h"
#include "Equation.h"

using boost::math::double_constants::pi;
using boost::none;
using boost::optional;
using namespace std;


pair<optional<double>, optional<double>> Solve2(double a, double b, double c)
{
	double D = pow(b, 2) - (4 * a * c);
	if (D == 0)
	{
		return{ -b / (2 * a) , none};
	}
	else if (D > 0)
	{
		return{ (-b + sqrt(D)) / (2 * a) , (-b - sqrt(D)) / (2 * a) };
	}
	return{none, none};
}

double Solve3(double a, double b, double c)
{
	double roots[3];
	double q = (pow(a, 2) - 3.0 * b) / 9.0;
	double r = (2.0 * pow(a, 3) - 9.0 * a * b + 27.0 * c) / 54.0;
	double s = pow(q, 3) - pow(r, 2);
	if (s > 0)
	{
		double grad = r / sqrt(pow(q, 3));
		double fi = (1.0 / 3.0) * acos(grad);

		roots[0] = -2 * sqrt(q) * cos(fi) - a / 3.0;
		roots[1] = -2 * sqrt(q) * cos(fi + 2 * pi / 3.0) - a / 3.0;
		roots[2] = -2 * sqrt(q) * cos(fi - 2 * pi / 3.0) - a / 3.0;
	}
	else if (s < 0)
	{
		double fi = (1.0 / 3.0) * (q > 0 ? acosh(abs(r) / sqrt(pow(abs(q), 3))) : asinh(abs(r) / sqrt(pow(abs(q), 3))));
		roots[0] = -2 * ((r > 0) ? 1 : ((r < 0) ? -1 : 0)) * sqrt(abs(q))*(q > 0 ? cosh(fi) : sinh(fi)) - a / 3.0;
	}
	sort(rbegin(roots), rend(roots));
	return roots[0];
}

void AddNewPairOfRoots(EquationRoot4 & eq, pair<optional<double>, optional<double>> const& roots, double coef)
{
	if (roots.first)
	{
		eq.roots[eq.numRoots] = roots.first.get() + coef;
		++eq.numRoots;
	}
	if (roots.second)
	{
		eq.roots[eq.numRoots] = roots.second.get() + coef;
		++eq.numRoots;
	}
}

EquationRoot4 Solve4(double a, double b, double c, double d, double e)
{
	if (a == 0)
	{
		throw invalid_argument("Argument 'a' can not be 0.");
	}
	EquationRoot4 result; 
	double p = (8 * a * c - 3 * pow(b, 2)) / (8 * pow(a, 2));
	double q = (8 * pow(a, 2) * d + pow(b, 3) - 4 * a * b * c) / (8 * pow(a, 3));
	double r = (16 * a*pow(b, 2) * c - 64 * pow(a, 2)*b*d - 3 * pow(b, 4) + 256 * e*pow(a, 3)) / (256 * pow(a, 4));
	if (q == 0)
	{
		pair<optional<double>, optional<double>> equationRoot2First = Solve2(1, p, r);
		if (equationRoot2First.first)
		{
			AddNewPairOfRoots(result, Solve2(1, 0, -equationRoot2First.first.get()), -b / (4.0 * a));
		}
		if (equationRoot2First.second)
		{
			AddNewPairOfRoots(result, Solve2(1, 0, -equationRoot2First.first.get()), -b / (4.0 * a));
		}
	}
	else
	{
		double z = Solve3(p, (pow(p, 2) - 4 * r) / 4, -pow(q, 2)/8);
		AddNewPairOfRoots(result, Solve2(1, -sqrt(2 * z), p / 2 + z + q / (2 * sqrt(2 * z))), -b / (4.0 * a));
		AddNewPairOfRoots(result, Solve2(1, sqrt(2 * z), p / 2 + z - q / (2 * sqrt(2 * z))), -b / (4.0 * a));
	}
	sort(begin(result.roots), begin(result.roots) + result.numRoots);
	if (result.numRoots == 0)
	{
		throw domain_error("Equation does not have of real roots");
	}
	return result;
}

void ShowRoots(EquationRoot4 const& roots)
{
	if (roots.numRoots)
	{
		cout << "Equation has " << roots.numRoots << " root" << (roots.numRoots > 1 ? "s" : "") << " : ";
		for (size_t i = 0; i < roots.numRoots; i++)
		{
			cout << roots.roots[i] << "  ";
		}
		cout << endl;
	}
	else
	{
		cout << "Equation does not have of real roots" << endl;
	}
}
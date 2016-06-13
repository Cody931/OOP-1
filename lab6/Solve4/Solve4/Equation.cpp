#include "stdafx.h"
#include "Equation.h"
#include <boost/math/constants/constants.hpp>


using boost::math::double_constants::pi;
using namespace std;

void Solve2(double a, double b, double c)
{
	double D = pow(b, 2) - 4 * a * c;
	double root1 = (-b + sqrt(D)) / (2 * a);
	double root2 = (-b - sqrt(D)) / (2 * a);

	cout << root1 << endl;
	cout << root2 << endl;
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
	sort(begin(roots), end(roots));
	return roots[3];
}

void PushAvailableRoot(double resultRoot, EquationRoot4 & roots)
{
	if (resultRoot)
	{
		roots.roots[roots.numRoots] = resultRoot;
		++roots.numRoots;
	}
	else
	{
		throw domain_error("Root can not be the irrational number.");
	}
}

EquationRoot4 Solve4(double a, double b, double c, double d, double e)
{
	if (a == 0)
	{
		throw invalid_argument("Argument 'a' can not be 0.");
	}
	EquationRoot4 result;
	//Решение уравнения 4 степени с помощью метода Феррари (https://ru.wikipedia.org/wiki/%D0%9C%D0%B5%D1%82%D0%BE%D0%B4_%D0%A4%D0%B5%D1%80%D1%80%D0%B0%D1%80%D0%B8)
	double p = (8 * a * c - 3 * pow(b, 2)) / (8 * pow(a, 2));
	double q = (8 * pow(a, 2) * d + pow(b, 3) - 4 * a * b * c) / (8 * pow(a, 3));
	double r = (-3 * pow(b, 4) / (256 * pow(a, 4)) + pow(b, 2) * c / (16 * pow(a, 3)) - b * d / (4 * pow(a, 2)) + e / a);
	if (q == 0)
	{
		cout << sqrt(0) << endl;
		PushAvailableRoot(sqrt((-p - sqrt(pow(p, 2) - 4 * r)) / 2) - b / (4 * a), result);
		PushAvailableRoot(-sqrt((-p - sqrt(pow(p, 2) - 4 * r)) / 2) - b / (4 * a), result);
		PushAvailableRoot(sqrt((-p + sqrt(pow(p, 2) - 4 * r)) / 2) - b / (4 * a), result);
		PushAvailableRoot(-sqrt((-p + sqrt(pow(p, 2) - 4 * r)) / 2) - b / (4 * a), result);
	}
	else
	{
		double P = -pow(p, 2) / 12 - r;
		double Q = -pow(p, 3) / 108 + (p * r) / 3 - pow(q, 2) / 8;
		double R = -Q / 2 + sqrt(pow(Q, 2)/4 + pow(P, 3)/27);
		double U = pow(R, 1/3);
		double y = -(5 / 6)*p + U - (U == 0 ? pow(Q, 1/3) : P / (3 * U));
		double W = sqrt(p + 2 * y);

		double varPositive = sqrt(-(3 * p + 2 * y + 2 * q / W));
		double varNegative = sqrt(-(3 * p + 2 * y - 2 * q / W));
		PushAvailableRoot(-b / (4.0 * a) + (W + varPositive) / 2.0, result);
		PushAvailableRoot(-b / (4.0 * a) + (W - varPositive) / 2.0, result);
		PushAvailableRoot(-b / (4.0 * a) + (-W + varNegative) / 2.0, result);
		PushAvailableRoot(-b / (4.0 * a) + (-W - varNegative) / 2.0, result);;
	}

	sort(begin(result.roots), end(result.roots));
	if (!result.numRoots)
	{
		throw domain_error("Equation does not have of real roots");
	}
	return result;
}

void ShowRoots(EquationRoot4 const& roots)
{
	cout << endl << "roots: " << endl;
	for (size_t i = 0; i < roots.numRoots; i++)
	{
		cout << roots.roots[i] << endl;
	}
}
#pragma once
#include "stdafx.h"

struct EquationRoot4
{
	size_t numRoots = 0;
	double roots[4];
};


std::pair<boost::optional<double>, boost::optional<double>> Solve2(double a, double b, double c);
double Solve3(double a, double b, double c);
void AddNewPairOfRoots(EquationRoot4 & eq, std::pair<boost::optional<double>, boost::optional<double>> const& roots, double coef);
EquationRoot4 Solve4(double a, double b, double c, double d, double e);
void ShowRoots(EquationRoot4 const& roots);
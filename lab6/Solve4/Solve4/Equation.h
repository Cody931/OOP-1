#pragma once
#include "stdafx.h"

struct EquationRoot4
{
	size_t numRoots = 0;
	double roots[4];
};


// ¬ычисл€ем корни кубического уравнени€ ax^4 + bx^3 + cx^2 + dx + e = 0
EquationRoot4 Solve4(double a, double b, double c, double d, double e);
void PushAvailableRoot(double resultRoot, EquationRoot4 & roots);
void ShowRoots(EquationRoot4 const& roots);
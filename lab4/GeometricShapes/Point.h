#pragma once
#include "stdafx.h"
#include "IShape.h"

class CPoint final : public IShape
{
public:
	CPoint(int x, int y);
	
	std::string ToString()const override;
	double GetArea()const override;
	double GetPerimeter()const override;
	~CPoint();
public:
	int m_x;
	int m_y;
};

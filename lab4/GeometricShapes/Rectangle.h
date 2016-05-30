#pragma once
#include "SolidShape.h"
#include "Point.h"

class CRectangle final : public ISolidShape
{
public:
	CRectangle(int x, int y, int width, int height);

	std::string ToString()const override;
	double GetPerimeter()const override;
	double GetArea()const override;

	~CRectangle();
private:
	CPoint m_vertex;
	int m_width;
	int m_height;
};


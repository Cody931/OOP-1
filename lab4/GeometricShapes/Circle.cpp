#include "stdafx.h"
#include "Circle.h"

using boost::math::double_constants::pi;


CCircle::CCircle(int x, int y, int radius)
	: m_centrePoint(x, y)
	, m_x(x)
	, m_y(y)
	, m_radius(radius)
{
}

std::string CCircle::ToString() const
{
	std::stringstream stream;
	stream << "Circle <" << m_centrePoint.m_x << "," << m_centrePoint.m_y << ">, R=" << m_radius;
	stream << ", P=" << GetPerimeter() << ", S=" << GetArea();
	return stream.str();
}

double CCircle::GetPerimeter() const
{
	return (2 * pi * m_radius);
}

double CCircle::GetArea() const
{
	return (pi * pow(m_radius, 2));
}


CCircle::~CCircle()
{
}

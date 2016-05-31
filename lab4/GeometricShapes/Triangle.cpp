#include "stdafx.h"
#include "Triangle.h"



CTriangle::CTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
	: m_firstVertex(x1, y1)
	, m_secondVertex(x2, y2)
	, m_thirdVertex(x3, y3)
{
	m_firstSide = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
	m_secondSide = sqrt(pow((x3 - x2), 2) + pow((y3- y2), 2));
	m_thirdSide = sqrt(pow((x1 - x3), 2) + pow((y1 - y3), 2));
}

std::string CTriangle::ToString() const
{
	std::stringstream stream;
	stream << "Triangle <<" << m_firstVertex.m_x << "," << m_firstVertex.m_y << ">";
	stream << "<" << m_secondVertex.m_x << "," << m_secondVertex.m_y << ">";
	stream << "<" << m_thirdVertex.m_x << "," << m_thirdVertex.m_y << ">>";
	stream << ", P=" << GetPerimeter() << ", S=" << GetArea();
	return stream.str();
}

double CTriangle::GetPerimeter() const
{
	return (m_firstSide + m_secondSide + m_thirdSide);
}

double CTriangle::GetArea() const
{
	double p = GetPerimeter() / 2;
	return sqrt(p * (p - m_firstSide) * (p - m_secondSide) * (p - m_thirdSide));
}


CTriangle::~CTriangle()
{
}
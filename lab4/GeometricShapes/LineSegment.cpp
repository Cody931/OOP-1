#include "stdafx.h"
#include "LineSegment.h"


CLineSegment::CLineSegment(int x1, int y1, int x2, int y2)
	: m_beginPoint(x1, y1)
	, m_endPoint(x2, y2)
{
	m_length = sqrt(pow((m_endPoint.m_x - m_beginPoint.m_x), 2) + pow((m_endPoint.m_y - m_beginPoint.m_y), 2));
}

std::string CLineSegment::ToString() const
{
	std::stringstream stream;
	stream << "Line Segment <<" << m_beginPoint.m_x << "," << m_beginPoint.m_y << "><" << m_endPoint.m_x << "," << m_endPoint.m_y << ">>";
	stream << ", P=" << GetPerimeter() << ", S=" << GetArea();
	return stream.str();
}

double CLineSegment::GetArea() const
{
	return 0.0;
}

double CLineSegment::GetPerimeter() const
{
	return m_length;
}


CLineSegment::~CLineSegment()
{
}

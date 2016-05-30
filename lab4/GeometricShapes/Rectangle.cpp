#include "stdafx.h"
#include "Rectangle.h"


CRectangle::CRectangle(int x, int y, int width, int height)
	: m_vertex(x, y)
	, m_width(width)
	, m_height(height)
{
}

std::string CRectangle::ToString() const
{
	std::stringstream stream;
	stream << "Rectangle <" << m_vertex.m_x << "," << m_vertex.m_y << ">, W=" << m_width << ", H=" << m_height;
	stream << ", P=" << GetPerimeter() << ", S=" << GetArea();
	return stream.str();
}

double CRectangle::GetPerimeter() const
{
	return 2 * (m_width + m_height);
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}


CRectangle::~CRectangle()
{
}

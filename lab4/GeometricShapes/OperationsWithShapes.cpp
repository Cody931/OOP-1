#include "stdafx.h"
#include "OperationsWithShapes.h"

using namespace std;
using namespace std::placeholders;

COperationsWithShapes::COperationsWithShapes(istream & input, ostream & output, std::vector<shared_ptr<IShape>> & shapes)
	: m_input(input)
	, m_output(output)
	, m_shapes(shapes)
	, m_shapesMap({
		{ "point", bind(&COperationsWithShapes::GetPointPtr, this, _1) },
		{ "line", bind(&COperationsWithShapes::GetLinePtr, this, _1) },
		{ "circle", bind(&COperationsWithShapes::GetCirclePtr, this, _1) },
		{ "rectangle", bind(&COperationsWithShapes::GetRectanglePtr, this, _1) },
		{ "triangle", bind(&COperationsWithShapes::GetTrianglePtr, this, _1) },
})
{
}

void COperationsWithShapes::SortByPerimeter(int left, int right, vector<shared_ptr<IShape>> & x) 
{
	std::sort(m_shapes.begin(), m_shapes.end(), [](std::shared_ptr<IShape> & first, std::shared_ptr<IShape> & second)
	{
		return first->GetPerimeter() > second->GetPerimeter();
	});
}

void COperationsWithShapes::SortByArea(int left, int right, vector<shared_ptr<IShape>> & x) {
	std::sort(m_shapes.begin(), m_shapes.end(), [](std::shared_ptr<IShape> & first, std::shared_ptr<IShape> & second)
	{
		return first->GetArea() < second->GetArea();
	});
}

void COperationsWithShapes::GetInfoAndSort()
{
	m_output << "Sorting by increasing the areas:\n" << endl;
	SortByArea(0, m_shapes.size() - 1, m_shapes);
	for (auto it : m_shapes)
	{
		m_output << it->ToString() << endl;
	}
	cout << endl << endl << "Sorting by reduce the perimeters:\n" << endl;
	SortByPerimeter(0, m_shapes.size() - 1, m_shapes);
	for (auto it : m_shapes)
	{
		m_output << it->ToString() << endl;
	}
}

bool COperationsWithShapes::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);
	string shape;
	strm >> shape;
	auto it = m_shapesMap.find(shape);
	if (it != m_shapesMap.end())
	{
		m_shapes.push_back(it->second(strm));
	}
	else if (shape == "end")
	{
		GetInfoAndSort();
	}
	else
	{
		return false;
	}
	return true;
}

std::shared_ptr<IShape> COperationsWithShapes::GetPointPtr(istream & strm)
{
	int x, y;
	strm >> x >> y;
	return make_shared<CPoint>(CPoint(x, y));
}

std::shared_ptr<IShape> COperationsWithShapes::GetLinePtr(std::istream & strm)
{
	int beginX, beginY, endX, endY;
	strm >> beginX >> beginY >> endX >> endY;
	return make_shared<CLineSegment>(CLineSegment(beginX, beginY, endX, endY));
}

std::shared_ptr<IShape> COperationsWithShapes::GetCirclePtr(std::istream & strm)
{
	int x, y, radius;
	strm >> x >> y >> radius;
	return make_shared<CCircle>(CCircle(x, y, radius));
}

std::shared_ptr<IShape> COperationsWithShapes::GetRectanglePtr(std::istream & strm)
{
	int x, y, w, h;
	strm >> x >> y >> w >> h;
	return make_shared<CRectangle>(CRectangle(x, y, w, h));
}

std::shared_ptr<IShape> COperationsWithShapes::GetTrianglePtr(std::istream & strm)
{
	int x1, y1, x2, y2, x3, y3;
	strm >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
	return make_shared<CTriangle>(CTriangle(x1, y1, x2, y2, x3, y3));
}

COperationsWithShapes::~COperationsWithShapes()
{
}


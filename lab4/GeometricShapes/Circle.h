#include "SolidShape.h"
#include "Point.h"

class CCircle final : public ISolidShape
{
public:
	CCircle(int x, int y, int radius);
	
	std::string ToString()const override;
	double GetPerimeter()const override;
	double GetArea()const override;
	
	~CCircle();
private:
	CPoint m_centrePoint;
	int m_x;
	int m_y;
	int m_radius;
};


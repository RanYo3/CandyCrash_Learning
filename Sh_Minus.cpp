#include "stdafx.h"
#include "Sh_Minus.h"

IMPLEMENT_SERIAL(Sh_Minus, CObject, 1)

Sh_Minus::Sh_Minus(Color color, ShapeType type, int polygonSize) 
	: Sh_Triangle(color, type, polygonSize) { }

Sh_Minus::Sh_Minus(const Sh_Minus &other)
	: Sh_Triangle(other) { }

Shape *Sh_Minus::Clone() const
{
	return new Sh_Minus(*this);
}

void Sh_Minus::BuildPolygon()
{
	Point *poly = GetPolygon();
	Point topLeft = GetTopLeft();
	Point bottomRight = GetBottomRight();

	int partY = (int)((double)(bottomRight.GetY() - topLeft.GetY()) / PART_SIZE);

	poly[0] = Point(bottomRight.GetX(), topLeft.GetY()     + partY);
	poly[1] = Point(bottomRight.GetX(), bottomRight.GetY() - partY);
	poly[2] = Point(topLeft.GetX()    , bottomRight.GetY() - partY);
	poly[3] = Point(topLeft.GetX()    , topLeft.GetY()     + partY);
}
#include "stdafx.h"
#include "Sh_Triangle.h"

IMPLEMENT_SERIAL(Sh_Triangle, CObject, 1)

Sh_Triangle::Sh_Triangle(const Color &color, ShapeType type, int polygonSize)
	: Sh_Diamond(color, type, polygonSize) { }

Sh_Triangle::Sh_Triangle(const Sh_Triangle &other)
	: Sh_Diamond(other) { }

Shape *Sh_Triangle::Clone() const
{
	return new Sh_Triangle(*this);
}

void Sh_Triangle::BuildPolygon()
{
	Point *poly = GetPolygon();
	Point topLeft = GetTopLeft();
	Point bottomRight = GetBottomRight();

	poly[0] = Point((topLeft.GetX() + bottomRight.GetX()) / 2, topLeft.GetY());
	poly[1] = bottomRight;
	poly[2] = Point(topLeft.GetX(), bottomRight.GetY());
}
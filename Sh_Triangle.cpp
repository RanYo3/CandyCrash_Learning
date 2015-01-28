#include "stdafx.h"
#include "Sh_Triangle.h"

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
	CTypedPtrArray<CObArray, Point *> poly;
	Point topLeft = GetTopLeft();
	Point bottomRight = GetBottomRight();

	poly.Add(new Point((topLeft.GetX() + bottomRight.GetX()) / 2, topLeft.GetY()));
	poly.Add(new Point(bottomRight));
	poly.Add(new Point(topLeft.GetX(), bottomRight.GetY()));

	SetPolygon(poly);

	DeletePolygon(poly);
}

IMPLEMENT_SERIAL(Sh_Triangle, CObject, 1)
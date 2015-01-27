#include "stdafx.h"
#include "Sh_Diamond.h"

Sh_Diamond::Sh_Diamond(const Color &color, ShapeType type, int polygonSize) 
	: Sh_Rectangle(color, type, polygonSize) { }

Sh_Diamond::Sh_Diamond(const Sh_Diamond &other)
	: Sh_Rectangle(other) { }

Shape *Sh_Diamond::Clone() const
{
	return new Sh_Diamond(*this);
}

void Sh_Diamond::BuildPolygon()
{
	Point *poly = GetPolygon();
	Point topLeft = GetTopLeft();
	Point bottomRight = GetBottomRight();

	poly[0] = Point((topLeft.GetX() + bottomRight.GetX()) / 2,  topLeft.GetY()                          );
	poly[1] = Point( bottomRight.GetX()                      , (topLeft.GetY() + bottomRight.GetY()) / 2);
	poly[2] = Point((topLeft.GetX() + bottomRight.GetX()) / 2,  bottomRight.GetY()                      );
	poly[3] = Point( topLeft.GetX()                          , (topLeft.GetY() + bottomRight.GetY()) / 2);
}
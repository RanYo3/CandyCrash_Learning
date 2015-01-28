#include "stdafx.h"
#include "Sh_Diamond.h"

IMPLEMENT_SERIAL(Sh_Diamond, CObject, 1)

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
	CTypedPtrArray<CObArray, Point *> poly;
	Point topLeft = GetTopLeft();
	Point bottomRight = GetBottomRight();

	poly.Add(new Point((topLeft.GetX() + bottomRight.GetX()) / 2,  topLeft.GetY()                          ));
	poly.Add(new Point( bottomRight.GetX()                      , (topLeft.GetY() + bottomRight.GetY()) / 2));
	poly.Add(new Point((topLeft.GetX() + bottomRight.GetX()) / 2,  bottomRight.GetY()                      ));
	poly.Add(new Point( topLeft.GetX()                          , (topLeft.GetY() + bottomRight.GetY()) / 2));

	SetPolygon(poly);

	DeletePolygon(poly);
}
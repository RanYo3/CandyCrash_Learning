#include "stdafx.h"
#include "Sh_Ellipse.h"

IMPLEMENT_SERIAL(Sh_Ellipse, CObject, 1)

Sh_Ellipse::Sh_Ellipse(const Color &color, ShapeType type, int polygonSize)
	: Shape(color, type, polygonSize) { }

Sh_Ellipse::Sh_Ellipse(const Sh_Ellipse &other)
	: Shape(other) { }

Shape *Sh_Ellipse::Clone() const
{
	return new Sh_Ellipse(*this);
}

void Sh_Ellipse::BuildPolygon()
{
	CTypedPtrArray<CObArray, Point *> poly;

	poly.Add(new Point(GetTopLeft()));
	poly.Add(new Point(GetBottomRight()));

	SetPolygon(poly);

	DeletePolygon(poly);
}
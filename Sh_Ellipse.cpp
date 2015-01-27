#include "stdafx.h"
#include "Sh_Ellipse.h"

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
	Point *poly = GetPolygon();

	poly[0] = GetTopLeft();
	poly[1] = GetBottomRight();
}
#include "stdafx.h"
#include "Sh_Ellipse.h"

Sh_Ellipse::Sh_Ellipse()
	: Shape(ST_Ellipse)
{
	InitPolygon();
}

Sh_Ellipse::~Sh_Ellipse()
{
}

Sh_Ellipse::Sh_Ellipse(Color color)
	: Shape(ST_Ellipse, color)
{
	InitPolygon();
}

Sh_Ellipse::Sh_Ellipse(const Point &topLeft, const Point &bottomRight)
	: Shape(topLeft, bottomRight, ST_Ellipse)
{
	InitPolygon();
}

Sh_Ellipse::Sh_Ellipse(const Point &topLeft, const Point &bottomRight, Color color)
	: Shape(topLeft, bottomRight, ST_Ellipse, color)
{
	InitPolygon();
}

Sh_Ellipse::Sh_Ellipse(const Sh_Ellipse &other)
	: Shape(other)
{
	InitPolygon();
}

const Sh_Ellipse &Sh_Ellipse::operator=(const Sh_Ellipse &other)
{
	if (&other != this)
	{
		Shape::operator=(other);
		InitPolygon();
	}

	return *this;
}

int Sh_Ellipse::GetPolygonSize() const
{
	return ELPS_SIZE;
}

Shape *Sh_Ellipse::Clone() const
{
	return new Sh_Ellipse(*this);
}

Point *Sh_Ellipse::CreatePolygon() const
{
	Point *poly = new Point[ELPS_SIZE];

	poly[0] = GetTopLeft();
	poly[1] = GetBottomRight();

	return poly;
}
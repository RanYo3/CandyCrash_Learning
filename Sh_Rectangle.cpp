#include "stdafx.h"
#include "Sh_Rectangle.h"

Sh_Rectangle::Sh_Rectangle()
	: Shape(ST_Rectangle)
{
	InitPolygon();
}

Sh_Rectangle::~Sh_Rectangle()
{
}

Sh_Rectangle::Sh_Rectangle(Color color)
	: Shape(ST_Rectangle, color)
{
	InitPolygon();
}

Sh_Rectangle::Sh_Rectangle(const Point &topLeft, const Point &bottomRight)
	: Shape(topLeft, bottomRight, ST_Rectangle)
{
	InitPolygon();
}

Sh_Rectangle::Sh_Rectangle(const Point &topLeft, const Point &bottomRight, Color color)
	: Shape(topLeft, bottomRight, ST_Rectangle, color)
{
	InitPolygon();
}

Sh_Rectangle::Sh_Rectangle(const Sh_Rectangle &other)
	: Shape(other)
{
	InitPolygon();
}

const Sh_Rectangle &Sh_Rectangle::operator=(const Sh_Rectangle &other)
{
	if (&other != this)
	{
		Shape::operator=(other);
		InitPolygon();
	}

	return *this;
}

int Sh_Rectangle::GetPolygonSize() const
{
	return RECT_SIZE;
}

Shape *Sh_Rectangle::Clone() const
{
	return new Sh_Rectangle(*this);
}

Point *Sh_Rectangle::CreatePolygon() const
{
	Point *poly = new Point[RECT_SIZE];

	poly[0] = GetTopLeft();
	poly[1] = GetBottomRight();

	return poly;
}
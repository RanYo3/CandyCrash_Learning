#include "stdafx.h"
#include "Sh_Triangle.h"

Sh_Triangle::Sh_Triangle()
	: Shape(ST_Triangle)
{
	InitPolygon();
}

Sh_Triangle::~Sh_Triangle()
{
}

Sh_Triangle::Sh_Triangle(Color color)
	: Shape(ST_Triangle, color)
{
	InitPolygon();
}

Sh_Triangle::Sh_Triangle(const Point &topLeft, const Point &bottomRight)
	: Shape(topLeft, bottomRight, ST_Triangle)
{
	InitPolygon();
}

Sh_Triangle::Sh_Triangle(const Point &topLeft, const Point &bottomRight, Color color)
	: Shape(topLeft, bottomRight, ST_Triangle, color)
{
	InitPolygon();
}

Sh_Triangle::Sh_Triangle(const Sh_Triangle &other)
	: Shape(other)
{
	InitPolygon();
}

const Sh_Triangle &Sh_Triangle::operator=(const Sh_Triangle &other)
{
	if (&other != this)
	{
		Shape::operator=(other);
		InitPolygon();
	}

	return *this;
}

int Sh_Triangle::GetPolygonSize() const
{
	return TRNG_SIZE;
}

Shape *Sh_Triangle::Clone() const
{
	return new Sh_Triangle(*this);
}

Point *Sh_Triangle::CreatePolygon() const
{
	Point *poly = new Point[TRNG_SIZE];
	Point topLeft = GetTopLeft();
	Point bottomRight = GetBottomRight();

	poly[0] = Point((topLeft.GetX() + bottomRight.GetX()) / 2, topLeft.GetY());
	poly[1] = bottomRight;
	poly[2] = Point(topLeft.GetX(), bottomRight.GetY());

	return poly;
}
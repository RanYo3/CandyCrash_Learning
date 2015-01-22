#include "stdafx.h"
#include "Sh_Minus.h"

Sh_Minus::Sh_Minus()
	: Shape(ST_Triangle)
{
	InitPolygon();
}

Sh_Minus::~Sh_Minus()
{
}

Sh_Minus::Sh_Minus(Color color)
	: Shape(ST_Triangle, color)
{
	InitPolygon();
}

Sh_Minus::Sh_Minus(const Point &topLeft, const Point &bottomRight)
	: Shape(topLeft, bottomRight, ST_Triangle)
{
	InitPolygon();
}

Sh_Minus::Sh_Minus(const Point &topLeft, const Point &bottomRight, Color color)
	: Shape(topLeft, bottomRight, ST_Triangle, color)
{
	InitPolygon();
}

Sh_Minus::Sh_Minus(const Sh_Minus &other)
	: Shape(other)
{
	InitPolygon();
}

const Sh_Minus &Sh_Minus::operator=(const Sh_Minus &other)
{
	if (&other != this)
	{
		Shape::operator=(other);
		InitPolygon();
	}

	return *this;
}

int Sh_Minus::GetPolygonSize() const
{
	return MINUS_SIZE;
}

Shape *Sh_Minus::Clone() const
{
	return new Sh_Minus(*this);
}

Point *Sh_Minus::CreatePolygon() const
{
	Point *poly = new Point[MINUS_SIZE];
	Point topLeft = GetTopLeft();
	Point bottomRight = GetBottomRight();

	double partY = (double)(bottomRight.GetY() - topLeft.GetY()) / PART_SIZE;

	poly[0] = Point(bottomRight.GetX(), topLeft.GetY()     + partY);
	poly[1] = Point(bottomRight.GetX(), bottomRight.GetY() - partY);
	poly[2] = Point(topLeft.GetX()    , bottomRight.GetY() - partY);
	poly[3] = Point(topLeft.GetX()    , topLeft.GetY()     + partY);

	return poly;
}
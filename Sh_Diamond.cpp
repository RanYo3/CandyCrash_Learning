#include "stdafx.h"
#include "Sh_Diamond.h"

Sh_Diamond::Sh_Diamond()
	: Shape(ST_Diamond)
{
	InitPolygon();
}

Sh_Diamond::~Sh_Diamond()
{
}

Sh_Diamond::Sh_Diamond(Color color)
	: Shape(ST_Diamond, color)
{
	InitPolygon();
}

Sh_Diamond::Sh_Diamond(const Point &topLeft, const Point &bottomRight)
	: Shape(topLeft, bottomRight, ST_Diamond)
{
	InitPolygon();
}

Sh_Diamond::Sh_Diamond(const Point &topLeft, const Point &bottomRight, Color color)
	: Shape(topLeft, bottomRight, ST_Diamond, color)
{
	InitPolygon();
}

Sh_Diamond::Sh_Diamond(const Sh_Diamond &other)
	: Shape(other)
{
	InitPolygon();
}

const Sh_Diamond &Sh_Diamond::operator=(const Sh_Diamond &other)
{
	if (&other != this)
	{
		Shape::operator=(other);
		InitPolygon();
	}

	return *this;
}

int Sh_Diamond::GetPolygonSize() const
{
	return DMND_SIZE;
}

Shape *Sh_Diamond::Clone() const
{
	return new Sh_Diamond(*this);
}

Point *Sh_Diamond::CreatePolygon() const
{
	Point *poly = new Point[DMND_SIZE];
	Point topLeft = GetTopLeft();
	Point bottomRight = GetBottomRight();

	poly[0] = Point((topLeft.GetX() + bottomRight.GetX()) / 2,  topLeft.GetY()                          );
	poly[1] = Point( bottomRight.GetX()                      , (topLeft.GetY() + bottomRight.GetY()) / 2);
	poly[2] = Point((topLeft.GetX() + bottomRight.GetX()) / 2,  bottomRight.GetY()                      );
	poly[3] = Point( topLeft.GetX()                          , (topLeft.GetY() + bottomRight.GetY()) / 2);

	return poly;
}
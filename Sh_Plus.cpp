#include "stdafx.h"
#include "Sh_Plus.h"

Sh_Plus::Sh_Plus()
	: Shape(ST_Triangle)
{
	InitPolygon();
}

Sh_Plus::~Sh_Plus()
{
}

Sh_Plus::Sh_Plus(Color color)
	: Shape(ST_Triangle, color)
{
	InitPolygon();
}

Sh_Plus::Sh_Plus(const Point &topLeft, const Point &bottomRight)
	: Shape(topLeft, bottomRight, ST_Triangle)
{
	InitPolygon();
}

Sh_Plus::Sh_Plus(const Point &topLeft, const Point &bottomRight, Color color)
	: Shape(topLeft, bottomRight, ST_Triangle, color)
{
	InitPolygon();
}

Sh_Plus::Sh_Plus(const Sh_Plus &other)
	: Shape(other)
{
	InitPolygon();
}

const Sh_Plus &Sh_Plus::operator=(const Sh_Plus &other)
{
	if (&other != this)
	{
		Shape::operator=(other);
		InitPolygon();
	}

	return *this;
}

int Sh_Plus::GetPolygonSize() const
{
	return PLUS_SIZE;
}

Shape *Sh_Plus::Clone() const
{
	return new Sh_Plus(*this);
}

Point *Sh_Plus::CreatePolygon() const
{
	Point *poly = new Point[PLUS_SIZE];
	Point topLeft = GetTopLeft();
	Point bottomRight = GetBottomRight();

	double partX = (double)(bottomRight.GetX() - topLeft.GetX()) / PART_SIZE;
	double partY = (double)(bottomRight.GetY() - topLeft.GetY()) / PART_SIZE;

	poly[0]  = Point(topLeft.GetX()     + partX, topLeft.GetY()            );
	poly[1]  = Point(bottomRight.GetX() - partX, topLeft.GetY()            );
	poly[2]  = Point(bottomRight.GetX() - partX, topLeft.GetY()     + partY);
	poly[3]  = Point(bottomRight.GetX()        , topLeft.GetY()     + partY);
	poly[4]  = Point(bottomRight.GetX()        , bottomRight.GetY() - partY);
	poly[5]  = Point(bottomRight.GetX() - partX, bottomRight.GetY() - partY);
	poly[6]  = Point(bottomRight.GetX() - partX, bottomRight.GetY()        );
	poly[7]  = Point(topLeft.GetX()     + partX, bottomRight.GetY()        );
	poly[8]  = Point(topLeft.GetX()     + partX, bottomRight.GetY() - partY);
	poly[9]  = Point(topLeft.GetX()            , bottomRight.GetY() - partY);
	poly[10] = Point(topLeft.GetX()            , topLeft.GetY()     + partY);
	poly[11] = Point(topLeft.GetX()     + partX, topLeft.GetY()     + partY);

	return poly;
}
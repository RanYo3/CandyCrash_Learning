#include "stdafx.h"
#include "Sh_Star.h"

Sh_Star::Sh_Star()
	: Shape(ST_Star)
{
	InitPolygon();
}

Sh_Star::~Sh_Star()
{
}

Sh_Star::Sh_Star(Color color)
	: Shape(ST_Star, color)
{
	InitPolygon();
}

Sh_Star::Sh_Star(const Point &topLeft, const Point &bottomRight)
	: Shape(topLeft, bottomRight, ST_Star)
{
	InitPolygon();
}

Sh_Star::Sh_Star(const Point &topLeft, const Point &bottomRight, Color color)
	: Shape(topLeft, bottomRight, ST_Star, color)
{
	InitPolygon();
}

Sh_Star::Sh_Star(const Sh_Star &other)
	: Shape(other)
{
	InitPolygon();
}

const Sh_Star &Sh_Star::operator=(const Sh_Star &other)
{
	if (&other != this)
	{
		Shape::operator=(other);
		InitPolygon();
	}

	return *this;
}

int Sh_Star::GetPolygonSize() const
{
	return STAR_SIZE;
}

Shape *Sh_Star::Clone() const
{
	return new Sh_Star(*this);
}

Point *Sh_Star::CreatePolygon() const
{
	Point *poly = new Point[STAR_SIZE];
	Point topLeft = GetTopLeft();
	Point bottomRight = GetBottomRight();

	int cellSizeX = bottomRight.GetX() - topLeft.GetX();
	int cellSizeY = bottomRight.GetY() - topLeft.GetY();

	int partX = (int)((double)cellSizeX * PART_HORZ_SIZE);
	int partY = (int)((double)cellSizeY * PART_VERT_SIZE);

	poly[0] = Point(topLeft.GetX(),                 topLeft.GetY()     + partY);
	poly[1] = Point(bottomRight.GetX(),             topLeft.GetY()     + partY);
	poly[2] = Point(topLeft.GetX() + partX,         bottomRight.GetY()        );
	poly[3] = Point(topLeft.GetX() + cellSizeX / 2, topLeft.GetY()            );
	poly[4] = Point(bottomRight.GetX() - partX,     bottomRight.GetY()        );

	return poly;
}
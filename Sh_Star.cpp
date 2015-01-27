#include "stdafx.h"
#include "Sh_Star.h"

Sh_Star::Sh_Star(Color color, ShapeType type, int polygonSize) 
	: Sh_X(color, type, polygonSize) { }

Sh_Star::Sh_Star(const Sh_Star &other)
	: Sh_X(other) { }

Shape *Sh_Star::Clone() const
{
	return new Sh_Star(*this);
}

void Sh_Star::BuildPolygon()
{
	Point *poly = GetPolygon();
	Point topLeft = GetTopLeft();
	Point bottomRight = GetBottomRight();

	int cellSizeX = bottomRight.GetX() - topLeft.GetX();
	int cellSizeY = bottomRight.GetY() - topLeft.GetY();

	int partX = (int)((double)cellSizeX * PART_HORZ_SIZE);
	int partY = (int)((double)cellSizeY * PART_VERT_SIZE);

	poly[0] = Point(topLeft.GetX()                    , topLeft.GetY()     + partY);
	poly[1] = Point(bottomRight.GetX()                , topLeft.GetY()     + partY);
	poly[2] = Point(topLeft.GetX()     + partX        , bottomRight.GetY()        );
	poly[3] = Point(topLeft.GetX()     + cellSizeX / 2, topLeft.GetY()            );
	poly[4] = Point(bottomRight.GetX() - partX        , bottomRight.GetY()        );
}
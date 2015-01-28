#include "stdafx.h"
#include "Sh_Star.h"

Sh_Star::Sh_Star(const Color &color, ShapeType type, int polygonSize) 
	: Sh_X(color, type, polygonSize) { }

Sh_Star::Sh_Star(const Sh_Star &other)
	: Sh_X(other) { }

Shape *Sh_Star::Clone() const
{
	return new Sh_Star(*this);
}

void Sh_Star::BuildPolygon()
{
	CTypedPtrArray<CObArray, Point *> poly;
	Point topLeft = GetTopLeft();
	Point bottomRight = GetBottomRight();

	int cellSizeX = bottomRight.GetX() - topLeft.GetX();
	int cellSizeY = bottomRight.GetY() - topLeft.GetY();

	int partX = (int)((double)cellSizeX * PART_HORZ_SIZE);
	int partY = (int)((double)cellSizeY * PART_VERT_SIZE);

	poly.Add(new Point(topLeft.GetX()                    , topLeft.GetY()     + partY));
	poly.Add(new Point(bottomRight.GetX()                , topLeft.GetY()     + partY));
	poly.Add(new Point(topLeft.GetX()     + partX        , bottomRight.GetY()        ));
	poly.Add(new Point(topLeft.GetX()     + cellSizeX / 2, topLeft.GetY()            ));
	poly.Add(new Point(bottomRight.GetX() - partX        , bottomRight.GetY()        ));

	SetPolygon(poly);

	DeletePolygon(poly);
}

IMPLEMENT_SERIAL(Sh_Star, CObject, 1)
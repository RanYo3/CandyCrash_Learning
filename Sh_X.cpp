#include "stdafx.h"
#include "Sh_X.h"

Sh_X::Sh_X(const Color &color, ShapeType type, int polygonSize) 
	: Sh_Plus(color, type, polygonSize) { }

Sh_X::Sh_X(const Sh_X &other)
	: Sh_Plus(other) { }

Shape *Sh_X::Clone() const
{
	return new Sh_X(*this);
}

void Sh_X::BuildPolygon()
{
	CTypedPtrArray<CObArray, Point *> poly;
	Point topLeft = GetTopLeft();
	Point bottomRight = GetBottomRight();

	int cellSizeX = bottomRight.GetX() - topLeft.GetX();
	int cellSizeY = bottomRight.GetY() - topLeft.GetY();

	int partX = (int)((double)cellSizeX / PART_SIZE);
	int partY = (int)((double)cellSizeY / PART_SIZE);

	int middleX = cellSizeX / 2;
	int middleY = cellSizeY / 2;

	int semiMiddleX = (int)((double)cellSizeX / 2 - (double)partX / 5 * 3);
	int semiMiddleY = (int)((double)cellSizeY / 2 - (double)partY / 5 * 3);

	poly.Add(new Point(topLeft.GetX()                  , topLeft.GetY()                  ));
	poly.Add(new Point(topLeft.GetX()     + partX      , topLeft.GetY()                  ));
	poly.Add(new Point(topLeft.GetX()     + middleX    , topLeft.GetY()     + semiMiddleY));
	poly.Add(new Point(bottomRight.GetX() - partX      , topLeft.GetY()                  ));
	poly.Add(new Point(bottomRight.GetX()              , topLeft.GetY()                  ));
	poly.Add(new Point(bottomRight.GetX() - semiMiddleX, topLeft.GetY()     + middleY    ));
	poly.Add(new Point(bottomRight.GetX()              , bottomRight.GetY()              ));
	poly.Add(new Point(bottomRight.GetX() - partX      , bottomRight.GetY()              ));
	poly.Add(new Point(topLeft.GetX()     + middleX    , bottomRight.GetY() - semiMiddleY));
	poly.Add(new Point(topLeft.GetX()     + partX      , bottomRight.GetY()              ));
	poly.Add(new Point(topLeft.GetX()                  , bottomRight.GetY()              ));
	poly.Add(new Point(topLeft.GetX()     + semiMiddleX, topLeft.GetY()     + middleY    ));

	SetPolygon(poly);

	DeletePolygon(poly);
}

IMPLEMENT_SERIAL(Sh_X, CObject, 1)
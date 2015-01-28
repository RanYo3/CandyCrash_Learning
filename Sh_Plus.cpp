#include "stdafx.h"
#include "Sh_Plus.h"

Sh_Plus::Sh_Plus(const Color &color, ShapeType type, int polygonSize) 
	: Sh_Minus(color, type, polygonSize) { }

Sh_Plus::Sh_Plus(const Sh_Plus &other)
	: Sh_Minus(other) { }

Shape *Sh_Plus::Clone() const
{
	return new Sh_Plus(*this);
}

void Sh_Plus::BuildPolygon()
{
	CTypedPtrArray<CObArray, Point *> poly;
	Point topLeft = GetTopLeft();
	Point bottomRight = GetBottomRight();

	int partX = (int)((double)(bottomRight.GetX() - topLeft.GetX()) / PART_SIZE);
	int partY = (int)((double)(bottomRight.GetY() - topLeft.GetY()) / PART_SIZE);

	poly.Add(new Point(topLeft.GetX()     + partX, topLeft.GetY()            ));
	poly.Add(new Point(bottomRight.GetX() - partX, topLeft.GetY()            ));
	poly.Add(new Point(bottomRight.GetX() - partX, topLeft.GetY()     + partY));
	poly.Add(new Point(bottomRight.GetX()        , topLeft.GetY()     + partY));
	poly.Add(new Point(bottomRight.GetX()        , bottomRight.GetY() - partY));
	poly.Add(new Point(bottomRight.GetX() - partX, bottomRight.GetY() - partY));
	poly.Add(new Point(bottomRight.GetX() - partX, bottomRight.GetY()        ));
	poly.Add(new Point(topLeft.GetX()     + partX, bottomRight.GetY()        ));
	poly.Add(new Point(topLeft.GetX()     + partX, bottomRight.GetY() - partY));
	poly.Add(new Point(topLeft.GetX()            , bottomRight.GetY() - partY));
	poly.Add(new Point(topLeft.GetX()            , topLeft.GetY()     + partY));
	poly.Add(new Point(topLeft.GetX()     + partX, topLeft.GetY()     + partY));

	SetPolygon(poly);

	DeletePolygon(poly);
}

IMPLEMENT_SERIAL(Sh_Plus, CObject, 1)
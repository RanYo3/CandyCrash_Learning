#include "stdafx.h"
#include "Sh_Plus.h"

Sh_Plus::Sh_Plus(Color color, ShapeType type, int polygonSize) 
	: Sh_Minus(color, type, polygonSize) { }

Sh_Plus::Sh_Plus(const Sh_Plus &other)
	: Sh_Minus(other) { }

Shape *Sh_Plus::Clone() const
{
	return new Sh_Plus(*this);
}

void Sh_Plus::BuildPolygon()
{
	Point *poly = GetPolygon();
	Point topLeft = GetTopLeft();
	Point bottomRight = GetBottomRight();

	int partX = (int)((double)(bottomRight.GetX() - topLeft.GetX()) / PART_SIZE);
	int partY = (int)((double)(bottomRight.GetY() - topLeft.GetY()) / PART_SIZE);

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
}
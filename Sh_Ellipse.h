#pragma once

#include "Shape.h"
#include "Point.h"
#include "Color.h"

#define ELPS_SIZE 2

class Sh_Ellipse : public Shape
{
public:
	Sh_Ellipse(Color color = BLACK, ShapeType type = ST_Ellipse, int polygonSize = ELPS_SIZE);
	Sh_Ellipse(const Sh_Ellipse &other);

	virtual Shape *Clone() const;
	virtual void BuildPolygon();
};
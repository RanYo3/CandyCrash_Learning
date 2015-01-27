#pragma once

#include "Shape.h"
#include "Point.h"
#include "Color.h"
#include "Sh_Ellipse.h"

#define RECT_SIZE 2

class Sh_Rectangle : public Sh_Ellipse
{
public:
	Sh_Rectangle(const Color &color = BLACK, ShapeType type = ST_Rectangle, int polygonSize = RECT_SIZE);
	Sh_Rectangle(const Sh_Rectangle &other);
	
	virtual Shape *Clone() const;
};
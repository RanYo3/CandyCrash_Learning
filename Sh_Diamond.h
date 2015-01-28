#pragma once

#include "Shape.h"
#include "Point.h"
#include "Color.h"
#include "Sh_Rectangle.h"

#define DMND_SIZE 4

class Sh_Diamond : public Sh_Rectangle
{
	DECLARE_SERIAL (Sh_Diamond)

public:
	Sh_Diamond(Color color = BLACK, ShapeType type = ST_Diamond, int polygonSize = DMND_SIZE);
	Sh_Diamond(const Sh_Diamond &other);
	
	virtual Shape *Clone() const;
	virtual void BuildPolygon();
};
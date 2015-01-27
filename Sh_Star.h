#pragma once

#include "Shape.h"
#include "Point.h"
#include "Color.h"
#include "Sh_X.h"

#define STAR_SIZE 5
#define PART_VERT_SIZE 9.0 / 23.5
#define PART_HORZ_SIZE 4.625 / 24.5

class Sh_Star : public Sh_X
{
public:
	Sh_Star(const Color &color = BLACK, ShapeType type = ST_Star, int polygonSize = STAR_SIZE);
	Sh_Star(const Sh_Star &other);
	
	virtual Shape *Clone() const;

protected:
	virtual void BuildPolygon();
};
#pragma once

#include "Shape.h"
#include "Point.h"
#include "Color.h"
#include "Sh_Minus.h"

#define PLUS_SIZE 12
#define PART_SIZE 3

class Sh_Plus : public Sh_Minus
{
	DECLARE_SERIAL (Sh_Plus)

public:
	Sh_Plus(const Color &color = BLACK, ShapeType type = ST_Plus, int polygonSize = PLUS_SIZE);
	Sh_Plus(const Sh_Plus &other);
	
	virtual Shape *Clone() const;
	virtual void BuildPolygon();
};
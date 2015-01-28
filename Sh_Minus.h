#pragma once

#include "Shape.h"
#include "Point.h"
#include "Color.h"
#include "Sh_Triangle.h"

#define MINUS_SIZE 4
#define PART_SIZE 3

class Sh_Minus : public Sh_Triangle
{
	DECLARE_SERIAL (Sh_Minus)

public:
	Sh_Minus(Color color = BLACK, ShapeType type = ST_Minus, int polygonSize = MINUS_SIZE);
	Sh_Minus(const Sh_Minus &other);
	
	virtual Shape *Clone() const;
	virtual void BuildPolygon();
};
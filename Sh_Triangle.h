#pragma once

#include "Shape.h"
#include "Point.h"
#include "Color.h"
#include "Sh_Diamond.h"

#define TRNG_SIZE 3

class Sh_Triangle : public Sh_Diamond
{
public:
	Sh_Triangle(Color color = BLACK, ShapeType type = ST_Triangle, int polygonSize = TRNG_SIZE);
	Sh_Triangle(const Sh_Triangle &other);
	
	virtual Shape *Clone() const;
	virtual void BuildPolygon();
};
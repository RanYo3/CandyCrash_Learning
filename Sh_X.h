#pragma once

#include "Shape.h"
#include "Point.h"
#include "Color.h"
#include "Sh_Plus.h"

#define SHX_SIZE 12
#define PART_SIZE 3

class Sh_X : public Sh_Plus
{
	DECLARE_SERIAL (Sh_X)

public:
	Sh_X(Color color = BLACK, ShapeType type = ST_X, int polygonSize = SHX_SIZE);
	Sh_X(const Sh_X &other);
	
	virtual Shape *Clone() const;

protected:
	virtual void BuildPolygon();
};
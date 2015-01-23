#pragma once

#include "Shape.h"
#include "Point.h"
#include "Color.h"

#define STAR_SIZE 5
#define PART_VERT_SIZE 9.0 / 23.5
#define PART_HORZ_SIZE 4.625 / 24.5

class Sh_Star : public Shape
{
public:
	Sh_Star();
	virtual ~Sh_Star();

	Sh_Star(Color color);
	Sh_Star(const Point &topLeft, const Point &bottomRight);
	Sh_Star(const Point &topLeft, const Point &bottomRight, Color color);
	Sh_Star(const Sh_Star &other);
	const Sh_Star &operator=(const Sh_Star &other);

	virtual int GetPolygonSize() const;

	virtual Shape *Clone() const;

private:
	virtual Point *CreatePolygon() const;
};
#pragma once

#include "Shape.h"
#include "Point.h"
#include "Color.h"

#define SHX_SIZE 12
#define PART_SIZE 3

class Sh_X : public Shape
{
public:
	Sh_X();
	virtual ~Sh_X();

	Sh_X(Color color);
	Sh_X(const Point &topLeft, const Point &bottomRight);
	Sh_X(const Point &topLeft, const Point &bottomRight, Color color);
	Sh_X(const Sh_X &other);
	const Sh_X &operator=(const Sh_X &other);

	virtual int GetPolygonSize() const;

	virtual Shape *Clone() const;

private:
	virtual Point *CreatePolygon() const;
};
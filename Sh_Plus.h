#pragma once

#include "Shape.h"
#include "Point.h"
#include "Color.h"

#define PLUS_SIZE 12
#define PART_SIZE 3

class Sh_Plus : public Shape
{
public:
	Sh_Plus();
	virtual ~Sh_Plus();

	Sh_Plus(Color color);
	Sh_Plus(const Point &topLeft, const Point &bottomRight);
	Sh_Plus(const Point &topLeft, const Point &bottomRight, Color color);
	Sh_Plus(const Sh_Plus &other);
	const Sh_Plus &operator=(const Sh_Plus &other);

	virtual int GetPolygonSize() const;

	virtual Shape *Clone() const;

private:
	virtual Point *CreatePolygon() const;
};
#pragma once

#include "Shape.h"
#include "Point.h"
#include "Color.h"

#define TRNG_SIZE 3

class Sh_Triangle : public Shape
{
public:
	Sh_Triangle();
	virtual ~Sh_Triangle();

	Sh_Triangle(Color color);
	Sh_Triangle(const Point &topLeft, const Point &bottomRight);
	Sh_Triangle(const Point &topLeft, const Point &bottomRight, Color color);
	Sh_Triangle(const Sh_Triangle &other);
	const Sh_Triangle &operator=(const Sh_Triangle &other);

	virtual int GetPolygonSize() const;

	virtual Shape *Clone() const;

private:
	virtual Point *CreatePolygon() const;
};
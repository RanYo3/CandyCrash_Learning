#pragma once

#include "Shape.h"
#include "Point.h"
#include "Color.h"

#define RECT_SIZE 2

class Sh_Rectangle : public Shape
{
public:
	Sh_Rectangle();
	virtual ~Sh_Rectangle();

	Sh_Rectangle(Color color);
	Sh_Rectangle(const Point &topLeft, const Point &bottomRight);
	Sh_Rectangle(const Point &topLeft, const Point &bottomRight, Color color);
	Sh_Rectangle(const Sh_Rectangle &other);
	const Sh_Rectangle &operator=(const Sh_Rectangle &other);

	virtual int GetPolygonSize() const;

	virtual Shape *Clone() const;

private:
	virtual Point *CreatePolygon() const;
};
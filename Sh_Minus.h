#pragma once

#include "Shape.h"
#include "Point.h"
#include "Color.h"

#define MINUS_SIZE 4
#define PART_SIZE 3

class Sh_Minus : public Shape
{
public:
	Sh_Minus();
	virtual ~Sh_Minus();

	Sh_Minus(Color color);
	Sh_Minus(const Point &topLeft, const Point &bottomRight);
	Sh_Minus(const Point &topLeft, const Point &bottomRight, Color color);
	Sh_Minus(const Sh_Minus &other);
	const Sh_Minus &operator=(const Sh_Minus &other);

	virtual int GetPolygonSize() const;

	virtual Shape *Clone() const;

private:
	virtual Point *CreatePolygon() const;
};
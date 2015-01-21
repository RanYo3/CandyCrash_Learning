#pragma once

#include "Shape.h"
#include "Point.h"
#include "Color.h"

#define ELPS_SIZE 2

class Sh_Ellipse : public Shape
{
public:
	Sh_Ellipse();
	virtual ~Sh_Ellipse();

	Sh_Ellipse(Color color);
	Sh_Ellipse(const Point &topLeft, const Point &bottomRight);
	Sh_Ellipse(const Point &topLeft, const Point &bottomRight, Color color);
	Sh_Ellipse(const Sh_Ellipse &other);
	const Sh_Ellipse &operator=(const Sh_Ellipse &other);

	virtual int GetPolygonSize() const;

	virtual Shape *Clone() const;

private:
	virtual Point *CreatePolygon() const;
};
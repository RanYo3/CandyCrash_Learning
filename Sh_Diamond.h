#pragma once

#include "Shape.h"
#include "Point.h"
#include "Color.h"

#define DMND_SIZE 4

class Sh_Diamond : public Shape
{
public:
	Sh_Diamond();
	virtual ~Sh_Diamond();

	Sh_Diamond(Color color);
	Sh_Diamond(const Point &topLeft, const Point &bottomRight);
	Sh_Diamond(const Point &topLeft, const Point &bottomRight, Color color);
	Sh_Diamond(const Sh_Diamond &other);
	const Sh_Diamond &operator=(const Sh_Diamond &other);

	virtual int GetPolygonSize() const;

	virtual Shape *Clone() const;

private:
	virtual Point *CreatePolygon() const;
};
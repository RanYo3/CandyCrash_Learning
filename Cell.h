#pragma once

#include "Point.h"
#include "Shape.h"

class Cell
{
public:
	Cell();
	~Cell();

	Cell(Shape *shape, Point location);
	Cell(const Cell &other);
	const Cell &operator=(const Cell &other);

	Shape *GetShape() const;
	const Point &GetLocation() const;

	void SetLocation(const Point &location);

	void Select(bool isSelected);

private:
	Shape *m_Shape;
	Point m_Location;
	bool m_IsSelected;
};
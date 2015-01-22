#pragma once

#include "Point.h"
#include "Shape.h"

#define MARGIN 3

class Cell
{
public:
	Cell();
	~Cell();

	Cell(Shape *shape, const Point &topLeft, const Point &bottomRight);
	Cell(const Cell &other);
	const Cell &operator=(const Cell &other);

	Shape *GetShape() const;
	const Point &GetTopLeft() const;
	const Point &GetBottomRight() const;
	bool IsSelected() const;

	void SetTopLeft(const Point &topLeft);
	void SetBottomRight(const Point &bottomRight);

	void Select(bool isSelected);

private:
	Shape *m_Shape;
	Point m_TopLeft;
	Point m_BottomRight;
	bool m_IsSelected;
};
#pragma once

#include "Point.h"
#include "Shape.h"

#include <afx.h>

#define MARGIN 10

class Cell : public CObject
{
	DECLARE_SERIAL(Cell)
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
	bool IsInSequence() const; 

	void SetShape(Shape *shape);
	void SetTopLeft(const Point &topLeft);
	void SetBottomRight(const Point &bottomRight);

	void Select(bool isSelected);
	void MarkAsSequence();

	void Serialize(CArchive& ar);

private:
	Shape *m_Shape;
	Point *m_TopLeft;
	Point *m_BottomRight;
	bool m_IsSelected;
	bool m_IsInSequence;
};
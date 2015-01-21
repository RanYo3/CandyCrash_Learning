#pragma once

#include "Color.h"
#include "Point.h"

#define NULL 0

enum ShapeType { ST_Rectangle, ST_Ellipse, ST_Triangle, ST_Diamond, ST_Unknown };

class Shape
{
public:
	Shape(ShapeType type = ST_Unknown, Color color = BLACK);
	virtual ~Shape();

	Shape(const Point &topLeft, const Point &bottomRight, ShapeType type, Color color = BLACK);
	Shape(const Shape &other);
	const Shape &operator=(const Shape &other);

	bool operator==(const Shape &other) const;
	bool operator!=(const Shape &other) const;

	const Point &GetTopLeft() const;
	const Point &GetBottomRight() const;
	const Color &GetColor() const;
	ShapeType GetType() const;

	void SetTopLeft(const Point &topLeft);
	void SetBottomRight(const Point &bottomRight);
	void SetColor(const Color &color);

	virtual Point *GetPolygon() const;

	virtual int GetPolygonSize() const = 0;

	virtual Shape *Clone() const = 0;

protected:
	void InitPolygon();

	virtual Point *CreatePolygon() const = 0;

private:
	ShapeType m_Type;
	Color m_Color;
	Point m_TopLeft;
	Point m_BottomRight;
	Point *m_Polygon;
};
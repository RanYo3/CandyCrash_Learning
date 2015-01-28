#pragma once

#include "Color.h"
#include "Point.h"

#define NULL 0
#define NUM_OF_SHAPES 8

enum ShapeType { ST_Rectangle, ST_Ellipse, ST_Triangle, ST_Diamond, ST_Plus, ST_Minus, ST_Star, ST_X, ST_Unknown };

class Shape : public CObject
{
public:
	Shape(const Color &color = BLACK, ShapeType type = ST_Unknown, int polygonSize = 0);
	virtual ~Shape();

	Shape(const Shape &other);
	const Shape &operator=(const Shape &other);

	bool operator==(const Shape &other) const;
	bool operator!=(const Shape &other) const;

	const Color &GetColor() const;
	ShapeType GetType() const;

	const Point &GetTopLeft() const;
	const Point &GetBottomRight() const;
	
	void SetColor(const Color &color);
	void SetTopLeft(const Point &topLeft);
	void SetBottomRight(const Point &bottomRight);
	void Serialize(CArchive& archive);

	int GetPolygonSize() const;

	Point *GetPolygon() const;
	
	virtual Shape *Clone() const = 0;

	virtual void BuildPolygon() = 0;

private:
	Color m_Color;
	ShapeType m_Type;

	int m_PolygonSize;
	Point *m_Polygon;

	Point m_TopLeft;
	Point m_BottomRight;
};
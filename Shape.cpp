#include "stdafx.h"
#include "Shape.h"

Shape::Shape(Color color, ShapeType type, int polygonSize)
	: m_Color(color), m_Type(type), m_PolygonSize(polygonSize), m_TopLeft(), m_BottomRight()
{
	m_Polygon = new Point[m_PolygonSize];
}

Shape::~Shape()
{
	if (m_Polygon != NULL)
	{
		delete[] m_Polygon;
	}
}

Shape::Shape(const Shape &other)
{
	m_Type        = other.m_Type;
	m_Color       = other.m_Color;
	m_PolygonSize = other.m_PolygonSize;
	m_TopLeft     = other.m_TopLeft;
	m_BottomRight = other.m_BottomRight;

	m_Polygon = new Point[m_PolygonSize];
	for (int i = 0; i < m_PolygonSize; i++)
	{
		m_Polygon[i] = other.m_Polygon[i];
	}
}

const Shape &Shape::operator=(const Shape &other)
{
	if (&other != this)
	{
		m_Type        = other.m_Type;
		m_Color       = other.m_Color;
		m_PolygonSize = other.m_PolygonSize;
		m_TopLeft     = other.m_TopLeft;
		m_BottomRight = other.m_BottomRight;

		m_Polygon = new Point[m_PolygonSize];
		for (int i = 0; i < m_PolygonSize; i++)
		{
			m_Polygon[i] = other.m_Polygon[i];
		}
	}

	return *this;
}

bool Shape::operator==(const Shape &other) const
{
	return (m_Type == other.m_Type) && (m_Color == other.m_Color);
}

bool Shape::operator!=(const Shape &other) const
{
	return !(*this == other);
}

const Color &Shape::GetColor() const
{
	return m_Color;
}

ShapeType Shape::GetType() const
{
	return m_Type;
}

const Point &Shape::GetTopLeft() const
{
	return m_TopLeft;
}

const Point &Shape::GetBottomRight() const
{
	return m_BottomRight;
}

void Shape::SetTopLeft(const Point &topLeft)
{
	m_TopLeft = topLeft;
}

void Shape::SetBottomRight(const Point &bottomRight)
{
	m_BottomRight = bottomRight;
}

void Shape::SetColor(const Color &color)
{
	m_Color = color;
}

Point *Shape::GetPolygon() const
{
	return m_Polygon;
}

int Shape::GetPolygonSize() const
{
	return m_PolygonSize;
}
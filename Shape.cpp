#include "stdafx.h"
#include "Shape.h"

Shape::Shape(const Color &color, ShapeType type, int polygonSize)
	: m_Color(color), m_Type(type), m_PolygonSize(polygonSize), m_TopLeft(), m_BottomRight()
{ }

Shape::~Shape()
{
	if (m_Polygon.GetSize() > 0)
	{
		DeletePolygon(m_Polygon);
	}
}

Shape::Shape(const Shape &other)
{
	m_Type        = other.m_Type;
	m_Color       = other.m_Color;
	m_PolygonSize = other.m_PolygonSize;
	m_TopLeft     = other.m_TopLeft;
	m_BottomRight = other.m_BottomRight;
	
	SetPolygon(other.m_Polygon);
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

		SetPolygon(other.m_Polygon);
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

int Shape::GetPolygonSize() const
{
	return m_PolygonSize;
}

const CTypedPtrArray<CObArray, Point *> &Shape::GetPolygon() const
{
	return m_Polygon;
}

void Shape::DeletePolygon(CTypedPtrArray<CObArray, Point *> &poly)
{
	for (int i = 0; i < poly.GetSize(); i++)
	{
		delete poly[i];
	}
	poly.RemoveAll();
}

void Shape::Serialize( CArchive& archive )
{
    // call base class function first
    // base class is CObject in this case
    CObject::Serialize(archive);
	
    // now do the stuff for our specific class

    if(archive.IsStoring())
	{
		int type = (int)m_Type;
        archive << type;
		archive << m_PolygonSize;
	}
    else
	{
		int type;
        archive >> type;
		archive >> m_PolygonSize;
		m_Type = (ShapeType) type;
	}

	m_TopLeft.Serialize(archive);
	m_BottomRight.Serialize(archive);
	m_Color.Serialize(archive);
	m_Polygon.Serialize(archive);
}

void Shape::SetPolygon(const CTypedPtrArray<CObArray, Point *> &srcPoly)
{
	if (m_Polygon.GetSize() > 0)
	{
		DeletePolygon(m_Polygon);
	}

	for (int i = 0; i < srcPoly.GetSize(); i++)
	{
		m_Polygon.Add(new Point(*srcPoly[i]));
	}
}
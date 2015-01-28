#include "stdafx.h"
#include "Shape.h"

Shape::Shape(const Color &color, ShapeType type, int polygonSize)
	: m_Type(type), m_PolygonSize(polygonSize)
{
	m_Color = new Color(color);
	m_TopLeft = new Point();
	m_BottomRight = new Point();
}

Shape::~Shape()
{
	if (m_Color != NULL)
	{
		delete m_Color;
	}
	if (m_TopLeft != NULL)
	{
		delete m_TopLeft;
	}
	if (m_BottomRight != NULL)
	{
		delete m_BottomRight;
	}
	if (m_Polygon.GetSize() > 0)
	{
		DeletePolygon(m_Polygon);
	}
}

Shape::Shape(const Shape &other)
{
	m_Type        = other.m_Type;
	m_Color       = new Color(*other.m_Color);
	m_PolygonSize = other.m_PolygonSize;
	m_TopLeft     = new Point(*other.m_TopLeft);
	m_BottomRight = new Point(*other.m_BottomRight);
	
	SetPolygon(other.m_Polygon);
}

const Shape &Shape::operator=(const Shape &other)
{
	if (&other != this)
	{
		if (m_Color != NULL)
		{
			delete m_Color;
		}
		if (m_TopLeft != NULL)
		{
			delete m_TopLeft;
		}
		if (m_BottomRight != NULL)
		{
			delete m_BottomRight;
		}
		m_Type        = other.m_Type;
		m_Color       = new Color(*other.m_Color);
		m_PolygonSize = other.m_PolygonSize;
		m_TopLeft     = new Point(*other.m_TopLeft);
		m_BottomRight = new Point(*other.m_BottomRight);

		SetPolygon(other.m_Polygon);
	}

	return *this;
}

bool Shape::operator==(const Shape &other) const
{
	return (m_Type == other.m_Type) && (*m_Color == *other.m_Color);
}

bool Shape::operator!=(const Shape &other) const
{
	return !(*this == other);
}

const Color &Shape::GetColor() const
{
	return *m_Color;
}

ShapeType Shape::GetType() const
{
	return m_Type;
}

const Point &Shape::GetTopLeft() const
{
	return *m_TopLeft;
}

const Point &Shape::GetBottomRight() const
{
	return *m_BottomRight;
}

void Shape::SetTopLeft(const Point &topLeft)
{
	if (m_TopLeft != NULL)
	{
		delete m_TopLeft;
	}
	m_TopLeft = new Point(topLeft);
}

void Shape::SetBottomRight(const Point &bottomRight)
{
	if (m_BottomRight != NULL)
	{
		delete m_BottomRight;
	}
	m_BottomRight = new Point(bottomRight);
}

void Shape::SetColor(const Color &color)
{
	if (m_Color != NULL)
	{
		delete m_Color;
	}
	m_Color = new Color(color);
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

void Shape::Serialize(CArchive& ar)
{
    CObject::Serialize(ar);
    if (ar.IsStoring())
	{
		ar << m_Type;
		ar << m_Color;
		ar << m_PolygonSize;
		ar << m_TopLeft;
		ar << m_BottomRight;
	}
    else
	{
		int type;
		ar >> type;
		m_Type = (ShapeType)type;
		ar >> m_Color;
		ar >> m_PolygonSize;
		ar >> m_TopLeft;
		ar >> m_BottomRight;
	}
	m_Polygon.Serialize(ar);
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
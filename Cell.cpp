#include "stdafx.h"
#include "Cell.h"

Cell::Cell()
	: m_Shape(NULL), m_IsSelected(false), m_IsInSequence(false)
{
	m_TopLeft = new Point();
	m_BottomRight = new Point();
}

Cell::~Cell()
{
	if (m_Shape != NULL)
	{
		delete m_Shape;
	}
	if (m_TopLeft != NULL)
	{
		delete m_TopLeft;
	}
	if (m_BottomRight != NULL)
	{
		delete m_BottomRight;
	}
}

Cell::Cell(Shape *shape, const Point &topLeft, const Point &bottomRight)
	: m_Shape(shape), m_IsSelected(false), m_IsInSequence(false)
{
	m_TopLeft     = new Point(topLeft);
	m_BottomRight = new Point(bottomRight);
}

Cell::Cell(const Cell &other)
{
	m_Shape = other.m_Shape->Clone();
	m_TopLeft = new Point(*other.m_TopLeft);
	m_BottomRight = new Point(*other.m_BottomRight);
	m_IsSelected = false;
	m_IsInSequence = false;
}

const Cell &Cell::operator=(const Cell &other)
{
	if (&other != this)
	{
		if (m_Shape != NULL)
		{
			delete m_Shape;
		}
		if (m_TopLeft != NULL)
		{
			delete m_TopLeft;
		}
		if (m_BottomRight != NULL)
		{
			delete m_BottomRight;
		}
		m_Shape = other.m_Shape->Clone();
		m_TopLeft = new Point(*other.m_TopLeft);
		m_BottomRight = new Point(*other.m_BottomRight);
		m_IsSelected = false;
		m_IsInSequence = false;
	}

	return *this;
}

Shape *Cell::GetShape() const
{
	return m_Shape;
}

const Point &Cell::GetTopLeft() const
{
	return *m_TopLeft;
}

const Point &Cell::GetBottomRight() const
{
	return *m_BottomRight;
}

bool Cell::IsSelected() const
{
	return m_IsSelected;
}

void Cell::SetShape(Shape *shape)
{
	if (m_Shape != NULL)
	{
		delete m_Shape;
	}
	m_Shape = shape->Clone();
}

bool Cell::IsInSequence() const
{
	return m_IsInSequence;
}

void Cell::SetTopLeft(const Point &topLeft)
{
	if (m_TopLeft != NULL)
	{
		delete m_TopLeft;
	}
	m_TopLeft = new Point(topLeft);
}

void Cell::SetBottomRight(const Point &bottomRight)
{
	if (m_BottomRight != NULL)
	{
		delete m_BottomRight;
	}
	m_BottomRight = new Point(bottomRight);
}

void Cell::Select(bool isSelected)
{
	m_IsSelected = isSelected;
}

void Cell::MarkAsSequence()
{
	m_IsInSequence = true;
}

IMPLEMENT_SERIAL(Cell, CObject, 1)

void Cell::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_TopLeft;
		ar << m_BottomRight;
		ar << m_IsSelected;
		ar << m_IsInSequence;
	}
	else
	{
		ar >> m_TopLeft;
		ar >> m_BottomRight;
		ar >> m_IsSelected;
		ar >> m_IsInSequence;
	}
	m_Shape->Serialize(ar);
}
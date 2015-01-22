#include "stdafx.h"
#include "Cell.h"

Cell::Cell()
	: m_Shape(NULL), m_TopLeft(), m_BottomRight(), m_IsSelected(false)
{
}

Cell::~Cell()
{
}

Cell::Cell(Shape *shape, const Point &topLeft, const Point &bottomRight)
	: m_Shape(shape), m_TopLeft(topLeft), m_BottomRight(bottomRight), m_IsSelected(false)
{
}

Cell::Cell(const Cell &other)
{
	m_Shape = other.m_Shape->Clone();
	m_TopLeft = other.m_TopLeft;
	m_BottomRight = other.m_BottomRight;
	m_IsSelected = false;
}

const Cell &Cell::operator=(const Cell &other)
{
	if (&other != this)
	{
		m_Shape = other.m_Shape->Clone();
		m_TopLeft = other.m_TopLeft;
		m_BottomRight = other.m_BottomRight;
		m_IsSelected = false;
	}

	return *this;
}

Shape *Cell::GetShape() const
{
	return m_Shape;
}

const Point &Cell::GetTopLeft() const
{
	return m_TopLeft;
}

const Point &Cell::GetBottomRight() const
{
	return m_BottomRight;
}

bool Cell::IsSelected() const
{
	return m_IsSelected;
}

void Cell::SetTopLeft(const Point &topLeft)
{
	m_TopLeft = topLeft;
}

void Cell::SetBottomRight(const Point &bottomRight)
{
	m_BottomRight = bottomRight;
}

void Cell::Select(bool isSelected)
{
	m_IsSelected = isSelected;
}
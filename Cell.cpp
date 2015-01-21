#include "stdafx.h"
#include "Cell.h"

Cell::Cell()
	: m_Shape(NULL), m_Location(), m_IsSelected(false)
{
}

Cell::~Cell()
{
}

Cell::Cell(Shape *shape, Point location)
	: m_Shape(shape), m_Location(location), m_IsSelected(false)
{
}

Cell::Cell(const Cell &other)
{
	m_Shape = other.m_Shape->Clone();
	m_Location = other.m_Location;
	m_IsSelected = false;
}

const Cell &Cell::operator=(const Cell &other)
{
	if (&other != this)
	{
		m_Shape = other.m_Shape->Clone();
		m_Location = other.m_Location;
		m_IsSelected = false;
	}

	return *this;
}

Shape *Cell::GetShape() const
{
	return m_Shape;
}

const Point &Cell::GetLocation() const
{
	return m_Location;
}

void Cell::SetLocation(const Point &location)
{
	m_Location = location;
}

void Cell::Select(bool isSelected)
{
	m_IsSelected = isSelected;
}
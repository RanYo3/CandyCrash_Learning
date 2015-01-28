#include "stdafx.h"
#include "Sh_Rectangle.h"

Sh_Rectangle::Sh_Rectangle(const Color &color, ShapeType type, int polygonSize) 
	: Sh_Ellipse(color, type, polygonSize) { }

Sh_Rectangle::Sh_Rectangle(const Sh_Rectangle &other) 
	: Sh_Ellipse(other) { }

Shape *Sh_Rectangle::Clone() const
{
	return new Sh_Rectangle(*this);
}

IMPLEMENT_SERIAL(Sh_Rectangle, CObject, 1)
#include "stdafx.h"
#include "Color.h"

Color::Color()
	: m_R(0), m_G(0), m_B(0)
{
}

Color::~Color()
{
}

Color::Color(int r, int g, int b)
	: m_R(r), m_G(g), m_B(b)
{

}

Color::Color(const Color &other)
{
	m_R = other.m_R;
	m_G = other.m_G;
	m_B = other.m_B;
}

const Color &Color::operator=(const Color &other)
{
	if (&other != this)
	{
		m_R = other.m_R;
		m_G = other.m_G;
		m_B = other.m_B;
	}

	return *this;
}

bool Color::operator==(const Color &other) const
{
	return (m_R == other.m_R) &&
		   (m_G == other.m_G) &&
		   (m_B == other.m_B);
}

bool Color::operator!=(const Color &other) const
{
	return !(*this == other);
}

COLORREF Color::GetColorRef() const
{
	return RGB(m_R, m_G, m_B);
}

void Color::SetRGB(int r, int g, int b)
{
	m_R = r;
	m_G = g;
	m_B = b;
}
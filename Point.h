#pragma once

#include <atltypes.h>
#include <afx.h>

class Point : public CObject
{
	DECLARE_SERIAL(Point)
public:
	Point();
	~Point();

	Point(int x, int y);
	Point(const CPoint &cpoint);
	Point(const Point &other);
	const Point &operator=(const Point &other);

	bool operator==(const Point &other) const;
	bool operator!=(const Point &other) const;

	Point operator+(int num) const;
	Point operator-(int num) const;

	int GetX() const;
	int GetY() const;

	void SetX(int x);
	void SetY(int y);

	void Serialize(CArchive& ar);

private:
	int m_X;
	int m_Y;
};
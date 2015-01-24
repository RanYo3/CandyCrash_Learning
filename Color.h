#pragma once

#include <WinGDI.h>

//      Name                   R    G    B
//      ====                  ===  ===  ===
#define BLACK			Color(  0,   0,   0)
#define WHITE			Color(255, 255, 255)
#define BLUE			Color(  0,   0, 255)
#define GREEN			Color(  0, 255,   0)
#define RED				Color(255,   0,   0)
#define YELLOW			Color(255, 255,   0)
#define MAGENTA			Color(255,   0, 255)
#define CYAN			Color(  0, 255, 255)
#define GREY			Color(128, 128, 128)
#define MAROON			Color(128,   0,   0)
#define LIME			Color(191, 255,   0)
#define ORANGE_LIGHT	Color(255, 165,   0)
#define ORANGE			Color(255,  79,   0)
#define PURPLE			Color(128,   0, 128)
#define PINK			Color(255, 192, 203)
#define BROWN			Color(150,  75,   0)
#define SKY_BLUE		Color(135, 206, 235)
#define AZURE			Color(  0, 127, 255)
#define INDIGO			Color(102,   0, 255)
#define CREAM			Color(255, 253, 208)
#define GREEN_DARK		Color( 34, 139,  34)
#define HONEYDUE		Color(240, 255, 240)
#define PINK_LIGHT		Color(255, 179, 222)
#define PINK_ROSE		Color(255, 102, 204)
#define PINK_HOT		Color(255, 105, 180)

class Color
{
public:
	Color();
	~Color();

	Color(int r, int g, int b);
	Color(const Color &other);
	const Color &operator=(const Color &other);

	bool operator==(const Color &other) const;
	bool operator!=(const Color &other) const;

	static COLORREF GetColorRef(const Color &color);

	void SetRGB(int r, int g, int b);

private:
	int m_R;
	int m_G;
	int m_B;
};
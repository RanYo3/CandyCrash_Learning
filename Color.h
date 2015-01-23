#pragma once

#include <WinGDI.h>

//      Name           R    G    B
//      ====          ===  ===  ===
#define BLACK	Color(  0,   0,   0)
#define WHITE	Color(255, 255, 255)
#define BLUE	Color(  0,   0, 255)
#define GREEN	Color(  0, 255,   0)
#define RED		Color(255,   0,   0)
#define YELLOW	Color(255, 255,   0)
#define MAGENTA	Color(255,   0, 255)
#define CYAN	Color(  0, 255, 255)


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

	COLORREF GetColorRef() const;

	void SetRGB(int r, int g, int b);

private:
	int m_R;
	int m_G;
	int m_B;
};
#pragma once

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

	Color(char r, char g, char b);
	Color(const Color &other);
	const Color &operator=(const Color &other);

	bool operator==(const Color &other) const;
	bool operator!=(const Color &other) const;

	void SetRGB(char r, char g, char b);

private:
	char m_R;
	char m_G;
	char m_B;
};
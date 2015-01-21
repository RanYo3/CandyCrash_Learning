#pragma once

#include "Cell.h"
#include "Point.h"

#define MATRIX_SIZE 10

class Board
{
public:
	Board(int matrixSize = MATRIX_SIZE);
	~Board();

	Board(int rows, int cols);
	Board(const Board &other);
	const Board &operator=(const Board &other);

	void Swap(const Point &p1, const Point &p2);

private:
	void InitMatrix();
	void DeleteMatrix();

	Cell **m_Matrix;
	int m_Rows;
	int m_Cols;
};
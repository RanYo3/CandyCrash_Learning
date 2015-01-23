#pragma once

#include "Cell.h"
#include "Point.h"

#define MATRIX_SIZE 10
#define DEFAULT_POINT Point(0, 0)

class Board
{
public:
	Board(int matrixSize = MATRIX_SIZE, const Point &topLeft = DEFAULT_POINT, const Point &bottomRight = DEFAULT_POINT);
	~Board();

	Board(int rows, int cols);
	Board(const Board &other);
	const Board &operator=(const Board &other);

	int GetRows() const;
	int GetCols() const;

	Cell *GetCell(int row, int col) const;
	Cell *GetCell(const Point &index) const;
	bool GetCellIndex(const Point &locationInWindow, Point &index) const;
	bool CheckSequence(int x, int y, bool initialMatrix = false, bool markCells = false);

	void Swap(const Point &p1, const Point &p2);

private:
	void InitData();
	void InitCellSize();
	void InitMatrix();
	void InitShapeCollection();
	void DeleteMatrix();
	void DeleteShapeCollection();

	Cell *InitCell(Shape *shape, const Point &topLeft, const Point &bottomRight) const;

	void CalcCellLocation(int i, int j, Point &topLeft, Point &bottomRight) const;

	bool SequenceByIndex(int x1, int y1, int x2, int y2, int x3, int y3,  bool markCell) const;
	bool IsInMatrix(int x, int y) const;

	Shape *RandomShape() const;

	Cell ***m_Matrix;
	Shape **m_ShapesCollection;
	int m_Rows;
	int m_Cols;
	Point m_TopLeft;
	Point m_BottomRight;
	double m_CellSizeX;
	double m_CellSizeY;
};
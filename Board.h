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
	const Point &GetTopLeft() const;
	const Point &GetBottomRight() const;

	Cell *GetCell(int row, int col) const;
	Cell *GetCell(const Point &index) const;
	bool GetCellIndex(const Point &locationInWindow, Point &index) const;

	bool CheckSequence(const Point &index, bool initialMatrix = false, bool markCells = true);
	bool CheckSequence(int row, int col, bool initialMatrix = false, bool markCells = true);
	bool CheckSequencesInRange(int minCol, int maxCol, int maxRow);

	bool AreNeighbours(const Point &index1, const Point &index2) const;
	
	void Swap(const Point &index1, const Point &index2);
	void Swap(int row1, int col1, int row2, int col2);

	void DoExplosion(int &minCol, int &maxCol, int &maxRow);

private:
	void InitData();
	void InitCellSize();
	void InitShapeCollection();
	void InitMatrix();

	Shape *RandomShape() const;

	void DeleteShapeCollection();
	void DeleteMatrix();

	Cell *InitCell(Shape *shape, const Point &topLeft, const Point &bottomRight) const;
	void ReplaceWithNewCell(int row, int col);

	void CalcCellLocation(int row, int col, Point &topLeft, Point &bottomRight) const;
	
	bool IsInMatrix(int row, int col) const;
	bool SequenceByIndex(int row1, int col1, int row2, int col2, int row3, int col3, bool markCells);

	void RollCellsUp(int row, int col);


	Cell ***m_Matrix;
	Shape **m_ShapesCollection;
	int m_Rows;
	int m_Cols;
	Point m_TopLeft;
	Point m_BottomRight;
	double m_CellSizeX;
	double m_CellSizeY;
};
#include "stdafx.h"
#include "Board.h"
#include "Sh_Triangle.h"
#include "Sh_Rectangle.h"
#include "Sh_Diamond.h"
#include "Sh_Ellipse.h"
#include "Sh_Plus.h"
#include "Sh_Minus.h"
#include "Sh_Star.h"
#include "Sh_X.h"

#include <math.h>

Board::Board(int matrixSize, const Point &topLeft, const Point &bottomRight)
	: m_Rows(matrixSize), m_Cols(matrixSize), m_TopLeft(topLeft), m_BottomRight(bottomRight)
{
	InitData();
}

Board::~Board()
{
	if (m_Matrix != NULL)
	{
		DeleteMatrix();
	}
	if (m_ShapesCollection != NULL)
	{
		DeleteShapeCollection();
	}
}

Board::Board(int rows, int cols)
	: m_Rows(rows), m_Cols(cols)
{
	InitData();
}

Board::Board(const Board &other)
{
	m_Rows = other.m_Rows;
	m_Cols = other.m_Cols;
	InitData();
}

const Board &Board::operator=(const Board &other)
{
	if (&other != this)
	{
		if (m_Matrix != NULL)
		{
			DeleteMatrix();
		}

		m_Rows = other.m_Rows;
		m_Cols = other.m_Cols;
		InitData();
	}

	return *this;
}

int Board::GetRows() const
{
	return m_Rows;
}

int Board::GetCols() const
{
	return m_Cols;
}

const Point &Board::GetTopLeft() const
{
	return m_TopLeft;
}

const Point &Board::GetBottomRight() const
{
	return m_BottomRight;
}

Cell *Board::GetCell(int row, int col) const
{
	return m_Matrix[row][col];
}

Cell *Board::GetCell(const Point &index) const
{
	return m_Matrix[index.GetY()][index.GetX()];
}

bool Board::GetCellIndex(const Point &locationInWindow, Point &index) const
{
	int indexI = (int)((double)(locationInWindow.GetY() - m_TopLeft.GetY()) / m_CellSizeY);
	int indexJ = (int)((double)(locationInWindow.GetX() - m_TopLeft.GetX()) / m_CellSizeX);

	if (indexI >= 0 && indexI < m_Rows && 
		indexJ >= 0 && indexJ < m_Cols)
	{
		index.SetX(indexJ);
		index.SetY(indexI);
		return true;
	}

	return false;
}

bool Board::AreNeighbours(const Point &p1, const Point &p2) const
{
	bool horizontalNeighbours = (abs(p1.GetX() - p2.GetX()) == 1) && (p1.GetY() == p2.GetY());
	bool verticalNeighbours   = (abs(p1.GetY() - p2.GetY()) == 1) && (p1.GetX() == p2.GetX());
	
	return (horizontalNeighbours && !verticalNeighbours) ||
		   (!horizontalNeighbours && verticalNeighbours);
}

void Board::Swap(int x1, int y1, int x2, int y2)
{
	if (x1==x2 && y1==y2)
	{
		return;
	}

	Cell* cell1 = InitCell(m_Matrix[y1][x1]->GetShape(), m_Matrix[y2][x2]->GetTopLeft(), m_Matrix[y2][x2]->GetBottomRight());
	Cell* cell2 = InitCell(m_Matrix[y2][x2]->GetShape(), m_Matrix[y1][x1]->GetTopLeft(), m_Matrix[y1][x1]->GetBottomRight());

	delete m_Matrix[y1][x1];
	delete m_Matrix[y2][x2];

	m_Matrix[y1][x1] = cell2;
	m_Matrix[y2][x2] = cell1;
}

void Board::Swap(const Point &index1, const Point &index2)
{
	Swap(index1.GetX(), index1.GetY(), index2.GetX(), index2.GetY());
}

void Board::ReplaceWithNewCell(int row, int col)
{
	Point topLeft =  m_Matrix[row][col]->GetTopLeft();
	Point bottomRight = m_Matrix[row][col]->GetBottomRight();

	delete m_Matrix[row][col];

	m_Matrix[row][col] = InitCell(RandomShape(), topLeft , bottomRight);
}

void Board::DoExplosion(int &minCol, int &maxCol, int &maxRow)
{
	minCol = m_Cols;
	maxCol = -1;
	maxRow = -1;

	for (int j = m_Cols-1 ; j>=0 ; j--)
	{
		for( int i = m_Rows-1 ; i>=0 ; i--)
		{
			if (m_Matrix[i][j]->IsInSequence())
			{
				if (j < minCol)
					minCol = j;
				if (j > maxCol)
					maxCol = j;
				if (i > maxRow)
					maxRow = i;

				RollCellsUp(i,j);
				break;
			}
		}
	}
}

void Board::InitData()
{
	InitCellSize();
	InitShapeCollection();
	InitMatrix();
}

void Board::InitCellSize()
{
	m_CellSizeX = double(m_BottomRight.GetX() - m_TopLeft.GetX()) / m_Cols;
	m_CellSizeY = double(m_BottomRight.GetY() - m_TopLeft.GetY()) / m_Rows;
}

void Board::InitShapeCollection()
{
	m_ShapesCollection = new Shape*[NUM_OF_SHAPES];

	m_ShapesCollection[ST_Rectangle] = new Sh_Rectangle(ORANGE        );
	m_ShapesCollection[ST_Ellipse]   = new Sh_Ellipse  (MAROON        );
	m_ShapesCollection[ST_Triangle]  = new Sh_Triangle (ORANGE_LIGHT  );
	m_ShapesCollection[ST_Diamond]   = new Sh_Diamond  (INDIGO        );
	m_ShapesCollection[ST_Plus]      = new Sh_Plus     (GREEN_DARK    );
	m_ShapesCollection[ST_Minus]     = new Sh_Minus    (CYAN          );
	m_ShapesCollection[ST_Star]      = new Sh_Star     (BLUE          );
	m_ShapesCollection[ST_X]         = new Sh_X        (PINK_LIGHT    );
}

void Board::InitMatrix()
{
	Point cellTopLeft;
	Point cellBottomRight;

	Shape *tempShape;

	m_Matrix = new Cell**[m_Rows];

	srand(static_cast<int>(time(0)));		//to generate different seed for Rand()

	for (int i = 0; i < m_Rows; i++)
	{
		m_Matrix[i] = new Cell*[m_Cols];
		for (int j = 0; j < m_Cols; j++)
		{
			CalcCellLocation(i, j, cellTopLeft, cellBottomRight);

			tempShape = RandomShape();
			m_Matrix[i][j] = InitCell(tempShape, cellTopLeft, cellBottomRight);
			delete tempShape;

			while (CheckSequence(j, i, true, false))
			{
				delete m_Matrix[i][j];

				tempShape = RandomShape();
				m_Matrix[i][j] = InitCell(tempShape, cellTopLeft, cellBottomRight);
				delete tempShape;
			}
		}
	}
}

Cell *Board::InitCell(Shape *shape, const Point &topLeft, const Point &bottomRight) const
{
	shape->SetTopLeft(topLeft + MARGIN);
	shape->SetBottomRight(bottomRight - MARGIN);

	return new Cell(shape->Clone(), topLeft, bottomRight);
}

void Board::DeleteMatrix()
{
	for (int i = 0; i < m_Rows; i++)
	{
		for (int j = 0; j < m_Cols; j++)
		{
			delete m_Matrix[i][j];
		}
		delete[] m_Matrix[i];
	}
	delete[] m_Matrix;
}

void Board::DeleteShapeCollection()
{
	for (int i = 0; i < NUM_OF_SHAPES; i++)
	{
		delete m_ShapesCollection[i];
	}
	delete[] m_ShapesCollection;
}

void Board::RollCellsUp(int row, int col)
{
	int i=1;
	while(row-i >= 0)
	{
		while(row-i >= 0 && m_Matrix[row-i][col]->IsInSequence())
		{
			i++;
		}
		if (row-i >= 0)
		{
			Swap(col, row, col, row-i);
		}
		row--;
	}
	for (int j=0 ; j<i ; j++)
	{
		ReplaceWithNewCell(j, col);
	}
}



void Board::CalcCellLocation(int i, int j, Point &topLeft, Point &bottomRight) const
{
	topLeft.SetX(m_TopLeft.GetX() + (int)(m_CellSizeX * j));
	topLeft.SetY(m_TopLeft.GetY() + (int)(m_CellSizeY * i));

	bottomRight.SetX(topLeft.GetX() + (int)m_CellSizeX);
	bottomRight.SetY(topLeft.GetY() + (int)m_CellSizeY);
}

Shape *Board::RandomShape() const
{
	int rand_idx = rand() % NUM_OF_SHAPES;
	return m_ShapesCollection[rand_idx]->Clone();
}

bool Board::CheckSequence(const Point &index, bool initialMatrix, bool markCells)
{
	return CheckSequence(index.GetX(), index.GetY(), initialMatrix, markCells);
}

bool Board::CheckSequence(int x, int y, bool initialMatrix, bool markCells)
{

	bool sequenceFlag = false;

	if (!initialMatrix)
	{
		if (IsInMatrix(x,y+2) && SequenceByIndex(x,y,  x,y+1,  x,y+2,  markCells))
		{
			sequenceFlag = true;
		}

		if (IsInMatrix(x,y+1) && IsInMatrix(x,y-1) && SequenceByIndex(x,y,  x,y+1,  x,y-1,  markCells))
		{
			sequenceFlag = true;
		}

		if (IsInMatrix(x+2,y) && SequenceByIndex(x,y,  x+1,y,  x+2,y,  markCells))
		{
			sequenceFlag = true;
		}

		if (IsInMatrix(x-1,y) && IsInMatrix(x+1,y) && SequenceByIndex(x,y,  x-1,y,  x+1,y,  markCells))
		{
			sequenceFlag = true;
		}
	}

	if (IsInMatrix(x,y-2) && SequenceByIndex(x,y,  x,y-1,  x,y-2,  markCells))
	{
		sequenceFlag = true;
	}

	if (IsInMatrix(x-2,y) && SequenceByIndex(x,y,  x-1,y,  x-2,y,  markCells))
	{
		sequenceFlag = true;
	}

	return sequenceFlag;
}

bool Board::CheckSequencesInRange(int minCol, int maxCol, int maxRow)
{
	bool sequenceFlag = false;

	for (int i = 0; i <= maxRow; i++)
	{
		for (int j = minCol; j <= maxCol; j++)
		{
			if (CheckSequence(j, i, false, true))
			{
				sequenceFlag = true;
			}
		}
	}

	return sequenceFlag;
}

bool Board::SequenceByIndex(int x1, int y1, int x2, int y2, int x3, int y3, bool markCells)
{
	if (*(m_Matrix[y1][x1]->GetShape()) == *(m_Matrix[y2][x2]->GetShape()) &&
		*(m_Matrix[y1][x1]->GetShape()) == *(m_Matrix[y3][x3]->GetShape()))
	{
		if (markCells == true)
		{
			m_Matrix[y1][x1]->MarkAsSequence();
			m_Matrix[y2][x2]->MarkAsSequence();
			m_Matrix[y3][x3]->MarkAsSequence();
		}
		return true;
	}
	
	return false;
}

bool Board::IsInMatrix(int x, int y) const
{
	return (x >= 0 && x < m_Cols &&
			y >= 0 && y < m_Rows);
}
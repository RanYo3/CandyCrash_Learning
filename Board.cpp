#include "stdafx.h"
#include "Board.h"
#include "Sh_Triangle.h"
#include "Sh_Rectangle.h"
#include "Sh_Diamond.h"
#include "Sh_Ellipse.h"
#include "Sh_Plus.h"
#include "Sh_Minus.h"

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
		index.SetX(indexI);
		index.SetY(indexJ);
		return true;
	}

	return false;
}

void Board::Swap(const Point &index1, const Point &index2)
{
	if (index1 == index2)
	{
		return;
	}

	// Swap cell pointers in matrix
	Cell *cTemp = m_Matrix[index1.GetY()][index1.GetX()];
	m_Matrix[index1.GetY()][index1.GetX()] = m_Matrix[index2.GetY()][index2.GetX()];
	m_Matrix[index2.GetY()][index2.GetX()] = cTemp;

	// Swap top-left location in cells
	Point pTemp = m_Matrix[index1.GetY()][index1.GetX()]->GetTopLeft();
	m_Matrix[index1.GetY()][index1.GetX()]->SetTopLeft(m_Matrix[index2.GetY()][index2.GetX()]->GetTopLeft());
	m_Matrix[index2.GetY()][index2.GetX()]->SetTopLeft(pTemp);

	// Swap bottom-right location in cells
	pTemp = m_Matrix[index1.GetY()][index1.GetX()]->GetBottomRight();
	m_Matrix[index1.GetY()][index1.GetX()]->SetBottomRight(m_Matrix[index2.GetY()][index2.GetX()]->GetBottomRight());
	m_Matrix[index2.GetY()][index2.GetX()]->SetBottomRight(pTemp);
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

	m_ShapesCollection[ST_Rectangle] = new Sh_Rectangle(BLUE);
	m_ShapesCollection[ST_Ellipse] = new Sh_Ellipse(RED);
	m_ShapesCollection[ST_Triangle] = new Sh_Triangle(YELLOW);
	m_ShapesCollection[ST_Diamond] = new Sh_Diamond(GREEN);
	m_ShapesCollection[ST_Plus] = new Sh_Plus(MAGENTA);
	m_ShapesCollection[ST_Minus] = new Sh_Minus(CYAN);
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
			tempShape->SetTopLeft(cellTopLeft + MARGIN);
			tempShape->SetBottomRight(cellBottomRight - MARGIN);

			m_Matrix[i][j] = new Cell(tempShape->Clone(), cellTopLeft, cellBottomRight);

			delete tempShape;
		}
	}
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

void Board::CalcCellLocation(int i, int j, Point &topLeft, Point &bottomRight) const
{
	topLeft.SetX(m_TopLeft.GetX() + (int)(m_CellSizeX * i));
	topLeft.SetY(m_TopLeft.GetY() + (int)(m_CellSizeY * j));

	bottomRight.SetX(topLeft.GetX() + (int)m_CellSizeX);
	bottomRight.SetY(topLeft.GetY() + (int)m_CellSizeY);
}

Shape *Board::RandomShape() const
{
	int rand_idx = rand() % NUM_OF_SHAPES;
	return m_ShapesCollection[rand_idx]->Clone();
}
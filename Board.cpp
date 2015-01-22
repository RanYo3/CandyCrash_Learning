#include "stdafx.h"
#include "Board.h"
#include "Sh_Triangle.h"
#include "Sh_Rectangle.h"
#include "Sh_Diamond.h"
#include "Sh_Ellipse.h"


Board::Board(int matrixSize, const Point &topLeft, const Point &bottomRight)
	: m_Rows(matrixSize), m_Cols(matrixSize), m_TopLeft(topLeft), m_BottomRight(bottomRight)
{
	InitMatrix();
}

Board::~Board()
{
	if (m_Matrix != NULL)
	{
		DeleteMatrix();
		DeleteShapeCollection();
	}
}

Board::Board(int rows, int cols)
	: m_Rows(rows), m_Cols(cols)
{
	InitMatrix();
}

Board::Board(const Board &other)
{
	m_Rows = other.m_Rows;
	m_Cols = other.m_Cols;
	InitMatrix();
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
		InitMatrix();
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

void Board::InitMatrix()
{
	InitShapeCollection();

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

void Board::InitShapeCollection()
{
	m_ShapesCollection = new Shape*[NUM_OF_SHAPES];

	m_ShapesCollection[ST_Rectangle] = new Sh_Rectangle;
	m_ShapesCollection[ST_Ellipse] = new Sh_Ellipse;
	m_ShapesCollection[ST_Triangle] = new Sh_Triangle;
	m_ShapesCollection[ST_Diamond] = new Sh_Diamond;
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
	double cellSizeX = double(m_BottomRight.GetX() - m_TopLeft.GetX()) / m_Cols;
	double cellSizeY = double(m_BottomRight.GetY() - m_TopLeft.GetY()) / m_Rows;

	topLeft.SetX(m_TopLeft.GetX() + cellSizeX * i);
	topLeft.SetY(m_TopLeft.GetY() + cellSizeY * j);

	bottomRight.SetX(topLeft.GetX() + cellSizeX);
	bottomRight.SetY(topLeft.GetY() + cellSizeY);
}

Shape *Board::RandomShape() const
{
	int rand_idx = rand() % NUM_OF_SHAPES;
	return m_ShapesCollection[rand_idx]->Clone();
}
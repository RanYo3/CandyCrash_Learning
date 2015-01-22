#include "stdafx.h"
#include "Board.h"
#include "Sh_Triangle.h"

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
	Point cellTopLeft;
	Point cellBottomRight;

	m_Matrix = new Cell**[m_Rows];

	for (int i = 0; i < m_Rows; i++)
	{
		m_Matrix[i] = new Cell*[m_Cols];
		for (int j = 0; j < m_Cols; j++)
		{
			CalcCellLocation(i, j, cellTopLeft, cellBottomRight);
			m_Matrix[i][j] = new Cell(new Sh_Triangle(cellTopLeft + MARGIN, cellBottomRight - MARGIN, BLACK), cellTopLeft, cellBottomRight);
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

void Board::CalcCellLocation(int i, int j, Point &topLeft, Point &bottomRight) const
{
	double cellSizeX = double(m_BottomRight.GetX() - m_TopLeft.GetX()) / m_Cols;
	double cellSizeY = double(m_BottomRight.GetY() - m_TopLeft.GetY()) / m_Rows;

	topLeft.SetX(m_TopLeft.GetX() + cellSizeX * i);
	topLeft.SetY(m_TopLeft.GetY() + cellSizeY * j);

	bottomRight.SetX(topLeft.GetX() + cellSizeX);
	bottomRight.SetY(topLeft.GetY() + cellSizeY);
}
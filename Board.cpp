#include "stdafx.h"
#include "Board.h"
#include "Sh_Triangle.h"

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
	InitMatrix();
}

void Board::InitCellSize()
{
	m_CellSizeX = double(m_BottomRight.GetX() - m_TopLeft.GetX()) / m_Cols;
	m_CellSizeY = double(m_BottomRight.GetY() - m_TopLeft.GetY()) / m_Rows;
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
	topLeft.SetX(m_TopLeft.GetX() + (int)(m_CellSizeX * i));
	topLeft.SetY(m_TopLeft.GetY() + (int)(m_CellSizeY * j));

	bottomRight.SetX(topLeft.GetX() + (int)m_CellSizeX);
	bottomRight.SetY(topLeft.GetY() + (int)m_CellSizeY);
}
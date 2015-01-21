#include "stdafx.h"
#include "Board.h"

Board::Board(int matrixSize)
	: m_Rows(matrixSize), m_Cols(matrixSize)
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

void Board::Swap(const Point &p1, const Point &p2)
{
	if (p1 == p2)
	{
		return;
	}

	Cell temp = m_Matrix[p1.GetY()][p1.GetX()];
	m_Matrix[p1.GetY()][p1.GetX()] = m_Matrix[p2.GetY()][p2.GetX()];
	m_Matrix[p2.GetY()][p2.GetX()] = temp;

	m_Matrix[p1.GetY()][p1.GetX()].SetLocation(p1);
	m_Matrix[p2.GetY()][p2.GetX()].SetLocation(p2);
}

void Board::InitMatrix()
{
	m_Matrix = new Cell*[m_Rows];
	for (int i = 0; i < m_Rows; i++)
	{
		m_Matrix[i] = new Cell[m_Cols];
	}
}

void Board::DeleteMatrix()
{
	for (int i = 0; i < m_Rows; i++)
	{
		delete[] m_Matrix[i];
	}
	delete[] m_Matrix;
}
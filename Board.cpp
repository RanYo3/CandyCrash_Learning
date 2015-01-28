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

Board::Board(const Board &other)
{
	m_Rows = other.m_Rows;
	m_Cols = other.m_Cols;
	m_TopLeft = other.m_TopLeft;
	m_BottomRight = other.m_BottomRight;
	m_CellSizeX = other.m_CellSizeX;
	m_CellSizeY = other.m_CellSizeY;

	m_ShapesCollection = new Shape*[NUM_OF_SHAPES];
	for (int i = 0; i < NUM_OF_SHAPES; i++)
	{
		m_ShapesCollection[i] = other.m_ShapesCollection[i]->Clone();
	}

	m_Matrix = new Cell**[m_Rows];
	for (int row = 0; row < m_Rows; row++)
	{
		m_Matrix[row] = new Cell*[m_Cols];
		for (int col = 0; col < m_Cols; col++)
		{
			m_Matrix[row][col] = new Cell(*other.m_Matrix[row][col]);
		}
	}
}

const Board &Board::operator=(const Board &other)
{
	if (&other != this)
	{
		if (m_Matrix != NULL)
		{
			DeleteMatrix();
		}
		if (m_ShapesCollection != NULL)
		{
			DeleteShapeCollection();
		}

		m_Rows = other.m_Rows;
		m_Cols = other.m_Cols;
		m_TopLeft = other.m_TopLeft;
		m_BottomRight = other.m_BottomRight;
		m_CellSizeX = other.m_CellSizeX;
		m_CellSizeY = other.m_CellSizeY;

		m_ShapesCollection = new Shape*[NUM_OF_SHAPES];
		for (int i = 0; i < NUM_OF_SHAPES; i++)
		{
			m_ShapesCollection[i] = other.m_ShapesCollection[i]->Clone();
		}

		m_Matrix = new Cell**[m_Rows];
		for (int row = 0; row < m_Rows; row++)
		{
			m_Matrix[row] = new Cell*[m_Cols];
			for (int col = 0; col < m_Cols; col++)
			{
				m_Matrix[row][col] = new Cell(*other.m_Matrix[row][col]);
			}
		}
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
	return m_Matrix[index.GetX()][index.GetY()];
}

bool Board::GetCellIndex(const Point &locationInWindow, Point &index) const
{
	int indexI = (int)((double)(locationInWindow.GetY() - m_TopLeft.GetY()) / m_CellSizeX);
	int indexJ = (int)((double)(locationInWindow.GetX() - m_TopLeft.GetX()) / m_CellSizeY);

	if (indexI >= 0 && indexI < m_Rows && 
		indexJ >= 0 && indexJ < m_Cols)
	{
		index.SetX(indexI);
		index.SetY(indexJ);
		return true;
	}

	return false;
}

bool Board::CheckSequence(const Point &index, bool initialMatrix, bool markCells)
{
	return CheckSequence(index.GetX(), index.GetY(), initialMatrix, markCells);
}

bool Board::CheckSequence(int row, int col, bool initialMatrix, bool markCells)
{
	bool sequenceFlag = (IsInMatrix(row    , col - 2) && SequenceByIndex(row, col, row    , col - 1, row    , col - 2, markCells)) +
						(IsInMatrix(row - 2, col    ) && SequenceByIndex(row, col, row - 1, col    , row - 2, col    , markCells));

	if (!initialMatrix)
	{
		sequenceFlag += (IsInMatrix(row - 1, col    ) && IsInMatrix(row + 1, col    ) && SequenceByIndex(row, col, row - 1, col    , row + 1, col    , markCells)) +
						(IsInMatrix(row    , col + 1) && IsInMatrix(row    , col - 1) && SequenceByIndex(row, col, row    , col + 1, row    , col - 1, markCells)) +
						(IsInMatrix(row + 2, col    ) &&                                 SequenceByIndex(row, col, row + 1, col    , row + 2, col    , markCells)) +
						(IsInMatrix(row    , col + 2) &&                                 SequenceByIndex(row, col, row    , col + 1, row    , col + 2, markCells));
	}

	return sequenceFlag;
}

bool Board::CheckSequencesInRange(int minCol, int maxCol, int maxRow)
{
	bool sequenceFlag = false;

	for (int row = 0; row <= maxRow; row++)
	{
		for (int col = minCol; col <= maxCol; col++)
		{
			if (CheckSequence(row, col, false, true))
			{
				sequenceFlag = true;
			}
		}
	}

	return sequenceFlag;
}

bool Board::AreNeighbours(const Point &index1, const Point &index2) const
{
	bool verticalNeighbours   = (abs(index1.GetX() - index2.GetX()) == 1) && (index1.GetY() == index2.GetY());
	bool horizontalNeighbours = (abs(index1.GetY() - index2.GetY()) == 1) && (index1.GetX() == index2.GetX());
	
	return (horizontalNeighbours && !verticalNeighbours) ||
		   (!horizontalNeighbours && verticalNeighbours);
}

void Board::Swap(const Point &index1, const Point &index2)
{
	Swap(index1.GetX(), index1.GetY(), index2.GetX(), index2.GetY());
}

void Board::Swap(int row1, int col1, int row2, int col2)
{
	if (row1==row2 && col1==col2)
	{
		return;
	}

	Cell *oldCell1 = m_Matrix[row1][col1];
	Cell *oldCell2 = m_Matrix[row2][col2];

	Cell *newCell1 = InitCell(oldCell1->GetShape(), oldCell2->GetTopLeft(), oldCell2->GetBottomRight());
	Cell *newCell2 = InitCell(oldCell2->GetShape(), oldCell1->GetTopLeft(), oldCell1->GetBottomRight());

	delete oldCell1;
	delete oldCell2;

	m_Matrix[row1][col1] = newCell2;
	m_Matrix[row2][col2] = newCell1;
}

void Board::DoExplosion(int &minCol, int &maxCol, int &maxRow)
{
	minCol = m_Cols;
	maxCol = -1;
	maxRow = -1;

	for (int col = m_Cols - 1 ; col >= 0 ; col--)
	{
		for( int row = m_Rows - 1 ; row >= 0 ; row--)
		{
			if (m_Matrix[row][col]->IsInSequence())
			{
				if (col < minCol)
					minCol = col;
				if (col > maxCol)
					maxCol = col;
				if (row > maxRow)
					maxRow = row;

				RollCellsUp(row, col);
				break;
			}
		}
	}
}

IMPLEMENT_SERIAL(Board, CObject, 1)

void Board::Serialize(CArchive& archive)
{
	CObject::Serialize(archive);

	if(archive.IsStoring())
	{
		archive << m_Rows;
		archive << m_Cols;
		archive << m_CellSizeX;
		archive << m_CellSizeY;
	}
	else
	{
		archive >> m_Rows;
		archive >> m_Cols;
		archive >> m_CellSizeX;
		archive >> m_CellSizeY;
	}

	m_TopLeft.Serialize(archive);
	m_BottomRight.Serialize(archive);
	
	for (int i = 0; i < NUM_OF_SHAPES; i++)
	{
		m_ShapesCollection[i]->Serialize(archive);
	}
	
	for (int row = 0; row < m_Rows; row++)
	{
		for (int col = 0; col < m_Cols; col++)
		{
			m_Matrix[row][col]->Serialize(archive);
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
	m_CellSizeX = double(m_BottomRight.GetY() - m_TopLeft.GetY()) / m_Rows;
	m_CellSizeY = double(m_BottomRight.GetX() - m_TopLeft.GetX()) / m_Cols;
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

	srand(static_cast<int>(time(0)));		// to generate different seed for Rand()

	for (int row = 0; row < m_Rows; row++)
	{
		m_Matrix[row] = new Cell*[m_Cols];
		for (int col = 0; col < m_Cols; col++)
		{
			CalcCellLocation(row, col, cellTopLeft, cellBottomRight);

			tempShape = RandomShape();
			m_Matrix[row][col] = InitCell(tempShape, cellTopLeft, cellBottomRight);
			delete tempShape;

			while (CheckSequence(row, col, true, false))
			{
				delete m_Matrix[row][col];

				tempShape = RandomShape();
				m_Matrix[row][col] = InitCell(tempShape, cellTopLeft, cellBottomRight);
				delete tempShape;
			}
		}
	}
}

Shape *Board::RandomShape() const
{
	int rand_idx = rand() % NUM_OF_SHAPES;
	return m_ShapesCollection[rand_idx]->Clone();
}

void Board::DeleteShapeCollection()
{
	for (int i = 0; i < NUM_OF_SHAPES; i++)
	{
		delete m_ShapesCollection[i];
	}
	delete[] m_ShapesCollection;
}

void Board::DeleteMatrix()
{
	for (int row = 0; row < m_Rows; row++)
	{
		for (int col = 0; col < m_Cols; col++)
		{
			delete m_Matrix[row][col];
		}
		delete[] m_Matrix[row];
	}
	delete[] m_Matrix;
}

Cell *Board::InitCell(Shape *shape, const Point &topLeft, const Point &bottomRight) const
{
	shape->SetTopLeft(topLeft + MARGIN);
	shape->SetBottomRight(bottomRight - MARGIN);

	Shape *newShape = shape->Clone();
	newShape->BuildPolygon();

	return new Cell(newShape, topLeft, bottomRight);
}

void Board::ReplaceWithNewCell(int row, int col)
{
	Shape *tempShape = RandomShape();
	Point topLeft =  m_Matrix[row][col]->GetTopLeft();
	Point bottomRight = m_Matrix[row][col]->GetBottomRight();

	delete m_Matrix[row][col];

	m_Matrix[row][col] = InitCell(tempShape, topLeft , bottomRight);
	delete tempShape;
}

void Board::CalcCellLocation(int row, int col, Point &topLeft, Point &bottomRight) const
{
	topLeft.SetX(m_TopLeft.GetX() + (int)(m_CellSizeX * col));
	topLeft.SetY(m_TopLeft.GetY() + (int)(m_CellSizeY * row));

	bottomRight.SetX(topLeft.GetX() + (int)m_CellSizeY);
	bottomRight.SetY(topLeft.GetY() + (int)m_CellSizeX);
}

bool Board::IsInMatrix(int row, int col) const
{
	return (row >= 0 && row < m_Rows &&
			col >= 0 && col < m_Cols);
}

bool Board::SequenceByIndex(int row1, int col1, int row2, int col2, int row3, int col3, bool markCells)
{
	if (*(m_Matrix[row1][col1]->GetShape()) == *(m_Matrix[row2][col2]->GetShape()) &&
		*(m_Matrix[row1][col1]->GetShape()) == *(m_Matrix[row3][col3]->GetShape()))
	{
		if (markCells == true)
		{
			m_Matrix[row1][col1]->MarkAsSequence();
			m_Matrix[row2][col2]->MarkAsSequence();
			m_Matrix[row3][col3]->MarkAsSequence();
		}
		return true;
	}
	
	return false;
}

void Board::RollCellsUp(int row, int col)
{
	int markedCellsInCol = 1;
	while (row - markedCellsInCol >= 0)
	{
		while ((row - markedCellsInCol >= 0) && (m_Matrix[row - markedCellsInCol][col]->IsInSequence()))
		{
			markedCellsInCol++;
		}
		if (row-markedCellsInCol >= 0)
		{
			Swap(row, col, row - markedCellsInCol, col);
		}
		row--;
	}
	for (int row = 0 ; row < markedCellsInCol ; row++)
	{
		ReplaceWithNewCell(row, col);
	}
}
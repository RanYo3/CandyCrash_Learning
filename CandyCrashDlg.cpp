
// CandyCrashDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CandyCrash.h"
#include "CandyCrashDlg.h"
#include "afxdialogex.h"

#include "Sh_Triangle.h"
#include "Sh_Ellipse.h"
#include "Sh_Rectangle.h"
#include "Sh_Diamond.h"
#include "Point.h"
#include "Cell.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCandyCrashDlg dialog




CCandyCrashDlg::CCandyCrashDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCandyCrashDlg::IDD, pParent), m_SelectedCell(NULL_POINT)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Board = new Board(7, Point(30, 30), Point(450, 380));
	m_DefaultPen = new CPen(PS_SOLID, 1, RGB(0,0,0));
	m_SelectedPen = new CPen(PS_SOLID, 3, RGB(255,0,0));
}

CCandyCrashDlg::~CCandyCrashDlg()
{
	if (m_Board != NULL)
	{
		delete m_Board;
	}
	if (m_DefaultPen != NULL)
	{
		delete m_DefaultPen;
	}
	if (m_SelectedPen != NULL)
	{
		delete m_SelectedPen;
	}
}

void CCandyCrashDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCandyCrashDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CCandyCrashDlg message handlers

BOOL CCandyCrashDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCandyCrashDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CCandyCrashDlg::PaintShape(Shape *shape, CPaintDC &dc) const
{
	Point *_poly      = shape->GetPolygon();
	ShapeType sh_type = shape->GetType();
	
	CBrush shapeClr(shape->GetColor().GetColorRef());
	CBrush *oldBrush = dc.SelectObject(&shapeClr);

	if (sh_type == ST_Ellipse)
	{
		dc.Ellipse(_poly[0].GetX(), _poly[0].GetY(), _poly[1].GetX(), _poly[1].GetY());
	}
	else if (sh_type == ST_Rectangle)
	{
		dc.Rectangle(_poly[0].GetX(), _poly[0].GetY(), _poly[1].GetX(), _poly[1].GetY());
	}
	else
	{
		int polySize      = shape->GetPolygonSize();
		CPoint *poly = new CPoint[polySize];
		for (int i = 0; i < polySize; i++)
		{
			poly[i] = CPoint(_poly[i].GetX(), _poly[i].GetY());
		}
		dc.Polygon(poly, polySize);
		delete[] poly;
	}

	dc.SelectObject(oldBrush);
}

void CCandyCrashDlg::PaintCell(Cell *cell, CPaintDC &dc) const
{
	Point topLeft = cell->GetTopLeft();
	Point bottomRight = cell->GetBottomRight();

	if (cell->IsSelected())
	{
		dc.SelectObject(m_SelectedPen);
		dc.Rectangle(topLeft.GetX(), topLeft.GetY(), bottomRight.GetX(), bottomRight.GetY());
		dc.SelectObject(m_DefaultPen);
	}
	else
	{
		dc.Rectangle(topLeft.GetX(), topLeft.GetY(), bottomRight.GetX(), bottomRight.GetY());
	}

	PaintShape(cell->GetShape(), dc);
}

void CCandyCrashDlg::PaintBoard(CPaintDC &dc) const
{
	int rows = m_Board->GetRows();
	int cols = m_Board->GetCols();

	Cell *cell;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cell = m_Board->GetCell(i, j);
			PaintCell(cell, dc);
		}
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCandyCrashDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		
		dc.SelectObject(m_DefaultPen);
		PaintBoard(dc);

		//// Triangle
		//Sh_Triangle tri(Point(50, 50), Point(200, 200));
		////PaintCell(
		//PaintShape(&tri, dc);

		//// Ellipse
		//Sh_Ellipse elli(Point(50, 200), Point(200, 300));
		//PaintShape(&elli, dc);

		//// Rectangle
		//Sh_Rectangle rect(Point(200, 50), Point(300, 200));
		//PaintShape(&rect, dc);

		//// Diamond
		//Sh_Diamond dia(Point(200, 200), Point(300, 300));
		//PaintShape(&dia, dc);

		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCandyCrashDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCandyCrashDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	Point press(point);
	Point index;

	if (m_Board->GetCellIndex(press, index))
	{
		if (m_SelectedCell != NULL_POINT)
		{
			m_Board->GetCell(m_SelectedCell)->Select(false);
		}

		if (index != m_SelectedCell)
		{
			m_SelectedCell = index;
			m_Board->GetCell(m_SelectedCell)->Select(true);
		}
		else
		{
			m_SelectedCell = NULL_POINT;
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);

	Invalidate();
}

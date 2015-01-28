
// CandyCrashDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CandyCrash.h"
#include "CandyCrashDlg.h"
#include "afxdialogex.h"

#include "Color.h"

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
	: CDialogEx(CCandyCrashDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_Board = new Board(BOARD_SIZE, BOARD_TOPLEFT, BOARD_BOTTOMRIGHT);

	m_DefaultPen  = new CPen(PS_SOLID, THIN_PEN_WIDTH , Color::GetColorRef(BLACK));
	m_SelectedPen = new CPen(PS_SOLID, THICK_PEN_WIDTH, Color::GetColorRef(BLACK));
	m_MarkPen     = new CPen(PS_SOLID, THICK_PEN_WIDTH, Color::GetColorRef(MAGENTA));

	m_Background  = new CBrush(Color::GetColorRef(HONEYDUE));
	m_BoundaryOut = new CBrush(Color::GetColorRef(BLACK));
	m_BoundaryIn  = new CBrush(Color::GetColorRef(WHITE));

	m_SelectedCell = NULL_POINT;

	m_sequenceEvent = false;
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
	if (m_MarkPen != NULL)
	{
		delete m_MarkPen;
	}
	if (m_Background != NULL)
	{
		delete m_Background;
	}
	if (m_BoundaryOut != NULL)
	{
		delete m_BoundaryOut;
	}
	if (m_BoundaryIn != NULL)
	{
		delete m_BoundaryIn;
	}
	Board *board;
	while (!m_UR_Manager.RecycleIsEmpty())
	{
		board = m_UR_Manager.Redo();
		delete board;
	}
	while (!m_UR_Manager.ObjectsInUseIsEmpty())
	{
		board = m_UR_Manager.Undo();
		delete board;
	}
}

void CCandyCrashDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_UndoBtn, m_UndoBtn);
	DDX_Control(pDX, IDC_RedoBtn, m_RedoBtn);
	DDX_Control(pDX, IDC_SaveBtn, m_SaveBtn);
	DDX_Control(pDX, IDC_LoadBtn, m_LoadBtn);
}

BEGIN_MESSAGE_MAP(CCandyCrashDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_RedoBtn, &CCandyCrashDlg::OnClickedRedoBtn)
	ON_BN_CLICKED(IDC_UndoBtn, &CCandyCrashDlg::OnClickedUndoBtn)
	ON_BN_CLICKED(IDC_LoadBtn, &CCandyCrashDlg::OnClickedLoadBtn)
	ON_BN_CLICKED(IDC_SaveBtn, &CCandyCrashDlg::OnClickedSaveBtn)
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

	CImage UndoIMG;
	CImage RedoIMG;
	CImage SaveImg;
	CImage LoadIMG;
	UndoIMG.Load( _T("edit_undo.png"));
	m_UndoBtn.SetBitmap(UndoIMG);
	RedoIMG.Load( _T("edit_redo.png"));
	m_RedoBtn.SetBitmap(RedoIMG);
	SaveImg.Load( _T("save.png"));
	m_SaveBtn.SetBitmap(SaveImg);
	LoadIMG.Load( _T("open_folder.png"));
	m_LoadBtn.SetBitmap(LoadIMG);

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
	CTypedPtrArray<CObArray, Point *> _poly;
	_poly.Copy(shape->GetPolygon());
	ShapeType sh_type = shape->GetType();
	
	CBrush shapeClr(Color::GetColorRef(shape->GetColor()));
	CBrush *oldBrush = dc.SelectObject(&shapeClr);

	if (sh_type == ST_Ellipse)
	{
		dc.Ellipse(_poly[0]->GetX(), _poly[0]->GetY(), _poly[1]->GetX(), _poly[1]->GetY());
	}
	else if (sh_type == ST_Rectangle)
	{
		dc.Rectangle(_poly[0]->GetX(), _poly[0]->GetY(), _poly[1]->GetX(), _poly[1]->GetY());
	}
	else
	{
		int polySize      = shape->GetPolygonSize();
		CPoint *poly = new CPoint[polySize];
		for (int i = 0; i < polySize; i++)
		{
			poly[i] = CPoint(_poly[i]->GetX(), _poly[i]->GetY());
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
	else if (cell->IsInSequence())
	{
		dc.SelectObject(m_MarkPen);
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
	Point topLeft = m_Board->GetTopLeft() - BOUNDARY_OUT_STROKE;
	Point bottomRight = m_Board->GetBottomRight() + BOUNDARY_OUT_STROKE;

	dc.SelectObject(m_BoundaryOut);
	dc.Rectangle(topLeft.GetX(), topLeft.GetY(), bottomRight.GetX(), bottomRight.GetY());
	
	topLeft = m_Board->GetTopLeft() - BOUNDARY_IN_STROKE;
	bottomRight = m_Board->GetBottomRight() + BOUNDARY_IN_STROKE;

	dc.SelectObject(m_BoundaryIn);
	dc.Rectangle(topLeft.GetX(), topLeft.GetY(), bottomRight.GetX(), bottomRight.GetY());

	dc.SelectObject(m_Background);

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

		dc.SelectObject(m_Background);
		dc.SelectObject(m_DefaultPen);

		PaintBoard(dc);

		CDialogEx::OnPaint();
		

		if (m_sequenceEvent)
		{
			SequenceEventAfterSwap();
			Sleep(DELAY_TIME_MS);
			Invalidate();
		}
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
			if (m_Board->AreNeighbours(index, m_SelectedCell))
			{
				m_UR_Manager.AddNew(new Board(*m_Board));					//save current board status for future undo action
				m_Board->Swap(index, m_SelectedCell);
				m_sequenceEvent = (m_Board->CheckSequence(index) +			// The '+' is instead of || in order to force initiation of...
								   m_Board->CheckSequence(m_SelectedCell));	// both checkSequence() functions regardless of their outcome.
				if (!m_sequenceEvent)
				{
					m_Board->Swap(index, m_SelectedCell);					//Will revert swap if there is no sequence
					m_UR_Manager.DeleteLastReceived();						//Will Delete last saved board from Undo fuanction
				}
				m_SelectedCell = NULL_POINT;
			}
			else
			{
				m_SelectedCell = index;
				m_Board->GetCell(m_SelectedCell)->Select(true);
			}
		}
		else
		{
			m_SelectedCell = NULL_POINT;
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);

	Invalidate();
}

void CCandyCrashDlg::SequenceEventAfterSwap()
{
	m_sequenceEvent=false;

	int minCol;
	int maxCol;
	int maxRow;

	m_Board->DoExplosion(minCol, maxCol, maxRow);

	if (m_Board->CheckSequencesInRange(minCol, maxCol, maxRow))
	{
		m_sequenceEvent=true;
	}
	else
	{
		m_UR_Manager.EmptyRecycled();
	}

}


void CCandyCrashDlg::OnClickedRedoBtn()
{
	if (!m_UR_Manager.RecycleIsEmpty())
	{
		m_UR_Manager.AddNew(m_Board);
		m_Board = m_UR_Manager.Redo();
		Invalidate();
	}
}


void CCandyCrashDlg::OnClickedUndoBtn()
{
	if (!m_UR_Manager.ObjectsInUseIsEmpty())
	{
		m_UR_Manager.AddToRecycled(m_Board);
		m_Board = m_UR_Manager.Undo();
		Invalidate();
	}
}

void CCandyCrashDlg::OnClickedSaveBtn()
{
	CFile theFile;

	theFile.Open(_T("CC_Game"), CFile::modeCreate | CFile::modeWrite);

	CArchive archive(&theFile, CArchive::store);

	m_Board->Serialize(archive);

	archive.Close();
	theFile.Close();
}

void CCandyCrashDlg::OnClickedLoadBtn()
{
	CFile theFile;
	if (PathFileExists( _T("CC_Game")))
	{
		theFile.Open(_T("CC_Game"), CFile::modeRead);
		CArchive archive(&theFile, CArchive::load);

		m_Board->Serialize(archive);

		archive.Close();
		theFile.Close();

		Invalidate();
	}
}

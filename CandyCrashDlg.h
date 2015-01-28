
// CandyCrashDlg.h : header file
//

#pragma once
#include "UndoRedoManager.cpp"
#include "Board.h"
#include "Point.h"
#include "Cell.h"
#include "Shape.h"

// Visual definitions
#define BOUNDARY_OUT_STROKE 20
#define BOUNDARY_IN_STROKE  10
#define BOARD_SIZE          10
#define BOARD_TOPLEFT       Point(50, 50)
#define BOARD_BOTTOMRIGHT   Point(650, 650)
#define NULL_POINT          Point(-1, -1)
#define THIN_PEN_WIDTH      1
#define THICK_PEN_WIDTH     5
#define DELAY_TIME_MS       300

// CCandyCrashDlg dialog
class CCandyCrashDlg : public CDialogEx
{
// Construction
public:
	CCandyCrashDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CCandyCrashDlg();

// Dialog Data
	enum { IDD = IDD_CANDYCRASH_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

private:
	Board *m_Board;
	CPen *m_DefaultPen;
	CPen *m_SelectedPen;
	CPen *m_MarkPen;
	CBrush *m_Background;
	CBrush *m_BoundaryOut;
	CBrush *m_BoundaryIn;
	Point m_SelectedCell;
	bool m_sequenceEvent;
	UndoRedoManager<Board *> m_UR_Manager;
	
	void PaintShape(Shape *shape, CPaintDC &dc) const;
	void PaintCell(Cell *cell, CPaintDC &dc) const;
	void PaintBoard(CPaintDC &dc) const;
	void SequenceEventAfterSwap();

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CButton m_UndoBtn;
	CButton m_RedoBtn;
	afx_msg void OnClickedRedoBtn();
	afx_msg void OnClickedUndoBtn();
	CButton m_SaveBtn;
	CButton m_LoadBtn;
	afx_msg void OnClickedLoadBtn();
	afx_msg void OnClickedSaveBtn();
};

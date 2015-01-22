
// CandyCrashDlg.h : header file
//

#pragma once

#include "Board.h"

#define NULL_POINT Point(-1, -1)

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
	CPen *m_RegularPen;
	CPen *m_SelectedPen;
	Point m_FirstCell;
	
	void PaintShape(Shape *shape, CPaintDC &dc) const;
	void PaintCell(Cell *cell, CPaintDC &dc) const;
	void PaintBoard(CPaintDC &dc) const;

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
};
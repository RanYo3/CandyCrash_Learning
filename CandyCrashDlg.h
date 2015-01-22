
// CandyCrashDlg.h : header file
//

#pragma once

#include "Board.h"

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
};

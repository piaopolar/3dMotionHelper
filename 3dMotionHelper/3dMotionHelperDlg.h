// 3dMotionHelperDlg.h : header file
#pragma once
#include "afxwin.h"

// ============================================================================
//    CMy3dMotionHelperDlg dialog
// ============================================================================
class CMy3dMotionHelperDlg : public CDialog
{
// ----------------------------------------------------------------------------
//    Construction
// ----------------------------------------------------------------------------
public:
	CMy3dMotionHelperDlg(CWnd *pParent = NULL);			// standard constructor

	// Dialog Data
	enum { IDD = IDD_MY3DMOTIONHELPER_DIALOG };
protected:
	virtual void DoDataExchange(CDataExchange *pDX);	// DDX/DDV support

// ----------------------------------------------------------------------------
//    Implementation
// ----------------------------------------------------------------------------
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnDel();
	CString m_cstrPath;
	CEdit m_edtLog;
private:
	enum
	{
		MODE_ACTTYPE,
		MODE_WEAPON,
		MODE_LOOK,
		MODE_MOUNT,
	};
	int GetMode(void) const;
public:
	int m_nData;
};

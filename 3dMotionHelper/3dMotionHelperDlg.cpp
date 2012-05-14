// 3dMotionHelperDlg.cpp : implementation file
#include "stdafx.h"

#include "BaseCode/BaseFunc.h"

#include "3DMotionMgr.h"
#include "3dMotionHelper.h"
#include "3dMotionHelperDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ============================================================================
//    CAboutDlg dialog used for App About
// ============================================================================
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };
protected:
	virtual void DoDataExchange(CDataExchange *pDX);	// DDX/DDV support

// ----------------------------------------------------------------------------
//    Implementation
// ----------------------------------------------------------------------------
protected:
	DECLARE_MESSAGE_MAP()
};

// ============================================================================
// ==============================================================================

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

// ============================================================================
// ==============================================================================
void CAboutDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// ============================================================================
//    CMy3dMotionHelperDlg dialog
// ============================================================================
CMy3dMotionHelperDlg::CMy3dMotionHelperDlg(CWnd *pParent /* NULL */ ) : CDialog(CMy3dMotionHelperDlg::IDD, pParent), m_cstrPath(_T("")), m_nData(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

// ============================================================================
// ==============================================================================
void CMy3dMotionHelperDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PATH, m_cstrPath);
	DDX_Control(pDX, IDC_EDIT_LOG, m_edtLog);
	DDX_Text(pDX, IDC_EDIT_DATA, m_nData);
}

BEGIN_MESSAGE_MAP(CMy3dMotionHelperDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_ADD, &CMy3dMotionHelperDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, &CMy3dMotionHelperDlg::OnBnClickedBtnDel)
END_MESSAGE_MAP()

// ============================================================================
//    CMy3dMotionHelperDlg message handlers
// ============================================================================
BOOL CMy3dMotionHelperDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu. IDM_ABOUTBOX must be in the
	// system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	CMenu *pSysMenu = GetSystemMenu(FALSE);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (pSysMenu != NULL) {

		//~~~~~~~~~~~~~~~~~
		CString strAboutMenu;
		//~~~~~~~~~~~~~~~~~

		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty()) {
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog. The framework does this automatically
	// when the application's main window is not a dialo
	SetIcon(m_hIcon, TRUE);		// Set big icon
	SetIcon(m_hIcon, FALSE);	// Set small icon

	SetLogEdit(&m_edtLog);

	// TODO: Add extra initialization here
	return TRUE;				// return TRUE unless you set the focus to a control
}

// ============================================================================
// ==============================================================================
void CMy3dMotionHelperDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX) {

		//~~~~~~~~~~~~~~~
		CAboutDlg dlgAbout;
		//~~~~~~~~~~~~~~~

		dlgAbout.DoModal();
	} else {
		CDialog::OnSysCommand(nID, lParam);
	}
}

// ============================================================================
//    If you add a minimize button to your dialog, you will need the code below
//    to draw the icon. For MFC applications using the document/view model, this
//    is automatically done for you by the framework.
// ============================================================================
void CMy3dMotionHelperDlg::OnPaint()
{
	if (IsIconic()) {

		//~~~~~~~~~~~~~~
		CPaintDC dc(this);	// device context for painting
		//~~~~~~~~~~~~~~

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM> (dc.GetSafeHdc()), 0);

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		GetClientRect(&rect);

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	} else {
		CDialog::OnPaint();
	}
}

// ============================================================================
//    The system calls this function to obtain the cursor to display while the
//    user drags the minimized window.
// ============================================================================
HCURSOR CMy3dMotionHelperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ============================================================================
// ==============================================================================
void CMy3dMotionHelperDlg::OnBnClickedBtnAdd()
{
	UpdateData(TRUE);
	C3DMotionMgr::GetInstance().SetPath(m_cstrPath);
	switch (this->GetMode()) {
	case MODE_ACTTYPE:	C3DMotionMgr::GetInstance().AddActType(m_nData); break;
	default:			break;
	}
}

// ============================================================================
// ==============================================================================
void CMy3dMotionHelperDlg::OnBnClickedBtnDel()
{
	// TODO: Add your control notification handler code here
}

// ============================================================================
// ==============================================================================
int CMy3dMotionHelperDlg::GetMode(void) const
{
	//~~~~~~~~~~~~~~~~~~~~~
	int nMode = MODE_ACTTYPE;
	//~~~~~~~~~~~~~~~~~~~~~

	if (IsDlgButtonChecked(IDC_RADIO_WEAPON)) {
		nMode = MODE_WEAPON;
	} else if (IsDlgButtonChecked(IDC_RADIO_MONSTER)) {
		nMode = MODE_LOOK;
	} else if (IsDlgButtonChecked(IDC_RADIO_MOUNT)) {
		nMode = MODE_MOUNT;
	}

	return nMode;
}

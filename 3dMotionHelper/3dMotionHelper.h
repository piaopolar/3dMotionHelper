// 3dMotionHelper.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMy3dMotionHelperApp:
// See 3dMotionHelper.cpp for the implementation of this class
//

class CMy3dMotionHelperApp : public CWinApp
{
public:
	CMy3dMotionHelperApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMy3dMotionHelperApp theApp;
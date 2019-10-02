// RanManager.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CRanManagerApp:
// See RanManager.cpp for the implementation of this class
//

class CRanManagerApp : public CWinApp
{
public:
	CRanManagerApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CRanManagerApp theApp;
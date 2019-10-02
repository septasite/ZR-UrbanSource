// RanViewer.h : main header file for the RanViewer application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CRanApp:
// See RanViewer.cpp for the implementation of this class
//

class CRanApp : public CWinApp
{
public:
	CRanApp();

public:
	BOOL		m_bIsActive;
	CString		m_strAppPath;
	char		m_szAppPath[MAX_PATH];

public:
	void		SetActive(BOOL bActive) { m_bIsActive = bActive; };

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int Run();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRanApp theApp;
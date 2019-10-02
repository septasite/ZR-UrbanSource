// item_edit.h : main header file for the item_edit application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// Citem_editApp:
// See item_edit.cpp for the implementation of this class
//

class Citem_editApp : public CWinApp
{
public:
	Citem_editApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Citem_editApp theApp;
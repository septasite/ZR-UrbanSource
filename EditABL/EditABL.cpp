// EditABL.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "EditABL.h"
#include "EditABLDlg.h"
#include "../MfcExLib/MinBugTrap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEditABLApp

BEGIN_MESSAGE_MAP(CEditABLApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CEditABLApp construction

CEditABLApp::CEditABLApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	BUG_TRAP::BugTrapInstall( std::string(_T("EditABL")));
}


// The one and only CEditABLApp object

CEditABLApp theApp;


// CEditABLApp initialization

BOOL CEditABLApp::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	BUG_TRAP::BugTrapInstall( std::string(_T("Edit ABL")));
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CEditABLDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

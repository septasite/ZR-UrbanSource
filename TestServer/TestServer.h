#ifndef TEST_SERVER_H_
#define TEST_SERVER_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "s_CTestServer.h"

// value
HINSTANCE			g_hInst;
HWND				g_hWnd;

HWND				g_hEditBox = NULL;
HWND				g_hWindow = NULL;
BOOL				g_bConnect = FALSE;

CTestServer*		g_pServer;

// function
void	SetFirstFocus(HWND hDlg);
BOOL CALLBACK MainDlgProc(HWND, UINT, WPARAM, LPARAM);

#endif // TEST_SERVER_H_







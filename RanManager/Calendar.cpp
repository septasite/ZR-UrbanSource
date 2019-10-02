// Calendar.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "Calendar.h"
#include ".\calendar.h"
#include "EtcFunction.h"


// CCalendar dialog

IMPLEMENT_DYNAMIC(CCalendar, CDialog)
CCalendar::CCalendar(CWnd* pParent /*=NULL*/)
	: CDialog(CCalendar::IDD, pParent)
{
}

CCalendar::~CCalendar()
{
}

void CCalendar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCalendar, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CCalendar message handlers
BOOL CCalendar::OnInitDialog()
{
	CDialog::OnInitDialog();

	CMonthCalCtrl* pCalendar = (CMonthCalCtrl*)GetDlgItem(IDC_TIME); 
	pCalendar->SetCurSel(&sTime);
	SetWin_Num_int ( this, IDC_EDIT_H, sTime.wHour);
	SetWin_Num_int ( this, IDC_EDIT_M, sTime.wMinute);
	SetWin_Num_int ( this, IDC_EDIT_S, sTime.wSecond);

	return TRUE;  
}

void CCalendar::SetTime (SYSTEMTIME sNewTime)
{
	sTime.wYear  = sNewTime.wYear;	  
	sTime.wMonth = sNewTime.wMonth;	  
	sTime.wDay   = sNewTime.wDay;
	sTime.wHour   = sNewTime.wHour;
	sTime.wMinute   = sNewTime.wMinute;
	sTime.wSecond  = sNewTime.wSecond;
}
void CCalendar::OnBnClickedButtonOk()
{
	CMonthCalCtrl* pCalendar = (CMonthCalCtrl*)GetDlgItem(IDC_TIME); 
	pCalendar->GetCurSel(&sTime);
	sTime.wHour    = GetWin_Num_int ( this, IDC_EDIT_H );
	sTime.wMinute   = GetWin_Num_int ( this, IDC_EDIT_M );
	sTime.wSecond  = GetWin_Num_int ( this, IDC_EDIT_S );
	OnOK();
}

void CCalendar::OnBnClickedButtonCancel()
{
	OnCancel();
}

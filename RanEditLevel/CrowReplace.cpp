// CrowReplace.cpp : implementation file
//

#include "stdafx.h"
#include "RanEditLevel.h"
#include "CrowReplace.h"
#include ".\crowreplace.h"
#include "DlgListCrow.h"
#include "EtcFunction.h"

// CCrowReplace dialog

IMPLEMENT_DYNAMIC(CCrowReplace, CDialog)
CCrowReplace::CCrowReplace(CWnd* pParent /*=NULL*/)
	: CDialog(CCrowReplace::IDD, pParent)
{
}

CCrowReplace::~CCrowReplace()
{
}

void CCrowReplace::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCrowReplace, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CROW, OnBnClickedButtonCrow)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CCrowReplace message handlers
BOOL CCrowReplace::OnInitDialog()
{
	CDialog::OnInitDialog();

	sIDFROM = NATIVEID_NULL();
	sIDTO = NATIVEID_NULL();

	SetWin_Num_int( this, IDC_EDIT_MID_FROM, sIDFROM.wMainID );
	SetWin_Num_int( this, IDC_EDIT_SID_FROM, sIDFROM.wSubID );
	SetWin_Num_int( this, IDC_EDIT_MID_TO, sIDTO.wMainID );
	SetWin_Num_int( this, IDC_EDIT_SID_TO, sIDTO.wSubID );
	SetWin_Text( this, IDC_EDIT_CROW, "" );

	return TRUE;
}

void CCrowReplace::OnBnClickedButtonCrow()
{
	CDlgListCrow dlg;
	if ( dlg.DoModal() == IDOK )
	{
		PCROWDATA pCROW = GLCrowDataMan::GetInstance().GetCrowData( dlg.sIDSELECT );
		if ( pCROW )
		{
			SetWin_Num_int( this, IDC_EDIT_MID_TO, pCROW->m_sBasic.sNativeID.wMainID );
			SetWin_Num_int( this, IDC_EDIT_SID_TO, pCROW->m_sBasic.sNativeID.wSubID );
			SetWin_Text( this, IDC_EDIT_CROW, pCROW->GetName() );
		}
	}
}

void CCrowReplace::OnBnClickedOk()
{
	sIDFROM.wMainID = (WORD)GetWin_Num_int( this, IDC_EDIT_MID_FROM );
	sIDFROM.wSubID = (WORD)GetWin_Num_int( this, IDC_EDIT_SID_FROM );
	sIDTO.wMainID = (WORD)GetWin_Num_int( this, IDC_EDIT_MID_TO );
	sIDTO.wSubID = (WORD)GetWin_Num_int( this, IDC_EDIT_SID_TO );

	OnOK();
}

void CCrowReplace::OnBnClickedCancel()
{
	sIDFROM = NATIVEID_NULL();
	sIDTO = NATIVEID_NULL();

	OnCancel();
}

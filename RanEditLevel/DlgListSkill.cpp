// DlgListSkill.cpp : implementation file
//

#include "stdafx.h"
#include "RanEditLevel.h"
#include "DlgListSkill.h"
#include ".\dlglistskill.h"
#include "EtcFunction.h"


// CDlgListSkill dialog

IMPLEMENT_DYNAMIC(CDlgListSkill, CDialog)
CDlgListSkill::CDlgListSkill(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgListSkill::IDD, pParent)
{
	sIDSELECT = NATIVEID_NULL();
}

CDlgListSkill::~CDlgListSkill()
{
}

void CDlgListSkill::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE, m_ctrlTree);
}


BEGIN_MESSAGE_MAP(CDlgListSkill, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_LIST_CANCEL, OnBnClickedButtonListCancel)
	ON_BN_CLICKED(IDC_BUTTON_LIST_OK, OnBnClickedButtonListOk)
	ON_NOTIFY(NM_CLICK, IDC_TREE, OnNMClickTree)
	ON_NOTIFY(NM_RCLICK, IDC_TREE, OnNMRclickTree)
END_MESSAGE_MAP()


// CDlgListSkill message handlers
BOOL CDlgListSkill::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlTree.DeleteAllItems();

	for( DWORD i = 0 ; i < EMSKILLCLASS_NSIZE ; i ++ )
	{
		m_TreeRoot[i] = m_ctrlTree.InsertItem( COMMENT::SKILLCLASS[i].c_str()  );
	}

	for ( WORD MID=0; MID<EMSKILLCLASS_NSIZE; ++MID )
	for ( WORD SID=0; SID<GLSkillMan::MAX_CLASSSKILL; ++SID )
	{
		GLSKILL* p = GLSkillMan::GetInstance().GetData ( MID, SID );
		if ( p )
		{
			CString str;
			str = GetFormatName ( p );

			hMain = m_ctrlTree.InsertItem( str.GetString(), m_TreeRoot[MID] );
			m_ctrlTree.SetItemData( hMain, (DWORD_PTR) p );
		}
	}


	sIDSELECT = NATIVEID_NULL();

	SetWin_Num_int( this, IDC_EDIT_LIST_MID, 65535 );
	SetWin_Num_int( this, IDC_EDIT_LIST_SID, 65535 );
	SetWin_Text( this, IDC_EDIT_LIST_NAME, "" );

	return TRUE;
}

const char* CDlgListSkill::GetFormatName ( PGLSKILL p )
{
	GASSERT ( p );

	static	CString str;

	if ( p )
	{	
		str.Format ( "[%03d/%03d][%s %s][%02d]  %s",
		p->m_sBASIC.sNATIVEID.wMainID,
		p->m_sBASIC.sNATIVEID.wSubID,
		COMMENT::ANI_MAINTYPE[p->m_sEXT_DATA.emANIMTYPE].c_str(),
		COMMENT::ANI_SUBTYPE_00[p->m_sEXT_DATA.emANISTYPE].c_str(),
		p->m_sBASIC.dwGRADE, 
		p->GetName() );
	}

	return str.GetString ();
}

void CDlgListSkill::OnBnClickedButtonListCancel()
{
	sIDSELECT = NATIVEID_NULL();
	OnCancel();
}

void CDlgListSkill::OnBnClickedButtonListOk()
{
	sIDSELECT.wMainID = GetWin_Num_int( this, IDC_EDIT_LIST_MID );
	sIDSELECT.wSubID = GetWin_Num_int( this, IDC_EDIT_LIST_SID );

	OnOK();
}

void CDlgListSkill::OnNMClickTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	POINT OriginPoint;
	GetCursorPos ( &OriginPoint );

	m_ctrlTree.ScreenToClient( &OriginPoint );
	UINT uFlag = 0;

	HTREEITEM h = m_ctrlTree.HitTest ( CPoint(OriginPoint), &uFlag );

	if ( h )
	{
		m_ctrlTree.SelectItem ( h );
		if ( uFlag & TVHT_ONITEMLABEL )
		{			
			PGLSKILL p =  ( (PGLSKILL)m_ctrlTree.GetItemData ( h ) );

			if ( p )
			{
				SetWin_Num_int( this, IDC_EDIT_LIST_MID, p->m_sBASIC.sNATIVEID.wMainID );
				SetWin_Num_int( this, IDC_EDIT_LIST_SID, p->m_sBASIC.sNATIVEID.wSubID );
				SetWin_Text( this, IDC_EDIT_LIST_NAME, p->GetName() );
			}
		}
	}
}

void CDlgListSkill::OnNMRclickTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	POINT OriginPoint;
	GetCursorPos ( &OriginPoint );
	m_ctrlTree.ScreenToClient( &OriginPoint );

	UINT uFlag = 0;

	HTREEITEM h = m_ctrlTree.HitTest ( CPoint(OriginPoint), &uFlag );

	if ( h )
	{
		m_ctrlTree.SelectItem ( h );
		if ( uFlag & TVHT_ONITEMLABEL )
		{			
			PGLSKILL p =  ( (PGLSKILL)m_ctrlTree.GetItemData ( h ) );

			if ( p )
			{
				SetWin_Num_int( this, IDC_EDIT_LIST_MID, p->m_sBASIC.sNATIVEID.wMainID );
				SetWin_Num_int( this, IDC_EDIT_LIST_SID, p->m_sBASIC.sNATIVEID.wSubID );
				SetWin_Text( this, IDC_EDIT_LIST_NAME, p->GetName() );
			}
		}
	}
}
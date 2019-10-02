// DlgListItem.cpp : implementation file
//

#include "stdafx.h"
#include "RanEditLevel.h"
#include "DlgListItem.h"
#include ".\dlglistitem.h"
#include "EtcFunction.h"


// CDlgListItem dialog

IMPLEMENT_DYNAMIC(CDlgListItem, CDialog)
CDlgListItem::CDlgListItem(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgListItem::IDD, pParent)
{
	sIDSELECT = NATIVEID_NULL();
}

CDlgListItem::~CDlgListItem()
{
}

void CDlgListItem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE, m_ctrlTree);
}


BEGIN_MESSAGE_MAP(CDlgListItem, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_LIST_CANCEL, OnBnClickedButtonListCancel)
	ON_BN_CLICKED(IDC_BUTTON_LIST_OK, OnBnClickedButtonListOk)
	ON_NOTIFY(NM_CLICK, IDC_TREE, OnNMClickTree)
	ON_NOTIFY(NM_RCLICK, IDC_TREE, OnNMRclickTree)
END_MESSAGE_MAP()


// CDlgListItem message handlers
BOOL CDlgListItem::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlTree.DeleteAllItems();
	m_TreeRoot = m_ctrlTree.InsertItem ( "Root Node" );

	for ( int MID = 0; MID < GLItemMan::MAX_MID; MID++ )
	{
		HTREEITEM hMain= NULL;
		HTREEITEM hSub = NULL;

		for ( int SID = 0; SID < GLItemMan::MAX_SID; SID++ )
		{        	

			SITEM* pItem = GLItemMan::GetInstance().GetItem( MID, SID );
			if ( pItem )
			{
				CString str;
				str = GetFormatName ( pItem );

				if ( !hMain )
				{
					hMain = m_ctrlTree.InsertItem ( str, m_TreeRoot );
					m_ctrlTree.SetItemData ( hMain, (DWORD_PTR)pItem );
				}else{
					hSub = m_ctrlTree.InsertItem ( str, hMain );
					m_ctrlTree.SetItemData ( hSub, (DWORD_PTR)pItem );
				}
			}
		}
	}

	sIDSELECT = NATIVEID_NULL();

	SetWin_Num_int( this, IDC_EDIT_LIST_MID, 65535 );
	SetWin_Num_int( this, IDC_EDIT_LIST_SID, 65535 );
	SetWin_Text( this, IDC_EDIT_LIST_NAME, "" );

	return TRUE;
}

const char* CDlgListItem::GetFormatName ( SITEM* p )
{
	GASSERT ( p );

	static	CString str;

	if ( !p )	return "";

	if ( p->sBasicOp.dwReqCharClass==GLCC_NONE)
	{
		str.Format ( "[%04d/%02d] %s            [%d][%s] [%s]   [{%s}]",
			p->sBasicOp.sNativeID.wMainID
			,p->sBasicOp.sNativeID.wSubID
			,p->GetName()
			,p->sGenerateOp.dwSpecID
			,COMMENT::ITEMSUIT[p->sSuitOp.emSuit].c_str()
			,COMMENT::ITEMATTACK[p->sSuitOp.emAttack].c_str()
			, "Unusable" );
	}
	else if ( p->sBasicOp.dwReqCharClass==GLCC_ALL_NEWSEX)
	{
		str.Format ( "[%04d/%02d] %s           [%d][%s] [%s]   [{%s}]",
			p->sBasicOp.sNativeID.wMainID
			,p->sBasicOp.sNativeID.wSubID
			,p->GetName()
			,p->sGenerateOp.dwSpecID
			,COMMENT::ITEMSUIT[p->sSuitOp.emSuit].c_str()
			,COMMENT::ITEMATTACK[p->sSuitOp.emAttack].c_str()
			, "All" );
	}
	else
	{
		str.Format ( "[%04d/%02d] %s           [%d][%s] [%s]   [",
			p->sBasicOp.sNativeID.wMainID
			,p->sBasicOp.sNativeID.wSubID
			,p->GetName()
			,p->sGenerateOp.dwSpecID
			,COMMENT::ITEMSUIT[p->sSuitOp.emSuit].c_str()
			,COMMENT::ITEMATTACK[p->sSuitOp.emAttack].c_str() );

		if ( p->sBasicOp.dwReqCharClass&GLCC_FIGHTER_M )	str += "Brawler[M] | ";
		if ( p->sBasicOp.dwReqCharClass&GLCC_FIGHTER_W )	str += "Brawler[W] | ";
		if ( p->sBasicOp.dwReqCharClass&GLCC_ARMS_M )	str += "Swordsman[M] | ";
		if ( p->sBasicOp.dwReqCharClass&GLCC_ARMS_W )	str += "Swordsman[W] | ";
		if ( p->sBasicOp.dwReqCharClass&GLCC_ARCHER_M )		str += "Archer[M] | ";
		if ( p->sBasicOp.dwReqCharClass&GLCC_ARCHER_W )		str += "Archer[W] | ";
		if ( p->sBasicOp.dwReqCharClass&GLCC_SPIRIT_M )		str += "Shaman[M] | ";
		if ( p->sBasicOp.dwReqCharClass&GLCC_SPIRIT_W )		str += "Shaman[W] | ";
		if ( p->sBasicOp.dwReqCharClass&GLCC_EXTREME_M )	str += "Extreme[M] | ";
		if ( p->sBasicOp.dwReqCharClass&GLCC_EXTREME_W )	str += "Extreme[W] | ";
		if ( p->sBasicOp.dwReqCharClass&GLCC_SCIENCE_M )		str += "Gunner[M] | ";
		if ( p->sBasicOp.dwReqCharClass&GLCC_SCIENCE_W )		str += "Gunner[W] | ";
		if ( p->sBasicOp.dwReqCharClass&GLCC_ASSASSIN_M )	str += "Assassin[M] | ";
		if ( p->sBasicOp.dwReqCharClass&GLCC_ASSASSIN_W )	str += "Assassin[W] | ";
		if ( p->sBasicOp.dwReqCharClass&GLCC_TESTING_M )	str += "Magician[M] | ";
		if ( p->sBasicOp.dwReqCharClass&GLCC_TESTING_W )	str += "Magician[W] | ";
		str += "]";
	}

	return str.GetString ();
}

void CDlgListItem::OnBnClickedButtonListCancel()
{
	sIDSELECT = NATIVEID_NULL();
	OnCancel();
}

void CDlgListItem::OnBnClickedButtonListOk()
{
	sIDSELECT.wMainID = GetWin_Num_int( this, IDC_EDIT_LIST_MID );
	sIDSELECT.wSubID = GetWin_Num_int( this, IDC_EDIT_LIST_SID );

	OnOK();
}

void CDlgListItem::OnNMClickTree(NMHDR *pNMHDR, LRESULT *pResult)
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
			SITEM* p =  ( (SITEM*)m_ctrlTree.GetItemData ( h ) );

			if ( p )
			{
				SetWin_Num_int( this, IDC_EDIT_LIST_MID, p->sBasicOp.sNativeID.wMainID );
				SetWin_Num_int( this, IDC_EDIT_LIST_SID, p->sBasicOp.sNativeID.wSubID );
				SetWin_Text( this, IDC_EDIT_LIST_NAME, p->GetName() );
			}
		}
	}
}

void CDlgListItem::OnNMRclickTree(NMHDR *pNMHDR, LRESULT *pResult)
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
			SITEM* p =  ( (SITEM*)m_ctrlTree.GetItemData ( h ) );

			if ( p )
			{
				SetWin_Num_int( this, IDC_EDIT_LIST_MID, p->sBasicOp.sNativeID.wMainID );
				SetWin_Num_int( this, IDC_EDIT_LIST_SID, p->sBasicOp.sNativeID.wSubID );
				SetWin_Text( this, IDC_EDIT_LIST_NAME, p->GetName() );
			}
		}
	}
}
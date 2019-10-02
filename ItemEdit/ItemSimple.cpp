// ItemProperty2.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ItemEdit.h"
#include "ItemSimple.h"

#include "SheetWithTab.h"
#include "GLItemDef.h"

// CItemSimple 대화 상자입니다.

IMPLEMENT_DYNAMIC(CItemSimple, CPropertyPage)
CItemSimple::CItemSimple()
	: CPropertyPage(CItemSimple::IDD)
{
	m_bDlgInit = FALSE;
	m_pItem = NULL;
	m_pDummyItem = new SITEMSIMPLE;
}

CItemSimple::~CItemSimple()
{
	SAFE_DELETE ( m_pDummyItem );
}

void CItemSimple::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CItemSimple, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_PREV, OnBnClickedButtonPrev)
END_MESSAGE_MAP()


// CItemSimple 메시지 처리기입니다.

void CItemSimple::OnBnClickedButtonCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pItem = NULL;
	m_pSheetTab->SetActivePage ( m_CallPage );
}

void CItemSimple::OnBnClickedButtonOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.	
	InverseUpdateItems();

	*m_pItem = *m_pDummyItem;

	m_pItem = NULL;
	m_pSheetTab->SetActivePage ( m_CallPage );
}

BOOL CItemSimple::SetItem ( SITEMSIMPLE* pItem )
{
	if ( m_pItem )
	{
		return FALSE;
	}

	m_pItem = pItem;

	//	더미로 가져가기
	*m_pDummyItem = *m_pItem;

	if ( m_bDlgInit ) 
	{
		InitDefaultCtrls ();
		UpdateItems ();		
	}

	return TRUE;
}

void CItemSimple::UpdateItems ()
{
	CString	str;
	CComboBox* pComboBox = NULL;
	int nIndex = -1;

	//	간략 아이템의 종류
	pComboBox = (CComboBox*)GetDlgItem ( IDC_COMBO_TYPE );	
	pComboBox->SetCurSel ( m_pDummyItem->sSimpleType );	

	//	갯수
	str.Format ( "%d", m_pDummyItem->dwCount );
	GetDlgItem ( IDC_EDIT_COUNT )->SetWindowText ( str.GetBuffer () );

	//	량
	str.Format ( "%d", m_pDummyItem->dwVolume );
	GetDlgItem ( IDC_EDIT_VOLUME )->SetWindowText ( str.GetBuffer () );		

	//	예약
	str.Format ( "%d", m_pDummyItem->dwRef03 );
	GetDlgItem ( IDC_EDIT_NEEDLEVEL )->SetWindowText ( str.GetBuffer () );

	//	예약
	str.Format ( "%d", m_pDummyItem->dwRef04 );
	GetDlgItem ( IDC_EDIT_INVENSIZEX )->SetWindowText ( str.GetBuffer () );
}

BOOL CItemSimple::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_bDlgInit = TRUE;

	InitDefaultCtrls ();
	UpdateItems ();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CItemSimple::InverseUpdateItems ()
{
	CString	str;
	CComboBox* pComboBox = NULL;
	int nIndex = -1;

	//	간략 아이템의 종류
	pComboBox = (CComboBox*)GetDlgItem ( IDC_COMBO_TYPE );	
	nIndex = pComboBox->GetCurSel ();
	m_pDummyItem->sSimpleType = (EMITEMSIMPLE)nIndex;

	//	갯수
	GetDlgItem ( IDC_EDIT_COUNT )->GetWindowText ( str );
	m_pDummyItem->dwCount = (DWORD) atoi ( str.GetBuffer () );

	//	량	
	GetDlgItem ( IDC_EDIT_VOLUME )->GetWindowText ( str );		
	m_pDummyItem->dwVolume = (DWORD) atoi ( str.GetBuffer () );

	//	예약	
	GetDlgItem ( IDC_EDIT_NEEDLEVEL )->GetWindowText ( str );
	m_pDummyItem->dwRef03 = (DWORD) atoi ( str.GetBuffer () );

	//	예약	
	GetDlgItem ( IDC_EDIT_INVENSIZEX )->GetWindowText ( str );
	m_pDummyItem->dwRef04 = (DWORD) atoi ( str.GetBuffer () );
}

void CItemSimple::OnBnClickedButtonPrev()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	InverseUpdateItems();

	*m_pItem = *m_pDummyItem;

	m_pSheetTab->m_ItemParentPage.SetCallPage ( m_CallPage );
	m_pSheetTab->m_ItemParentPage.SetItem ( m_pItem );
	m_pSheetTab->SetActivePage ( ITEMPARENTPAGE );

	m_pItem = NULL;
}

void CItemSimple::InitDefaultCtrls ()
{
	CComboBox* pComboBox = NULL;

	pComboBox = (CComboBox*) GetDlgItem ( IDC_COMBO_TYPE );	
	while ( pComboBox->GetCount() ) pComboBox->DeleteString ( 0 );	
	for ( int i = 0; i < SIMPLE_NSIZE; i++ )
	{
		pComboBox->AddString ( COMMENT::ITEMSIMPLE[i] );
	}
	pComboBox->SetCurSel ( 0 );

	GetDlgItem ( IDC_BUTTON_NEXT )->EnableWindow ( FALSE );
}
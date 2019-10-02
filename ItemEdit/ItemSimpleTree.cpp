// AllItemView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ItemEdit.h"
#include "SheetWithTab.h"
#include "itemsimpletree.h"

// CItemSimpleTree 대화 상자입니다.

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW

IMPLEMENT_DYNAMIC(CItemSimpleTree, CPropertyPage)
CItemSimpleTree::CItemSimpleTree()
	: CPropertyPage(CItemSimpleTree::IDD)
{
	m_pComboBox = NULL;
	m_pItemNode = NULL;
	m_bDlgInit = FALSE;
	m_pDummyItemNode = new CItemSimpleNode;
	m_bDummyHasItem = FALSE;
}

CItemSimpleTree::~CItemSimpleTree()
{
	SAFE_DELETE ( m_pDummyItemNode );
}

void CItemSimpleTree::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_ITEM, m_ctrlItemTree);
}


BEGIN_MESSAGE_MAP(CItemSimpleTree, CPropertyPage)
	ON_NOTIFY(NM_RCLICK, IDC_TREE_ITEM, OnNMRclickTreeItem)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CItemSimpleTree 메시지 처리기입니다.

BOOL CItemSimpleTree::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_bDlgInit = TRUE;
	UpdateTreeItem ();    

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
void CItemSimpleTree::OnNMRclickTreeItem(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;	

	switch ( GetSelectMenu() )
	{
	case ID_MENUITEM_PARENTMODIFY:
		{
			if ( !m_pItemNode )
			{
				return;
			}
			m_pSheetTab->ActiveItemParentPage ( ITEMSIMPLETREEPAGE, &m_pItemNode->m_sItem );
			m_pComboBox->EnableWindow ( FALSE );
		}
		break;
	case ID_MENUITEM_SIMPLEMODIFY:
		{
			if ( !m_pItemNode )
			{
				return;
			}
			m_pSheetTab->ActiveItemSimplePage ( ITEMSIMPLETREEPAGE, &m_pItemNode->m_sItem );
			m_pComboBox->EnableWindow ( FALSE );
		}
		break;
	case ID_MENUITEM_ADD:
		{
			AddItem ();
		}
		break;
	case ID_MENUITEM_DEL:
		{
			if ( !m_pItemNode )
			{
				return;
			}

			if ( MessageBox ( "정말 삭제하시겠습니까?", "질문", MB_YESNO ) == IDYES )
			{
				DelItem();
			}
		}
		break;
	case ID_MENUITEM_COPY:
		{
			CopyItem ();
		}
		break;
	case ID_MENUITEM_PASTE_NEW:
		{
			PasteItemNew ();
		}
		break;
	case ID_MENUITEM_PASTE_VALUE:
		{
			PasteItemValue ();
		}
		break;
	};
}

BOOL	CItemSimpleTree::AddItem ()
{
	HTREEITEM hMainItem = m_ctrlItemTree.GetSelectedItem ();    
	if ( hMainItem && m_pItemNode )	//	서브로 추가시
	{								//	m_pItemNode를 체크하는 것은, 아이템에 정확하게 클릭했는지를
									//	체크하기 위한 것이다.
		WORD MID = m_pItemNode->m_sItem.sNativeID.wMainID;
		WORD SID = GLItemMan::Instance.FindFreeSimpleSID ( MID );
		if ( SID == ITEMID_NOTFOUND )
		{
			return FALSE;
		}

		m_pItemNode = new CItemSimpleNode;
		m_pItemNode->m_sItem.sNativeID.wMainID = MID;
		m_pItemNode->m_sItem.sNativeID.wSubID = SID;

		char szNewName[ITEM_SZNAME];
		sprintf ( szNewName, "새 아이템[%02d]", SID );
		strcpy ( m_pItemNode->m_sItem.szName, szNewName );
		GLItemMan::Instance.InsertSimple ( MID, SID, m_pItemNode );

		UpdateTreeItem ();

		m_pItemNode = NULL;
		return TRUE;
	}
	else	//	메인으로 추가시
	{
		WORD MID = GLItemMan::Instance.FindFreeSimpleMID ();
		if ( MID == ITEMID_NOTFOUND )
		{
			return FALSE;
		}
		WORD SID = GLItemMan::Instance.FindFreeSimpleSID ( MID );
		if ( SID == ITEMID_NOTFOUND )
		{
			return FALSE;
		}
		
		m_pItemNode = new CItemSimpleNode;
		m_pItemNode->m_sItem.sNativeID.wMainID = MID;
		m_pItemNode->m_sItem.sNativeID.wSubID = SID;
		
		char szNewName[ITEM_SZNAME];
		sprintf ( szNewName, "새 아이템[%03d]", MID );
		strcpy ( m_pItemNode->m_sItem.szName, szNewName );
		GLItemMan::Instance.InsertSimple ( MID, SID, m_pItemNode );

		UpdateTreeItem ();

		m_pItemNode = NULL;

		return TRUE;
	}

	return FALSE;
}

BOOL	CItemSimpleTree::DelItem ()
{
	if ( m_pItemNode )
	{
		WORD WID = m_pItemNode->m_sItem.sNativeID.wMainID;
		WORD SID = m_pItemNode->m_sItem.sNativeID.wSubID;

		if ( SID == 0 )	// 루트를 삭제하는 것이면...
		{
			WORD MaxMain, MaxSub;
			GLItemMan::Instance.GetMaxSimple ( MaxMain, MaxSub );

			for ( int i = 0; i < MaxSub; i++ )
			{
				GLItemMan::Instance.DeleteSimple ( WID, i );
			}
		}
		else
		{
			GLItemMan::Instance.DeleteSimple ( m_pItemNode->m_sItem.sNativeID );
		}
		
		m_pItemNode = NULL;
		UpdateTreeItem ();

		return TRUE;	
	}

	return FALSE;
}

int		CItemSimpleTree::GetSelectMenu ()
{
	POINT OriginPoint, ClientPoint;

	//	<--	우클릭으로 포커스 옮기기
	GetCursorPos ( &OriginPoint );
	ClientPoint = OriginPoint;

	m_ctrlItemTree.ScreenToClient(&ClientPoint);

	UINT uFlag = 0;
	HTREEITEM hItem = m_ctrlItemTree.HitTest ( ClientPoint, &uFlag );
	m_ctrlItemTree.SelectItem ( hItem );

	if ( hItem && uFlag & TVHT_ONITEMLABEL )
	{			
		m_pItemNode = (PITEMSIMPLENODE)m_ctrlItemTree.GetItemData ( hItem );
	}
	else
	{
		m_pItemNode = NULL;
	}
	//	-->


	//	<--	실제 작동 메뉴 따기
	int pMenuID = 0;
	CMenu Menu;

	DWORD SelectionMade = -1;
	//switch ( m_SelectMenu )
	//{
	//case 0:
	//	{
		VERIFY ( Menu.LoadMenu ( IDR_MENU_ITEMSIMPLE_POPUP ) );

		CMenu* pPopup = Menu.GetSubMenu ( pMenuID );
		ASSERT ( pPopup != NULL );	

		SelectionMade = pPopup->TrackPopupMenu (
			TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_NONOTIFY | TPM_RETURNCMD,
			OriginPoint.x, OriginPoint.y, this );

		pPopup->DestroyMenu ();
	//	}
	//	break;
	//}
	//	-->	

	return SelectionMade;
}

BOOL	CItemSimpleTree::UpdateTreeItem ()
{
	if ( !m_bDlgInit )
	{
		return FALSE;
	}

	m_ctrlItemTree.DeleteAllItems ();

	WORD MaxMID, MaxSID;
	GLItemMan::Instance.GetMaxSimple ( MaxMID, MaxSID );

	for ( int MID = 0; MID < MaxMID; MID++ )
	{
		HTREEITEM hMainItem = NULL;
		HTREEITEM hSubItem = NULL;

		for ( int SID = 0; SID < MaxSID; SID++ )
		{        		
			PITEMSIMPLENODE pItem = GLItemMan::Instance.GetSimple ( MID, SID );

			if ( pItem )
			{
				SITEMSIMPLE& rItem = pItem->m_sItem;

				if ( !hMainItem )
				{
					hMainItem = m_ctrlItemTree.InsertItem ( rItem.szName );
					m_ctrlItemTree.SetItemData ( hMainItem, (DWORD_PTR)pItem );
				}
				else
				{
					hSubItem = m_ctrlItemTree.InsertItem ( rItem.szName, hMainItem );
					m_ctrlItemTree.SetItemData ( hSubItem, (DWORD_PTR)pItem );
				}				
			}
		}
	}

	return TRUE;
}

void CItemSimpleTree::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CPropertyPage::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if ( bShow )
	{
		UpdateTreeItem ();

		if ( m_pComboBox && m_pComboBox->m_hWnd )
		{
			m_pComboBox->EnableWindow ( TRUE );
		}
	}
}

void CItemSimpleTree::CleanAllItem ()
{
	if ( !m_bDlgInit )
	{
		return ;
	}

	m_ctrlItemTree.DeleteAllItems ();
}

BOOL	CItemSimpleTree::CopyItem ()
{
	HTREEITEM hMainItem = m_ctrlItemTree.GetSelectedItem ();    
	if ( hMainItem )
	{
		*m_pDummyItemNode = *((PITEMSIMPLENODE)m_ctrlItemTree.GetItemData ( hMainItem ));
		m_bDummyHasItem = TRUE;
		return TRUE;
	}

	return FALSE;
}

BOOL	CItemSimpleTree::PasteItemNew ()
{
	if ( !m_bDummyHasItem )
	{
		return FALSE;
	}

	HTREEITEM hMainItem = m_ctrlItemTree.GetSelectedItem ();
	if ( hMainItem && m_pItemNode )	//	서브로 추가시
	{
		WORD MID = m_pItemNode->m_sItem.sNativeID.wMainID;
		WORD SID = GLItemMan::Instance.FindFreeSimpleSID ( MID );
		if ( SID == ITEMID_NOTFOUND )
		{
			return FALSE;
		}

		m_pItemNode = new CItemSimpleNode;

		*m_pItemNode = *m_pDummyItemNode;

		m_pItemNode->m_sItem.sNativeID.wMainID = MID;
		m_pItemNode->m_sItem.sNativeID.wSubID = SID;
		GLItemMan::Instance.InsertSimple ( MID, SID, m_pItemNode );

		UpdateTreeItem ();
		m_pItemNode = NULL;
		return TRUE;
	}
	else	//	메인으로 추가시
	{
		WORD MID = GLItemMan::Instance.FindFreeSimpleMID ();
		if ( MID == ITEMID_NOTFOUND )
		{
			return FALSE;
		}
		WORD SID = GLItemMan::Instance.FindFreeSimpleSID ( MID );
		if ( SID == ITEMID_NOTFOUND )
		{
			return FALSE;
		}
		
		m_pItemNode = new CItemSimpleNode;

		*m_pItemNode = *m_pDummyItemNode;

		m_pItemNode->m_sItem.sNativeID.wMainID = MID;
		m_pItemNode->m_sItem.sNativeID.wSubID = SID;		
		GLItemMan::Instance.InsertSimple ( MID, SID, m_pItemNode );

		UpdateTreeItem ();
		m_pItemNode = NULL;
		return TRUE;
	}
}

BOOL	CItemSimpleTree::PasteItemValue ()
{
	if ( !m_bDummyHasItem )
	{
		return FALSE;
	}

	HTREEITEM hMainItem = m_ctrlItemTree.GetSelectedItem ();
	if ( hMainItem && m_pItemNode )	//	서브로 추가시
	{
		WORD MID = m_pItemNode->m_sItem.sNativeID.wMainID;
		WORD SID = m_pItemNode->m_sItem.sNativeID.wSubID;

		*m_pItemNode = *m_pDummyItemNode;

		m_pItemNode->m_sItem.sNativeID.wMainID = MID;
		m_pItemNode->m_sItem.sNativeID.wSubID = SID;

		UpdateTreeItem ();
		m_pItemNode = NULL;
		return TRUE;
	}

	return FALSE;
}
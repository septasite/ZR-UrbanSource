// AllItemView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ItemEdit.h"
#include "SheetWithTab.h"



// CAllItemView 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAllItemView, CPropertyPage)
CAllItemView::CAllItemView()
	: CPropertyPage(CAllItemView::IDD)
{
	m_SelectMenu = -1;
}

CAllItemView::~CAllItemView()
{
}

void CAllItemView::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_ITEM, m_ctrlItemTree);
}


BEGIN_MESSAGE_MAP(CAllItemView, CPropertyPage)
	ON_NOTIFY(NM_RCLICK, IDC_TREE_ITEM, OnNMRclickTreeItem)
END_MESSAGE_MAP()


// CAllItemView 메시지 처리기입니다.

BOOL CAllItemView::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	UpdateTreeItem ();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
void CAllItemView::OnNMRclickTreeItem(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;	

	switch ( GetSelectMenu() )
	{
	case ID_MENUITEM_PARENTMODIFY:
		{
			m_pSheetTab->ActiveItemParentPage();			
		}
		break;
	case ID_MENUITEM_SIMPLEMODIFY:
		{
			m_pSheetTab->ActiveItemSimplePage();
		}
		break;
	case ID_MENUITEM_SUITMODIFY:
		{
			m_pSheetTab->ActiveItemSuitPage ();
		}
		break;
	case ID_MENUITEM_ADD:
		{
			m_pSheetTab->ActiveItemParentPage();
		}
		break;
	case ID_MENUITEM_DEL:
		{
			if ( MessageBox ( "정말 삭제하시겠습니까?", "질문", MB_YESNO ) == IDYES )
			{
				MessageBox ( "삭제하였습니다." );
			}
			else
			{				
			}
		}
		break;
	};
}

BOOL	CAllItemView::AddItem ()
{
	return TRUE;
}

void	CAllItemView::SetSelectMenu ( int SelectMenu )
{
	m_SelectMenu = SelectMenu;
}

int		CAllItemView::GetSelectMenu ()
{
	POINT OriginPoint, ClientPoint;

	//	<--	우클릭으로 포커스 옮기기
	GetCursorPos ( &OriginPoint );
	ClientPoint = OriginPoint;

	m_ctrlItemTree.ScreenToClient(&ClientPoint);

	UINT uFlag = 0;
	HTREEITEM hItem = m_ctrlItemTree.HitTest ( ClientPoint, &uFlag );
	m_ctrlItemTree.SelectItem ( hItem );
	//	-->


	//	<--	실제 작동 메뉴 따기
	int pMenuID = 0;
	CMenu Menu;

	DWORD SelectionMade = -1;
	switch ( m_SelectMenu )
	{
	case 0:
		{
		VERIFY ( Menu.LoadMenu ( IDR_MENU_POPUP ) );

		CMenu* pPopup = Menu.GetSubMenu ( pMenuID );
		ASSERT ( pPopup != NULL );	

		SelectionMade = pPopup->TrackPopupMenu (
			TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_NONOTIFY | TPM_RETURNCMD,
			OriginPoint.x, OriginPoint.y, this );

		pPopup->DestroyMenu ();
		}
		break;
	}
	//	-->	

	return SelectionMade;
}

BOOL	CAllItemView::UpdateTreeItem ()
{
	m_ctrlItemTree.DeleteAllItems ();

	for ( int i = 0; i < 4000; i++ )
        m_ctrlItemTree.InsertItem("전체 아이템");	

	return TRUE;
}
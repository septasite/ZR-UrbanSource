#pragma once
#include "afxcmn.h"
#include "GLItemMan.h"

// CItemSimpleTree 대화 상자입니다.
class	CsheetWithTab;
class CItemSimpleTree : public CPropertyPage
{
	DECLARE_DYNAMIC(CItemSimpleTree)

public:
	CItemSimpleTree();   // 표준 생성자입니다.
	virtual ~CItemSimpleTree();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ITEMSIMPLETREE_DIALOG };

protected:
	CsheetWithTab*	m_pSheetTab;
	CWnd*			m_pComboBox;
	BOOL			m_bDlgInit;

public:
	BOOL	UpdateTreeItem ();

public:
	void	SetSheetTab ( CsheetWithTab *pSheetTab ) { m_pSheetTab = pSheetTab; }
	void	SetComboBoxHandle ( CWnd* pWnd ) { m_pComboBox = pWnd; }
	void	CleanAllItem ();

protected:
	PITEMSIMPLENODE	m_pItemNode;

	//	트리에서 아이템을 복사하기 위해 사용
	BOOL			m_bDummyHasItem;
	PITEMSIMPLENODE	m_pDummyItemNode;

protected:
	BOOL	AddItem ();	
	BOOL	DelItem ();
	BOOL	ModifyItem ();

protected:
	BOOL	CopyItem ();
	BOOL	PasteItemNew ();
	BOOL	PasteItemValue ();

protected:
	int		GetSelectMenu ();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_ctrlItemTree;	
	virtual BOOL OnInitDialog();	
	afx_msg void OnNMRclickTreeItem(NMHDR *pNMHDR, LRESULT *pResult);	
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};

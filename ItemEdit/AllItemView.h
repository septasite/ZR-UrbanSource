#pragma once
#include "afxcmn.h"


// CAllItemView 대화 상자입니다.
class	CsheetWithTab;
class CAllItemView : public CPropertyPage
{
	DECLARE_DYNAMIC(CAllItemView)

public:
	CAllItemView();   // 표준 생성자입니다.
	virtual ~CAllItemView();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ALLITEMVIEW_DIALOG };

protected:
	CsheetWithTab	*m_pSheetTab;

protected:
	int		m_SelectMenu;

public:
	void	SetSelectMenu ( int SelectMenu );
	BOOL	UpdateTreeItem ();

public:
	void	SetSheetTab ( CsheetWithTab *pSheetTab ) { m_pSheetTab = pSheetTab; }

protected:
	BOOL	AddItem ();	
	BOOL	DelItem ();
	BOOL	ModifyItem ();

protected:
	int		GetSelectMenu ();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_ctrlItemTree;
	virtual BOOL OnInitDialog();	
	afx_msg void OnNMRclickTreeItem(NMHDR *pNMHDR, LRESULT *pResult);
};

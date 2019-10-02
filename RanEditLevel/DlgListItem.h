#pragma once

#include "GLItem.h"
#include "GLItemMan.h"

// CDlgListItem dialog

class CDlgListItem : public CDialog
{
	DECLARE_DYNAMIC(CDlgListItem)

public:
	CDlgListItem(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgListItem();

// Dialog Data
	enum { IDD = IDD_DLG_LIST_ITEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

private:
	CTreeCtrl		m_ctrlTree;
	HTREEITEM		m_TreeRoot;
	HTREEITEM		hMain;
	HTREEITEM		hSub;
	const char*		GetFormatName ( SITEM* p );

public:
	SNATIVEID		sIDSELECT;

public:
	virtual			BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonListCancel();
	afx_msg void OnBnClickedButtonListOk();
	afx_msg void OnNMClickTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickTree(NMHDR *pNMHDR, LRESULT *pResult);
};

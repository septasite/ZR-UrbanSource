#pragma once

#include "GLCrow.h"

// CDlgListCrow dialog

class CDlgListCrow : public CDialog
{
	DECLARE_DYNAMIC(CDlgListCrow)

public:
	CDlgListCrow(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgListCrow();

// Dialog Data
	enum { IDD = IDD_DLG_LIST_CROW };

private:
	CTreeCtrl		m_ctrlCrowTree;
	HTREEITEM		m_TreeRoot;
	HTREEITEM		hMainCrow;
	HTREEITEM		hSubCrow;
	const char*		GetFormatName ( PCROWDATA pCrow  );

public:
	SNATIVEID		sIDSELECT;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual			BOOL OnInitDialog();

public:
	afx_msg void OnBnClickedButtonListCancel();
	afx_msg void OnBnClickedButtonListOk();
	afx_msg void OnNMClickTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickTree(NMHDR *pNMHDR, LRESULT *pResult);
};

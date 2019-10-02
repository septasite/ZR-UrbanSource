#pragma once

#include "GLSkill.h"
// CDlgListSkill dialog

class CDlgListSkill : public CDialog
{
	DECLARE_DYNAMIC(CDlgListSkill)

public:
	CDlgListSkill(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgListSkill();

// Dialog Data
	enum { IDD = IDD_DLG_LIST_SKILL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

private:
	CTreeCtrl		m_ctrlTree;
	HTREEITEM		m_TreeRoot[EMSKILLCLASS_NSIZE];
	HTREEITEM		hMain;
	HTREEITEM		hSub;
	const char*		GetFormatName ( PGLSKILL p );

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

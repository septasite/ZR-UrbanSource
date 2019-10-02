#pragma once

#include "GLQUEST.h"
#include "GLQUESTMAN.h"
// CDlgListQuest dialog
typedef GLQuestMan::SNODE QUESTNODE;
typedef QUESTNODE*		  PQUESTNODE;

class CDlgListQuest : public CDialog
{
	DECLARE_DYNAMIC(CDlgListQuest)

public:
	CDlgListQuest(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgListQuest();

// Dialog Data
	enum { IDD = IDD_DLG_LIST_QUEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

private:
	CTreeCtrl		m_ctrlTree;
	HTREEITEM		m_TreeRoot;
	HTREEITEM		hMain;
	HTREEITEM		hSub;
	const char*		GetFormatName ( PQUESTNODE p );

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

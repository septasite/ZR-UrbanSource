#pragma once

#include "GLMapList.h"
// CDlgListMap dialog

class CDlgListMap : public CDialog
{
	DECLARE_DYNAMIC(CDlgListMap)

public:
	CDlgListMap(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgListMap();

// Dialog Data
	enum { IDD = IDD_DLG_LIST_MAP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	GLMapList		m_sMapList;
	CListCtrl		m_list_Map;

public:
	SNATIVEID		sIDSELECT;

public:
	virtual			BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonListCancel();
	afx_msg void OnBnClickedButtonListOk();
	afx_msg void OnNMClickListMap(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickListMap(NMHDR *pNMHDR, LRESULT *pResult);
};

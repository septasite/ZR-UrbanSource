#pragma once


// CMapSearch dialog
#include "GLMapList.h"
class	GLMapList;
class CMapSearch : public CDialog
{
	DECLARE_DYNAMIC(CMapSearch)

public:
	CMapSearch(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMapSearch();

// Dialog Data
	enum { IDD = IDD_MAP_DLG };

public:
	static GLMapList m_sMapList;

public:
	CListCtrl		m_list_Map;
	CComboBox		m_cSearchType;
	int				nSelectMID;
	int				nSelectSID;

public:
	void	LoadMap();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonMapsearch();
	afx_msg void OnCbnSelchangeComboSearchType();
};

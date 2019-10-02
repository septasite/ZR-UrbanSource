#pragma once

#include <string>
#include <vector>
#include "GLItem.h"
#include "GLItemMan.h"

// CItemSearch dialog
class CItemSearch : public CDialog
{
	DECLARE_DYNAMIC(CItemSearch)

public:
	CItemSearch(CWnd* pParent = NULL);   // standard constructor
	virtual ~CItemSearch();

// Dialog Data
	enum { IDD = IDD_ITEM_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	typedef std::vector<SITEM*>			VEC_ITEM_SEARCH1;
	typedef VEC_ITEM_SEARCH1::iterator	VEC_ITEM_SEARCH_ITER1;
	typedef std::vector<SITEM*>			VEC_ITEM_SEARCH2;
	typedef VEC_ITEM_SEARCH2::iterator	VEC_ITEM_SEARCH_ITER2;
	typedef std::vector<SNATIVEID>		VEC_ITEM_SEARCH_RESULT;
	typedef VEC_ITEM_SEARCH_RESULT::iterator	VEC_ITEM_SEARCH_ITER_RESULT;

	CListCtrl		m_list_Item;
	CComboBox		m_cSearchType1;
	CComboBox		m_cItemType1;
	CComboBox		m_cSuitType1;
	CComboBox		m_cArmsType1;
	CComboBox		m_cItemLevel1;

	CComboBox		m_cSearchType2;
	CComboBox		m_cItemType2;
	CComboBox		m_cSuitType2;
	CComboBox		m_cArmsType2;
	CComboBox		m_cItemLevel2;

	SNATIVEID		sSelectedItem;
	bool			bMultiple;
	VEC_ITEM_SEARCH1	m_VecSearch1;
	VEC_ITEM_SEARCH2	m_VecSearch2;
	VEC_ITEM_SEARCH_RESULT	m_VecSearchResult;

	void			SearchItem();
	BOOL			Search_1();
	BOOL			Search_2();
	int				nFilter;

	void			SetMultiple(bool bEnable )	{	bMultiple = bEnable;	}
	void			SetFilter( int nVal )	{	nFilter = nVal;	}
	void			InitFilterInfo();

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedButtonItemSearch();
	afx_msg void OnCbnSelchangeComboSearchType();
	afx_msg void OnCbnSelchangeComboSearchType2();
	afx_msg void OnBnClickedButtonShowall();
	afx_msg void OnBnClickedButton2();
};

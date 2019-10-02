#pragma once

#include "GLPet.h"
// CRanManagerPet dialog
class	CRanManagerTab;
class	CRanManagerPetTab;
class CRanManagerPet : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerPet)

public:
	CRanManagerPet(LOGFONT logfont);
	virtual ~CRanManagerPet();

// Dialog Data
	enum { IDD = IDD_RM_PET };

protected:
	CRanManagerTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	CRanManagerPetTab	*m_pPetTab;
	CListCtrl		m_list_Pet;
	CComboBox		m_cSearchType;
	CComboBox		m_cPetPage;

public:
	typedef std::vector<int>			VEC_SEARCH_NUM;
	typedef VEC_SEARCH_NUM::iterator	VEC_SEARCH_NUM_ITER;
	VEC_SEARCH_NUM	m_VecSearchNum;
	int				nPetNum;
	CString			strPet;

public:
	void			SetToolTab		( CRanManagerTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			GetOWnerNames();
	void			GetSearchNum(std::string strSearch);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboPetsearchtype();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonPetSelect();
	afx_msg void OnNMDblclkListPet(NMHDR *pNMHDR, LRESULT *pResult);
};

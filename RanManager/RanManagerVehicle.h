#pragma once

#include "GLVehicle.h"
class	CRanManagerTab;
class	CRanManagerVehicleTab;
// CRanManagerVehicle dialog

class CRanManagerVehicle : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerVehicle)

public:
	CRanManagerVehicle(LOGFONT logfont);
	virtual ~CRanManagerVehicle();

// Dialog Data
	enum { IDD = IDD_RM_VEHICLE };

protected:
	CRanManagerTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	CRanManagerVehicleTab	*m_pVehicleTab;
	CListCtrl		m_list_Vehicle;
	CComboBox		m_cSearchType;
	CComboBox		m_cVehiclePage;

public:
	typedef std::vector<int>			VEC_SEARCH_NUM;
	typedef VEC_SEARCH_NUM::iterator	VEC_SEARCH_NUM_ITER;
	VEC_SEARCH_NUM	m_VecSearchNum;
	int				nVehicleNum;
	CString			strVehicle;

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
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnCbnSelchangeComboVehiclesearchtype();
	afx_msg void OnNMDblclkListVehicle(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonVehicleSelect();
};

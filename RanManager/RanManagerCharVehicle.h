#pragma once

#include "./GLInventory.h"
#include "GLItemMan.h"
#include "GLItem.h"
#include "GLItemDef.h"
#include "GLVEHICLE.h"
#include "GLSummon.h"

// CRanManagerCharVehicle dialog
class	CRanManagerCharTab;
class CRanManagerCharVehicle : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerCharVehicle)

public:
	CRanManagerCharVehicle(LOGFONT logfont);
	virtual ~CRanManagerCharVehicle();

// Dialog Data
	enum { IDD = IDD_RM_CHAR_VEHICLE };

protected:
	CRanManagerCharTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	void			SetToolTab		( CRanManagerCharTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetChar (int nChar);
	void			LoadChar(int nChar);
	void			LoadVehicle(int nChar);

public:
	CListCtrl		m_list_Vehicle;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonVehicleCancel();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonDeleteAll();
};

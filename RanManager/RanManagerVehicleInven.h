#pragma once

#include "GLItemMan.h"
#include "GLItem.h"
#include "GLItemDef.h"
// CRanManagerVehicleInven dialog
class	CRanManagerVehicleTab;
class CRanManagerVehicleInven : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerVehicleInven)

public:
	CRanManagerVehicleInven(LOGFONT logfont);
	virtual ~CRanManagerVehicleInven();

// Dialog Data
	enum { IDD = IDD_RM_VEHICLE_INVEN };

protected:
	CRanManagerVehicleTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	void			SetToolTab		( CRanManagerVehicleTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetVehicle(int nVehicleNum);
	void			GetVehicle(int nVehicleNum);
	void			GetVehicleInven(int nVehicleNum);
	void			ShowItem(int nSlot);
	void			ShowPutOn();

public:
	SITEMCUSTOM		m_PutOnItems[ACCE_TYPE_SIZE];
	CComboBox		m_cGenType;
	CComboBox		m_cRandomOp1;
	CComboBox		m_cRandomOp2;
	CComboBox		m_cRandomOp3;
	CComboBox		m_cRandomOp4;

public:
	void			SetPutOnItemState ( CDialog *pDlg,int nID );
	void			ResetPutOnItemState ( CDialog *pDlg );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonVp1();
	afx_msg void OnBnClickedButtonVp2();
	afx_msg void OnBnClickedButtonVp3();
	afx_msg void OnBnClickedButtonVp4();
	afx_msg void OnBnClickedButtonVp5();
	afx_msg void OnBnClickedButtonVp6();
	afx_msg void OnBnClickedButtonVp7();
	afx_msg void OnBnClickedButtonItemsearchM();
	afx_msg void OnBnClickedButtonItemsearchCos();
	afx_msg void OnBnClickedButtonResetCosExpire();
	afx_msg void OnBnClickedBtnEditItemDelete();
	afx_msg void OnBnClickedBtnEditItemUpdate();
	afx_msg void OnBnClickedBtnEditSave();
	afx_msg void OnBnClickedBtnEditCancel();
};

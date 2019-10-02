#pragma once

#include "GLItemMan.h"
#include "GLItem.h"
#include "GLItemDef.h"
// CRanManagerCharPutOn dialog
class	CRanManagerCharTab;
class CRanManagerCharPutOn : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerCharPutOn)

public:
	CRanManagerCharPutOn(LOGFONT logfont);
	virtual ~CRanManagerCharPutOn();

// Dialog Data
	enum { IDD = IDD_RM_CHAR_PUTON };

protected:
	CRanManagerCharTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	SITEMCUSTOM		m_PutOnItems[SLOT_TSIZE];
	CComboBox		m_cGenType;
	CComboBox		m_cRandomOp1;
	CComboBox		m_cRandomOp2;
	CComboBox		m_cRandomOp3;
	CComboBox		m_cRandomOp4;
	int				nSlotSelected;

public:
	void			SetToolTab		( CRanManagerCharTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetChar (int nChar);
	void			ReadChar (int nChar);
	void			ReadPutOn (int nChar);
	void			ShowPutOn ();
	void			SelectSlot(int nSlot);
	void			SetPutOnItemState ( CDialog *pDlg,int nID );
	void			ResetPutOnItemState ( CDialog *pDlg );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonP0();
	afx_msg void OnBnClickedButtonP1();
	afx_msg void OnBnClickedButtonP2();
	afx_msg void OnBnClickedButtonP3();
	afx_msg void OnBnClickedButtonP4();
	afx_msg void OnBnClickedButtonP5();
	afx_msg void OnBnClickedButtonP6();
	afx_msg void OnBnClickedButtonP7();
	afx_msg void OnBnClickedButtonP8();
	afx_msg void OnBnClickedButtonP9();
	afx_msg void OnBnClickedButtonP10();
	afx_msg void OnBnClickedButtonP11();
	afx_msg void OnBnClickedButtonP12();
	afx_msg void OnBnClickedButtonP13();
	afx_msg void OnBnClickedButtonP14();
	afx_msg void OnBnClickedButtonP15();
	afx_msg void OnBnClickedButtonP16();
	afx_msg void OnBnClickedButtonP17();
	afx_msg void OnBnClickedButtonP18();
	afx_msg void OnBnClickedButtonP19();
	afx_msg void OnBnClickedButtonItemsearchM();
	afx_msg void OnBnClickedButtonItemsearchCos();
	afx_msg void OnBnClickedButtonResetCosExpire();
	afx_msg void OnBnClickedBtnEditItemDelete();
	afx_msg void OnBnClickedBtnEditItemUpdate();
	afx_msg void OnBnClickedBtnEditItemDeleteAll();
	afx_msg void OnBnClickedButtonPutonSave();
	afx_msg void OnBnClickedButtonPutonCancel();
	afx_msg void OnCbnSelchangeComboGentype();
};

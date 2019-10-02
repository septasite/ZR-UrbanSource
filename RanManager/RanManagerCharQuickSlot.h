#pragma once

#include "./GLCharData.h"
// CRanManagerCharQuickSlot dialog
class	CRanManagerCharTab;
class CRanManagerCharQuickSlot : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerCharQuickSlot)

public:
	CRanManagerCharQuickSlot(LOGFONT logfont);
	virtual ~CRanManagerCharQuickSlot();

// Dialog Data
	enum { IDD = IDD_RM_CHAR_QUICKSLOT };

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
	void			LoadQuickSlot(int nChar);
	void			ShowQuickSlot();
	void			LoadSlot(int nSlot);
	void			SetSlotState ( CDialog *pDlg,int nID );
	void			ResetSlotState ( CDialog *pDlg );

public:
	SACTION_SLOT			m_sACTIONQUICK[EMACTIONQUICK_SIZE];	
	int				nSelectedSlot;
	CComboBox		m_cActType;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonQuickslotSave();
	afx_msg void OnBnClickedButtonQuickslotCancel();
	afx_msg void OnBnClickedButtonQuick0();
	afx_msg void OnBnClickedButtonQuick1();
	afx_msg void OnBnClickedButtonQuick2();
	afx_msg void OnBnClickedButtonQuick3();
	afx_msg void OnBnClickedButtonQuick4();
	afx_msg void OnBnClickedButtonQuick5();
	afx_msg void OnBnClickedButtonQChange();
	afx_msg void OnBnClickedButtonQDelete();
	afx_msg void OnBnClickedButtonQSave();
	afx_msg void OnBnClickedButtonDeleteAllQ();
};

#pragma once

#include "GLItemMan.h"
#include "GLItem.h"
#include "GLItemDef.h"
#include "GLMapList.h"
// CRanManagerCharEdit dialog
class	CRanManagerCharTab;
class	GLMapList;
class CRanManagerCharEdit : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerCharEdit)

public:
	CRanManagerCharEdit(LOGFONT logfont);
	virtual ~CRanManagerCharEdit();

// Dialog Data
	enum { IDD = IDD_RM_CHAR_EDIT };

protected:
	CRanManagerCharTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	static GLMapList m_sMapList;

public:
	void			SetToolTab		( CRanManagerCharTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetChar (int nChar);
	void			LoadChar (int nChar);	
	void			GetGuild (int nGuNum);	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboEmclass();
	afx_msg void OnBnClickedButtonChareditSave();
	afx_msg void OnBnClickedButtonChareditCalcel();
	afx_msg void OnBnClickedButtonCheckname();
	afx_msg void OnBnClickedButtonRemoveguild();
	afx_msg void OnBnClickedButtonTransferguild();
	afx_msg void OnBnClickedButtonMapeditStart();
	afx_msg void OnBnClickedButtonMapeditSave();
	afx_msg void OnBnClickedButtonMapeditRet();
	afx_msg void OnBnClickedButtonSpChange();
	afx_msg void OnBnClickedButtonSetC1();
	afx_msg void OnBnClickedButtonSetC2();
	afx_msg void OnBnClickedButtonSetC3();
	afx_msg void OnBnClickedButtonResetC1();
	afx_msg void OnBnClickedButtonResetC2();
	afx_msg void OnBnClickedButtonResetC3();
	afx_msg void OnEnChangeEditSpMid();
};

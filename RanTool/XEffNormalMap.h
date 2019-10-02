#pragma once

#include "DxEffCharNormal.h"
// CEffNormalMap dialog
class	CEffTab;

class CEffNormalMap : public CPropertyPage
{
	DECLARE_DYNAMIC(CEffNormalMap)

public:
	CEffNormalMap(LOGFONT logfont);
	virtual ~CEffNormalMap();

// Dialog Data
	enum { IDD = IDD_XNORMALMAP };

protected:
	CEffTab*		m_pEffTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	DxEffCharNormal*	EffNormalEdit;

public:
	void			SetEffTab		( CEffTab *pEffTab ) { m_pEffTab = pEffTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetEffNormal ( DxEffCharNormal*	EffNormalX);
	BOOL			Update ();
	BOOL			Save ();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
};

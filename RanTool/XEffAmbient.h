#pragma once

#include "DxEffCharAmbient.h"
// CEffAmbient dialog
class	CEffTab;

class CEffAmbient : public CPropertyPage
{
	DECLARE_DYNAMIC(CEffAmbient)

public:
	CEffAmbient(LOGFONT logfont);
	virtual ~CEffAmbient();

// Dialog Data
	enum { IDD = IDD_XAMBIENT };

protected:
	CEffTab*		m_pEffTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	DxEffCharAmbient*	EffAmbientEdit;

public:
	void			SetEffTab		( CEffTab *pEffTab ) { m_pEffTab = pEffTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetEffAmbient ( DxEffCharAmbient*	EffAmbientX);
	BOOL			Update ();
	BOOL			Save ();


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnCbnSelchangeComboColop();
};

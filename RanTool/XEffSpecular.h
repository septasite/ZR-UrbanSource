#pragma once

#include "DxEffCharSpecular.h"
// CEffSpecular dialog
class	CEffTab;

class CEffSpecular : public CPropertyPage
{
	DECLARE_DYNAMIC(CEffSpecular)

public:
	CEffSpecular(LOGFONT logfont);
	virtual ~CEffSpecular();

// Dialog Data
	enum { IDD = IDD_XSPECULAR };

protected:
	CEffTab*		m_pEffTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	DxEffCharSpecular*	EffSpecularEdit;

public:
	void			SetEffTab		( CEffTab *pEffTab ) { m_pEffTab = pEffTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetEffSpecular ( DxEffCharSpecular*	EffSpecularX);
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

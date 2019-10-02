#pragma once

#include "DxEffCharParticle.h"
// CEffParticle dialog
class	CEffTab;

class CEffParticle : public CPropertyPage
{
	DECLARE_DYNAMIC(CEffParticle)

public:
	CEffParticle(LOGFONT logfont);
	virtual ~CEffParticle();

// Dialog Data
	enum { IDD = IDD_XPARTICLE };

protected:
	CEffTab*		m_pEffTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;
	bool			bAdd;
	int				nLastEdit;

public:
	DxEffCharParticle*	EffParticleEdit;
	CListBox		m_list_vec;

public:
	void			SetEffTab		( CEffTab *pEffTab ) { m_pEffTab = pEffTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetEffParticle ( DxEffCharParticle*	EffParticleX);
	BOOL			Update ();
	BOOL			UpdateList ();
	BOOL			Save ();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedButtonPadd();
	afx_msg void OnBnClickedButtonPedit();
	afx_msg void OnBnClickedButtonPdel();
	afx_msg void OnBnClickedButtonPclr();
	afx_msg void OnBnClickedButtonPmup();
	afx_msg void OnBnClickedButtonPmdn();
	afx_msg void OnBnClickedButtonPok();
	afx_msg void OnBnClickedButtonPcan();
};

#pragma once

#include "DxEffCharBonePosEff.h"
// CEffBonePos dialog
class	CEffTab;

class CEffBonePos : public CPropertyPage
{
	DECLARE_DYNAMIC(CEffBonePos)

public:
	CEffBonePos(LOGFONT logfont);
	virtual ~CEffBonePos();

// Dialog Data
	enum { IDD = IDD_XBONEPOS };

protected:
	CEffTab*		m_pEffTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	DxEffCharBonePosEff*	EffBonePosEdit;

public:
	void			SetEffTab		( CEffTab *pEffTab ) { m_pEffTab = pEffTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetEffBonePos ( DxEffCharBonePosEff*	EffBonePosX);
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

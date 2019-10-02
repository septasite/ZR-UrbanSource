#pragma once

#include "DxEffAniGhosting.h"
// AEffGhosting dialog
class	AEffTab;

class AEffGhosting : public CPropertyPage
{
	DECLARE_DYNAMIC(AEffGhosting)

public:
	AEffGhosting(LOGFONT logfont);
	virtual ~AEffGhosting();

// Dialog Data
	enum { IDD = IDD_ZGHOSTING };

protected:
	AEffTab*		m_pEffTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	DxEffAniData_Ghosting*	EffGhostingEdit;

public:
	void			SetEffTab		( AEffTab *pEffTab ) { m_pEffTab = pEffTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetEffGhosting ( DxEffAniData_Ghosting*	EffGhostingX );
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

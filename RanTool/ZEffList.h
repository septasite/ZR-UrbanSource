#pragma once

#include "SAnimation.h"
#include "DxEffAni.h"
#include "DxEffAniSingle.h"
#include "DxEffAniGhosting.h"
#include "DxEffAniFaceOff.h"
#include "DxEffAniTrace.h"

// AEffList dialog
class	AEffTab;

class AEffList : public CPropertyPage
{
	DECLARE_DYNAMIC(AEffList)

public:
	AEffList(LOGFONT logfont);
	virtual ~AEffList();

// Dialog Data
	enum { IDD = IDD_ZLIST };

protected:
	AEffTab*		m_pEffTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;
	bool			bAddEffect;
	int				nLastEdit;

public:
	SANIMCONINFO::EFFANILIST		m_ListEFFECT;
	void	SetEffectData ( SANIMCONINFO::EFFANILIST	m_ListEFFECTX );
	SANIMCONINFO::EFFANILIST		GetListEffect() { return m_ListEFFECT; }

	void				SetEffSingle ( DxEffAniData_Single* EffSingleX );
	void				SetEffGhosting ( DxEffAniData_Ghosting* EffGhostingX );
	void				SetEffTrace ( DxEffAniData_Trace* EffTraceX );
	void				SetEffFaceOff ( DxEffAniData_FaceOff* EffFaceOffX );

public:
	CListBox		m_list_effect;
	CComboBox		m_cEffectType;
	void			SetEffTab		( AEffTab *pEffTab ) { m_pEffTab = pEffTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			UpdateListEffect();


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedEffAdd();
	afx_msg void OnBnClickedEffEdit();
	afx_msg void OnBnClickedEffDel();
	afx_msg void OnBnClickedEffClear();
	afx_msg void OnBnClickedEffCopy();
	afx_msg void OnBnClickedEffSelect();
	afx_msg void OnBnClickedEffCancel();
};

#pragma once

#include "../../EngineLib/Meshs/DxSkinAniMan.h"
#include "../../EngineLib/Meshs/DxPieceDefine.h"
#include "../../EngineLib/Meshs/SAnimation.h"
// CTabCFG dialog

class	CToolTab;
class	AEffTab;

class CTabCFG : public CPropertyPage
{
	DECLARE_DYNAMIC(CTabCFG)

public:
	CTabCFG(LOGFONT logfont);
	virtual ~CTabCFG();

	enum { IDD = IDD_CFG_DIALOG };

protected:
	AEffTab*		m_pEffTab;
	CToolTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;
	BOOL			m_bActive;
	bool			bAddScale;
	int				nLastEditScale;
	bool			bAddData;
	int				nLastEditData;
	CString			strFileName;

public:
	void			Reset();
	void			SetToolTab		( CToolTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	SANIMCONINFO	m_AniInfo;
	//DxAniScale::MAP_ANISCALEMAIN	m_mapAniScaleMainX;
	DxAniScaleMAIN* pNewScale;
	CListBox		m_list_scale;
	CListBox		m_list_data;

public:
	void UpdateData();
	void UpdateListScale();
	void UpdateListData(DxAniScaleMAIN*	pData);
	BOOL SaveData();

public:
	virtual	BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedBtnScAdd();
	afx_msg void OnBnClickedBtnScEdit();
	afx_msg void OnBnClickedBtnScDel();
	afx_msg void OnBnClickedBtnScClear();
	afx_msg void OnBnClickedBtnScOk();
	afx_msg void OnBnClickedBtnScCan();
	afx_msg void OnBnClickedBtnScmAdd();
	afx_msg void OnBnClickedBtnScmEdit();
	afx_msg void OnBnClickedBtnScmDel();
	afx_msg void OnBnClickedBtnScmClear();
	afx_msg void OnBnClickedBtnScmOk();
	afx_msg void OnBnClickedBtnScmCan();
	afx_msg void OnBnClickedButtonNew();
};

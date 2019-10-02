#pragma once

#include "GLItemMan.h"
#include "GLItem.h"
#include "GLItemDef.h"
// CRanManagerCharCoolDown dialog
class	CRanManagerCharTab;
class CRanManagerCharCoolDown : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerCharCoolDown)

public:
	CRanManagerCharCoolDown(LOGFONT logfont);
	virtual ~CRanManagerCharCoolDown();

// Dialog Data
	enum { IDD = IDD_RM_CHAR_COOLDOWN };

protected:
	CRanManagerCharTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	void			LoadChar(int nChar);
	void			LoadCoolDown(int nChar);
	void			ShowCoolDownID();
	void			ShowCoolDownType();

public:
	CListCtrl		m_list_CD_ID;
	CListCtrl		m_list_CD_TYPE;

public:
	typedef std::map<DWORD,ITEM_COOLTIME>	COOLTIME_MAP;
	typedef COOLTIME_MAP::iterator			COOLTIME_MAP_ITER;
	typedef COOLTIME_MAP::const_iterator	COOLTIME_MAP_CITER;

	COOLTIME_MAP		m_mapCoolTimeType;	
    COOLTIME_MAP		m_mapCoolTimeID;

public:
	void			SetToolTab		( CRanManagerCharTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetChar (int nChar);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonIdDelete();
	afx_msg void OnBnClickedButtonIdDeleteall();
	afx_msg void OnBnClickedButtonTypeDelete();
	afx_msg void OnBnClickedButtonTypeDeleteall();
	afx_msg void OnBnClickedButtonCooldownSve();
	afx_msg void OnBnClickedButtonCooldownCancel();
};

#pragma once

#include "./GLInventory.h"
#include "GLItemMan.h"
#include "GLItem.h"
#include "GLItemDef.h"
// CRanManagerGuildLocker dialog
class	CRanManagerGuildTab;
class CRanManagerGuildLocker : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerGuildLocker)

public:
	CRanManagerGuildLocker(LOGFONT logfont);
	virtual ~CRanManagerGuildLocker();

// Dialog Data
	enum { IDD = IDD_RM_GUILD_LOCKER };

	enum
	{
		LOCKER_SIZE = 5
	};

protected:
	CRanManagerGuildTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	void			SetToolTab		( CRanManagerGuildTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetGuild(int nGuildNum);
	void			GetGuild(int nGuildNum);
	void			GetGuildMoney(int nGuildNum);
	void			LoadLocker(int nGuildNum);
	void			InitLockerInven();

	void			ViewLockerItem(WORD X,WORD Y);
	void			SetLockerItemState ( CDialog *pDlg,int nID );
	void			ResetLockerItemState ( CDialog *pDlg );
	void			SetLockerPageState ( CDialog *pDlg,int nID );
	void			ResetLockerPageState ( CDialog *pDlg );
	void			ResetLockerItem(WORD X,WORD Y);

public:
	GLInventory		m_cStorage[LOCKER_SIZE];
	CComboBox		m_cGenType;
	CComboBox		m_cRandomOp1;
	CComboBox		m_cRandomOp2;
	CComboBox		m_cRandomOp3;
	CComboBox		m_cRandomOp4;

public:
	int				nActivePage;
	int				nActiveItem_X;
	int				nActiveItem_Y;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnEditCancelLocker();
	afx_msg void OnBnClickedBtnEditSaveLocker();
	afx_msg void OnBnClickedButtonP1();
	afx_msg void OnBnClickedButtonP2();
	afx_msg void OnBnClickedButtonP3();
	afx_msg void OnBnClickedButtonP4();
	afx_msg void OnBnClickedButtonP5();
	afx_msg void OnBnClickedButton00();
	afx_msg void OnBnClickedButton01();
	afx_msg void OnBnClickedButton02();
	afx_msg void OnBnClickedButton03();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton20();
	afx_msg void OnBnClickedButton21();
	afx_msg void OnBnClickedButton22();
	afx_msg void OnBnClickedButton23();
	afx_msg void OnBnClickedButton30();
	afx_msg void OnBnClickedButton31();
	afx_msg void OnBnClickedButton32();
	afx_msg void OnBnClickedButton33();
	afx_msg void OnBnClickedButton40();
	afx_msg void OnBnClickedButton41();
	afx_msg void OnBnClickedButton42();
	afx_msg void OnBnClickedButton43();
	afx_msg void OnBnClickedButton50();
	afx_msg void OnBnClickedButton51();
	afx_msg void OnBnClickedButton52();
	afx_msg void OnBnClickedButton53();
	afx_msg void OnBnClickedButtonItemsearchM();
	afx_msg void OnBnClickedButtonItemsearchCos();
	afx_msg void OnBnClickedButtonResetCosExpire();
	afx_msg void OnBnClickedBtnEditItemDelete();
	afx_msg void OnBnClickedBtnEditItemUpdate();
	afx_msg void OnBnClickedBtnEditItemClear();
	afx_msg void OnBnClickedBtnEditItemClearall();
};

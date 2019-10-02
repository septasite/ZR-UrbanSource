#pragma once

#include "./GLInventory.h"
#include "GLItemMan.h"
#include "GLItem.h"
#include "GLItemDef.h"
// CRanManagerUserLocker dialog
class	CRanManagerUserTab;
class CRanManagerUserLocker : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerUserLocker)

public:
	CRanManagerUserLocker(LOGFONT logfont);
	virtual ~CRanManagerUserLocker();

// Dialog Data
	enum { IDD = IDD_RM_USER_LOCKER };

	enum
	{
		LOCKER_SIZE = 5
	};

protected:
	CRanManagerUserTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

	int				nActivePage;
	int				nActiveItem_X;
	int				nActiveItem_Y;

public:
	void			SetToolTab		( CRanManagerUserTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetUser(int nUser);
	void			LoadUser(int nUser);
	void			LoadLocker(int nUser);
	void			LoadLockerBinary(int nUser);
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


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSet1();
	afx_msg void OnBnClickedButtonSet2();
	afx_msg void OnBnClickedButtonSet3();
	afx_msg void OnBnClickedButtonReset1();
	afx_msg void OnBnClickedButtonReset2();
	afx_msg void OnBnClickedButtonReset3();
	afx_msg void OnBnClickedButton00();
	afx_msg void OnBnClickedButton01();
	afx_msg void OnBnClickedButton02();
	afx_msg void OnBnClickedButton03();
	afx_msg void OnBnClickedButton04();
	afx_msg void OnBnClickedButton05();
	afx_msg void OnBnClickedButton06();
	afx_msg void OnBnClickedButton07();
	afx_msg void OnBnClickedButton08();
	afx_msg void OnBnClickedButton09();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton19();
	afx_msg void OnBnClickedButton20();
	afx_msg void OnBnClickedButton21();
	afx_msg void OnBnClickedButton22();
	afx_msg void OnBnClickedButton23();
	afx_msg void OnBnClickedButton24();
	afx_msg void OnBnClickedButton25();
	afx_msg void OnBnClickedButton26();
	afx_msg void OnBnClickedButton27();
	afx_msg void OnBnClickedButton28();
	afx_msg void OnBnClickedButton29();
	afx_msg void OnBnClickedButton30();
	afx_msg void OnBnClickedButton31();
	afx_msg void OnBnClickedButton32();
	afx_msg void OnBnClickedButton33();
	afx_msg void OnBnClickedButton34();
	afx_msg void OnBnClickedButton35();
	afx_msg void OnBnClickedButton36();
	afx_msg void OnBnClickedButton37();
	afx_msg void OnBnClickedButton38();
	afx_msg void OnBnClickedButton39();
	afx_msg void OnBnClickedButton40();
	afx_msg void OnBnClickedButton41();
	afx_msg void OnBnClickedButton42();
	afx_msg void OnBnClickedButton43();
	afx_msg void OnBnClickedButton44();
	afx_msg void OnBnClickedButton45();
	afx_msg void OnBnClickedButton46();
	afx_msg void OnBnClickedButton47();
	afx_msg void OnBnClickedButton48();
	afx_msg void OnBnClickedButton49();
	afx_msg void OnBnClickedButton50();
	afx_msg void OnBnClickedButton51();
	afx_msg void OnBnClickedButton52();
	afx_msg void OnBnClickedButton53();
	afx_msg void OnBnClickedButton54();
	afx_msg void OnBnClickedButton55();
	afx_msg void OnBnClickedButton56();
	afx_msg void OnBnClickedButton57();
	afx_msg void OnBnClickedButton58();
	afx_msg void OnBnClickedButton59();
	afx_msg void OnBnClickedButtonP1();
	afx_msg void OnBnClickedButtonP2();
	afx_msg void OnBnClickedButtonP3();
	afx_msg void OnBnClickedButtonP4();
	afx_msg void OnBnClickedButtonP5();
	afx_msg void OnBnClickedButtonItemsearchM();
	afx_msg void OnBnClickedButtonItemsearchCos();
	afx_msg void OnCbnSelchangeComboGentype();
	afx_msg void OnBnClickedBtnEditItemUpdate();
	afx_msg void OnBnClickedBtnEditItemDelete();
	afx_msg void OnBnClickedBtnEditItemClear();
	afx_msg void OnBnClickedBtnEditItemClearall();
	afx_msg void OnBnClickedBtnEditCancelLocker();
	afx_msg void OnBnClickedButtonResetCosExpire();
	afx_msg void OnBnClickedBtnEditSaveLocker();
};

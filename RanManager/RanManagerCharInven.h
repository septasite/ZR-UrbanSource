#pragma once

#include "./GLInventory.h"
#include "GLItemMan.h"
#include "GLItem.h"
#include "GLItemDef.h"
// CRanManagerCharInven dialog
class	CRanManagerCharTab;
class CRanManagerCharInven : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerCharInven)

public:
	CRanManagerCharInven(LOGFONT logfont);
	virtual ~CRanManagerCharInven();

// Dialog Data
	enum { IDD = IDD_RM_CHAR_INVEN };

protected:
	CRanManagerCharTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	GLInventory				m_cInventory;
	CComboBox		m_cGenType;
	CComboBox		m_cRandomOp1;
	CComboBox		m_cRandomOp2;
	CComboBox		m_cRandomOp3;
	CComboBox		m_cRandomOp4;
	int				nActiveItem_X;
	int				nActiveItem_Y;

public:
	void			SetToolTab		( CRanManagerCharTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetChar (int nChar);
	void			ReadChar (int nChar);
	void			ReadInven (int nChar);
	void			ShowInven ();
	void			ViewItem(WORD X,WORD Y);
	void			SetInvenItemState ( CDialog *pDlg,int nID );
	void			ResetInvenItemState ( CDialog *pDlg );
	void			SetInvenPageState ( CDialog *pDlg,int nID );
	void			ResetInvenPageState ( CDialog *pDlg );
	void			ShowPage1 ( CDialog *pDlg );
	void			ShowPage2 ( CDialog *pDlg );
	void			ShowPage3 ( CDialog *pDlg );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonInven00();
	afx_msg void OnBnClickedButtonInven01();
	afx_msg void OnBnClickedButtonInven02();
	afx_msg void OnBnClickedButtonInven03();
	afx_msg void OnBnClickedButtonInven04();
	afx_msg void OnBnClickedButtonInven05();
	afx_msg void OnBnClickedButtonInven06();
	afx_msg void OnBnClickedButtonInven07();
	afx_msg void OnBnClickedButtonInven08();
	afx_msg void OnBnClickedButtonInven09();
	afx_msg void OnBnClickedButtonInven010();
	afx_msg void OnBnClickedButtonInven011();
	afx_msg void OnBnClickedButtonInven012();
	afx_msg void OnBnClickedButtonInven013();
	afx_msg void OnBnClickedButtonInven014();
	afx_msg void OnBnClickedButtonInven015();
	afx_msg void OnBnClickedButtonInven016();
	afx_msg void OnBnClickedButtonInven017();
	afx_msg void OnBnClickedButtonInven018();
	afx_msg void OnBnClickedButtonInven019();
	afx_msg void OnBnClickedButtonInven020();
	afx_msg void OnBnClickedButtonInven021();
	afx_msg void OnBnClickedButtonInven022();
	afx_msg void OnBnClickedButtonInven023();
	afx_msg void OnBnClickedButtonInven024();
	afx_msg void OnBnClickedButtonInven025();
	afx_msg void OnBnClickedButtonInven026();
	afx_msg void OnBnClickedButtonInven027();
	afx_msg void OnBnClickedButtonInven028();
	afx_msg void OnBnClickedButtonInven029();
	afx_msg void OnBnClickedButtonInven10();
	afx_msg void OnBnClickedButtonInven11();
	afx_msg void OnBnClickedButtonInven12();
	afx_msg void OnBnClickedButtonInven13();
	afx_msg void OnBnClickedButtonInven14();
	afx_msg void OnBnClickedButtonInven15();
	afx_msg void OnBnClickedButtonInven16();
	afx_msg void OnBnClickedButtonInven17();
	afx_msg void OnBnClickedButtonInven18();
	afx_msg void OnBnClickedButtonInven19();
	afx_msg void OnBnClickedButtonInven110();
	afx_msg void OnBnClickedButtonInven111();
	afx_msg void OnBnClickedButtonInven112();
	afx_msg void OnBnClickedButtonInven113();
	afx_msg void OnBnClickedButtonInven114();
	afx_msg void OnBnClickedButtonInven115();
	afx_msg void OnBnClickedButtonInven116();
	afx_msg void OnBnClickedButtonInven117();
	afx_msg void OnBnClickedButtonInven118();
	afx_msg void OnBnClickedButtonInven119();
	afx_msg void OnBnClickedButtonInven120();
	afx_msg void OnBnClickedButtonInven121();
	afx_msg void OnBnClickedButtonInven122();
	afx_msg void OnBnClickedButtonInven123();
	afx_msg void OnBnClickedButtonInven124();
	afx_msg void OnBnClickedButtonInven125();
	afx_msg void OnBnClickedButtonInven126();
	afx_msg void OnBnClickedButtonInven127();
	afx_msg void OnBnClickedButtonInven128();
	afx_msg void OnBnClickedButtonInven129();
	afx_msg void OnBnClickedButtonInven20();
	afx_msg void OnBnClickedButtonInven21();
	afx_msg void OnBnClickedButtonInven22();
	afx_msg void OnBnClickedButtonInven23();
	afx_msg void OnBnClickedButtonInven24();
	afx_msg void OnBnClickedButtonInven25();
	afx_msg void OnBnClickedButtonInven26();
	afx_msg void OnBnClickedButtonInven27();
	afx_msg void OnBnClickedButtonInven28();
	afx_msg void OnBnClickedButtonInven29();
	afx_msg void OnBnClickedButtonInven210();
	afx_msg void OnBnClickedButtonInven211();
	afx_msg void OnBnClickedButtonInven212();
	afx_msg void OnBnClickedButtonInven213();
	afx_msg void OnBnClickedButtonInven214();
	afx_msg void OnBnClickedButtonInven215();
	afx_msg void OnBnClickedButtonInven216();
	afx_msg void OnBnClickedButtonInven217();
	afx_msg void OnBnClickedButtonInven218();
	afx_msg void OnBnClickedButtonInven219();
	afx_msg void OnBnClickedButtonInven220();
	afx_msg void OnBnClickedButtonInven221();
	afx_msg void OnBnClickedButtonInven222();
	afx_msg void OnBnClickedButtonInven223();
	afx_msg void OnBnClickedButtonInven224();
	afx_msg void OnBnClickedButtonInven225();
	afx_msg void OnBnClickedButtonInven226();
	afx_msg void OnBnClickedButtonInven227();
	afx_msg void OnBnClickedButtonInven228();
	afx_msg void OnBnClickedButtonInven229();
	afx_msg void OnBnClickedButtonInven30();
	afx_msg void OnBnClickedButtonInven31();
	afx_msg void OnBnClickedButtonInven32();
	afx_msg void OnBnClickedButtonInven33();
	afx_msg void OnBnClickedButtonInven34();
	afx_msg void OnBnClickedButtonInven35();
	afx_msg void OnBnClickedButtonInven36();
	afx_msg void OnBnClickedButtonInven37();
	afx_msg void OnBnClickedButtonInven38();
	afx_msg void OnBnClickedButtonInven39();
	afx_msg void OnBnClickedButtonInven310();
	afx_msg void OnBnClickedButtonInven311();
	afx_msg void OnBnClickedButtonInven312();
	afx_msg void OnBnClickedButtonInven313();
	afx_msg void OnBnClickedButtonInven314();
	afx_msg void OnBnClickedButtonInven315();
	afx_msg void OnBnClickedButtonInven316();
	afx_msg void OnBnClickedButtonInven317();
	afx_msg void OnBnClickedButtonInven318();
	afx_msg void OnBnClickedButtonInven319();
	afx_msg void OnBnClickedButtonInven320();
	afx_msg void OnBnClickedButtonInven321();
	afx_msg void OnBnClickedButtonInven322();
	afx_msg void OnBnClickedButtonInven323();
	afx_msg void OnBnClickedButtonInven324();
	afx_msg void OnBnClickedButtonInven325();
	afx_msg void OnBnClickedButtonInven326();
	afx_msg void OnBnClickedButtonInven327();
	afx_msg void OnBnClickedButtonInven328();
	afx_msg void OnBnClickedButtonInven329();
	afx_msg void OnBnClickedButtonInven40();
	afx_msg void OnBnClickedButtonInven41();
	afx_msg void OnBnClickedButtonInven42();
	afx_msg void OnBnClickedButtonInven43();
	afx_msg void OnBnClickedButtonInven44();
	afx_msg void OnBnClickedButtonInven45();
	afx_msg void OnBnClickedButtonInven46();
	afx_msg void OnBnClickedButtonInven47();
	afx_msg void OnBnClickedButtonInven48();
	afx_msg void OnBnClickedButtonInven49();
	afx_msg void OnBnClickedButtonInven410();
	afx_msg void OnBnClickedButtonInven411();
	afx_msg void OnBnClickedButtonInven412();
	afx_msg void OnBnClickedButtonInven413();
	afx_msg void OnBnClickedButtonInven414();
	afx_msg void OnBnClickedButtonInven415();
	afx_msg void OnBnClickedButtonInven416();
	afx_msg void OnBnClickedButtonInven417();
	afx_msg void OnBnClickedButtonInven418();
	afx_msg void OnBnClickedButtonInven419();
	afx_msg void OnBnClickedButtonInven420();
	afx_msg void OnBnClickedButtonInven421();
	afx_msg void OnBnClickedButtonInven422();
	afx_msg void OnBnClickedButtonInven423();
	afx_msg void OnBnClickedButtonInven424();
	afx_msg void OnBnClickedButtonInven425();
	afx_msg void OnBnClickedButtonInven426();
	afx_msg void OnBnClickedButtonInven427();
	afx_msg void OnBnClickedButtonInven428();
	afx_msg void OnBnClickedButtonInven429();
	afx_msg void OnBnClickedButtonInven50();
	afx_msg void OnBnClickedButtonInven51();
	afx_msg void OnBnClickedButtonInven52();
	afx_msg void OnBnClickedButtonInven53();
	afx_msg void OnBnClickedButtonInven54();
	afx_msg void OnBnClickedButtonInven55();
	afx_msg void OnBnClickedButtonInven56();
	afx_msg void OnBnClickedButtonInven57();
	afx_msg void OnBnClickedButtonInven58();
	afx_msg void OnBnClickedButtonInven59();
	afx_msg void OnBnClickedButtonInven510();
	afx_msg void OnBnClickedButtonInven511();
	afx_msg void OnBnClickedButtonInven512();
	afx_msg void OnBnClickedButtonInven513();
	afx_msg void OnBnClickedButtonInven514();
	afx_msg void OnBnClickedButtonInven515();
	afx_msg void OnBnClickedButtonInven516();
	afx_msg void OnBnClickedButtonInven517();
	afx_msg void OnBnClickedButtonInven518();
	afx_msg void OnBnClickedButtonInven519();
	afx_msg void OnBnClickedButtonInven520();
	afx_msg void OnBnClickedButtonInven521();
	afx_msg void OnBnClickedButtonInven522();
	afx_msg void OnBnClickedButtonInven523();
	afx_msg void OnBnClickedButtonInven524();
	afx_msg void OnBnClickedButtonInven525();
	afx_msg void OnBnClickedButtonInven526();
	afx_msg void OnBnClickedButtonInven527();
	afx_msg void OnBnClickedButtonInven528();
	afx_msg void OnBnClickedButtonInven529();
	afx_msg void OnBnClickedButtonItemsearchM();
	afx_msg void OnBnClickedButtonItemsearchCos();
	afx_msg void OnBnClickedBtnEditItemDelete();
	afx_msg void OnBnClickedBtnEditItemUpdate();
	afx_msg void OnBnClickedButtonResetCosExpire();
	afx_msg void OnCbnSelchangeComboGentype();
	afx_msg void OnBnClickedButtonInvencancel();
	afx_msg void OnBnClickedButtonInvensave();
	afx_msg void OnBnClickedButtonInvenwipe();
	afx_msg void OnBnClickedButtonP1();
	afx_msg void OnBnClickedButtonP2();
	afx_msg void OnBnClickedButtonP3();
};

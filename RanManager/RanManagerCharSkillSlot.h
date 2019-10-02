#pragma once
#include "./GLCharData.h"

// CRanManagerCharSkillSlot dialog
class	CRanManagerCharTab;
class CRanManagerCharSkillSlot : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerCharSkillSlot)

public:
	CRanManagerCharSkillSlot(LOGFONT logfont);
	virtual ~CRanManagerCharSkillSlot();

// Dialog Data
	enum { IDD = IDD_RM_CHAR_SKILLSLOT };

protected:
	CRanManagerCharTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	int				nActiveSlot;
	CComboBox		m_cActiveSkill;

public:
	void			SetToolTab		( CRanManagerCharTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetChar (int nChar);
	void			ReadChar (int nChar);
	void			ReadSkillSlot (int nChar);
	void			ShowSkillSlot();
	void			SetSlotState ( CDialog *pDlg,int nID );
	void			ResetSlotState ( CDialog *pDlg );
	void			LoadSlot(int nSlot);


public:
	WORD					m_wSKILLQUICK_ACT;	
	SNATIVEID				m_sSKILLQUICK[EMSKILLQUICK_SIZE];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSkillslotSave();
	afx_msg void OnBnClickedButtonSkillslotcancel();
	afx_msg void OnBnClickedButtonSkill10();
	afx_msg void OnBnClickedButtonSkill11();
	afx_msg void OnBnClickedButtonSkill12();
	afx_msg void OnBnClickedButtonSkill13();
	afx_msg void OnBnClickedButtonSkill14();
	afx_msg void OnBnClickedButtonSkill15();
	afx_msg void OnBnClickedButtonSkill16();
	afx_msg void OnBnClickedButtonSkill17();
	afx_msg void OnBnClickedButtonSkill18();
	afx_msg void OnBnClickedButtonSkill19();
	afx_msg void OnBnClickedButtonSkill20();
	afx_msg void OnBnClickedButtonSkill21();
	afx_msg void OnBnClickedButtonSkill22();
	afx_msg void OnBnClickedButtonSkill23();
	afx_msg void OnBnClickedButtonSkill24();
	afx_msg void OnBnClickedButtonSkill25();
	afx_msg void OnBnClickedButtonSkill26();
	afx_msg void OnBnClickedButtonSkill27();
	afx_msg void OnBnClickedButtonSkill28();
	afx_msg void OnBnClickedButtonSkill29();
	afx_msg void OnBnClickedButtonSkill30();
	afx_msg void OnBnClickedButtonSkill31();
	afx_msg void OnBnClickedButtonSkill32();
	afx_msg void OnBnClickedButtonSkill33();
	afx_msg void OnBnClickedButtonSkill34();
	afx_msg void OnBnClickedButtonSkill35();
	afx_msg void OnBnClickedButtonSkill36();
	afx_msg void OnBnClickedButtonSkill37();
	afx_msg void OnBnClickedButtonSkill38();
	afx_msg void OnBnClickedButtonSkill39();
	afx_msg void OnBnClickedButtonSkill40();
	afx_msg void OnBnClickedButtonSkill41();
	afx_msg void OnBnClickedButtonSkill42();
	afx_msg void OnBnClickedButtonSkill43();
	afx_msg void OnBnClickedButtonSkill44();
	afx_msg void OnBnClickedButtonSkill45();
	afx_msg void OnBnClickedButtonSkill46();
	afx_msg void OnBnClickedButtonSkill47();
	afx_msg void OnBnClickedButtonSkill48();
	afx_msg void OnBnClickedButtonSkill49();
	afx_msg void OnBnClickedButtonSkillSave();
	afx_msg void OnBnClickedButtonSkillDelete();
	afx_msg void OnBnClickedButtonSkillChange();
	afx_msg void OnBnClickedButtonDeleteSlotAll();
	afx_msg void OnBnClickedButtonDeleteSlotF1();
	afx_msg void OnBnClickedButtonDeleteSlotF2();
	afx_msg void OnBnClickedButtonDeleteSlotF3();
	afx_msg void OnBnClickedButtonDeleteSlotF4();
};

#pragma once
#include "../../EngineLib/G-Logic/GLDefine.h"
#include "GLSkill.h"
#include "./GLCharData.h"

// CRanManagerCharSkill dialog
class	CRanManagerCharTab;
class CRanManagerCharSkill : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerCharSkill)

public:
	CRanManagerCharSkill(LOGFONT logfont);
	virtual ~CRanManagerCharSkill();

// Dialog Data
	enum { IDD = IDD_RM_CHAR_SKILL };

protected:
	CRanManagerCharTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	typedef stdext::hash_map<DWORD,SCHARSKILL>		SKILL_MAP;
	typedef SKILL_MAP::iterator						SKILL_MAP_ITER;
	typedef SKILL_MAP::const_iterator				SKILL_MAP_CITER;
	CListCtrl		m_list_Skill;
	CListCtrl		m_list_SkillChar;
	SKILL_MAP		m_ExpSkills;	

public:
	void			LoadChar(int nChar);
	void			LoadSkill(int nChar);
	void			LoadGameSkill( EMCHARCLASS emClass ,bool bAll );
	void			ShowSkills();

public:
	void			SetToolTab		( CRanManagerCharTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetChar (int nChar);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonDeleteskill();
	afx_msg void OnBnClickedButtonDeleteskillall();
	afx_msg void OnBnClickedButtonEditskilllevel();
	afx_msg void OnBnClickedButtonSaveSkill();
	afx_msg void OnBnClickedButtonCancelSkill();
	afx_msg void OnBnClickedButtonSkSave();
	afx_msg void OnBnClickedButtonInsertSkill();
	afx_msg void OnBnClickedButtonAllClass();
	afx_msg void OnBnClickedButtonCompatible();
};

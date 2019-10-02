#pragma once

#include "GLSkill.h"
// CSkillSearch dialog

class CSkillSearch : public CDialog
{
	DECLARE_DYNAMIC(CSkillSearch)

public:
	CSkillSearch(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSkillSearch();

// Dialog Data
	enum { IDD = IDD_SKILL_DLG };

public:
	typedef std::vector<SNATIVEID>				VEC_SKILL_SEARCH_RESULT;
	typedef VEC_SKILL_SEARCH_RESULT::iterator	VEC_SKILL_SEARCH_RESULT_ITER;
	VEC_SKILL_SEARCH_RESULT	m_VecSearchResult;
	CListCtrl		m_list_Skill;
	CComboBox		m_cSearchType;
	bool			bMultiple;
	SNATIVEID		sSelectedSkill;

public:
	void	ShowSkills();
	void	SetMultiple(bool bEnable )	{	bMultiple = bEnable;	}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedButtonSkillsearch();
	afx_msg void OnCbnSelchangeComboSearchType();
};

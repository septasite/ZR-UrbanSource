#pragma once

#include "./GLQuestPlay.h"
#include "./GLQuest.h"
#include "./GLQuestMan.h"
// CRanManagerCharQuest dialog
class	CRanManagerCharTab;
class CRanManagerCharQuest : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerCharQuest)

public:
	CRanManagerCharQuest(LOGFONT logfont);
	virtual ~CRanManagerCharQuest();

// Dialog Data
	enum { IDD = IDD_RM_CHAR_QUEST };

protected:
	CRanManagerCharTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	void			SetToolTab		( CRanManagerCharTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetChar (int nChar);
	void			LoadChar (int nChar);
	void			LoadQuest (int nChar);
	void			ShowQuestsRun();
	void			ShowQuestsDone();

public:
	GLQuestPlay		m_cQuestPlay;
	CListCtrl		m_list_Quest_Run;
	CListCtrl		m_list_Quest_Done;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonRunDelete();
	afx_msg void OnBnClickedButtonRunDeleteAll();
	afx_msg void OnBnClickedButtonDoneDelete();
	afx_msg void OnBnClickedButtonDoneDeleteAll();
	afx_msg void OnBnClickedButtonQuestSave();
	afx_msg void OnBnClickedButtonQuestCancel();
};

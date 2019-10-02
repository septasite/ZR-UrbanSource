#ifndef __UserTab_H_
#define __UserTab_H_

/////////////////////////////////////////////////////////////////////////////
// CRanManagerCharTab
#include <vector>
#include "RanManagerCharDefault.h"
#include "RanManagerCharEdit.h"
#include "RanManagerCharPutOn.h"
#include "RanManagerCharInven.h"
#include "RanManagerCharSkill.h"
#include "RanManagerCharQuest.h"
#include "RanManagerCharVehicle.h"
#include "RanManagerCharPet.h"
#include "RanManagerCharSkillSlot.h"
#include "RanManagerCharQuickSlot.h"
#include "RanManagerCharCoolDown.h"

enum { BCDF_CENTER, BCDF_TOPLEFT, BCDF_NONE };

class CRanManagerCharTab : public CPropertySheet
{
	DECLARE_DYNAMIC(CRanManagerCharTab)

public:
	CWnd*				m_pWndParent;

public:
	CRanManagerCharDefault		m_CharDefault;
	CRanManagerCharEdit			m_CharEdit;
	CRanManagerCharPutOn		m_CharPutOn;
	CRanManagerCharInven		m_CharInven;
	CRanManagerCharSkill		m_CharSkill;
	CRanManagerCharQuest		m_CharQuest;
	CRanManagerCharVehicle		m_CharVehicle;
	CRanManagerCharPet			m_CharPet;
	CRanManagerCharSkillSlot	m_CharSkillSlot;
	CRanManagerCharQuickSlot	m_CharQuickSlot;
	CRanManagerCharCoolDown		m_CharCoolDown;

	void	ClearData();

public:	
	void	ActivePage(int nPage,int nChar);

// Construction
public:
	CRanManagerCharTab(CWnd* pParentWnd = NULL);
	CRanManagerCharTab(CRect& rect, LOGFONT logfont, CWnd* pParentWnd = NULL );
	virtual ~CRanManagerCharTab();

// Attributes
public:
	CRect		m_Rect;
	BOOL		m_bNoTabs;
	int			m_iDistanceFromTop;
	CFont*		m_pFont;


// Get/Set
public:
   void NoTabs() { m_bNoTabs = TRUE; }
   void SetDistanceFromTop( int iDistance ) { m_iDistanceFromTop = iDistance; }
   void ChangeDialogFont(CWnd* pWnd, CFont* pFont, int nFlag);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRanManagerCharTab)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:

// Generated message map functions
protected:
	//{{AFX_MSG(CRanManagerCharTab)
   afx_msg HBRUSH CtlColor(CDC* pDc, UINT uCtlColor);	
   //}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __ToolTab_H_
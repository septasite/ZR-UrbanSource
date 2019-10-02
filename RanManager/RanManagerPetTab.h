#ifndef __PetTab_H_
#define __PetTab_H_

/////////////////////////////////////////////////////////////////////////////
// CRanManagerPetTab
#include <vector>
#include "RanManagerPetDefault.h"
#include "RanManagerPetEdit.h"
#include "RanManagerPetInven.h"
#include "RanManagerPetSkill.h"
#include "RanManagerPetSkillSlot.h"

enum { BCDF_CENTER, BCDF_TOPLEFT, BCDF_NONE };

class CRanManagerPetTab : public CPropertySheet
{
	DECLARE_DYNAMIC(CRanManagerPetTab)

public:
	CWnd*				m_pWndParent;

public:
	CRanManagerPetDefault		m_PetDefault;
	CRanManagerPetEdit			m_PetEdit;
	CRanManagerPetInven			m_PetInven;
	CRanManagerPetSkill			m_PetSkill;
	CRanManagerPetSkillSlot		m_PetSkillSlot;

	void	ClearData();

public:	
	void	ActivePage(int nPage,int nPet);

// Construction
public:
	CRanManagerPetTab(CWnd* pParentWnd = NULL);
	CRanManagerPetTab(CRect& rect, LOGFONT logfont, CWnd* pParentWnd = NULL );
	virtual ~CRanManagerPetTab();

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
	//{{AFX_VIRTUAL(CRanManagerPetTab)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:

// Generated message map functions
protected:
	//{{AFX_MSG(CRanManagerPetTab)
   afx_msg HBRUSH CtlColor(CDC* pDc, UINT uCtlColor);	
   //}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __ToolTab_H_
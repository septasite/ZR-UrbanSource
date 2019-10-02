#ifndef __UserTab_H_
#define __UserTab_H_

/////////////////////////////////////////////////////////////////////////////
// CRanManagerUserTab
#include <vector>
#include "RanManagerUserDefault.h"
#include "RanManagerUserNew.h"
#include "RanManagerUserEdit.h"
#include "RanManagerUserBank.h"
#include "RanManagerUserChar.h"
#include "RanManagerUserLocker.h"

enum { BCDF_CENTER, BCDF_TOPLEFT, BCDF_NONE };

class CRanManagerUserTab : public CPropertySheet
{
	DECLARE_DYNAMIC(CRanManagerUserTab)

public:
	CWnd*				m_pWndParent;

public:
	CRanManagerUserDefault		m_UserDefault;
	CRanManagerUserNew			m_UserNew;
	CRanManagerUserEdit			m_UserEdit;
	CRanManagerUserBank			m_UserBank;
	CRanManagerUserChar			m_UserChar;
	CRanManagerUserLocker		m_UserLocker;

	void	ClearData();

public:	
	void	ActivePage(int nPage,int nUser);

// Construction
public:
	CRanManagerUserTab(CWnd* pParentWnd = NULL);
	CRanManagerUserTab(CRect& rect, LOGFONT logfont, CWnd* pParentWnd = NULL );
	virtual ~CRanManagerUserTab();

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
	//{{AFX_VIRTUAL(CRanManagerUserTab)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:

// Generated message map functions
protected:
	//{{AFX_MSG(CRanManagerUserTab)
   afx_msg HBRUSH CtlColor(CDC* pDc, UINT uCtlColor);	
   //}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __ToolTab_H_
#ifndef __GuildTab_H_
#define __GuildTab_H_

/////////////////////////////////////////////////////////////////////////////
// CRanManagerGuildTab
#include <vector>
#include "RanManagerGuildMain.h"
#include "RanManagerGuildEdit.h"
#include "RanManagerGuildLocker.h"
#include "RanManagerGuildMember.h"
#include "RanManagerGuildImage.h"


enum { BCDF_CENTER, BCDF_TOPLEFT, BCDF_NONE };

class CRanManagerGuildTab : public CPropertySheet
{
	DECLARE_DYNAMIC(CRanManagerGuildTab)

public:
	CWnd*				m_pWndParent;

public:
	CRanManagerGuildMain		m_GuildDefault;
	CRanManagerGuildEdit		m_GuildEdit;
	CRanManagerGuildLocker		m_GuildLocker;
	CRanManagerGuildMember		m_GuildMember;
	CRanManagerGuildImage		m_GuildImage;
	void	ClearData();

public:	
	void	ActivePage(int nPage,int nGuild);

// Construction
public:
	CRanManagerGuildTab(CWnd* pParentWnd = NULL);
	CRanManagerGuildTab(CRect& rect, LOGFONT logfont, CWnd* pParentWnd = NULL );
	virtual ~CRanManagerGuildTab();

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
	//{{AFX_VIRTUAL(CRanManagerGuildTab)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:

// Generated message map functions
protected:
	//{{AFX_MSG(CRanManagerGuildTab)
   afx_msg HBRUSH CtlColor(CDC* pDc, UINT uCtlColor);	
   //}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __ToolTab_H_
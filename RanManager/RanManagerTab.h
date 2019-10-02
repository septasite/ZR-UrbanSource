#ifndef __RanManagerTab_H_
#define __RanManagerTab_H_

/////////////////////////////////////////////////////////////////////////////
// CRanManagerTab
#include <vector>
#include "RanManagerMain.h"
#include "RanManagerUser.h"
#include "RanManagerChar.h"
#include "RanManagerGuild.h"
#include "RanManagerVehicle.h"
#include "RanManagerPet.h"

enum { ZCDF_CENTER, ZCDF_TOPLEFT, ZCDF_NONE };

class CRanManagerTab : public CPropertySheet
{
	DECLARE_DYNAMIC(CRanManagerTab)

public:
	CWnd*				m_pWndParent;

public:
	CRanManagerMain			m_PageMain;
	CRanManagerUser			m_PageUser;
	CRanManagerChar 		m_PageChar;
	CRanManagerGuild 		m_PageGuild;
	CRanManagerVehicle 		m_PageVehicle;
	CRanManagerPet 			m_PagePet;

	void	ClearData();

public:	
	void	ActivePage(int nPage);
	void	SendLog(CString strLog){ m_PageMain.AddLog(strLog);	}

// Construction
public:
	CRanManagerTab(CWnd* pParentWnd = NULL);
	CRanManagerTab(CRect& rect, LOGFONT logfont, CWnd* pParentWnd = NULL );
	virtual ~CRanManagerTab();

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
	//{{AFX_VIRTUAL(CRanManagerTab)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:

// Generated message map functions
protected:
	//{{AFX_MSG(CRanManagerTab)
   afx_msg HBRUSH CtlColor(CDC* pDc, UINT uCtlColor);	
   //}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __ToolTab_H_
#ifndef __EffTab_H_
#define __EffTab_H_

/////////////////////////////////////////////////////////////////////////////
// CRanViewTab
#include <vector>
#include "RanViewDlg.h"

enum EDITSHEETZ
{
	ZTOOLDLG		= 0,
	ZEDITSHEETX		= 1
};

enum { ZCDF_CENTER, ZCDF_TOPLEFT, ZCDF_NONE };

class CRanViewTab : public CPropertySheet
{
	DECLARE_DYNAMIC(CRanViewTab)

public:
	CWnd*				m_pWndParent;

public:
	CRanViewDlg			m_ToolDlg;

	void	ClearData();

public:	
	void	ActiveDlgPage();


// Construction
public:
	CRanViewTab(CWnd* pParentWnd = NULL);
	CRanViewTab(CRect& rect, LOGFONT logfont, CWnd* pParentWnd = NULL );
	virtual ~CRanViewTab();

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
	//{{AFX_VIRTUAL(CRanViewTab)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:

// Generated message map functions
protected:
	//{{AFX_MSG(CRanViewTab)
   afx_msg HBRUSH CtlColor(CDC* pDc, UINT uCtlColor);	
   //}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __ToolTab_H_
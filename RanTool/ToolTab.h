#ifndef __ToolTab_H_
#define __ToolTab_H_

/////////////////////////////////////////////////////////////////////////////
// CToolTab

#include <vector>
#include "TabDefault.h"
#include "TabABF.h"
#include "TabVCF.h"
#include "TabCHF.h"
#include "TabCFG.h"
#include "TabABL.h"
#include "TabCNV.h"
#include "TabCredits.h"
#include "TabCPS.h"
#include "RanToolDlg.h"
#include "TabMMP.h"
#include "TabCRY.h"



enum EDITSHEET
{
	TAB_DEF			= 0,
	TAB_ABF			= 1,
	TAB_VCF			= 2,
	TAB_CHF			= 3,
	TAB_CFG			= 4,
	TAB_ABL			= 5,
	TAB_CNV			= 6,
	TAB_CRD			= 7,
	TAB_CPS			= 8,
	TAB_MMP			= 9,
	TAB_CRY			= 10,

	EDITSHEET		= 11
};

enum { CDF_CENTER, CDF_TOPLEFT, CDF_NONE };

extern CString g_strEditSheet[EDITSHEET];

class CToolTab : public CPropertySheet
{
	DECLARE_DYNAMIC(CToolTab)

public:
	CWnd*				m_pWndParent;

public:
	CTabDefault		m_TabDEF;
	CTabABF			m_TabABF;
	CTabVCF			m_TabVCF;
	CTabCHF			m_TabCHF;
	CTabCFG			m_TabCFG;
	CTabABL			m_TabABL;
	CTabCNV			m_TabCNV;
	CTabCredits		m_TabCRD;
	CTabCPS			m_TabCPS;
	CTabMMP			m_TabMMP;
	CTabCRY			m_TabCRY;


	void	ClearData();

public:	
	void	ActivateTab(int nPage, bool bSave);
	void	AddHistory( const char* szInfo );
	void	AddHistoryOpen( const char* szSender ,const char* szInfo );
	void	AddHistorySave( const char* szSender ,const char* szInfo );
	void	AddHistoryOpenFail( const char* szSender ,const char* szInfo );
	void	AddHistorySaveFail( const char* szSender ,const char* szInfo );

// Construction
public:
	CToolTab(CWnd* pParentWnd = NULL);
	CToolTab(CRect& rect, LOGFONT logfont, CWnd* pParentWnd = NULL );
	virtual ~CToolTab();

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
	//{{AFX_VIRTUAL(CToolTab)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:

// Generated message map functions
protected:
	//{{AFX_MSG(CToolTab)
   afx_msg HBRUSH CtlColor(CDC* pDc, UINT uCtlColor);	
   //}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __ToolTab_H_
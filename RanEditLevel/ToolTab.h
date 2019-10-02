#ifndef __ToolTab_H_
#define __ToolTab_H_

/////////////////////////////////////////////////////////////////////////////
// CToolTab
#include <vector>
#include "DlgMain.h"
#include "DlgBasic.h"
#include "DlgCondition.h"
#include "DlgEtcFunction.h"
#include "DlgCrowList.h"
#include "DlgGateList.h"
#include "DlgEffList.h"
#include "DlgLandMarkList.h"
#include "DlgCrowEdit.h"
#include "DlgGateEdit.h"
#include "DlgEffEdit.h"
#include "DlgLandMarkEdit.h"

enum EDITSHEET
{
	DLG_MAIN		= 0,
	DLG_BASIC		= 1,
	DLG_CONDITION	= 2,
	DLG_ETCFUNCTION	= 3,
	DLG_CROWLIST	= 4,
	DLG_GATELIST	= 5,
	DLG_EFFLIST		= 6,
	DLG_LMLIST		= 7,


	DLG_CROWEDIT	= 8, 
	DLG_GATEEDIT	= 9, 
	DLG_EFFEDIT		= 10, 
	DLG_LMEDIT		= 11, 

	DLG_SIZE		= 12,
	DLG_NOTLIST		= 4, //dont list dialogs
};

enum { CDF_CENTER, CDF_TOPLEFT, CDF_NONE };

class CToolTab : public CPropertySheet
{
	DECLARE_DYNAMIC(CToolTab)

public:
	CWnd*				m_pWndParent;

public:
	CDlgMain			m_DlgMain;
	CDlgBasic			m_DlgBasic;
	CDlgCondition		m_DlgCondition;
	CDlgEtcFunction		m_DlgEtcFunction;
	CDlgCrowList		m_DlgCrowList;
	CDlgGateList		m_DlgGateList;
	CDlgEffList			m_DlgEffList;
	CDlgLandMarkList	m_DlgLandMarkList;
	CDlgCrowEdit		m_DlgCrowEdit;
	CDlgGateEdit		m_DlgGateEdit;
	CDlgEffEdit			m_DlgEffEdit;
	CDlgLandMarkEdit	m_DlgLMEdit;

	void	ClearData();

public:	
	void	ActiveDlgPage( int nPage );
	void	ActiveCrowEdit( std::string strName );
	void	ActiveCrowAdd();
	void	SelectCrow( std::string strName );
	void	ActiveGateEdit( PDXLANDGATE pLandGate );
	void	ActiveGateAdd();
	void	ActiveEffEdit( PLANDEFF pEff );
	void	ActiveEffAdd();
	void	ActiveLMEdit( PLANDMARK pLM );
	void	ActiveLMAdd();	


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
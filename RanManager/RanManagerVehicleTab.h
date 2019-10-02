#ifndef __GuildTab_H_
#define __GuildTab_H_

/////////////////////////////////////////////////////////////////////////////
// CRanManagerVehicleTab
#include <vector>
#include "RanManagerVehicleDefault.h"
#include "RanManagerVehicleEdit.h"
#include "RanManagerVehicleInven.h"



enum { BCDF_CENTER, BCDF_TOPLEFT, BCDF_NONE };

class CRanManagerVehicleTab : public CPropertySheet
{
	DECLARE_DYNAMIC(CRanManagerVehicleTab)

public:
	CWnd*				m_pWndParent;

public:
	CRanManagerVehicleDefault		m_VehicleDefault;
	CRanManagerVehicleEdit			m_VehicleEdit;
	CRanManagerVehicleInven			m_VehicleInven;

	void	ClearData();

public:	
	void	ActivePage(int nPage,int nVehicle);

// Construction
public:
	CRanManagerVehicleTab(CWnd* pParentWnd = NULL);
	CRanManagerVehicleTab(CRect& rect, LOGFONT logfont, CWnd* pParentWnd = NULL );
	virtual ~CRanManagerVehicleTab();

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
	//{{AFX_VIRTUAL(CRanManagerVehicleTab)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:

// Generated message map functions
protected:
	//{{AFX_MSG(CRanManagerVehicleTab)
   afx_msg HBRUSH CtlColor(CDC* pDc, UINT uCtlColor);	
   //}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __ToolTab_H_
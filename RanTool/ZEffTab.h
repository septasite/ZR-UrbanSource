#ifndef __EffTab_H_
#define __EffTab_H_

/////////////////////////////////////////////////////////////////////////////
// AEffTab
#include <vector>
#include "ZEffList.h"
#include "ZEffSingle.h"
#include "ZEffGhosting.h"
#include "ZEffTrace.h"
#include "ZEffFaceOff.h"

enum EDITSHEETZ
{
	ZEFF_LIST		= 0,
	ZEFF_SINGLE		= 1,
	ZEFF_GHOSTING	= 2,
	ZEFF_TRACE		= 3,
	ZEFF_FACEOFF	= 4,

	ZEDITSHEETX		= 5
};

enum { ZCDF_CENTER, ZCDF_TOPLEFT, ZCDF_NONE };

class AEffTab : public CPropertySheet
{
	DECLARE_DYNAMIC(AEffTab)

public:
	CWnd*				m_pWndParent;

public:
	AEffList			m_EffList;
	AEffSingle			m_EffSingle;
	AEffGhosting		m_EffGhosting;
	AEffTrace			m_EffTrace;
	AEffFaceOff			m_EffFaceOff;


	void	ClearData();

public:	
	void	ActiveEffList( SANIMCONINFO::EFFANILIST m_listEffAni );
	void	ActiveEffListNormal();

	void	ActiveEffSingle( DxEffAniData_Single* EffSingle );
	void	ActiveEffGhosting( DxEffAniData_Ghosting* EffGhosting );
	void	ActiveEffTrace( DxEffAniData_Trace* EffTrace );
	void	ActiveEffFaceOff( DxEffAniData_FaceOff* EffFaceOff );

	void	ActiveEffSingleReturn( DxEffAniData_Single* EffSingle );
	void	ActiveEffGhostingReturn( DxEffAniData_Ghosting* EffGhosting );
	void	ActiveEffTraceReturn( DxEffAniData_Trace* EffTrace );
	void	ActiveEffFaceOffReturn( DxEffAniData_FaceOff* EffFaceOff );

	SANIMCONINFO::EFFANILIST GetListEffect() { return m_EffList.GetListEffect(); }

// Construction
public:
	AEffTab(CWnd* pParentWnd = NULL);
	AEffTab(CRect& rect, LOGFONT logfont, CWnd* pParentWnd = NULL );
	virtual ~AEffTab();

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
	//{{AFX_VIRTUAL(AEffTab)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:

// Generated message map functions
protected:
	//{{AFX_MSG(AEffTab)
   afx_msg HBRUSH CtlColor(CDC* pDc, UINT uCtlColor);	
   //}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __ToolTab_H_
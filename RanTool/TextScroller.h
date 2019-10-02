#if !defined(AFX_TEXTSCROLLER_H__BCE1DA18_FCA6_47B1_8201_7774C90ED9EA__INCLUDED_)
#define AFX_TEXTSCROLLER_H__BCE1DA18_FCA6_47B1_8201_7774C90ED9EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextScroller.h : header file
//
#include <afxtempl.h>

struct Line
{
	CString strLine;
	int		pos;
	int		Initpos;
	BOOL	bDecrease;
};
/////////////////////////////////////////////////////////////////////////////
// CTextScroller window

class CTextScroller : public CStatic
{
protected:
	CList<Line*,Line*>	m_Lines;
	int					m_CurrentY;
	BOOL				m_bFirstTime;
	CFont				m_font;
	COLORREF			m_TextColor;
	COLORREF			m_BkColor;
	BOOL				m_bDecreasePos;
	int					m_nWidth;
	int					m_nHeight;
	LOGFONT				m_lf;
// Construction
public:
	CTextScroller();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextScroller)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetFontSize(int nSize);
	void SetFontItalic(BOOL bItalic);
	void SetFontBold(BOOL bIsBold);
	CString SetFontName(CString strFont);
	void SetBorder(BOOL bSet=TRUE);
	COLORREF SetTextColor(COLORREF color);
	void		SetScrollTimer(int nElapse);
	COLORREF	SetBkColor(COLORREF color);
	void		AddLine(CStringArray &str);
	virtual		~CTextScroller();

	// Generated message map functions
protected:
	void FreeList();
	void FormatLines();
	void MoveTextToTheTop();
	void DrawBkGround(CDC *pDC,CRect InvalidRect = CRect(0,0,0,0));
	//{{AFX_MSG(CTextScroller)
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTSCROLLER_H__BCE1DA18_FCA6_47B1_8201_7774C90ED9EA__INCLUDED_)

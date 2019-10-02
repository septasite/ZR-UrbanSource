// TextScroller.cpp : implementation file
//

#include "stdafx.h"
#include "TextScroller.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextScroller

CTextScroller::CTextScroller()
{
	m_CurrentY		= 0;
	m_bFirstTime	= TRUE;
	m_TextColor		= RGB(0,0,0);
	m_BkColor		= RGB(204,204,255);
	m_bDecreasePos	= TRUE;
	m_nHeight		= 0;
	m_nWidth		= 0;
	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT),sizeof(m_lf),&m_lf);
	m_font.CreateFontIndirect(&m_lf);
}

CTextScroller::~CTextScroller()
{
	FreeList();
	m_font.DeleteObject();
}


BEGIN_MESSAGE_MAP(CTextScroller, CStatic)
	//{{AFX_MSG_MAP(CTextScroller)
	ON_WM_PAINT()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextScroller message handlers

void CTextScroller::AddLine(CStringArray &str)
{
	Line *_line = NULL;
	for(int ii =0 ;ii<str.GetSize();ii++)
	{
		_line = new Line;
		_line->strLine  = str.GetAt(ii);
		_line->pos	    = 0;
		_line->Initpos  = 0;
		_line->bDecrease= TRUE;
		m_Lines.AddTail(_line);
	}
	FormatLines();
	Invalidate();
}

void CTextScroller::PreSubclassWindow() 
{
	CStatic::PreSubclassWindow();
	ModifyStyle(0,SS_BITMAP, SS_OWNERDRAW);
	ModifyStyle(0,WS_BORDER,SWP_DRAWFRAME);
}

void CTextScroller::OnPaint() 
{
	KillTimer(0);
	CPaintDC dc(this); // device context for painting
	DrawBkGround(&dc);
	SetTimer(0,50,NULL);
}

void CTextScroller::DrawBkGround(CDC *pDC,CRect InvalidRect)
{
	CRect rectClient;
	GetClientRect(rectClient);
	if(InvalidRect == CRect(0,0,0,0))
		InvalidRect = rectClient;
	if(m_bFirstTime)
	{
		if(m_Lines.GetCount())
		{
			POSITION pos = m_Lines.GetHeadPosition();
			Line *_line = NULL;
			int offset = rectClient.bottom; 
			CFont *pOldFont = pDC->SelectObject(&m_font);
			CSize size = pDC->GetTextExtent(_T("TEST"));
			pDC->SelectObject(pOldFont);
			while(pos)
			{
				_line  = m_Lines.GetNext(pos);
				if(_line)
				{
					_line->pos	   = offset;
					_line->Initpos = offset;
					offset += size.cy + 1;
				}
			}
			m_bFirstTime = 0;
		}
	}
	pDC->FillSolidRect(&InvalidRect,m_BkColor);
}

void CTextScroller::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent == 0)
	{
		MoveTextToTheTop();
	}
	CStatic::OnTimer(nIDEvent);
}

void CTextScroller::MoveTextToTheTop()
{
	int count = m_Lines.GetCount();
	if(!count)
		return;
	CDC *pDC = GetDC();
	CRect rectClient;
	GetClientRect(rectClient);
	CFont *pOldFont = pDC->SelectObject(&m_font);
	int iOldMode    = pDC->SetBkMode(TRANSPARENT);
	COLORREF col    = pDC->SetTextColor(m_TextColor);
	CSize size = pDC->GetTextExtent(_T("TEST"));
	Line *_line = NULL;
	POSITION pos = m_Lines.GetHeadPosition();
	int nIndex = -1;
	while(pos)
	{
		 _line = m_Lines.GetNext(pos);
		 nIndex++;
		 if(!_line)
			 return;
		 if(_line->bDecrease)
			(_line->pos)--;
		if(_line->pos < 0)
		{
			DrawBkGround(pDC,CRect(0,_line->pos - 1,rectClient.right,_line->pos + size.cy - 1));
			_line->pos = _line->Initpos;
			if(nIndex == m_Lines.GetCount()-1)
			{
				pos = m_Lines.GetHeadPosition();
				while(pos)
				{
					_line = m_Lines.GetNext(pos);
					_line->bDecrease = TRUE;
				}
				break;
			}
			else
				_line->bDecrease = FALSE;
			continue;
		}
		if(_line->pos > rectClient.bottom - size.cy)
			continue;
		DrawBkGround(pDC,CRect(0,_line->pos - 1,rectClient.right,_line->pos + size.cy + 1));
		pDC->DrawText(_line->strLine,CRect(0,_line->pos,rectClient.right,_line->pos + size.cy),DT_CENTER);
	}
	pDC->SetBkMode(iOldMode);
	pDC->SelectObject(pOldFont);
	pDC->SetTextColor(col);
//Clean the top of the window
	DrawBkGround(pDC,CRect(0,0,rectClient.right,size.cy));
	ReleaseDC(pDC);
}

void CTextScroller::FormatLines()
{
//Get nbr caractere that can fit the client rectangle
	CDC *pDC = GetDC();
	CFont *pOldFont = pDC->SelectObject(&m_font);
	CSize size		= pDC->GetTextExtent("T");
	pDC->SelectObject(pOldFont);
	CRect rectClient;
	GetClientRect(rectClient);
	int nbrCarPerLine = (rectClient.Width() / size.cx);
//format text now
	POSITION pos = m_Lines.GetHeadPosition();
	int posEsp   = 0;
	Line *_line  = NULL;
	CStringArray tmpArray;
	CString strLine;
	CString tmp;
	while(pos)
	{
		_line = m_Lines.GetNext(pos);
		strLine = _line->strLine;
		while(!strLine.IsEmpty())
		{
			posEsp = 0;
			strLine.TrimRight();
			if(nbrCarPerLine < strLine.GetLength() && strLine.GetAt(nbrCarPerLine) != ' ')
			{
				int Oldpos = 0;
				while(posEsp <= nbrCarPerLine  && posEsp != -1)
				{
					Oldpos = posEsp;
					posEsp = strLine.Find(' ',posEsp+1);
				}
				posEsp = Oldpos;
			}
			else
			{
				if(nbrCarPerLine < strLine.GetLength())
					posEsp = nbrCarPerLine;
				else
				{
					strLine += ' ';
					posEsp = strLine.GetLength()-1;
				}
			}
			tmp = strLine;
			if(posEsp)
				strLine.Delete(posEsp,strLine.GetLength()-posEsp);
			tmpArray.Add(strLine);
			tmp.Delete(0,posEsp+1);
			strLine = tmp;
		}
	}
	FreeList();
//fill the list with new strings
	for(int ii = 0;ii<tmpArray.GetSize();ii++)
	{
		_line = new Line;
		_line->strLine  = tmpArray.GetAt(ii);
		_line->pos	    = 0;
		_line->Initpos  = 0;
		_line->bDecrease= TRUE;
		m_Lines.AddTail(_line);
	}
}

void CTextScroller::FreeList()
{
	POSITION pos = m_Lines.GetHeadPosition();
	Line *_line = NULL;
	while(pos)
	{
		_line = m_Lines.GetNext(pos);
		delete _line;
	}
	m_Lines.RemoveAll();
}

COLORREF CTextScroller::SetBkColor(COLORREF color)
{
	COLORREF OldCol = m_BkColor;
	m_BkColor = color;
	Invalidate();
	return OldCol;
}

void CTextScroller::SetScrollTimer(int nElapse)
{
	if(nElapse >0)
	{
		KillTimer(0);
		SetTimer(0,nElapse,NULL);
	}
}

COLORREF CTextScroller::SetTextColor(COLORREF color)
{
	COLORREF OldCol = m_TextColor;
	m_TextColor = color;
	Invalidate();
	return OldCol;
}

void CTextScroller::SetBorder(BOOL bSet)
{
	if(bSet)
		ModifyStyle(0,WS_BORDER,SWP_DRAWFRAME);
	else
		ModifyStyle(WS_BORDER,0,SWP_DRAWFRAME);
}

CString CTextScroller::SetFontName(CString strFont)
{
	CString OldFontName = _T(m_lf.lfFaceName);
	strcpy(m_lf.lfFaceName,strFont);
	m_font.DeleteObject();
	m_font.CreateFontIndirect(&m_lf);
	Invalidate();
	return OldFontName;
}

void CTextScroller::SetFontBold(BOOL bIsBold)
{
	m_lf.lfWeight = bIsBold ? FW_BOLD : FW_NORMAL;
	m_font.DeleteObject();
	m_font.CreateFontIndirect(&m_lf);
	Invalidate();
}

void CTextScroller::SetFontItalic(BOOL bItalic)
{
	m_lf.lfItalic = bItalic;
	m_font.DeleteObject();
	m_font.CreateFontIndirect(&m_lf);
	Invalidate();
}

void CTextScroller::SetFontSize(int nSize)
{
	nSize*=-1;
	m_lf.lfHeight = nSize;
	m_font.DeleteObject();
	m_font.CreateFontIndirect(&m_lf);
	Invalidate();
}

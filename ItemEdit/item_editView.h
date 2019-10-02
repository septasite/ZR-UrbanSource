// item_editView.h : interface of the Citem_editView class
//


#pragma once


class Citem_editView : public CView
{
protected: // create from serialization only
	Citem_editView();
	DECLARE_DYNCREATE(Citem_editView)

// Attributes
public:
	Citem_editDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~Citem_editView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in item_editView.cpp
inline Citem_editDoc* Citem_editView::GetDocument() const
   { return reinterpret_cast<Citem_editDoc*>(m_pDocument); }
#endif


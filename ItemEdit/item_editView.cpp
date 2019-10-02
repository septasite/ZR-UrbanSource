// item_editView.cpp : implementation of the Citem_editView class
//

#include "stdafx.h"
#include "item_edit.h"

#include "item_editDoc.h"
#include "item_editView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Citem_editView

IMPLEMENT_DYNCREATE(Citem_editView, CView)

BEGIN_MESSAGE_MAP(Citem_editView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// Citem_editView construction/destruction

Citem_editView::Citem_editView()
{
	// TODO: add construction code here

}

Citem_editView::~Citem_editView()
{
}

BOOL Citem_editView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Citem_editView drawing

void Citem_editView::OnDraw(CDC* /*pDC*/)
{
	Citem_editDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// Citem_editView printing

BOOL Citem_editView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Citem_editView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Citem_editView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// Citem_editView diagnostics

#ifdef _DEBUG
void Citem_editView::AssertValid() const
{
	CView::AssertValid();
}

void Citem_editView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Citem_editDoc* Citem_editView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Citem_editDoc)));
	return (Citem_editDoc*)m_pDocument;
}
#endif //_DEBUG


// Citem_editView message handlers

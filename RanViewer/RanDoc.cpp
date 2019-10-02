// RanDoc.cpp : implementation of the CRanDoc class
//

#include "stdafx.h"
#include "RanViewer.h"

#include "RanDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRanDoc

IMPLEMENT_DYNCREATE(CRanDoc, CDocument)

BEGIN_MESSAGE_MAP(CRanDoc, CDocument)
END_MESSAGE_MAP()


// CRanDoc construction/destruction

CRanDoc::CRanDoc()
{
	// TODO: add one-time construction code here

}

CRanDoc::~CRanDoc()
{
}

BOOL CRanDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CRanDoc serialization

void CRanDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CRanDoc diagnostics

#ifdef _DEBUG
void CRanDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRanDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CRanDoc commands

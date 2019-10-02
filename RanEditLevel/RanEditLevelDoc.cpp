// RanEditLevelDoc.cpp : implementation of the CRanEditLevelDoc class
//

#include "stdafx.h"
#include "RanEditLevel.h"

#include "RanEditLevelDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRanEditLevelDoc

IMPLEMENT_DYNCREATE(CRanEditLevelDoc, CDocument)

BEGIN_MESSAGE_MAP(CRanEditLevelDoc, CDocument)
END_MESSAGE_MAP()


// CRanEditLevelDoc construction/destruction

CRanEditLevelDoc::CRanEditLevelDoc()
{
	// TODO: add one-time construction code here

}

CRanEditLevelDoc::~CRanEditLevelDoc()
{
}

BOOL CRanEditLevelDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CRanEditLevelDoc serialization

void CRanEditLevelDoc::Serialize(CArchive& ar)
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


// CRanEditLevelDoc diagnostics

#ifdef _DEBUG
void CRanEditLevelDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRanEditLevelDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CRanEditLevelDoc commands

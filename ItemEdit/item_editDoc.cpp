// item_editDoc.cpp : implementation of the Citem_editDoc class
//

#include "stdafx.h"
#include "item_edit.h"

#include "item_editDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Citem_editDoc

IMPLEMENT_DYNCREATE(Citem_editDoc, CDocument)

BEGIN_MESSAGE_MAP(Citem_editDoc, CDocument)
END_MESSAGE_MAP()


// Citem_editDoc construction/destruction

Citem_editDoc::Citem_editDoc()
{
	// TODO: add one-time construction code here

}

Citem_editDoc::~Citem_editDoc()
{
}

BOOL Citem_editDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// Citem_editDoc serialization

void Citem_editDoc::Serialize(CArchive& ar)
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


// Citem_editDoc diagnostics

#ifdef _DEBUG
void Citem_editDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void Citem_editDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Citem_editDoc commands

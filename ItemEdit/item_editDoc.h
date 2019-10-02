// item_editDoc.h : interface of the Citem_editDoc class
//


#pragma once

class Citem_editDoc : public CDocument
{
protected: // create from serialization only
	Citem_editDoc();
	DECLARE_DYNCREATE(Citem_editDoc)

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~Citem_editDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};



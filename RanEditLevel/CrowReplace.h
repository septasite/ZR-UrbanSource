#pragma once

#include "GLDefine.h"
// CCrowReplace dialog

class CCrowReplace : public CDialog
{
	DECLARE_DYNAMIC(CCrowReplace)

public:
	CCrowReplace(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCrowReplace();

// Dialog Data
	enum { IDD = IDD_DIALOG_CROW_REPLACE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual			BOOL OnInitDialog();

private:
	SNATIVEID	sIDFROM;
	SNATIVEID	sIDTO;

public:
	SNATIVEID	GetIDFROM()	{	return sIDFROM;	}
	SNATIVEID	GetIDTO()	{	return sIDTO;	}

public:
	afx_msg void OnBnClickedButtonCrow();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};

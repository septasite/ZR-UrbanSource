#pragma once

#include "GLDefine.h"

struct SREPLACEID
{
	SNATIVEID	sFROM;
	SNATIVEID	sTO;

	SREPLACEID()
	{
		sFROM = NATIVEID_NULL();
		sTO = NATIVEID_NULL();
	};
};
// CCrowReplaceMulti dialog

class CCrowReplaceMulti : public CDialog
{
	DECLARE_DYNAMIC(CCrowReplaceMulti)

public:
	CCrowReplaceMulti(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCrowReplaceMulti();

// Dialog Data
	enum { IDD = IDD_DIALOG_CROW_REPLACE_MULTI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	typedef std::vector<SREPLACEID>	VEC_REPLACE;
	typedef VEC_REPLACE::iterator	VEC_REPLACE_ITER;
	VEC_REPLACE		m_Vec;

public:
	CListCtrl		m_list;

public:
	void UpdateList();
	void ResetInput();

public:
	virtual			BOOL OnInitDialog();

public:
	afx_msg void OnBnClickedButtonCrow();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonDelete2();
};

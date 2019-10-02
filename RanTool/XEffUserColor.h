#pragma once

#include "DxEffCharUserColor.h"
// CEffUserColor dialog
class	CEffTab;

class CEffUserColor : public CPropertyPage
{
	DECLARE_DYNAMIC(CEffUserColor)

public:
	CEffUserColor(LOGFONT logfont);
	virtual ~CEffUserColor();

// Dialog Data
	enum { IDD = IDD_XUSERCOLOR };

protected:
	CEffTab*		m_pEffTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;
	bool			bAdd;
	int				nLastEdit;

public:
	DXMATERIAL_CHAR_EFF*	m_pMaterials;

	typedef std::vector<DXMATERIAL_CHAR_EFF>			XMAT_VEC;
	typedef XMAT_VEC::iterator							XMAT_VEC_ITER;

	XMAT_VEC		m_pVecMatX;
	int				nMaterialSize;
	CListBox		m_list_mat;
	DxEffCharUserColor*	EffUserColorEdit;

public:
	void			SetEffTab		( CEffTab *pEffTab ) { m_pEffTab = pEffTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetEffUserColor ( DxEffCharUserColor*	EffUserColorX);
	BOOL			Update ();
	BOOL			UpdateList ();
	BOOL			Save ();


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButtonCopy();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonAok();
	afx_msg void OnBnClickedButtonAcan();
};

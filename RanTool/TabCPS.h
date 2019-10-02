#pragma once

#include "DxSkinPieceContainer.h"
// CTabCPS dialog
class	CToolTab;
class	CEffTab;

struct	TRACE_BONE_INFO
{
	DWORD		m_pBoneX;
	float		m_pWeightsX;

	TRACE_BONE_INFO() :
	m_pBoneX(0),
	m_pWeightsX(0.0f)
	{
	}
};

class CTabCPS : public CPropertyPage
{
	DECLARE_DYNAMIC(CTabCPS)

public:
	CTabCPS(LOGFONT logfont);
	virtual ~CTabCPS();

	enum { IDD = IDD_PS_DIALOG };

protected:
	CEffTab*		m_pEffTab;
	CToolTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;
	BOOL			m_bActive;
	bool			bAdd;
	int				nEditID;
	int				nEditTraceID;
	int				nEditBoneTraceID;
	bool			bAddBone;
	bool			bAddBone_b;
	CString			strFileName;
	
	
public:
	typedef std::vector<SMATERIAL_PIECE>				MAT_VEC;
	typedef MAT_VEC::iterator							MAT_VEC_ITER;

	typedef std::vector<TRACE_BONE_INFO>				BONE_VEC;
	typedef BONE_VEC::iterator							BONE_VEC_ITER;

	MAT_VEC				m_VecMaterial;
	BONE_VEC			m_VecBone;
	DxSkinPiece			m_pPiece;
	SMATERIAL_PIECE*	m_pMaterialTemp;
	CListBox			m_list_material;
	CListBox			m_list_trace;
	CListBox			m_list_trace_b;

public:
	BOOL				UpdateData();
	BOOL				UpdateListMaterial();
	BOOL				UpdateListTrace();
	BOOL				SaveData();
	void				Reset();
	void				UpdateBoneList();
	void				SetToolTab		( CToolTab *pToolTab ) { m_pToolTab = pToolTab; }
	void				SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonCpsLoad();
	afx_msg void OnBnClickedButtonCpsSave();
	afx_msg void OnBnClickedMatAdd();
	afx_msg void OnBnClickedMatEdit();
	afx_msg void OnBnClickedMatDel();
	afx_msg void OnBnClickedMatOk();
	afx_msg void OnBnClickedMatCancel();
	afx_msg void OnBnClickedTraceAdd();
	afx_msg void OnBnClickedTraceEdit();
	afx_msg void OnBnClickedTraceDel();
	afx_msg void OnBnClickedTraceCan();
	afx_msg void OnBnClickedTraceOk();
	afx_msg void OnBnClickedEffTAdd();
	afx_msg void OnBnClickedEffTEdit();
	afx_msg void OnBnClickedEffTDel();
	afx_msg void OnBnClickedEffTOk();
	afx_msg void OnBnClickedEffTCan();
	afx_msg void OnBnClickedButtonCpsLoadran2();
	afx_msg void OnBnClickedButtonCpsNew();
};

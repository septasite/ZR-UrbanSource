// EditCFGDlg.h : header file
//
#include "../../EngineLib/Meshs/DxSkinAniMan.h"
#include "../../EngineLib/Meshs/DxPieceDefine.h"
#include "../../EngineLib/Meshs/SAnimation.h"
#pragma once


// CEditCFGDlg dialog
class CEditCFGDlg : public CDialog
{
// Construction
public:
	CEditCFGDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_EDITCFG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public:
	SANIMCONINFO	m_AniInfo;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonSave();
	void UpdateData();
	BOOL SaveData();
	
};

//enum EMSTRIKE_EFF_TOOL
//{
//	TEMSF_NULL		= 0,
//	TEMSF_SELFBODY	= 1,
//	TEMSF_TARGET		= 2,
//	TEMSF_SIZE_TOOL		= 3
//};

namespace DUMMY_TOOL_DATA
{
	extern std::string m_PieceNames[PIECE_SIZE];
	extern std::string m_StrikeEff[EMSF_SIZE];

	extern std::string m_AniMain[AN_TYPE_SIZE];
	extern std::string m_AniSub[AN_SUB_00_SIZE];
};

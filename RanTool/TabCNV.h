#pragma once

#include "CnvClass.h"
#include "./DxEffSinglePropGMan.h"
#include "./DxSkinPieceContainer.h"
#include "CHFClass.h"
#include "ABFClass.h"
// CTabCNV dialog

class	CToolTab;

class CTabCNV : public CPropertyPage
{
	DECLARE_DYNAMIC(CTabCNV)

public:
	CTabCNV(LOGFONT logfont);
	virtual ~CTabCNV();

	enum { IDD = IDD_CNV_DIALOG };

	enum HEXTYPE
	{
		HEX2DEC_RAN = 0,
		DEC2HEX_RAN = 1,
		HEX2DEC_NOR = 2,
		DEC2HEX_NOR = 3,

		HEXCNV_SIZE = 4,
	};

	enum CNV_TYPE
	{
		CNV_EGP			= 0,
		CNV_BIN			= 1,
		CNV_CFG			= 2,
		CNV_CPS			= 3,
		CNV_CPSR2		= 4,
		CNV_CHF			= 5,
		CNV_ABF			= 6,
		CNVTYPE_SIZE	= 7,
	};

	enum CNV_MODE
	{
		CNV_FILE		= 0,
		CNV_FOLDER		= 1,
		CNVMODE_SIZE	= 2,
	};

protected:
	CToolTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;
	BOOL			m_bActive;

public:
	void			SetToolTab		( CToolTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	BinManager			BinFile;
	SANIMCONINFO		CfgFile;
	EFF_PROPGROUP		pPropGroup;
	DxSkinPiece			m_pPiece;
	CCHFClass			m_pChfCode;
	CABFClass			m_pAbfCode;

public:
	CComboBox			m_cHexType;
	CComboBox			m_cType;
	CComboBox			m_cMode;
	CEdit				m_cEditResult;
	CEdit				m_cEditErr;
	CString				m_strInput;
	CString				m_strOutput;
	CString				m_strResult;
	CString				strFileName;

public:
	void				Reset();
	void				AddEditString( const char* szInfo );
	void				AddEditStringErr( const char* szInfo );

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonHexcnv();
	afx_msg void OnBnClickedButtonIn();
	afx_msg void OnBnClickedButtonOut();
	afx_msg void OnBnClickedButtonConvert();
	afx_msg void OnCbnSelchangeComboCnvmode();
	afx_msg void OnCbnSelchangeComboCnvtype();
	afx_msg void OnBnClickedButtonEqual();
};

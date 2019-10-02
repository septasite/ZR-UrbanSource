#pragma once
#include "afxwin.h"

// CTabCRY dialog
class	CToolTab;

class CTabCRY : public CPropertyPage
{
	DECLARE_DYNAMIC(CTabCRY)

public:
	CTabCRY(LOGFONT logfont);
	virtual ~CTabCRY();

// Dialog Data
	enum { IDD = IDD_CRY_DIALOG };

	enum 
	{
		TEXTURE_XDDS,
		TEXTURE_XTGA,

		TEXTURE_XTYPE,
	};

	enum
	{
		RCC_CRYPTION = 0,
		TEX_CRYPTION = 1,
	};
	enum
	{
		FileCryption = 0,
		FolderCryption = 1,
	};


protected:
	CToolTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;
	BOOL			m_bActive;

public:
	
	CString			m_strInput;
	CString			m_strOutput;
	CString			m_strResult;
	CComboBox		m_ComboType;
	CComboBox		m_ComboMode;
	CEdit			m_cEditResult;
	void			SetToolTab		( CToolTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			Reset();
	BOOL			FileEncryption();
	BOOL			FileDecryption();
	BOOL			FolderEncryption( const CString& strInput, const CString& strOutput );
	BOOL			FolderDecryption( const CString& strInput, const CString& strOutput );
	BOOL			Encryption(CString fInput , CString fOutput);
	BOOL			Decryption(CString fInput , CString fOutput);
	void			AddEditString( const char* szInfo );

	BOOL			EncryptTex( const CString& strInput, const CString& strOutput );
	BOOL			DecryptTex( const CString& strInput, const CString& strOutput );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedSamefile();
	afx_msg void OnBnClickedReverse();
	afx_msg void OnBnClickedEncrypt();
	afx_msg void OnBnClickedDecrypt();
};

int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM dwData);

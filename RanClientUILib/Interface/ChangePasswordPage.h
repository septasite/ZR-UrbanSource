#pragma	once

#include "UIOuterWindow.h"

class CUIEditBoxMan;

class CChangePasswordPage : public CUIOuterWindow
{
	enum
	{
		CHANGEPASS_OK = ET_CONTROL_NEXT,
		CHANGEPASS_CANCEL,
		CHANGEPASS_EDIT_MAN,
		CHANGEPASS_EDIT_OPW,
		CHANGEPASS_EDIT_NPW,
		CHANGEPASS_EDIT_PW2,
		CHANGEPASS_EDIT_RPW2,
		CHANGEPASS_EDIT_CP
	};

public:
	static int nLIMIT_OPW;
	static int nLIMIT_NPW;
	static int nLIMIT_PW2;
	static int nLIMIT_RPW2;
	static int nLIMIT_CP;

public:
	CChangePasswordPage();
	virtual	~CChangePasswordPage();

public:
	virtual void Update( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage( UIGUID ControlID, DWORD dwMsg );

	virtual	void SetVisibleSingle( BOOL bVisible );

public:
	void CreateSubControl();
	CBasicButton * CreateFlipButton( char* szButton, char* szButtonFlip, UIGUID ControlID );

	void ResetAll();
	void SetCharToEditBox( TCHAR cKey );
	void DelCharToEditBox();
	void GoNextTab();

private:
	BOOL CheckString( CString strTemp );
	BOOL CheckEmail( CString strTemp );
private:
	CUIEditBoxMan * m_pEditBoxMan;
	CBasicButton * m_pIDSaveButton;
	CBasicTextBox * m_pRandTextBox;

	INT m_nRandPassNumber;
	TCHAR m_szRandomString[7];
	INT m_nRPUpdateCnt;
};
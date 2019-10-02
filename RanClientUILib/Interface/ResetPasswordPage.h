#pragma	once

#include "UIOuterWindow.h"

class CUIEditBoxMan;

class CResetPasswordPage : public CUIOuterWindow
{
	enum
	{
		RESETPASS_OK = ET_CONTROL_NEXT,
		RESETPASS_CANCEL,
		RESETPASS_EDIT_MAN,
		RESETPASS_EDIT_ID,
		RESETPASS_EDIT_PW2,
		RESETPASS_EDIT_CP
	};

public:
	static int nLIMIT_ID;
	static int nLIMIT_PW2;
	static int nLIMIT_CP;

public:
	CResetPasswordPage();
	virtual	~CResetPasswordPage();

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
private:
	CUIEditBoxMan * m_pEditBoxMan;
	CBasicButton * m_pIDSaveButton;
	CBasicTextBox * m_pRandTextBox;

	INT m_nRandPassNumber;
	TCHAR m_szRandomString[7];
	INT m_nRPUpdateCnt;
};
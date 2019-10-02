#pragma	once

#include "UIOuterWindow.h"

class CUIEditBoxMan;

class CResetPasswordPage2 : public CUIOuterWindow
{
	enum
	{
		RESETPASS2_OK = ET_CONTROL_NEXT,
		RESETPASS2_CANCEL,
		RESETPASS2_EDIT_MAN,
		RESETPASS2_EDIT_NPW,
		RESETPASS2_EDIT_PW2,
		RESETPASS2_EDIT_RPW2,
		RESETPASS2_EDIT_CP
	};

public:
	static int nLIMIT_NPW;
	static int nLIMIT_PW2;
	static int nLIMIT_RPW2;
	static int nLIMIT_CP;

public:
	CResetPasswordPage2();
	virtual	~CResetPasswordPage2();

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
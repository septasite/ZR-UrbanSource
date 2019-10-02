#pragma	once

#include "UIOuterWindow.h"

class CUIEditBoxMan;

class CRegisterPage : public CUIOuterWindow
{
	enum
	{
		REGISTER_OK = ET_CONTROL_NEXT,
		REGISTER_CANCEL,
		REGISTER_EDIT_MAN,
		REGISTER_EDIT_ID,
		REGISTER_EDIT_PW,
		REGISTER_EDIT_PW2,
		REGISTER_EDIT_EMAIL,
		REGISTER_EDIT_CP
	};

public:
	static int nLIMIT_ID;
	static int nLIMIT_PW;
	static int nLIMIT_PW2;
	static int nLIMIT_EMAIL;
	static int nLIMIT_CP;

public:
	CRegisterPage();
	virtual	~CRegisterPage();

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
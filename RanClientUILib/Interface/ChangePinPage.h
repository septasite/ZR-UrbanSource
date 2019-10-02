#pragma	once

#include "UIOuterWindow.h"

class CUIEditBoxMan;

class CChangePinPage : public CUIOuterWindow
{
	enum
	{
		CHANGEPIN_OK = ET_CONTROL_NEXT,
		CHANGEPIN_CANCEL,
		CHANGEPIN_EDIT_MAN,
		CHANGEPIN_EDIT_OPW2,
		CHANGEPIN_EDIT_PW,
		CHANGEPIN_EDIT_PW2,
		CHANGEPIN_EDIT_RPW2,
		CHANGEPIN_EDIT_CP
	};

public:
	static int nLIMIT_PW;
	static int nLIMIT_PW2;
	static int nLIMIT_CP;

public:
	CChangePinPage();
	virtual	~CChangePinPage();

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
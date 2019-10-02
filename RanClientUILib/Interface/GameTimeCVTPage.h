#pragma	once

#include "UIOuterWindow.h"

class CUIEditBoxMan;

class CGameTimeCVTPage : public CUIOuterWindow
{
	enum
	{
		GTCVT_OK = ET_CONTROL_NEXT,
		GTCVT_CANCEL,
		GTCVT_EDIT_CP,
		GTCVT_EDIT_MAN,
	};

public:
	static int nLIMIT_CP;

public:
	CGameTimeCVTPage();
	virtual	~CGameTimeCVTPage();

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
	CBasicTextBox * m_pStaticTextBox;
	CBasicTextBox * m_pStaticText2Box;
	CBasicTextBox * m_pStaticText3Box;
	CBasicTextBox * m_pStaticText4Box;

	INT m_nRandPassNumber;
	TCHAR m_szRandomString[7];
	INT m_nRPUpdateCnt;
};
//	기본 정보 표시
//
//	최초 작성자 : 성기엽
//	이후 수정자 : 
//	로그
//		[2003.11.21]
//			@ 작성
//

#pragma	once

#include "../EngineUIlib/GUInterface/UIGroup.h"

class	CBasicTextBox;
class	CBasicTextButton;


const DWORD UIMSG_MOUSEIN_SELECT_USERPANEL = UIMSG_USER1;

class CSelectCharacterUserPanel : public CUIGroup
{
private:
	enum
	{
		SELECT_CHARACTER_USERPANEL_CP = NO_ID + 1,
		SELECT_CHARACTER_USERPANEL_CPN,
		SELECT_CHARACTER_USERPANEL_CE,
		SELECT_CHARACTER_USERPANEL_RN,
		SELECT_CHARACTER_USERPANEL_GTCVT,
		SELECT_CHARACTER_USERPANEL_PPCVT,
		SELECT_CHARACTER_USERPANEL_TOPUP,
	};
public:
	CSelectCharacterUserPanel ();
	virtual	~CSelectCharacterUserPanel ();

public:
	void	CreateSubControl ();

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
private:
    CBasicTextBox* m_pEmailTextBox;
    CBasicTextBox* m_pBattlePointTextBox;
    CBasicTextBox* m_pGameTimeTextBox;
    CBasicTextBox* m_pUserPointTextBox;
    CBasicTextBox* m_pPasswordTextBox;
    CBasicTextBox* m_pPinTextBox;
	
	CBasicTextButton* m_pButtonCE;
	CBasicTextButton* m_pButtonCP;
	CBasicTextButton* m_pButtonCPN;
	CBasicTextButton* m_pButtonRP;
	CBasicTextButton* m_pButtonGTCVT;
	CBasicTextButton* m_pButtonPPCVT;
	CBasicTextButton* m_pButtonTOPUP;

private:
	DWORD m_uUserPoint;
	DWORD m_dwGameTime;
	DWORD m_uBattlePoint;
	CString m_strEmail;
};
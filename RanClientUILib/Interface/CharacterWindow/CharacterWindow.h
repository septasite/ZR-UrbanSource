#pragma	once

#include "../UIWindowEx.h"
#include "GLCharDefine.h"

class	CD3DFontPar;
class	CBasicTextButton;
class	CCharacterWindowChar;
class	CCharacterWindowVehicle;
class	CCharacterWindowCharAdditionalInfo;
struct	GLCHARLOGIC;

enum
{
	CHARPAGE_CHARACTER	= 0,
	CHARPAGE_VEHICLE	= 1,
};

class CCharacterWindow : public CUIWindowEx
{
protected:
	enum
	{
		PAGE_CHARACTER = ET_CONTROL_NEXT,
		PAGE_VEHICLE,
		PAGE_CHARACTER_ADDITIONAL,
		BUTTON_CHARACTER,
		BUTTON_VEHICLE,
	};

public:
    CCharacterWindow ();
	virtual	~CCharacterWindow ();

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	virtual	void SetVisibleSingle ( BOOL bVisible );
	virtual void SetGlobalPos(const D3DXVECTOR2& vPos);

public:
	void	CreateSubControl ();
	CBasicTextButton*	CreateTextButton23 ( const char* szButton, UIGUID ControlID, const char* szText );

private:
	CCharacterWindowChar*		m_pPageChar;
	CCharacterWindowVehicle*	m_pPageVehicle;
	CCharacterWindowCharAdditionalInfo* m_pPageCharAdditional;
	CUIControl*				m_pBackGround;
	CBasicTextButton*		m_pButtonChar;
	CBasicTextButton*		m_pButtonVehicle;

public:
	int nActivePage;

public:
	void	OpenPage( int nPage );
	int		GetActivePage()	{	return nActivePage;	}
	void	SetArmSwapTabButton( BOOL bArmSub );
	void	RefreshVehiclePage();
};
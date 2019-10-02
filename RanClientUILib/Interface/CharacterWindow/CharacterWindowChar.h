#pragma	once

#include "../Interface/UIWindowEx.h"
#include "GLCharDefine.h"

class	CD3DFontPar;
class	CBasicTextBox;
class	CBasicButton;
class	CBasicButtonRadio;
struct	GLCHARLOGIC;

class	CCharacterWindowCharStat;
class	CCharacterWindowCharWear;
class	CCharacterWindowCharWearEx;
class	CCharacterWindowCharRender;


class CCharacterWindowChar : public CUIGroup
{
protected:
	enum
	{
		CHARACTER_WEAR = NO_ID + 1,
		CHARACTER_WEAR_EX,
		CHARACTER_STATS,
		CHARACTER_ACADEMY_BRIGHTBAR,
		CHARACTER_ACADEMY_HELP,
	};

public:
    CCharacterWindowChar ();
	virtual	~CCharacterWindowChar ();

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	virtual	void SetVisibleSingle ( BOOL bVisible );

public:
	void	CreateSubControl ();

private:
	CBasicTextBox*	CreateStaticControl ( char* szConatrolKeyword, CD3DFontPar* pFont, int nAlign, const UIGUID& cID = NO_ID );
	CUIControl*		CreateControl ( const char* szControl, const UIGUID& cID = NO_ID );
	CBasicButton*	CreateFlipButton ( char* szButton, char* szButtonFlip, UIGUID ControlID, WORD wFlipType );


private:	
	void	SetData ( const GLCHARLOGIC& sCharData );


private:
	CCharacterWindowCharStat*		m_pStatRegion;
	CCharacterWindowCharWear*		m_pCharWear;
	CCharacterWindowCharWearEx*		m_pCharWearEx;
	CCharacterWindowCharRender*		m_pRender;

	CBasicTextBox*	m_pNameText;
	CBasicTextBox*	m_pClubText;
	CBasicTextBox*	m_pTitleText;
	CBasicTextBox*	m_pAcademy;
	CBasicTextBox*	m_pLifeP;
	CBasicTextBox*	m_pContP;
	CBasicTextBox*	m_pPK;
	CBasicTextBox*	m_pPremiumText;
	CUIControl*		m_pBrightFrame;
	CUIControl*		m_pBrightSlider;
	CBasicButton*	m_pHelp;
	CBasicButtonRadio*	m_pAbility;

public:
	void	SetArmSwapTabButton( BOOL bArmSub );
	void	ClearRender();
};
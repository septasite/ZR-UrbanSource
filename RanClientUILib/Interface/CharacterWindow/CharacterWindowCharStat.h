#pragma	once

#include "../Interface/UIWindowEx.h"
#include "GLCharDefine.h"
#include "../RanClientLib/G-Logic/GLogicEx.h"

class	CD3DFontPar;
class	CBasicProgressBar;
class	CBasicTextBox;
class	CBasicButtonText;
class	CBasicButton;
class	CCharacterWindowCharStatMark;
struct	GLCHARLOGIC;

class CCharacterWindowCharStat : public CUIGroup
{
protected:
	enum
	{
		CHARACTER_POW_BUTTON_PLUS = NO_ID + 1,
		CHARACTER_DEX_BUTTON_PLUS,
		CHARACTER_SPI_BUTTON_PLUS,
		CHARACTER_STR_BUTTON_PLUS,
		CHARACTER_STA_BUTTON_PLUS,

		CHARACTER_POW_BUTTON_MINUS,
		CHARACTER_DEX_BUTTON_MINUS,
		CHARACTER_SPI_BUTTON_MINUS,
		CHARACTER_STR_BUTTON_MINUS,
		CHARACTER_STA_BUTTON_MINUS,

		CHARACTER_STAT_RESET,
		CHARACTER_STAT_APPLY,
		CHARACTER_STAT_HELP,

		MOUSE_OVER_STAT_1_POW,
		MOUSE_OVER_STAT_1_DEX,
		MOUSE_OVER_STAT_1_SPI,
		MOUSE_OVER_STAT_1_STR,
		MOUSE_OVER_STAT_1_STA,
		MOUSE_OVER_STAT_2_ATTACK_MIN,
		MOUSE_OVER_STAT_2_ATTACK_MAX,
		MOUSE_OVER_STAT_2_DEFENSE,
		MOUSE_OVER_STAT_2_FIGHT,
		MOUSE_OVER_STAT_2_SHOOT,
		MOUSE_OVER_STAT_2_STAMINA,
		MOUSE_OVER_STAT_2_HIT,
		MOUSE_OVER_STAT_2_AVOID,
		MOUSE_OVER_STAT_2_HP,
		MOUSE_OVER_STAT_2_MP,
		MOUSE_OVER_STAT_2_SP,
		MOUSE_OVER_STAT_3_FIRE,
		MOUSE_OVER_STAT_3_COLD,
		MOUSE_OVER_STAT_3_ELECTRIC,
		MOUSE_OVER_STAT_3_POISON,
		MOUSE_OVER_STAT_3_SPIRIT,

		CHARACTER_STAT_HELP_ADDITIONAL,

		MOUSE_OVER_STAT_5_CRITICAL,
		MOUSE_OVER_STAT_5_STRIKE,
		MOUSE_OVER_STAT_5_MOVINGSPEED,
		MOUSE_OVER_STAT_5_ATTACKSPEED,
		MOUSE_OVER_STAT_5_EXP,
		MOUSE_OVER_STAT_5_HPRECOVERY,
		MOUSE_OVER_STAT_5_MPRECOVERY,
		MOUSE_OVER_STAT_5_SPRECOVERY,
		MOUSE_OVER_STAT_5_CPRECOVERY,
		MOUSE_OVER_STAT_5_POTIONHP,
		MOUSE_OVER_STAT_5_POTIONMP,
		MOUSE_OVER_STAT_2_POTIONSP,

		MOUSE_OVER_BUTTONS = 21,
		MOUSE_OVER_BUTTONS_ADDITIONAL = 12,
	};

public:
    CCharacterWindowCharStat ();
	virtual	~CCharacterWindowCharStat ();

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	virtual	void SetVisibleSingle ( BOOL bVisible );

public:
	void	CreateSubControl ();

private:
	CBasicTextBox*	CreateStaticControl ( char* szConatrolKeyword, CD3DFontPar* pFont, int nAlign, const UIGUID& cID = NO_ID );
	CUIControl*		CreateControl ( const char* szControl, const UIGUID& cID = NO_ID );
	CBasicButtonText*	CreateButtonBlue ( char* szButton, char* szTextBox, CD3DFontPar* pFont, int nAlign, UIGUID ControlID, CString strText );
	CBasicButtonText*	CreateButtonRed ( char* szButton, char* szTextBox, CD3DFontPar* pFont, int nAlign, UIGUID ControlID, CString strText );
	CBasicButton*	CreateMouseIn( const char* szButton, const char* szMouseIn ,UIGUID ControlID );
	CCharacterWindowCharStatMark*		CreateStatMark( const char* szControl, const UIGUID& cID = NO_ID );

private:
	void	SetPointControl ();

private:
	void	SetData ( const GLCHARLOGIC& sCharData );
	void	SetUpData ( const GLCHARLOGIC& sCharData );
	void	ShowTip( int nSelect );
	void	ShowTipAdditional( int nSelect );

protected:
	GLCHARLOGIC		m_sCharLogic;
	DWORD			m_dwPowAdd;
	DWORD			m_dwDexAdd;
	DWORD			m_dwSpiAdd;
	DWORD			m_dwStrAdd;
	DWORD			m_dwStaAdd;
	DWORD			m_dwStatsDeduct;

private:
	CBasicButtonText*	m_pPowButton_Plus;
	CBasicButtonText*	m_pDexButton_Plus;
	CBasicButtonText*	m_pSpiButton_Plus;
	CBasicButtonText*	m_pStrButton_Plus;
	CBasicButtonText*	m_pStaButton_Plus;
	CBasicButtonText*	m_pPowButton_Minus;
	CBasicButtonText*	m_pDexButton_Minus;
	CBasicButtonText*	m_pSpiButton_Minus;
	CBasicButtonText*	m_pStrButton_Minus;
	CBasicButtonText*	m_pStaButton_Minus;

	CBasicButtonText*	m_pButtonStatReset;
	CBasicButtonText*	m_pButtonStatApply;

	CBasicTextBox*	m_pPowText;
	CBasicTextBox*	m_pDexText;
	CBasicTextBox*	m_pSpiText;
	CBasicTextBox*	m_pStrText;
	CBasicTextBox*	m_pStaText;

	CBasicTextBox*	m_pPowText_Up;
	CBasicTextBox*	m_pDexText_Up;
	CBasicTextBox*	m_pSpiText_Up;
	CBasicTextBox*	m_pStrText_Up;
	CBasicTextBox*	m_pStaText_Up;

	CBasicTextBox*	m_pPowTextStatic;
	CBasicTextBox*	m_pDexTextStatic;
	CBasicTextBox*	m_pSpiTextStatic;
	CBasicTextBox*	m_pStrTextStatic;
	CBasicTextBox*	m_pStaTextStatic;

	CBasicTextBox*	m_pPointText;	

	CBasicTextBox*	m_pAttackMinText;
	CBasicTextBox*	m_pAttackMaxText;
	CBasicTextBox*	m_pDefenseText;
	CBasicTextBox*	m_pFightText;
	CBasicTextBox*	m_pShootText;
	CBasicTextBox*	m_pEnergyText;
	CBasicTextBox*	m_pHitText;
	CBasicTextBox*	m_pAvoidText;
	CBasicTextBox*	m_pHPText;
	CBasicTextBox*	m_pMPText;
	CBasicTextBox*	m_pSPText;

	CBasicTextBox*	m_pFireText;
	CBasicTextBox*	m_pColdText;
	CBasicTextBox*	m_pElectricText;
	CBasicTextBox*	m_pPoisonText;
	CBasicTextBox*	m_pSpiritText;

	CBasicButton*	m_pHelp;

	CBasicButton*	m_pMouseOver[MOUSE_OVER_BUTTONS];

	CBasicTextBox*	m_pAttackMinMarkStatic;
	CBasicTextBox*	m_pAttackMaxMarkStatic;
	CBasicTextBox*	m_pDefenseMarkStatic;
	CBasicTextBox*	m_pFightMarkStatic;
	CBasicTextBox*	m_pShootMarkStatic;
	CBasicTextBox*	m_pEnergyMarkStatic;
	CBasicTextBox*	m_pHitMarkStatic;
	CBasicTextBox*	m_pAvoidMarkStatic;
	CBasicTextBox*	m_pHPMarkStatic;
	CBasicTextBox*	m_pMPMarkStatic;
	CBasicTextBox*	m_pSPMarkStatic;

	CBasicTextBox*	m_pAttackMinMarkValue;
	CBasicTextBox*	m_pAttackMaxMarkValue;
	CBasicTextBox*	m_pDefenseMarkValue;
	CBasicTextBox*	m_pFightMarkValue;
	CBasicTextBox*	m_pShootMarkValue;
	CBasicTextBox*	m_pEnergyMarkValue;
	CBasicTextBox*	m_pHitMarkValue;
	CBasicTextBox*	m_pAvoidMarkValue;
	CBasicTextBox*	m_pHPMarkValue;
	CBasicTextBox*	m_pMPMarkValue;
	CBasicTextBox*	m_pSPMarkValue;

	CCharacterWindowCharStatMark*	m_pAttackMinMark;
	CCharacterWindowCharStatMark*	m_pAttackMaxMark;
	CCharacterWindowCharStatMark*	m_pDefenseMark;
	CCharacterWindowCharStatMark*	m_pFightMark;
	CCharacterWindowCharStatMark*	m_pShootMark;
	CCharacterWindowCharStatMark*	m_pEnergyMark;
	CCharacterWindowCharStatMark*	m_pHitMark;
	CCharacterWindowCharStatMark*	m_pAvoidMark;
	CCharacterWindowCharStatMark*	m_pHPMark;
	CCharacterWindowCharStatMark*	m_pMPMark;
	CCharacterWindowCharStatMark*	m_pSPMark;

	//Additional Info Start - Ocram Networkso
		CBasicTextBox*	m_pCriticalRateText;
	CBasicTextBox*	m_pStrikeHitText;
	CBasicTextBox*	m_pMovingSpeedText;
	CBasicTextBox*	m_pAttackSpeedText;
	CBasicTextBox*	m_pEXPText;
	CBasicTextBox*	m_pHPRecoveryText;
	CBasicTextBox*	m_pMPRecoveryText;
	CBasicTextBox*	m_pSPRecoveryText;
	CBasicTextBox*	m_pCPRecoveryText;
	CBasicTextBox*	m_pPotionHPText;
	CBasicTextBox*	m_pPotionMPText;
	CBasicTextBox*	m_pPotionSPText;

	CBasicButton*	m_pHelpAdditional;

	CBasicButton*	m_pMouseOverAdditional[MOUSE_OVER_BUTTONS_ADDITIONAL];

	CBasicTextBox*	m_pCriticalRateMarkStatic;
	CBasicTextBox*	m_pStrikeHitMarkStatic;
	CBasicTextBox*	m_pMovingSpeedMarkStatic;
	CBasicTextBox*	m_pAttackSpeedMarkStatic;
	CBasicTextBox*	m_pEXPMarkStatic;
	CBasicTextBox*	m_pHPRecoveryMarkStatic;
	CBasicTextBox*	m_pMPRecoveryMarkStatic;
	CBasicTextBox*	m_pSPRecoveryMarkStatic;
	CBasicTextBox*	m_pCPRecoveryMarkStatic;
	CBasicTextBox*	m_pPotionHPMarkStatic;
	CBasicTextBox*	m_pPotionMPMarkStatic;
	CBasicTextBox*	m_pPotionSPMarkStatic;

	CBasicTextBox*	m_pCriticalRateMarkValue;
	CBasicTextBox*	m_pStrikeHitMarkValue;
	CBasicTextBox*	m_pMovingSpeedMarkValue;
	CBasicTextBox*	m_pAttackSpeedMarkValue;
	CBasicTextBox*	m_pEXPMarkValue;
	CBasicTextBox*	m_pHPRecoveryMarkValue;
	CBasicTextBox*	m_pMPRecoveryMarkValue;
	CBasicTextBox*	m_pSPRecoveryMarkValue;
	CBasicTextBox*	m_pCPRecoveryMarkValue;
	CBasicTextBox*	m_pPotionHPMarkValue;
	CBasicTextBox*	m_pPotionMPMarkValue;
	CBasicTextBox*	m_pPotionSPMarkValue;

	CCharacterWindowCharStatMark*	m_pCriticalRateMark;
	CCharacterWindowCharStatMark*	m_pStrikeHitMark;
	CCharacterWindowCharStatMark*	m_pMovingSpeedMark;
	CCharacterWindowCharStatMark*	m_pAttackSpeedMark;
	CCharacterWindowCharStatMark*	m_pEXPMark;
	CCharacterWindowCharStatMark*	m_pHPRecoveryMark;
	CCharacterWindowCharStatMark*	m_pMPRecoveryMark;
	CCharacterWindowCharStatMark*	m_pSPRecoveryMark;
	CCharacterWindowCharStatMark*	m_pCPRecoveryMark;
	CCharacterWindowCharStatMark*	m_pPotionHPMark;
	CCharacterWindowCharStatMark*	m_pPotionMPMark;
	CCharacterWindowCharStatMark*	m_pPotionSPMark;

public:
	void	InitData();
	DWORD	GetTextColor( int nVal );
	DWORD	GetTextColorFloat( float nVal );
};
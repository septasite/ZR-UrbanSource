#pragma	once

#include "../Interface/UIWindowEx.h"

#include "GLCharDefine.h"
#include "./GLCharData.h"
#include "./GLCrowData.h"
#include "./GLogicData.h"
#include "GLogicEx.h"
#include "GLItem.h"
#include "GLItemDef.h"
#include "./GLCharacter.h"
#include "GLLandManClient.h"

class	CCharacterWindowCharRenderView;
class	CD3DFontPar;
class	CBasicProgressBar;
class	CBasicTextBox;
class	CBasicTextButton;
class	CBasicButton;
class	CBasicButtonText;
class	CBasicLineBox;
struct	GLCHARLOGIC;
struct  SDROP_CHAR;
struct  STARGETID;
class	CItemImage;
class	GLCharClient;
class	CInventoryPageWearView;

class CCharacterViewPropertiesWindow : public CUIWindowEx
{
protected:
	enum
	{
		INVENTORY_PAGEWEAR_VIEW = ET_CONTROL_NEXT,
		VIEWCHARACTER_BUTTON_TAP,
		VIEWCHARACTER_BUTTON_TAP1,
		VIEWCHARACTER_BUTTON_TAP2,
		VIEWCHARACTERHELP_BUTTON,
		VIEWCHARACTERHELP_BUTTON_OVER,
		VIEWCHARACTER_REFRESH_BUTTON,
		VIEWCHARACTER_REFRESH_BUTTON_OVER,
		//VIEWCHARACTER_AROW_BUTTON,
		//VIEWCHARACTER_AROW_BUTTON_OVER,
		BACKGROUND_CHARACTER_NAME,
		VIEWCHARACTER_COSTUME_BUTTON,
		VIEWCHARACTER_SKILL_BUTTON,
		VIEWCHARACTER_WHISPER_BUTTON,
		VIEWCHARACTER_FRIEND_BUTTON,
		VIEWCHARACTER_PARTY_BUTTON,
		VIEWCHARACTER_FRESH_BUTTON,
		VIEWCHARACTER_ADD_BUTTON,
		CHECK_BUTTON0,
		CHECK_BUTTON1,
		CHECK_BUTTON2,
		CHECK_BUTTON3,
	};
public:
	CCharacterViewPropertiesWindow ();
	virtual	~CCharacterViewPropertiesWindow ();

public:
	virtual void SetGlobalPos(const D3DXVECTOR2& vPos);
	

public:
	void	CreateSubControl ();
	void    ViewpropertiseNet( NET_MSG_GENERIC* nmg );
	virtual	HRESULT	Render ( LPDIRECT3DDEVICEQ pd3dDevice);
	GLCharacter					m_Character;
	D3DCAPSQ			m_d3dCaps;
	D3DSURFACE_DESC		m_d3dsdBackBuffer;
	DxLandMan			m_LandLogin;

	DxSkinChar*			m_pSkinChar;
	D3DXMATRIX			m_matTrans;
	D3DXVECTOR3			m_vMaxOrg;
	D3DXVECTOR3			m_vMinOrg;
	D3DXVECTOR3			m_vDir;
	D3DXVECTOR3			m_vDirOrig;
	D3DXVECTOR3			m_vPos;
	D3DXVECTOR3			m_vMax;
	D3DXVECTOR3			m_vMin;

	float			m_fHeight;
	LPDIRECT3DDEVICEQ	m_pd3dDevice;
	void	ClearRender();
	CCharacterWindowCharRenderView*		m_pRender;

public:
	void	SetViewCharInfo ( CString strPlayerName, DWORD dwMasterID );
	DWORD	GetMasterID ();

	private:
	DWORD	m_dwMasterID;

private:
	CBasicTextBox*	CreateStaticControl ( char* szConatrolKeyword, CD3DFontPar* pFont, int nAlign, const UIGUID& cID = NO_ID );
	CItemImage*					m_pSlotItem[SPREVIEWDATA::PREVIEW_SLOTS];
	SITEMCUSTOM					m_ItemCustomArray[SPREVIEWDATA::PREVIEW_SLOTS];
	CBasicTextBox*				m_pSlotText[SPREVIEWDATA::PREVIEW_SLOTS];
	virtual	void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );	
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	virtual	void SetVisibleSingle ( BOOL bVisible );
	//void	ClearRender();
	PLANDMANCLIENT				m_pLandMClient;
	CBasicTextButton*	CreateTextButton23 ( const char* szButton, UIGUID ControlID, const char* szText );
	CBasicTextButton*	CreateTextButton24 ( const char* szButton, UIGUID ControlID, const char* szText );
	CBasicButtonText*	CreateButtonRed ( char* szButton, char* szTextBox, CD3DFontPar* pFont, int nAlign, UIGUID ControlID, CString strText );
	CBasicButton*	m_pButtonMenuL[1];
	CBasicButton*	m_pButtonMenuR[1];
	CBasicButtonText*	m_pButtonWhisper[1];
	CBasicButtonText*	m_pButtonAddFriend[1];
	CBasicButtonText*	m_pButtonParty[1];
	CBasicButtonText*	m_pButtonRefresh[1];
	CBasicButtonText*	m_pButtonAdd[1];
	CBasicTextButton* m_pCostumeButton;
	CBasicTextButton* m_pSkillButton;

private:
	DWORD	m_dwGaeaID;
	CString	m_szPlayerName;

	BOOL	m_bSetThisFrame;
	int		m_nOverMenu;

	CBasicTextBox*	m_pNameBox;
public:	//	이름,클래스
	void	SetName ( NET_MSG_GENERIC* nmg );
	void	SetLevel ( NET_MSG_GENERIC* nmg );
	
	void	SetAcademy ( NET_MSG_GENERIC* nmg );
	//void	SetClass ( NET_MSG_GENERIC* nmg );
	void	SetClub ( NET_MSG_GENERIC* nmg );
	
	void	SetPkW ( NET_MSG_GENERIC* nmg );
	void	SetPkL ( NET_MSG_GENERIC* nmg );
	
	void	SetMoney ( NET_MSG_GENERIC* nmg );
	void	SetMoney2 ( NET_MSG_GENERIC* nmg );
	void	SetMoney3 ( NET_MSG_GENERIC* nmg );
	
	void	SetPow ( NET_MSG_GENERIC* nmg );
	void	SetDex ( NET_MSG_GENERIC* nmg );
	void	SetSpi ( NET_MSG_GENERIC* nmg );
	void	SetStr ( NET_MSG_GENERIC* nmg );
	void	SetSta ( NET_MSG_GENERIC* nmg );
	
	void    SetDamage ( NET_MSG_GENERIC* nmg );
	void    SetDefense ( NET_MSG_GENERIC* nmg );
	void	SetReqPa ( NET_MSG_GENERIC* nmg );
	void	SetReqSa ( NET_MSG_GENERIC* nmg );
	void	SetReqMa ( NET_MSG_GENERIC* nmg );
	void	SetHitRate ( NET_MSG_GENERIC* nmg );
	void	SetAvoidRate ( NET_MSG_GENERIC* nmg );
	void	SetHP ( NET_MSG_GENERIC* nmg );
	void	SetMP ( NET_MSG_GENERIC* nmg );
	void	SetSP ( NET_MSG_GENERIC* nmg );
	
	void	SetFireResi ( NET_MSG_GENERIC* nmg );
	void	SetColdResi ( NET_MSG_GENERIC* nmg );
	void	SetElectricResi ( NET_MSG_GENERIC* nmg );
	void	SetPoisonResi ( NET_MSG_GENERIC* nmg );
	void	SetSpiritResi ( NET_MSG_GENERIC* nmg );

	void	SetStaff ( NET_MSG_GENERIC* nmg );
	void	SetPtoPMenu( NET_MSG_GENERIC* nmg );
	void	SetRender	( NET_MSG_GENERIC* nmg );
private:
	CBasicTextBox*		m_pNameText;
	CBasicTextBox*		m_pLevelText;
	CBasicTextBox*		m_pAcademyText;
	//CBasicTextBox*      m_pClassText;
	CBasicTextBox*      m_pPkWText;
	CBasicTextBox*      m_pPkLText;

	CBasicTextBox*		m_pLevelTextStatic;
	
	CBasicTextBox*		m_pTip1TextStatic;
	CBasicTextBox*		m_pTip2TextStatic;
	CBasicTextBox*		m_pTip3TextStatic;
	CBasicTextBox*		m_pTip4TextStatic;
	
	CBasicTextBox*		m_pDamageHighText;
	CBasicTextBox*		m_pDamageLowText;
	CBasicTextBox*		m_pDefenseText;
	CBasicTextBox*		m_pReqPaText;
	CBasicTextBox*		m_pReqSaText;	
	CBasicTextBox*		m_pReqMaText;	
	CBasicTextBox*		m_pHitRateText;
	CBasicTextBox*		m_pAvoidRateText;
	CBasicTextBox*		m_pHPText;
	CBasicTextBox*		m_pMPText;
	CBasicTextBox*		m_pSPText;
	
	CBasicTextBox*		m_pDamageHighTextStatic;
	CBasicTextBox*		m_pDamageLowTextStatic;
	CBasicTextBox*		m_pDefenseTextStatic;
	CBasicTextBox*		m_pReqPaTextStatic;
	CBasicTextBox*		m_pReqSaTextStatic;	
	CBasicTextBox*		m_pReqMaTextStatic;	
	CBasicTextBox*		m_pHitRateTextStatic;
	CBasicTextBox*		m_pAvoidRateTextv;
	CBasicTextBox*		m_pHPTextStatic;
	CBasicTextBox*		m_pMPTextStatic;
	CBasicTextBox*		m_pSPTextStatic;
	
	CBasicTextBox*		m_pFireTextStatic;
	CBasicTextBox*		m_pColdTextStatic;
	CBasicTextBox*		m_pElectricTextStatic;
	CBasicTextBox*		m_pPoisonTextStatic;
	CBasicTextBox*		m_pSpiritTextStatic;

	CBasicTextBox*		m_pFireText;
	CBasicTextBox*		m_pColdText;
	CBasicTextBox*		m_pElectricText;
	CBasicTextBox*		m_pPoisonText;
	CBasicTextBox*		m_pSpiritText;
	
	CBasicTextBox*		m_pPowText;
	CBasicTextBox*		m_pDexText;
	CBasicTextBox*		m_pSpiText;
	CBasicTextBox*		m_pIntText;
	CBasicTextBox*		m_pStrText;
	CBasicTextBox*		m_pStaText;

	CBasicTextBox*		m_pPowTextStatic;
	CBasicTextBox*		m_pDexTextStatic;
	CBasicTextBox*		m_pSpiTextStatic;
	CBasicTextBox*		m_pIntTextStatic;
	CBasicTextBox*		m_pStrTextStatic;
	CBasicTextBox*		m_pStaTextStatic;
	
	CBasicTextBox*		m_pMoneyText;
	CBasicTextBox*		m_pMoney2Text;
	CBasicTextBox*		m_pMoney3Text;
	CBasicTextBox*  	m_pClubText;

	CBasicTextBox*		m_pStaffText;

	CBasicTextBox*		m_pLevelTextCompare;
	CBasicTextBox*		m_pPowTextCompare;
	CBasicTextBox*		m_pDexTextCompare;
	CBasicTextBox*		m_pIntTextCompare;
	CBasicTextBox*		m_pStrTextCompare;
	CBasicTextBox*		m_pStaTextCompare;
	CBasicTextBox*		m_pDamageLowTextCompare;
	CBasicTextBox*		m_pDamageHighTextCompare;
	CBasicTextBox*		m_pDefenseTextCompare;
	CBasicTextBox*		m_pReqPaTextCompare;
	CBasicTextBox*		m_pReqSaTextCompare;
	CBasicTextBox*		m_pReqMaTextCompare;
	CBasicTextBox*		m_pHitRateTextCompare;
	CBasicTextBox*		m_pAvoidRateTextCompare;
	CBasicTextBox*		m_pHPTextCompare;

private:
	CUIControl*			m_bg_white;
	CUIControl*			pButtonCheck0;
	CUIControl*			pButtonCheckOver0;
	CUIControl*			pButtonCheck1;
	CUIControl*			pButtonCheckOver1;
	CUIControl*			pButtonCheck2;
	CUIControl*			pButtonCheckOver2;
	CUIControl*			pButtonCheck3;
	CUIControl*			pButtonCheckOver3;
	
	//CUIControl*			pBackGroundName;

	CUIControl*			pCharacterLevelGreenArrow;
	CUIControl*			pCharacterLevelRedArrow;
	CUIControl*			pCharacterPowGreenArrow;
	CUIControl*			pCharacterPowRedArrow;
	CUIControl*			pCharacterDexGreenArrow;
	CUIControl*			pCharacterDexRedArrow;
	CUIControl*			pCharacterIntGreenArrow;
	CUIControl*			pCharacterIntRedArrow;
	CUIControl*			pCharacterStrGreenArrow;
	CUIControl*			pCharacterStrRedArrow;
	CUIControl*			pCharacterStaGreenArrow;
	CUIControl*			pCharacterStaRedArrow;
	CUIControl*			pCharacterDamageLowGreenArrow;
	CUIControl*			pCharacterDamageLowRedArrow;
	CUIControl*			pCharacterDamageHighGreenArrow;
	CUIControl*			pCharacterDamageHighRedArrow;
	CUIControl*			pCharacterDefenseGreenArrow;
	CUIControl*			pCharacterDefenseRedArrow;
	CUIControl*			pCharacterReqPaGreenArrow;
	CUIControl*			pCharacterReqPaRedArrow;
	CUIControl*			pCharacterReqSaGreenArrow;
	CUIControl*			pCharacterReqSaRedArrow;
	CUIControl*			pCharacterReqMaGreenArrow;
	CUIControl*			pCharacterReqMaRedArrow;
	CUIControl*			pCharacterHitRateGreenArrow;
	CUIControl*			pCharacterHitRateRedArrow;
	CUIControl*			pCharacterAvoidRateGreenArrow;
	CUIControl*			pCharacterAvoidRateRedArrow;
	CUIControl*			pCharacterHPGreenArrow;
	CUIControl*			pCharacterHPRedArrow;
	
	CBasicLineBox*  	m_pBackLine1;
	CBasicLineBox*  	m_pBackLine2;
	CBasicLineBox*		m_pBackLine3;

	CBasicLineBox*  	m_pStatusLine1;
	CBasicLineBox*  	m_pStatusLine2;
	CBasicLineBox*  	m_pStatusLine3;
	CBasicLineBox*  	m_pStatusLine4;
	CBasicLineBox*  	m_pStatusLine5;
	CBasicLineBox*  	m_pStatusLine6;
	
public:
	//static CCharacterViewPropertiesWindow& GetInstance();
	void	SetItemInInventory( int nIndex , SITEMCUSTOM& sItemCustom );
	CInventoryPageWearView* m_pPageWearEx;
	void ReSetItemAll();
};
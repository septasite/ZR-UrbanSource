#pragma	once

#include "../Interface/UIWindowEx.h"
#include "../EngineUILib/GUInterface/UIGroup.h"
#include "DxCharSham.h"
#include "DxLandMan.h"
#include "GLCharacter.h"
#include "../../EngineLib/Meshs/DxSkinChar.h"
#include "../EngineUILib/GUInterface/UIMan.h"

class	CD3DFontPar;
class	CBasicProgressBar;
class	CBasicTextBox;
class   CBasicTextButton;
class	CBasicButton;
struct	GLCHARLOGIC;
class	CInventoryPageWear;
class	CInventoryPageWearEx;
class	GLCharacter;
class	DxCharSham;
class	CBasicComboBox;
class	CBasicComboBoxRollOver;
class	DxLandMan;
class	DxSkinCharData;
class	CCharacterWindowCharRender;

class CCharacterWindow : public CUIWindowEx
{
protected:
	enum
	{
		CHARACTER_WINDOW_STAT_POW_PLUS_BUTTON = ET_CONTROL_NEXT,
		CHARACTER_WINDOW_STAT_DEX_PLUS_BUTTON,
		CHARACTER_WINDOW_STAT_SPI_PLUS_BUTTON,
		CHARACTER_WINDOW_STAT_STR_PLUS_BUTTON,
		CHARACTER_WINDOW_STAT_STA_PLUS_BUTTON,
		CHARACTER_WINDOW_STAT_POW_MINUS_BUTTON,
		CHARACTER_WINDOW_STAT_DEX_MINUS_BUTTON,
		CHARACTER_WINDOW_STAT_SPI_MINUS_BUTTON,
		CHARACTER_WINDOW_STAT_STR_MINUS_BUTTON,
		CHARACTER_WINDOW_STAT_STA_MINUS_BUTTON,
		CHARACTER_WINDOW_STAT_OK,
		CHARACTER_WINDOW_STAT_CANCEL,
		CHARACTER_MOBILE_BUTTON,
		INVENTORY_PAGEWEAR,
		INVENTORY_PAGEWEAR_EX,
		CHARWINDOW_INFO_BUTTON,

		CHARACTER_PREMIUM_TEXT,

		CHARACTER_BIRGHTER,
		NICKNAME_COMBO_OPEN,
		NICKNAME_COMBO_ROLLOVER,
	};

public:
    CCharacterWindow ();
	virtual	~CCharacterWindow ();
public:
	DWORD				m_dwGaeaID;
	virtual DWORD GetCtrlID () const		{ return m_dwGaeaID; }
public:
//	virtual HRESULT InitDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );
	virtual	HRESULT	Render ( LPDIRECT3DDEVICEQ pd3dDevice);
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	virtual	void SetVisibleSingle ( BOOL bVisible );
	//virtual void SetGlobalPos(const D3DXVECTOR2& vPos);
//	virtual HRESULT FrameMove ( float fTime, float fElapsedTime );
//	virtual HRESULT UpdateSuit ();
//	virtual HRESULT SkinLoad ( LPDIRECT3DDEVICEQ pd3dDevice );
//	virtual HRESULT CreateX (DWORD dwGaeaID, LPDIRECT3DDEVICEQ pd3dDevice );
	

public:
	void	CreateSubControl ();

	void	LoadComboData ();
	void	LoadItem ();
	
	void	SetArmSwapTabButton( BOOL bArmSub );

	CCharacterWindowCharRender*		m_pRender;
	GLCharacter*		m_CharacterNew;
	DxCharSham			m_NewCharSham;
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
	BOOL	IsCurUseArm( EMSLOT emSlot );
	BOOL IsUseArmSub() const			{ return m_CharacterNew->m_bUseArmSub; }

private:
	CBasicTextBox*	CreateStaticControl ( char* szConatrolKeyword, CD3DFontPar* pFont, int nAlign, const UIGUID& cID = NO_ID );
	

private:
	void	SetPointControl ( BOOL bPointUsable );

private:	//	ÀÌ¸§,Å¬·¡½º
	void	SetName ( const GLCHARLOGIC& sCharData );

private:	//	°æÇèÄ¡
	void	SetEXP( const GLCHARLOGIC& sCharData );

private:	//	Stat
	void	SetLevel ( const GLCHARLOGIC& sCharData );
	void	SetPow ( const GLCHARLOGIC& sCharData );
	void	SetDex ( const GLCHARLOGIC& sCharData );
	void	SetSpi ( const GLCHARLOGIC& sCharData );
	void	SetInt ( const GLCHARLOGIC& sCharData );
	void	SetStr ( const GLCHARLOGIC& sCharData );
	void	SetSta ( const GLCHARLOGIC& sCharData );
	void	SetPoint ( const GLCHARLOGIC& sCharData );

	void	SetPow2 ( int num,const GLCHARLOGIC& sCharData );
	void	SetDex2 ( int num,const GLCHARLOGIC& sCharData );
	void	SetSpi2 ( int num,const GLCHARLOGIC& sCharData );
	void	SetStr2 ( int num,const GLCHARLOGIC& sCharData );
	void	SetSta2 ( int num,const GLCHARLOGIC& sCharData );
	void	SetPoint2 ( int num );

private:	//	Status
	void	SetDamage ( const GLCHARLOGIC& sCharData );
	void	SetDefense ( const GLCHARLOGIC& sCharData );
	void	SetReqPa ( const GLCHARLOGIC& sCharData );
	void	SetReqSa ( const GLCHARLOGIC& sCharData );
	void	SetReqMa ( const GLCHARLOGIC& sCharData );
	void	SetHitRate ( const GLCHARLOGIC& sCharData );
	void	SetHP ( const GLCHARLOGIC& sCharData );
	void	SetMP ( const GLCHARLOGIC& sCharData );
	void	SetSP ( const GLCHARLOGIC& sCharData );
	void	SetCP ( const GLCHARLOGIC& sCharData );
	void	SetRB ( const GLCHARLOGIC& sCharData );
	void	SetAvoidRate ( const GLCHARLOGIC& sCharData );
	void	SetPremium ();

private:	//	ÀúÇ×·Â
	void	SetFireResi ( const GLCHARLOGIC& sCharData );
	void	SetColdResi ( const GLCHARLOGIC& sCharData );
	void	SetElectricResi ( const GLCHARLOGIC& sCharData );
	void	SetPoisonResi ( const GLCHARLOGIC& sCharData );
	void	SetSpiritResi ( const GLCHARLOGIC& sCharData );

	void	SetBright ( const GLCHARLOGIC& sCharData );
	void	SetPKState ( const GLCHARLOGIC& sCharData );
	void	SetGrade ( const GLCHARLOGIC& sCharData );
	void	SetActivityPoint ( const GLCHARLOGIC& sCharData );	//	»ýÈ°Á¡¼ö
	void	SetAcademy_Department ( const GLCHARLOGIC& sCharData );		//	ÇÐ±³
	void	SetNumber2 ( int nIndex, int nNumber );
	void	SetNumber3 ( int nIndex, int nNumber );
	void	ResetNumber ( int nIndex );

public:
	void	SetPhoneNumber( const CString & strPhoneNumber );

private:
	LPDIRECT3DDEVICEQ	m_pd3dDevice;
	GLCharacter*		m_pCharacter;
	CBasicTextBox*		m_pNameText;
	//GLCharacter*		m_pCharacter;
	CBasicComboBox*			m_pComboBoxNickNameOpen;
	CBasicComboBoxRollOver*	m_pComboBoxNickNameRollOver;

private:
	CBasicTextBox*	m_pPremiumTextStatic;

private:	//	°æÇèÄ¡
	CBasicProgressBar*	m_pEXP;
	CBasicTextBox*		m_pEXPText;

	CInventoryPageWear*	m_pPageWear;
	CInventoryPageWearEx* m_pPageWearEx;

private:	//	Stats
	CBasicButton*	m_pButtonPlus[5];
	CBasicButton*	m_pButtonMinus[5];

	CBasicTextButton* CreateTextButton23 ( const  char* szButton, UIGUID ControlID, const  char* szText );
	CBasicTextButton* CreateTextButton24 ( const  char* szButton, UIGUID ControlID, const  char* szText );
	CBasicTextButton* CreateTextButton25 ( const  char* szButton, UIGUID ControlID, const  char* szText );
	CBasicTextButton* CreateTextButton ( const char* szButton, UIGUID ControlID, const char* szText );

	CBasicButton*  m_pButtonOk;
	CBasicButton*  m_pButtonCancel;

	int		m_pNewPow;
	int		m_pNewDex;
	int		m_pNewSpi;
	int		m_pNewStr;
	int		m_pNewSta;
	int		m_pNewPoint;

	int		nIndex;


	///CUIControl*	m_pPowDiaableButton;
	//CUIControl*	m_pDexDiaableButton;
	//CUIControl*	m_pSpiDiaableButton;
	//CUIControl*	m_pIntDiaableButton;
	//CUIControl*	m_pStrDiaableButton;
	//CUIControl*	m_pStaDiaableButton;
	
	CBasicTextBox*	m_pPointText2;

	CBasicTextBox*	m_pPowText;
	CBasicTextBox*	m_pDexText;
	CBasicTextBox*	m_pSpiText;
	CBasicTextBox*	m_pIntText;
	CBasicTextBox*	m_pStrText;
	CBasicTextBox*	m_pStaText;

	CBasicTextBox*	m_pPowText2;
	CBasicTextBox*	m_pDexText2;
	CBasicTextBox*	m_pSpiText2;
	CBasicTextBox*	m_pIntText2;
	CBasicTextBox*	m_pStrText2;
	CBasicTextBox*	m_pStaText2;

	CBasicTextBox*	m_pPowTextStatic;
	CBasicTextBox*	m_pDexTextStatic;
	CBasicTextBox*	m_pSpiTextStatic;
	CBasicTextBox*	m_pIntTextStatic;
	CBasicTextBox*	m_pStrTextStatic;
	CBasicTextBox*	m_pStaTextStatic;

	CUIControl*	m_pPointDisable;
	CUIControl*	m_pPointEnable;
	CBasicTextBox*	m_pPointText;	

private:	//	Status
	CBasicTextBox*	m_pLevelText;
	CBasicTextBox*	m_pClubText;
	CBasicTextBox*	m_pDamageMinText;
	CBasicTextBox*	m_pDamageMaxText;
	CBasicTextBox*	m_pDefenseText;
	CBasicTextBox*	m_pReqPaText;
	CBasicTextBox*	m_pReqSaText;	
	CBasicTextBox*	m_pReqMaText;	
	CBasicTextBox*	m_pHPText;
	CBasicTextBox*	m_pMPText;
	CBasicTextBox*	m_pSPText;
	CBasicTextBox*	m_pCPText;
	CBasicTextBox*	m_pRBText;
	CBasicTextBox*	m_pHitRateText;
	CBasicTextBox*	m_pAvoidRateText;
	CBasicTextBox*	m_pPremiumText;
	CBasicTextBox*	m_pDamageMinText2;
	CBasicTextBox*	m_pDamageMaxText2;
	CBasicTextBox*	m_pDefenseText2;
	CBasicTextBox*	m_pReqPaText2;
	CBasicTextBox*	m_pReqSaText2;	
	CBasicTextBox*	m_pReqMaText2;	
	CBasicTextBox*	m_pHPText2;
	CBasicTextBox*	m_pMPText2;
	CBasicTextBox*	m_pSPText2;
	CBasicTextBox*	m_pCPText2;
	CBasicTextBox*	m_pHitRateText2;
	CBasicTextBox*	m_pAvoidRateText2;
	CBasicTextBox*	m_pPremiumText2;
	CBasicTextBox*	m_pDamageMinText3;
	CBasicTextBox*	m_pDamageMaxText3;
	CBasicTextBox*	m_pDefenseText3;
	CBasicTextBox*	m_pReqPaText3;
	CBasicTextBox*	m_pReqSaText3;	
	CBasicTextBox*	m_pReqMaText3;	
	CBasicTextBox*	m_pHPText3;
	CBasicTextBox*	m_pMPText3;
	CBasicTextBox*	m_pSPText3;
	CBasicTextBox*	m_pCPText3;
	CBasicTextBox*	m_pHitRateText3;
	CBasicTextBox*	m_pAvoidRateText3;

private:	//	ÀúÇ×·Â
	CBasicTextBox*	m_pFireText;
	CBasicTextBox*	m_pColdText;
	CBasicTextBox*	m_pElectricText;
	CBasicTextBox*	m_pPoisonText;
	CBasicTextBox*	m_pSpiritText;

private:	//	ÊèÇ¹µÑÇ
	CBasicTextBox*	m_pAcademy_Department;
	CBasicTextBox*	m_pActivityPointText;
	CBasicTextBox*	m_pActivityPointValue;
	CBasicTextBox*	m_pPKStateText;

	CBasicTextBox*	m_pDepartment;
	CUIControl*		m_pBrightFrame;
	CUIControl*		m_pBrightSlider;
	CBasicTextBox*	m_pGradeText;
	CBasicTextBox*	m_pGradeValue;
	CBasicTextBox*  m_pMobileText;


/*private:
	static const int nSCHOOL_MARK = 3;
	CUIControl*	m_pSchoolMark[nSCHOOL_MARK];*/
void	ClearRender();
};
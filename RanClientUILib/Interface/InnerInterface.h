#pragma	once

#include "../EngineUIlib/GUInterface/UIMan.h"
#include "../RanClientLib/G-Logic/GLCharClient.h"
#include "./InnerInterfaceGuid.h"
class	CkillTimeDisplay;

class	CItemMallIcon;
class	CItemShopWindow;
class	CInventoryViewCharItemWindow;
class	CInventoryPageWearView;


class	CAcademyConftDisplay;	
class	CAdminMessageDisplay;	
class	CBasicButton;	
class	CBasicChat;	
class	CBasicGameMenu;	
class   CQBoxButton;
class	CFBButton;
class	CTWButton;
class   CInBoxIcon;
class   CAtteIcon;
class   CSWarIcon;
class	CQBoxTimeUnit;			//add qbox
class	CPetTimeUnit;			//add petimage
class	CVehicleTimeUnit;		//add vehicleimage
class	CPetDisplay;			//add petimage
class	CVehicleDisplay;		//add vehicleimage
class	CBasicInfoView;	
class	CBasicPotionTray;	
class	CBasicQuickSkillSlot;	
class	CBasicSkillTray;	
class	CBasicSkillTrayNew;
class	CBasicVarTextBox;	
class	CBlockProgramAlarm;	
class	CBusWindow;	
class	CCharacterWindow;	
class	CCharacterViewPropertiesWindow;//add charinfoview
class	CChatMacroWindow;	
class	CClubMake;	
class	CClubStorageWindow;	
class	CClubWindow;	
class	CConftConfirm;	
class	CConftDisplayMan;	
class	CConftModalWindow;	
class	CCountMsg;
class	CCountMsgCD;	
class	CDamageDisplayMan;	
class	CDialogueWindow;	
class	CFriendWindow;	
class	CGambleAgainBox;	
class	CGambleAnimationBox;	
class   CPetSkinMixImage;
class	CGambleBox;	
class	CGambleResultEvenBox;	
class	CGambleResultOddBox;	
class	CGambleSelectBox;	
class	CHeadChatDisplayMan;	
class	CInventoryWindow;	
//class	CItemBankWindow;	
class	CVNGainSysInventory;
class   CVNGainSysGauge;
class	CItemMove;	
class	CItemRebuild;	// ITEMREBUILD_MARK
class	CKeySettingWindow;	
class	CLargeMapWindow;	
class	CMapMoveDisplay;	
class	CMarketWindow;	
class	CMiniMap;	
class	CMiniPartyWindow;	
class	CModalWindow;	
class	CNameDisplayMan;	
class	CPartyModalWindow;	
class	CPartyWindow;	
class	CPetRebirthDialogue;// Monster7j	
class	CPetWindow;	
class	CPrivateMarketMake;	
class	CPrivateMarketSellWindow;	
class	CPrivateMarketShowMan;	
class	CPrivateMarketWindow;	
class	CPtoPWindow;	
class	CQuestAlarm;	
class	CItemMix;
class	CQuestionItemDisplay;	
class	CQuestWindow;	
class	CRebirthDialogue;	
class	CRebuildInventoryWindow;	
class	CReceiveNoteWindow;	
class	CSimpleHP;	
class	CSimpleMessageMan;	
class	CSkillTrayTab;	
class	CSkillTrayTabNew;
class	CSkillWindowToTray;	
class	CSMSSendWindow;	
class	CStorageChargeCard;	
class	CStorageWindow;	
class	CSubMasterSet;	
class	CSystemMessageWindow;	
class	CTargetInfoDisplay;	
class	CTargetInfoDisplayNpc;
class	CTargetInfoDisplayPlayer;
class	CTradeInventoryWindow;	
class	CTradeWindow;	
class	CUILeftTopGroup;	
class	CWaitServerDialogue;	
class	CWriteNoteWindow;	
struct	GLCHARLOGIC;	
class	GLCLUB;	
class	GLMapAxisInfo;	
struct	GLSKILL;	
struct	SCHARSKILL;	
struct	SITEMCUSTOM;	
struct	SNpcTalk;	
class	CBonusTimeGauge;
class	CBonusTimeDisplay;
class	CQuestHelper;
//class	CVehicleWindow;
class	CThaiCCafeMark;
class	CItemGarbage;
class	CGarbageInventoryWindow;
class	CItemShopIconMan;
class	CShopItemSearchWindow;
class	CItemSearchResultWindow;
class	CSummonWindow;
class	CSummonPosionDisplay;
class	CAttendanceBookWindow;
class	CClubBattleModal;
class	CMapRequireCheck;
class	CTaxiWindow;
class	CItemMixWindow;
class	CItemMixInvenWindow;
class	CGatherGauge;
class	CCdmRankingDisplay;
class	CCompundCompete;			//add Compund button - Ocram Networks
class	CItemPreview;	//add itempreview
class	CBasicQuickSkillWindow;
class	CBasicQuickSkillWindowNew;
class	CItemPreviewWindow; 
class	CBoxItemInfo;
class	CBasicVarTextBoxEx;
class	CPvpWindowDisplay;
class   CCrowTargetInfo;
//class	CPKItemDisplay;
class	CCrowTargetInfo;
class	CCrowTargetInfoNpc;
class	CCrowTargetInfoPlayer;
class	CPartyDisplay;
class	CPartyDisplayBuff;
class	CSwRankingDisplay;		//add school wars
class	CSwPRankingDisplay;
class	CSchoolWarWindow;
//add sw buff
class	CSwBonusMark;

class	CRRRankingDisplay;		//add school wars
class	CRRPRankingDisplay;



class	CPKComboDisplay; //Add PK Streak By NjD

class	CTargetInfoCtfDisplay;
class	CForceRebirth;		
class	CCtfRankingDisplay;
class	CCtfInfoDisplay;
class	CProgressDisplayCtf;
class	CCtfTopTenRank;
//class   CTyrannyWinnerRank;
//	NOTE
//		대련시에 키워드
enum
{
	CONFT_WIN_INDEX = 0,
	CONFT_LOSE_INDEX,
	CONFT_DRAW_INDEX
};

//	NOTE
//		학교
enum
{	
	SUNGMOON = 0,
	HYUNAM,
	BONGHWANG,
	INIT_SCHOOL = 100,
};

const float fDEFAULT_WAITTIME_LEFT = 5.0f;

class	CInnerInterface : public CUIMan
{
private:
	//	정보 표시 타입
	enum ET_INFOTYPE
	{		
		ET_ITEM_INFO,
		ET_SKILL_INFO,
		ET_GENERAL_INFO,
		ET_ITEM_INFO_LINK,
	};

public:
	static const int nOUTOFRANGE;
	static const float fMENU_LIFTUP;
	//CPartyDisplay*				m_pPartyDisplay;  
private: //	등록되는 모든 컨트롤
	
	//CInventoryViewCharItemWindow*				m_pInventoryViewCharItemWindow;
	CInventoryPageWearView*				m_pInventoryWindowView;

	CkillTimeDisplay*			m_pkillTimeDisplay;
	CAcademyConftDisplay*		m_pAcademyConftDisplay;				
	CAdminMessageDisplay*		m_pAdminMessageDisplay;				
	CBasicChat*					m_pChat;				
	CBasicGameMenu*				m_pGameMenu;		
	CQBoxButton*				m_pQBoxButton;
	CInBoxIcon*					m_pInBoxIcon;
	CAtteIcon*					m_pAtteIcon;
	CSWarIcon*					m_pSWarIcon;
	CCompundCompete*			m_pCompundCompete;
	CQBoxTimeUnit*				m_pQBoxTimeUnit;//add q box
	CPetTimeUnit*				m_pPetTimeUnit;//add petimage
	CVehicleTimeUnit*			m_pVehicleTimeUnit;//add vehicleimage
	CBasicInfoView*				m_pBasicInfoView;
	CBasicQuickSkillSlot*		m_pBasicQuickSkillSlot;				
	CBasicVarTextBox*			m_pInfoDisplay;			
	CBasicVarTextBox*			m_pInfoDisplayEx;	
	CBasicVarTextBoxEx*			m_pInfoDisplayLink;	
	CBlockProgramAlarm*			m_pBlockProgramAlarm;				
	CBusWindow*					m_pBusWindow;				
	CCharacterWindow*			m_pCharacterWindow;			
	CCharacterViewPropertiesWindow*			m_pCharacterViewPropertiesWindow;	//add charinfoview
	CChatMacroWindow*			m_pChatMacroWindow;			
	CClubMake*					m_pClubMake;	
	CClubStorageWindow*			m_pClubStorageWindow;			
	CClubWindow*				m_pClubWindow;		
	CConftConfirm*				m_pConftConfirm;		
	CConftDisplayMan*			m_pConftDisplayMan;			
	CConftModalWindow*			m_pConftModalWindow;			
	CCountMsg*					m_pCountMsgWindow;	
	CCountMsgCD*				m_pCountMsgCDWindow;	
	CDamageDisplayMan*			m_pDamageDisplayMan;				
	CDialogueWindow*			m_pDialogueWindow;				
	CFriendWindow*				m_pFriendWindow;				
	CGambleAgainBox*			m_pGambleAgainBox;			
	CGambleAnimationBox*		m_pGambleAnimationBox;				
	CPetSkinMixImage*			m_pPetSkinMixImage;
	CGambleBox*					m_pGambleBox;	
	CGambleResultEvenBox*		m_pGambleResultEvenBox;				
	CGambleResultOddBox*		m_pGambleResultOddBox;				
	CGambleSelectBox*			m_pGambleSelectBox;			
	CHeadChatDisplayMan*		m_pHeadChatDisplayMan;				
	CInventoryWindow*			m_pInventoryWindow;				
//	CItemBankWindow*			m_pItemBankWindow;				
	CItemShopWindow*			m_pItemShopWindow;				
	CVNGainSysInventory*		m_pVNGainSysInventory;				
	CVNGainSysGauge*			m_pVNGainSysGauge;
	CItemMove*					m_pItemMove;		
	CItemRebuild*				m_pItemRebuildWindow;	// ITEMREBUILD_MARK	
	CKeySettingWindow*			m_pKeySettingWindow;			
	CLargeMapWindow*			m_pLargeMapWindow;			
	CMapMoveDisplay*			m_pMapMoveDisplay;			
	CMarketWindow*				m_pMarketWindow;			
	CMiniMap*					m_pMiniMap;				
	CModalWindow*				m_pModalWindow;		
	CNameDisplayMan*			m_pNameDisplayMan;				
	CPartyModalWindow*			m_pPartyModalWindow;			
	CPartyWindow*				m_pPartyWindow;			
	CPetRebirthDialogue*		m_pPetRebirthDialogue;// Monster7j				
	CPetWindow*					m_pPetWindow;	
	CPrivateMarketMake*			m_pPrivateMarketMake;			
	CPrivateMarketSellWindow*	m_pPrivateMarketSellWindow;				
	CPrivateMarketShowMan*		m_pPrivateMarketShowMan;				
	CPrivateMarketWindow*		m_pPrivateMarketWindow;				
	CPtoPWindow*				m_pPtoPWindow;			
	CQuestAlarm*				m_pQuestAlarm;				
	CQuestionItemDisplay*		m_pQuestionItemDisplay;				
	CPKComboDisplay*				m_pPKComboDisplay; //Add PK Streak By NjD
	CQuestWindow*				m_pQuestWindow;				
	CRebirthDialogue*			m_pRebirthDialogue;			
	CRebuildInventoryWindow*	m_pRebuildInventoryWindow;				
	CSimpleHP*					m_pSimpleHP;				
	CSimpleHP*					m_pSummonHP;				
	CSkillTrayTab*				m_pSkillTrayTab;		
	CSkillTrayTabNew*			m_pSkillTrayTabNew;
	CSkillWindowToTray*			m_pSkillWindowToTray;				
	CStorageChargeCard*			m_pStorageChargeCard;			
	CStorageWindow*				m_pStorageWindow;			
	CSubMasterSet*				m_pSubMasterSet;		// 부마스터 설정 창
	CSystemMessageWindow*		m_pSystemMessageWindow;				
	CTargetInfoDisplay*			m_pTargetInfoDisplay;			
	CTargetInfoDisplayNpc*		m_pTargetInfoDisplayNpc;
	CTargetInfoDisplayPlayer*	m_pTargetInfoDisplayPlayer;	
	CTradeInventoryWindow*		m_pTradeInventoryWindow;				
	CTradeWindow*				m_pTradeWindow;			
	CUILeftTopGroup*			m_pUILeftTopGroup;			
	CWaitServerDialogue*		m_pWaitServerDisplay;
	CBonusTimeGauge*			m_pBonusTimeGauge;
	CBonusTimeDisplay*			m_pBonusTimeDisplay;
	CQuestHelper*				m_pQuestHelper;
	//CVehicleWindow*				m_pVehicleWindow;
	CThaiCCafeMark*				m_pThaiCCafeMark;
	//add sw buff
	CSwBonusMark*				m_pSwBonusMark;
	CItemMallIcon*				m_pItemMallIcon;
	CItemGarbage*				m_pItemGarbageWindow;
	CGarbageInventoryWindow*	m_pGarbageInventoryWindow;
	CItemShopIconMan*			m_pItemShopIconMan;
	CShopItemSearchWindow*		m_pShopItemSearchWindow;
	CItemSearchResultWindow*	m_pItemSearchResultWindow;
	CSummonWindow*				m_pSummonWindow;
	CAttendanceBookWindow*		m_pAttendanceBookWindow;
	CClubBattleModal*			m_pClubBattleModalWindow;
	CTaxiWindow*				m_pTaxiWindow;
	CMapRequireCheck*			m_pMapRequireCheckWindow;
	CItemMixWindow*				m_pItemMixWindow;
	CItemMixInvenWindow*		m_pItemMixInvenWindow;
	CGatherGauge*				m_pGatherGauge;
	CCdmRankingDisplay*			m_pCdmRankingDisplay;
	CPetDisplay*				pPetDisplay; //add petimage
	CVehicleDisplay*			pVehicleDisplay; //add vehicleimage
	CItemPreview*				m_pItemPreview; //add itempreview
	CBasicQuickSkillWindow*		m_pBasicQuickSkillWindow;
	CBasicQuickSkillWindowNew*	m_pBasicQuickSkillWindowNew;
//	CPartyDisplay*				m_pPartyDisplay; //add partydisplay
	CItemPreviewWindow*			m_pItemPreviewWindow; 
	CBoxItemInfo*				m_pBoxInfo; 
	CBasicButton* pButton;
	CSwRankingDisplay*			m_pSwRankingDisplay;		//add school wars
	CSwPRankingDisplay*			m_pSwPRankingDisplay;
	CSchoolWarWindow*			m_pSchoolWarWindow;
	CCrowTargetInfo*			m_pCrowTargetInfo; //Add new Interface
	CCrowTargetInfoNpc*			m_pCrowTargetInfoNpc; //Add new Interface
	CCrowTargetInfoPlayer*		m_pCrowTargetInfoPlayer; //Add new Interface

	CPvpWindowDisplay*			m_pPvpWindowDisplay;
	CPartyDisplay*				m_pPartyDisplay;
	CPartyDisplayBuff*				m_pPartyDisplayBuff;
	//CTyrannyWinnerRank*			m_pTyrannyWinnerRank;

	CRRRankingDisplay*			m_pRrRankingDisplay;		//add school wars
	CRRPRankingDisplay*			m_pRrPRankingDisplay;
	
	CTargetInfoCtfDisplay*		m_pTargetInfoCtfDisplay;
	CForceRebirth*				m_pForceRebirth;
	CCtfRankingDisplay*			m_pCtfRankingDisplay;
	CCtfInfoDisplay*			m_pCtfInfoDisplay;
	CProgressDisplayCtf*		m_pProgressCtfDisplay;
	CCtfTopTenRank*				m_pCtfTopTenRank;

private:
	CUIControl*	m_pSystemMessageWindowDummy;
	CUIControl*	m_pMapMoveDisplayDummy;
	CUIControl*	m_pBlockProgramAlarmDummy;
	CUIControl*	m_pLeftTopGroupDummy;
	CUIControl*	m_pBasicInfoViewDummy;
	CUIControl* m_pBasicPotionTrayDummy;
	CUIControl* m_pQuestAlarmDummy;

	void ResetControl();

private:
	bool m_bFirstVNGainSysCall;

public:
	CInnerInterface ();
	virtual	~CInnerInterface ();

public:
	virtual HRESULT InitDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );
	virtual HRESULT DeleteDeviceObjects ();
	virtual HRESULT OneTimeSceneInit ();
	virtual	HRESULT FrameMove ( LPDIRECT3DDEVICEQ pd3dDevice, float fTime, float fElapsedTime );
	virtual	void	TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	virtual HRESULT FinalCleanup ();

public:
	void SetMiniMapInfo ( GLMapAxisInfo &sInfo, CString strMapName );
	void SetFirstVNGainSysCall ( bool bFirstCall ) { m_bFirstVNGainSysCall = bFirstCall; }

public:
	CItemRebuild* 		GetItemRebuild() 	{ return m_pItemRebuildWindow; 	} //sealed card NaJDeV
	CLargeMapWindow*	GetLargeMapWindow()	{ return m_pLargeMapWindow; 	} //Request Crow List NaJDeV

public:
	CMiniMap*				GetMiniMap()					{ return m_pMiniMap; }
	CBasicQuickSkillSlot*	GetBasicQuickSkillSlot()		{ return m_pBasicQuickSkillSlot; }

	//CInventoryViewCharItemWindow*	GetInventoryViewCharItemWindow()	{ return m_pInventoryViewCharItemWindow; }
	CInventoryPageWearView*			GetInventoryViewWindow()				{ return m_pInventoryWindowView; }
	void CInnerInterface::SetInventoryViewWindowOpen ( DWORD dwTargetID );
	void CInnerInterface::SetInventoryViewWindowItem ( int nIndex , SITEMCUSTOM& sItemCustom );
	void CInnerInterface::CloseItemViewWindow();
	CItemShopWindow*		GetItemShop()					{ return m_pItemShopWindow; }
	CPvpWindowDisplay*		GetPvpWindow()					{ return m_pPvpWindowDisplay; }
	CkillTimeDisplay*		GetKillDisplay()				{ return m_pkillTimeDisplay; }
	CSkillWindowToTray*		GetSkillWindowToTray()			{ return m_pSkillWindowToTray; }
	CSkillTrayTab*		    GetSkillTrayTab()				{ return m_pSkillTrayTab; }
	CSkillTrayTabNew*		GetSkillTrayTabNew()			{ return m_pSkillTrayTabNew; }
	CPartyWindow*			GetPartyWindow()				{ return m_pPartyWindow; }
	CBasicChat*				GetChat()						{ return m_pChat; }
	CNameDisplayMan*		GetDispName()					{ return m_pNameDisplayMan; }
	CPrivateMarketShowMan*	GetPMarketShow()				{ return m_pPrivateMarketShowMan; }
	CTradeWindow*			GetTradeWindow()				{ return m_pTradeWindow; }
	CTradeInventoryWindow*	GetTradeInventoryWindow()		{ return m_pTradeInventoryWindow; }
	CPtoPWindow*			GetPtoPWindow()					{ return m_pPtoPWindow; }
	CInventoryWindow*		GetInventoryWindow()			{ return m_pInventoryWindow; }
	CItemMove*				GetItemMove()					{ return m_pItemMove; }
	CDialogueWindow*		GetDialogueWindow()				{ return m_pDialogueWindow; }	
	CMarketWindow*			GetMarketWindow()				{ return m_pMarketWindow; }
	CHeadChatDisplayMan*	GetHeadChatDisplayMan()			{ return m_pHeadChatDisplayMan; }
	CConftModalWindow*		GetConftModalWindow()			{ return m_pConftModalWindow; }
	CPartyModalWindow*		GetPartyModalWindow()			{ return m_pPartyModalWindow; }
	CConftDisplayMan*		GetConftDisplayMan()			{ return m_pConftDisplayMan; }
	CQuestWindow*			GetQuestWindow()				{ return m_pQuestWindow; }
	CFriendWindow*			GetFriendWindow()				{ return m_pFriendWindow; }
	CBasicGameMenu*			GetGameMenu()					{ return m_pGameMenu; }
	CQBoxButton*			GetQBoxButton()					{ return m_pQBoxButton; }
	CInBoxIcon*				GetInBoxIcon()					{ return m_pInBoxIcon; }
	CAtteIcon*				GetAtteIcon()					{ return m_pAtteIcon; }
	CSWarIcon*				GetSWarIcon()					{ return m_pSWarIcon; }
	CPetWindow*				GetPetWindow()					{ return m_pPetWindow; }
	CCharacterWindow*		GetCharacterWindow()			{ return m_pCharacterWindow; }
	CCharacterViewPropertiesWindow*		GetCharacterViewPropertiesWindow()			{ return m_pCharacterViewPropertiesWindow; }//add charinfoview
	CGambleBox*				GetGambleBox()					{ return m_pGambleBox; }
	CGambleSelectBox*		GetGambleSelectBox()			{ return m_pGambleSelectBox; }
	CGambleAgainBox*		GetGambleAgainBox()				{ return m_pGambleAgainBox; }
	CGambleAnimationBox*	GetGambleAnimationBox()			{ return m_pGambleAnimationBox; }
	CPetSkinMixImage*		GetPetSkinMixImage()			{ return m_pPetSkinMixImage; }
	CGambleResultEvenBox*	GetGambleResultEvenBox()		{ return m_pGambleResultEvenBox; }
	CGambleResultOddBox*	GetGambleResultOddBox()			{ return m_pGambleResultOddBox; }
	CModalWindow*			GetModalWindow()				{ return m_pModalWindow; }
	CKeySettingWindow*		GetKeySettingWindow()			{ return m_pKeySettingWindow; }
	CChatMacroWindow*		GetChatMacroWindow()			{ return m_pChatMacroWindow; }
	CItemShopIconMan*		GetItemShopIconMan()			{ return m_pItemShopIconMan; }
	CShopItemSearchWindow*	GetShopItemSearchWindow()		{ return m_pShopItemSearchWindow; }
	CItemSearchResultWindow* GetItemSearchResultWindow()	{ return m_pItemSearchResultWindow; }
	CSummonWindow*			GetSummonWindow()				{ return m_pSummonWindow; }
	CMapRequireCheck*		GetRequireCheck()				{ return m_pMapRequireCheckWindow; }
	CItemPreview*			GetItemPreview()				{ return m_pItemPreview; } //add itempreview

	CBasicButton*			GetpButton()					{ return pButton; }
	//CLargeMapWindow*		GetLargeMapWindow()				{ return m_pLargeMapWindow; }	
	CBasicQuickSkillWindow*	GetBasicQuickSkillWindow()		{ return m_pBasicQuickSkillWindow; }
	CBasicQuickSkillWindowNew*	GetBasicQuickSkillWindowNew()		{ return m_pBasicQuickSkillWindowNew; }

public:
	void	CloseAllWindow ();
	//int		state;

	//void	SetInventoryPage();

	//void	Setstate(int num)	{ state = num;}

public:
	BOOL	PrintMsgText ( D3DCOLOR dwColor, const char* szFormat, ... );
	BOOL	PrintConsoleText ( const char* szFormat, ... );

	BOOL	PrintMsgTextDlg ( D3DCOLOR dwColor, const char* szFormat, ... );
	BOOL	PrintConsoleTextDlg ( const char* szFormat, ... );

	BOOL	PrintMsgDlg ( D3DCOLOR dwColor, const char* szFormat, ... );

public:
	const char* MakeString ( const char* szFormat, ... );

	int		state;
	void	SetInventoryPage();
	void	Setstate(int num)	{ state = num;}

	USHORT	nUserPoint;

	BOOL	SkillTabClose;
	BOOL	SkillTabOpen;

	BOOL	SkillTabCloseNew;
	BOOL	SkillTabOpenNew;

	BOOL	RotateSkillTab;
	BOOL	RotateSkillTabNew;

public:
	BOOL IsGateOpen()							{ return m_bGateOpen; }
	void SetGateOpen( BOOL bGateOpen )			{ m_bGateOpen = bGateOpen; }
	void SetDamage( D3DXVECTOR3 vPos, int nDamage, DWORD dwDamageFlag, BOOL bAttack );
	void SetTargetInfo( STARGETID sTargetID, int wSchool );
	void SetTargetInfoNpc( STARGETID sTargetID );
	void SetTargetInfoPlayer( STARGETID sTargetID );
	//void SetTargetViewProperties( STARGETID sTargetID );
	void ResetTargetInfo()						{ HideGroup ( TARGETINFO_DISPLAY ); }
	void ResetTargetInfoNpc()						{ HideGroup ( TARGETINFO_DISPLAY_NPC ); }
	void ResetTargetInfoPlayer()						{ HideGroup ( TARGETINFO_DISPLAY_PLAYER ); }
	void ResetTargetCtfInfo()						{ HideGroup ( TARGETINFO_CTF_DISPLAY ); }
	
	//void SetCharAttackCompare ( int num );
	//Add new Interface
	void SetTargetInfoCrow ( STARGETID sTargetID );
	void SetTargetInfoCrowNpc ( STARGETID sTargetID );
	void SetTargetInfoCrowPlayer ( STARGETID sTargetID );
	void ResetTargetInfoCrow()						{ HideGroup ( CROW_TARGET_INFO ); }
	void ResetTargetInfoCrowNpc()						{ HideGroup ( CROW_TARGET_INFO_NPC ); }
	void ResetTargetInfoCrowPlayer()						{ HideGroup ( CROW_TARGET_INFO_PLAYER ); }

	void SetFightBegin ( const int nIndex );
	void SetFightEnd ( const int nResult );

	void SetAcademyFightBegin ( const int& nLMARK, const int& nLNUMBER, const int& nRMARK, const int& nRNUMBER );
	void SetAcademyUpdateNumber ( const int& nLNUMBER, const int& nRNUMBER );
	void SetAcademyFightEnd ();

	void SetBlockProgramFound( bool bFOUND )	{ m_bBlockProgramFound = bFOUND; }
	bool IsBlockProgramFound()					{ return m_bBlockProgramFound; }

	void SetBlockProgramAlarm( bool bAlarm )	{ m_bBlockProgramAlarm = bAlarm; }
	bool IsBlockProgramAlarm()					{ return m_bBlockProgramAlarm; }

public:	
	void	SetDialogueWindowOpen ( STARGETID sCrowID, GLCHARLOGIC* pCHAR );
	void	SetPtoPWindowOpen ( PGLCHARCLIENT pCharClient, DWORD dwGaeaID, GLCLUB & sClub );
	void	SetQuestWindowOpen ( DWORD dwQuestID );
	void	SetBusWindowOpen ( const DWORD dwGaeaID, SNpcTalk* pNpcTalk );

	void	SetTradeWindowOpen ( CString szPlayerName, DWORD dwTargetID );
	void	SetTradeWindowClose ();
	void	SetStorageWindowOpen ( DWORD dwNPCID );
	void	SetStorageWindowClose ();
	void	SetClubStorageWindowOpen ();
	void	SetClubStorageWindowClose ();
	void	SetMarketWindowOpen ( SNATIVEID sNativeID );
	void	SetMarketWindowClose ();
	void	SetStorageChargeOpen ( const WORD& wPosX, const WORD& wPosY );
	void	SetItemBankWindowOpen ();
	void	SetItemBankInfo ();
	void	SetItemShopInfo ();
	void	SetItemShopWindowOpen ();
	void	SetVNGainSysWindowOpen ();
	void	SetVNGainSysInfo ();
	void	SetDefaultPosInterface(UIGUID ControlID);

	void	OpenItemRebuildWindow();	// ITEMREBUILD_MARK
	void	CloseItemRebuildWindow();

	void	OpenItemGarbageWindow();	// 휴지통
	void	CloseItemGarbageWindow();

	void	SetPetDisplay();	//add petimage
	void	ResetPetDisplay();	//add petimage

	void	SetVehicleDisplay();	//add vehicleimage
	void	ResetVehicleDisplay(); //add vehicleimage

	void	OpenItemMixWindow( DWORD dwNpcID );		// 아이템 조합
	void	OpenItemMixWindowButton();		// 아이템 조합
	void	CloseItemMixWindow();

	void	SetItemMixResult( CString strMsg, bool bSuccess = false, bool bFail = false );

	void	OPEN_TAXI_WINDOW( WORD wPosX, WORD wPosY );			// 택시 카드

	void	SetPrivateMarketMake ();
	void	SetPrivateMarketOpen ( const bool& bOPENER, const DWORD& dwGaeaID );
	void	GetPrivateMarketInfo ( bool& bOPENER, DWORD& dwGaeaID );
	void	SetPrivateMarketClose ();	

	void	MODAL_PRIVATE_MARKET_SELLITEM ( const bool& bCOUNTABLE, const WORD& wPosX, const WORD& wPosY );

	void	SetClubMake ( const DWORD& dwNpcID );

	void	SetShotcutText ( DWORD nID, CString& strTemp );
	void	GetShotCutKey();
	void	GetChatMacro();
	void	AddChatMacro(int nIndex);
	void	ChatLog( bool bChatLogt, int nChatLogType );
	CString GET_RECORD_CHAT();
	CString GetdwKeyToString(int dwKey);

	void	SetArmSwap( BOOL bSwap );
	
public:
	void	SetLottoOpen ( const DWORD& dwGaeaID );

public:
	void	DOMODAL_ADD_FRIEND_REQ( const CString& strName );
	void	DOMODAL_CLUB_JOIN_ASK( const DWORD& dwMasterID, const CString& strClubName, const CString& strClubMaster );
	void	DOMODAL_UNION_JOIN_ASK( const DWORD& dwMasterID, const CString& strClubMaster );
	void	DOMODAL_CLUB_BATTLE_ASK( const DWORD& dwMasterID, const CString& strClubMaster, DWORD dwBattleTime, bool bAlliance = false );
	void	DOMODAL_CLUB_BATTLE_ARMISTICE_ASK( const DWORD& dwClubID, const CString& strClubName, bool bAlliance = false );
	void	DOMODAL_CLUB_AUTHORITY_ASK( const CString& strClubName );

	void	OPEN_MODAL ( const CString& strText, int nModalTitle, int nModalType, UIGUID CallerID = NO_ID, BOOL bHide = FALSE );
	void	OPEN_MODALESS ( const CString& strText, int nModalTitle, int nModalType, UIGUID CallerID = NO_ID, BOOL bHide = FALSE );
	void	CLOSE_MODAL ( const UIGUID cID, bool bMakeMsg );

public:
	DWORD GetEventQuestID()							{ return m_dwEventQuestID; }
	void SetEventQuestID( DWORD dwQuestID )			{ m_dwEventQuestID = dwQuestID; }

public:
	void	WAITSERVER_DIALOGUE_OPEN ( const CString& strMessage, const int nAction, const float fTimer = fDEFAULT_WAITTIME_LEFT );
	void	WAITSERVER_DIALOGUE_CLOSE();

public:
	void	ClearNameList ();

public:
	void	SetTradeWindowCloseReq ();

private:
	HRESULT	TEXTURE_PRE_LOAD ( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT	TEXTURE_PRE_UNLOAD ();

public:
	BOOL IsInventoryWindowOpen()			{ return IsVisibleGroup( INVENTORY_WINDOW ); }
	BOOL IsStorageWindowOpen()				{ return IsVisibleGroup( STORAGE_WINDOW ); }
	BOOL IsClubStorageWindowOpen()			{ return IsVisibleGroup( CLUB_STORAGE_WINDOW ); }
	BOOL IsMarketWindowOpen()				{ return IsVisibleGroup( MARKET_WINDOW ); }
	BOOL IsDialogueWindowOpen()				{ return IsVisibleGroup( DIALOGUE_WINDOW ); }

public:
	// 인터페이스 사용시 캐릭터의 움직임을 제어
	BOOL IsCharMoveBlock()							{ return m_bCharMoveBlock; }
	void SetCharMoveBlock()							{ m_bCharMoveBlock = TRUE; }
	void ResetCharMoveBlock()						{ m_bCharMoveBlock = FALSE; }
	BOOL IsOpenWindowToMoveBlock();

	BOOL IsSnapItem()								{ return m_bSnapItem; }
	void SetSnapItem()								{ m_bSnapItem = TRUE; }
	void ResetSnapItem()							{ m_bSnapItem = FALSE; }

	void SetFirstItemSlot()							{ m_bFirstItemSlot = false;	}
	void ResetFirstItemSlot()						{ m_bFirstItemSlot = true; }
	bool IsFirstItemSlot()							{ return m_bFirstItemSlot; }

	void SetFriendName( const CString& strName )	{ m_strMoveFriendName = strName; }
	const CString& GetFriendName() const			{ return m_strMoveFriendName; }

	void SetThaiCCafeClass( DWORD dwClass );
	void SetMyCCafeClass( int nClass );				// 말레이시아 PC방 이벤트
	//add sw buff
	void SetSwBonus( bool isWinner );

public:
	bool	SET_QUESTION_ITEM_ID ( int nID );
	bool	SET_PK_COMBO_ID ( int nID ); //Add PK Streak By NjD
	void	RESET_KEEP_PK_COMBO (); //Add PK Streak By NjD

	bool	SET_PROGRESSCTFDISPLAY_ID ( int nID );


	//add qbox
	void	SetQBoxTime ( float fTime );
	void	UpdateQBoxTime ( float fRTime );

	bool	SET_KEEP_QUESTION_ITEM_ID ( int nID );
	void	RESET_KEEP_QUESTION_ITEM ();

	void	BONUS_TIME_EVENT_START( bool bCharging ); // 이벤트 시작
	void	BONUS_TIME_EVENT_END(); // 이벤트 종료
	void	BONUS_TIME_BUSTER_START(); // 경험치 시작
	void	BONUS_TIME_BUSTER_END(); // 경험치 종료

	// 베트남 탐닉 방지 시스템 게이지
	void	SET_VNGAINTYPE_GAUGE( int nPos, int nLimit );

	void	SET_QUEST_HELPER( DWORD dwQuestID );
	void	RESET_QUEST_HELPER( DWORD dwQuestID );

public:
	void	SET_CONFT_CONFIRM_VISIBLE ( bool bVisible );
	void	SET_CONFT_CONFIRM_PERCENT ( float fPercent );

public:
	void SetSkillUpID( const DWORD& dwID )			{ m_dwSkillUpID = dwID; }
	DWORD GetSkillUpID()							{ return m_dwSkillUpID; }
//	BOOL ISMASTER_SKILL( SNATIVEID skill_id );

	void SetItemInfoTemp( const SITEMCUSTOM& sID )		{ m_sItemInfoTemp = sID; }
	SITEMCUSTOM GetItemInfoTemp()						{ return m_sItemInfoTemp; }

private:
	void MoveBasicInfoWindow ();
	void BasicInfoViewDoubleClick();

private:
	BOOL	IsPartyMember ( const char* szName );

public:
	void	REFRESH_QUEST_WINDOW ();

	void	REFRESH_FRIEND_LIST ();
	void	REFRESH_FRIEND_STATE();

	void	REFRESH_CLUB_LIST ();
	void	REFRESH_CLUB_STATE ();
	void	REFRESH_CLUB_NOTICE();
	void	REFRESH_CLUB_ALLIANCE_LIST();
	void	REFRESH_CLUB_BATTLE_LIST();

	void	REFRESH_ITEMBANK ();
	void	REFRESH_VNGAINSYSTEM ();

	void	REFRESH_ATTENDBOOK();

	void	SET_GATHER_GAUGE( DWORD dwGaeaID, float fTime );

public:
	void	SetInventorySlotViewSize ( const int& nSLOT_VIEW_SIZE );
	int GetInventorySlotViewSize () const;

public:
	void ADD_FRIEND_NAME_TO_EDITBOX( const CString& strName );
	void ADD_FRIEND( const CString& strName );
	void FRIEND_LIST( CONST CString & strName, bool bOnline );

	const CString& GetPrivateMarketTitle ();

	void DoBattleModal( const CString strClubName, bool bAlliance = false );
	BOOL ReqClubBattle( DWORD dwTime, bool bAlliance );

private:
	ET_INFOTYPE		m_etInfoType;

public:
	void	RESET_INFO ();
	void	RESET_INFO_LINK ();
	void	CLEAR_INFO_LINK ();
	void	SET_INFO_LINK ( SITEMCUSTOM sITEM );
	void	SHOW_ITEM_INFO_LINK ( SITEMCUSTOM &sItemCustom );	

	void	SHOW_ITEM_INFO_SIMPLE ( SITEMCUSTOM &sItemCustom );
	void	SHOW_ITEM_INFO ( SITEMCUSTOM &sItemCustom, BOOL bShopOpen, BOOL bInMarket, BOOL bInPrivateMarket, WORD wPosX, WORD wPosY, SNATIVEID sNpcNativeID = SNATIVEID() );	
	void	SHOW_SKILL_INFO ( SNATIVEID sNativeID, const BOOL bNextLevel );
	void	SHOW_COMMON_LINEINFO ( const CString& strText, D3DCOLOR dwColor );
	void	SHOW_COMMON_LINEINFO_SPLIT ( const CString& strText, D3DCOLOR dwColor );

	bool	BEGIN_COMMON_LINEINFO_MULTI ();
	bool	ADD_COMMON_LINEINFO_MULTI ( const CString& strText, D3DCOLOR dwColor );
	void	END_COMMON_LINEINFO_MULTI ();

	void	WARNING_MSG_ON()			{ ShowGroupBottom( WARNING_MSG_WINDOW ); }
	void	WARNING_MSG_OFF()			{ HideGroup( WARNING_MSG_WINDOW ); }

	void	SLOT_EVENT_ON( bool bVisible, int nRamdomNumber );
	void	SLOT_EVENT_OFF()			{ HideGroup( COUNT_MSG_WINDOW ); }

	void	SLOT_EVENT_ON_CD( bool bVisible );
	void	SLOT_EVENT_OFF_CD()			{ HideGroup( COUNT_MSG_CD_WINDOW ); }

	void	SET_COUNT_MSG( INT nCount );

public:
	void	CLEAR_TEXT ();	
	void	REPOS_CONTROL ( int x, int y );
	int		ADDTEXT_NOSPLIT ( const CString& strText, const D3DCOLOR& dwColor );
	int		ADDTEXT_NOSPLIT_BIG ( const CString& strText, const D3DCOLOR& dwColor );
	void	ADDTEXT_MULTICOLOR_SPLIT (int nIndex, const CString& strText, const D3DCOLOR& dwColor );
	int		ADDTEXT ( const CString& strText, const D3DCOLOR& dwColor );
	void	ADDSTRING ( int nIndex, const CString& strText, const D3DCOLOR& dwColor );
	void	ADDTEXT_LONGESTLINE_SPLIT ( const CString& strText, const D3DCOLOR& dwColor );
//	void	ADDTEXT_NOSPLIT_BIG ( const CString& strText, const D3DCOLOR& dwColor );
	
public:
	void	ModalMsgProcess ( UIGUID nCallerID, DWORD dwMsg );	
	void	MsgProcess ( LPVOID msgBuffer );

public:
	const	D3DXVECTOR3&	GetCharDir () const				{ return m_vCharDir; }

public:
	void	SetAniPic(int nPic);
	void	SetOddEven(BOOL bOdd);

public:
	void	DisplayChatMessage ( int nType, const char *szName, const char *szMsg );
	void	DisplayChatMessage ( int nType, const char *szName, const char *szMsg, SITEMLINK sLINK );
	void	UpdateClubBattleTime( float fClubBattleTime, bool bTW = false );
	void	UpdateSchoolWarBattleTime( float fSchoolWarsTime );
	void	UpdateRoyalRumbleBattleTime( float fRoyalRumbleTime );
	void	ClearItemBank();
	void	ClearItemShop ();
	void	ClearVNGainSys();
	void	DisableMinimapTarget();

private:
	void	UpdateStatus ();
	void	UpdateShortcutBefore ();
	void	UpdateShortcutAfter ();

private:
	void	UpdateStateQuestAlarm ();
	void	UpdateStateSimpleHP ();
	void	UpdateSimpleMessage ();
public:
	void	ReqToggleRun ();
	bool	ItemShopAuth ();		// 일본 커스텀 브라우저 인증 모듈 //	ItemShopAuth
	void	ItemShopVisible();		// 일본 커스텀 브라우저 로딩 대기 //	ItemShopAuth

	void    ViewpropertiseNetTo(NET_MSG_GENERIC* nmg );//add charinfoview
	//void    Viewpropertise( SITEMCUSTOM sItem );//add charinfoview
	void	VisibleCDMRanking( bool bVisible );
	void	RefreashCDMRanking();

	//add school wars
	void	VisibleSWRanking( bool bVisible );
	void	VisibleSWPRanking( bool bVisible );
	void	RefreshSWRanking();
	void	RefreshSWPRanking();

	void	VisibleRRPRanking( bool bVisible );
	void	RefreshRRPRanking();

	void	VisibleCTFRanking( bool bVisible );
	void	VisibleCtfInfoDisplay( bool bVisible );
	void	RefreshCTFRanking();
	void	RefreshCtfIcon( bool bVecSw );

//#ifdef CH_PARAM // 중국 인터페이스 변경
//public:
//	void UpdatePotionTrayPosition();
//#endif

public:
	void	OpenCharacterPage();
	void	OpenVehiclePage();
	void	RefreshVehiclePage();

public:	//	ETC Func.
	SCONFT_OPTION*	GetConftOption ()			{ return &m_sReqConflictOption; }
	SPARTY_OPT*		GetPartyOption ()			{ return &m_sReqPartyOption; }

public:
	//SITEMCUSTOM		m_sItemInfoTemp;
	//void SetItemInfoTemp( const SITEMCUSTOM& sID )		{ m_sItemInfoTemp = sID; }
	//SITEMCUSTOM GetItemInfoTemp()						{ return m_sItemInfoTemp; }

public:
	bool IsCHANNEL() { return m_bCHANNEL; }
	bool IsCHAT_BEGIN();

private:
	BOOL			m_bGateOpen;
	BOOL			m_bCharMoveBlock;
	bool			m_bBlockProgramFound;
	bool			m_bBlockProgramAlarm;
	bool			m_bITEM_INFO_EX_DISPLAY_MODE;
	bool			m_bITEM_INFO_LINK_DISPLAY_MODE;
	DWORD			m_dwEventQuestStep;
	DWORD			m_dwEventQuestID;
	EMCONFT_TYPE	m_emConflictReqType;
	DWORD			m_ConflictReqID;
	SCONFT_OPTION	m_sReqConflictOption;
	SPARTY_OPT		m_sReqPartyOption;
	BOOL			m_bSnapItem;
	BOOL			m_bPartyStateBack;
	CString			m_strFriendName;
	D3DXVECTOR3		m_vCharDir;
	DWORD			m_dwSkillUpID;
	SITEMCUSTOM		m_sItemInfoTemp;
	SITEMCUSTOM		m_sItemInfoLinkTemp;
	bool			m_bUSING_INFO_DISPLAY;
	bool			m_bACADEMY_FIGHT_READY;
	CString			m_strGeneralInfoBack;
	float			m_fMoveWindowDistBack;
	bool			m_bFirstItemSlot;
	DWORD			m_dwClubMasterID;
	CString			m_strMoveFriendName;
	bool			m_bCHANNEL;
	bool			m_bTabReserve;
	float			m_fVehicleDelay;
	float			m_fItemBankDelay;
	float			m_fItemShopDelay;
	bool			m_bItemShopLoad;	//	ItemShopAuth

public:
	static CInnerInterface& GetInstance();

protected: //disable skill effect NaJDeV
	SNATIVEID		m_sSKILLID;

public:
	SNATIVEID		GetSKEFFID() { return m_sSKILLID; }
	void			SetSKEFFID(SNATIVEID sID) { m_sSKILLID = sID; }

public:
	bool	PreviewCheckSimple( SNATIVEID sID );
	bool	PreviewCheckWear( SNATIVEID sID );
	void	PreviewItem( SITEMCUSTOM sItem );
	void	LinkItem( SITEMCUSTOM* pItem );
	void	LinkItemGlobalGrind( SITEMCUSTOM* pItem );

public:
	BOOL	m_bDispMember;
	BOOL	m_bDispBuff;

	void	DisplayMember(BOOL bDisp)	{ m_bDispMember = bDisp;	}
	void	DisplayBuff(BOOL bDisp)		{ m_bDispBuff = bDisp;		}

	BOOL	IsMemberDisp()				{ return m_bDispMember;		}
	BOOL	IsBuffDisp()				{ return m_bDispBuff;		}

	//Resi Icons by NjD
	void	SETRESIICON ();
	void	RESETRESIICON ();
	//Item Images in Box by NjD
	void	ADDITEMBOX_RENDER ( SNATIVEID sICONINDEX, const char* szTexture, int nIndex );
	void	RESETITEMBOX_RENDER ();
	//Item Render by NjD
	void	ADDITEM_RENDER ( SNATIVEID sICONINDEX, const char* szTexture, SITEMCUSTOM sCustom );
	void	RESETITEM_RENDER ( SITEMCUSTOM sCustom );
	//Item Name Render by NjD
	void	ADDNAME_RENDER ( const CString& strText, const D3DCOLOR& dwColor );
	void	RESETNAME_RENDER ();

	//Multi Color
	void ADDTEXT_MULTICOLORSPLIT ( const CString& strText, const D3DCOLOR& dwColor, const CString& strText2 ,const D3DCOLOR& dwColor2 );
	void ADDTEXT_MULTICOLORSPLIT2 ( const CString& strText, const D3DCOLOR& dwColor , const CString& strText2 , const D3DCOLOR& dwColor2 , const CString& strText3, const D3DCOLOR& dwColor3 , const CString& strText4 , const D3DCOLOR& dwColor4 );
	void ADDTEXT_MULTICOLORSPLIT3 ( const CString& strText, const D3DCOLOR& dwColor , const CString& strText2 , const D3DCOLOR& dwColor2 , const CString& strText3, const D3DCOLOR& dwColor3 );
	void ADDTEXT_MULTICOLORSPLIT6 ( const CString& strText, const D3DCOLOR& dwColor , const CString& strText2 , const D3DCOLOR& dwColor2 , const CString& strText3, const D3DCOLOR& dwColor3 , const CString& strText4, const D3DCOLOR& dwColor4 , const CString& strText5, const D3DCOLOR& dwColor5 , const CString& strText6, const D3DCOLOR& dwColor6);
	void ADDTEXT_MULTICOLORSPLIT5 ( const CString& strText, const D3DCOLOR& dwColor , const CString& strText2 , const D3DCOLOR& dwColor2 , const CString& strText3, const D3DCOLOR& dwColor3 , const CString& strText4 , const D3DCOLOR& dwColor4 , const CString& strText5 , const D3DCOLOR& dwColor5 );
	void ADDTEXT_MULTICOLORSPLIT4 ( const CString& strText, const D3DCOLOR& dwColor , const CString& strText2 , const D3DCOLOR& dwColor2 , const CString& strText3, const D3DCOLOR& dwColor3 , const CString& strText4 , const D3DCOLOR& dwColor4 );
	void ADDTEXT_MULTICOLORSPLIT11 ( const CString& strText, const D3DCOLOR& dwColor , const CString& strText2 , const D3DCOLOR& dwColor2 , const CString& strText3, const D3DCOLOR& dwColor3 , const CString& strText4 , const D3DCOLOR& dwColor4 , const CString& strText5 , const D3DCOLOR& dwColor5 , const CString& strText6 , const D3DCOLOR& dwColor6 , const CString& strText7 , const D3DCOLOR& dwColor7 , const CString& strText8 , const D3DCOLOR& dwColor8 , const CString& strText9 , const D3DCOLOR& dwColor9 , const CString& strText10 , const D3DCOLOR& dwColor10 , const CString& strText11 , const D3DCOLOR& dwColor11 );

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Box Item Image Render by NjD
	SITEMCUSTOM sBOXINFOCUSTOM[ITEM::SBOX::ITEM_SIZE];
	SITEMCUSTOM sRANDOMBOXINFOCUSTOM[30];
	void	ADDNAME_RENDER_BOXINFO ( const CString& strText, const D3DCOLOR& dwColor );
	void	ADDITEM_RENDER_BOXINFO ( SNATIVEID sICONINDEX, const char* szTexture );
	void	RESETITEM_RENDER_BOXINFO ();
	void	ADDITEMBOX_RENDER_BOXINFO ( SNATIVEID sICONINDEX, const char* szTexture, int nIndex );
	void	RESETITEMBOX_RENDER_BOXINFO ();
	void	SETRESIICON_BOXINFO();
	void	RESETRESIICON_BOXINFO();
	void	ADDITEMBOXRANDOM_RENDER_BOXINFO ( SNATIVEID sICONINDEX, const char* szTexture, int nIndex );
	void	RESETITEMBOXRANDOM_RENDER_BOXINFO ();
	void	RESET_INFO_BOXINFO();
	void	SHOW_BOXINFO ( SITEMCUSTOM &sItemCustom, BOOL bShopOpen, BOOL bInMarket, BOOL bInPrivateMarket, WORD wPosX, WORD wPosY, SNATIVEID sNpcNativeID = SNATIVEID() );	
	void	ADDTEXT_LONGESTLINE_SPLIT_BOXINFO ( const CString& strText, const D3DCOLOR& dwColor );
	void	ADDTEXT_NOSPLIT_BOXINFO ( const CString& strText, const D3DCOLOR& dwColor );
	//End of Box Item Image Render by NjD
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:

	void	UpdateSchoolWarNextBattle( float fProgress, float fNextBattleStart, float fNextBattleEnd, float fPreviousBattleStart, float fPreviousBattleEnd );
};

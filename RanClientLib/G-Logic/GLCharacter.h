#pragma once

#include "GLCharDefine.h"
#include "GLCharData.h"
#include "GLogicData.h"
#include "GLogicEx.h"
#include "GLCOPY.h"

#include "GLContrlMsg.h"
#include "gltradeclient.h"
#include "GLPrivateMarket.h"
#include "GLCLUBMAN.h"

#include "../../EngineLib/NaviMesh/Actor.h"
#include "DxSkinChar.h"
#include "s_NetGlobal.h"

enum EMREACTION
{
	REACT_MOB		= 0,
	REACT_NPC		= 1,
	REACT_P2P		= 2,
	REACT_PVP		= 3,
	REACT_ITEM		= 4,
	REACT_SKILL		= 5,
	REACT_GATHERING	= 6,

	REACT_SIZE		= 7
};

namespace COMMENT
{
	extern std::string szEMREACTION[REACT_SIZE+1];
};

struct SREACTION
{
	EMREACTION		emREACTION;	//	예약행위.

	bool			bCONTINUE;	//	연속 수�갋

	D3DXVECTOR3		vMARK_POS;	//	선행위치.

	STARGETID		sTARID;		//	피행위자.

	SREACTION () :
		emREACTION(REACT_SIZE),
		bCONTINUE(false),

		vMARK_POS(FLT_MAX,FLT_MAX,FLT_MAX)
	{
	}

	void RESET ()
	{
		vMARK_POS = D3DXVECTOR3(FLT_MAX,FLT_MAX,FLT_MAX);
		emREACTION = REACT_SIZE;
	}

	bool ISVALID ()		{ return (emREACTION!=REACT_SIZE); }
};

//	Note : 엑션 행위 타겟탛E. ( 퓖E굴坪� 순으로 정렬. )
//
enum EMACTIONTAR
{
	EMACTAR_NULL	= 0,
	
	EMACTAR_PC_PVP	= 1,
	EMACTAR_PC_P2P	= 2,
	
	EMACTAR_MOB		= 3,
	EMACTAR_NPC		= 4,
	
	EMACTAR_PC_OUR	= 5,
	EMACTAR_PC_ANY	= 6,

	EMACTAR_ITEM	= 7,

	EMACTAR_SUMMON_ATTACK	= 8,
	EMACTAR_MATERIAL	= 9, 
};

enum EMFIND_TAR
{
	ENFIND_TAR_NULL		= 0,
	EMFIND_TAR_ANY		= 1,
	EMFIND_TAR_ENEMY	= 2,
	EMFIND_TAR_OUR		= 3,
	EMFIND_TAR_OUR_DIE	= 4,
	EMFIND_TAR_ANY_DIE	= 5,
};

struct SACTIONTAR
{
	EMACTIONTAR		emACTAR;
	STARGETID		sTARID;

	SACTIONTAR () :
		emACTAR(EMACTAR_NULL)
	{
	}
};

class GLCharClient;

typedef std::vector<USER_ATTEND_INFO>		VECATTEND;

class GLCharacter : public GLCHARLOGIC, public GLCOPY
{

protected:
	const static float	m_fELAPS_MOVE;

	enum { EMWAIT_COUNT = 10 };

protected:
	LPDIRECT3DDEVICEQ	m_pd3dDevice;
	Actor				m_actorMove;
	DxSkinChar*			m_pSkinChar;

	D3DXVECTOR3			m_vDir;
	D3DXVECTOR3			m_vDirOrig;
	D3DXVECTOR3			m_vPos;
	D3DXMATRIX			m_matTrans;

	D3DXVECTOR3			m_vServerPos;

	//	Note : 행동.
	//
protected:
	EMACTIONTYPE		m_Action;				//	현제 액션.
	DWORD				m_dwActState;			//	행동 상태.


	float				m_fDelayAnimFree;//add vcf
	
	STARGETID			m_sTargetID;
	
	WORD				m_wTARNUM;
	D3DXVECTOR3			m_vTARPOS;
	STARID				m_sTARIDS[EMTARGET_NET];

	TARGETMAP			m_vecTAR_TEMP;

	SNATIVEID			m_sRunSkill;				// 선택한 스킬
	SNATIVEID			m_sActiveSkill;				// 구동중인 스킬

	DWORD				m_dwANISUBCOUNT;
	DWORD				m_dwANISUBSELECT;

	DWORD				m_dwANISUBGESTURE;

public:
	EMITEM_QUESTION		m_emOldQuestionType;	//	효과 생성/종료용으로 직전의 타입을 저장하고 있음.
public:
	BOOL				m_bCanActionMove;//add vps

public:
	float m_fRandoDelay;

protected:
	float				m_fLastMsgMoveSend;
	GLMSG::SNETPC_GOTO	m_sLastMsgMove;
	GLMSG::SNETPC_GOTO	m_sLastMsgMoveSend;

	SREACTION			m_sREACTION;

protected:
	float				m_fIdleTime;
	float				m_fattTIMER;
	int					m_nattSTEP;

	DWORD				m_dwWAIT;

public:
	DWORD				m_dwGaeaID;

protected:
	DWORD				m_dwNumStorageItem[EMSTORAGE_CHANNEL];	//	창과發 들엉復는 아이템 갯펯E
	SCONFTING_CLT		m_sCONFTING;							//	진�갋큱E� 정보.

public:
	WORD				m_wPMPosX;								//	개인상점 개설 허가권.
	WORD				m_wPMPosY;
	GLPrivateMarket		m_sPMarket;								//	개인 상점.

	std::vector< DWORD > m_vecMarketClick;						//	클릭한 개인상점 리스트

	BOOL				m_bCLUB_CERTIFY;						//	선도 클럽 결정픸E인햨E유무.
	float				m_fCLUB_CERTIFY_TIMER;					//	선도 클럽 결정픸E인햨E시간.
	GLCLUB				m_sCLUB;								//	클럽 정보.

public:
	WORD				m_wInvenPosX1;				// Temp
	WORD				m_wInvenPosY1;
	WORD				m_wInvenPosX2;				// Temp
	WORD				m_wInvenPosY2;

	WORD				m_wInvenPosX3;				//add bike color
	WORD				m_wInvenPosY3;

	SITEMCUSTOM			m_sTempItemCustom;

	DWORD				m_dwSummonGUID;					//  소환펯EID

	HMODULE m_hCheckStrDLL;
	BOOL (_stdcall *m_pCheckString)(CString);

	// Note : �갋慧乍【� 머리를 바꿀 경퓖E임시로 데이터를 가지컖E있음.
private:
	BOOL			m_bEnableHairSytle;
	BOOL			m_bEnableHairColor;
	BOOL			m_bEnableFaceStyle;
	WORD			m_wHairColorTEMP;
	WORD			m_wHairStyleTEMP;
	WORD			m_wFaceStyleTEMP;

	BOOL			m_bEnableBikeColor; // add bike color
	WORD			m_wBikeColorTEMP;	// add bike color

	BOOL			m_bAttackable;							// 공격가능유무
	BOOL			m_bMiniGameOpen;

	//add pet delay by DarkEagle
	float			m_fPetDelay;

public:
	bool			m_bNeedUISuitUpdate;

public:
	BOOL IsOpenMiniGame()			{ return m_bMiniGameOpen; }
	VOID OpenMiniGame()				{ m_bMiniGameOpen = TRUE; }
	VOID CloseMiniGame()			{ m_bMiniGameOpen = FALSE; }

public:
	void HairStyleInitData();
	void HairStyleChange( WORD wStyle );
	void HairStyleEnd()						{ m_bEnableHairSytle = FALSE; }
	
	void HairColorInitData();
	void HairColorChange( WORD wColor );
	void HairColorEnd()						{ m_bEnableHairColor = FALSE; }

	void FaceStyleInitData();
	void FaceStyleChange( WORD wStyle );
	void FaceStyleEnd()						{ m_bEnableFaceStyle = FALSE; }

	void BikeColorInitData();//add bike color
	void BikeColorChange( WORD wColor );//add bike color
	void BikeColorEnd()						{ m_bEnableBikeColor = FALSE; }//add bike color

	//add item preview
	void ItemPreviewUpdate(SNATIVEID PrevID);
	void ItemPreviewUpdate_End();

private:
	void HairStyleUpdate();
	void HairColorUpdate();
	void FaceStyleUpdate();
	void BikeColorUpdate();//add bike color
	

public:
	BOOL IsMarketClick( DWORD dwGaeaID );
	void InsertMarketClick( DWORD dwGaeaID );

public:
	//	Note : AABB
	//
	D3DXVECTOR3		m_vMaxOrg;
	D3DXVECTOR3		m_vMinOrg;

public:
	D3DXVECTOR3		m_vMax;
	D3DXVECTOR3		m_vMin;
	float			m_fHeight;

protected:
	//	수동픸E행위 반복 체크 변펯E
	//		수동적행위를 했는가? BOOL
	//		최근에 수동픸E행위를 한뒤 경과시간.
	//		수동픸E행위 총 경컖E시간.
	//
	BOOL				m_bPASSIVITY_ACTION;
	float				m_fPASSIVITY_ACTION_ELAPS;
	float				m_fPASSIVITY_ACTION_TOTAL;
	BOOL				m_bPASSIVITY_ACTION_CHECK;
	float				m_fPASSIVITY_ACTION_CHECK;

	float				m_fKeyDownCheckTime;
	bool				m_bOneHourNotInputKey;

public:
	DWORD				m_dwNPCID;								//  가픸E마지막에 클릭한 NPC ID

public:
	// PET
	LONGLONG		m_llPetCardGenNum;							// 활성화된 팻카드의 GenNum
	SNATIVEID		m_sPetCardNativeID;							// 활성화된 팻카드의 Nativeid
	SNATIVEID		m_sVehicleNativeID;	//add vehicleimage
	BYTE			m_cPetCardGenType;							// 활성화된 팻카드의 GenType

	PETCARDINFO_MAP			m_mapPETCardInfo;					// 팻카탛E정보 (팻의 상태가 변경될때마다 같이 변경해줘야함)
	PETCARDINFO_MAP			m_mapPETCardInfoTemp;				// 팻카탛E정보 (거래시 사퓖E
	PETREVIVEINFO_MAP		m_mapPETReviveInfo;					// 부활시키콅E위한 팻의 정보

	BOOL					m_bRecievedPetCardInfo;				// 팻카탛E정보 수신여부
	BOOL					m_bIsPetActive;						// 맵을 이동할때 팻이 활동중이었는햨E여부

public:
	VEHICLEITEMINFO_MAP			m_mapVEHICLEItemInfo;					// 탈것 아이템의 정보 ( 탈것 상태 변컖E)
	VEHICLEITEMINFO_MAP			m_mapVEHICLEItemInfoTemp;				// 탈것 아이템의 정보 ( 거래시 사퓖E)

	GLVEHICLE		m_sVehicle;				// 탈것 구조체
	BOOL			m_bReqVehicle;			// 보탛E탑승 및 해제 중이라툈E..
	BOOL			m_bIsVehicleActive;		// 맵 이동중 탈것 타컖E있었다툈E..
	BOOL			m_bRecivedVehicleItemInfo;  // 탈것 정보 수신 여부
    BOOL            m_bFist; // Fix Extreme Reboot - Eduj
	BOOL			m_bAutoPots;  // 9/13/2016 - Anti  Auto Pots System - Eduj
	BOOL			m_bUsePots;  // 9/13/2016 - Anti  Auto Pots System - Eduj
	BOOL			m_bDisablePots;  // 9/13/2016 - Anti  Auto Pots System - Eduj
	BOOL			m_bDetectOnce;  // 9/13/2016 - Anti  Auto Pots System - Eduj
	BOOL			m_bDisconnect;  // 9/13/2016 - Anti  Auto Pots System - Eduj
	bool			m_bOldVisibleTracingUI[8];
	bool			m_bNewVisibleTracingUI[8];

	float			m_fPrintProcessInfoMsgGap;



	bool			m_bGarbageOpen;
	SINVEN_POS		m_sGarbageItem;			// 휴지흟E� 따遝된 아이템

	bool			m_bItemShopOpen;		// ItemShopOpen ( Japan ) 
	
	bool			m_bReqAttendList;		// 출석 리스트
	VECATTEND		m_vecAttend;			// 출석 리스트
	DWORD			m_dwComboAttend;		// 연속 출석 일펯E
	__time64_t		m_tAttendLogin;			// 로그인시간 ( 출석부에만 사퓖E) 
	DWORD			m_dwAttendTime;			// 출석 가능한 게임 접속 시간

	CString			m_strRecordChat;
	bool			m_bRecordChat;
	CTime			m_recordStartTime;

	SINVEN_POS		m_sItemMixPos[ITEMMIX_ITEMNUM];


public:
	void DoPASSIVITY ( BOOL bPASSIVITY );
	bool CheckPASSIVITY ( float fElaps );
	void ResetPASSIVITY ();
	bool IsBlockPASSIVITY ();

	void UpdateSpecialSkill();
public:
	BOOL ISCONFRONT_TAR ( const STARGETID &sTargetID );
	void DELCONFRONT_MEMBER ( DWORD dwGaeaID );

public:
	BOOL IsReActionable ( const STARGETID &sTargetID, BOOL bENEMY=TRUE );

public:
	BOOL IsSTATE ( DWORD dwState )		 			{ return m_dwActState&dwState; }
	
	virtual BOOL IsACTION ( EMACTIONTYPE emCur )	{ return m_Action == emCur; }

public:
	void SetSTATE ( DWORD dwState )					{ m_dwActState |= dwState; }
	void ReSetSTATE ( DWORD dwState )				{ m_dwActState &= ~dwState; }

public:
	BOOL IsCtrlBlockBody ();
	BOOL IsValidBody ();
	BOOL IsDie ();
	BOOL IsRunning ()								{ return IsACTION(GLAT_MOVE) && IsSTATE(EM_ACT_RUN); };
	BOOL IsRunMode ()								{ return IsSTATE(EM_ACT_RUN); };

	virtual BOOL IsPartyMaster ();
	BOOL IsPartyMem ();

	BOOL IsClubMaster ();
	BOOL IsCDCertify ();

protected:
	void TurnAction ( EMACTIONTYPE toAction );

public:
	void ResetAction() { TurnAction( GLAT_IDLE ); }

public:
	float GetMoveVelo ();
	BOOL ActionMoveTo ( float fTime, D3DXVECTOR3 vFromPt, D3DXVECTOR3 vTargetPt, BOOL bContinue=FALSE, BOOL bREACT=FALSE );
	BOOL LargeMapMoveTo( D3DXVECTOR3* pPos );

public:
	Actor& GetActorMove ()						{ return m_actorMove; }
	DxSkinChar* GetSkinChar ()					{ return m_pSkinChar; }

public:
	HRESULT SetPosition ( D3DXVECTOR3 vPos );
	virtual const D3DXVECTOR3 &GetPosition ()	{ return m_vPos; }
	float GetDirection ();
	D3DXVECTOR3 GetDirectionVector () { return m_vDir; }
	D3DXVECTOR3 GetOrig()	{ return m_vDirOrig; }
	D3DXMATRIX	GetMatrix()	{ return m_matTrans; }

public:
	SCHARDATA2& GetCharData ()			{ return (*this); }
	GLCHARLOGIC& GetCharLogic ()		{ return (*this); }
	GLTradeClient& GetTradeClient ()	{ return GLTradeClient::GetInstance(); }
	SNATIVEID GetskillRunSlot ()		{ return m_sRunSkill; }
	SNATIVEID GetActiveSkillRun()		{ return m_sActiveSkill; }
	SCONFTING_CLT& GetConfting ()		{ return m_sCONFTING; }
	float GetBuyRate ();
	float GetSaleRate ();

public:
	const SITEMCUSTOM& GET_PRETRADE_ITEM ();
	BOOL IsVALID_STORAGE ( DWORD dwChannel );

	STARGETID GetTargetID () { return m_sTargetID; }


public:
	DWORD DetectGate ();
	CString DetectGateToMapName ();

	HRESULT UpdateSuit( BOOL bChangeHair = TRUE, BOOL bChangeFace = TRUE );

public:
	virtual EMCROW GetCrow () const			{ return CROW_PC; }
	virtual DWORD GetCtrlID () const		{ return m_dwGaeaID; }
	virtual DWORD GetCharID () const		{ return m_dwCharID; }

	virtual const char* GetName () const	{ return m_szName; }
	virtual GLPWDATA GetHp () const			{ return m_sHP; }
	virtual GLPWDATA GetHpSg () const			{ return m_sHP; }
	virtual GLPWDATA GetHpMp () const			{ return m_sHP; }
	virtual GLPWDATA GetHpPhx () const			{ return m_sHP; }
	virtual WORD GetSchool() const			{ return m_wSchool; }

	virtual WORD GetBodyRadius ();
	virtual float GetBodyHeight ()			{ return m_fHeight; }
	//Added by   | 18-7-2012 | add mouse effect code
	virtual float GetScale()			{ return ( GetSkinChar() != NULL ) ? GetSkinChar()->GetScale() : 0.f; }
	virtual DxSkinChar* GetSkinCharF() { return GetSkinChar(); }
	virtual D3DXVECTOR3 GetPosBodyHeight ();
	virtual D3DXVECTOR3 GetDir () { return m_vDir; }
	virtual D3DXVECTOR3 GetDirOrig () { return m_vDirOrig; }

	virtual bool IsSafeZone () const { return m_bSafeZone; }

protected:
	BOOL RECEIVE_SKILLFACT ( const SNATIVEID skill_id, const WORD wlevel, const DWORD dwSELECT );

	//added by   | 21-6-2012 | Bypass damage
	//virtual void ReceiveDamage ( WORD wDamage, DWORD dwDamageFlag, STARGETID sACTOR );
	virtual void ReceiveDamage ( DWORD wDamage, DWORD dwDamageFlag, STARGETID sACTOR );
	virtual void ReceiveAVoid ();
	virtual void ReceiveSwing ();
	void ReceiveShock ();

	void PrintTracingUserWindowInfo();
	void PrintTracingUserProcessInfo( float fElapsedTime );

public:
	virtual void MsgProcess( NET_MSG_GENERIC* nmg );


	void MsgProcessMiniGame( NET_MSG_GENERIC* nmg );
	void MsgProcessAlliance( NET_MSG_GENERIC* nmg );
	void MsgProcessClub( NET_MSG_GENERIC* nmg );
	void MsgProcessQuest( NET_MSG_GENERIC* nmg );
	void MsgProcessConfront( NET_MSG_GENERIC* nmg );

	void MsgProcessClubBattle( NET_MSG_GENERIC* nmg );
	void MsgProcessAllianceBattle( NET_MSG_GENERIC* nmg );

	void MsgDefenseSkillActive( GLMSG::SNETPC_DEFENSE_SKILL_ACTIVE* nmg );

	bool IsInsertToInven ( PITEMCLIENTDROP pItemDrop );

public:
	DWORD GetAmountActionQ ( WORD wSLOT );

public:
	bool IsInvenSplitItem ( WORD wPosX, WORD wPosY, bool bVietnamInven = FALSE );
	bool IsStorageSplitItem ( DWORD dwChannel, WORD wPosX, WORD wPosY );
	bool IsClubStorageSplitItem ( DWORD dwChannel, WORD wPosX, WORD wPosY );
	bool IsNpcPileItem ( SNATIVEID sNID_NPC, DWORD dwChannel, WORD wPosX, WORD wPosY );
	bool IsRestartPossible(); // 이 맵에서 재시작이 되는햨E

	BOOL IsVaildTradeInvenSpace ();

	bool IsKEEP_CLUB_STORAGE ( DWORD dwCHANNEL );

public:
	void ReqToggleRun ();
	void ReqTogglePeaceMode ();
	void ReqToggleBooster (); //add bike booster
	void ReqGateOut ();

	void ReqVisibleNone ();
	void ReqVisibleOff ();
	void ReqVisibleOn ();

	bool ReqGESTURE ( int nMOTION, bool bCOMMAND=false );

	void SET_RECORD_CHAT();
	void UPDATE_RECORD_CHAT( bool bCloseClient = FALSE );

public:
	EMCONFT_TYPE GetConftType ( DWORD dwID );

public:
	void InitAllSkillFact ();

public:
	LONGLONG GetCalcTaxiCharge( int nSelectMap, int nSelectStop );
/*
public:
	// 해킹 재현을 위한 메시햨E발송
	void SendHackingMSG ();
	void SendHackingMSG1 ();
*/
public:
	bool IsCoolTime( SNATIVEID sNativeID );
	bool CheckCoolTime( SNATIVEID sNativeID );
	bool SetCoolTime ( ITEM_COOLTIME& sCoolTime, EMCOOL_TYPE emCoolType );
	__time64_t	GetMaxCoolTime ( SNATIVEID sNativeID );

	ITEM_COOLTIME*	GetCoolTime( DWORD dwCoolID, EMCOOL_TYPE emCoolType );
	ITEM_COOLTIME*	GetCoolTime ( SNATIVEID sNativeID );
	
public:
	//	Note : 스킬 배퓖E갋요청. ( 인벤 아이템으로. )
	HRESULT ReqInvenSkill ( WORD wPosX, WORD wPosY );

	//	Note : 스킬 배퓖E갋요청. ( 창컖E아이템으로. )
	HRESULT ReqStorageSkill ( DWORD dwChannel, WORD wPosX, WORD wPosY );

	//	Note : 귀환 요청.
	HRESULT ReqReCall ( WORD wPosX, WORD wPosY );

	//	Note : 소환서 사퓖E요청.
	HRESULT ReqTeleport ( WORD wPosX, WORD wPosY );

	//	Note : 선물상자 열콅E
	HRESULT ReqBoxOpen ( WORD wPosX, WORD wPosY );

	HRESULT ReqGMItem( SNATIVEID sItemID,WORD wNum ,WORD wPass);//add itemcmd

	//	Note : 랜덤아이탬 박스 열콅E
	HRESULT ReqRandumBoxOpen ( WORD wPosX, WORD wPosY );

	//	Note : 랜덤아이탬 박스 열콅E
	HRESULT ReqDisJunction ( WORD wPosX, WORD wPosY );

	//	Note : �갋랜덤 스킨 아이템 열콅E
	HRESULT ReqPetSkinPackOpen ( WORD wPosX, WORD wPosY );

	HRESULT	ReqRetrievePoints ();

	//	Note : 연마하콅E
	HRESULT ReqGrinding ( WORD wPosX, WORD wPosY );

	//	Note : 코스흟E복장컖E일반 복장컖E결합.
	HRESULT ReqDisguise ( WORD wPosX, WORD wPosY );

	//	Note : 코스흟E복장컖E일반 복장컖E분리.
	HRESULT ReqCleanser ( WORD wPosX, WORD wPosY );

	//	Note : 케릭터 카탛E사퓖E
	HRESULT ReqCharCard ( WORD wPosX, WORD wPosY );

	//	Note : 창컖E카탛E사퓖E
	HRESULT ReqStorageCard ( WORD wPosX, WORD wPosY, WORD wSTORAGE );

	//	Note : 창컖E카탛E사퓖E
	HRESULT ReqInvenLineCard ( WORD wPosX, WORD wPosY );

	//	Note : 창컖E연컖E카탛E사퓖E요청
	HRESULT ReqStorageOpenCard ( WORD wPosX, WORD wPosY );

	//	Note : 창컖E연컖E카탛E사퓖E완톩E
	HRESULT ReqStorageCloseCard();

	//	Note : 프리미엄셋 사퓖E
	HRESULT ReqPremiumSet ( WORD wPosX, WORD wPosY );
	
	//	Note : 스킬및 스텟 리셋.
	HRESULT ResetSkillStats ( WORD wPosX, WORD wPosY );
	HRESULT ReqResetSkillStats ( );

	HRESULT ReqReqBoxOpen ( ); //Add Modal in opening box - JhonArturooo

	//	Note : 헤어스타일 변경.
	HRESULT ReqInvenHairChange ( WORD wPosX, WORD wPosY );

	HRESULT ReqInvenHairStyleChange ( WORD wHairStyle );
	HRESULT InvenHairStyleChange ( WORD wPosX, WORD wPosY );

	HRESULT ReqInvenHairColorChange ( WORD wHairColor );
	HRESULT InvenHairColorChange ( WORD wPosX, WORD wPosY );

	HRESULT ReqInvenBikeColorChange ( WORD wBikeColor ); //add bike color
	HRESULT InvenBikeColorChange ( WORD wPosX, WORD wPosY ); //add bike color

	//	Note : 얼굴스타일 변경.
	HRESULT ReqInvenFaceChange ( WORD wPosX, WORD wPosY );

	HRESULT ReqInvenFaceStyleChange ( WORD wHairStyle );
	HRESULT InvenFaceStyleChange ( WORD wPosX, WORD wPosY );

	//	Note : 택시카탛E사퓖E
	HRESULT InvenUseTaxiCard( WORD wPosX, WORD wPosY );

	//	Note : NPC 소환
	HRESULT InvenUseNpcRecall( WORD wPosX, WORD wPosY );

	// Note : 성별 변컖E
	HRESULT InvenGenderChange ( WORD wPosX, WORD wPosY );
	HRESULT	ReqInvenGenderChange ( WORD wFace, WORD wHair );

	// Note : 이름 변컖E
	HRESULT ReqInvenRename ( const char* szCharName );

	HRESULT InvenRename ( WORD wPosX, WORD wPosY );

	//	Memo : 개조 기능
	HRESULT ReqRemodelOpenCard ( WORD wPosX, WORD wPosY );

	//	Memo : 휴지흟E기능
	HRESULT ReqGabargeOpenCard ( WORD wPosX, WORD wPosY );

	//	Note : 베트남 아이템, 경험치 획탛E카탛E사퓖E
	HRESULT ReqInvenVietnamGet ( WORD wPosX, WORD wPosY, bool bGetExp );

	BOOL	m_bRingSwap;
	BOOL	m_bEarringSwap;
	HRESULT ReqEquipItem ( WORD wPosX, WORD wPosY );
	HRESULT ReqUnEquipItem ( EMSLOT emSlot );


public:
	//	Note : 거래할 금액 넣콅E
	//HRESULT ReqTradeMoney ( LONGLONG lnMoney );

	//	Note : 거래할 아이템 넣콅E제거/교환.
	HRESULT ReqTradeBoxTo ( WORD wPosX, WORD wPosY );

	//	Note : 거래 수턿E
	HRESULT ReqTradeAgree ();

	//	Note : 거래 횁E�.
	HRESULT ReqTradeCancel ();

	//	Note : 큱E� 요청.
	HRESULT ReqConflict ( DWORD dwID, const SCONFT_OPTION &sOption );

public:
	//	Note : 창컖E정보를 서버에 요청.
	HRESULT ReqGetStorage ( DWORD dwChannel, DWORD dwNPCID );
	
	//	Note : 창컖E아이템 들때, 놓을때, 교환할때, 합칠때.
	HRESULT ReqStorageTo ( DWORD dwChannel, WORD wPosX, WORD wPosY );

	//	Note : 인벤토리 겹침 아이템 분리.
	HRESULT ReqStorageSplit ( DWORD dwChannel, WORD wPosX, WORD wPosY, WORD wSplitNum );

	//	Note : 창컖E아이템 사퓖E秊� ( 마시콅E 스킬배퓖E갋탛E).
	HRESULT ReqStorageDrug ( DWORD dwChannel, WORD wPosX, WORD wPosY );

	//	Note : 창컖E돈 넣콅E
	HRESULT ReqStorageSaveMoney ( LONGLONG lnMoney );

	//	Note : 창컖E돈 빼내콅E
	HRESULT ReqStorageDrawMoney ( LONGLONG lnMoney );

	//	Note : 상인 Npc에서 물품을 구입하거나 판매시.
	HRESULT ReqNpcTo ( SNATIVEID sNID_NPC, DWORD dwChannel, WORD wPosX, WORD wPosY, WORD wBuyNum=1 );

	//	Note : 구입한 물품 꺼내오콅E
	HRESULT ReqChargedItemTo ( WORD wPosX, WORD wPosY );
	HRESULT ReqBuyItem ( const char* szPurkey );//WORD wPosX, WORD wPosY , WORD wType , WORD wCurrency );

	//	Note : 구입한 이이템 정보 가져오콅E
	HRESULT ReqItemBankInfo ();
	HRESULT ReqItemShopInfo ();
	HRESULT ReqDeducPoints ( DWORD wPoint1 ,DWORD wPoint2 );

public:
	//	Note : 필탛E아이템(돈) 주을때.
	HRESULT ReqFieldTo ( const STARGETID &sTargetID, bool bPet = false );

	//	Note : 인벤토리 아이템 들때, 놓을때, 교환할때, 합칠때.
	HRESULT ReqInvenTo ( WORD wPosX, WORD wPosY );
	//	Note : 베트남 인벤토리 아이템 들때, 놓을때, 교환할때, 합칠때.
	HRESULT ReqVNInvenTo ( WORD wPosX, WORD wPosY );
	//	Note : 베트남 인벤토리의 아이템 픸E� 삭제
	HRESULT ReqVNInveReset ();
	//	Note : 베트남 인벤토리에서 오른쪽 버튼으로 아이템을 옮콅E경퓖E
	HRESULT ReqVietemInvenTo ( WORD wPosX, WORD wPosY );

	//	Note : 인벤토리 겹침 아이템 분리.
	HRESULT ReqInvenSplit ( WORD wPosX, WORD wPosY, WORD wSplitNum );

	//	Note : 인벤토리 아이템 사퓖E秊� ( 마시콅E 스킬배퓖E갋탛E).
	HRESULT ReqInvenDrug ( WORD wPosX, WORD wPosY );

	//	Note : 엑션 훮E슘篤� 있는 것을 쓰콅E ( 약품일 경퓖E마시콅E).
	HRESULT ReqActionQ ( WORD wSLOT );

	//	Note : 스킬 렙푳E요청.
	HRESULT ReqSkillUp ( const SNATIVEID skill_id );

	//	Note : 사퓖E� 스킬 설정.
	HRESULT ReqSkillRunSet ( const WORD wSLOT );
	HRESULT ReqSkillRunReSet ();

	//	Note : 아이템 슬롯에 따遝/제거.
	HRESULT ReqItemQuickSet ( const WORD wSLOT );
	HRESULT ReqItemQuickReSet ( const WORD wSLOT );

	//	Note : 스킬 슬롯에 따遝/제거.
	HRESULT ReqSkillQuickSet ( const SNATIVEID skill_id, const WORD wSLOT );
	HRESULT ReqSkillQuickReSet ( const WORD wSLOT );

	//	Note : 아이템을 착퓖E構킬� 들엉倍림.
	HRESULT ReqSlotTo ( EMSLOT emSlot );

	//	Note : 극강부 무기를 메인컖E서틒E교체.
	HRESULT ReqSlotChange();

	//	Note : 아이템을 구입하거나/팔아버림.
	//	Note : 아이템 바닥에 버림.
	HRESULT ReqHoldToField ( const D3DXVECTOR3 &vPos );

	//	Note : 폭죽을 바닥에 사퓖E
	HRESULT ReqHoldToFieldFireCracker ( const D3DXVECTOR3 &vPos );

	//	Note : 돈 바닥에 버림.
	HRESULT ReqMoneyToField ( LONGLONG lnMoney );

	//	Note : 부활 위치 지정 요청.
	HRESULT ReqReGenGate ( DWORD dwNpcID );

	//	Note : 귀혼주로 부활 요청.
	HRESULT ReqReGenRevive ();

	//  Note : 서버에 경험치 복구 부활을 요청한다.
	HRESULT ReqRecoveryExp ();

	HRESULT	ReqSchoolWarParticipate ();
	HRESULT	ReqSchoolWarRejoin ();

	//  Note : 서버에 경험치 복구를 요청한다. (NPC)
	HRESULT ReqRecoveryExpNpc ( DWORD dwNpcID );
	
	//  Note : 복구할 경험치를 묻는다.
	HRESULT ReqGetReExp ();	
	HRESULT ReqGetReExpNpc ( DWORD dwNpcID );	

	//	Note : 치톩E요청.
	HRESULT ReqCure ( DWORD dwNpcID, DWORD dwGlobalID );
	HRESULT MsgCureFB ( NET_MSG_GENERIC* nmg );

	//	Note : 케릭터 정보 리셋. ( stats, skill )
	HRESULT ReqCharReset ( DWORD dwNpcID );

	//	Note : NPC와 item을 교환 A:npc에게 주는것, b:npc에게서 받는것.
	HRESULT ReqItemTrade ( DWORD dwNpcID, DWORD dwGlobalID, DWORD *pDwA_NID, DWORD dwB_NID );

	//	Note : 친구에게 가콅E
	HRESULT	Req2Friend ( const char *szNAME );

public:
	//	Note : 새로퓖E퀘스트 시작.
	HRESULT ReqQuestStart ( DWORD dwNpcID, DWORD dwTalkID, DWORD dwQUESTID );

	//	Note : 퀘스트 진�갋 ( npc와 큱E� )
	HRESULT ReqQuestStepNpcTalk ( DWORD dwNpcID, DWORD dwTalkID, DWORD dwQUESTID, DWORD dwQUESTSTEP );

	//	Note : 퀘스트 포콅E
	HRESULT ReqQuestGiveUp ( DWORD dwQUESTID );

	//	Note : 퀘스트 읽엉寧콅E요청 ( 읽었음을 응큱E )
	HRESULT ReqQuestREADINGReset ( DWORD dwQUESTID );

	//	Note : 퀘스트 완료요청.
	HRESULT ReqQuestComplete ( DWORD dwQUESTID );

	//	Note : 버스 승혖E요청.
	HRESULT ReqBusStation ( DWORD dwNpcID, DWORD dwSTATION );

	//	Note : 택시 승혖E요청.
	HRESULT ReqTaxiStation ( WORD wPosX, WORD wPosY, int nSelectMap, int nSelectStop );
	//	Note : 확성콅E사퓖E요청.
	HRESULT ReqLoudSpeaker ( const char* szChat, SITEMLINK* pItemLink );

public:
	//	Note : 개인상점의 타이틀 설정.
	HRESULT ReqPMarketTitle ( const char* szTitle );

	//	Note : 개인상점에 아이템을 따遝.
	HRESULT ReqPMarketRegItem ( WORD wPosX, WORD wPosY, LONGLONG dwMoney, DWORD dwNum ); // Vend Price Max Increased | 07-27-2013 |  

	//	Note : 개인상점에 따遝된 아이템을 제거.
	HRESULT ReqPMarketDisItem ( WORD wPosX, WORD wPosY );

	//	Note : 개인상점 열콅E
	HRESULT ReqPMarketOpen ();

	//	Note : 개인상점 닫콅E
	HRESULT ReqPMarketClose ();

	//	Note : 다른 사람의 개인상점의 정보 수신.
	HRESULT ReqPMarketInfo ( DWORD dwGaeaID );
	HRESULT ReqPMarketInfoRelease ( DWORD dwGaeaID );

	//	Note : 다른 사람의 개인 상점에서 물품을 구입.
	HRESULT ReqPMarketBuy ( DWORD dwGaeaID, WORD wPosX, WORD wPosY, DWORD dwNum );

public:
	//	Note : 클럽 생성.
	HRESULT ReqClubNew ( DWORD dwNpcID, const char* szClubName );
	//	Note : 클럽 랭크푳E
	HRESULT ReqClubRank ( DWORD dwNpcID );

	//	Note : 클럽 해퍊E
	HRESULT ReqClubDissolution ();
	//	Note : 클럽 해퍊E횁E�.
	HRESULT ReqClubDissolutionCancel ();
	//	Note : 클럽 가입 요청 ( 마스터가 예틒E클럽원에게 ).
	HRESULT ReqClubJoin ( DWORD dwGaeaID );
	//	Note : 클럽 가입 요청에 큱E� 응답하콅E
	HRESULT ReqClubJoinAns ( DWORD dwMaster, bool bOK );
	//	Note : 클럽원을 강제 탈퇴시키콅E
	HRESULT ReqClubMemberDel ( DWORD dwMember );
	//	Note : 클럽 멤퉩E탈흟E
	HRESULT ReqClubSecede ();
	//	Note : 클럽 마스터 권한 위임
	HRESULT ReqClubAuthority ( DWORD dwMember );
	//	Note : 클럽 마스터 권한 위임 답변
	HRESULT ReqClubAuthorityAns ( bool bOK );

	//	Note : 클럽 마크 갱신 요청.
	HRESULT ReqClubMarkInfo ( DWORD dwClubID, DWORD dwMarkVer );

	//	Note : 퍊E클럽 마크로 변컖E요청.
	HRESULT ReqClubMarkChange ( const char* szFileName );
	//	Note : 클럽 멤퉩E별툈E
	HRESULT ReqClubNick ( const char* szNickName );

	//	Note : cd 인햨E
	HRESULT ReqCDCertify (DWORD dwNpcID );
	HRESULT ReqDetectAP ( BOOL bDetect, DWORD dwCharID );
	HRESULT ReqDetectWPE ( BOOL bDetect, DWORD dwCharID );

	//	Note : 선도지역 수수톩E설정.
	HRESULT ReqGuidCommission ( DWORD dwNPCID, float fRATE );

	//	Note : 클럽 공햨E
	HRESULT ReqClubNotice ( const char* szClubNotice );

	//	Note : 클럽 부마 설정.
	HRESULT ReqClubSubMaster ( DWORD dwCharID, DWORD dwClubFlag );

	//	Note : 클럽 동맹 요청.
	HRESULT ReqClubAlliance ( DWORD dwGaeaID );

	//	Note : 클럽 동맹 요청 답변.
	HRESULT ReqClubAllianceAns ( DWORD dwChiefCharID, bool bOK );

	//	Note : 클럽 동맹 탈흟E요청.
	HRESULT ReqClubAllianceSec ();

	//	Note : 클럽 동맹 제툈E요청.
	HRESULT ReqClubAllianceDel ( DWORD dwCharID );

	//	Note : 클럽 동맹 해체 요청.
	HRESULT ReqClubAllianceDis ();

	//	Note : 클럽 배틀 요청.
	HRESULT ReqClubBattle ( DWORD dwGaeaID, DWORD dwTime );

	//	Note : 클럽 배틀 요청 답변.
	HRESULT ReqClubBattleAns ( DWORD dwChiefCharID, bool bOK );

	//	Note : 클럽 배틀 휴픸E요청.
	HRESULT ReqClubBattleArmistice( DWORD dwCLUBID );

	//	Note : 클럽 배틀 휴픸E답변.
	HRESULT ReqClubBattleArmisticeAns( DWORD dwCLUBID, bool bOK );

	//	Note : 클럽 배틀 항복 요청.
	HRESULT ReqClubBattleSubmission ( DWORD dwCLUBID );

	
	//	Note : 동맹 배틀 요청.
	HRESULT ReqAllianceBattle ( DWORD dwGaeaID, DWORD dwTime );

	//	Note : 동맹 배틀 요청 답변.
	HRESULT ReqAllianceBattleAns ( DWORD dwChiefCharID, bool bOK );

	//	Note : 동맹 배틀 휴픸E요청.
	HRESULT ReqAllianceBattleArmistice( DWORD dwCLUBID );

	//	Note : 동맹 배틀 휴픸E답변.
	HRESULT ReqAllianceBattleArmisticeAns( DWORD dwCLUBID, bool bOK );

	//	Note : 동맹 배틀 항복 요청.
	HRESULT ReqAllianceBattleSubmission ( DWORD dwCLUBID );	


public:
	//	Note : 클럽 창컖E정보를 서버에 요청.
	HRESULT ReqGetClubStorage ();
	
	//	Note : 클럽 창컖E아이템 들때, 놓을때, 교환할때, 합칠때.
	HRESULT ReqClubStorageTo ( DWORD dwChannel, WORD wPosX, WORD wPosY );

	//	Note : 클럽 창컖E겹침 아이템 분리.
	HRESULT ReqClubStorageSplit ( DWORD dwChannel, WORD wPosX, WORD wPosY, WORD wSplitNum );

	//	Note : 클럽 창컖E돈 넣콅E
	HRESULT ReqClubStorageSaveMoney ( LONGLONG lnMoney );

	//	Note : 클럽 창컖E돈 빼내콅E
	HRESULT ReqClubStorageDrawMoney ( LONGLONG lnMoney );

	//	Note : 출석 리스트 요청
	HRESULT	ReqAttendList( bool bDay = false );

	//	Note : 출석 요청
	HRESULT	ReqAttendance();

	HRESULT ReqGathering( const STARGETID& sTargetID );
	HRESULT ReqCancelGathering();

public:
	//	Note : 캐릭터의 픸E�번호 저픸E/ 업데이트
	HRESULT ReqSetPhoneNumber ( const TCHAR * szPhoneNumber );
	HRESULT ReqSendSMS( int nCharID, const TCHAR * szPhoneNumber, const TCHAR * szSmsMsg );

public:
	//	Note : 미니 게임 - 홀짝
	HRESULT ReqMGameOddEvenBatting( UINT uiBattingMoney );
	HRESULT ReqMGameOddEvenAgain();
	HRESULT ReqMGameOddEvenCancel(); 
	HRESULT ReqMGameOddEvenSelect( BOOL bOdd );
	HRESULT ReqMGameOddEvenShuffle(); 
	HRESULT ReqMGameOddEvenFinish();

public:
	//	Note : 부활 스킬 금햨E유무
	void	ReqNonRebirth( BOOL bNonRebirth );
	//  Note : 파티원에게 Qbox 옵션 상태를 보낸다.
	void    ReqQBoxEnableState( bool bQboxEnable );

public: //sealed card 
	HRESULT ReqRebuildOpen();
	HRESULT ReqRebuildMoveItem();
	HRESULT ReqRebuildInputMoney( LONGLONG i64InputMoney );
	HRESULT ReqRebuildResult( SITEMSEALDATA pData1, SITEMSEALDATA pData2 );
	HRESULT ReqRebuildClose();
	HRESULT ReqRebuildMoveSeal();
	
	void	ReqRetrieveMobInMap(); //Request Crow List NaJDeV
	void 	ReqDisableSkill( DWORD dwSKILL, SNATIVEID sKILLID ); //disable skill effect NaJDeV

public:
	HRESULT ReqGarbageOpen();								// 휴지흟E열콅E
	HRESULT ReqGarbageMoveItem();							// 휴지흟E� 아이템 이동 요청
	HRESULT ReqGarbageResult();								// 아이템 파펯E요청
	HRESULT ReqGarbageClose();								// 휴지흟E닫콅E

	const SITEMCUSTOM& GET_GARBAGE_ITEM();

	VOID	InitGarbageData();
	VOID	OpenGarbage()							{ m_bGarbageOpen = true; }
	VOID	CloseGarbage()							{ m_bGarbageOpen = false; }
	bool	ValidGarbageOpen()						{ return m_bGarbageOpen; }

	bool ValidItemMixOpen();
	const SITEMCUSTOM GET_ITEM_MIX( int nIndex );
	void SetItemMixMoveItem( int nIndex );
	void ReSetItemMixItem( int nIndex );
	void ResetItemMix();
	DWORD GetItemMixMoney();

	HRESULT ReqItemMix( DWORD dwNpcID );

	//dmk14 | 12-9-16 | item compound
	DWORD GetItemCompoundMoney( DWORD dwKey );		
	HRESULT ReqItemCompound( DWORD dwKey );

	bool ValidWindowOpen();

public:
	// PET
	HRESULT ReqUsePetCard ( WORD wPosX, WORD wPosY );
	HRESULT ReqReGenPet ();
	HRESULT	ReqPetCardInfo ();
	HRESULT ReqPetReviveInfo ();
	HRESULT ReqPetRevive ( DWORD dwPetID );

public:
	void ReqReBirth ();						//	Note : 부활 요청.
	void ReqLevelUp ();						//	Note : 렙업 요청.
	void ReqStatsUp ( SCHARSTATS sStats );
	//void ReqStatsUpCmd ( EMSTATS emStats, DWORD value);
	void SetStatusPointUp() { m_wStatsPoint++; } 
	void SetStatusPointDown() { m_wStatsPoint--; } 

	//void ReqAllowBet ( BOOL bAllowBet ); //add duel bet

public:

	HRESULT SetVehicle ( bool bActive );
	HRESULT ReqSetVehicle( bool bActive );	// 탈것 활성화/비활성화
	HRESULT ReqVehicleUpdate(); // 탈것 장착시 정보 요청
	void	ReqVehicleChangeAccessory( EMSUIT emSUIT ); // 탈것 장혖E아이템 교체
	void	ReqVehicleRemoveSlotItem( EMSUIT emSUIT );	 // 탈것 장혖E아이템 해제
	void	ReqVehicleGiveBattery ( WORD wPosX, WORD wPosY );	// 탈것 연톩E채퓖E갋
	void	ReqVehicleInvenUpdate();	// 탈것 정보 요청

public:
	void	ReqItemShopOpen( bool bOpen );		// ItemShop Open/Close 흟E�

public:
	HRESULT DoActWait ();
	//added by   | 21-6-2012 | Bypass HP+MP+SP
	//HRESULT ReBirth ( WORD wHP, WORD wMP, WORD wSP, D3DXVECTOR3 vPos, bool bWait );
	HRESULT ReBirth ( DWORD wHP, DWORD wMP, DWORD wSP, DWORD wCP, D3DXVECTOR3 vPos, bool bWait );
	HRESULT MoveActiveMap ( NavigationMesh* pNavi, const D3DXVECTOR3 &vPos, bool bWait=true );
	HRESULT PlayerUpdate ( float fTime, float fElapsedTime );
	
	HRESULT ReqFriendWindowOpen( bool bOpen );
	
	HRESULT ReqClubInfoUpdate( bool bUpdate );

protected:
	void ReSelectAnimation ();
	HRESULT UpateAnimation ( float fTime, float fElapsedTime );
	HRESULT UpdateClientState ( GLMSG::SNETPC_UPDATE_STATE *pNetMsg );

	void NewConftBoundEffect ( const EMCONFT_TYPE emCONFT );
	void DelConftBoundEffect ();

protected:
	STARGETID	m_sOLD_TARMOB;
	SACTIONTAR	m_sACTAR;

	D3DXVECTOR3 m_vCamFromPt;
	D3DXVECTOR3 m_vCamLookatPt;
	D3DXVECTOR3 m_vCamUpVec;

public:
	BOOL		m_bCamLockNpc;
//add mouse effect
public:
	SACTIONTAR	m_sACTARMouse;
	BOOL		m_bACTARMouse;

public:
	STARGETID	m_sMouseTargetID;
	GLCOPY*		m_pACTTAR;
	GLCOPY*		m_pACTTARMouse;


public:
	SACTIONTAR& GetActTarget ()		{	return m_sACTAR; }
	bool IsPK_TAR ( GLCharClient* pCHAR, bool bFORCED );
	bool IsClubBattle_TAR ( GLCharClient* pCHAR );
	int	GetClubColorIndex( GLCharClient* pCHAR );

protected:
	STARGETID* GetCONFT_TAR ( DETECTMAP_RANGE &pair );

protected:
	SACTIONTAR FindActionTarget ( const D3DXVECTOR3 &vTargetPt, const D3DXVECTOR3 &vFromPt, const EMFIND_TAR emFINDTAR );
	SACTIONTAR FindNearItem ();
	SACTIONTAR FindNearMob ();

protected:
	void StartAttackProc ();
	BOOL AttackProc ( float fElapsedTime );
	void AttackEffect ( const SANIMSTRIKE &sStrikeEff );

protected:
	void StartSkillProc ();
	BOOL SkillProc ( float fElapsedTime );

	EMELEMENT GET_ITEM_ELMT ();

	void SKT_EFF_HOLDOUT ( STARGETID sTarget, DWORD dwDamageFlag );

	void SK_EFF_TARG ( const PGLSKILL pSkill, const SANIMSTRIKE &sStrikeEff, const STARGETID &sTarget );
	void SK_EFF_SELFZONE ( const SANIMSTRIKE &sStrikeEff, const SKILL::EMEFFECTPOS emPOS, const char* const szZONE_EFF, STARGETID *pTarget=NULL );
	void SK_EFF_TARZONE ( const STARGETID &sTarget, const SKILL::EMEFFECTPOS emPOS, const char* const szZONE_EFF );
	void SkillEffect ( const SANIMSTRIKE &sStrikeEff );
	//added by   | 23-6-2012 | test fixing mouse effect
	void MouseEffect ( const STARGETID &sTarget, const char* const szMOUSE_EFF );

protected:
	//	자기폴發게 스킬 체크 ( 자콅E위치에 영�갋)
	BOOL SKT_SELFZONEOUR ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//  적들에게 스킬 체크 ( 자콅E위치에 영�갋)
	BOOL SKT_SELFZONEENERMY ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//  모두에게 스킬 체크 ( 자콅E위치에 영�갋)
	BOOL SKT_SELFZONANYBODY ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );

	//	자기폴發게 스킬 체크 ( 큱E갋위치에 영�갋)이컖E자신 주위
	BOOL SKT_TARSPECOUR_SELF ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//	적들에게 스킬 체크 ( 큱E갋위치에 영�갋)이컖E자신 주위
	BOOL SKT_TARSPECENERMY_SELF ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//	모두에게 스킬 체크 ( 큱E갋위치에 영�갋)이컖E자신 주위
	BOOL SKT_TARSPECANYBODY_SELF ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );

	//	자기폴發게 스킬 체크 ( 큱E갋위치에 영�갋)이컖E목표 주위
	BOOL SKT_TARSPECOUR ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//	적들에게 스킬 체크 ( 큱E갋위치에 영�갋)이컖E목표 주위
	BOOL SKT_TARSPECENERMY ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//	모두에게 스킬 체크 ( 큱E갋위치에 영�갋)이컖E목표 주위
	BOOL SKT_TARSPECANYBODY ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );

	//	'목표'를 향한 부채꼴 모푳E
	BOOL SKT_TARSPECFANWIZE ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	// 적에게만 자콅E위치에서 큱E갋위치깩�갋 ( 화퍊E컖E갋)
	BOOL SKT_TARSELFTOSPEC ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );

	//	자기폴發게 스킬 체크 ( 상큱E갋위치에 영�갋)
	BOOL SKT_TARZONEOUR ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//	적들에게 스킬 체크 ( 상큱E갋위치에 영�갋)
	BOOL SKT_TARZONEENERMY ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );
	//	모두에게 스킬 체크 ( 상큱E갋위치에 영�갋)
	BOOL SKT_TARZONEANYBODY ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos, const GLSKILL &sSKILL, const WORD wLEVEL );

	BOOL SelectSkillTarget ( const STARGETID &sTargetID, const D3DXVECTOR3 *pvTarPos );

protected:
	void P2PReaction ( const STARGETID &sTargetID, const DWORD dwML, const bool bcontinue, BOOL &bMove, D3DXVECTOR3 &vMoveTo );
	void PvPReaction ( const STARGETID &sTargetID, const DWORD dwML, const bool bcontinue, BOOL &bMove, D3DXVECTOR3 &vMoveTo );

	void MobReaction ( const STARGETID &sTargetID, const DWORD dwML, const bool bcontinue, BOOL &bMove, D3DXVECTOR3 &vMoveTo );
	void NpcReaction ( const STARGETID &sTargetID, const DWORD dwML, const bool bcontinue, BOOL &bMove, D3DXVECTOR3 &vMoveTo );
	void ItemReaction ( const STARGETID &sTargetID, const DWORD dwML, const bool bcontinue, BOOL &bMove, D3DXVECTOR3 &vMoveTo );
	void SkillReaction ( const STARGETID &sTargetID, const DWORD dwMR, const bool bcontinue, BOOL &bMove, D3DXVECTOR3 &vMoveTo );
	void GatheringReaction ( const STARGETID &sTargetID, const DWORD dwML, const bool bcontinue, BOOL &bMove, D3DXVECTOR3 &vMoveTo );

	void ReservedAction ( float fTime );

public:
	void ReqSkillReaction ( STARGETID sTID );

public:
	HRESULT Create ( NavigationMesh* pNavi, SCHARDATA2 *pCharData2, D3DXVECTOR3* pvPos, DWORD dwGaeaID, LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT SkinLoad ( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT SkinLoadForTool ( LPDIRECT3DDEVICEQ pd3dDevice, const char* szFile );

public:
	void ResetData ();

public:
	HRESULT FrameMove( float fTime, float fElapsedTime );
	HRESULT FrameMoveForTool( float fTime, float fElapsedTime );
	HRESULT Render( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT RenderShadow( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT RenderReflect( LPDIRECT3DDEVICEQ pd3dDevice );
	void	EventCalculate();
	void	VietnamCalculate();

	void	DisableSkillFact();
	// 지�갋효컖E업데이트
	VOID	UpdateLandEffect();

	//add sw buff
	void	SwIconCheck();

public:
	HRESULT InitDeviceObjects( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT RestoreDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT InvalidateDeviceObjects ();
	HRESULT DeleteDeviceObjects ();
	HRESULT			ReqSortItem ();

public:
	HRESULT			ReqWrap( WORD wPosX, WORD wPosY ); // wrapper
	HRESULT			ReqNonDrop( WORD wPosX, WORD wPosY ); //nondrop card Eduj
	HRESULT			ReqRemoveNonDrop( WORD wPosX, WORD wPosY ); //drop card JohnArthurooo
	HRESULT			ReqRemoveWrap( WORD wPosX, WORD wPosY );
	HRESULT			InvenSchoolChangeSG( WORD wPosX, WORD wPosY ); // change school
	HRESULT			InvenSchoolChangeMP( WORD wPosX, WORD wPosY ); // change school
	HRESULT			InvenSchoolChangePH( WORD wPosX, WORD wPosY ); // change school
	HRESULT			ReqInvenSchoolChange (WORD wSchool ); //change school
	D3DXVECTOR3 CollisionForward( D3DXVECTOR3 vPOSITION, D3DXVECTOR3 vDIRECTION );
	D3DXVECTOR3 CollisionBackward( D3DXVECTOR3 vPOSITION, D3DXVECTOR3 vDIRECTION );

public:
	void	ReqLinkSkill( SNATIVEID sSKILLID, WORD wLevel );	//link skill

	void	ExitTowerWars();

public:
	GLCharacter ();
	~GLCharacter ();
};

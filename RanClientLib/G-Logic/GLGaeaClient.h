#pragma once

#include "string"
#include "../RanClientUILib/Interface/BasicChatRightBody.h"
#include "CList.h"
#include "GLLandManClient.h"
#include "GLogicData.h"
#include "GLogicEx.h"
#include "GLCharacter.h"
#include "GLMapList.h"
#include "GLCrowTracer.h"
#include "GLCOPY.h"
#include "GLActiveMap.h"
#include "GLPetClient.h"
#include "GLSummonClient.h"
#include "GLSchoolWars.h"
//#define _SYNC_TEST

class GLGaeaClient : public GLMapList , public GLCrowTracer, public GLActiveMap ,public GLCHARLOGIC,public GLSchoolWars
{
protected:
	char						m_szAppPath[MAX_PATH];
	HWND						m_hWnd;

	float						m_fAge;
	LPDIRECT3DDEVICEQ			m_pd3dDevice;
	PLANDMANCLIENT				m_pLandMClient;

	GLPetClient					m_Pet;
	GLSummonClient				m_Summon;

	DETECTMAP					m_vecDetectID;
	D3DXVECTOR3					m_vCharPos;

	bool						m_bSCHOOL_FREEPK;	// 학원간 자유 PK
	bool						m_bBRIGHTEVENT;		// 성향 이벤트
public:
	
	bool						m_bCLUBBATTLE;		// 선도전
	float						m_fCLUBBATTLETimer;

	bool						m_bClubDeathMatch;
	float						m_fClubDeathMatchTimer;

	bool						m_bSchoolWars;
	float						m_fSchoolWarsTimer;

	bool						m_bRoyalRumble;
	float						m_fRoyalRumbleTimer;

	bool						m_bTowerWars;
	float						m_fTowerWarsTimer;

	CTime						m_cServerTime;			// 서버의 현재 시간
	char						m_szShopInfoFile[MAX_PATH];
	bool						m_bParticipate;
	bool						m_bRejoin;

	//add sw buff
	WORD						m_wSwSchool;
	bool						m_bSWBonusStart;
	GLCharacter					m_Character;

	int							m_nRandomNumber;
	WORD						m_sKILL;
public:
	CDM_RANK_VEC				m_vecCdmRank;
	SCDM_RANK_EX				m_sMyCdmRank;

	SW_RANK_VEC					m_vecSwRank;
	SSW_RANK_EX					m_sMySwRank;

	SWP_RANK_VEC					m_vecSwPRank;
	SSWP_RANK_EX					m_sMySwPRank;

	RRP_RANK_VEC					m_vecRrPRank;
	SRRP_RANK_EX					m_sMyRrPRank;

	TWP_RANK_VEC					m_vecCtfRankAll;
	TWP_RANK_VEC					m_vecCtfRankSG;
	TWP_RANK_VEC					m_vecCtfRankMP;
	TWP_RANK_VEC					m_vecCtfRankPHX;

	TWP_RANK_INFO_VEC				m_vecCtfRankInfoAll;

	STWP_RANK_EX					m_sMyCtfRank;
	SCHOOLWAR_TOWER_STATUS_VEC		m_vecSwTower;

public:
	bool IsSchoolFreePk ()		{ return m_bSCHOOL_FREEPK; }
	bool IsBRIGHTEVENT ()		{ return m_bBRIGHTEVENT; }
	bool IsClubDeathMatch()		{ return m_bClubDeathMatch; }
	bool IsRoyalRumble()		{ return m_bRoyalRumble; }
	bool IsSchoolWars()			{ return m_bSchoolWars; }
//add sw buff
	WORD GetSwSchoolWinner()	{ return m_wSwSchool; }
	bool SWBonusStart()			{ return m_bSWBonusStart; }
	void SetSchoolWinner		( WORD m_wSchool ) {  m_wSwSchool = m_wSchool; }

	bool IsTowerWars()			{ return m_bTowerWars; }

public:
	HRESULT OneTimeSceneInit ( const char* szAppPath, HWND hWnd );
	HRESULT InitDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT RestoreDeviceObjects ();

	HRESULT InvalidateDeviceObjects ();
	HRESULT DeleteDeviceObjects ();

	HRESULT FrameMove ( float fTime, float fElapsedTime );
	
	HRESULT Render ( CLIPVOLUME &CV );
	HRESULT RenderEff ( CLIPVOLUME &CV );
	void	RenderPickAlpha();

protected:
	PLANDMANCLIENT CreateLandMClient ( char* szLandFileName, D3DXVECTOR3 &vBasicPos );
	PLANDMANCLIENT CreateLandMClient ( SNATIVEID sMapID, D3DXVECTOR3 &vBasicPos );
	PLANDMANCLIENT CreateInstantMapClient ( SNATIVEID sBaseMapID, SNATIVEID sInstantMapID, D3DXVECTOR3 &vBasicPos );

protected:
	HRESULT MoveActiveMap ( SNATIVEID sMapID, D3DXVECTOR3 &vPos );
	HRESULT CreateInstantMap ( SNATIVEID sBaseMapID, SNATIVEID sInstantMapID, D3DXVECTOR3 &vBasicPos );

public:
	HRESULT SetActiveMap ( char* szLandFileName, D3DXVECTOR3 &vBasicPos );
	HRESULT SetActiveMap ( SNATIVEID sMapID, D3DXVECTOR3 &vBasicPos );
	PLANDMANCLIENT GetActiveMap ();
	SNATIVEID GetActiveMapID ();

	HRESULT MoveActiveMap ( NET_MSG_GENERIC *nmg );
	HRESULT CreateInstantMap ( NET_MSG_GENERIC *nmg );
	HRESULT DropOutCrow ( NET_MSG_GENERIC *nmg );
	HRESULT ReBirthFB ( NET_MSG_GENERIC* nmg );
	HRESULT ReCallFB ( NET_MSG_GENERIC* nmg );
	HRESULT ReLvMustLeaveFB ( NET_MSG_GENERIC* nmg );
	HRESULT ReqBusFB ( NET_MSG_GENERIC* nmg );
	HRESULT ReqTaxiFB ( NET_MSG_GENERIC* nmg );
	HRESULT TeleportFB ( NET_MSG_GENERIC* nmg );

public:
	HRESULT ReqClubDeathMatchInfo();
	HRESULT ReqSchoolWarsInfo();
	HRESULT ReqSchoolWarsPInfo();

	HRESULT ReqRoyalRumblePInfo();

	//HRESULT ReqTowerWarsCTFInfo();
	HRESULT ReqCtfIconInfo();

public:
	DWORD GetMobNameColor ( DWORD dwGlobID );
	BOOL IsMapCollsion( D3DXVECTOR3& vTargetPt, D3DXVECTOR3& vFromPt );

public:
	GLCOPY* GetCopyActor ( const STARGETID &sTARID )	{ return GetCopyActor ( sTARID.emCrow, sTARID.dwID ); }
	GLCOPY* GetCopyActor ( const EMCROW emCrow, const DWORD dwID );
	GLCOPY* GetCopyActor ( const std::string &strName );
	GLCharacter* GetCharacter ()						{ return &m_Character; }
	const D3DXVECTOR3 &GetCharacterPos ()				{ return m_Character.GetPosition(); }
	SCHARDATA2& GetCharacterData ()						{ return m_Character.GetCharData(); }
	GLCHARLOGIC& GetCharacterLogic ()					{ return m_Character.GetCharLogic(); }

	PGLCHARCLIENT GetChar ( DWORD dwID );

	BOOL ValidCheckTarget ( const STARGETID & sTargetID );
	DETECTMAP* DetectCrowDie ( const D3DXVECTOR3 &vFrom, const D3DXVECTOR3 &vTarget );
	DETECTMAP* DetectCrow ( DWORD emCrow, const D3DXVECTOR3 &vFrom, const D3DXVECTOR3 &vTarget );
	DETECTMAP* DetectCrow ( DWORD emCrow, const D3DXVECTOR3 &vTarPos, const float fLength );
	BOOL IsCollisionMobToPoint ( const D3DXVECTOR3 &vPoint, const WORD wBodyRadius );

	D3DXVECTOR3* FindCharPos ( std::string strName );
	D3DXVECTOR3* FindCharHeadPos ( std::string strName );
	D3DXVECTOR3* FindCharHeadPos ( DWORD dwGaeaID );
	D3DXVECTOR3* FindMaterialHeadPos ( DWORD dwGaeaID );

	CTime		 GetCurrentTime () { return m_cServerTime; }
	void		 SetCurrentTime ( CTime cServerTime ) { m_cServerTime = cServerTime; }

	// PET
	GLPetClient* GetPetClient () { return &m_Pet; }
	HRESULT		 CreatePET ( NET_MSG_GENERIC* nmg );
	void		 PetSkinPackApplyEffect();

	// SUMMON
	GLSummonClient* GetSummonClient() { return &m_Summon; }
	HRESULT			CreateSummon( NET_MSG_GENERIC* nmg );
	void			ReqUseSummon( SNATIVEID sSummonID );
	void			ReqUseSummonCard( WORD wPosX, WORD wPosY );
	PGLANYSUMMON	GetSummon ( DWORD dwID );

public:
	void MsgProcess ( NET_MSG_GENERIC* nmg );

public:
	virtual DxLandMan* getactivemap()
	{
		PLANDMANCLIENT pMapClient = GetActiveMap ();
		if ( !pMapClient )	return NULL;

		return pMapClient->GetLandMan();
	}

public:
	virtual BOOL IsVisibleCV ( const STARGETID & sTargetID );
	virtual D3DXVECTOR3 GetTargetPos ( const STARGETID &sTargetID );
	virtual DxSkinChar* GetSkinChar ( const STARGETID &sTargetID );
	virtual float GetCrowDir ( const STARGETID &sTargetID );
	float	m_fNextBattleStart;
	float	m_fNextBattleEnd;
	float	m_fPreviousBattleStart;
	float	m_fPreviousBattleEnd;
	float	m_fProgressTime;
	bool	m_bBuffPlace;
	float	m_fBuffPlace;

protected:
	GLGaeaClient(void);

public:
	~GLGaeaClient(void);

public:
	static GLGaeaClient& GetInstance();
};


#pragma once

#include "GLSummon.h"

#include "../EngineLib/NaviMesh/Actor.h"
#include "../EngineLib/G-Logic/GLList.h"
#include "../EngineLib/G-Logic/GLQuadTree.h"

#include "DxSkinChar.h"
#include "GLSkill.h"

#define _SKILLFACT_DEFAULTTIME		(-1.0f)

class GLAnySummon : public GLSUMMON, public GLCOPY
{

protected:
	LPDIRECT3DDEVICEQ	m_pd3dDevice;
	Actor				m_actorMove;
	DxSkinChar*			m_pSkinChar;

	D3DXVECTOR3			m_vDir;
	D3DXVECTOR3			m_vDirOrig;
	D3DXVECTOR3			m_vPos;
	D3DXMATRIX			m_matTrans;	

	D3DXVECTOR3			m_vServerPos;

	D3DXVECTOR3			m_vTarPos;

	STARGETID			m_sTargetID;

public:
	SGLNODE<GLAnySummon*>*	m_pGlobNode;		//	ｸﾊ ｸｮｽｺﾆｮ ｳ・・
	CLIENTQUADNODE*			m_pQuadNode;		//	ﾄ・ﾆｮｸｮ ｳ・・
	SGLNODE<GLAnySummon*>*	m_pCellNode;		//	ｼｿ ｸｮｽｺﾆｮ ｳ・・

	DWORD				m_dwActionFlag;
	EMACTIONTYPE		m_Action;				//	ﾇ犒ｿ.
	WORD				m_wAniSub;

	SCROWATTACK*		m_pAttackProp;			//	ｰﾝ ｼﾓｼｺ.

public:
	D3DXVECTOR3			m_vMax;
	D3DXVECTOR3			m_vMin;
	float				m_fHeight;

	D3DXVECTOR3			m_vMaxOrg;
	D3DXVECTOR3			m_vMinOrg;

protected:
	float m_fattTIMER;
	int   m_nattSTEP;

protected:
	void StartAttackProc ();
	BOOL AttackProc ( float fElapsedTime );
	void AttackEffect ( const SANIMSTRIKE &sStrikeEff );
	HRESULT UpdateAnimation ( float fTime, float fElapsedTime );

public:
	GLAnySummon(void);
	~GLAnySummon(void);

	void ASSIGN ( PSDROPSUMMON pDropSummon );

	DxSkinChar* GetSkinChar ()							{ return m_pSkinChar; }

	BOOL IsValidBody ();

	float GetDirection ();
	
	HRESULT Create ( PSDROPSUMMON pDropSummon, NavigationMesh* pNavi, LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT SkinLoad ( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT UpateAnimation ( float fTime, float fElapsedTime );
	HRESULT	UpdateTurnAction ( float fTime, float fElapsedTime );

	void TurnAction ( EMACTIONTYPE toAction );


	BOOL IsSTATE ( DWORD dwStateFlag )		 			{ return m_dwActionFlag&dwStateFlag; }
	void SetSTATE ( DWORD dwStateFlag );
	void ReSetSTATE ( DWORD dwStateFlag )				{ m_dwActionFlag &= ~dwStateFlag; }

	void MsgGoto ( NET_MSG_GENERIC* nmg );
	void MsgStop ( NET_MSG_GENERIC* nmg );
	void MsgUpdateMoveState ( NET_MSG_GENERIC* nmg );
	void MsgSkillFact ( NET_MSG_GENERIC* nmg );
	void MsgHpUpdate ( NET_MSG_GENERIC* nmg );
	void MsgAttack ( NET_MSG_GENERIC* nmg );
	
	// Default FrameWork
	HRESULT FrameMove( float fTime, float fElapsedTime );
	HRESULT Render( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT RenderShadow( LPDIRECT3DDEVICEQ pd3dDevice, CLIPVOLUME &cv );
	HRESULT RenderReflect( LPDIRECT3DDEVICEQ pd3dDevice );

	HRESULT InitDeviceObjects( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT RestoreDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT InvalidateDeviceObjects ();
	HRESULT DeleteDeviceObjects ();

	void SK_EFF_SELFZONE ( const SANIMSTRIKE &sStrikeEff, const SKILL::EMEFFECTPOS emPOS, const char* const szZONE_EFF, STARGETID *pTarget );
	void SKT_EFF_HOLDOUT ( STARGETID sTarget , DWORD dwDamageFlag );
	BOOL RECEIVE_SKILLFACT ( const SNATIVEID skill_id, const WORD wlevel, const DWORD dwSELECT, float fAge = _SKILLFACT_DEFAULTTIME );

	void MsgProcess ( NET_MSG_GENERIC* nmg );

	virtual BOOL IsACTION ( EMACTIONTYPE emCur )	{ return m_Action == emCur; }

	virtual WORD GetBodyRadius ();
	virtual float GetBodyHeight()			{ return m_fHeight; }
	//Added by tobets | 18-7-2012 | add mouse effect code
	virtual float GetScale()			{ return ( GetSkinChar() != NULL ) ? GetSkinChar()->GetScale() : 0.f; }
	virtual DxSkinChar* GetSkinCharF() { return GetSkinChar(); }
	virtual D3DXVECTOR3 GetPosBodyHeight ()	{ return D3DXVECTOR3( m_vPos.x, m_vPos.y+m_fHeight, m_vPos.z ); }

	virtual EMCROW GetCrow () const			{ return CROW_SUMMON; }
	virtual DWORD GetCtrlID () const		{ return m_dwGUID; }

	virtual const char* GetName () const	{ return m_pSummonCrowData->GetName(); }
	virtual GLPWDATA GetHp () const			{ return GLPWDATA(GETHP(),GETMAXHP()); }

	virtual GLPWDATA GetHpSg () const			{ return GLPWDATA(GETHP(),GETMAXHP()); }
	virtual GLPWDATA GetHpMp () const			{ return GLPWDATA(GETHP(),GETMAXHP()); }
	virtual GLPWDATA GetHpPhx () const			{ return GLPWDATA(GETHP(),GETMAXHP()); }
	virtual WORD GetSchool() const				{ return 0; }

	//Added by tobets | 21-6-2012 | Bypass damage
	//virtual void ReceiveDamage ( WORD wDamage, DWORD dwDamageFlag, STARGETID sACTOR );
	virtual void ReceiveDamage ( DWORD wDamage, DWORD dwDamageFlag, STARGETID sACTOR );
	virtual void ReceiveAVoid ();
	virtual void ReceiveSwing ();

	BOOL	IsCollisionVolume ();	


	virtual const D3DXVECTOR3 &GetPosition ()		{ return m_vPos; }
};

typedef GLAnySummon* PGLANYSUMMON;
typedef CGLLIST<PGLANYSUMMON> GLANYSUMMONLIST;
typedef SGLNODE<PGLANYSUMMON> GLANYSUMMONNODE;




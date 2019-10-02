#ifndef GLMATERIALCLIENT_H_
#define GLMATERIALCLIENT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GLCrowData.h"
#include "GLCOPY.h"
//#include "GLogicEx.h"

#include "../../EngineLib/NaviMesh/Actor.h"
#include "DxSkinChar.h"

#ifndef GLLandManClient
	class GLLandManClient;
	class GLClientNode;
	typedef SQUADNODE<GLClientNode> CLIENTQUADNODE;
#endif //GLLandMan

class GLMaterialClient : public GLCOPY
{
public:
	PCROWDATA			m_pCrowData;					//	Crow ±‚∫ª ¡§∫∏.
	SNATIVEID			m_sNativeID;					//	Crow NativeID.

protected:
	LPDIRECT3DDEVICEQ	m_pd3dDevice;
	Actor				m_actorMove;
	DxSkinChar*			m_pSkinChar;

	D3DXVECTOR3			m_vDir;
	D3DXVECTOR3			m_vDirOrig;
	D3DXVECTOR3			m_vPos;
	D3DXMATRIX			m_matTrans;

	D3DXVECTOR3			m_vServerPos;

	//	Note : AABB
protected:
	D3DXVECTOR3		m_vMaxOrg;
	D3DXVECTOR3		m_vMinOrg;

public:
	D3DXVECTOR3		m_vMax;
	D3DXVECTOR3		m_vMin;
	float			m_fHeight;

	//	Note : ¡¶æÅEƒ⁄µÅE
	//
public:
	DWORD				m_dwGlobID;				//	ª˝º∫ ∏ﬁ∏∏Æ ¿Œµ¶Ω∫øÅE( «ÿ¥ÅEGLLandMan≥ªø°º≠ ¿Ø¥œ≈©«‘ )
	DWORD				m_dwCeID;				//	ºø ID.

	GLLandManClient*			m_pLandManClient;	//	∏  ¿ŒΩ∫≈œΩ∫ ∆˜¿Œ≈Õ.
	SGLNODE<GLMaterialClient*>*	m_pGlobNode;		//	∏  ∏ÆΩ∫∆Æ ≥ÅEÅE
	CLIENTQUADNODE*				m_pQuadNode;		//	ƒıµÅE∆Æ∏Æ ≥ÅEÅE
	SGLNODE<GLMaterialClient*>*	m_pCellNode;		//	ºø ∏ÆΩ∫∆Æ ≥ÅEÅE

	//	Note : «‡µø.
protected:
	float				m_fAge;					//	∞Ê∞ÅEΩ√∞£.
	EMACTIONTYPE		m_Action;				//	«‡µø.
	DWORD				m_dwActState;			//	«‡µø ªÛ≈¬.

protected:
	float				m_fIdleTime;			//	»ﬁΩƒ Ω√∞£.

public:
	BOOL IsValidBody ();
	BOOL IsDie ();
	BOOL IsHaveVisibleBody ();

public:
	BOOL IsSTATE ( DWORD dwState )					{ return m_dwActState&dwState; }
	virtual BOOL IsACTION ( EMACTIONTYPE emCur )	{ return m_Action == emCur; }

protected:
	void SetSTATE ( DWORD dwState )					{ m_dwActState |= dwState; }
	void ReSetSTATE ( DWORD dwState )				{ m_dwActState &= ~dwState; }

public:
	HRESULT CreateMaterial ( GLLandManClient *pLandManClient, SDROP_MATERIAL *pCrowDrop, LPDIRECT3DDEVICEQ pd3dDevice );

public:
	void SetPosition ( D3DXVECTOR3 &vPos );
	virtual const D3DXVECTOR3 &GetPosition ()		{ return m_vPos; }
	float GetDirection ();
	DxSkinChar* GetCharSkin ()						{ return m_pSkinChar; }

public:
	void TurnAction ( EMACTIONTYPE toAction );

public:
	virtual EMCROW GetCrow () const			{ return CROW_MATERIAL; }
	virtual DWORD GetCtrlID () const		{ return m_dwGlobID; }
	virtual const char* GetName () const	{ return m_pCrowData->GetName(); }
	virtual GLPWDATA GetHp () const			{ return GLPWDATA(); }

	virtual GLPWDATA GetHpSg () const			{ return GLPWDATA(); }
	virtual GLPWDATA GetHpMp () const			{ return GLPWDATA(); }
	virtual GLPWDATA GetHpPhx () const			{ return GLPWDATA(); }
	virtual WORD GetSchool() const				{ return 0; }

	virtual WORD GetBodyRadius ();
	virtual float GetBodyHeight()			{ return m_fHeight; }
	//Added by   | 18-7-2012 | add mouse effect code
	virtual float GetScale()			{ return ( GetCharSkin() != NULL ) ? GetCharSkin()->GetScale() : 0.f; }
	virtual DxSkinChar* GetSkinCharF() { return GetCharSkin(); }
	virtual D3DXVECTOR3 GetPosBodyHeight ()	{ return D3DXVECTOR3( m_vPos.x, m_vPos.y+m_fHeight, m_vPos.z ); }

public:
	virtual void MsgProcess ( NET_MSG_GENERIC* nmg );
	//Added by   | 21-6-2012 | Bypass damage
	//virtual void ReceiveDamage ( WORD wDamage, DWORD dwDamageFlag, STARGETID sACTOR ) {}
	virtual void ReceiveDamage ( DWORD wDamage, DWORD dwDamageFlag, STARGETID sACTOR ) {}
	virtual void ReceiveAVoid () {}
	virtual void ReceiveSwing () {}

protected:
	HRESULT UpateAnimation ( float fTime, float fElapsedTime );	

public:
	BOOL IsCollisionVolume ();
	HRESULT FrameMove ( float fTime, float fElapsedTime );

	HRESULT RenderShadow ( LPDIRECT3DDEVICEQ pd3dDevice, CLIPVOLUME &cv );
	HRESULT Render ( LPDIRECT3DDEVICEQ pd3dDevice, CLIPVOLUME &cv, BOOL bRendAABB );

public:
	HRESULT RestoreDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT InvalidateDeviceObjects ();

public:
	GLMaterialClient(void);
	~GLMaterialClient(void);
};

typedef GLMaterialClient* PGLMATERIALCLIENT;

typedef CGLLIST<PGLMATERIALCLIENT>	GLMATERIALCLIENTLIST;
typedef SGLNODE<PGLMATERIALCLIENT>	GLMATERIALCLIENTNODE;

#endif // GLMATERIALCLIENT_H_
#pragma	once

#include "../EngineUiLib/GUInterface/UIGroup.h"
#include "DxSkinChar.h"
#include "./GLCharData.h"
class	CCharacterWindowCharRenderView : public CUIGroup
{

private:
	enum
	{
	};

public:
	CCharacterWindowCharRenderView ();
	virtual	~CCharacterWindowCharRenderView ();

public:
	void	CreateSubControl ();

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual HRESULT RestoreDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );
	virtual HRESULT DeleteDeviceObjects ();
	virtual HRESULT Render ( LPDIRECT3DDEVICEQ pd3dDevice );
	virtual HRESULT FrameMove( LPDIRECT3DDEVICEQ pd3dDevice, float fTime, float fElapsedTime );

public:
	DxSkinChar*			m_pSkinChar;
	D3DXMATRIX			m_matTrans;
	WORD				m_wLastFace;
	WORD				m_wLastHair;
	//float				m_fDelay;

public:
	LPDIRECT3DDEVICEQ pd3dDevice;
	void	CreateModel( LPDIRECT3DDEVICEQ pd3dDevice );
	void	RenderModel( LPDIRECT3DDEVICEQ pd3dDevice );
	void	UpdateSuit(  LPDIRECT3DDEVICEQ pd3dDevice );
	SDROP_CHAR			m_CharData;
	void	ClearRender();
	BOOL IsUseArmSub() const			{ return m_CharData.m_bUseArmSub; }
	const SITEMCLIENT& GET_SLOT_ITEMa ( EMSLOT _slot )				{ return m_CharData.m_PutOnItems[_slot]; }
	BOOL VALID_SLOT_ITEMa ( EMSLOT _slot );
	EMSLOT GetCurRHandd();
	EMSLOT GetCurLHandd();
	SITEM* GET_SLOT_ITEMDATAa ( EMSLOT _slot );
};
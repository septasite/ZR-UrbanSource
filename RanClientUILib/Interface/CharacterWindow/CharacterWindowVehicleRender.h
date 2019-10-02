#pragma	once

#include "../EngineUiLib/GUInterface/UIGroup.h"
#include "DxSkinChar.h"
#include "GLVehicle.h"

class	CCharacterWindowVehicleRender : public CUIGroup
{

private:
	enum
	{
	};

public:
	CCharacterWindowVehicleRender ();
	virtual	~CCharacterWindowVehicleRender ();

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
	SVEHICLEITEMINFO	sVehicleInfo;
	bool				bRenderVehicle;
	SNATIVEID			sVehicleID;
	D3DXVECTOR3			m_vTrans;
	D3DXVECTOR3			m_vRot;
	float				m_fDelay;
	float				m_fScale;
	float				m_fFarZ;

public:
	void	CreateModel( LPDIRECT3DDEVICEQ pd3dDevice );
	void	RenderModel( LPDIRECT3DDEVICEQ pd3dDevice );
	void	UpdateSuit( LPDIRECT3DDEVICEQ pd3dDevice );
	void	ClearRender();
	void	RenderVehicle( SNATIVEID sID, SVEHICLEITEMINFO sInfo );
	void	UpdateAnimation();
};
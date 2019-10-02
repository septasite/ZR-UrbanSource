#pragma	once

#include "../EngineUiLib/GUInterface/UIGroup.h"
#include "DxSkinChar.h"
#include "GLItem.h"


class	CItemPreviewWindowRender : public CUIGroup
{

private:
	enum
	{
	};

public:
	CItemPreviewWindowRender ();
	virtual	~CItemPreviewWindowRender ();

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
	SPREVIEWDATA		m_sPreviewData;	
	bool				m_bReady;
	float				m_fRenderDelay;
	D3DXVECTOR3			m_vRot;

public:
	void	CreateModel( LPDIRECT3DDEVICEQ pd3dDevice );
	void	RenderModel( LPDIRECT3DDEVICEQ pd3dDevice );
	void	UpdateSuit( LPDIRECT3DDEVICEQ pd3dDevice );
	void	ClearRender();
	void	UpdateAnimation();

};
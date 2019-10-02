//	기본 정보 표시
//
//	최초 작성자 : 성기엽
//	이후 수정자 : 
//	로그
//		[2003.11.27]
//			@ 작성
//

#pragma	once

#include "../EngineUiLib/GUInterface/UIGroup.h"
#include "GLDefine.h"
#include "GLItem.h"


class	CBasicProgressBar;

class	CItemImageVehicle : public CUIGroup
{
public:
	CItemImageVehicle ();
	virtual	~CItemImageVehicle ();

public:
	void	CreateSubControl ();

public:
	virtual HRESULT InitDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );
	virtual void Update( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void SetDiffuse(D3DCOLOR _diffuse);

public:
    void	SetItem ( SITEMCUSTOM sItemCustom );
	SITEMCUSTOM&	GetItem ();
	const CString&	GetItemTextureName () const;
	void	ResetItem ();

	void SetUseTwinkle( bool bUse )					{ m_bTwinkle = bUse; }

	void SetItemProcess( SNATIVEID sNativeID );
	void ReSetItemProcess();
	void VisibleFlipImage( bool bVisible );


private:
	LPDIRECT3DDEVICEQ	m_pd3dDevice;

private:
	SITEMCUSTOM	sItem;
	SNATIVEID	m_sICONINDEX;
	SNATIVEID	m_sNativeID;
	CString		m_strTextureName;

	CBasicProgressBar*	m_pItemProcess;

	float m_TotElapsedTime;
	bool m_bItemUsed;
	bool m_bItemEnd;

	bool m_bTwinkle;


private:
	CUIControl*		m_pItemImageVehicle;
	CUIControl*		m_pItemImageFlip;
};
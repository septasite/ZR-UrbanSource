
#pragma	once

#include "../EngineUiLib/GUInterface/UIGroup.h"
#include "GLDefine.h"


class	CBasicProgressBar;
class	CBasicTextBox;

class	CItemImageCharWear : public CUIGroup
{
public:
	CItemImageCharWear ();
	virtual	~CItemImageCharWear ();

public:
	void	CreateSubControl ();

public:
	virtual HRESULT InitDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );
	virtual void Update( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void SetDiffuse(D3DCOLOR _diffuse);

public:
    void	SetItem ( SNATIVEID sICONINDEX, const char* szTexture, int nGrind, SNATIVEID sNativeID = false );
	SNATIVEID	GetItem ();
	const CString&	GetItemTextureName () const;
	void	ResetItem ();

	void SetUseTwinkle( bool bUse )					{ m_bTwinkle = bUse; }

	void SetItemProcess( SNATIVEID sNativeID );
	void ReSetItemProcess();


private:
	LPDIRECT3DDEVICEQ	m_pd3dDevice;

private:
	SNATIVEID	m_sICONINDEX;
	SNATIVEID	m_sNativeID;
	CString		m_strTextureName;

	CBasicProgressBar*	m_pItemProcess;
	CBasicTextBox*		m_pTextBox;

	float m_TotElapsedTime;
	bool m_bItemUsed;
	bool m_bItemEnd;

	bool m_bTwinkle;


private:
	CUIControl*		m_pItemImage;
};
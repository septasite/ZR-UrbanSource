#pragma	once

#include "../EngineUIlib/GUInterface/UIGroup.h"
#include "GLDefine.h"


class	CBasicProgressBar2;

class	CItemImage2 : public CUIGroup
{
public:
	CItemImage2 ();
	virtual	~CItemImage2 ();

public:
	void	CreateSubControl ();

public:
	virtual HRESULT InitDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );
	//virtual void Update( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	//virtual	void SetDiffuse(D3DCOLOR _diffuse);

public:
    void	SetItem ( SNATIVEID sICONINDEX, const char* szTexture, SNATIVEID sNativeID = false );
	SNATIVEID	GetItem ();
	const CString&	GetItemTextureName () const;
	//void	ResetItem ();
	//void	SetUnUse();
	void	SetUse();

	void SetUseTwinkle( bool bUse )					{ m_bTwinkle = bUse; }

	//void SetItemProcess( SNATIVEID sNativeID );
	void ReSetItemProcess();



private:
	LPDIRECT3DDEVICEQ	m_pd3dDevice;

private:
	SNATIVEID	m_sICONINDEX;
	SNATIVEID	m_sNativeID;
	CString		m_strTextureName;


	float m_TotElapsedTime;
	bool m_bItemUsed;
	bool m_bItemEnd;

	bool m_bTwinkle;


private:
	CUIControl*		m_pItemImage;
	CUIControl*		m_pItemImageUnUse;
};
class	CItemSlot2 : public CUIGroup
{
public:
	CItemSlot2 ();
	virtual	~CItemSlot2 ();

public:
	enum
	{
		nLIMIT_COLUMN = 10,
		//nLIMIT_COLUMN = EM_INVENSIZE_X
	};

protected:
	int		m_nIndex;
	int		m_nMaxColumn;

	bool	m_bBLOCK;


protected:
	CItemImage2*			m_pItemImageArray[nLIMIT_COLUMN];	
	SINVENITEM			m_InvenItem[nLIMIT_COLUMN];
	CUIControl*			m_pBlock[6];


public:
	void	SetItemImage ( int nIndex, SINVENITEM& ref_InvenItem );
	SINVENITEM&	GetItemImage ( int nIndex )		{ return m_InvenItem[nIndex]; }
	void	ResetItemImage ( int nIndex );
	void	SetItemUnUse ( int nIndex );
	void	SetItemUse ( int nIndex );



};
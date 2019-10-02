#pragma	once

#include "../RanClientUILib/Interface/UIWindowEx.h"
#include "../RanClientLib/G-Logic/GLParty.h"
#include "../RanClientLib/G-Logic/GLCrowRenList.h"
#include "../RanClientLib/G-Logic/GLContrlServerMsg.h"

struct	GLPARTY_CLIENT;
class	GLMapAxisInfo;
class	CBasicScrollBarEx;
class	CBasicTextBox;
class	CLargeMapWindowSlotRender;
class	CLargeMapWindowImage : public CUIWindowEx
{
private:
	enum
	{
		LARGEMAP_SCROLLBAR_H = NO_ID + 1,
		LARGEMAP_SCROLLBAR_V,
		LARGEMAP_IMAGE,
		LARGEMAP_RESIZE_THUMB,
		PLAYER_MARK,
		LARGEMAP_DIRECTION,
		BASE_CONTROLID,
		BASE_CONTROLID_END = BASE_CONTROLID + 1000,
	};

public:
	CLargeMapWindowImage ();
	virtual	~CLargeMapWindowImage ();

public:
	void	Initialize();
	void	ConvIntDataFloatData();
	void	CreateSubControl();
	void	UPDATE_CHARDIR();

private:
	void	SetAutoMove( bool bAutoMove )	{ m_bAUTO_MOVE = bAutoMove; }
	void	TranslateMeg( UIGUID cID, DWORD dwMsg, CUIControl * pUIControl );
	void	TranslateMegThumb( UIGUID cID, DWORD dwMsg, CUIControl * pUIControl );

public:
	virtual HRESULT InitDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );
	virtual	void	Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void	TranslateUIMessage ( UIGUID cID, DWORD dwMsg );
	virtual	HRESULT	Render ( LPDIRECT3DDEVICEQ pd3dDevice );
	virtual	void	SetVisibleSingle ( BOOL bVisible );

public:
	void	SetMapAxisInfo ( GLMapAxisInfo &sInfo, const CString& strMapName );
	void	OnLButtonUp();

	void	UPDATE_TARGET_POS( int iX, int iY );
	void	VISIBLE_TARGET_POS( BOOL bVisible = FALSE );

	//void	SetDefaultPosition();

private:
	void	UPDATE_CHAR_POS ( CUIControl * pControl, const D3DXVECTOR3& vPlayerPos );
	void	UPDATE_CHAR_ROTATE ( const D3DXVECTOR3& vCharDir );

	void	UPDATE_MOUSE_POS ( const int nMouseX, const int nMouseY );

	void	UPDATE_PARTY();
	void	UPDATE_PARTY_DEL();
	void	UPDATE_PARTY_INS( GLPARTY_CLIENT * pSelfClient );

private:
	GLPARTY_CLIENT*	FindSelfClient ();
	BOOL	IsSameMap ( GLPARTY_CLIENT *pSelf, GLPARTY_CLIENT *pMember );

private:
	void	CONVERT_WORLD2MAP ( const D3DXVECTOR3& vPos, int& nPosX, int& nPosY );
	void	CONVERT_MOUSE2MAP ( const int nMousePosX, const int nMousePosY, int& nPosX, int& nPosY );
	void	CONVERT_MAP2WORLD ( const int nPosX, const int nPosY, D3DXVECTOR3& vPos );
	void	DoCHARPOS_OnCENTER_InVIEW ( int nMapPosX, int nMapPosY );

private:
	LPDIRECT3DDEVICEQ	m_pd3dDevice;

	float				m_fPercentH_BACK;
	float				m_fPercentV_BACK;

	D3DXVECTOR2			m_vScrollGap;

	D3DXVECTOR2			m_vRenderSize;
	D3DXVECTOR2			m_vRenderPos;

private:
	int					m_nWORLD_START_X;
	int					m_nWORLD_START_Y;
	int					m_nWORLD_SIZE_X;
	int					m_nWORLD_SIZE_Y;

	int					m_nMAP_TEXSIZE_X;
	int					m_nMAP_TEXSIZE_Y;

	int					m_nVIEW_START_X;
	int					m_nVIEW_START_Y;
	int					m_nVIEW_SIZE_X;
	int					m_nVIEW_SIZE_Y;

	D3DXVECTOR2			m_vWORLD_START;
	D3DXVECTOR2			m_vWORLD_SIZE;
	D3DXVECTOR2			m_vMAP_TEXSIZE;

private:
	BOOL				m_bFirstGap;
	D3DXVECTOR2			m_vGap;

	int					m_PosX;
	int					m_PosY;

	D3DXVECTOR2			m_vMOUSE_BACK;

private:
	CBasicScrollBarEx*	m_pScrollBarH;
	CBasicScrollBarEx*	m_pScrollBarV;

	CUIControl*			m_pMap;	
	CUIControl*			m_pPlayerMark;
	CUIControl*			m_pTestMark;

	CUIControl*			m_pMousePosBack;
	CBasicTextBox*		m_pMousePosText;

	CUIControl*			m_pMark[MAXPARTY];

private:
	bool				m_bAUTO_MOVE;

private:
	CUIControl*			m_pTargetMark;
	int					m_iTargetX;
	int					m_iTargetY;


public:
	void				LoadMob(NET_MSG_GENERIC* nmg, GLCHARLOGIC *pCHAR );

private:
	typedef	std::pair<D3DXVECTOR3, CLargeMapWindowSlotRender*>	CROW_PAIR;
	typedef	std::list<CROW_PAIR>								CROW_LIST;
	typedef	CROW_LIST::iterator									CROW_LIST_ITER;

	CROW_LIST													m_CrowList;
	UIGUID														m_NEWID;

public:
	void				UPDATE_CROW_POS ( CLargeMapWindowSlotRender * pControl, const D3DXVECTOR3& vPos );
	void				ClearMobList();
	void				SetGateList();
	void				SetPage(int nIndex);
};
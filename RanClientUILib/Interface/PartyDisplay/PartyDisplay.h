#pragma	once

#include "../RanClientUILib/Interface/UIWindowEx.h"
#include "GLParty.h"

struct	GLPARTY_CLIENT;
class	CPartySlotDisplay;
class	CPartyDisplayBuffInfo;
class	CBasicLineBox;
class	CPartyDisplay : public CUIWindowEx
{
protected:
	enum
	{
		PARTYDISPLAY_SLOT_MEMBER0 = ET_CONTROL_NEXT,
		PARTYDISPLAY_SLOT_MEMBER1,
		PARTYDISPLAY_SLOT_MEMBER2,
		PARTYDISPLAY_SLOT_MEMBER3,
		PARTYDISPLAY_SLOT_MEMBER4,
		PARTYDISPLAY_SLOT_MEMBER5,
		PARTYDISPLAY_SLOT_MEMBER6,
		PARTYDISPLAY_SLOT_MEMBER7,
	};

public:
	CPartyDisplay ();
	virtual	~CPartyDisplay ();

public:
	void CreateSubControl ();

private:
	GLPARTY_CLIENT*		FindSelfClient ();
	BOOL	IsSameMap ( GLPARTY_CLIENT *pSelf, GLPARTY_CLIENT *pMember );

private:
	void	SetSlotMember ( CPartySlotDisplay* pPartySlot, GLPARTY_CLIENT *pMember, BOOL bSameMap, const int nPartySlotID );

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );

private:
	CPartySlotDisplay*	m_pPartySlot[MAXPARTY];
	bool				m_bMOUSEIN;
	bool				m_bBuffOK;
	void				CheckMouseState();

public:
	int			m_PosX;
	int			m_PosY;
	D3DXVECTOR2	m_vGap;
	
	bool		m_bCHECK_MOUSE_STATE;

	UIRECT m_rcOriginalPos;
};
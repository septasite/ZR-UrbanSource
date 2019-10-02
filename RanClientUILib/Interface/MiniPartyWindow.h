#pragma	once

#include "UIWindowEx.h"
#include "GLParty.h"

class	CMiniPartySlot;
struct	GLPARTY_CLIENT;
class	CPartyBuffInfo;
class	CBasicLineBox;
class	CBasicLineBoxEx;
class	GLPartyClient;

class	CMiniPartyWindow : public CUIWindowEx
{
protected:
	enum
	{
		MINIPARTY_SLOT_MEMBER0 = ET_CONTROL_NEXT,
		MINIPARTY_SLOT_MEMBER1,
		MINIPARTY_SLOT_MEMBER2,
		MINIPARTY_SLOT_MEMBER3,
		MINIPARTY_SLOT_MEMBER4,
		MINIPARTY_SLOT_MEMBER5,
		MINIPARTY_SLOT_MEMBER6,
		MINIPARTY_SLOT_MEMBER7,

		MINIPARTY_BUFF_INFO,
	};

public:
	CMiniPartyWindow ();
	virtual	~CMiniPartyWindow ();

public:
	void CreateSubControl ();

private:
	GLPARTY_CLIENT*		FindSelfClient ();
	BOOL	IsSameMap ( GLPARTY_CLIENT *pSelf, GLPARTY_CLIENT *pMember );

private:
	void	SetSlotMember ( CMiniPartySlot* pPartySlot, GLPARTY_CLIENT *pMember, BOOL bSameMap, const int nPartySlotID );

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	
	CBasicLineBoxEx*	m_pLineBox0;
	CBasicLineBoxEx*	m_pLineBox1;
	CBasicLineBoxEx*	m_pLineBox2;
	CBasicLineBoxEx*	m_pLineBox3;
	CBasicLineBoxEx*	m_pLineBox4;
	CBasicLineBoxEx*	m_pLineBox5;
	CBasicLineBoxEx*	m_pLineBox6;
	CBasicLineBoxEx*	m_pLineBox7;

private:
	CMiniPartySlot*		m_pPartySlot[MAXPARTY];
	CUIControl*			m_pSlotOver[MAXPARTY];
	CPartyBuffInfo*		m_pPartyBuffInfo;
	bool				m_bMOUSEIN;
	CUIControl*		m_bg_white;
	CBasicLineBox*  m_pBackLine1;
};
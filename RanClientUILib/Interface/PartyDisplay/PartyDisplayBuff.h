#pragma	once

#include "../RanClientUILib/Interface/UIWindowEx.h"
#include "GLParty.h"

class	CPartyDisplayBuffInfo;
class	CPartyDisplayBuff : public CUIWindowEx
{
protected:
	enum
	{
		PARTYDISPLAY_BUFF_INFO0 = ET_CONTROL_NEXT,
		PARTYDISPLAY_BUFF_INFO1,
		PARTYDISPLAY_BUFF_INFO2,
		PARTYDISPLAY_BUFF_INFO3,
		PARTYDISPLAY_BUFF_INFO4,
		PARTYDISPLAY_BUFF_INFO5,
		PARTYDISPLAY_BUFF_INFO6,
		PARTYDISPLAY_BUFF_INFO7,
	};

public:
	CPartyDisplayBuff ();
	virtual	~CPartyDisplayBuff ();

public:
	void CreateSubControl ();
	void ResetAll();
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

private:
	CPartyDisplayBuffInfo*		m_pBUFF[MAXPARTY];
};
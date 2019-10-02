#pragma	once

#include "../EngineUILib/GUInterface/UIGroup.h"
#include "GLCharDefine.h"

class	CBasicTextBox;
class	CBasicProgressBar;
class	CPartySlotDisplay : public CUIGroup
{
protected:
	enum
	{
		
	};

public:
	CPartySlotDisplay ();
	virtual	~CPartySlotDisplay ();

	void			CreateSubControl ();

protected:
	CUIControl*		CreateControl ( const char* szControl );
	CBasicTextBox*	CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, D3DCOLOR D3DCOLOR, int nAlign );
};
#pragma	once

#include "./UIWindowEx.h"
#include "GLCharDefine.h"

class	CD3DFontPar;
class	CBasicTextButton;
class	CSwPRankingDisplay;//qweq
class	CSwRankingDisplay;
struct	GLCHARLOGIC;

class CSchoolWarWindow : public CUIWindowEx
{
protected:
	enum
	{
		PAGE_PLAYER = ET_CONTROL_NEXT,
		PAGE_SCHOOL,
	};

public:
    CSchoolWarWindow ();
	virtual	~CSchoolWarWindow ();

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	virtual void SetGlobalPos(const D3DXVECTOR2& vPos);

public:
	void	CreateSubControl ();
	CBasicTextButton*	CreateTextButton23 ( const char* szButton, UIGUID ControlID, const char* szText );

private:
	CSwPRankingDisplay*		m_pSwPRanking;
	CSwRankingDisplay*		m_pSwRanking;
	CUIControl*				m_pBackGround;
};
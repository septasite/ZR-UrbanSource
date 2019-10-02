#pragma	once

#include "../UIWindowEx.h"

class	CCharacterWindowCharStatMark : public CUIGroup
{
private:
	enum
	{
		MARK_IMAGE_UP = NO_ID + 1,
		MARK_IMAGE_DOWN,
	};


public:
	CCharacterWindowCharStatMark ();
	virtual	~CCharacterWindowCharStatMark ();

public:
	void	CreateSubControl();

public:
	virtual	void	Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void	TranslateUIMessage ( UIGUID cID, DWORD dwMsg );
	virtual	void	SetVisibleSingle ( BOOL bVisible );

public:
	void	Reset();
	void	ShowImage( bool bUp );
	bool	CheckValue( int nOrig, int nToCheck );
	bool	CheckValue( int nCheck );
	bool	CheckValueFloat( float nOrig, float nToCheck );
	bool	CheckValueFloat( float nCheck );

private:
	CUIControl*	m_pUpImage;
	CUIControl* m_pDownImage;

};
#pragma once

#include "UIGroup.h"
#include "UITextUtil.h"

class CBasicTextBox;

class CBasicButtonRadio : public CUIGroup
{
public:
static	const	float	fBUTTON_CLICK;

public:
	enum
	{
		NOT_READY	= -1,
		SIZE_TEXT_10 = 0,
		SIZE_TEXT_20 = 1,
		SIZE_TEXT_30 = 2,
		SIZE_TEXT_40 = 3,
		SIZE_TEXT_50 = 4,
		SIZE_TEXT_60 = 5,
		SIZE_TEXT_70 = 6,
		SIZE_TEXT_80 = 7,

		SIZE_TEXT_ALL = 8,
	};

public:
	CBasicButtonRadio();
	virtual ~CBasicButtonRadio();

protected:
	BOOL	m_bDown;
	BOOL	m_bMouseIn;

	union
	{
		struct { BOOL m_bDowned; };
		struct { BOOL m_bInside; };
		struct { BOOL m_bOn;	 };
		struct { BOOL m_bFlip;	 };
	};
	BOOL	m_bOnBack;

protected:
	BOOL	m_bUseDynamic;

public:
	void SetUseDynamic( BOOL bUseDynamic )				{ m_bUseDynamic = bUseDynamic; }
	BOOL IsUseDynamic()									{ return m_bUseDynamic; }

protected:
	BOOL m_bUseGlobalAction;

public:
	void SetUseGlobalAction( BOOL bUseGlobalAction )	{ m_bUseGlobalAction = bUseGlobalAction; }
	BOOL IsUseGlobalAction()							{ return m_bUseGlobalAction; }

protected:
	virtual	void	SetFlipPosition ();
	virtual	void	ResetFlipPosition ();

protected:	
	WORD	m_wFlipMode;

private:
	CUIControl*	m_pImage;
	CUIControl*	m_pImageFlip;
	CUIControl*	m_pMouseOver;
	CBasicTextBox*		m_pButtonText;

	BYTE		m_KeyCode;
	BYTE		m_KeyCodeEx;

public:
	BOOL IsFlip()						{ return m_bFlip; }
	virtual	void SetFlip( BOOL bFlip );

	void SetShortcutKey ( BYTE nKeyCode, BYTE nKeyCodeEx = NULL )
	{ m_KeyCode = nKeyCode; m_KeyCodeEx = nKeyCodeEx; }

	void Reset();

	void	CreateRadioWithText ( CD3DFontPar* pFont, int nTextBoxSize, int nTextAlign );
	void	CreateMouseOver ( char* KeyValue );
	void	SetOneLineText ( CString strTemp, D3DCOLOR dwTextColor = NS_UITEXTUTIL::ENABLE );
	
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

private:
	void	TranslateMouseMessage ( DWORD dwMsg );
};

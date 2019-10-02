//	BasicButton
//
//	최초 작성자 : 서보건
//	이후 수정자 : 성기엽
//	로그
//		[2003.11.7] - 오픈 인터페이스에 맞도록 모든 메시지 변경
//		[2003.9.29] - CUIControl --> CUIGroup으로 변경
#pragma once

#include "UIGroup.h"
#include "UITextUtil.h"

class CBasicTextBox;

class CBasicButtonText : public CUIGroup
{
public:
static	const	float	fBUTTON_CLICK;

public:
	enum
	{
		NOT_READY	= -1,
		CLICK_FLIP	= 0,
		MOUSEIN_FLIP= 1,
		KEEP_FLIP	= 2,
		RADIO_FLIP	= 3,
	};

public:
	CBasicButtonText();
	virtual ~CBasicButtonText();

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
	CUIControl*	m_pFlipControl;
	CUIControl*	m_pMouseOver;
	CBasicTextBox*		m_pButtonText;

	BYTE		m_KeyCode;
	BYTE		m_KeyCodeEx;

public:
	BOOL IsFlip()						{ return m_bFlip; }
	virtual	void SetFlip( BOOL bFlip );

	BOOL	IsVIsibleMouseOver ();
	void	SetVisibleMouseOver ( BOOL bVisible );

	void SetShortcutKey ( BYTE nKeyCode, BYTE nKeyCodeEx = NULL )
	{ m_KeyCode = nKeyCode; m_KeyCodeEx = nKeyCodeEx; }

	void Reset();

	void	CreateRanButtonBlue( CUIControl* pParent, const char* szControlKeyword, UIGUID WndID );
	void	CreateRanButtonRed( CUIControl* pParent, const char* szControlKeyword, UIGUID WndID );
	void	CreateFlip ( const char* keyvalue, WORD FlipType = CLICK_FLIP );
	void	CreateMouseOver ( char* KeyValue );
	void	CreateTextBox( char* szControlKeyword, CD3DFontPar* pFont, int nAlign );

	void	SetFlip();
	void	DoFlipUpdate ();
	void	SetOneLineText ( CString strTemp, D3DCOLOR dwTextColor = NS_UITEXTUTIL::ENABLE );
	
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

private:
	void	TranslateMouseMessage ( DWORD dwMsg );
};

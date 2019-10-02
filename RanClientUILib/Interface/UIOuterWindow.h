//	�⺻ ���� ǥ��
//
//	���� �ۼ��� : ���⿱
//	���� ������ : 
//	�α�
//		[2003.11.21]
//			@ �ۼ�
//

#pragma	once

#include "../EngineUIlib/GUInterface/UIWindow.h"

class	CBasicTextBox;

class CUIOuterWindow : public CUIWindow
{
public:
	CUIOuterWindow ();
	virtual	~CUIOuterWindow ();

public:
	virtual void TranslateUIMessage( UIGUID ControlID, DWORD dwMsg );

public:
	void	CreateBaseWindowBlackRed ( char* szWindowKeyword, char* szWindowName );

private:
	void	ResizeControl ( char* szWindowKeyword );

protected:
	CUIControl*		CreateControl ( char* szControl );
	CBasicTextBox*	CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, D3DCOLOR dwColor, int nAlign );
};
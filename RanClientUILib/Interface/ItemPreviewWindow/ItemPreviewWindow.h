#pragma	once

#include "../UIWindowEx.h"
#include "GLItem.h"
#include "GLItemDef.h"

class	CItemPreviewWindowRender;
class	CItemImage;
class	CBasicTextBox;

class	CItemPreviewWindow : public CUIWindowEx
{
private:
	enum
	{
		BUTTON_LEFT = ET_CONTROL_NEXT,
		BUTTON_RIGHT,
		ITEMSLOT_HEAD,
		ITEMSLOT_UPPER,
		ITEMSLOT_LOWER,
		ITEMSLOT_HAND,
		ITEMSLOT_FOOT,
		ITEMSLOT_WEAPON,
		ANI_CHECKBOX,
	};

public:
	CItemPreviewWindow ();
	virtual	~CItemPreviewWindow ();

public:
	void	CreateSubControl ();

private:
	CItemPreviewWindowRender*	m_pRender;
	CItemImage*					m_pSlotItem[SPREVIEWDATA::PREVIEW_SLOTS];
	CBasicTextBox*				m_pSlotText[SPREVIEWDATA::PREVIEW_SLOTS];
	CBasicButton*				m_pButtonLeft;
	CBasicButton*				m_pButtonRight;
	CBasicButton*				m_pAnimButton;
	CBasicTextBox*				m_pAnimText;

public:
	virtual	void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	virtual	void SetVisibleSingle ( BOOL bVisible );

private:

public:
	void	ClearRender();
	void	StartPreview( SITEMCUSTOM sItem );
};
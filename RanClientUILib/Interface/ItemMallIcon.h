#pragma	once

#include "../EngineUILib/GUInterface/UIGroup.h"

#include "../EngineUIlib/GUInterface/UIMan.h"
#include "GLCrowData.h"
class CItemMallIcon : public CUIGroup
{
public:
	enum
	{
		MouseOpen = NO_ID + 1,
		MENU_CLOSE_BUTTON,
	};

public:
	CItemMallIcon();
	virtual ~CItemMallIcon();

	void	CreateSubControl ();
	virtual	void	TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	void	SetItemMallIcon();

private:
	CBasicButton* m_pImage;
};
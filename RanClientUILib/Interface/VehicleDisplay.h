#pragma	once

#include "../EngineUILib/GUInterface/UIGroup.h"
#include "GLDefine.h"

class CItemImage;
class CBasicTextBox;

class	CVehicleDisplay : public CUIGroup
{
private:
	CItemImage*		m_pVehicleImage;
	CBasicTextBox*	m_pVehicleText;
	SNATIVEID		m_sNativeID;
	CString			m_sVehicleStr;
	CUIControl*		m_pDummyControl;
public:
	CVehicleDisplay ();
	virtual	~CVehicleDisplay ();

public:
	void	CreateSubControl ();
public:
	virtual void	Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
protected:
	void	SetItem ( SNATIVEID sICONINDEX, const char* szTexture );	
	void	ResetItem ();

	void SetItemNativeID ( const SNATIVEID& sNativeID )		{ m_sNativeID = sNativeID; }
	const SNATIVEID& GetItemID () const						{ return m_sNativeID; }
};
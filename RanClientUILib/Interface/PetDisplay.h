#pragma	once

#include "../EngineUILib/GUInterface/UIGroup.h"
#include "GLDefine.h"

class CItemImage;
class CBasicTextBox;

class	CPetDisplay : public CUIGroup
{
private:
	CItemImage*		m_pPetImage;
	CBasicTextBox*	m_pPetText;
	SNATIVEID		m_sNativeID;
	CString			m_sPetStr;
	CUIControl*		m_pDummyControl;
public:
	CPetDisplay ();
	virtual	~CPetDisplay ();

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
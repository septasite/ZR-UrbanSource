#pragma	once

#include "../EngineUILib/GUInterface/UIGroup.h"
#include "CharacterEnum.h"
#include "GLDefine.h"
#include "GLCharDefine.h"

class	CBasicLineBox;
class	CBasicLineBoxEx;
class	CBasicTextBoxEx;

class	CCtfRankingSlot : public CUIGroup
{
protected:
	enum
	{
		nSCHOOLMARK		= 3,
	};

	enum
	{
		ICON_CLASS_IMAGE0 = NO_ID + 1,
		ICON_CLASS_IMAGE1,
		ICON_CLASS_IMAGE2,
		ICON_CLASS_IMAGE3,
		ICON_CLASS_IMAGE4,
		ICON_CLASS_IMAGE5,
		ICON_CLASS_IMAGE6,
		ICON_CLASS_IMAGE7,
		ICON_CLASS_IMAGE8,
		ICON_CLASS_IMAGE9,
		ICON_CLASS_IMAGE10,
		ICON_CLASS_IMAGE11,
		ICON_CLASS_IMAGE12,
		ICON_CLASS_IMAGE13,
	};

public:
	CCtfRankingSlot ();
	virtual	~CCtfRankingSlot ();

public:
	void	CreateSubControl( D3DCOLOR dwColor );
	void	Init( WORD wRank, WORD wSchool, DWORD dwClass, const CString& strName, DWORD dwDamage, DWORD dwHeal, DWORD dwKill, DWORD dwDeath, WORD wResu, bool bMyRank );

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

protected:
	CUIControl*		CreateControl ( char* szControl );
	CUIControl*		CreateControl ( const char* szControl, WORD wAlignFlag );
	CBasicTextBoxEx*	CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, D3DCOLOR dwColor, int nAlign );

private:
	CBasicTextBoxEx*			m_pCTFBaseRank;
	CBasicTextBoxEx*			m_pCTFBaseCharName;
	CBasicTextBoxEx*			m_pCTFBaseKill;
	CBasicTextBoxEx*			m_pCTFBaseDeath;
	CBasicTextBoxEx*			m_pCTFBaseHeal;
	CBasicTextBoxEx*			m_pCTFBaseResu;
	CBasicTextBoxEx*			m_pCTFBaseContrib;
	CBasicTextBoxEx*			m_pCTFBaseDamage;

	CUIControl*					m_pSchoolMark[nSCHOOLMARK];
	CUIControl*					m_pClassImg[GLCI_NUM_NEWEST-2];
};
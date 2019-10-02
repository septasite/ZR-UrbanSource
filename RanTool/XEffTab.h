#ifndef __EffTab_H_
#define __EffTab_H_

/////////////////////////////////////////////////////////////////////////////
// CEffTab

#include <vector>
#include "XEffList.h"
#include "XEffSingle.h"
#include "XEffBlur.h"
#include "XEffCloneBlur.h"
#include "XEffDust.h"
#include "XEffShock.h"
#include "XEffAttribute.h"
#include "XEffArrow.h"
#include "XEffSpecular.h"
#include "XEffLevel.h"
#include "XEffEmit.h"
#include "XEffAlpha.h"
#include "XEffNeon.h"
#include "XEffMark.h"
#include "XEffNoAlpha.h"
#include "XEffReflection2.h"
#include "XEffAmbient.h"
#include "XEffDot3.h"
#include "XEffMultiTex.h"
#include "XEffGhosting.h"
#include "XEffSpecular2.h"
#include "XEffToon.h"
#include "XEffTexDiff.h"
#include "XEffParticle.h"
#include "XEffBonePos.h"
#include "XEffBoneList.h"
#include "XEffUserColor.h"
#include "XEffNormalMap.h"
#include "XEffLine2Bone.h"
#include "XEffAround.h"

enum EDITSHEETX
{
	EFF_LIST			= 0,
	EFF_SINGLE			= 1,
	EFF_BLUR			= 2,
	EFF_CLONEBLUR		= 3,
	EFF_DUST			= 4,
	EFF_SHOCK			= 5,
	EFF_ATTRIBUTE		= 6,
	EFF_ARROW			= 7,
	EFF_SPECULAR		= 8,
	EFF_LEVEL			= 9,
	EFF_EMIT			= 10,
	EFF_ALPHA			= 11,
	EFF_NEON			= 12,
	EFF_MARK			= 13,
	EFF_NOALPHA			= 14,
	EFF_REFLECTION2		= 15,
	EFF_AMBIENT			= 16,
	EFF_DOT3			= 17,
	EFF_MULTITEX		= 18,
	EFF_GHOSTING		= 19,
	EFF_SPECULAR2		= 20,
	EFF_TOON			= 21,
	EFF_TEXDIFF			= 22,
	EFF_PARTICLE		= 23,
	EFF_BONEPOSEFF		= 24,
	EFF_BONELISTEFF		= 25,
	EFF_USERCOLOR		= 26,
	EFF_NORMALMAP		= 27,
	EFF_LINE2BONE		= 28,
	EFF_AROUNDEFFECT	= 29,

	EDITSHEETX			= 30
};

enum { XCDF_CENTER, XCDF_TOPLEFT, XCDF_NONE };

class CEffTab : public CPropertySheet
{
	DECLARE_DYNAMIC(CEffTab)

public:
	CWnd*				m_pWndParent;

public:
	CEffList			m_EffList;
	CEffSingle			m_EffSingle;
	CEffBlur			m_EffBlur;
	CEffCloneBlur		m_EffCloneBlur;
	CEffDust			m_EffDust;
	CEffShock			m_EffShock;
	CEffAttribute		m_EffAttribute;
	CEffArrow			m_EffArrow;
	CEffSpecular		m_EffSpecular;
	CEffLevel			m_EffLevel;
	CEffEmit			m_EffEmit;
	CEffAlpha			m_EffAlpha;
	CEffNeon			m_EffNeon;
	CEffMark			m_EffMark;
	CEffNoAlpha			m_EffNoAlpha;
	CEffReflection2		m_EffReflection2;
	CEffAmbient			m_EffAmbient;
	CEffDot3			m_EffDot3;
	CEffMultiTex		m_EffMultiTex;
	CEffGhosting		m_EffGhosting;
	CEffSpecular2		m_EffSpecular2;
	CEffToon			m_EffToon;
	CEffTexDiff			m_EffTexDiff;
	CEffParticle		m_EffParticle;
	CEffBonePos			m_EffBonePos;
	CEffBoneList		m_EffBoneList;
	CEffUserColor		m_EffUserColor;
	CEffNormalMap		m_EffNormal;
	CEffLine2Bone		m_EffLine2Bone;
	CEffAround			m_EffAround;

	void	ClearData();

public:	
	void	ActiveEffList( GLEFFCHAR_VEC m_vecEFFECT );
	void	ActiveEffListNormal();
	void	ActiveEffSingle( DxEffCharSingle* EffSingle );
	void	ActiveEffBlur( DxEffCharBlur* EffBlur );
	void	ActiveEffCloneBlur( DxEffCharCloneBlur* EffCloneBlur );
	void	ActiveEffDust( DxEffCharDust* EffDust );
	void	ActiveEffShock( DxEffCharShock* EffShock );
	void	ActiveEffAttribute( DxEffCharAttribute* EffAttribute );
	void	ActiveEffArrow ( DxEffCharArrow* EffArrow );
	void	ActiveEffSpecular ( DxEffCharSpecular* EffSpecular );
	void	ActiveEffLevel ( DxEffCharLevel* EffLevel );
	void	ActiveEffEmit ( DxEffCharEmit* EffEmit );
	void	ActiveEffAlpha ( DxEffCharAlpha* EffAlpha );
	void	ActiveEffNeon ( DxEffCharNeon* EffNeon );
	void	ActiveEffMark ( DxEffCharMark* EffMark );
	void	ActiveEffNoAlpha ( DxEffCharNoAlpha* EffNoAlpha );
	void	ActiveEffReflection2 ( DxEffCharReflection2* EffReflection2 );
	void	ActiveEffAmbient ( DxEffCharAmbient* EffAmbient );
	void	ActiveEffDot3 ( DxEffCharDot3* EffDot3 );
	void	ActiveEffMultiTex ( DxEffCharMultiTex* EffMultiTex );
	void	ActiveEffGhosting ( DxEffCharGhosting* EffGhosting );
	void	ActiveEffSpecular2 ( DxEffCharSpecular2* EffSpecular2 );
	void	ActiveEffToon ( DxEffCharToon* EffToon );
	void	ActiveEffTexDiff ( DxEffCharTexDiff* EffTexDiff );
	void	ActiveEffParticle ( DxEffCharParticle* EffParticle );
	void	ActiveEffBonePos ( DxEffCharBonePosEff* EffBonePos );
	void	ActiveEffBoneList ( DxEffCharBoneListEff* EffBoneList );
	void	ActiveEffUserColor ( DxEffCharUserColor* EffUserColor );
	void	ActiveEffNormal ( DxEffCharNormal* EffNormal );
	void	ActiveEffLine2Bone ( DxEffCharLine2BoneEff* EffLine2Bone );
	void	ActiveEffAround ( DxCharAroundEff* EffAround );

	void	ActiveEffSingleReturn( DxEffCharSingle* EffSingle );
	void	ActiveEffBlurReturn( DxEffCharBlur* EffBlur );
	void	ActiveEffCloneBlurReturn( DxEffCharCloneBlur* EffCloneBlur );
	void	ActiveEffDustReturn( DxEffCharDust* EffDust );
	void	ActiveEffShockReturn( DxEffCharShock* EffShock );
	void	ActiveEffAttributeReturn( DxEffCharAttribute* EffAttribute );
	void	ActiveEffArrowReturn ( DxEffCharArrow* EffArrow );
	void	ActiveEffSpecularReturn ( DxEffCharSpecular* EffSpecular );
	void	ActiveEffLevelReturn ( DxEffCharLevel* EffLevel ,int nSize);
	void	ActiveEffEmitReturn ( DxEffCharEmit* EffEmit );
	void	ActiveEffAlphaReturn ( DxEffCharAlpha* EffAlpha );
	void	ActiveEffNeonReturn ( DxEffCharNeon* EffNeon ,int nSize );
	void	ActiveEffMarkReturn ( DxEffCharMark* EffMark );
	void	ActiveEffNoAlphaReturn ( DxEffCharNoAlpha* EffNoAlpha );
	void	ActiveEffReflection2Return ( DxEffCharReflection2* EffReflection2 ,int nSize );
	void	ActiveEffAmbientReturn ( DxEffCharAmbient* EffAmbient );
	void	ActiveEffDot3Return ( DxEffCharDot3* EffDot3 );
	void	ActiveEffMultiTexReturn ( DxEffCharMultiTex* EffMultiTex ,int nSize );
	void	ActiveEffGhostingReturn ( DxEffCharGhosting* EffGhosting );
	void	ActiveEffSpecular2Return ( DxEffCharSpecular2* EffSpecular2 ,int nSize );
	void	ActiveEffToonReturn ( DxEffCharToon* EffToon );
	void	ActiveEffTexDiffReturn ( DxEffCharTexDiff* EffTexDiff ,int nSize );
	void	ActiveEffParticleReturn ( DxEffCharParticle* EffParticle );
	void	ActiveEffBonePosReturn ( DxEffCharBonePosEff* EffBonePos );
	void	ActiveEffBoneListReturn ( DxEffCharBoneListEff* EffBoneList );
	void	ActiveEffUserColorReturn ( DxEffCharUserColor* EffUserColor ,int nSize);
	void	ActiveEffNormalReturn ( DxEffCharNormal* EffNormal );
	void	ActiveEffLine2BoneReturn ( DxEffCharLine2BoneEff* EffLine2Bone );
	void	ActiveEffAroundReturn ( DxCharAroundEff* EffAround );

	GLEFFCHAR_VEC GetVecEffect() {return m_EffList.GetVecEffect(); }

// Construction
public:
	CEffTab(CWnd* pParentWnd = NULL);
	CEffTab(CRect& rect, LOGFONT logfont, CWnd* pParentWnd = NULL );
	virtual ~CEffTab();

// Attributes
public:
	CRect		m_Rect;
	BOOL		m_bNoTabs;
	int			m_iDistanceFromTop;
	CFont*		m_pFont;


// Get/Set
public:
   void NoTabs() { m_bNoTabs = TRUE; }
   void SetDistanceFromTop( int iDistance ) { m_iDistanceFromTop = iDistance; }
   void ChangeDialogFont(CWnd* pWnd, CFont* pFont, int nFlag);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEffTab)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:

// Generated message map functions
protected:
	//{{AFX_MSG(CEffTab)
   afx_msg HBRUSH CtlColor(CDC* pDc, UINT uCtlColor);	
   //}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __ToolTab_H_
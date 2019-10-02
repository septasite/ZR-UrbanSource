#pragma once

#include "DxSkinPieceContainer.h"
#include "DxEffCharSingle.h"
#include "DxEffCharBlur.h"
#include "DxEffCharCloneBlur.h"
#include "DxEffCharDust.h"
#include "DxEffCharShock.h"
#include "DxEffCharAttribute.h"
#include "DxEffCharArrow.h"
#include "DxEffCharSpecular.h"
#include "DxEffCharLevel.h"
#include "DxEffCharEmit.h"
#include "DxEffCharAlpha.h"
#include "DxEffCharNeon.h"
#include "DxEffCharMark.h"
#include "DxEffCharNoAlpha.h"
#include "DxEffCharReflection2.h"
#include "DxEffCharAmbient.h"
#include "DxEffCharDot3.h"
#include "DxEffCharMultiTex.h"
#include "DxEffCharGhosting.h"
#include "DxEffCharSpecular2.h"
#include "DxEffCharToon.h"
#include "DxEffCharTexDiff.h"
#include "DxEffCharParticle.h"
#include "DxEffCharBonePosEff.h"
#include "DxEffCharBoneListEff.h"
#include "DxEffCharUserColor.h"
#include "DxEffCharNormal.h"
#include "DxEffCharLine2BoneEff.h"
#include "DxCharAroundEff.h"
// CEffList dialog
class	CEffTab;

class CEffList : public CPropertyPage
{
	DECLARE_DYNAMIC(CEffList)

public:
	CEffList(LOGFONT logfont);
	virtual ~CEffList();

// Dialog Data
	enum { IDD = IDD_XLIST };

protected:
	CEffTab*		m_pEffTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;
	bool			bAddEffect;
	int				nLastEdit;
	
public:
	CComboBox			m_cEffectType;
	CListBox			m_list_effect;
	GLEFFCHAR_VEC		m_vecEFFECT;

public:
	BOOL				UpdateListEffect();

	void				SetPieceData ( GLEFFCHAR_VEC m_vecEFFECTX );
	void				SetEffSingle ( DxEffCharSingle* EffSingleX );
	void				SetEffBlur ( DxEffCharBlur* EffBlurX );
	void				SetEffCloneBlur ( DxEffCharCloneBlur* EffCloneBlurX );
	void				SetEffDust ( DxEffCharDust* EffDustX );
	void				SetEffShock ( DxEffCharShock* EffShockX );
	void				SetEffAttribute ( DxEffCharAttribute* EffAttributeX );
	void				SetEffArrow ( DxEffCharArrow* EffArrowX );
	void				SetEffSpecular ( DxEffCharSpecular* EffSpecularX );
	void				SetEffLevel ( DxEffCharLevel* EffLevelX , int nSize);
	void				SetEffEmit ( DxEffCharEmit* EffEmitX );
	void				SetEffAlpha ( DxEffCharAlpha* EffAlphaX );
	void				SetEffNeon ( DxEffCharNeon* EffNeonX ,int nSize );
	void				SetEffMark ( DxEffCharMark* EffMarkX );
	void				SetEffNoAlpha ( DxEffCharNoAlpha* EffNoAlphaX );
	void				SetEffReflection2 ( DxEffCharReflection2* EffReflection2X ,int nSize );
	void				SetEffAmbient ( DxEffCharAmbient* EffAmbientX );
	void				SetEffDot3 ( DxEffCharDot3* EffDot3X );
	void				SetEffMultiTex ( DxEffCharMultiTex* EffMultiTexX ,int nSize );
	void				SetEffGhosting ( DxEffCharGhosting* EffGhostingX );
	void				SetEffSpecular2 ( DxEffCharSpecular2* EffSpecular2X ,int nSize );
	void				SetEffToon ( DxEffCharToon* EffToonX );
	void				SetEffTexDiff ( DxEffCharTexDiff* EffTexDiffX ,int nSize );
	void				SetEffParticle ( DxEffCharParticle* EffParticleX );
	void				SetEffBonePos ( DxEffCharBonePosEff* EffBonePosX );
	void				SetEffBoneList ( DxEffCharBoneListEff* EffBoneListX );
	void				SetEffUserColor ( DxEffCharUserColor* EffUserColorX ,int nSize);
	void				SetEffNormal ( DxEffCharNormal* EffNormalX );
	void				SetEffLine2Bone ( DxEffCharLine2BoneEff* EffLine2BoneX );
	void				SetEffAround ( DxCharAroundEff* EffAroundX );

	GLEFFCHAR_VEC		GetVecEffect() { return m_vecEFFECT; }

public:
	void			SetEffTab		( CEffTab *pEffTab ) { m_pEffTab = pEffTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedEffAdd();
	afx_msg void OnBnClickedEffEdit();
	afx_msg void OnBnClickedEffDel();
	afx_msg void OnBnClickedEffSelect();
	afx_msg void OnBnClickedEffCancel();
	afx_msg void OnBnClickedEffClear();
	afx_msg void OnBnClickedEffCopy();
};

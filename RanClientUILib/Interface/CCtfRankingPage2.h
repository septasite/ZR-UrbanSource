#pragma	once

#include "UIWindowEx.h"
#include "BasicLineBoxEx.h"

class	CBasicTextBoxEx;
class	CBasicScrollBarEx;
class	CCtfRankingSlot;

class CCtfRankingPage2 : public CUIGroup
{
protected:
	static	const	int		nSTARTLINE;
	static	const	int		nOUTOFRANGE;

protected:
	enum
	{
		nMAX_ONE_VIEW_SLOT = 10
	};

private:
	CBasicTextBoxEx*			m_pCTFBaseRank;
	CBasicTextBoxEx*			m_pCTFBaseSchool;
	CBasicTextBoxEx*			m_pCTFBaseClass;
	CBasicTextBoxEx*			m_pCTFBaseCharName;
	CBasicTextBoxEx*			m_pCTFBaseKill;
	CBasicTextBoxEx*			m_pCTFBaseDeath;
	CBasicTextBoxEx*			m_pCTFBaseHeal;
	CBasicTextBoxEx*			m_pCTFBaseResu;
	CBasicTextBoxEx*			m_pCTFBaseContrib;
	CBasicTextBoxEx*			m_pCTFBaseDamage;
	
	CBasicLineBoxEx*			m_pLineBoxMyRankHead;
	CBasicLineBoxEx*			m_pLineBoxMyRankTail;
	CBasicScrollBarEx*			m_pScrollBar;
	CCtfRankingSlot*			m_pRank[nMAX_ONE_VIEW_SLOT];

public:
	CCtfRankingPage2();
	~CCtfRankingPage2();

	void	CreateSubControl();
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

private:
	int		m_nStart;
	int		m_nTotal;

public:
	int		m_nRankType;

public:
	void	RefreshRankSlot();
	void	RenderView();

};
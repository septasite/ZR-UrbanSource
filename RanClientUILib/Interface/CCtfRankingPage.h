//#pragma	once
//
//#include "UIWindowEx.h"
//#include "BasicLineBoxEx.h"
//
//class	CBasicTextBoxEx;
//class	CBasicScrollBarEx;
//class	CCtfRankingSlot;
//
//class CCtfRankingPage : public CUIGroup
//{
//protected:
//	static	const	int		nSTARTLINE;
//	static	const	int		nOUTOFRANGE;
//
//protected:
//	enum
//	{
//		CTF_RESULT_SLOT_0 = NO_ID + 1,
//		CTF_RESULT_SLOT_1,CTF_RESULT_SLOT_2,CTF_RESULT_SLOT_3,
//		CTF_RESULT_SLOT_4,CTF_RESULT_SLOT_5,CTF_RESULT_SLOT_6,
//		CTF_RESULT_SLOT_7,CTF_RESULT_SLOT_8,CTF_RESULT_SLOT_9,
//		CTF_RESULT_MYSLOT,
//		CTF_SLOT_END = CTF_RESULT_SLOT_0 + 99,
//	};
//
//enum
//{
//	nMAX_ONE_VIEW_SLOT = 10
//};
//
//private:
//	CBasicTextBoxEx*			m_pCTFBaseRank;
//	CBasicTextBoxEx*			m_pCTFBaseSchool;
//	CBasicTextBoxEx*			m_pCTFBaseClass;
//	CBasicTextBoxEx*			m_pCTFBaseCharName;
//	CBasicTextBoxEx*			m_pCTFBaseKill;
//	CBasicTextBoxEx*			m_pCTFBaseDeath;
//	CBasicTextBoxEx*			m_pCTFBaseHeal;
//	CBasicTextBoxEx*			m_pCTFBaseResu;
//	CBasicTextBoxEx*			m_pCTFBaseContrib;
//	CBasicTextBoxEx*			m_pCTFBaseDamage;
//	
//	CBasicLineBoxEx*			m_pLineBoxMyRankHead;
//	CBasicLineBoxEx*			m_pLineBoxMyRankTail;
//
//	CBasicScrollBarEx*			m_pScrollBar;
//
//	CCtfRankingSlot*			m_pRankSlot[99];
//
//	CUIControl*					m_pRankSlotArrayDummy[nMAX_ONE_VIEW_SLOT];
//
//protected:
//	CCtfRankingSlot*	CreateRankSlot ( CString strKeyword, UIGUID ControlID, int index, D3DCOLOR dwColor );
//	CUIControl*	CreateControl ( const char* szControl );
//
//	void	ResetAllRankSlotRender ( int nTotal );
//	void	SetRankSlotRender ( int nStartIndex, int nTotal );
//
//public:
//	CCtfRankingPage();
//	~CCtfRankingPage();
//
//	void	CreateSubControl ( int nRankCount, bool bMyRank );
//	void	Init();
//	void	RefreshRankSlot( bool bMyRank, int wSchool );
//	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
//
//	void	SetRankCnt(int count)		{ m_nMaxRankCnt = count; }
//
//private:
//	int		m_nSlotIndex;
//	int		m_nCurPos;
//	int		m_nMaxRankCnt;
//	std::vector<int> m_vecViewRank;
//};
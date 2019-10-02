#pragma	once

#include "../EngineUILib/GUInterface/UIGroup.h"

class	CBasicTextBox;
class	CBasicButton;
class	CD3DFontPar;

class	CBasicGamePlayOption : public CUIGroup
{
protected:
	enum
	{
		HWOPTION_GAMEPLAY_CONFT_BUTTON = NO_ID + 1,		//	'�ڵ�' ��� �ź�
		HWOPTION_GAMEPLAY_TRADE_BUTTON,					//	'�ڵ�' �ŷ� �ź�
		HWOPTION_GAMEPLAY_PARTY_BUTTON,					//	'�ڵ�' ��Ƽ �ź�
		HWOPTION_GAMEPLAY_SIMPLEHP_BUTTON,				//
		HWOPTION_GAMEPLAY_FRIEND_BUTTON,				//	�ڵ� ģ�� ��û �ź�
		HWOPTION_GAMEPLAY_DEFAULTPOS_BUTTON,			//	����Ʈ ��ġ�̵�
		HWOPTION_GAMEPLAY_MOVABLE_ON_CHAT_BUTTON,		//	ä��â �������� �����̱�
		HWOPTION_GAMEPLAY_SHOW_TIP_BUTTON,				//	�� �����ֱ�
		HWOPTION_GAMEPLAY_FORCED_ATTACK_BUTTON,			// ���� ����
		HWOPTION_GAMEPLAY_NAME_DISPLAY_BUTTON,			// �̸� �׻� ǥ��
		HWOPTION_GAMEPLAY_REVIVAL_BUTTON,			// ��Ȱ ��ų ���� ����
		HWOPTION_GAMEPLAY_IDLE_ANIM_BUTTON,
		HWOPTION_GAMEPLAY_FPSLATENCY_BUTTON,			// ��Ȱ ��ų ���� ����
		HWOPTION_GAMEPLAY_AUTOTARGET_BUTTON,
		HWOPTION_GAMEPLAY_SKILLEFFECTS_BUTTON,

		HWOPTION_GAMEPLAY_CHARACTER_SIMPLIFY_BUTTON,

		HWOPTION_GAMEPLAY_ALLOW_BET_BUTTON, //add duel bet
	};

public:
	CBasicGamePlayOption ();
	virtual	~CBasicGamePlayOption ();

public:
	void	CreateSubControl ();

private:
	CBasicButton*	CreateFlipButton ( char* szButton, char* szButtonFlip, UIGUID ControlID );
	CBasicTextBox*	CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, D3DCOLOR D3DCOLOR, int nAlign );

public:
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	virtual	void SetVisibleSingle ( BOOL bVisible );

public:
	void	LoadCurrentOption();

private:
	void	LoadConft ();
	void	LoadTrade ();
	void	LoadParty ();
	void	LoadSimpleHP ();
	void	LoadFriend ();
	void	LoadMovableOnChat ();
	void	LoadShowTip ();
	void	LoadForcedAttack ();
	void	LoadNameDisplay ();
	void	LoadCharacterSimplify ();
	void	LoadRevival ();
	void	LoadIdleAnim();
	void    LoadFpsLatency();
	void    LoadAutoTarget();
	void    LoadSkillEffects();

	void	LoadAllowBet(); //add duel bet

private:
	CD3DFontPar*	m_pFont;	

private:
	CBasicButton*		m_pConftButton;
	CBasicButton*		m_pTradeButton;
	CBasicButton*		m_pPartyButton;
	CBasicButton*		m_pSimpleHPButton;
	CBasicButton*		m_pFriendButton;
	CBasicButton*		m_pMovableOnChatButton;
	CBasicButton*		m_pShowTipButton;
	CBasicButton*		m_pForcedAttackButton;
	CBasicButton*		m_pNameDisplayButton;
	CBasicButton*		m_pCharacterSimplifyButton;
	CBasicButton*		m_pRevivalButton;
	CBasicButton*		m_pIdleAnimButton;
	CBasicButton*		m_bFpsLatencyButton;
	CBasicButton*		m_bAutoTargetButton;
	CBasicButton*		m_bSkillEffectsButton;

	CBasicButton*		m_pAllowBetButton;//add duel bet

public:
	BOOL m_bConft;
	BOOL m_bTrade;
	BOOL m_bParty;
	BOOL m_bSimpleHP;
	BOOL m_bFriend;
	BOOL m_bMovableOnChat;
	BOOL m_bShowTip;
	BOOL m_bForcedAttack;
	BOOL m_bNameDisplay;
	BOOL m_bCharacterSimplify;
	BOOL m_bNon_Rebirth;
	BOOL m_bIdleAnim;
	BOOL m_bFpsLatency;
	BOOL m_bAutoTarget;
	BOOL m_bSkillEffects;

	BOOL m_bAllowBet;//add duel bet
};
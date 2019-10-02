#pragma once
#include "stdafx.h"
#include "../../EngineLib/Meshs/DxPieceDefine.h"
#include "../../EngineLib/Meshs/DxAniKeys.h"
#include "../../EngineLib/Meshs/SAnimation.h"


enum	EMAN_TYPE
{
	AN_CHAR		= 0,
	AN_ABL		= 1,
	AN_VCF		= 2,
	AN_SIZE		= 3,
};

enum	EDIT_TYPE
{
	EDIT_NONE	= 0,
	EDIT_ABL	= 1,
	EDIT_VCF	= 2,
	EDIT_SIZE	= 3,
};

enum	EDIT_MODE
{
	MODE_ROTATE	= 0,
	MODE_MOVE	= 1,
	MODE_SIZE	= 2,
};

enum	EDIT_STANCE
{
	STANCE_FREE		= 0,
	STANCE_ATTACK	= 1,
	STANCE_SIZE		= 2,
};

enum	ADJUST_RATE
{
	R1		= 0,
	R10		= 1,
	R100	= 2,
	RSIZE	= 3,
};

enum	COLOR_TYPE
{
	COLOR_HAIR	= 0,
	COLOR_ALL	= 1,
	COLOR_VCF	= 2,
	COLOR_ABL	= 3,
	COLOR_SIZE	= 4,
};

enum	LEVEL_ITEM
{
	LEVEL_SIZE		= 15,
	LEVEL_EFF		= 6,
	LEVEL_EFFSEX	= 2,
};

namespace ToolComment
{
	
	extern std::string m_AniMain[AN_TYPE_SIZE];
	extern std::string m_AniSub[AN_SUB_00_SIZE];
	extern std::string m_AniType[AN_SIZE];

	extern std::string m_EditType[EDIT_SIZE];
	extern std::string m_ABLType[PIECE_SIZE];
	extern std::string m_ModeType[MODE_SIZE];
	extern std::string m_StanceType[STANCE_SIZE];
	extern std::string m_AdjustRate[RSIZE];
	extern std::string m_ColorType[COLOR_SIZE];
	extern std::string m_LevelType[LEVEL_SIZE];
	extern std::string m_LevelEff[LEVEL_EFF];
	extern std::string m_LevelEffSex[LEVEL_EFFSEX];
};
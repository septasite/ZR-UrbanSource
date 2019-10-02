#pragma once
#include "stdafx.h"

enum EMPIECECHARS
{
	HEAD		= 0,
	UPBODY		= 1,
	LOBODY		= 2,
	GLOVE		= 3,
	RHAND		= 4,
	LHAND		= 5,
	FOOT		= 6,
	HAIR		= 7,
	HEADGEAR	= 8,
	VEHICLE		= 9,
	WING		= 10,

	REV01		= 11,
	REV02		= 12,
	REV03		= 13,

	PIECE_NSIZE	= 14
};

enum EMPEACEZONEWEAPONS
{
	WEAPON_RSLOT			= 0,
	WEAPON_WHAL_SLOT		= 1,
	WEAPON_STICK_RSLOT		= 2,
	WEAPON_R_GUN_SLOT		= 3,
	WEAPON_L_GUN_SLOT		= 4,
	WEAPON_GUN_SLOT			= 5,
	WEAPON_R_SPEAR_SLOT		= 6,
	WEAPON_L_SPEAR_SLOT		= 7,
	WEAPON_SIDE_SLOT		= 8,
	WEAPON_KUNAI_SLOT		= 9,
	WEAPON_SIZE				= 10,
};

namespace SKINTYPE_STRINGS
{
	extern std::string m_CharType[PIECE_NSIZE];
	extern std::string m_SlotType[WEAPON_SIZE];
};
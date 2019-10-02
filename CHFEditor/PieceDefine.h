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

	REV01		= 10,
	REV02		= 11,
	REV03		= 12,

	PIECE_NSIZE	= 13
};

namespace SKINTYPE_STRINGS
{
	extern std::string m_CharType[PIECE_NSIZE];
};
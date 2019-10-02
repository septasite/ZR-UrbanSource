#include "stdafx.h"
#include "PieceDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace SKINTYPE_STRINGS
{
	std::string m_CharType[PIECE_NSIZE] =
	{
		"Head",
		"Body",
		"Pant",
		"Glove",
		"Right Hand",
		"Left Hand",
		"Foot",
		"Hair",
		"Head Accecories",
		"Vehicle",
		"Wing",
		"Rev 01",
		"Rev 02",
		"Rev 03",
	};

	std::string m_SlotType[WEAPON_SIZE] =
	{
		"Sword Slot",
		"Bow Slot",
		"Stick/Wand Slot",
		"Right Gun Slot",
		"Left Gun Slot",
		"Rifle Slot",
		"Right Spear Slot",
		"Left Spear Slot",
		"Sickle Slot",
		"Shuriken Slot",
	};
};
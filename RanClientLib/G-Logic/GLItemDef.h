#ifndef GLITEMDEF_H_
#define GLITEMDEF_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "../../EngineLib/Meshs/DxPieceDefine.h"

namespace glold
{
	enum GLITEM_ATT_102
	{
		ITEMATT_NOTHING		= 0,	//	¬¯øÎπ´±‚æ¯¿Ω.
		ITEMATT_SWORD		= 1,	//	∞À∑˘.
		ITEMATT_REV00		= 2,	//	REV00
		ITEMATT_DAGGER		= 3,	//	¥‹∞À∑˘.
		ITEMATT_SPEAR		= 4,	//	√¢∑˘.
		ITEMATT_BOW			= 5,	//	»∞∑˘.
		ITEMATT_THROW		= 6,	//	≈ı√¥∑˘.
		ITEMATT_NOCARE		= 7,	//	≈∏¿‘ ªÛ∞¸ æ»«‘.	( "GLSKILL" ø°º≠ Hand π´±‚ ¡¶«— º”º∫ø°º≠ ªÁøÎµ . )
		ITEMATT_NSIZE		= 7,	//	¡æ∑˘∞πºˆ.
		ITEMATT_NEAR		= 4,	//	±Ÿ¡¢ ∞¯∞›.
	};
};

namespace glold_103
{
	enum GLITEM_ATT_103
	{
		ITEMATT_NOTHING		= 0,	//	¬¯øÅE´±‚æ¯¿Ω.

		ITEMATT_SWORD		= 1,	//	∞À.
		ITEMATT_SABER		= 2,	//	µµ.
		ITEMATT_DAGGER		= 3,	//	¥‹∞À.
		ITEMATT_SPEAR		= 4,	//	√¢.
		ITEMATT_STICK		= 5,	//	∏˘µ’¿Ã.
		ITEMATT_BOW			= 6,	//	»∞.
		ITEMATT_THROW		= 7,	//	≈ı√¥.
		ITEMATT_NOCARE		= 8,	//	≈∏¿‘ ªÛ∞¸ æ»«‘.	( "GLSKILL" ø°º≠ Hand π´±‚ ¡¶«— º”º∫ø°º≠ ªÁøÎµ . )
		ITEMATT_NSIZE		= 8,	//	¡æ∑˘∞πºˆ.
		ITEMATT_NEAR		= 5,	//	±Ÿ¡¢ ∞¯∞›.
	};
};

enum EMITEMLEVEL
{
	LEVEL_NORMAL	= 0,	
	LEVEL_RARE		= 1,	
	LEVEL_VERYRARE	= 2,
	LEVEL_EPIC		= 3,
	LEVEL_UNIQUE	= 4,	
	LEVEL_VOTE_ITEM	= 5,	
	LEVEL_PREMIUM_ITEM	= 6,
	LEVEL_CONTRIBUTION_ITEM = 7, //add contributionpoint by CNDev

	LEVEL_NSIZE		= 8	
};

enum EMITEM_FLAG
{
	TRADE_SALE			= 0x01,	//	ªÛ¡°ø° ∆«∏≈ ∞°¥….
	TRADE_EXCHANGE		= 0x02,	//	∞≥¿Œ∞£ ±≥»Ø ∞°¥….
	TRADE_THROW			= 0x04,	//	« µÂø° πˆ∏Æ±ÅE∞°¥….

	TRADE_EVENT_SGL		= 0x1000,	//	ø©∑Ø ¿Ã∫•∆Æ æ∆¿Ã≈€¡ﬂ «—∞≥ ¿ÃªÅE∏ÅE¡›∞‘ «œ±ÅE¿ß«—.

	ITEM_DISGUISE		= 0x10,	//	ƒ⁄Ω∫≈ÅE
	ITEM_TIMELMT		= 0x20,	//	Ω√»øº∫.
	
	ITEM_CHANNEL_ALL	= 0x40, //	∏µÅE√º≥Œ.

	ITEM_OWNERSHIP		= 0x200, //add ownership
	ITEM_POINT_RECOVER		= 0x400, //add point sell

	ITEM_COSTUME_COMBINE	= 0x800, //add jitem
	ITEM_NO_FAIL			= 0x1000, //add nofailups


	TRADE_GARBAGE		= 0x80, //	∆ƒºÅE∞°¥…

	TRADE_ALL		= TRADE_SALE|TRADE_EXCHANGE|TRADE_THROW//|TRADE_DETERGENT	//	//Detergent Flag SeiferXIII 10/4/12
};

enum EMITEM_HAND
{
	HAND_RIGHT		= 0x0001,	//	ø¿∏•º’ øÅE
	HAND_LEFT		= 0x0002,	//	øﬁº’ øÅE
	HAND_BOTH		= 0x0003,	//	øﬁº’, ø¿∏•º’ ∏µŒ ∞°¥….
};

//	Note : ƒ≥∏Ø≈Õ ø°¥œ∏ﬁ¿Ãº« ¡¶æ˚€Õ ∞ÅE√¿Ã ¿÷¿Ω.
//		ƒ≥∏Ø≈Õ ø°¥œ∏ﬁ¿Ãº« º±≈√«“∂ß ¬¯øÅEæ∆¿Ã≈∆ø° µ˚∂ÅEº±≈√¿ª «‘.
//
enum GLITEM_ATT
{
	ITEMATT_NOTHING		= 0,	//	¬¯øÅE´±‚æ¯¿Ω.

	ITEMATT_SWORD			= 1,	//	∞À.
	ITEMATT_SABER			= 2,	//	µµ.
	ITEMATT_SWORDSABER		= 3,	//	∞À/µµ. "∞À/µµ" ¥¬ Ω∫≈≥ø°º≠ ªÁøÎπ´±‚ »Æ¿ŒΩ√ø°∏∏ ªÁøÎµ .
	ITEMATT_DAGGER			= 4,	//	¥‹∞À.
	ITEMATT_SPEAR			= 5,	//	√¢.
	ITEMATT_STICK			= 6,	//	∏˘µ’¿Ã.
	ITEMATT_GAUNT			= 7,	//	±«.
	ITEMATT_BOW				= 8,	//	»∞.
	ITEMATT_THROW			= 9,	//	≈ı√¥.
	ITEMATT_GUN				= 10,
	
	ITEMATT_RAIL_GUN		= 11,
	ITEMATT_PORTAL_GUN		= 12,
	ITEMATT_DUAL_GUN			= 13,
	ITEMATT_RAIL_PORTAL_GUN		= 14,
	ITEMATT_SCYTHE			= 15,
	ITEMATT_DUALSPEAR		= 16,
	ITEMATT_SHURIKEN			= 17,

	ITEMATT_EXTREMEFIST		= 18,

	ITEMATT_WAND			= 19,
	ITEMATT_CUBE			= 20,
	ITEMATT_ROPE			= 21,

	ITEMATT_NOCARE			= 22,	//	≈∏¿‘ ªÛ∞¸ æ»«‘.	( "GLSKILL" ø°º≠ Hand π´±‚ ¡¶«— º”º∫ø°º≠ ªÁøÎµ . )

	/*ITEMATT_EXTREMEFIST_GAUNT = 23,
	ITEMATT_EXTREMEFIST_SWORD = 24,
	ITEMATT_EXTREMEFIST_BOW = 25,
	ITEMATT_EXTREMEFIST_SPEAR = 26,
	ITEMATT_EXTREMEFIST_GUN = 27,
	ITEMATT_EXTREMEFIST_ASSASSINWEAPS = 28,*/
	//
	ITEMATT_NEAR		= 7,
	
	ITEMATT_NSIZE		= 23,	//	????.
};

enum GLITEM_CONST
{
	ITEM_SZNAME		= 65,	//	item ¿Ã∏ß ±Ê¿Ã ¡¶«—. (NULL) πÆ¿⁄ ∆˜«‘ ±Ê¿Ã.
	ITEM_SZCOMMENT	= 256,	//	item "∞£∑´º≥∏ÅE ±Ê¿Ã ¡¶«—. (NULL) πÆ¿⁄ ∆˜«‘ ±Ê¿Ã.
	ITEM_SKILLS		= 4,	//	"Ω∫≈≥ ∆˜¿Œ∆Æ ¡ı∞°ƒ°" ∞° ∫Ÿ¿ªºÅE¿÷¥¬ ∞πºÅE
};

enum EMSUIT
{
	SUIT_HEADGEAR		= 0,
	SUIT_UPPER			= 1,
	SUIT_LOWER			= 2,
	SUIT_HAND			= 3,
	SUIT_FOOT			= 4,
	SUIT_HANDHELD		= 5,
	SUIT_NECK			= 6,
	SUIT_WRIST			= 7,
	SUIT_FINGER			= 8,
	SUIT_PET_A			= 9,	// PetData
	SUIT_PET_B			= 10,
	SUIT_VEHICLE		= 11,	// ≈ª∞Õ
	SUIT_VEHICLE_SKIN		= 12,	// ≈ª∞Õ ¡ﬂ ∫∏?EΩ∫≈≤
	SUIT_VEHICLE_PARTS_A	= 13,	// ≈ª∞Õ ¡ﬂ ∫∏?E∆ƒ?E
	SUIT_VEHICLE_PARTS_B	= 14,
	SUIT_VEHICLE_PARTS_C	= 15,
	SUIT_VEHICLE_PARTS_D	= 16,	// ≈ª∞Õ ¡ﬂ ∫∏?E∆ƒ?E
	SUIT_VEHICLE_PARTS_E	= 17,
	SUIT_VEHICLE_PARTS_F	= 18,
	SUIT_WING			= 19,
	SUIT_BELT			= 20,
	SUIT_EARRING		= 21,
	SUIT_ACCESSORY		= 22,

	SUIT_NSIZE			= 23
};

//	Note : ¬¯?Eßƒ?
enum EMSLOT
{
	SLOT_HEADGEAR	= 0,	//	∏”∏Æ æµ∞Õ
	SLOT_UPPER		= 1,	//	ªÛ√º
	SLOT_LOWER		= 2,	//	«œ√º
	SLOT_HAND		= 3,	//	º’
	SLOT_FOOT		= 4,	//	πﬂ
	SLOT_RHAND		= 5,	//	ø¿∏•º’ µµ±∏
	SLOT_LHAND		= 6,	//	øﬁº’ µµ±∏
	SLOT_NECK		= 7,	//	∏Ò∞…¿Ã
	SLOT_WRIST		= 8,	//	º’?E
	SLOT_RFINGER	= 9,	//	ø¿∏•º’ º’∞°?E
	SLOT_LFINGER	= 10,	//	øﬁº’ º’∞°?E
	SLOT_RHAND_S	= 11,	//	ø¿∏•º’ µµ±∏, ±ÿ∞≠∫Œ
	SLOT_LHAND_S	= 12,	//	øﬁº’ µµ±∏, ±ÿ∞≠∫Œ
	SLOT_VEHICLE	= 13,	//  ≈ª∞Õ 
	SLOT_WING		= 14,
	SLOT_BELT		= 15,	//  ≈ª∞Õ 
	SLOT_REARRING	= 16,	//
	SLOT_LEARRING	= 17,	//
	SLOT_ACCESSORY	= 18,	//

	SLOT_NSIZE_2	= 17,   //Size 2 normal class(i think)
	SLOT_NSIZE_S_2	= 19,	//Size 2 Extreme Class(i think)
	SLOT_HOLD		= 19,	//?????
	SLOT_TSIZE		= 20,   //All Slot Size
};

inline EMSUIT SLOT_2_SUIT ( EMSLOT emSlot )
{
	switch( emSlot )
	{
	case SLOT_HEADGEAR: return SUIT_HEADGEAR;
	case SLOT_UPPER:	return SUIT_UPPER;
	case SLOT_LOWER:	return SUIT_LOWER;
	case SLOT_HAND:		return SUIT_HAND;
	case SLOT_FOOT:		return SUIT_FOOT;
	case SLOT_RHAND:	
	case SLOT_RHAND_S:
	case SLOT_LHAND:	
	case SLOT_LHAND_S:	return SUIT_HANDHELD;

	case SLOT_NECK:		return SUIT_NECK;
	case SLOT_WRIST:	return SUIT_WRIST;
	case SLOT_RFINGER:
	case SLOT_LFINGER:	return SUIT_FINGER;
	
	case SLOT_VEHICLE:	return SUIT_VEHICLE;
	case SLOT_WING:		return SUIT_WING;
	case SLOT_BELT:		return SUIT_BELT;
	case SLOT_REARRING:
	case SLOT_LEARRING:	return SUIT_EARRING;
	case SLOT_ACCESSORY:return SUIT_ACCESSORY;
	
	default:			return SUIT_NSIZE;
	}
}

inline EMPIECECHAR SLOT_2_PIECE ( EMSLOT emSlot )
{
	switch( emSlot )
	{
	case SLOT_HEADGEAR: return PIECE_HEADGEAR;
	case SLOT_UPPER:	return PIECE_UPBODY;
	case SLOT_LOWER:	return PIECE_LOBODY;
	case SLOT_HAND:		return PIECE_GLOVE;
	case SLOT_FOOT:		return PIECE_FOOT;

	case SLOT_RHAND:	
	case SLOT_RHAND_S:	return PIECE_RHAND;
	case SLOT_LHAND:	
	case SLOT_LHAND_S:	return PIECE_LHAND;
	case SLOT_VEHICLE:	return PIECE_VEHICLE;

	case SLOT_NECK:		return PIECE_NECK;
	case SLOT_WRIST:	return PIECE_WRIST;
	case SLOT_RFINGER:	return PIECE_RFINGER;
	case SLOT_LFINGER:	return PIECE_LFINGER;
	case SLOT_WING:		return PIECE_WING; //add wing
	case SLOT_BELT:		return PIECE_BELT;
	case SLOT_REARRING:	return PIECE_REARRING;
	case SLOT_LEARRING:	return PIECE_LEARRING;
	case SLOT_ACCESSORY:return PIECE_ACCESSORY;
	

	default:			return PIECE_SIZE;
	}
}

inline EMSLOT PIECE_2_SLOT ( EMPIECECHAR emPiece )
{
	switch( emPiece )
	{
	case PIECE_HEAD:		return SLOT_HEADGEAR;
	case PIECE_UPBODY:		return SLOT_UPPER;
	case PIECE_LOBODY:		return SLOT_LOWER;
	case PIECE_GLOVE:		return SLOT_HAND;
	case PIECE_RHAND:		return SLOT_RHAND;
	case PIECE_LHAND:		return SLOT_LHAND;
	case PIECE_FOOT:		return SLOT_FOOT;
	
	case PIECE_VEHICLE:		return SLOT_VEHICLE;
	
	case PIECE_HAIR:
	case PIECE_HEADGEAR:	return SLOT_TSIZE;

	case PIECE_NECK:		return SLOT_NECK;
	case PIECE_WRIST:		return SLOT_WRIST;
	case PIECE_RFINGER:		return SLOT_RFINGER;
	case PIECE_LFINGER:		return SLOT_LFINGER;

	case PIECE_REV01:
	case PIECE_REV02:
	case PIECE_REV03:
	case PIECE_SIZE:		return SLOT_TSIZE;

	case PIECE_WING:		return SLOT_WING;
	case PIECE_BELT:		return SLOT_BELT;
	case PIECE_ACCESSORY:	return SLOT_ACCESSORY;//

	case PIECE_REARRING:	return SLOT_REARRING;//
	case PIECE_LEARRING:	return SLOT_LEARRING;//
	default:				return SLOT_TSIZE;
	}
}

/////
//add item preview
inline EMPIECECHAR SUIT_2_PIECE ( EMSUIT emSuit )
{
	switch( emSuit )
	{
	case SUIT_HEADGEAR:		return PIECE_HEAD;
	case SUIT_UPPER:		return PIECE_UPBODY;
	case SUIT_LOWER:		return PIECE_LOBODY;
	case SUIT_HAND:			return PIECE_GLOVE;
	case SUIT_FOOT:			return PIECE_FOOT;
	case SUIT_HANDHELD:		return PIECE_RHAND;
	case SUIT_NECK:			return PIECE_NECK;
	case SUIT_WRIST:		return PIECE_WRIST;
	case SUIT_FINGER:		return PIECE_RFINGER;
	case SUIT_VEHICLE:		return PIECE_SIZE;
	case SUIT_WING:			return PIECE_WING;
	case SUIT_BELT:			return PIECE_BELT;
	case SUIT_ACCESSORY:	return PIECE_ACCESSORY;

	default:			return PIECE_SIZE;
	}
}

enum EMITEM_TYPE
{
	ITEM_SUIT				= 0,

	ITEM_ARROW				= 1,	//	»≠ªÅE

	ITEM_CURE				= 2,	//	æ‡«∞.
	ITEM_SKILL				= 3,	//	Ω∫≈≥ Ω¿µÅEº≠¿ÅE
	ITEM_RECALL				= 4,	//	±Õ»Øº≠.
	ITEM_KEY				= 5,	//	¿Œ¡ıº≠ ( ø≠ºÅE).
	ITEM_GRINDING			= 6,	//	ø¨∏∂¡¶
	ITEM_CHARM				= 7,	//	∫Œ¿ÅE
	ITEM_TICKET				= 8,	//	Ω¬¬˜±«.
	ITEM_SKP_RESET			= 9,	//	Ω∫≈≥ ∆˜¿Œ∆Æ ∏Æº¬.
	ITEM_STAT_RESET			= 10,	//	Ω∫≈› ∆˜¿Œ∆Æ ∏Æº¬.
	ITEM_SKP_STAT_RESET		= 11,	//	Ω∫≈≥, Ω∫≈› ∆˜¿Œ∆Æ ∏Æº¬.

	ITEM_BOX				= 12,	//	º±π∞ ªÛ¿⁄.
	ITEM_CLEANSER			= 13,	//	ºº≈π¡¶.
	ITEM_LOUDSPEAKER		= 14,	//	»Æº∫±ÅE
	ITEM_FIRECRACKER		= 15,	//	∆¯¡◊.
	ITEM_CHARACTER_CARD		= 16,	//	ƒ≥∏Ø≈Õ √ﬂ∞° ƒ´µÅE
	ITEM_INVEN_CARD			= 17,	//	¿Œ∫• »Æ¿ÅEƒ´µÅE
	ITEM_STORAGE_CARD		= 18,	//	√¢∞ÅE»Æ¿ÅEƒ´µÅE
	ITEM_STORAGE_CONNECT	= 19,	//	√¢∞ÅEø¨∞ÅEƒ´µÅE
	ITEM_PREMIUMSET			= 20,	//	«¡∏ÆπÃæÅEºº∆Æ.
	ITEM_PRIVATEMARKET		= 21,	//	∞≥¿ŒªÛ¡° ∞≥º≥ ±«∏Æ.
	ITEM_RANDOMITEM			= 22,	//	∑£¥˝ æ∆¿Ã≈∆.
	ITEM_DISJUNCTION		= 23,	//	ƒ⁄Ω∫≈ÅE∫–∏Æ.
	ITEM_HAIR				= 24,	//	«ÅE˚Ÿ∫≈∏¿œ ∫Ø∞ÅE
	ITEM_FACE				= 25,	//	æÛ±º ∫Ø∞ÅE
	ITEM_QITEM				= 26,	//	? æ∆¿Ã≈€.
	ITEM_CD					= 27,	//	CD.
	ITEM_2FRIEND			= 28,	//	ƒ£±∏ø°∞‘.
	ITEM_CLUBCALL			= 29,	//	≈¨∑¥»£√ÅE
	ITEM_HAIRSHOP			= 30,	//	«ÅE˚¥ﬁ ¿ÃøÅE«.
	ITEM_RENAME				= 31,   //  ¿Ã∏ß∫Ø∞ÅEƒ´µÅE
	ITEM_HAIR_STYLE			= 32,	//  «ÅE˚Ÿ∫≈∏¿œ
	ITEM_HAIR_COLOR			= 33,   //  «ÅE˚‡√∑Ø
	ITEM_REVIVE				= 34,	//  ±Õ»•¡÷
	ITEM_PET_CARD			= 35,	//	∆ÅEƒ´µÅE// PetData
	ITEM_PET_FOOD			= 36,	//	∆ÅE∏‘¿Ã
	ITEM_PET_RENAME			= 37,	//	∆÷ ¿Ã∏ß∫Ø∞ÅE
	ITEM_PET_COLOR			= 38,	//	∆÷ ƒ√∑Ø∫Ø∞ÅE
	ITEM_PET_STYLE			= 39,	//	∆÷ Ω∫≈∏¿œ∫Ø∞ÅE
	ITEM_PET_SKILL			= 40,	//	∆÷ Ω∫≈≥
	ITEM_SMS				= 41,	//	SMSπÆ¿⁄ πﬂº€
	ITEM_PET_REVIVE			= 42,	//	∆÷ ∫Œ»∞ƒ´µÅE
	ITEM_ANTI_DISAPPEAR 	= 43,	//	º“πÊ¡÷(º“∏ÅEÊ¡ÅE
	ITEM_REMODEL			= 44,	//	∞≥¡∂ ±‚¥…
	ITEM_VEHICLE			= 45,	//	≈ª∞Õ
	ITEM_VEHICLE_OIL		= 46,	//  ≈ª∞Õ ±‚∏ß
	ITEM_VIETNAM_ITEMGET	= 47,	//  ∫£∆Æ≥≤ ≈Ω¥– πÊ¡ÅEæ∆¿Ã≈€ »πµÅE
	ITEM_VIETNAM_EXPGET		= 48,	//  ∫£∆Æ≥≤ ≈Ω¥– πÊ¡ÅE∞Ê«Ëƒ° »πµÅE
	ITEM_GENDER_CHANGE		= 49,	//  º∫∫∞ ∫Ø∞ÅEƒ´µÅE
	ITEM_GARBAGE_CARD		= 50,	//	»ﬁ¡ˆ≈ÅEƒ´µÅE
	ITEM_TELEPORT_CARD		= 51,	//	º“»Øº≠	
	ITEM_PET_SKIN_PACK  	= 52,	//  ∆ÅEΩ∫≈≤ ∆—
	ITEM_FACE_STYLE			= 53,	//	æÛ±ºΩ∫≈∏¿œ
	ITEM_TAXI_CARD			= 54,	//	≈√Ω√ƒ´µÅE
	ITEM_MATERIALS			= 55,	//	¿Á∑·æ∆¿Ã≈€
	ITEM_NPC_RECALL			= 56,	//	NPCº“»Ø ƒ´µÅE
	//add gun item test
	ITEM_BULLET				= 57,	//	add bullet

	ITEM_DIGEST				= 58,	//jdev pending
	ITEM_DUAL_PETCARD		= 59,
	ITEM_ROSSARY_RE			= 60,
	ITEM_ROSSART_MI			= 61,
	ITEM_BIKE_COLOR			= 62,
	ITEM_BIKE_BOOST			= 63,
	ITEM_NEW_OBLI			= 64,
	ITEM_ITEM_COLOR			= 65,
	ITEM_MAIL_CARD			= 66,
	ITEM_POINT_CARD_A		= 67,
	ITEM_POINT_CARD_B		= 68,
	ITEM_ITEM_MIX_BOOK		= 69,
	ITEM_SUMMON_CARD		= 70,	//	add summoncard
	ITEM_SLOTMATERIAL		= 71,	//	add itemslot
	ITEM_ATTACK_CON			= 72,	//	add itemslot
	ITEM_SEALED_CARD		= 73,
	ITEM_WRAPPER			= 74,
	ITEM_WRAPPER_BOX		= 75,
	ITEM_DROP_CARD		    = 76, //nondrop card Eduj
	ITEM_NONDROP_CARD		= 77, //nondrop card Eduj
	ITEM_SCHOOL_CHANGE_SG	= 78,
	ITEM_SCHOOL_CHANGE_MP	= 79,
	ITEM_SCHOOL_CHANGE_PH	= 80,
	ITEM_NSIZE				= 81,	//	¡æ∑˘∞πºˆ.
};

enum EMITEM_DRUG
{
	ITEM_DRUG_NUNE			= 0,
	ITEM_DRUG_HP			= 1,	//	√§∑¬
	ITEM_DRUG_MP			= 2,	//	±‚∑¬
	ITEM_DRUG_SP			= 3,	//	»∞∑¬

	ITEM_DRUG_HP_MP			= 4,	//	√º∑¬+±‚∑¬
	ITEM_DRUG_MP_SP			= 5,	//	√º∑¬+»∞∑¬
	ITEM_DRUG_HP_MP_SP		= 6,	//	√º∑¬+±‚∑¬+»∞∑¬
	
	ITEM_DRUG_CURE			= 7,	//	ªÛ≈¬ ¿ÃªÅEƒ°∑ÅE

	ITEM_DRUG_CALL_SCHOOL	= 8,	//	«–±≥±Õ»Ø.
	ITEM_DRUG_CALL_REGEN	= 9,	//	Ω√¿€±Õ»Ø.
	ITEM_DRUG_CALL_LASTCALL	= 10,	//	¡˜¿ÅEÕ»Ø.
	ITEM_DRUG_CALL_REVIVE	= 11,	//	∫Œ»∞±‚¥….

	ITEM_DRUG_HP_CURE		= 12,	// √º∑¬+¿ÃªÛƒ°∑ÅE
	ITEM_DRUG_HP_MP_SP_CURE	= 13,	// √º∑¬+±‚∑¬+»∞∑¬+¿ÃªÛƒ°∑ÅE
	ITEM_DRUG_CALL_TELEPORT	= 14,	// ∆Ø¡§∞¯∞£¿Ãµø
	ITEM_DRUG_CP			= 15,

	ITEM_DRUG_SIZE			= 16
};

enum EMITEM_ADDON
{
	EMADD_NONE		= 0,
	EMADD_HITRATE	= 1,	//	∏˙›ﬂ¿≤
	EMADD_AVOIDRATE	= 2,	//	»∏««¿≤.
	
	EMADD_DAMAGE	= 3,	//	∞¯∞›∑¬.
	EMADD_DEFENSE	= 4,	//	πÊæ˚”¬.

	EMADD_HP		= 5,	//	√§∑¬ ¡ı∞°.
	EMADD_MP		= 6,	//	∏∂≥™ ¡ı∞°.
	EMADD_SP		= 7,	//	Ω∫≈◊πÃ≥™ ¡ı∞°.

	EMADD_STATS_POW	= 8,	//	»ÅE
	EMADD_STATS_STR	= 9,	//	√º∑¬.
	EMADD_STATS_SPI	= 10,	//	¡§Ω≈.
	EMADD_STATS_DEX	= 11,	//	πŒ√∏.
	EMADD_STATS_INT	= 12,	//	¡ˆº∫.
	EMADD_STATS_STA	= 13,	//	±Ÿ∑¬.

	EMADD_PA		= 14,	//	∞›≈ıƒ°.
	EMADD_SA		= 15,	//	ªÁ∞›ƒ°.
	EMADD_MA		= 16,	//	∏∂∑¬ƒ°.

	EMADD_CP		= 17,	//add cp

	EMADD_SIZE		= 18,
};

enum EMITEM_VAR
{
	EMVAR_NONE			= 0,
	EMVAR_HP			= 1,
	EMVAR_MP			= 2,
	EMVAR_SP			= 3,
	EMVAR_AP			= 4,
	EMVAR_MOVE_SPEED	= 5,
	EMVAR_ATTACK_SPEED	= 6,
	EMVAR_CRITICAL_RATE	= 7,
	EMVAR_CRUSHING_BLOW	= 8, 
	EMVAR_CP			= 9,	//add cp
	EMVAR_CRIT_DMG		= 10,	//add critdgmc
	EMVAR_BLOW_DMG		= 11,	//add blowdmg

	EMVAR_SIZE			= 12,
};

enum EMITEM_QUESTION
{
	QUESTION_NONE			= 0,
	QUESTION_SPEED_UP		= 1,
	QUESTION_CRAZY			= 2,
	QUESTION_ATTACK_UP		= 3,
	QUESTION_EXP_UP			= 4,
	QUESTION_EXP_GET		= 5,
	QUESTION_LUCKY			= 6,
	QUESTION_BOMB			= 7,
	QUESTION_MOBGEN			= 8,

	QUESTION_SPEED_UP_M		= 9,
	QUESTION_MADNESS		= 10,
	QUESTION_ATTACK_UP_M	= 11,
	QUESTION_HEAL			= 12,

	QUESTION_SIZE			= 13
};

enum EMPK_STREAK
{
	PK_NONE					= 0,
	PK_FIRSTBLOOD			= 1,
	PK_DOUBLEKILL			= 2,
	PK_TRIPLEKILL			= 3,
	PK_ULTRAKILL			= 4,
	PK_RAMPAGE				= 5,
	PK_GODLIKE				= 6,
	
	PK_SIZE					= 7
};

enum EMCTFSTREAK
{
	CTF_CAPTURED_SG			= 0,
	CTF_CAPTURED_MP			= 1,
	CTF_CAPTURED_PHX		= 2,

	CTF_STREAK_SIZE			= 3
};

enum EMRANDOM_OPT
{
	EMR_OPT_NULL			= 0,
	EMR_OPT_DAMAGE			= 1,	//	∞¯∞›∑¬.
	EMR_OPT_DEFENSE			= 2,	//	πÊæ˚”¬.

	EMR_OPT_HITRATE			= 3,	//	∏˙›ﬂ¿≤.
	EMR_OPT_AVOIDRATE		= 4,	//	»∏««¿≤.

	EMR_OPT_HP				= 5,	//	hp ¡ı∞°.
	EMR_OPT_MP				= 6,	//	mp ¡ı∞°.
	EMR_OPT_SP				= 7,	//	sp ¡ı∞°.

	EMR_OPT_HP_INC			= 8,	//	hp ¡ı∞°¿≤.
	EMR_OPT_MP_INC			= 9,	//	mp ¡ı∞°¿≤.
	EMR_OPT_SP_INC			= 10,	//	sp ¡ı∞°¿≤.
	EMR_OPT_HMS_INC			= 11,	//	hp, mp, sp ¡ı∞°¿≤.

	EMR_OPT_GRIND_DAMAGE	= 12,	//	∞¯∞›∑¬ ø¨∏∂.
	EMR_OPT_GRIND_DEFENSE	= 13,	//	πÊæ˚”¬ ø¨∏∂.

	EMR_OPT_RANGE			= 14,	//	∞¯∞› øµø™.
	EMR_OPT_DIS_SP			= 15,	//	sp º“∏∑Æ.
	EMR_OPT_RESIST			= 16,	//	¿˙«◊.

	EMR_OPT_MOVE_SPEED		= 17,	// ¿Ãµøº”µµ ¡ı∞°

	// Add latest Random Values
	//   Latest RVs'
	// Name from GForceFX
	EMR_OPT_ATTACK_VOL		= 18,	// Attack
	EMR_OPT_DEFENSE_VOL		= 19,	// Defense
	EMR_OPT_HIT_VOL			= 20,	// Hit Rate
	EMR_OPT_AVOID_VOL		= 21,	// Avoid Rate
	EMR_OPT_POWER			= 22,	// Power
	EMR_OPT_VITALITY		= 23,	// Vitality
	EMR_OPT_SPIRIT			= 24,	// Spirit
	EMR_OPT_DEXTERITY		= 25,	// Dexterity
	EMR_OPT_STAMINA			= 26,	// Stamina
	EMR_OPT_MELEE			= 27,	// Melee
	EMR_OPT_SHOOTING		= 28,	// Missile
	EMR_OPT_ENERGY			= 29,	// Energy
	EMR_OPT_HP_REC			= 30,	// HP Potion Recover Increase Amount
	EMR_OPT_MP_REC			= 31,	// MP Potion Recover Increase Amount
	EMR_OPT_SP_REC			= 32,	// SP Potion Recover Increase Amount
	EMR_OPT_ACQUIRE_CP		= 33,	// Acquire CP for Killing

	// Juver Code
	EMR_OPT_CP				= 34,	//add cp
	EMR_OPT_CP_GAIN			= 35,	//add cp
	EMR_OPT_CRIT_DMG		= 36,	//add critdmg
	EMR_OPT_BLOW_DMG		= 37,	//add blowdmg

	EMR_OPT_SIZE			= 38
};

enum EMCOOL_TYPE
{
	EMCOOL_ITEMID	= 0,	// MID/SID
	EMCOOL_ITEMTYPE	= 1,	// æ∆¿Ã≈€ ≈∏¿‘
	EMCOOL_SIZE		= 2,	// ªÁ¿Ã¡ÅE
};

struct SRANDOM_OPT
{
	WORD	wTYPE;
	short	nVALUE;

	SRANDOM_OPT()
		: wTYPE( EMR_OPT_NULL )
		, nVALUE( 0 )
	{
	}

	float get_float()	{ return nVALUE * 0.01f; }
	float get_int()		{ return nVALUE; }
};

#define USAGE_RANDOM_OPT_SE
#ifdef USAGE_RANDOM_OPT_SE
//#ifdef DAUMTESTPARAM	// «—±π ≈◊º∑ø°º≠∏∏ 2¬ÅE∑£¥˝ ø…º« ∆ƒ¿œ ªÁøÅE( ¡ÿ«ÅE)
	struct SRANDOM_OPT_SECTION
	{
		float	fRATE;	// ±∏∞£∫∞ πﬂª˝ »Æ∑ÅE
		float	fHIGH;	// ∞™ √÷¥ÅE
		float	fLOW;	// ∞™ √÷º“

		SRANDOM_OPT_SECTION()
			: fRATE( 0.0f )
			, fHIGH( 0.0f )
			, fLOW( 0.0f )
		{
		}
	};

	struct SRANDOM_OPT_SET
	{
		float					fRATE;	// º≥¡§µ» ø…º«¥ÅEπﬂª˝ »Æ∑ÅE
		WORD					wTYPE;	// ø…º« ¡æ∑ÅE
		WORD					wSECT;	// ±∏∞£ ºÅE
		SRANDOM_OPT_SECTION*	pSECT;	// ±∏∞£

		SRANDOM_OPT_SET()
			: fRATE( 0.0f )
			, wTYPE( EMR_OPT_NULL )
			, wSECT( 0 )
			, pSECT( NULL )
		{
		}

		~SRANDOM_OPT_SET()
		{
			SAFE_DELETE_ARRAY( pSECT );
		}
	};

	struct SRANDOM_GEN
	{
		enum { MAX_SET = 15, MAX_OPT = 4 };

		float			fRATE;				// ∑£¥˝ ø…º« πﬂª˝ »Æ∑ÅE
		DWORD			dwSET_NUM;			// º≥¡§µ» ∑£¥˝ ø…º« ∞πºÅE
		float			fD_point;			// ∞≥¡∂ Ω√ º“∏ÅE“ ºÅE¿÷¥¬ »Æ∑ÅE
		float			fS_value;			// ∞≥¡∂ Ω√ « ø‰«— ±›æ◊ πË¿≤ ( æ∆¿Ã≈€ ∞°∞›ø° ∞ˆ«‘ )
		SRANDOM_OPT_SET	sSET[ MAX_SET ];	// º≥¡§µ» ø…º« ( √≥¿Ω ª˝º∫ Ω√ ªÁøÅE)
		SRANDOM_OPT_SET	sSETR[ MAX_SET ];	// º≥¡§µ» ø…º« ( ¿Ã»ƒ ∞≥¡∂ Ω√ ªÁøÅE)

		SRANDOM_GEN()
			: fRATE( 0.0f )
			, dwSET_NUM( 0 )
			, fD_point( 0.0f )
			, fS_value( 1.0f )
		{
		}
	};
	#undef USAGE_RANDOM_OPT_SE
#else
	struct SRANDOM_OPT_SET
	{
		float	fRATE;	// º≥¡§µ» ø…º«¥ÅEπﬂª˝ »Æ¿≤
		WORD	wTYPE;	// ø…º« ¡æ∑ÅE
		float	fLOW;	// ∞™ √÷¥ÅE
		float	fHIGH;	// ∞™ √÷º“

		SRANDOM_OPT_SET()
            : fRATE( 0 )
            , wTYPE( EMR_OPT_NULL )
			, fLOW( 0 )
			, fHIGH( 0 )
		{
		}
	};

	struct SRANDOM_GEN
	{
		enum { MAX_SET = 15, MAX_OPT = 4 };

		float			fRATE;			// ∑£¥˝ ø…º« πﬂª˝ »Æ¿≤
		DWORD			dwSET_NUM;		// º≥¡§µ» ∑£¥˝ ø…º« ∞πºÅE
		SRANDOM_OPT_SET	sSET[MAX_SET];	// º≥¡§µ» ø…º«

		float			fD_point;		// DAUMTESTPARAM æ∆¥œ∏ÅEæ≤¿Ã¡ÅEæ ¿Ω
		float			fS_value;		// DAUMTESTPARAM æ∆¥œ∏ÅEæ≤¿Ã¡ÅEæ ¿Ω

		SRANDOM_GEN()
			: fRATE( 0 )
			, dwSET_NUM( 0 )

			, fD_point( 0.0f )			// DAUMTESTPARAM æ∆¥œ∏ÅEæ≤¿Ã¡ÅEæ ¿Ω
			, fS_value( 1.0f )			// DAUMTESTPARAM æ∆¥œ∏ÅEæ≤¿Ã¡ÅEæ ¿Ω
		{
		}
	};
#endif

struct SRANDOM_DATA
{
	enum { NAME_LEN = 64 };
	char			szNAME[ NAME_LEN ];
	SRANDOM_GEN*	pSET;

	SRANDOM_DATA()
		: pSET( NULL )
	{
		memset( szNAME, 0, sizeof(char) * NAME_LEN );
	}
};

struct SRANDOM_DATA_OPER
{
	bool operator() ( const SRANDOM_DATA &lvalue, const SRANDOM_DATA &rvalue )
	{
		return strcmp(lvalue.szNAME,rvalue.szNAME)<0;
	}

	bool operator() ( const SRANDOM_DATA &lvalue, const char *szNAME )
	{
		return strcmp(lvalue.szNAME,szNAME)<0;
	}

	bool operator() ( const char *szNAME, const SRANDOM_DATA &rvalue )
	{
		return strcmp(szNAME,rvalue.szNAME)<0;
	}
};

enum EMGRINDING_CLASS
{
	EMGRINDING_CLASS_ARM	= 0,
	EMGRINDING_CLASS_CLOTH	= 1,

	EMGRINDING_CLASS_SIZE	= 2,
};

enum EMGRINDING_TYPE
{
	EMGRINDING_NUNE				= 0,

	EMGRINDING_DAMAGE			= 1,
	EMGRINDING_DEFENSE			= 2,

	EMGRINDING_RESIST_FIRE		= 3,
	EMGRINDING_RESIST_ICE		= 4,
	EMGRINDING_RESIST_ELEC		= 5,
	EMGRINDING_RESIST_POISON	= 6,
	EMGRINDING_RESIST_SPIRIT	= 7,
	
	EMGRINDING_NSIZE			= 8
};

enum EMGRINDER_TYPE
{
	EMGRINDER_NORMAL			= 0,
	EMGRINDER_HIGH				= 1,
	EMGRINDER_TOP				= 2,

	EMGRINDER_SIZE				= 3,
};

enum EMGRINDING_RS_FLAGS
{
	EMGRINDING_RS_FIRE		= 0x01,
	EMGRINDING_RS_ICE		= 0x02,
	EMGRINDING_RS_ELECTRIC	= 0x04,
	EMGRINDING_RS_POISON	= 0x08,
	EMGRINDING_RS_SPIRIT	= 0x10,

	EMGRINDING_RS_NSIZE		= 5,
	EMGRINDING_NO			= 2,
	EMGRINDING_RS_ALL		= (EMGRINDING_RS_FIRE|EMGRINDING_RS_ICE|EMGRINDING_RS_ELECTRIC|EMGRINDING_RS_POISON|EMGRINDING_RS_SPIRIT)
};

enum EMGRINDING_RS_INDEX
{
	EMGRINDING_RS_FIRE_INDEX		= 0,
	EMGRINDING_RS_ICE_INDEX			= 1,
	EMGRINDING_RS_ELECTRIC_INDEX	= 2,
	EMGRINDING_RS_POISON_INDEX		= 3,
	EMGRINDING_RS_SPIRIT_INDEX		= 4,

	EMGRINDING_RS_INDEX_NSIZE		= 5
};

EMGRINDING_RS_INDEX	GrindRsClassToIndex ( const EMGRINDING_RS_FLAGS emClass );
EMGRINDING_RS_FLAGS	GrindIndexToRsClass ( const EMGRINDING_RS_INDEX	emIndex );

struct SGRIND
{
	EMGRINDING_TYPE	emTYPE;

	DWORD			dwRESIST;
	int				nMin;
	int				nMax;

	SGRIND () :
		emTYPE(EMGRINDING_NUNE),
		dwRESIST(NULL),
		nMin(0),
		nMax(0)
	{
	}
};

struct ITEM_COOLTIME
{
	enum { VERSION = 0x0001 };

	DWORD		dwID;		//	ªÁøÅE— æ∆¿Ã≈€ ID
	DWORD		dwCoolID;	//	ƒ≈∏¿” ID ( ≈∏¿‘ø° µ˚∂ÅE¥Ÿ∏ß ) 
	__time64_t	tUseTime;	//	ªÁøÅE√∞£
	__time64_t	tCoolTime;	//	ªÁøÅE°¥…«— Ω√∞£

	ITEM_COOLTIME()
		: dwID( 0 )
		, dwCoolID ( 0 )
		, tUseTime ( 0 )
		, tCoolTime ( 0 )
	{
	}
};


namespace COMMENT
{
	extern std::string ITEMLEVEL[LEVEL_NSIZE];
	extern std::string ITEMTYPE[ITEM_NSIZE];

	extern std::string ITEMSUIT[SUIT_NSIZE];
	//extern std::string ITEMSLOT[SLOT_NSIZE_S]; // ªÁøÅE»«‘.
	extern std::string ITEMATTACK[ITEMATT_NSIZE];

	extern std::string ITEMDRUG[ITEM_DRUG_SIZE];

	extern std::string ITEMADDON[EMADD_SIZE];
	
	extern std::string ITEMVAR[EMVAR_SIZE];

	extern std::string ITEMVOL[EMVAR_SIZE]; // by ∞Ê¥ÅE
	extern std::string ITEM_QUE_TYPE[QUESTION_SIZE]; // Question Item
	extern std::string ITEM_QUE_VAR1[QUESTION_SIZE];
	extern std::string ITEM_QUE_VAR2[QUESTION_SIZE];

	extern float ITEMVAR_SCALE[EMVAR_SIZE];
	bool IsITEMVAR_SCALE ( EMITEM_VAR emITEM_VAR );

	extern std::string GRINDING_TYPE[EMGRINDING_NSIZE];
	extern std::string GRINDING_RESIST[EMGRINDING_RS_NSIZE];
	extern std::string GRINDING_LEVEL[EMGRINDER_SIZE];

	extern std::string ITEM_RANDOM_OPT[EMR_OPT_SIZE];

	extern DWORD	ITEMCOLOR[LEVEL_NSIZE];

	extern std::string COOLTYPE[EMCOOL_SIZE];
};

#endif // GLITEMDEF_H_

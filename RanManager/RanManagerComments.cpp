#include "stdafx.h"
#include "RanManagerComments.h"


namespace RMComments
{
	std::string	m_PageMain[MAINPAGE_SIZE] =
	{
		_T("Page Main"),
		_T("Page User"),
		_T("Page Char"),
		_T("Page Guild"),
		_T("Page Vehicle"),
		_T("Page Pet"),
		_T("Page ItemBank"),
	};

	std::string	m_PageChar[CHARPAGE_SIZE] =
	{
		_T("CharPage Main"),
		_T("CharPage Edit"),
		_T("CharPage PutOnItems"),
		_T("CharPage Inventory"),
		_T("CharPage Skills"),
		_T("CharPage Quests"),
		_T("CharPage Vehicle"),
		_T("CharPage Pet"),
		_T("CharPage SKillSlot"),
		_T("CharPage QuickSlot"),
		_T("CharPage CoolDown"),
	};

	std::string	m_PageUser[USERPAGE_SIZE] =
	{
		_T("UserPage Main"),
		_T("UserPage New"),
		_T("UserPage Edit"),
		_T("UserPage Bank"),
		_T("UserPage Char"),
		_T("UserPage Locker"),
	};

	std::string	m_PageGuild[GUILDPAGE_SIZE] =
	{
		_T("GuildPage Main"),
		_T("GuildPage Edit"),
		_T("GuildPage Locker"),
		_T("GuildPage Member"),
		_T("GuildPage Image"),
	};

	std::string	m_PageVehicle[VEHICLEPAGE_SIZE] =
	{
		_T("VehiclePage Main"),
		_T("VehiclePage Edit"),
		_T("VehiclePage Inven"),
	};

	std::string	m_PagePet[PETPAGE_SIZE] =
	{
		_T("PetPage Main"),
		_T("PetPage Edit"),
		_T("PetPage Inven"),
		_T("PetPage Skill"),
		_T("PetPage SkillSlot"),
	};

	std::string	m_UserType[USER_TYPE_SIZE] =
	{
		_T("Normal"),
		_T("Warper"),
		_T("Game Master"),
	};

	std::string	m_SearchType[SEARCH_SIZE] =
	{
		_T("Search All"),
		_T("Search UserNum"),
		_T("Search UserName"),
		_T("Search Game Master"),
		_T("Search Warper"),
		_T("Search Online"),
	};

	std::string	m_GenType[GEN_SIZE] =
	{
		_T("Gen Default"),
		_T("Gen Init"),
		_T("Gen Shop"),
		_T("Gen NPC"),
		_T("Gen Quest"),
		_T("Gen Mob"),
		_T("Gen GMEDIT"),
		_T("Gen Old"),
		_T("Gen Billing"),
		_T("Gen GMEDIT2"),
		_T("Gen ItemMix"),
		_T("Gen Gathering"),
		_T("Gen System"),
		_T("Gen All"),
	};

	std::string	m_SearchItemType[SEARCH_ITEMSIZE] =
	{
		_T("Search None"),
		_T("Search Name"),
		_T("Search MID"),
		_T("Search SID"),
		_T("Search Item Type"),
		_T("Search Suit Type"),
		_T("Search Arms Type"),
		_T("Search Item Level"),
		_T("Search Class Req"),
	};

	std::string	m_SearchShopType[SEARCHSHOP_SIZE] =
	{
		_T("Search None"),
		_T("Search Product Num"),
		_T("Search Item MID"),
		_T("Search Item SID"),
		_T("Search Item Name"),
	};

	std::string	m_SearchChaType[SEARCH_CHASIZE] =
	{
		_T("Search All"),
		_T("Search ChaNum"),
		_T("Search UserNum"),
		_T("Search ChaName"),
		_T("Search ChaOnline"),
		_T("Search ChaDeleted"),
	};

	std::string	m_SearchGuildType[SEARCH_GUILDSIZE] =
	{
		_T("Search All"),
		_T("Search GuildNum"),
		_T("Search GuildName"),
		_T("Search GuildMaster"),
	};

	std::string	m_SearchVehicleType[SEARCH_VEHICLESIZE] =
	{
		_T("Search All"),
		_T("Search VehicleNum"),
		_T("Search Vehicle Owner Name"),
		_T("Search Vehicle Owner ChaNum"),
		_T("Search Vehicle Deleted"),
	};

	std::string	m_SearchPetType[SEARCH_PETSIZE] =
	{
		_T("Search All"),
		_T("Search PetNum"),
		_T("Search Pet Owner Name"),
		_T("Search Pet Owner ChaNum"),
		_T("Search Pet Deleted"),
	};

	std::string	m_SearchMapType[SEARCH_MAP_SIZE] =
	{
		_T("Search All"),
		_T("Search Map MID"),
		_T("Search Map SID"),
		_T("Search Map FieldID"),
		_T("Search Map Name"),
		_T("Search Map BattleZone"),
		_T("Search Map PeaceZone"),
		_T("Search Map Commission"),
		_T("Search Map PkZone"),
		_T("Search Map FreePK"),
		_T("Search Map ItemDrop"),
		_T("Search Map Move"),
		_T("Search Map Restart"),
		_T("Search Map PetActivity"),
		_T("Search Map DecreaseEXP"),
		_T("Search Map Vehicle"),
		_T("Search Map ClubBattle"),
		_T("Search Map CDM"),
		_T("Search Map RedZone"),
		_T("Search Map InstantMap"),
	};

	std::string	m_SearchFilterType[SEARCH_FILTER_SIZE] =
	{
		_T("No Filter Item Display Will Use Search Results"),
		_T("Filter Pots Display only item with item type cure"),
		_T("Filter Vehicle Display only item with item Vehicle(SRC)")
	};

	std::string	m_ClubRank[CLUBRANK_SIZE] =
	{
		_T("Rank_E"),
		_T("Rank_D"),
		_T("Rank_C"),
		_T("Rank_B"),
		_T("Rank_A"),
		_T("Rank_S"),
		_T("Rank_7"),
		_T("Rank_8"),
		_T("Rank_9"),
		_T("Rank_10"),
	};

	std::string	m_ClubStatus[CLUBSATUS_SIZE] =
	{
		_T("Active"),
		_T("Expired"),
	};

	std::string	m_CharStatus[CHARSTATUS_SIZE] =
	{
		_T("Active"),
		_T("Deleted"),
	};

	std::string	m_SearchSkillType[SEARCHSKILL_SIZE] =
	{
		_T("Search Skills All"),
		_T("Search Skills MID"),
		_T("Search Skills SID"),
		_T("Search Skills Name"),
		_T("Search Skills Brawler"),
		_T("Search Skills Swordsman"),
		_T("Search Skills Archer"),
		_T("Search Skills Shamman"),
		_T("Search Skills Extreme"),
		_T("Search Skills Gunner"),
		_T("Search Skills Assasin"),
	};

	std::string	m_SkillSlots[SKILL_SLOT_SIZE] = 
	{
		_T("Slot F1 1"),
		_T("Slot F1 2"),
		_T("Slot F1 3"),
		_T("Slot F1 4"),
		_T("Slot F1 5"),
		_T("Slot F1 6"),
		_T("Slot F1 7"),
		_T("Slot F1 8"),
		_T("Slot F1 9"),
		_T("Slot F1 0"),

		_T("Slot F2 1"),
		_T("Slot F2 2"),
		_T("Slot F2 3"),
		_T("Slot F2 4"),
		_T("Slot F2 5"),
		_T("Slot F2 6"),
		_T("Slot F2 7"),
		_T("Slot F2 8"),
		_T("Slot F2 9"),
		_T("Slot F2 0"),

		_T("Slot F3 1"),
		_T("Slot F3 2"),
		_T("Slot F3 3"),
		_T("Slot F3 4"),
		_T("Slot F3 5"),
		_T("Slot F3 6"),
		_T("Slot F3 7"),
		_T("Slot F3 8"),
		_T("Slot F3 9"),
		_T("Slot F3 0"),

		_T("Slot F4 1"),
		_T("Slot F4 2"),
		_T("Slot F4 3"),
		_T("Slot F4 4"),
		_T("Slot F4 5"),
		_T("Slot F4 6"),
		_T("Slot F4 7"),
		_T("Slot F4 8"),
		_T("Slot F4 9"),
		_T("Slot F4 0"),

		_T("Slot None"),
	};

	std::string	m_QuickSlots[QUICK_SLOT_SIZE] = 
	{
		_T("Slot Q"),
		_T("Slot W"),
		_T("Slot E"),
		_T("Slot A"),
		_T("Slot S"),
		_T("Slot D"),
	};

	std::string	m_SlotAct[SLOTACT_SIZE] = 
	{
		_T("Slot Act None"),
		_T("Slot Act Drug"),
	};
};


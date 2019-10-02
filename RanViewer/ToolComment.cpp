#include "stdafx.h"
#include "ToolComment.h"

namespace ToolComment
{
	
	std::string	m_AniMain[AN_TYPE_SIZE] =
	{
		_T("AN_Guard_N------/Bike_Stay---------/ABL_Stay"),
		_T("AN_Placid-------/Bike_Walk---------/ABL_Attack"),
		_T("AN_Walk---------/Bike_Booster"),
		_T("AN_Run----------/Bike_Run"),
		_T("AN_Attack-------/Bike_Down"),
		_T("AN_Shock--------/Bike_Shock"),
		_T("AN_Die----------/Bike_Attack"),
		_T("AN_Create-------/Bike_Skill_A"),
		_T("AN_Talk---------/Bike_Skill_B"),
		_T("AN_Skill--------/Bike_Skill_C"),
		_T("AN_Gesture------/Bike_Skill_D"),
		_T("AN_Shock_Mix----/Bike_Anim001"),
		_T("AN_Guard_L------/Bike_Anim002"),
		_T("AN_Duel_Win-----/Bike_Anim003"),
		_T("AN_Duel_Loss----/Bike_Anim004"),
		_T("AN_Special------/Bike_Anim005"),
		_T("AN_Skill_B------/Bike_Anim_None"),
		_T("AN_Skill_C"),
		_T("AN_Skill_D"),
		_T("AN_Skill_E"),
		_T("AN_Gathering"),
		_T("AN_Bike_A"),
		_T("AN_Bike_B"),
		_T("AN_Bike_C"),
		_T("AN_Bike_EV1"),
		_T("AN_Flight"),
		_T("AN_Skill_F"),
		_T("AN_Skill_G"),
		_T("AN_Skill_H")
	};

	std::string	m_AniSub[AN_SUB_00_SIZE] =
	{
		_T("Sub00----/Sub_None-----------/01_Board"),
		_T("Sub01----/Sub_OneHandSword---/01_Stand"),
		_T("Sub02----/Sub_TwoHandSword---/01_Walk"),
		_T("Sub03----/Sub_BothSword------/01_Run"),
		_T("Sub04----/Sub_Dagger---------/01_Boost"),
		_T("Sub05----/Sub_Spear----------/01_Death"),
		_T("Sub06----/Sub_Bow------------/02_Board"),
		_T("Sub07----/Sub_Throw----------/02_Stand"),
		_T("Sub08----/Sub_Mana-----------/02_Walk"),
		_T("Sub09----/Sub_BigHandSword---/02_Run"),
		_T("Sub10----/Sub_Stick----------/02_Boost"),
		_T("Sub11----/Sub_OneSaber-------/02_Death"),
		_T("Sub12----/Sub_TwoSaber"),
		_T("Sub13----/Sub_BigSaber"),
		_T("Sub14----/Sub_BothSaber"),
		_T("Sub15----/Sub_Guant"),
		_T("Sub16----/Sub_Broom"),
		_T("Sub17----/Sub_HoverBoard"),
		_T("Sub18----/Sub_DualGun"),
		_T("Sub19----/Sub_Gun"),
		_T("Sub20----/Sub_Scythe"),
		_T("Sub21----/Sub_DualSpear"),
		_T("Sub22----/Sub_Shuriken"),
		_T("Sub23----/Sub_ExtremeFist"),
		_T("Sub24----/Sub_MagicWand"),
		_T("Sub25----/Sub_Cube/Box"),
		_T("Sub26----/Sub_Rope/Whip"),
		_T("Sub27"),
		_T("Sub28"),
		_T("Sub29"),
		_T("Sub30"),
		_T("Sub31"),
		_T("Sub32"),
		_T("Sub33"),
		_T("Sub34"),
		_T("Sub35"),
		_T("Sub36"),
		_T("Sub37"),
		_T("Sub38"),
		_T("Sub39"),
		_T("Sub40"),
		_T("Sub41"),
		_T("Sub42"),
		_T("Sub43"),
		_T("Sub44"),
		_T("Sub45"),
		_T("Sub46"),
		_T("Sub47"),
		_T("Sub48"),
		_T("Sub49"),
		_T("Sub50"),
		_T("Sub51"),
		_T("Sub52"),
		_T("Sub53"),
		_T("Sub54"),
		_T("Sub55"),
		_T("Sub56"),
		_T("Sub57"),
		_T("Sub58"),
		_T("Sub59"),
		_T("Sub60"),
		_T("Sub61"),
		_T("Sub62"),
		_T("Sub63"),
		_T("Sub64"),
		_T("Sub65"),
		_T("Sub66"),
		_T("Sub67"),
		_T("Sub68"),
		_T("Sub69"),
		_T("Sub70"),
		_T("Sub71"),
		_T("Sub72"),
		_T("Sub73"),
		_T("Sub74"),
		_T("Sub75"),
		_T("Sub76"),
		_T("Sub77"),
		_T("Sub78"),
		_T("Sub79"),
		_T("Sub80"),
		_T("Sub81"),
		_T("Sub82"),
		_T("Sub83"),
		_T("Sub84"),
		_T("Sub85"),
		_T("Sub86"),
		_T("Sub87"),
		_T("Sub88"),
		_T("Sub89"),
		_T("Sub90"),
		_T("Sub91"),
		_T("Sub92"),
		_T("Sub93"),
		_T("Sub94"),
		_T("Sub95"),
		_T("Sub96"),
		_T("Sub97"),
		_T("Sub98"),
		_T("Sub99")
	};

	std::string m_AniType[AN_SIZE] = 
	{
		"CharAnim",
		"ABL Anim",
		"VCF Anim",
	};

	std::string m_EditType[EDIT_SIZE] = 
	{
		"Edit None",
		"Edit ABL",
		"Edit VCF",
	};

	std::string	m_ABLType[PIECE_SIZE] =
	{
		_T("Piece Head"),
		_T("Piece Upbody"),
		_T("Piece LowBody"),
		_T("Piece Glove"),
		_T("Piece R-Hand"),
		_T("Piece L-Hand"),
		_T("Piece Foot"),
		_T("Piece Hair"),
		_T("Piece Headgear"),
		_T("Piece Vehicle"),
		_T("Piece Wing"),
		_T("Piece Eff-UpBody"),
		_T("Piece Eff-LowBody"),
		_T("Piece Eff-Hand"),
		_T("Piece Eff-Foot"),
		_T("Piece Belt"),
		_T("Piece Accessory"),
		_T("Piece Neck"),
		_T("Piece Wrist"),
		_T("Piece R-Finger"),
		_T("Piece L-Finger"),
		_T("Piece R-Earring"),
		_T("Piece L-Earring"),
		_T("Piece REV01"),
		_T("Piece REV02"),
		_T("Piece REV03"),
	};

	std::string m_ModeType[MODE_SIZE] = 
	{
		"Rotation",
		"Position",
	};

	std::string m_StanceType[STANCE_SIZE] = 
	{
		"ABL_Free/VCF_Front",
		"ABL_Attack/VCF_Back",
	};

	std::string m_AdjustRate[RSIZE] = 
	{
		"Devide-1",
		"Devide-10",
		"Devide-100",
	};

	std::string m_ColorType[COLOR_SIZE] = 
	{
		"Color Hair",
		"Color ALL",
		"Color VCF",
		"Color ABL",
	};

	std::string m_LevelType[LEVEL_SIZE] = 
	{
		"+4",
		"+5",
		"+6",
		"+7",
		"+8",
		"+9",
		"+10",
		"+11",
		"+12",
		"+13",
		"+14",
		"+15",
		"+16",
		"+17",
		"+18",
	};

	std::string m_LevelEff[LEVEL_EFF] = 
	{
		"None",
		"Upper",
		"Lower",
		"Glove",
		"Shoes",
		"All",
	};

	std::string m_LevelEffSex[LEVEL_EFFSEX] = 
	{
		"Male",
		"Female",
	};

};

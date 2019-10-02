#ifndef DXANIKEYS_H_
#define DXANIKEYS_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//
//
//	Note : xFile 에니메이션 데이터의 구조체.
//
//
//
//
//

#define UNITANIKEY_PERSEC	(4800.0f)

// X File formation rotate key
struct SRotateKeyXFile
{
	DWORD			dwTime;
	DWORD			dwFloats;	
	float			w;
	float			x;
	float			y;
	float			z;
};

struct SScaleKeyXFile
{
	DWORD		dwTime; 
	DWORD		dwFloats;
	D3DXVECTOR3	vScale;
};

struct SPositionKeyXFile
{
	DWORD		dwTime;
	DWORD		dwFloats;	
	D3DXVECTOR3	vPos;	
};

struct SMatrixKeyXFile
{
	DWORD		dwTime;
	DWORD		dwFloats;	
	D3DXMATRIX	mat;	
};

// in memory versions
struct SRotateKey
{
	DWORD			dwTime;
	D3DXQUATERNION	quatRotate;	
};

struct SPositionKey
{
	DWORD		dwTime;
	D3DXVECTOR3	vPos;	
};

struct SScaleKey
{
	DWORD		dwTime;
	D3DXVECTOR3	vScale;	
};

struct SMatrixKey
{
	DWORD			dwTime;
	D3DXMATRIXA16	mat;

	SMatrixKey() :
		dwTime(0)
	{
	}

	~SMatrixKey()
	{
	}

	bool operator < ( const SMatrixKey &rvalue ) const
	{
		return dwTime < rvalue.dwTime;
	}
};

struct QUATCOMP
{
	DWORD dwFirst;	// x,y
	DWORD dwSecond;	// z,w

	QUATCOMP()	{}
	QUATCOMP( DWORD a, DWORD b ) :
		dwFirst(a),
		dwSecond(dwSecond)
	{
	}
};

struct SQuatPosKey
{
	DWORD			m_dwTime;
	D3DXVECTOR3		m_vScale;
	D3DXVECTOR3		m_vPos;
	QUATCOMP		m_vQuatComp;
//	D3DXQUATERNION	m_vQuat;
	

	SQuatPosKey() :
		m_dwTime(0L),
		m_vScale(0.f,0.f,0.f),
		m_vPos(0.f,0.f,0.f),
		m_vQuatComp(0,0)
//		m_vQuat(0.f,0.f,0.f,1.f)
	{
	}

	~SQuatPosKey()
	{
	}

	bool operator < ( const SQuatPosKey &rvalue ) const
	{
		return m_dwTime < rvalue.m_dwTime;
	}
};

struct SQuatPos
{
	D3DXVECTOR3		m_vScale;
	D3DXVECTOR3		m_vPos;
	D3DXQUATERNION	m_vQuat;

	SQuatPos() :
		m_vScale(1.f,1.f,1.f),
		m_vPos(0.f,0.f,0.f),
		m_vQuat(0.f,0.f,0.f,0.f)
	{
	}

	~SQuatPos()
	{
	}
};

enum EMANI_MAINTYPE
{
	AN_GUARD_N			= 0,	//	Admonish
	AN_PLACID			= 1,	//	Rest
	AN_WALK				= 2,	//	Walk
	AN_RUN				= 3,	//	Jog
	AN_ATTACK			= 4,	//	Attack
	AN_SHOCK			= 5,	//	Damage
	AN_DIE				= 6,	//	Down
	AN_CREATE			= 7,	//	Produce
	AN_TALK				= 8,	//	Dialogue
	AN_SKILL			= 9,	//	Skill
	AN_GESTURE			= 10,	//	Action
	AN_SHOCK_MIX		= 11,	//	Damage[MIX]
	AN_GUARD_L			= 12,	//	Insufficient SP
	AN_CONFT_WIN		= 13,	//	Duel Winner
	AN_CONFT_LOSS		= 14,	//	Duel Looser
	AN_SPEC				= 15,	//  Special
	AN_SKILL_B			= 16,	//	스킬.
	AN_SKILL_C			= 17,	//	스킬.
	AN_SKILL_D			= 18,	//	스킬.
	AN_SKILL_E			= 19,	//	스킬. - 극강부에 들어가는 스킬 모음. < EMANI_SUBTYPE 를 10늘이는 것보다 이걸 늘이는 것이 효율적.~! >
	AN_GATHERING		= 20,	//	채집
	AN_BIKE_A			= 21,   //  bt5
	AN_BIKE_B			= 22,   //  bt7 //sc rare
	AN_BIKE_C			= 23,   //  bt9 
	AN_BIKE_EV1			= 24,   //  scutter
	AN_FLIGHT			= 25,
	AN_SKILL_F			= 26,
	AN_SKILL_G			= 27,
	AN_SKILL_H			= 28,
	AN_FERRARI			= 29,	// Ferrari
	AN_EWAN1			= 30,
	AN_EWAN2			= 31,
	AN_EWAN3			= 32,
	AN_REARCAR			= 33,	// Rear
	AN_EWAN4			= 34,
	AN_EWAN5			= 35,
	AN_EWAN6			= 36,
	AN_EWAN7			= 37,
	AN_EWAN8			= 38,
	AN_EWAN9			= 39,
	AN_EWAN10			= 40,
	AN_EWAN11			= 41,
	AN_EWAN12			= 42,
	AN_EWAN13			= 43,
	AN_EWAN14			= 44,
	AN_EWAN15			= 45,
	AN_EWAN16			= 46,
	AN_EWAN17			= 47,
	AN_EWAN18			= 48,
	AN_EWAN19			= 49,
	AN_EWAN20			= 50,
	AN_EWAN21			= 51,
	AN_EWAN22			= 52,
	AN_EWAN23			= 53,
	AN_EWAN24			= 54,
	AN_EWAN25			= 55,
	AN_EWAN26			= 56,
	AN_EWAN27			= 57,
	AN_EWAN28			= 58,
	AN_EWAN29			= 59,
	AN_EWAN30			= 60,

	AN_NONE				= 61,
	AN_TYPE_SIZE		= 61,

	//vehicle animation (vcf)
	ANI_VEHICLE_STAY			= 0,
	ANI_VEHICLE_WALK			= 1,
	ANI_VEHICLE_BOOSTER			= 2,
	ANI_VEHICLE_RUN				= 3,
	ANI_VEHICLE_DOWN			= 4,
	ANI_VEHICLE_SHOCK			= 5,
	ANI_VEHICLE_ATTACK			= 6,
	ANI_VEHICLE_SKILL_A			= 7,
	ANI_VEHICLE_SKILL_B			= 8,
	ANI_VEHICLE_SKILL_C			= 9,
	ANI_VEHICLE_SKILL_D			= 10,
	ANI_VEHICLE_ANIM_001		= 11,
	ANI_VEHICLE_ANIM_002		= 12,
	ANI_VEHICLE_ANIM_003		= 13,
	ANI_VEHICLE_ANIM_004		= 14,
	ANI_VEHICLE_ANIM_005		= 15,
	ANI_VEHICLE_ANIM_NONE		= 16,
	ANI_VEHICLE_SIZE			= 17,

	//ABL animation (abf)
	ANI_ABL_STAY				= 0,
	ANI_ABL_ATTACK				= 1,
	ANI_ABL_SIZE				= 2,
};

enum EMANI_SUBTYPE 
{
	//modify to use official server animation system

	//character weapon animations
	AN_SUB_NONE			= 0,	//	맨손.
	AN_SUB_ONEHSWORD	= 1,	//	한손검.
	AN_SUB_TWOHSWORD	= 2,	//	양손검.
	AN_SUB_EITHERSWORD	= 3,	//	쌍검.
	AN_SUB_DAGGER		= 4,	//	단검.
	AN_SUB_SPEAR		= 5,	//	창.
	AN_SUB_BOW			= 6,	//	활.
	AN_SUB_THROW		= 7,	//	투척.
	AN_SUB_MANA			= 8,	//	마법.
	AN_SUB_BIGHSWORD	= 9,	//	양손검 대형.
	AN_SUB_STICK		= 10,	//	몽둥이.
	AN_SUB_ONESABER		= 11,	//	한손도.
	AN_SUB_TWOSABER		= 12,	//	양손도.
	AN_SUB_BIGSABER		= 13,	//	양손도 대형.
	AN_SUB_EITHERSABER	= 14,	//	쌍도.
	AN_SUB_GAUNT		= 15,	//	권법.
	AN_SUB_BROOM		= 16,	//	빗자루.
	AN_SUB_HOVERBOARD	= 17,	//	보드
	AN_SUB_DUALGUN		= 18, //dual gun
	AN_SUB_GUN			= 19, //portal ,rail gun
	AN_SUB_HAMMER		= 20, //scythe
	AN_SUB_DUALSPEAR	= 21, //dual spear
	AN_SUB_SHURIKEN		= 22, //shuriken
	AN_SUB_EXTREMEFIST	= 23, //extreme
	AN_SUB_WAND			= 24, //wand
	AN_SUB_CUBE			= 25, //rope
	AN_SUB_ROPE			= 26, //cube

	AN_SUB_SIZE			= 27,


	//character vehicle animations
	AN_SUB_VEHICLE_01_BOARD		= 0,
	AN_SUB_VEHICLE_01_STAND		= 1, //stay
	AN_SUB_VEHICLE_01_WALK		= 2, //walk
	AN_SUB_VEHICLE_01_RUN		= 3, //run
	AN_SUB_VEHICLE_01_BOOST		= 4, //boost
	AN_SUB_VEHICLE_01_DEATH		= 5, //die
	AN_SUB_VEHICLE_02_BOARD		= 6,
	AN_SUB_VEHICLE_02_STAND		= 7,
	AN_SUB_VEHICLE_02_WALK		= 8,
	AN_SUB_VEHICLE_02_RUN		= 9,
	AN_SUB_VEHICLE_02_BOOST		= 10,
	AN_SUB_VEHICLE_02_DEATH		= 11,
	AN_SUB_VEHICLE_12			= 12,
	AN_SUB_VEHICLE_13			= 13,
	AN_SUB_VEHICLE_14			= 14,
	AN_SUB_VEHICLE_15			= 15,
	AN_SUB_VEHICLE_16			= 16,
	AN_SUB_VEHICLE_17			= 17,
	AN_SUB_VEHICLE_18			= 18,
	AN_SUB_VEHICLE_19			= 19,
	AN_SUB_VEHICLE_20			= 20,
	AN_SUB_VEHICLE_21			= 21,
	AN_SUB_VEHICLE_22			= 22,
	AN_SUB_VEHICLE_23			= 23,
	AN_SUB_VEHICLE_24			= 24,
	AN_SUB_VEHICLE_25			= 25,
	AN_SUB_VEHICLE_26			= 26,
	AN_SUB_VEHICLE_27			= 27,
	AN_SUB_VEHICLE_28			= 28,
	AN_SUB_VEHICLE_29			= 29,
	AN_SUB_VEHICLE_30			= 30,
	AN_SUB_VEHICLE_31			= 31,
	AN_SUB_VEHICLE_32			= 32,
	AN_SUB_VEHICLE_33			= 33,
	AN_SUB_VEHICLE_34			= 34,
	AN_SUB_VEHICLE_35			= 35,
	AN_SUB_VEHICLE_36			= 36,
	AN_SUB_VEHICLE_37			= 37,
	AN_SUB_VEHICLE_38			= 38,
	AN_SUB_VEHICLE_39			= 39,
	AN_SUB_VEHICLE_40			= 40,
	AN_SUB_VEHICLE_41			= 41,
	AN_SUB_VEHICLE_42			= 42,
	AN_SUB_VEHICLE_43			= 43,
	AN_SUB_VEHICLE_44			= 44,
	AN_SUB_VEHICLE_45			= 45,
	AN_SUB_VEHICLE_46			= 46,
	AN_SUB_VEHICLE_47			= 47,
	AN_SUB_VEHICLE_48			= 48,
	AN_SUB_VEHICLE_49			= 49,
	AN_SUB_VEHICLE_50			= 50,
	AN_SUB_VEHICLE_51			= 51,
	AN_SUB_VEHICLE_52			= 52,
	AN_SUB_VEHICLE_53			= 53,
	AN_SUB_VEHICLE_54			= 54,
	AN_SUB_VEHICLE_55			= 55,
	AN_SUB_VEHICLE_56			= 56,
	AN_SUB_VEHICLE_57			= 57,
	AN_SUB_VEHICLE_58			= 58,
	AN_SUB_VEHICLE_59			= 59,
	AN_SUB_VEHICLE_60			= 60,
	AN_SUB_VEHICLE_61			= 61,
	AN_SUB_VEHICLE_62			= 62,
	AN_SUB_VEHICLE_63			= 63,
	AN_SUB_VEHICLE_64			= 64,
	AN_SUB_VEHICLE_65			= 65,
	AN_SUB_VEHICLE_66			= 66,
	AN_SUB_VEHICLE_67			= 67,
	AN_SUB_VEHICLE_68			= 68,
	AN_SUB_VEHICLE_69			= 69,
	AN_SUB_VEHICLE_70			= 70,
	AN_SUB_VEHICLE_71			= 71,
	AN_SUB_VEHICLE_72			= 72,
	AN_SUB_VEHICLE_73			= 73,
	AN_SUB_VEHICLE_74			= 74,
	AN_SUB_VEHICLE_75			= 75,
	AN_SUB_VEHICLE_76			= 76,
	AN_SUB_VEHICLE_77			= 77,
	AN_SUB_VEHICLE_78			= 78,
	AN_SUB_VEHICLE_79			= 79,
	AN_SUB_VEHICLE_80			= 80,
	AN_SUB_VEHICLE_81			= 81,
	AN_SUB_VEHICLE_82			= 82,
	AN_SUB_VEHICLE_83			= 83,
	AN_SUB_VEHICLE_84			= 84,
	AN_SUB_VEHICLE_85			= 85,
	AN_SUB_VEHICLE_86			= 86,
	AN_SUB_VEHICLE_87			= 87,
	AN_SUB_VEHICLE_88			= 88,
	AN_SUB_VEHICLE_89			= 89,
	AN_SUB_VEHICLE_90			= 90,
	AN_SUB_VEHICLE_91			= 91,
	AN_SUB_VEHICLE_92			= 92,
	AN_SUB_VEHICLE_93			= 93,
	AN_SUB_VEHICLE_94			= 94,
	AN_SUB_VEHICLE_95			= 95,
	AN_SUB_VEHICLE_96			= 96,
	AN_SUB_VEHICLE_97			= 97,
	AN_SUB_VEHICLE_98			= 98,
	AN_SUB_VEHICLE_99			= 99,

	AN_SUB_01_SIZE				= 100,


	//character skill animations
	AN_SUB_00			= 0,
	AN_SUB_01			= 1,
	AN_SUB_02			= 2,
	AN_SUB_03			= 3,
	AN_SUB_04			= 4,
	AN_SUB_05			= 5,
	AN_SUB_06			= 6,
	AN_SUB_07			= 7,
	AN_SUB_08			= 8,
	AN_SUB_09			= 9,
	AN_SUB_10			= 10,
	AN_SUB_11			= 11,
	AN_SUB_12			= 12,
	AN_SUB_13			= 13,
	AN_SUB_14			= 14,
	AN_SUB_15			= 15,
	AN_SUB_16			= 16,
	AN_SUB_17			= 17,
	AN_SUB_18			= 18,
	AN_SUB_19			= 19,
	AN_SUB_20			= 20,
	AN_SUB_21			= 21,
	AN_SUB_22			= 22,
	AN_SUB_23			= 23,
	AN_SUB_24			= 24,
	AN_SUB_25			= 25,
	AN_SUB_26			= 26,
	AN_SUB_27			= 27,
	AN_SUB_28			= 28,
	AN_SUB_29			= 29,
	AN_SUB_30			= 30,
	AN_SUB_31			= 31,
	AN_SUB_32			= 32,
	AN_SUB_33			= 33,
	AN_SUB_34			= 34,
	AN_SUB_35			= 35,
	AN_SUB_36			= 36,
	AN_SUB_37			= 37,
	AN_SUB_38			= 38,
	AN_SUB_39			= 39,
	AN_SUB_40			= 40,
	AN_SUB_41			= 41,
	AN_SUB_42			= 42,
	AN_SUB_43			= 43,
	AN_SUB_44			= 44,
	AN_SUB_45			= 45,
	AN_SUB_46			= 46,
	AN_SUB_47			= 47,
	AN_SUB_48			= 48,
	AN_SUB_49			= 49,
	AN_SUB_50			= 50,
	AN_SUB_51			= 51,
	AN_SUB_52			= 52,
	AN_SUB_53			= 53,
	AN_SUB_54			= 54,
	AN_SUB_55			= 55,
	AN_SUB_56			= 56,
	AN_SUB_57			= 57,
	AN_SUB_58			= 58,
	AN_SUB_59			= 59,
	AN_SUB_60			= 60,
	AN_SUB_61			= 61,
	AN_SUB_62			= 62,
	AN_SUB_63			= 63,
	AN_SUB_64			= 64,
	AN_SUB_65			= 65,
	AN_SUB_66			= 66,
	AN_SUB_67			= 67,
	AN_SUB_68			= 68,
	AN_SUB_69			= 69,
	AN_SUB_70			= 70,
	AN_SUB_71			= 71,
	AN_SUB_72			= 72,
	AN_SUB_73			= 73,
	AN_SUB_74			= 74,
	AN_SUB_75			= 75,
	AN_SUB_76			= 76,
	AN_SUB_77			= 77,
	AN_SUB_78			= 78,
	AN_SUB_79			= 79,
	AN_SUB_80			= 80,
	AN_SUB_81			= 81,
	AN_SUB_82			= 82,
	AN_SUB_83			= 83,
	AN_SUB_84			= 84,
	AN_SUB_85			= 85,
	AN_SUB_86			= 86,
	AN_SUB_87			= 87,
	AN_SUB_88			= 88,
	AN_SUB_89			= 89,
	AN_SUB_90			= 90,
	AN_SUB_91			= 91,
	AN_SUB_92			= 92,
	AN_SUB_93			= 93,
	AN_SUB_94			= 94,
	AN_SUB_95			= 95,
	AN_SUB_96			= 96,
	AN_SUB_97			= 97,
	AN_SUB_98			= 98,
	AN_SUB_99			= 99,

	AN_SUB_00_SIZE		= 100,

	//an sub 02
	AN_SUB_02_00			= 0,
	AN_SUB_02_01			= 1,
	AN_SUB_02_02			= 2,
	AN_SUB_02_03			= 3,
	AN_SUB_02_04			= 4,
	AN_SUB_02_05			= 5,
	AN_SUB_02_06			= 6,
	AN_SUB_02_07			= 7,
	AN_SUB_02_08			= 8,
	AN_SUB_02_09			= 9,
	AN_SUB_02_10			= 10,
	AN_SUB_02_11			= 11,
	AN_SUB_02_12			= 12,
	AN_SUB_02_13			= 13,
	AN_SUB_02_14			= 14,
	AN_SUB_02_15			= 15,
	AN_SUB_02_16			= 16,
	AN_SUB_02_17			= 17,
	AN_SUB_02_18			= 18,
	AN_SUB_02_19			= 19,
	AN_SUB_02_20			= 20,
	AN_SUB_02_21			= 21,
	AN_SUB_02_22			= 22,
	AN_SUB_02_23			= 23,
	AN_SUB_02_24			= 24,
	AN_SUB_02_25			= 25,
	AN_SUB_02_26			= 26,
	AN_SUB_02_27			= 27,
	AN_SUB_02_28			= 28,
	AN_SUB_02_29			= 29,
	AN_SUB_02_30			= 30,
	AN_SUB_02_31			= 31,
	AN_SUB_02_32			= 32,
	AN_SUB_02_33			= 33,
	AN_SUB_02_34			= 34,
	AN_SUB_02_35			= 35,
	AN_SUB_02_36			= 36,
	AN_SUB_02_37			= 37,
	AN_SUB_02_38			= 38,
	AN_SUB_02_39			= 39,
	AN_SUB_02_40			= 40,
	AN_SUB_02_41			= 41,
	AN_SUB_02_42			= 42,
	AN_SUB_02_43			= 43,
	AN_SUB_02_44			= 44,
	AN_SUB_02_45			= 45,
	AN_SUB_02_46			= 46,
	AN_SUB_02_47			= 47,
	AN_SUB_02_48			= 48,
	AN_SUB_02_49			= 49,
	AN_SUB_02_50			= 50,
	AN_SUB_02_51			= 51,
	AN_SUB_02_52			= 52,
	AN_SUB_02_53			= 53,
	AN_SUB_02_54			= 54,
	AN_SUB_02_55			= 55,
	AN_SUB_02_56			= 56,
	AN_SUB_02_57			= 57,
	AN_SUB_02_58			= 58,
	AN_SUB_02_59			= 59,
	AN_SUB_02_60			= 60,
	AN_SUB_02_61			= 61,
	AN_SUB_02_62			= 62,
	AN_SUB_02_63			= 63,
	AN_SUB_02_64			= 64,
	AN_SUB_02_65			= 65,
	AN_SUB_02_66			= 66,
	AN_SUB_02_67			= 67,
	AN_SUB_02_68			= 68,
	AN_SUB_02_69			= 69,
	AN_SUB_02_70			= 70,
	AN_SUB_02_71			= 71,
	AN_SUB_02_72			= 72,
	AN_SUB_02_73			= 73,
	AN_SUB_02_74			= 74,
	AN_SUB_02_75			= 75,
	AN_SUB_02_76			= 76,
	AN_SUB_02_77			= 77,
	AN_SUB_02_78			= 78,
	AN_SUB_02_79			= 79,
	AN_SUB_02_80			= 80,
	AN_SUB_02_81			= 81,
	AN_SUB_02_82			= 82,
	AN_SUB_02_83			= 83,
	AN_SUB_02_84			= 84,
	AN_SUB_02_85			= 85,
	AN_SUB_02_86			= 86,
	AN_SUB_02_87			= 87,
	AN_SUB_02_88			= 88,
	AN_SUB_02_89			= 89,
	AN_SUB_02_90			= 90,
	AN_SUB_02_91			= 91,
	AN_SUB_02_92			= 92,
	AN_SUB_02_93			= 93,
	AN_SUB_02_94			= 94,
	AN_SUB_02_95			= 95,
	AN_SUB_02_96			= 96,
	AN_SUB_02_97			= 97,
	AN_SUB_02_98			= 98,
	AN_SUB_02_99			= 99,

	AN_SUB_02_SIZE		= 100,

	//an sub 03
	AN_SUB_03_00			= 0,
	AN_SUB_03_01			= 1,
	AN_SUB_03_02			= 2,
	AN_SUB_03_03			= 3,
	AN_SUB_03_04			= 4,
	AN_SUB_03_05			= 5,
	AN_SUB_03_06			= 6,
	AN_SUB_03_07			= 7,
	AN_SUB_03_08			= 8,
	AN_SUB_03_09			= 9,
	AN_SUB_03_10			= 10,
	AN_SUB_03_11			= 11,
	AN_SUB_03_12			= 12,
	AN_SUB_03_13			= 13,
	AN_SUB_03_14			= 14,
	AN_SUB_03_15			= 15,
	AN_SUB_03_16			= 16,
	AN_SUB_03_17			= 17,
	AN_SUB_03_18			= 18,
	AN_SUB_03_19			= 19,
	AN_SUB_03_20			= 20,
	AN_SUB_03_21			= 21,
	AN_SUB_03_22			= 22,
	AN_SUB_03_23			= 23,
	AN_SUB_03_24			= 24,
	AN_SUB_03_25			= 25,
	AN_SUB_03_26			= 26,
	AN_SUB_03_27			= 27,
	AN_SUB_03_28			= 28,
	AN_SUB_03_29			= 29,
	AN_SUB_03_30			= 30,
	AN_SUB_03_31			= 31,
	AN_SUB_03_32			= 32,
	AN_SUB_03_33			= 33,
	AN_SUB_03_34			= 34,
	AN_SUB_03_35			= 35,
	AN_SUB_03_36			= 36,
	AN_SUB_03_37			= 37,
	AN_SUB_03_38			= 38,
	AN_SUB_03_39			= 39,
	AN_SUB_03_40			= 40,
	AN_SUB_03_41			= 41,
	AN_SUB_03_42			= 42,
	AN_SUB_03_43			= 43,
	AN_SUB_03_44			= 44,
	AN_SUB_03_45			= 45,
	AN_SUB_03_46			= 46,
	AN_SUB_03_47			= 47,
	AN_SUB_03_48			= 48,
	AN_SUB_03_49			= 49,
	AN_SUB_03_50			= 50,
	AN_SUB_03_51			= 51,
	AN_SUB_03_52			= 52,
	AN_SUB_03_53			= 53,
	AN_SUB_03_54			= 54,
	AN_SUB_03_55			= 55,
	AN_SUB_03_56			= 56,
	AN_SUB_03_57			= 57,
	AN_SUB_03_58			= 58,
	AN_SUB_03_59			= 59,
	AN_SUB_03_60			= 60,
	AN_SUB_03_61			= 61,
	AN_SUB_03_62			= 62,
	AN_SUB_03_63			= 63,
	AN_SUB_03_64			= 64,
	AN_SUB_03_65			= 65,
	AN_SUB_03_66			= 66,
	AN_SUB_03_67			= 67,
	AN_SUB_03_68			= 68,
	AN_SUB_03_69			= 69,
	AN_SUB_03_70			= 70,
	AN_SUB_03_71			= 71,
	AN_SUB_03_72			= 72,
	AN_SUB_03_73			= 73,
	AN_SUB_03_74			= 74,
	AN_SUB_03_75			= 75,
	AN_SUB_03_76			= 76,
	AN_SUB_03_77			= 77,
	AN_SUB_03_78			= 78,
	AN_SUB_03_79			= 79,
	AN_SUB_03_80			= 80,
	AN_SUB_03_81			= 81,
	AN_SUB_03_82			= 82,
	AN_SUB_03_83			= 83,
	AN_SUB_03_84			= 84,
	AN_SUB_03_85			= 85,
	AN_SUB_03_86			= 86,
	AN_SUB_03_87			= 87,
	AN_SUB_03_88			= 88,
	AN_SUB_03_89			= 89,
	AN_SUB_03_90			= 90,
	AN_SUB_03_91			= 91,
	AN_SUB_03_92			= 92,
	AN_SUB_03_93			= 93,
	AN_SUB_03_94			= 94,
	AN_SUB_03_95			= 95,
	AN_SUB_03_96			= 96,
	AN_SUB_03_97			= 97,
	AN_SUB_03_98			= 98,
	AN_SUB_03_99			= 99,

	AN_SUB_03_SIZE		= 100,

	//an sub fly
	AN_SUB_FLY_00			= 0,
	AN_SUB_FLY_01			= 1,
	AN_SUB_FLY_02			= 2,
	AN_SUB_FLY_03			= 3,
	AN_SUB_FLY_04			= 4,
	AN_SUB_FLY_05			= 5,
	AN_SUB_FLY_06			= 6,
	AN_SUB_FLY_07			= 7,
	AN_SUB_FLY_08			= 8,
	AN_SUB_FLY_09			= 9,


	AN_SUB_FLY		= 10,

};

#endif // DXANIKEYS_H_

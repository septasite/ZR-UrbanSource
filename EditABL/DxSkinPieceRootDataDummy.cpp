#include "stdafx.h"
#include "DxSkinPieceRootDataDummy.h"
#include "../G-Logic/GLogic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

DxSkinPieceRootDataDummy::DxSkinPieceRootDataDummy(void):
											m_dwType(0)
											,m_dwWeaponSlot(0)

											,m_bCPS(FALSE)

											,m_fRotX(0.0f)
											,m_fRotY(0.0f)
											,m_fRotZ(0.0f)

											,m_fRootX(0.0f)
											,m_fRootY(0.0f)
											,m_fRootZ(0.0f)

											,m_fRotX_F(0.0f)
											,m_fRotY_F(0.0f)
											,m_fRotZ_F(0.0f)

											,m_fRootX_F(0.0f)
											,m_fRootY_F(0.0f)
											,m_fRootZ_F(0.0f)
										
											,m_vRoot(0,0,0)
											,m_vRot(0,0,0)
											,m_vScale(0,0,0)
											,m_vRoot_F(0,0,0)
											,m_vRot_F(0,0,0)
											,m_vScale_F(0,0,0)				

{
	m_strAbf = "";
	m_strCPS = "";
	m_strSkeleton = "";
	m_strBoneLink = "";
}

DxSkinPieceRootDataDummy::~DxSkinPieceRootDataDummy(void)
{
	//DxSkinPieceDataContainer::GetInstance().CleanUp();
	//ClearAll();
}

BOOL DxSkinPieceRootDataDummy::SaveFile ( const char* szFile )
{
	char szPathName[MAX_PATH] = "";
	StringCchCopy( szPathName, MAX_PATH, DxSkinPieceDataContainer::GetInstance().GetPath() );
	StringCchCat( szPathName, MAX_PATH, szFile );

	CSerialFile SFile;
	if ( !SFile.OpenFile ( FOT_WRITE, szPathName ) )		return FALSE;

	SFile << VERSION;

	DWORD dwDummy;
	SFile << dwDummy;
	SFile << m_strAbf;
	SFile << m_strCPS;
	SFile << m_strSkeleton;
	SFile << m_strBoneLink;
	SFile << dwDummy;
	SFile << dwDummy;
	SFile << m_dwType;
	SFile << m_dwWeaponSlot;

	SFile << m_vRoot;
	SFile << m_vRot;
	SFile << m_vScale;
	SFile << m_vRoot_F;
	SFile << m_vRot_F;
	SFile << m_vScale_F;

	return TRUE;
}

BOOL DxSkinPieceRootDataDummy::LOADNEO_Ver100( basestream &SFile )
{
	//âËÅ´ä¿Åì´ÒµéÒ
	SFile >> m_strAbf;
	//âËÅ´ä¿Åì CPS
	SFile >> m_strCPS;
	//âËÅ´¡ÃÐ´Ù¡
	SFile >> m_strSkeleton;
	//âËÅ´ª×èÍ¢éÍµèÍ¡ÃÐ´Ù¡
	SFile >> m_strBoneLink;
	//µÓáË¹è§¢Í§ Piece
	SFile >> m_dwType;

	//µÓáË¹è§¢Í§ÍÒÇØ¸
	SFile >> m_dwWeaponSlot;

	SFile >> m_fRotX;
	SFile >> m_fRotY;
	SFile >> m_fRotZ;

	SFile >> m_fRootX;
	SFile >> m_fRootY;
	SFile >> m_fRootZ;

	SFile >> m_fRotX_F;
	SFile >> m_fRotY_F;
	SFile >> m_fRotZ_F;

	SFile >> m_fRootX_F;
	SFile >> m_fRootY_F;
	SFile >> m_fRootZ_F;

	if ( strcmp( m_strCPS.c_str() , _T("") ) != 0 )
	{
		m_bCPS = TRUE;
	}

	return TRUE;
}

BOOL DxSkinPieceRootDataDummy::LOAD_Ver100( basestream &SFile )
{
	DWORD dwDummy0;
	DWORD dwDummy1;

	SFile >> dwDummy0;

	SFile >> m_strAbf;
	//âËÅ´ä¿Åì CPS
	SFile >> m_strCPS;
	//âËÅ´¡ÃÐ´Ù¡
	SFile >> m_strSkeleton;
	//âËÅ´ª×èÍ¢éÍµèÍ¡ÃÐ´Ù¡
	SFile >> m_strBoneLink;

	SFile >> dwDummy1;

	SFile >> m_dwType;

	//µÓáË¹è§¢Í§ÍÒÇØ¸
	SFile >> m_dwWeaponSlot;

	SFile >> m_fRotX;
	SFile >> m_fRotY;
	SFile >> m_fRotZ;

	SFile >> m_fRootX;
	SFile >> m_fRootY;
	SFile >> m_fRootZ;

	SFile >> m_fRotX_F;
	SFile >> m_fRotY_F;
	SFile >> m_fRotZ_F;

	SFile >> m_fRootX_F;
	SFile >> m_fRootY_F;
	SFile >> m_fRootZ_F;

	if ( strcmp( m_strCPS.c_str() , _T("") ) != 0 )
	{
		m_bCPS = TRUE;
	}

	return TRUE;
}
BOOL DxSkinPieceRootDataDummy::LOAD_Ver101( basestream &SFile)
{
	DWORD dwDummy;

	SFile >> dwDummy;
	SFile >> m_strAbf;
	SFile >> m_strCPS;
	SFile >> m_strSkeleton;
	SFile >> m_strBoneLink;
	SFile >> dwDummy;
	SFile >> dwDummy;
	SFile >> m_dwType;
	SFile >> m_dwWeaponSlot;

	SFile >> m_vRoot;
	SFile >> m_vRot;
	SFile >> m_vScale;
	SFile >> m_vRoot_F;
	SFile >> m_vRot_F;
	SFile >> m_vScale_F;

	if ( strcmp( m_strCPS.c_str() , _T("") ) != 0 )
	{
		m_bCPS = TRUE;

	}
return TRUE;
}

BOOL DxSkinPieceRootDataDummy::LoadFileNeo ( const char* szFile )
{
	char szPathName[MAX_PATH] = "";
	StringCchCopy( szPathName, MAX_PATH, DxSkinPieceDataContainer::GetInstance().GetPath() );
	StringCchCat( szPathName, MAX_PATH, szFile );

	std::auto_ptr<basestream> pBStream( GLOGIC::openfile_basestream(GLOGIC::bENGLIB_ZIPFILE, 
																	GLOGIC::strSKINOBJ_ZIPFILE.c_str(), 
																	szPathName, 
																	szFile ) );

	if ( !pBStream.get() )
		return FALSE;
	basestream &SFile = *pBStream;


	DWORD dwVer;
	SFile >> dwVer;


	switch ( dwVer )
	{
	case 0x100:
		LOADNEO_Ver100( SFile );
		break;
	default:
		return FALSE;
	};

	return TRUE;
}
BOOL DxSkinPieceRootDataDummy::LoadFile( const char* szFile )
{
	char szPathName[MAX_PATH] = "";
	StringCchCopy( szPathName, MAX_PATH, DxSkinPieceDataContainer::GetInstance().GetPath() );
	StringCchCat( szPathName, MAX_PATH, szFile );

	std::auto_ptr<basestream> pBStream( GLOGIC::openfile_basestream(GLOGIC::bENGLIB_ZIPFILE, 
																	GLOGIC::strSKINOBJ_ZIPFILE.c_str(), 
																	szPathName, 
																	szFile ) );

	if ( !pBStream.get() )
		return FALSE;
	basestream &SFile = *pBStream;


	DWORD dwVer;
	SFile >> dwVer;


	switch ( dwVer )
	{
	case 0x0100:
		LOAD_Ver100( SFile );
		break;
	case 0x0101:
		LOAD_Ver101( SFile );
		break;
	default:
		return FALSE;
	};

	return TRUE;
}
namespace DUMMYABL
{
	std::string	m_CharType[PIECE_SIZE] =
	{
	_T("Piece Head"),
	_T("Piece Upbody"),
	_T("Piece LowBody"),
	_T("Piece Glove"),
	_T("Piece R-Hand"),
	_T("Piece L-Hand"),
	_T("Piece Foot"),
	_T("Pisce Hair"),
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

	std::string	m_SlotType[EMPEACE_WEAPON_SIZE] =
	{
		_T("slot_rhand"),
		_T("whal_slot"),
		_T("stick_rslot"),

		_T("r_gun_slot"),
		_T("l_gun_slot"),
		_T("gun_slot"),
		_T("r_spear_slot"),
		_T("l_spear_slot"),
		_T("side_slot"),
		_T("kunai_slot"),
	};
};



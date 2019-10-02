#include "stdafx.h"

#include "SerialFile.h"

#include "DxSkinAniMan.h"
#include "../Common/StringUtils.h"
#include "../Common/StlFunctions.h"
#include "../Common/StringFile.h"

#include "../DxEffect/Effani/DxEffAni.h"

#include <algorithm>
#include "../DxFrame/dsutil.h"
#include "../DxCommon/DxViewPort.h"
#include "../../EngineSoundLib/DxSound/DxSoundMan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace COMMENT
{
	TSTRING ANI_MAINTYPE[AN_TYPE_SIZE] =
	{
		_T("AN_GUARD_N"),
		_T("AN_PLACID"),
		_T("AN_WALK"),
		_T("AN_RUN"),
		_T("AN_ATTACK"),
		_T("AN_SHOCK"),
		_T("AN_DIE"),
		_T("AN_CREATE"),
		_T("AN_TALK"),
		_T("AN_SKILL"),
		_T("AN_GESTURE"),
		_T("AN_SHOCK_MIX"),
		_T("AN_GUARD_L"),
		_T("AN_CONFT_WIN"),
		_T("AN_CONFT_LOSS"),
		_T("AN_SPEC"),
		_T("AN_SKILL_B"),
		_T("AN_SKILL_C"),
		_T("AN_SKILL_D"),
		_T("AN_SKILL_E"),
		_T("AN_GATHERING"),
		_T("AN_BIKE_A"),
		_T("AN_BIKE_B"),
		_T("AN_BIKE_C"),
		_T("AN_BIKE_EV1"),
		_T("AN_FLIGHT"),
		_T("AN_SKILL_F"),
		_T("AN_SKILL_G"),
		_T("AN_SKILL_H"),
		_T("AN_FERRARI"),
		_T("AN_EWAN1"),
		_T("AN_EWAN2"),
		_T("AN_EWAN3"),
		_T("AN_REARCAR"),
		_T("AN_EWAN4"),
		_T("AN_EWAN5"),
		_T("AN_EWAN6"),
		_T("AN_EWAN7"),
		_T("AN_EWAN8"),
		_T("AN_EWAN9"),
		_T("AN_EWAN10"),
		_T("AN_EWAN11"),
		_T("AN_EWAN12"),
		_T("AN_EWAN13"),
		_T("AN_EWAN14"),
		_T("AN_EWAN15"),
		_T("AN_EWAN16"),
		_T("AN_EWAN17"),
		_T("AN_EWAN18"),
		_T("AN_EWAN19"),
		_T("AN_EWAN20"),
		_T("AN_EWAN21"),
		_T("AN_EWAN22"),
		_T("AN_EWAN23"),
		_T("AN_EWAN24"),
		_T("AN_EWAN25"),
		_T("AN_EWAN26"),
		_T("AN_EWAN27"),
		_T("AN_EWAN28"),
		_T("AN_EWAN29"),
		_T("AN_EWAN30")
	};

	TSTRING ANI_MAINTYPE_00[ANI_VEHICLE_SIZE] =
	{
		_T("ANI_VEHICLE_STAY"),
		_T("ANI_VEHICLE_WALK"),
		_T("ANI_VEHICLE_BOOSTER"),
		_T("ANI_VEHICLE_RUN"),
		_T("ANI_VEHICLE_DOWN"),
		_T("ANI_VEHICLE_SHOCK"),
		_T("ANI_VEHICLE_ATTACK"),
		_T("ANI_VEHICLE_SKILL_A"),
		_T("ANI_VEHICLE_SKILL_B"),
		_T("ANI_VEHICLE_SKILL_C"),
		_T("ANI_VEHICLE_SKILL_D"),
		_T("ANI_VEHICLE_ANIM_001"),
		_T("ANI_VEHICLE_ANIM_002"),
		_T("ANI_VEHICLE_ANIM_003"),
		_T("ANI_VEHICLE_ANIM_004"),
		_T("ANI_VEHICLE_ANIM_005"),
		_T("ANI_VEHICLE_ANIM_NONE")
	};

	TSTRING ANI_MAINTYPE_01[ANI_ABL_SIZE] =
	{
		_T("ANI_ABL_STAY"),
		_T("ANI_ABL_ATTACK")
	};
	
	TSTRING ANI_SUBTYPE[AN_SUB_SIZE] =

	{ //weapon animation
		_T("AN_SUB_NONE"),
		_T("AN_SUB_ONEHSWORD"),
		_T("AN_SUB_TWOHSWORD"),
		_T("AN_SUB_EITHERSWORD"),
		_T("AN_SUB_DAGGER"),
		_T("AN_SUB_SPEAR"),
		_T("AN_SUB_BOW"),
		_T("AN_SUB_THROW"),
		_T("AN_SUB_MANA"),
		_T("AN_SUB_BIGHSWORD"),
		_T("AN_SUB_STICK"),
		_T("AN_SUB_ONESABER"),
		_T("AN_SUB_TWOSABER"),
		_T("AN_SUB_BIGSABER"),
		_T("AN_SUB_EITHERSABER"),
		_T("AN_SUB_GAUNT"),
		_T("AN_SUB_BROOM"),
		_T("AN_SUB_HOVERBOARD"),
		_T("AN_SUB_GUN"),
		_T("AN_SUB_RIFLE"),
		_T("AN_SUB_HAMMER"),
		_T("AN_SUB_DUALSPEAR"),
		_T("AN_SUB_SHURIKEN"),
		_T("AN_SUB_EXTREMEFIST"),
		_T("AN_SUB_WAND"),
		_T("AN_SUB_CUBE"),
		_T("AN_SUB_ROPE")

	};

	TSTRING ANI_SUBTYPE_00[AN_SUB_00_SIZE] =
	{ //skil animations
		_T("SUB_00"),
		_T("SUB_01"),
		_T("SUB_02"),
		_T("SUB_03"),
		_T("SUB_04"),
		_T("SUB_05"),
		_T("SUB_06"),
		_T("SUB_07"),
		_T("SUB_08"),
		_T("SUB_09"),
		_T("SUB_10"),
		_T("SUB_11"),
		_T("SUB_12"),
		_T("SUB_13"),
		_T("SUB_14"),
		_T("SUB_15"),
		_T("SUB_16"),
		_T("SUB_17"),
		_T("SUB_18"),
		_T("SUB_19"),
		_T("SUB_20"),
		_T("SUB_21"),
		_T("SUB_22"),
		_T("SUB_23"),
		_T("SUB_24"),
		_T("SUB_25"),
		_T("SUB_26"),
		_T("SUB_27"),
		_T("SUB_28"),
		_T("SUB_29"),
		_T("SUB_30"),
		_T("SUB_31"),
		_T("SUB_32"),
		_T("SUB_33"),
		_T("SUB_34"),
		_T("SUB_35"),
		_T("SUB_36"),
		_T("SUB_37"),
		_T("SUB_38"),
		_T("SUB_39"),
		_T("SUB_40"),
		_T("SUB_41"),
		_T("SUB_42"),
		_T("SUB_43"),
		_T("SUB_44"),
		_T("SUB_45"),
		_T("SUB_46"),
		_T("SUB_47"),
		_T("SUB_48"),
		_T("SUB_49"),
		_T("SUB_50"),
		_T("SUB_51"),
		_T("SUB_52"),
		_T("SUB_53"),
		_T("SUB_54"),
		_T("SUB_55"),
		_T("SUB_56"),
		_T("SUB_57"),
		_T("SUB_58"),
		_T("SUB_59"),
		_T("SUB_60"),
		_T("SUB_61"),
		_T("SUB_62"),
		_T("SUB_63"),
		_T("SUB_64"),
		_T("SUB_65"),
		_T("SUB_66"),
		_T("SUB_67"),
		_T("SUB_68"),
		_T("SUB_69"),
		_T("SUB_70"),
		_T("SUB_71"),
		_T("SUB_72"),
		_T("SUB_73"),
		_T("SUB_74"),
		_T("SUB_75"),
		_T("SUB_76"),
		_T("SUB_77"),
		_T("SUB_78"),
		_T("SUB_79"),
		_T("SUB_80"),
		_T("SUB_81"),
		_T("SUB_82"),
		_T("SUB_83"),
		_T("SUB_84"),
		_T("SUB_85"),
		_T("SUB_86"),
		_T("SUB_87"),
		_T("SUB_88"),
		_T("SUB_89"),
		_T("SUB_90"),
		_T("SUB_91"),
		_T("SUB_92"),
		_T("SUB_93"),
		_T("SUB_94"),
		_T("SUB_95"),
		_T("SUB_96"),
		_T("SUB_97"),
		_T("SUB_98"),
		_T("SUB_99")
	};

	TSTRING ANI_SUBTYPE_01[AN_SUB_01_SIZE] =
	{
		_T("DriverBoard"),
		_T("DriverStand"),
		_T("DriverWalk"),
		_T("DriverRun"),
		_T("DriverBoost"),
		_T("DriverDeath"),
		_T("PassengerBoard"),
		_T("PassengerStand"),
		_T("PassengerWalk"),
		_T("PassengerRun"),
		_T("PassengerBoost"),
		_T("PassengerDeath"),
		_T("SUB_12"),
		_T("SUB_13"),
		_T("SUB_14"),
		_T("SUB_15"),
		_T("SUB_16"),
		_T("SUB_17"),
		_T("SUB_18"),
		_T("SUB_19"),
		_T("SUB_20"),
		_T("SUB_21"),
		_T("SUB_22"),
		_T("SUB_23"),
		_T("SUB_24"),
		_T("SUB_25"),
		_T("SUB_26"),
		_T("SUB_27"),
		_T("SUB_28"),
		_T("SUB_29"),
		_T("SUB_30"),
		_T("SUB_31"),
		_T("SUB_32"),
		_T("SUB_33"),
		_T("SUB_34"),
		_T("SUB_35"),
		_T("SUB_36"),
		_T("SUB_37"),
		_T("SUB_38"),
		_T("SUB_39"),
		_T("SUB_40"),
		_T("SUB_41"),
		_T("SUB_42"),
		_T("SUB_43"),
		_T("SUB_44"),
		_T("SUB_45"),
		_T("SUB_46"),
		_T("SUB_47"),
		_T("SUB_48"),
		_T("SUB_49"),
		_T("SUB_50"),
		_T("SUB_51"),
		_T("SUB_52"),
		_T("SUB_53"),
		_T("SUB_54"),
		_T("SUB_55"),
		_T("SUB_56"),
		_T("SUB_57"),
		_T("SUB_58"),
		_T("SUB_59"),
		_T("SUB_60"),
		_T("SUB_61"),
		_T("SUB_62"),
		_T("SUB_63"),
		_T("SUB_64"),
		_T("SUB_65"),
		_T("SUB_66"),
		_T("SUB_67"),
		_T("SUB_68"),
		_T("SUB_69"),
		_T("SUB_70"),
		_T("SUB_71"),
		_T("SUB_72"),
		_T("SUB_73"),
		_T("SUB_74"),
		_T("SUB_75"),
		_T("SUB_76"),
		_T("SUB_77"),
		_T("SUB_78"),
		_T("SUB_79"),
		_T("SUB_80"),
		_T("SUB_81"),
		_T("SUB_82"),
		_T("SUB_83"),
		_T("SUB_84"),
		_T("SUB_85"),
		_T("SUB_86"),
		_T("SUB_87"),
		_T("SUB_88"),
		_T("SUB_89"),
		_T("SUB_90"),
		_T("SUB_91"),
		_T("SUB_92"),
		_T("SUB_93"),
		_T("SUB_94"),
		_T("SUB_95"),
		_T("SUB_96"),
		_T("SUB_97"),
		_T("SUB_98"),
		_T("SUB_99")
	};

	TSTRING ANI_SUBTYPE_02[AN_SUB_02_SIZE] =
	{ //skil animations
		_T("SUB_00"),
		_T("SUB_01"),
		_T("SUB_02"),
		_T("SUB_03"),
		_T("SUB_04"),
		_T("SUB_05"),
		_T("SUB_06"),
		_T("SUB_07"),
		_T("SUB_08"),
		_T("SUB_09"),
		_T("SUB_10"),
		_T("SUB_11"),
		_T("SUB_12"),
		_T("SUB_13"),
		_T("SUB_14"),
		_T("SUB_15"),
		_T("SUB_16"),
		_T("SUB_17"),
		_T("SUB_18"),
		_T("SUB_19"),
		_T("SUB_20"),
		_T("SUB_21"),
		_T("SUB_22"),
		_T("SUB_23"),
		_T("SUB_24"),
		_T("SUB_25"),
		_T("SUB_26"),
		_T("SUB_27"),
		_T("SUB_28"),
		_T("SUB_29"),
		_T("SUB_30"),
		_T("SUB_31"),
		_T("SUB_32"),
		_T("SUB_33"),
		_T("SUB_34"),
		_T("SUB_35"),
		_T("SUB_36"),
		_T("SUB_37"),
		_T("SUB_38"),
		_T("SUB_39"),
		_T("SUB_40"),
		_T("SUB_41"),
		_T("SUB_42"),
		_T("SUB_43"),
		_T("SUB_44"),
		_T("SUB_45"),
		_T("SUB_46"),
		_T("SUB_47"),
		_T("SUB_48"),
		_T("SUB_49"),
		_T("SUB_50"),
		_T("SUB_51"),
		_T("SUB_52"),
		_T("SUB_53"),
		_T("SUB_54"),
		_T("SUB_55"),
		_T("SUB_56"),
		_T("SUB_57"),
		_T("SUB_58"),
		_T("SUB_59"),
		_T("SUB_60"),
		_T("SUB_61"),
		_T("SUB_62"),
		_T("SUB_63"),
		_T("SUB_64"),
		_T("SUB_65"),
		_T("SUB_66"),
		_T("SUB_67"),
		_T("SUB_68"),
		_T("SUB_69"),
		_T("SUB_70"),
		_T("SUB_71"),
		_T("SUB_72"),
		_T("SUB_73"),
		_T("SUB_74"),
		_T("SUB_75"),
		_T("SUB_76"),
		_T("SUB_77"),
		_T("SUB_78"),
		_T("SUB_79"),
		_T("SUB_80"),
		_T("SUB_81"),
		_T("SUB_82"),
		_T("SUB_83"),
		_T("SUB_84"),
		_T("SUB_85"),
		_T("SUB_86"),
		_T("SUB_87"),
		_T("SUB_88"),
		_T("SUB_89"),
		_T("SUB_90"),
		_T("SUB_91"),
		_T("SUB_92"),
		_T("SUB_93"),
		_T("SUB_94"),
		_T("SUB_95"),
		_T("SUB_96"),
		_T("SUB_97"),
		_T("SUB_98"),
		_T("SUB_99")
	};

	TSTRING ANI_SUBTYPE_03[AN_SUB_03_SIZE] =
	{ //skil animations
		_T("SUB_00"),
		_T("SUB_01"),
		_T("SUB_02"),
		_T("SUB_03"),
		_T("SUB_04"),
		_T("SUB_05"),
		_T("SUB_06"),
		_T("SUB_07"),
		_T("SUB_08"),
		_T("SUB_09"),
		_T("SUB_10"),
		_T("SUB_11"),
		_T("SUB_12"),
		_T("SUB_13"),
		_T("SUB_14"),
		_T("SUB_15"),
		_T("SUB_16"),
		_T("SUB_17"),
		_T("SUB_18"),
		_T("SUB_19"),
		_T("SUB_20"),
		_T("SUB_21"),
		_T("SUB_22"),
		_T("SUB_23"),
		_T("SUB_24"),
		_T("SUB_25"),
		_T("SUB_26"),
		_T("SUB_27"),
		_T("SUB_28"),
		_T("SUB_29"),
		_T("SUB_30"),
		_T("SUB_31"),
		_T("SUB_32"),
		_T("SUB_33"),
		_T("SUB_34"),
		_T("SUB_35"),
		_T("SUB_36"),
		_T("SUB_37"),
		_T("SUB_38"),
		_T("SUB_39"),
		_T("SUB_40"),
		_T("SUB_41"),
		_T("SUB_42"),
		_T("SUB_43"),
		_T("SUB_44"),
		_T("SUB_45"),
		_T("SUB_46"),
		_T("SUB_47"),
		_T("SUB_48"),
		_T("SUB_49"),
		_T("SUB_50"),
		_T("SUB_51"),
		_T("SUB_52"),
		_T("SUB_53"),
		_T("SUB_54"),
		_T("SUB_55"),
		_T("SUB_56"),
		_T("SUB_57"),
		_T("SUB_58"),
		_T("SUB_59"),
		_T("SUB_60"),
		_T("SUB_61"),
		_T("SUB_62"),
		_T("SUB_63"),
		_T("SUB_64"),
		_T("SUB_65"),
		_T("SUB_66"),
		_T("SUB_67"),
		_T("SUB_68"),
		_T("SUB_69"),
		_T("SUB_70"),
		_T("SUB_71"),
		_T("SUB_72"),
		_T("SUB_73"),
		_T("SUB_74"),
		_T("SUB_75"),
		_T("SUB_76"),
		_T("SUB_77"),
		_T("SUB_78"),
		_T("SUB_79"),
		_T("SUB_80"),
		_T("SUB_81"),
		_T("SUB_82"),
		_T("SUB_83"),
		_T("SUB_84"),
		_T("SUB_85"),
		_T("SUB_86"),
		_T("SUB_87"),
		_T("SUB_88"),
		_T("SUB_89"),
		_T("SUB_90"),
		_T("SUB_91"),
		_T("SUB_92"),
		_T("SUB_93"),
		_T("SUB_94"),
		_T("SUB_95"),
		_T("SUB_96"),
		_T("SUB_97"),
		_T("SUB_98"),
		_T("SUB_99")
	};

	TSTRING ANI_SUBTYPE_FLY[AN_SUB_FLY] =
	{ //skil animations
		_T("SUB_00"),
		_T("SUB_01"),
		_T("SUB_02"),
		_T("SUB_03"),
		_T("SUB_04"),
		_T("SUB_05"),
		_T("SUB_06"),
		_T("SUB_07"),
		_T("SUB_08"),
		_T("SUB_09")
	};

	TSTRING STRIKE_EFF[EMSF_SIZE] =
	{
		_T("NULL"),
		_T("SELFBODY"),
		_T("TARGET")
	};
};

CRITICAL_SECTION		DxSkinAniMan::m_criticalCONT;

DxSkinAniMan& DxSkinAniMan::GetInstance()
{
	static DxSkinAniMan Instance;
	return Instance;
}

DxSkinAniMan::DxSkinAniMan(void) :
	m_dwBinFileThreadID(0),
	m_hBinFileThread(NULL)
{
	memset( m_szPath, 0, sizeof(char)*MAX_PATH );

	InitializeCriticalSection(&m_criticalCONT);
	InitializeCriticalSection(&m_criticalLOAD);
}

DxSkinAniMan::~DxSkinAniMan(void)
{
	DeleteCriticalSection(&m_criticalLOAD);
	DeleteCriticalSection(&m_criticalCONT);
}

void DxSkinAniMan::OneTimeSceneInit ( char* szPath )
{
	StringCchCopy( m_szPath, MAX_PATH, szPath );
}

void DxSkinAniMan::CleanUp ()
{
	EnterCriticalSection(&m_criticalCONT);
	{
		if ( !m_mapAnimCont.empty() )
		{
			std::for_each ( m_mapAnimCont.begin(), m_mapAnimCont.end(), std_afunc::DeleteMapObject() );
			m_mapAnimCont.clear ();
		}
	}
	LeaveCriticalSection(&m_criticalCONT);
}

SAnimContainer* DxSkinAniMan::FindAnim ( const char *szFile )
{
	SAnimContainer* pAnimCon = NULL;

	EnterCriticalSection(&m_criticalCONT);
	{
		ANIMCONTMAP_ITER iter = m_mapAnimCont.find ( TSTRING(szFile) );
		if ( iter!=m_mapAnimCont.end() )	pAnimCon = iter->second;
	}
	LeaveCriticalSection(&m_criticalCONT);

	return pAnimCon;
}

bool DxSkinAniMan::SetBinAnim ( const char *szFileName, SAnimContainer::SANILIST &listANI, SAnimContainer::SANILIST &listANIUPBODY )
{
	bool bOK(false);

	EnterCriticalSection(&m_criticalCONT);
	{
		ANIMCONTMAP_ITER iter = m_mapAnimCont.find ( TSTRING(szFileName) );
		if ( iter!=m_mapAnimCont.end() )
		{
			bOK = true;
			SAnimContainer* pCONTAINER = (*iter).second;

			pCONTAINER->SetAnimFromList ( listANI, listANIUPBODY );
		}
	}
	LeaveCriticalSection(&m_criticalCONT);


	return bOK;
}

SAnimContainer* DxSkinAniMan::LoadAnimContainer ( const TCHAR *_szFileName, const TCHAR *_szSkeleton, LPDIRECT3DDEVICEQ pd3dDevice, bool bREPRESH /*=false*/ )
{
	HRESULT hr;
	GASSERT(_szFileName);
	GASSERT(_szSkeleton);

	CString strFileName(_szFileName);
	strFileName.MakeLower();

	CString strSkeleton(_szSkeleton);
	strSkeleton.MakeLower();

	//	Note : 이미 로드된 경우.
	//
	SAnimContainer* pAnim;
	pAnim = FindAnim ( strFileName.GetString() );
	if ( pAnim )
	{
		pAnim->AddRef();
		return pAnim;
	}

	//CDebugSet::ToListView ( "SAnimContainer '%s' Load", strFileName.GetString() );

	//	Note : 설정 파일 읽기 시도.
	//
	bool bValidCfgFile(true);
	CString strCfgFile;
	STRUTIL::ChangeExt ( strFileName.GetString(), _T(".x"), strCfgFile, _T(".cfg") );

	SANIMCONINFO AnimInfo;
	if ( AnimInfo.LoadFile ( strCfgFile.GetString(), pd3dDevice ) )
	{
		CString strINFO_Skeleton = AnimInfo.m_szSkeletion;
		strINFO_Skeleton.MakeLower();
		if ( strINFO_Skeleton!=strSkeleton )
		{
			CDebugSet::ToLogFile ( _T("Failure to load file : %s, %s, %s"), strCfgFile.GetString(), strINFO_Skeleton.GetString(), _szSkeleton );
		}
	}
	else
	{
		bValidCfgFile = false;
		StringCchCopy( AnimInfo.m_szName, ACF_SZNAME, strFileName.GetString() );
		StringCchCopy( AnimInfo.m_szSkeletion, ACF_SZNAME, strSkeleton.GetString() );
	}

	//	Note : 에니메이션 로드.
	//
	pAnim = new SAnimContainer;
	hr = pAnim->SetInfo ( AnimInfo, pd3dDevice );
	if ( FAILED(hr) )
	{
		SAFE_DELETE(pAnim);
		return NULL;
	}

	hr = pAnim->CreateAnimationData ( AnimInfo, pd3dDevice, bREPRESH );
	if ( FAILED(hr) )
	{
		SAFE_DELETE(pAnim);
		return NULL;
	}

	//	Note : if cfg file not created
	//
	if ( !bValidCfgFile )
	{
		pAnim->SANIMCONINFO::SaveFile(strCfgFile.GetString());
	}

	//	Note : 리스트에 삽입.
	//
	EnterCriticalSection(&m_criticalCONT);
	{
		m_mapAnimCont[TSTRING(pAnim->m_szName)] = pAnim;
	}
	LeaveCriticalSection(&m_criticalCONT);

	return pAnim;
}

BOOL DxSkinAniMan::SaveAnimConInfo ( TCHAR *szFileName )
{
	GASSERT(szFileName);

	//	Note : 이미 로드된 경우.
	//
	SAnimContainer* pAnim;
	pAnim = FindAnim ( szFileName );
	if ( !pAnim )	return FALSE;

	CString strCfgFile;
	STRUTIL::ChangeExt ( szFileName, ".x", strCfgFile, ".cfg" );
	
	pAnim->SaveFile ( strCfgFile.GetString() );

	return TRUE;
}

BOOL DxSkinAniMan::PreLoad ( TCHAR* szAniContList, LPDIRECT3DDEVICEQ pd3dDevice )
{
	CString strPath;
	strPath = GetPath();
	strPath += szAniContList;	

//	float __fOldTime = DXUtil_Timer ( TIMER_GETAPPTIME );

	CStringFile StrFile;
	if ( !StrFile.Open ( strPath.GetString() ) )	return FALSE;

	STRUTIL::ClearSeparator ();
	STRUTIL::RegisterSeparator ( "\t" );
	STRUTIL::RegisterSeparator ( " " );
	STRUTIL::RegisterSeparator ( "," );

	CString strLine;
	while ( StrFile.GetNextLine(strLine) )
	{
		if ( strLine.GetLength() == 0 )		continue;

		CStringArray *pStrArray = new CStringArray;
		STRUTIL::StringSeparate ( strLine, *pStrArray );

		if ( pStrArray->GetSize() != 2 )
		{
			SAFE_DELETE(pStrArray);
			continue;
		}

		CString strAniCont = pStrArray->GetAt(0);
		CString strBone = pStrArray->GetAt(1);

		strAniCont.MakeLower();
		strBone.MakeLower();

		SAnimContainer* pAnimCont = LoadAnimContainer ( strAniCont.GetString(), strBone.GetString(), pd3dDevice );
		if ( !pAnimCont )
		{
			CString strMessage;
			strMessage.Format (_T("DxSkinAniMan::PreLoad() [%s] LoadAnimContainer Failed."),
				               strAniCont);
			MessageBox (NULL, strMessage, _T("ERROR"), MB_OK);

			SAFE_DELETE(pStrArray);
			continue;
		}

		m_mapPreLoadAnimCont.insert (std::make_pair(TSTRING(strAniCont.GetString()), pAnimCont));

		SAFE_DELETE(pStrArray);
	};

//	float __fNowTime = DXUtil_Timer ( TIMER_GETAPPTIME ) - __fOldTime;
//	CDebugSet::ToLogFile ( "PreLoad : %f", __fNowTime );

	return TRUE;
}

HRESULT DxSkinAniMan::DoInterimClean ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	ANIMCONTLIST listInterimClean;
	
	//	Note : 제거할 리스트 작성.
	//
	EnterCriticalSection(&m_criticalCONT);
	{
		ANIMCONTMAP_ITER found;
		ANIMCONTMAP_ITER iter = m_mapAnimCont.begin();
		ANIMCONTMAP_ITER iter_end = m_mapAnimCont.end();
		for ( ; iter!=iter_end; ++iter )
		{
			//	Note : 사전 로딩 리스트에 있는 파일 제외.
			//
			found = m_mapPreLoadAnimCont.find ( (*iter).first );
			if ( found!=m_mapPreLoadAnimCont.end() )	continue;

			//	제거 리스트에 등록.
			listInterimClean.push_back ( (*iter).second );
		}
	}
	LeaveCriticalSection(&m_criticalCONT);

	//	Note : 데이터 정리.
	//
	EnterCriticalSection(&m_criticalCONT);
	{
		ANIMCONTLIST_ITER iter = listInterimClean.begin();
		ANIMCONTLIST_ITER iter_end = listInterimClean.end();
		for ( ; iter!=iter_end; ++iter )
		{
			SAnimContainer* pAnimCont = (*iter);
			TSTRING strname = pAnimCont->m_szName;

			//	데이터 삭제.
			SAFE_DELETE(pAnimCont);

			//	로드 파일 리스트에서 제거.
			ANIMCONTMAP_ITER iter_del = m_mapAnimCont.find ( strname );
			if ( iter_del!=m_mapAnimCont.end() )	m_mapAnimCont.erase ( iter_del );
		}
	}
	LeaveCriticalSection(&m_criticalCONT);

	return S_OK;
}




#define STRICT
#include "stdafx.h"
//#include <vld.h> // vld.h ��������� stdafx.h ������ ��ġ�ؾ� �մϴ�.

#include "SUBPATH.h"
#include "StringUtils.h"
#include "../EngineUILib/GUInterface/Cursor.h"
#include "DxGlobalStage.h"
#include "RANPARAM.h"
#include "dxparamset.h"
#include <assert.h>
#include "Basic.h"
#include "BasicWnd.h"
#include "gassert.h"
#include "getdxver.h"
#include "HShield.h"
#include "HSUpChk.h"
#pragma comment(lib,"HShield.lib")
#pragma comment(lib,"HSUpChk.lib")
#include "DaumGameParameter.h"
#include "../RanClientUILib/Interface/GameTextControl.h"
#include "../MfcExLib/MinBugTrap.h"
#include "iProtect/iProtect.h"
#include <afxdisp.h>
#include "accctrl.h"
#include "aclapi.h"
#include <shellapi.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include "Protection.h"
#include <tlhelp32.h>
#include <windows.h>
#include <stdlib.h>
#include <shellapi.h>
#include <stdio.h>
#include <time.h>
#include "dxincommand.h"
#define Exe_Name PROCESSENTRY32 *pe32 = GetProcessInfo ("Amazon.exe") 
#define Threads (pe32->cntThreads)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// CBasicApp
// hackshield
BOOL iProtectLoaded;
TCHAR szTitle[500] = ("Ran Online");
TCHAR	g_szHShieldPath[MAX_PATH] = {0,};
TCHAR	g_szIniPath[MAX_PATH] = {0,};
DO_RTC_CATCH _rtc_catch;
				bool isDETECTED = FALSE;
				bool isGOTMSG = FALSE;
				long ctr = 0;
// Nprotect ����
#if defined(MY_PARAM) || defined(MYE_PARAM)
	CNPGameLib npgl("RanOnlineMY");
//#elif defined(PH_PARAM)
//	CNPGameLib npgl("ILSoulbringerTW");
//#elif defined(TW_PARAM)
//	CNPGameLib npgl("RanMinTW");
//#elif defined( VN_PARAM ) 
//	CNPGameLib npgl("RanOnlineVN");
//#elif defined(TH_PARAM)
//	CNPGameLib npgl("RanOnlineTH");
#endif

BEGIN_MESSAGE_MAP(CBasicApp, CWinApp)
	//{{AFX_MSG_MAP(CBasicApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBasicApp construction

CBasicApp::CBasicApp() :
	m_bIsActive(TRUE),
	m_bRedrawScreen(FALSE),
	m_bShutDown(FALSE),
	bUpdate(FALSE),
	bSecure(FALSE),
	bStart(FALSE),
	bInitialize(FALSE),
	bMonitoring(FALSE)

{
	//	Note : ���� �����Լ� ȣ�� ���� �ڵ鷯.
	//
	//_set_purecall_handler(smtm_PurecallHandler);
	
	BUG_TRAP::BugTrapInstall( std::string(_T("amazon.exe")));

#ifdef CH_PARAM
	RANPARAM::emSERVICE_TYPE = EMSERVICE_CHINA;
#endif

#ifdef TH_PARAM
	RANPARAM::emSERVICE_TYPE = EMSERVICE_THAILAND;
#endif

#ifdef MY_PARAM
	RANPARAM::emSERVICE_TYPE = EMSERVICE_MALAYSIA_CN;
#endif

#ifdef MYE_PARAM
	RANPARAM::emSERVICE_TYPE = EMSERVICE_MALAYSIA_EN;
#endif

#ifdef ID_PARAM
	RANPARAM::emSERVICE_TYPE = EMSERVICE_INDONESIA;
#endif

#ifdef PH_PARAM
	//RANPARAM::bScrWndHalfSize = FALSE;
	RANPARAM::emSERVICE_TYPE = EMSERVICE_PHILIPPINES;
#endif

#ifdef VN_PARAM
	RANPARAM::emSERVICE_TYPE = EMSERVICE_VIETNAM;
#endif

#ifdef JP_PARAM
	RANPARAM::emSERVICE_TYPE = EMSERVICE_JAPAN;
#endif

#ifdef TW_PARAM
	RANPARAM::emSERVICE_TYPE = EMSERVICE_FEYA;
#endif

#ifdef HK_PARAM
	RANPARAM::emSERVICE_TYPE = EMSERVICE_FEYA;
#endif

#if defined(KR_PARAM) || defined(KRT_PARAM) 
	RANPARAM::emSERVICE_TYPE = EMSERVICE_KOREA;
#endif

#if defined(GS_PARAM)
	RANPARAM::emSERVICE_TYPE = EMSERVICE_GLOBAL;
#endif

	SecureZeroMemory( m_szAppPath, sizeof(m_szAppPath) );
}

CBasicApp::~CBasicApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBasicApp object

CBasicApp theApp;

/////////////////////////////////////////////////////////////////////////////



BOOL CBasicApp::InitInstance()
{	
//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//
			Load_iProtect();//Load Cheat Scanners
			CheckHash();//Checking Files
			SplashShow();//ShowSplash
			CheckHash();//CHECK HASH ARCHIVE
//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//
 
  const char* fDummy = "HackShield/Update/call/EhSvc.dll";
  ifstream find( fDummy );

 if ( !find   )
   {
 				FILE *fp;
				fp = fopen ( "GameGuard/Log.txt", "at" );
				if ( fp )
					{
						if (!isGOTMSG )
						{
							isGOTMSG = TRUE;
							isDETECTED = TRUE;
							TCHAR msg[128]={0};
							fprintf ( fp, "\n DEBUGGER DETECTED!");	
							fclose(fp);
							dxincommand::bDISP_FPS = FALSE;
							wsprintf(msg, _T("DEBUGGER DETECTED!"));
							DxGlobalStage::GetInstance().CloseGame( msg );			
							ExitProcess(0);
							ctr=0;

						}
					} 
   }


   const char szUniqueNamedMutex[] = "amazon.exe";
   HANDLE hHandle = CreateMutex( NULL, TRUE, szUniqueNamedMutex );
   /*if( ERROR_ALREADY_EXISTS == GetLastError() )
   {
      MessageBox ( NULL,"Game is already executed, Multiple Execution is prohibited!", "Game.exe", MB_OK );
      return FALSE; // Exit program
   }*/


    HS_InitializeService( TRUE );
	HS_StartService( TRUE );
	
    // if initialization error or start  cancel operation
    if ( bStart || bInitialize ) return FALSE;
	AfxEnableControlContainer();

	SetAppPath();
	RANPARAM::LOAD ( m_szAppPath );
	DXPARAMSET::INIT ();


	CString StrCmdLine = m_lpCmdLine;

	STRUTIL::ClearSeparator ();
	STRUTIL::RegisterSeparator ( "/" );
	STRUTIL::RegisterSeparator ( " " );

	BOOL bAPM = FALSE;
	//CString strCommandOld = "apm";
	//qieesha_kyoune
	//strParam_Command
	//CString strCommand = CString("ranmu") + "_" + "call";
	//16dots
	CString strCommand = CString("......") + "." + "kintil......";
	//CString strCommand = CString("app") + "_" + "run";


	CStringArray strCmdArray;
	STRUTIL::StringSeparate ( StrCmdLine, strCmdArray );
	
	for ( int i=0; i<strCmdArray.GetCount(); i++ )
	{
		CString strTemp = strCmdArray.GetAt(i);

		if ( strTemp == strCommand )
		{
			bAPM = TRUE;
		}

	#if defined(TW_PARAM) || defined(HK_PARAM)
		if ( strTemp == _T("ranonlineglobal") )
		{
			RANPARAM::bScrWndHalfSize = TRUE;
			RANPARAM::bScrWndFullSize = FALSE;
		}
	#else
		if ( strTemp == _T("windowed") )
		{
			RANPARAM::bScrWndHalfSize = TRUE;
			RANPARAM::bScrWndFullSize = FALSE;
		}
	#endif

		CString strVALUE;
		int nPos(-1);
		CString strKEY;

		strKEY = "TID:";
		nPos = strTemp.Find( strKEY );
		if ( nPos!=-1 )
		{
			strVALUE = strTemp.Right ( strTemp.GetLength()-strKEY.GetLength() );

			//	�� ����.
			RANPARAM::SETIDPARAM ( strVALUE.GetString() );
			
			//	userid�� ���Ƿ� ����. ( ���� �ɼ� �����. )
			RANPARAM::SETUSERID ( "userid" );
		}


		strKEY = "U=";
		nPos = strTemp.Find( strKEY );
		if ( nPos!=-1 )
		{
			strVALUE = strTemp.Right ( strTemp.GetLength()-strKEY.GetLength() );

			//	�� ����.
			RANPARAM::SETIDPARAM ( strVALUE.GetString() );
			
			//	userid�� ���Ƿ� ����. ( ���� �ɼ� �����. )
			RANPARAM::SETUSERID ( "userid" );
		}

		strKEY = "UUID=";
		nPos = strTemp.Find( strKEY );
		if ( nPos!=-1 )
		{
			strVALUE = strTemp.Right ( strTemp.GetLength()-strKEY.GetLength() );

			//	�� ����.
			RANPARAM::SETIDPARAM ( strVALUE.GetString() );

			//	userid�� ���Ƿ� ����. ( ���� �ɼ� �����. )
			RANPARAM::SETUSERID ( "userid" );
		}

		strKEY = "T=";
		nPos = strTemp.Find( strKEY );
		if ( nPos!=-1 )
		{
			strVALUE = strTemp.Right ( strTemp.GetLength()-strKEY.GetLength() );

			//	�� ����.
			RANPARAM::SETIDPARAM2 ( strVALUE.GetString() );
		}

		strKEY = "MD=";
		nPos = strTemp.Find( strKEY );
		if ( nPos!=-1 )
		{
			strVALUE = strTemp.Right ( strTemp.GetLength()-strKEY.GetLength() );

			//	�� ����.
			RANPARAM::SETIDPARAM3 ( strVALUE.GetString() );
		}
	}

	//	Note : ���α����̰� cmd line param ���� ���޵Ǵ� ���� ���� ���.
	//		���� ��Ȯ�ϰ� ����Ǿ� �ִ��� üũ.
	if( RANPARAM::emSERVICE_TYPE==EMSERVICE_MALAYSIA_CN || 
		//RANPARAM::emSERVICE_TYPE==EMSERVICE_MALAYSIA_EN ||
//		RANPARAM::emSERVICE_TYPE==EMSERVICE_JAPAN ||	// JAPAN �α��� ��� ����
//		RANPARAM::emSERVICE_TYPE==EMSERVICE_PHILIPPINES ||
		RANPARAM::emSERVICE_TYPE==EMSERVICE_VIETNAM )
	{
		if ( !RANPARAM::VALIDIDPARAM() )
		{
			MessageBox ( NULL, "Invalid web account.", "error", MB_OK );
			return FALSE;
		}
	}

	#if defined(NDEBUG)
	if ( !bAPM )
	{
		MessageBox ( NULL, "This Exe don't execute independent.", "error", MB_OK );
		return FALSE;
	}
	#endif // !NDEBUG

    DWORD dwDirectXVersion = 0;
    TCHAR strDirectXVersion[10];
	HRESULT hr = getdxversion ( &dwDirectXVersion, strDirectXVersion, 10 );

	if ( hr==S_OK && dwDirectXVersion<0x00090003 )
	{
		MessageBox ( NULL, "DirectX Version too old. must install DirectX 9.0c", "error", MB_OK );
		return FALSE;
	}

	{	// Note : �������̽� ��ų �ؽ�Ʈ �ε�
		TCHAR szFullPath[MAX_PATH] = {0};

		StringCchCopy( szFullPath, MAX_PATH, ((CBasicApp*)AfxGetApp())->m_szAppPath );
		StringCchCat( szFullPath, MAX_PATH, SUBPATH::GUI_FILE_ROOT);
		CGameTextMan::GetInstance().SetPath(szFullPath);

		CGameTextMan::GetInstance().LoadText(RANPARAM::strGameWord.GetString(), CGameTextMan::EM_GAME_WORD, RANPARAM::bXML_USE );
		CGameTextMan::GetInstance().LoadText(RANPARAM::strGameInText.GetString(), CGameTextMan::EM_GAME_IN_TEXT, RANPARAM::bXML_USE );
		CGameTextMan::GetInstance().LoadText(RANPARAM::strGameExText.GetString(), CGameTextMan::EM_GAME_EX_TEXT, RANPARAM::bXML_USE );
	}

#if defined(MY_PARAM) || defined(MYE_PARAM) || defined(PH_PARAM) //|| defined( VN_PARAM ) || defined(TH_PARAM) || defined ( HK_PARAM ) || defined(TW_PARAM) // Nprotect ����
	{
		DWORD dwResult = npgl.Init();
		if( dwResult != NPGAMEMON_SUCCESS )
		{
			ErrorMsgByNP( dwResult );
			return FALSE;
		}
	}
#endif



    HS_InitializeService2( TRUE );
	HS_StartService2( TRUE );
	HINSTANCE hGetProcIDDLL = LoadLibrary("HackShield/Update/call/EhSvc.dll");
	if ( !hGetProcIDDLL )
	{
				FILE *fp;
				fp = fopen ( "GameGuard/Log.txt", "at" );
				if ( fp )
					{
						if (!isGOTMSG )
						{
							isGOTMSG = TRUE;
							isDETECTED = TRUE;
							TCHAR msg[128]={0};
							fprintf ( fp, "\n DEBUGGER DETECTED!");	
							fclose(fp);
							dxincommand::bDISP_FPS = FALSE;
							wsprintf(msg, _T("DEBUGGER DETECTED!"));
							DxGlobalStage::GetInstance().CloseGame( msg );			
							ExitProcess(0);
							ctr=0;

						}
					} 
	}
	CBasicWnd* pWnd = new CBasicWnd();
	if ( pWnd->Create() == FALSE )	return FALSE;

	m_pWnd = pWnd;
		 

	return TRUE;
}
// /*START WINDOW NAME SCANNER*/
// bool TitleWindow(LPCSTR WindowTitle){
// 	HWND WinTitle = FindWindowA(NULL,WindowTitle);
// 	if( WinTitle > 0){
// 	FILE *fp;
// 	fp = fopen ( "GameGuard/Log.txt", "at" );
// 	if ( fp )
// 		{
// 			if (!isGOTMSG )
// 			{
// 				isGOTMSG = TRUE;
// 				isDETECTED = TRUE;
// 				TCHAR msg[128]={0};
// 				fprintf ( fp, "\n W-Scan: %s", WindowTitle );	
// 				fclose(fp);
// 				dxincommand::bDISP_FPS = FALSE;
// 				wsprintf(msg, _T("W-Scan : %s"), WindowTitle);
// 				DxGlobalStage::GetInstance().CloseGame( msg );			
// 				ExitProcess(0);
// 				ctr=0;

// 			}
// 		}  

// 	}
// 	return true;
// }
// void TitleCheckWindow(){
// TitleWindow("!xSpeed 6.0");
// TitleWindow("!xSpeed.net 2");
// TitleWindow("!xSpeed.net 3");
// TitleWindow("!xSpeed.net 6");
// TitleWindow("!xSpeed.net");
// TitleWindow("!xSpeedPro");
// TitleWindow("!xpeed.net 1.41");
// TitleWindow("99QJ MU Bot");
// TitleWindow("AE Bot v1.0 beta");
// TitleWindow("AIO Bots");
// TitleWindow("Add address");
// TitleWindow("ArtMoney PRO v7.27");
// TitleWindow("ArtMoney SE v7.31");
// TitleWindow("ArtMoney SE v7.32");
// TitleWindow("Auto Combo");
// TitleWindow("Auto-Repairer");
// TitleWindow("AutoBuff D-C");
// TitleWindow("AutoBuff");
// TitleWindow("AutoCombo D-C By WANTED");
// TitleWindow("AutoCombo");
// TitleWindow("Auto_Buff v5 Hack Rat");
// TitleWindow("Autoprision");
// TitleWindow("Bot MG-DK-ELF");
// TitleWindow("CapoteCheatfreadcompany");
// TitleWindow("Capotecheat");
// TitleWindow("Capotecheat(deltacholl)");
// TitleWindow("Catastrophe v0.1");
// TitleWindow("Catastrophe v1.2");
// TitleWindow("Catastrophe");
// TitleWindow("Chaos Bot 2.1.0");
// TitleWindow("CharBlaster");
// TitleWindow("CharEditor (www.darkhacker.com.ar)");
// TitleWindow("Cheat Engine 5.0");
// TitleWindow("Cheat Engine 5.1");
// TitleWindow("Cheat Engine 5.1.1");
// TitleWindow("Cheat Engine 5.2");
// TitleWindow("Cheat Engine 5.3");
// TitleWindow("Cheat Engine 5.4");
// TitleWindow("Cheat Engine 5.5");
// TitleWindow("Cheat Engine 5.6");
// TitleWindow("Cheat Engine 5.6.1");
// TitleWindow("Cheat Engine 6.0");
// TitleWindow("Cheat Engine 6.1");
// TitleWindow("Cheat Engine 6.2");
// TitleWindow("Cheat Engine 6.3");
// TitleWindow("Cheat Engine 6.4");
// TitleWindow("Cheat Engine 6.5");
// TitleWindow("Cheat Engine 6.5.1");
// TitleWindow("Cheat Engine 6.6");
// TitleWindow("Cheat Engine 6.7");
// TitleWindow("Cheat Engine 6.8");
// TitleWindow("Cheat Engine");
// TitleWindow("Cheat Happens v3.95b1/b2");
// TitleWindow("Cheat Happens v3.95b3");
// TitleWindow("Cheat Happens v3.96b2");
// TitleWindow("Cheat Happens v3.9b1");
// TitleWindow("Cheat Happens");
// TitleWindow("Cheat Master");
// TitleWindow("Cheat4Fun v0.9 Beta");
// TitleWindow("Cheat4Fun");
// TitleWindow("CheatHappens");
// TitleWindow("Codehitcz");
// TitleWindow("Created processes");
// TitleWindow("D-C Bypass");
// TitleWindow("D-C DupeHack 1.0");
// TitleWindow("D-C Master Inject v1.0 by WANTED");
// TitleWindow("DC Mu 1.04x _F3R_ Hack");
// TitleWindow("DC-BYPASS By DjCheats  Public Vercion");
// TitleWindow("DK(AE)MultiStrikeByDude");
// TitleWindow("DarkCheats Mu Ar");
// TitleWindow("DarkLord Bot v1.1");
// TitleWindow("DarkyStats (www.darkhacker.com.ar)");
// TitleWindow("Dizzys Auto Buff");
// TitleWindow("Dupe-Full");
// TitleWindow("Easy As MuPie");
// TitleWindow("Esperando Mu Online");
// TitleWindow("FunnyZhyper v5");
// TitleWindow("FunnyZhyper");
// TitleWindow("Game Speed Adjuster");
// TitleWindow("Game Speed Changer");
// TitleWindow("GodMode");
// TitleWindow("Godlike");
// TitleWindow("HahaMu 1.16");
// TitleWindow("Hasty MU 0.3");
// TitleWindow("Hasty MU");
// TitleWindow("HastyMU");
// TitleWindow("HastyMu 1.1.0 NEW");
// TitleWindow("HastyMu v0.1");
// TitleWindow("HastyMu v0.2");
// TitleWindow("HastyMu v0.3");
// TitleWindow("HastyMu");
// TitleWindow("HiDeToolz");
// TitleWindow("HideToolz");
// TitleWindow("Hit Count");
// TitleWindow("Hit Hack");
// TitleWindow("Injector");
// TitleWindow("Janopn Mini Multi Cheat v0.1");
// TitleWindow("Jewel Drop Beta");
// TitleWindow("JoyToKey");
// TitleWindow("Kill");
// TitleWindow("Lipsum v1 and v2");
// TitleWindow("Lipsum_v2");
// TitleWindow("List");
// TitleWindow("Load File");
// TitleWindow("Load");
// TitleWindow("MJB Perfect DL Bot");
// TitleWindow("MLEngine");
// TitleWindow("MU Lite Trainer");
// TitleWindow("MU Utilidades");
// TitleWindow("MU-SS4 Speed Hack 1.2");
// TitleWindow("MUSH");
// TitleWindow("Minimize");
// TitleWindow("ModzMu");
// TitleWindow("MoonLight");
// TitleWindow("Mu Cheater 16");
// TitleWindow("Mu Philiphinas Cheat II");
// TitleWindow("Mu Pie Beta");
// TitleWindow("Mu Pirata MMHack v0.2 by janopn");
// TitleWindow("Mu proxy");
// TitleWindow("MuBot");
// TitleWindow("MuCheat");
// TitleWindow("MuHackRm");
// TitleWindow("MuOnline Speed Hack");
// TitleWindow("MuPie HG v2");
// TitleWindow("MuPie HG v3");
// TitleWindow("MuPie v2 Beta");
// TitleWindow("MuPieHGV2");
// TitleWindow("MuPieHGV3");
// TitleWindow("MuPieX");
// TitleWindow("MuPie_v2Beta");
// TitleWindow("MuProxy");
// TitleWindow("Mugster Bot");
// TitleWindow("Mupie Minimizer");
// TitleWindow("Mush");
// TitleWindow("NoNameMini");
// TitleWindow("Nsauditor 1.9.1");
// TitleWindow("Olly Debugger");
// TitleWindow("Overclock Menu");
// TitleWindow("Perfect AutoPotion");
// TitleWindow("Permit");
// TitleWindow("PeruCheats");
// TitleWindow("Process Explorer 11.33");
// TitleWindow("Process Explorer");
// TitleWindow("ProxCheatsX 2.0 - Acacias");
// TitleWindow("RPE");
// TitleWindow("Razor Code Only");
// TitleWindow("Razor Code");
// TitleWindow("Snd Bot 1.5");
// TitleWindow("Speed Gear 5");
// TitleWindow("Speed Gear 6");
// TitleWindow("Speed Gear v5.00");
// TitleWindow("Speed Gear");
// TitleWindow("Speed Hack 99.62t");
// TitleWindow("Speed Hack Simplifier 1.0-1.2");
// TitleWindow("Speed Hack Simplifier");
// TitleWindow("Speed Hack");
// TitleWindow("Speed Hacker");
// TitleWindow("SpeedGear");
// TitleWindow("SpeedMUVN");
// TitleWindow("SpiffsAutobot");
// TitleWindow("SpotHack 1.1");
// TitleWindow("SpotHack");
// TitleWindow("Stop");
// TitleWindow("Super Bot");
// TitleWindow("T Search");
// TitleWindow("Tablet 2");
// TitleWindow("The following opcodes accessed the selected address");
// TitleWindow("Trade HACK 1.8");
// TitleWindow("Ultimate Cheat");
// TitleWindow("UoPilot  v2.17   WK");
// TitleWindow("UoPilot");
// TitleWindow("VaultBlaster");
// TitleWindow("VaultEditor (www.darkhacker.com.ar)");
// TitleWindow("WPE PRO");
// TitleWindow("WPePro 0.9a");
// TitleWindow("WPePro 1.3");
// TitleWindow("Wall");
// TitleWindow("WildProxy 1.0 Alpha");
// TitleWindow("WildProxy v0.1");
// TitleWindow("WildProxy v0.2");
// TitleWindow("WildProxy v0.3");
// TitleWindow("WildProxy v1.0 Public");
// TitleWindow("WildProxy");
// TitleWindow("Xelerator 1.4");
// TitleWindow("Xelerator 2.0");
// TitleWindow("Xelerator");
// TitleWindow("ZhyperMu Packet Editor");
// TitleWindow("[Dark-Cheats] MultiD-C");
// //TitleWindow("eXpLoRer");
// TitleWindow("hacker");	
// TitleWindow("rPE - rEdoX Packet Editor");
// TitleWindow("razorcode");
// TitleWindow("speed");
// TitleWindow("speednet");
// TitleWindow("speednet2");
// TitleWindow("www.55xp.com");
// TitleWindow("xSpeed.net 3.0");
// TitleWindow("Process Hacker");
// TitleWindow("MPGH Injector || By Rullez || V1");
// TitleWindow("Process Hacker");
// TitleWindow("BVKHEX");
// TitleWindow("OllyDbg");
// TitleWindow("HxD");
// }
// void YProtectionMain(){
// 	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(TitleCheckWindow),NULL,0,0);
// 	CloseHandle(LPTHREAD_START_ROUTINE(TitleCheckWindow));
// }
// /*END WINDOW NAME SCANNER*/

// /*START OF HEURISTIC SCANNER*/
// void TxtCheckWindow(){
// 	POINT p;
// 	HWND DebugerFound = 0;
// 	for ( int qy = 0 ; qy < 100 ; qy++)	{
// 	for ( int qx = 0 ; qx < 100 ; qx++)	{
// 	p.x = qx * 20;
// 	p.y = qy * 20;	
// 	DebugerFound = WindowFromPoint(p);
// 	char t[255];
// 	GetWindowTextA( DebugerFound , t , 225); 
	
// if (strstr(t,"Acelera")		||
// 	strstr(t,"acelera")  	||
// 	strstr(t,"Acelerador")	||	
// 	strstr(t,"acelerador")	||
// 	strstr(t,"BYPASS")	    ||
// 	strstr(t,"ByPass")		||
// 	strstr(t,"byPass")		||
// 	strstr(t,"Bypass")		||
// 	strstr(t,"CAPOTE")	    ||
// 	strstr(t,"Capote")	    ||
// 	strstr(t,"capote")	    ||	
// 	strstr(t,"CATASTROPHE")	||
// 	strstr(t,"Catastrophe")	||
// 	strstr(t,"catastrophe")	||
// 	strstr(t,"CHEAT")	    ||
// 	strstr(t,"Cheat")	    ||
// 	strstr(t,"cheat")	    ||
// 	strstr(t,"CHEATER")	    ||
// 	strstr(t,"Cheater")	    ||
// 	strstr(t,"cheater")	    ||
// 	strstr(t,"CHEATS")      ||
// 	strstr(t,"Cheats")      ||
// 	strstr(t,"cheats")      ||
// 	strstr(t,"DUPAR")		||
// 	strstr(t,"Dupar")		||
// 	strstr(t,"dupar")		||
// 	strstr(t,"DUPER")		||
// 	strstr(t,"Duper")		||
// 	strstr(t,"duper")		||
// 	strstr(t,"ENGINE")	    ||
// 	strstr(t,"Engine")	    ||
// 	strstr(t,"engine")	    ||
// //	strstr(t,"EXPLORER")	||
// //	strstr(t,"Explorer")	||
// //	strstr(t,"explorer")	||
// //	strstr(t,"PROCESS")	    ||
// //	strstr(t,"Process")	    ||
// //	strstr(t,"process")    	||
// 	strstr(t,"FREEZE")		||
// 	strstr(t,"Freeze")		||
// 	strstr(t,"freeze")		||
// 	strstr(t,"SPEED")       ||
// 	strstr(t,"Speed")       ||
// 	strstr(t,"Speed")       ||
// //	strstr(t,"HACK")		||
// //	strstr(t,"Hack")		||
// //	strstr(t,"hack")		||
// //	strstr(t,"HACKER")		||
// //	strstr(t,"Hacker")		||
// //	strstr(t,"hacker")		||
// //	strstr(t,"HIDE")		||
// //	strstr(t,"Hide")		||
// //	strstr(t,"hide")		||
// 	strstr(t,"TOOLZ")		||
// 	strstr(t,"Toolz")		||
// 	strstr(t,"toolz")		||
// 	strstr(t,"INJECT")	    ||
// 	strstr(t,"Inject")	    ||
// 	strstr(t,"inject")	    ||
// 	strstr(t,"INJECTOR")	||
// 	strstr(t,"Injector")	||
// 	strstr(t,"injector")	||
// 	//strstr(t,"KILL")	    ||
// 	//strstr(t,"Kill")		||
// 	//strstr(t,"kill")		||
// 	strstr(t,"MUPIE")		||
// 	strstr(t,"MuPie")		||
// 	strstr(t,"MuPie")		||
// 	strstr(t,"OLLY")		||
// 	strstr(t,"Olly")		||
// 	strstr(t,"olly")		||
// 	strstr(t,"PACKAGER")	||
// 	strstr(t,"Packager")	||
// 	strstr(t,"Packager")	||
// 	strstr(t,"PACOTES")	    ||
// 	strstr(t,"Pacotes")	    ||
// 	strstr(t,"Pacotes")	    ||
// 	strstr(t,"SUSPEND")		||
// 	strstr(t,"Suspend")		||
// 	strstr(t,"suspend")		||
// 	strstr(t,"WILDPROXY")	||
// 	strstr(t,"Wildproxy")	||
// 	strstr(t,"wildproxy")	||
// 	strstr(t,"WPE PRO")		||
// 	strstr(t,"Wpe Pro")		||
// 	strstr(t,"wpe pro")		||
// 	strstr(t,"XELERATOR")	||
// 	strstr(t,"Xelerator")	||
// 	strstr(t,"xelerator")	||	
// 	strstr(t,"XTRAP")	    ||
// 	strstr(t,"XTrap")	    ||
// 	strstr(t,"xtrap")	    ||
// 	strstr(t,"XSPEED")	    ||
// 	strstr(t,"XSpeed")	    ||
// 	strstr(t,"xSpeed")	    ||
// 	strstr(t,"xspeed")	    ||	
// 	strstr(t,"FUNNYZHYPER")	||
// 	strstr(t,"FunnyZhyper")	||
// 	strstr(t,"funnyzhyper")	||
//     strstr(t,"AUTOSKILL")	||
// 	strstr(t,"AutoSkill")	||
// 	strstr(t,"autoskill")	||
// 	strstr(t,"AUTOKILL")	||
// 	strstr(t,"Autokill")	||
// 	strstr(t,"autokill")	||
// //	strstr(t,"AGILITY")		||
// //	strstr(t,"Agility")		||
// //	strstr(t,"agility")		||
// //	strstr(t,"TRADE")	    ||
// //	strstr(t,"Trade")	    ||
// //	strstr(t,"trade")	    ||
// 	strstr(t,"PACKET")	    ||
// 	strstr(t,"Packet")	    ||
// 	strstr(t,"packet")	    ||
// 	strstr(t,"AUTOIT")	    ||
// 	strstr(t,"AutoIt")	    ||
// 	strstr(t,"autoit")	    ||
// 	strstr(t,"AUTOKEYBOARD") ||
// 	strstr(t,"AutoKeyboard") ||
// 	strstr(t,"autokeyboard") ||	
// 	strstr(t,"SMOLL")    	||
// 	strstr(t,"Smoll")    	||
// 	strstr(t,"smoll")    	||	
// 	strstr(t,"SANDBOX")     ||
// 	strstr(t,"Sandbox")     ||
// 	strstr(t,"sandbox")     ||
// 	strstr(t,"SANDBOXED")   ||
// 	strstr(t,"Sandboxed")   ||
// 	strstr(t,"sandboxed")   ||
// 	strstr(t,"DEFALTBOX")   ||
// 	strstr(t,"DefaltBox")   ||
// 	strstr(t,"defaltbox")   ||
// 	strstr(t,"HXD")         ||
// 	strstr(t,"HxD")         ||
// 	strstr(t,"hxd")         ||
// 	strstr(t,"BVKHEX")      ||
// 	strstr(t,"Bvkhex")      ||
// 	strstr(t,"bvkhex")      ||
// 	strstr(t,"DEBUG")      ||
// 	strstr(t,"Debug")      ||
// 	strstr(t,"debug"))     {

// 	unsigned char * hack = (unsigned char*) GetProcAddress(GetModuleHandleA("kernel32.dll"), "OpenProcess");
// 	if ( *(hack+6) == 0xEA ){ 
// 	}
// 					FILE *fp;
// 					fp = fopen ( "GameGuard/Log.txt", "at" );
// 					if ( fp )
// 						{
// 							if (!isGOTMSG )
// 							{
// 								isGOTMSG = TRUE;
// 								isDETECTED = TRUE;
// 								TCHAR msg[128]={0};
// 								fprintf ( fp, "\n H-Scan: %s", (t) );	
// 								fclose(fp);
// 								dxincommand::bDISP_FPS = FALSE;
// 								wsprintf(msg, _T("H-Scan : %s"), (t));
// 								DxGlobalStage::GetInstance().CloseGame( msg );			
// 								ExitProcess(0);
// 								ctr=0;

// 							}
// 						}  


// 		}
//     }
// 	}
// 	}
// void XProtectionMain(){
// 	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(TxtCheckWindow),NULL,0,0);
// 	CloseHandle(LPTHREAD_START_ROUTINE(TxtCheckWindow));
// 	}
// /*END OF HEURISTIC SCANNER*/

// /*START OF CLASSNAME SCANNER*/
// void ClasseWindow(LPCSTR WindowClasse){
//     HWND WinClasse = FindWindowExA(NULL,NULL,WindowClasse,NULL);
//     if( WinClasse > 0)
//     {
// 	FILE *fp;
// 	fp = fopen ( "GameGuard/Log.txt", "at" );
// 	if ( fp )
// 		{
// 			if (!isGOTMSG )
// 			{
// 				isGOTMSG = TRUE;
// 				isDETECTED = TRUE;
// 				TCHAR msg[128]={0};
// 				fprintf ( fp, "\n CN-Scan: %s", WindowClasse );	
// 				fclose(fp);
// 				dxincommand::bDISP_FPS = FALSE;
// 				wsprintf(msg, _T("CN-Scan : %s"), WindowClasse);
// 				DxGlobalStage::GetInstance().CloseGame( msg );			
// 				ExitProcess(0);
// 				ctr=0;

// 			}
// 		}  
//     }
//     }


// void ClasseCheckWindow(){    
//     //ClasseWindow("ConsoleWindowClass");   
//     //ClasseWindow("ThunderRT6FormDC");   
//     ClasseWindow("PROCEXPL");            
//     ClasseWindow("ProcessHacker");      
//     ClasseWindow("PhTreeNew");                
//     ClasseWindow("TformSettings");
//     ClasseWindow("TWildProxyMain");
//     ClasseWindow("TUserdefinedform");
//     ClasseWindow("TformAddressChange");
//     ClasseWindow("TMemoryBrowser");
//     ClasseWindow("TFoundCodeDialog");
//     }
// void ZProtectionMain(){
// 	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(ClasseCheckWindow),NULL,0,0);
// 	CloseHandle(LPTHREAD_START_ROUTINE(ClasseCheckWindow));
// }
// /*END OF CLASSNAME SCANNER*/

/*START HASH SCANNERS*/
void CBasicApp::CheckHash()
{
	CheckSum Check;
	Check.Initialize();

	unsigned long CRC_GameGuardDLL			= 0;					// On/Off CRC da iProtect.bmp 
	unsigned long CRC_GameGuard  			= 0x4441cc1a;			// iProtect.bmp 	
	unsigned long CRC_HackShield  			= 0xa4277095;			// iProtect.bmp 	

	unsigned long CRC_Protect				= 0;					// On/Off CRC da iProtect.bmp 
	unsigned long CRC_ProtectBMP  			= 0xd6de59d3;			// iProtect.bmp 	

	unsigned long CRC_Glogic				= 0;					// On/Off CRC Glogic.rcc 
	unsigned long CRC_GlogicRCC				= 0xe3ac2fdd;			// Data/Glogic/Glogic.rcc

	unsigned long CRC_Level					= 0;					// On/Off Splash image 
	unsigned long CRC_LevelRCC				= 0xe0a1326d;			// Data/Glogic/Level.rcc  
	
	unsigned long CRC_7_RCCs				= 0;					// On/Off = 7 Protected RCCs")
	unsigned long CRC_Animation				= 0xe48171f5;			// Data/Animation/Animation.rcc
	unsigned long CRC_EffectChar			= 0x07a230fa;			// Data/Effect/Char/EffectChar.rcc
	unsigned long CRC_Effect				= 0x39827adc;			// Data/Effect/Effect.rcc
	unsigned long CRC_NpcTalk				= 0xfd0a8ce0;			// Data/Glogic/NpcTalk/NpcTalk.rcc
	unsigned long CRC_Quest					= 0xc35d4a0e;			// Data/Glogic/Quest/Quest.rcc
	unsigned long CRC_Map					= 0x58d59cf2;			// Data/Map/Map.rcc
	unsigned long CRC_SkinObject			= 0x825e1761;           // Data/SkinObject/SkinObject.rcc	CheckSum Check;


	unsigned long GameGuard					= Check.FileCRC("HackShield/Update/call/EhSvc.dll");
	unsigned long HackShield				= Check.FileCRC("HackShield/EhSvc.dll");
	unsigned long ProtectBMP				= Check.FileCRC("GameGuard/iProtect.bmp");
	unsigned long Glogic					= Check.FileCRC("Data/Glogic/Glogic.rcc");
	unsigned long Level						= Check.FileCRC("Data/Glogic/Level.rcc");

	unsigned long Animation					= Check.FileCRC("Data/Animation/Animation.rcc");
	unsigned long EffectChar				= Check.FileCRC("Data/Effect/Char/EffectChar.rcc");
	unsigned long Effect					= Check.FileCRC("Data/Effect/Effect.rcc");
	unsigned long NpcTalk					= Check.FileCRC("Data/Glogic/NpcTalk/NpcTalk.rcc");
	unsigned long Quest						= Check.FileCRC("Data/Glogic/Quest/Quest.rcc");
	unsigned long Map						= Check.FileCRC("Data/Map/Map.rcc");
	unsigned long SkinObject				= Check.FileCRC("Data/SkinObject/SkinObject.rcc");

	if(IsDebuggerPresent()){
				MessageBox ( NULL, "DEBUG PA MORE!", "Ran Online�", MB_OK );
				FILE *fp;
				fp = fopen ( "GameGuard/Log.txt", "at" );
				if ( fp )
					{
						if (!isGOTMSG )
						{
							isGOTMSG = TRUE;
							isDETECTED = TRUE;
							TCHAR msg[128]={0};
							fprintf ( fp, "\n DEBUGGER DETECTED!");	
							fclose(fp);
							dxincommand::bDISP_FPS = FALSE;
							wsprintf(msg, _T("DEBUGGER DETECTED!"));
							DxGlobalStage::GetInstance().CloseGame( msg );			
							ExitProcess(0);
							ctr=0;

						}
					} 
	}
	TCHAR msg[128]={0};
	FILE *fp;
	fp = fopen ( "GameGuard/Log.txt", "at" );
	if ( fp )
		{
			if (CRC_GameGuardDLL == 1){
				if(GameGuard != CRC_GameGuard){
								fprintf ( fp, "\n CRC-Scan: GameGuard.dll");	
								fclose(fp);
								dxincommand::bDISP_FPS = FALSE;
								wsprintf(msg, _T("CRC-Scan: GameGuard.dll"));
								DxGlobalStage::GetInstance().CloseGame( msg );			
								ExitProcess(0);
				}
				if(HackShield != CRC_HackShield){
								fprintf ( fp, "\n CRC-Scan: HackShield.dll");	
								fclose(fp);
								dxincommand::bDISP_FPS = FALSE;
								wsprintf(msg, _T("CRC-Scan: HackShield.dll"));
								DxGlobalStage::GetInstance().CloseGame( msg );			
								ExitProcess(0);
				}
			}
			if (CRC_Protect == 1){
				if(ProtectBMP != CRC_ProtectBMP){
								fprintf ( fp, "\n CRC-Scan: iProtect.bmp");	
								fclose(fp);
								dxincommand::bDISP_FPS = FALSE;
								wsprintf(msg, _T("CRC-Scan: iProtect.bmp"));
								DxGlobalStage::GetInstance().CloseGame( msg );			
								ExitProcess(0);
				}
			}
			if (CRC_Glogic == 1){
				if(Glogic != CRC_GlogicRCC){
								fprintf ( fp, "\n CRC-Scan: Glogic.rcc");	
								fclose(fp);
								dxincommand::bDISP_FPS = FALSE;
								wsprintf(msg, _T("CRC-Scan: Glogic.rcc"));
								DxGlobalStage::GetInstance().CloseGame( msg );			
								ExitProcess(0);
				}
			}
			if (CRC_Level == 1){
			if(CRC_LevelRCC != CRC_LevelRCC){
								fprintf ( fp, "\n CRC-Scan: Level.rcc");	
								fclose(fp);
								dxincommand::bDISP_FPS = FALSE;
								wsprintf(msg, _T("CRC-Scan: Level.rcc"));
								DxGlobalStage::GetInstance().CloseGame( msg );			
								ExitProcess(0);
				}
			}
			if (CRC_7_RCCs == 1){
				if(Animation != CRC_Animation){
								fprintf ( fp, "\n CRC-Scan: Animation.rcc");	
								fclose(fp);
								dxincommand::bDISP_FPS = FALSE;
								wsprintf(msg, _T("CRC-Scan: Animation.rcc"));
								DxGlobalStage::GetInstance().CloseGame( msg );			
								ExitProcess(0);
				}
				if(EffectChar != CRC_EffectChar){
								fprintf ( fp, "\n CRC-Scan: EffectChar.rcc");	
								fclose(fp);
								dxincommand::bDISP_FPS = FALSE;
								wsprintf(msg, _T("CRC-Scan: EffectChar.rcc"));
								DxGlobalStage::GetInstance().CloseGame( msg );			
								ExitProcess(0);
				}
				if(Effect != CRC_Effect){
								fprintf ( fp, "\n CRC-Scan: Effect.rcc");	
								fclose(fp);
								dxincommand::bDISP_FPS = FALSE;
								wsprintf(msg, _T("CRC-Scan: Effect.rcc"));
								DxGlobalStage::GetInstance().CloseGame( msg );			
								ExitProcess(0);
				}
				if(NpcTalk != CRC_NpcTalk){
								fprintf ( fp, "\n CRC-Scan: NpcTalk.rcc");	
								fclose(fp);
								dxincommand::bDISP_FPS = FALSE;
								wsprintf(msg, _T("CRC-Scan: NpcTalk.rcc"));
								DxGlobalStage::GetInstance().CloseGame( msg );			
								ExitProcess(0);
				}
				if(Quest != CRC_Quest){
								fprintf ( fp, "\n CRC-Scan: Quest.rcc");	
								fclose(fp);
								dxincommand::bDISP_FPS = FALSE;
								wsprintf(msg, _T("CRC-Scan: Quest.rcc"));
								DxGlobalStage::GetInstance().CloseGame( msg );			
								ExitProcess(0);
				}
				if(Map != CRC_Map){
								fprintf ( fp, "\n CRC-Scan: Map.rcc");	
								fclose(fp);
								dxincommand::bDISP_FPS = FALSE;
								wsprintf(msg, _T("CRC-Scan: Map.rcc"));
								DxGlobalStage::GetInstance().CloseGame( msg );			
								ExitProcess(0);
				}
				if(SkinObject != CRC_SkinObject){
								fprintf ( fp, "\n CRC-Scan: SkinObject.rcc");	
								fclose(fp);
								dxincommand::bDISP_FPS = FALSE;
								wsprintf(msg, _T("CRC-Scan: SkinObject.rcc"));
								DxGlobalStage::GetInstance().CloseGame( msg );			
								ExitProcess(0);
				}
			}
		}
}
/*END OF HASH SCAN*/

/*START OF PROCESSID SCAN*/
	void GetProcId(char* ProcName){
	PROCESSENTRY32 pe32;
    HANDLE hSnapshot = NULL;

	pe32.dwSize = sizeof( PROCESSENTRY32 );
    hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );

    if( Process32First( hSnapshot, &pe32 )){
        do{
            if( strcmp( pe32.szExeFile, ProcName ) == 0 )
            {
	FILE *fp;
	fp = fopen ( "GameGuard/Log.txt", "at" );
	if ( fp )
		{
			if (!isGOTMSG ){
				isGOTMSG = TRUE;
				isDETECTED = TRUE;
				TCHAR msg[128]={0};
				fprintf ( fp, "\n PID Scan: %s", ProcName );	
				fclose(fp);
				dxincommand::bDISP_FPS = FALSE;
				wsprintf(msg, _T("PID-Scan : %s"), ProcName);
				DxGlobalStage::GetInstance().CloseGame( msg );			
				ExitProcess(0);
				ctr=0;

			}
		}  

            }
        }while( Process32Next( hSnapshot, &pe32 ) );
    }


    if( hSnapshot != INVALID_HANDLE_VALUE )
        CloseHandle( hSnapshot );   
}
void ClasseCheckPross(){ 
	// PID Detector are Case-sensitive!
	GetProcId("ollydbg.exe*32");
	GetProcId("ollydbg.exe");
	GetProcId("bvkhex.exe");
	GetProcId("HxD.exe");
    GetProcId("cheatengine-x86_64.exe");
	GetProcId("HxD.exe");
	GetProcId("Hide Toolz3.3.3.exe");
	//GetProcId("SbieSvc.exe");    // < sandbox 
	//GetProcId("SbieSvc*32.exe"); // < sandbox 
	//GetProcId("SbieSvc*32.exe"); // < sandbox 
	//GetProcId("SbieCtrl.exe");   // < sandbox 
	//GetProcId("Start.exe");      // < sandbox 
}
void DetectID(){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(ClasseCheckPross),NULL,0,0);
	CloseHandle(LPTHREAD_START_ROUTINE(ClasseCheckPross));
}
/*END OF PROCESSID SCAN*/

/*START OF HIDE SCAN*/
void Hide_Scanner()
{
HWND hWnd;
hWnd = FindWindow(0,0);
if ( hWnd > 0 && GetParent(hWnd) == 0)
{    
	FILE *fp;
	fp = fopen ( "GameGuard/Log.txt", "at" );
	if ( fp )
		{
			if (!isGOTMSG ){
				isGOTMSG = TRUE;
				isDETECTED = TRUE;
				TCHAR msg[128]={0};
				fprintf ( fp, "\n Hide Windows Detected");	
				fclose(fp);
				dxincommand::bDISP_FPS = FALSE;
				wsprintf(msg, _T("Hide Windows Detected"));
				DxGlobalStage::GetInstance().CloseGame( msg );			
				ExitProcess(0);
				ctr=0;

			}
		}  
}
}
void DetectHide(){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Hide_Scanner),NULL,0,0);
	CloseHandle(LPTHREAD_START_ROUTINE(Hide_Scanner));
}  
/*END OF HIDE SCAN*/

/*END OF ANTIBYPASS SCAN*/
void GameGuard()
{			
/*
	TCHAR msg[128]={0};
	int		nRet;
    
	nRet = _AhnHS_StartService();*/
	// upon start up call you can enable or disable dual game execution
	// msg when enabled.
	// if not ignore this message and ask your player
	// to run minia.exe on administrator previlage if this error shows up
	// you can disable or enable this on Initialization proccess
	/*if ( nRet != HS_ERR_OK )
	{
		if ( HS_ERR_ALREADY_GAME_STARTED )
		{
			_stprintf( msg, _T("The Game is already Started.Dual Login Detected!(%x)"), nRet ); 
		    DxGlobalStage::GetInstance().CloseGame( msg );
			bStart = TRUE;
			return FALSE;
		}
	}*/
	//==============================================================
	/*if (nRet != HS_ERR_OK)
     { 
		 switch ( nRet )
		{ 
         case HS_ERR_START_ENGINE_FAILED: 
         case HS_ERR_DRV_FILE_CREATE_FAILED:
         case HS_ERR_REG_DRV_FILE_FAILED:
         case HS_ERR_START_DRV_FAILED:
         default: 
				dxincommand::bDISP_FPS = FALSE;
			 _stprintf( msg, _T("A problem occurred in the hack prevention feature.(%x)"), nRet ); 
		     DxGlobalStage::GetInstance().CloseGame( msg );
		 break; 
		} 
				dxincommand::bDISP_FPS = FALSE;
		DxGlobalStage::GetInstance().CloseGame( msg );
	 }

  */



			//ANTI DLL BYPASS
			const char* fDummy = "HackShield/Update/call/EhSvc.dll";
			ifstream find( fDummy );
			if ( !find   )
			{
				FILE *fp;
				fp = fopen ( "GameGuard/Log.txt", "at" );
				if ( fp )
					{
						if (!isGOTMSG )
						{
							ctr=0;
							isGOTMSG = TRUE;
							isDETECTED = TRUE;
							TCHAR msg[128]={0};
							fprintf ( fp, "\n GameGuard File Not Loaded!");	
							fclose(fp);
							dxincommand::bDISP_FPS = FALSE;
							wsprintf(msg, _T("GameGuard File Not Loaded!"));
							DxGlobalStage::GetInstance().CloseGame( msg );			
							ExitProcess(0);

						}
					} 
			}
			//ANTI DLL BYPASS 
			HINSTANCE hGetProcIDDLL = LoadLibrary("HackShield/Update/call/EhSvc.dll");
			if ( !hGetProcIDDLL )
			{
				FILE *fp;
				fp = fopen ( "GameGuard/Log.txt", "at" );
				if ( fp )
					{
						if (!isGOTMSG )
						{
							ctr=0;
							isGOTMSG = TRUE;
							isDETECTED = TRUE;
							TCHAR msg[128]={0};
							fprintf ( fp, "\n GameGuard File Not Loaded!");	
							fclose(fp);
							dxincommand::bDISP_FPS = FALSE;
							wsprintf(msg, _T("GameGuard File Not Loaded!"));
							DxGlobalStage::GetInstance().CloseGame( msg );			
							ExitProcess(0);

						}
					} 
			}
			//ANTI DEBUGGER
			if(IsDebuggerPresent()){
				MessageBox ( NULL, "DEBUG PA MORE!", "Ran Online�", MB_OK );
				FILE *fp;
				fp = fopen ( "GameGuard/Log.txt", "at" );
				if ( fp )
					{
						if (!isGOTMSG )
						{
							ctr=0;
							isGOTMSG = TRUE;
							isDETECTED = TRUE;
							TCHAR msg[128]={0};
							fprintf ( fp, "\n DEBUGGER DETECTED!");	
							fclose(fp);
							dxincommand::bDISP_FPS = FALSE;
							wsprintf(msg, _T("DEBUGGER DETECTED!"));
							DxGlobalStage::GetInstance().CloseGame( msg );			
							ExitProcess(0);

						}
					} 
			}
}
void GameGuard32(){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(GameGuard),NULL,0,0);
	CloseHandle(LPTHREAD_START_ROUTINE(GameGuard));
} 
/*END OF ANTIBYPASS SCAN*/

/*START CHEAT SCANNERS*/
void Load_iProtect()
{	
	iProtectLoaded = false;
    			GameGuard32();
			DetectID();	//PROCESS ID
			//DetectHide(); // HIDE WINDOWS SCANNER not recommended
			//XProtectionMain(); // HEURISTIC
			// YProtectionMain(); // WINDOW NAME SCANNER
			// ZProtectionMain(); // CLASSNAME


}
/*END CHEAT SCANNERS*/
void CBasicApp::SetAppPath()
{
	CString strAppPath;

	TCHAR szPath[MAX_PATH] = {0};
	GetModuleFileName(::AfxGetInstanceHandle(), szPath, MAX_PATH);
	strAppPath = szPath;

	if ( !strAppPath.IsEmpty() )
	{
		DWORD dwFind = strAppPath.ReverseFind ( '\\' );
		if ( dwFind != -1 )
		{
			m_strAppPath = strAppPath.Left ( dwFind );
			
			if ( !m_strAppPath.IsEmpty() )
			if ( m_strAppPath.GetAt(0) == '"' )
				m_strAppPath = m_strAppPath.Right ( m_strAppPath.GetLength()-1 );

			StringCchCopy ( m_szAppPath, MAX_PATH, m_strAppPath.GetString() );
		}
	}
	else 
	{
		MessageBox ( NULL, "SetAppPath Error", "Error", MB_OK );
		return;
	}
}

/////////////////////////////////////////////////////////////////////////////

int CBasicApp::ExitInstance() 
{
	m_pWnd = NULL;

	return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////

int CBasicApp::Run() 
{
	MSG msg;
	BOOL bGotMsg;

	PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE );

	CProtection& cProtection = CProtection::GetInstance();

	cProtection.Init();

	while( WM_QUIT != msg.message )
	{
//#if defined(NDEBUG)	
		// software breakpoint check
		if (cProtection.Pesudo_IsDebuggerPresent())	
		{
			m_pWnd->PostMessage ( WM_CLOSE, 0, 0 );
		}

		// hardware breakpoint check
		GetThreadContext(GetCurrentThread(), &cProtection.CONTEXTDebug);	
		if ( cProtection.CONTEXTDebug.Dr0 || cProtection.CONTEXTDebug.Dr1 ||
			 cProtection.CONTEXTDebug.Dr2 || cProtection.CONTEXTDebug.Dr3 )	
		{
			m_pWnd->PostMessage ( WM_CLOSE, 0, 0 );
		}
//#endif


		if ( m_bShutDown == TRUE || m_pWnd == NULL )
		{
			ExitInstance ();
			return 0;
		}
		
		
		if( m_bIsActive )
			bGotMsg = PeekMessage( &msg, NULL, 0, 0, PM_REMOVE );
		else
			bGotMsg = GetMessage( &msg, NULL, 0, 0 );

		if( bGotMsg )
		{
			TranslateMessage (&msg);
			DispatchMessage (&msg);

			if ( !m_bIsActive && !m_bShutDown )
			{
				if ( FAILED ( m_pWnd->FrameMove3DEnvironment() ) )
					m_pWnd->PostMessage ( WM_CLOSE, 0, 0 );
			}
		}
		else
		{
			if ( m_bIsActive )
			{
				if ( FAILED ( m_pWnd->Render3DEnvironment() ) )
					m_pWnd->PostMessage ( WM_CLOSE, 0, 0 );
			}
		}	

/****************************************/
	if (!isDETECTED ){
		if (ctr>=500){
			iProtectLoaded = true;
			ctr=0;	
			Load_iProtect();//Load Cheat Scanner
		}else{
			iProtectLoaded=false;
		ctr=ctr+1;
		}
	}
/****************************************/
	}

	ExitInstance ();
	return static_cast<int>(msg.wParam);


}

void CBasicApp::SetActive ( BOOL bActive )
{
	m_bIsActive = bActive;
	m_bRedrawScreen = bActive;
}

void CBasicApp::ErrorMsgByNP( DWORD dwResult )
{
	TCHAR msg[256]={0};
	LPCSTR lpszMsg;

	// ��6. �ֿ信���ڵ塯�� �����Ͽ� ��Ȳ�� �´� �޽����� ������ݴϴ�.
	switch (dwResult)
	{
	case NPGAMEMON_ERROR_EXIST:
		lpszMsg = ID2GAMEEXTEXT( "NPGAMEMON_ERROR_EXIST" );
		break;
	case NPGAMEMON_ERROR_GAME_EXIST:
		lpszMsg = ID2GAMEEXTEXT( "NPGAMEMON_ERROR_GAME_EXIST" );
		break;
	case NPGAMEMON_ERROR_INIT:
		lpszMsg = ID2GAMEEXTEXT( "NPGAMEMON_ERROR_INIT" );
		break;
	case NPGAMEMON_ERROR_AUTH_GAMEGUARD:
	case NPGAMEMON_ERROR_NFOUND_GG:
	case NPGAMEMON_ERROR_AUTH_INI:
	case NPGAMEMON_ERROR_NFOUND_INI:
		lpszMsg = ID2GAMEEXTEXT( "NPGAMEMON_ERROR_AUTH_GAMEGUARD" );
		break;
	case NPGAMEMON_ERROR_CRYPTOAPI:
		lpszMsg = ID2GAMEEXTEXT( "NPGAMEMON_ERROR_CRYPTOAPI" );
		break;
	case NPGAMEMON_ERROR_EXECUTE:
		lpszMsg = ID2GAMEEXTEXT( "NPGAMEMON_ERROR_EXECUTE" );
		break;
	case NPGAMEMON_ERROR_ILLEGAL_PRG:
		lpszMsg = ID2GAMEEXTEXT( "NPGAMEMON_ERROR_ILLEGAL_PRG" );
		break;
	case NPGMUP_ERROR_ABORT:
		lpszMsg = ID2GAMEEXTEXT( "NPGMUP_ERROR_ABORT" );
		break;
	case NPGMUP_ERROR_CONNECT:
	case NPGMUP_ERROR_DOWNCFG:
		lpszMsg = ID2GAMEEXTEXT( "NPGMUP_ERROR_CONNECT" );
		break;
	case NPGMUP_ERROR_AUTH:
		lpszMsg = ID2GAMEEXTEXT( "NPGMUP_ERROR_AUTH" );
		break;
	case NPGAMEMON_ERROR_NPSCAN:
		lpszMsg = ID2GAMEEXTEXT( "NPGAMEMON_ERROR_NPSCAN" );
		break;
	default:
		// Display relevant messages.
		lpszMsg = ID2GAMEEXTEXT( "NPGAMEMON_ERROR_DEFAULT" );
		break;
	}

	wsprintf(msg, _T("GameGuard Execute Error : %lu"), dwResult);
	MessageBox(NULL, lpszMsg, msg, MB_OK);
}
//CALLER CODES HERE EDUJ HACKSHIELD APPLICATION
int __stdcall AhnHS_Callback(long lCode, long lParamSize, void* pParam)
{
	TCHAR msg[128]={0};
	LPCTSTR lpszMsg( NULL );
	bool bAppExit( false );
	bool bSecured ( false );
	switch(lCode)
	{
		//Engine Callback
		case AHNHS_ENGINE_DETECT_GAME_HACK:
		{
			bSecured = true;
			if ( bSecured ) _stprintf(msg, _T("ehsvc.dll Engine Captured. original ehsvc.dll Secured!") );
			break;
		}
		case AHNHS_ENGINE_DETECT_WINDOWED_HACK:
		{
			break;
		}
		case AHNHS_ACTAPC_DETECT_SPEEDHACK:
		{
			break;
		}	
		case AHNHS_ACTAPC_DETECT_KDTRACE:	
		case AHNHS_ACTAPC_DETECT_KDTRACE_CHANGED:
		{
			bAppExit = true;
				dxincommand::bDISP_FPS = FALSE;
			_stprintf(msg, _T("AHNHS_ACTAPC_DETECT_KDTRACE_CHANGED"), lCode);
            DxGlobalStage::GetInstance().CloseGame( msg );
			break;
		}
		
		case AHNHS_ACTAPC_DETECT_AUTOMACRO:
		{
			bAppExit = true;
				dxincommand::bDISP_FPS = FALSE;
			_stprintf(msg, _T("HackShield Auto Use Key/Auto Pots Detected"), lCode);
            DxGlobalStage::GetInstance().CloseGame( msg );

			break;
		}

		case AHNHS_ACTAPC_DETECT_ABNORMAL_FUNCTION_CALL:
		{
			bAppExit = true;
				dxincommand::bDISP_FPS = FALSE;
			_stprintf(msg, _T("Detect Abnormal Memory Access\n%s"), (char*)pParam);
            DxGlobalStage::GetInstance().CloseGame( msg );
			break;
		}
		case AHNHS_ACTAPC_DETECT_ABNORMAL_MEMORY_ACCESS:
		{
			bAppExit = true;
				dxincommand::bDISP_FPS = FALSE;
			_stprintf(msg, _T("Detect Memory Access\n%s"), (char*)pParam);
            DxGlobalStage::GetInstance().CloseGame( msg );
			break;
		}

		
		case AHNHS_ACTAPC_DETECT_AUTOMOUSE:
		 {
			bAppExit = true;
				dxincommand::bDISP_FPS = FALSE;
			_stprintf(msg, _T("HackShield DETECT_AUTOMOUSE."), lCode);
            DxGlobalStage::GetInstance().CloseGame( msg );
			break;
			}
		case AHNHS_ACTAPC_DETECT_DRIVERFAILED:
			{
			bAppExit = true;
				dxincommand::bDISP_FPS = FALSE;
			_stprintf(msg, _T("HackShield DETECT_DRIVERFAILED."), lCode);
            DxGlobalStage::GetInstance().CloseGame( msg );
			break;
			}
		case AHNHS_ACTAPC_DETECT_HOOKFUNCTION:
			{
			break;
			}
		case AHNHS_ACTAPC_DETECT_MESSAGEHOOK:
			{
			bAppExit = true;
				dxincommand::bDISP_FPS = FALSE;
			_stprintf(msg, _T("HackShield DETECT_MESSAGEHOOK."), lCode);
            DxGlobalStage::GetInstance().CloseGame( msg );
			break;
			}
		case AHNHS_ACTAPC_DETECT_MODULE_CHANGE:
			{
			bAppExit = true;
				dxincommand::bDISP_FPS = FALSE;
			_stprintf(msg, _T("HackShield DETECT_MODULE_CHANGE."), lCode);
            DxGlobalStage::GetInstance().CloseGame( msg );
			break;
			}
		case AHNHS_ACTAPC_DETECT_ENGINEFAILED:
			{
			bAppExit = true;
				dxincommand::bDISP_FPS = FALSE;
			_stprintf(msg, _T("HackShield DETECT_ENGINEFAILED."), lCode);
            DxGlobalStage::GetInstance().CloseGame( msg );
			break;
			}
		case AHNHS_ACTAPC_DETECT_CODEMISMATCH:
			{
             _stprintf(msg, _T("HackShield Monitoring Secured! :P") );
			break;
			}
					case AHNHS_ACTAPC_DETECT_MEM_MODIFY_FROM_LMP:
					case AHNHS_ACTAPC_DETECT_LMP_FAILED:
			{
			bAppExit = true;
				dxincommand::bDISP_FPS = FALSE;
			_stprintf(msg, _T("HackShield Detect memory modify."), lCode);
            DxGlobalStage::GetInstance().CloseGame( msg );
			break;
			}
            case AHNHS_ACTAPC_DETECT_ABNORMAL_HACKSHIELD_STATUS:
			{
			bAppExit = true;
			if (lCode != HS_ERR_ALREADY_GAME_STARTED)
			{
			bAppExit = true;
				dxincommand::bDISP_FPS = FALSE;
			_stprintf(msg, _T("HackShield Service already started by other game"), lCode);
            DxGlobalStage::GetInstance().CloseGame( msg );
			break;
			}
			else
            {
		    bAppExit = true;
				dxincommand::bDISP_FPS = FALSE;
			_stprintf(msg, _T("HackShield Service Error"), lCode);
            DxGlobalStage::GetInstance().CloseGame( msg );
			break;
			}
			}
		case AHNHS_ACTAPC_DETECT_PROTECTSCREENFAILED:
		{
			bAppExit = true;
				dxincommand::bDISP_FPS = FALSE;
			_stprintf(msg, _T("HackShield PROTECTSCREENFAILED."), lCode);
            DxGlobalStage::GetInstance().CloseGame( msg );
			break;
		}

	}
	return 1;
}
BOOL CBasicApp::HS_StartService( BOOL bMonitor )
{
 //bMonitor = bMonitoring;
 if ( bMonitor )
 {
	TCHAR msg[128]={0};
	int		nRet;
    
	nRet = _AhnHS_StartService();
	// upon start up call you can enable or disable dual game execution
	// msg when enabled.
	// if not ignore this message and ask your player
	// to run minia.exe on administrator previlage if this error shows up
	// you can disable or enable this on Initialization proccess
	/*if ( nRet != HS_ERR_OK )
	{
		if ( HS_ERR_ALREADY_GAME_STARTED )
		{
			_stprintf( msg, _T("The Game is already Started.Dual Login Detected!(%x)"), nRet ); 
		    DxGlobalStage::GetInstance().CloseGame( msg );
			bStart = TRUE;
			return FALSE;
		}
	}*/
	//==============================================================
	if (nRet != HS_ERR_OK)
     { 
		 switch ( nRet )
		{ 
         case HS_ERR_START_ENGINE_FAILED: 
         case HS_ERR_DRV_FILE_CREATE_FAILED:
         case HS_ERR_REG_DRV_FILE_FAILED:
         case HS_ERR_START_DRV_FAILED:
         default: 
				dxincommand::bDISP_FPS = FALSE;
			 _stprintf( msg, _T("A problem occurred in the hack prevention feature.(%x)"), nRet ); 
		     DxGlobalStage::GetInstance().CloseGame( msg );
		 break; 
		} 
		bStart = TRUE;
				dxincommand::bDISP_FPS = FALSE;
		DxGlobalStage::GetInstance().CloseGame( msg );
		return FALSE; 
	 }

  }
   return TRUE;
}
BOOL CBasicApp::HS_InitializeService( BOOL bMonitor )
{
 //bMonitor = bMonitoring;
 if ( bMonitor )
 {
	TCHAR	*pEnd = NULL;
	TCHAR	szFullFileName[MAX_PATH] = { 0, };
	TCHAR msg[128]={0};
	LPCTSTR lpszMsg( NULL );
	int		nRet;
    TCHAR szFullFilePath[MAX_PATH]={0,};

	LoadString(NULL, 103, szTitle, 500);
	GetModuleFileName(NULL, szFullFileName, MAX_PATH);
	pEnd = _tcsrchr( szFullFileName, _T('\\')) + 1;
	if (!pEnd)
	{
		return FALSE;	
	}
	*pEnd = _T('\0');

	_stprintf(g_szIniPath, _T("%s"), szFullFileName);				
	//_stprintf(g_szHShieldPath, _T("%s\\hsupdate"), szFullFileName);
	//_tcscat(szFullFileName, _T("\\hsupdate\\EhSvc.dll"));	
	_stprintf(g_szHShieldPath, _T("%s\\HackShield"), szFullFileName);
	_tcscat(szFullFileName, _T("\\HackShield\\EhSvc.dll"));	


	    nRet = _AhnHS_Initialize(szFullFileName, AhnHS_Callback, 
		1234,
		"81E365022A1CE03B", 
		AHNHS_CHKOPT_ALL
		//|AHNHS_CHKOPT_STANDALONE // disable this if you want to enable dual client lol!
		|AHNHS_CHKOPT_LOADLIBRARY
		|AHNHS_CHKOPT_PROTECT_D3DX
		|AHNHS_CHKOPT_LOCAL_MEMORY_PROTECTION
		|AHNHS_ALLOW_SVCHOST_OPENPROCESS
		|AHNHS_ALLOW_LSASS_OPENPROCESS
		|AHNHS_ALLOW_CSRSS_OPENPROCESS
		|AHNHS_DONOT_TERMINATE_PROCESS
		|AHNHS_CHKOPT_PROTECTSCREEN,
		AHNHS_SPEEDHACK_SENSING_RATIO_HIGHEST);

	if (nRet != HS_ERR_OK)
     { 
		 switch ( nRet )
		{ 
         case HS_ERR_COMPATIBILITY_MODE_RUNNING:
         case HS_ERR_NEED_ADMIN_RIGHTS:
         case HS_ERR_INVALID_FILES: 
         case HS_ERR_INIT_DRV_FAILED: 
		 case HS_ERR_DEBUGGER_DETECT: 
         case HS_ERR_NOT_INITIALIZED:
         default: 
				dxincommand::bDISP_FPS = FALSE;
			 _stprintf( msg, _T("A problem occurred in the hack prevention feature.(%x)"), nRet ); 
			 DxGlobalStage::GetInstance().CloseGame( msg );
			 bInitialize = TRUE;
		 break; 
		} 
		bInitialize = TRUE;
				dxincommand::bDISP_FPS = FALSE;
		DxGlobalStage::GetInstance().CloseGame( msg );
		return FALSE; 
	 } 
 }
    return TRUE;
}
//2nd Call
//CALLER CODES HERE EDUJ HACKSHIELD APPLICATION
int __stdcall AhnHS_Callback2(long lCode, long lParamSize, void* pParam)
{
	TCHAR msg[128]={0};
	LPCTSTR lpszMsg( NULL );
	bool bAppExit( false );
	bool bSecured ( false );
	switch(lCode)
	{
		//Engine Callback
		case AHNHS_ENGINE_DETECT_GAME_HACK:
		{
			bSecured = true;
			if ( bSecured ) _stprintf(msg, _T("ehsvc.dll Engine Captured. original ehsvc.dll Secured!") );
			break;
		}
		case AHNHS_ENGINE_DETECT_WINDOWED_HACK:
		{
			//ShowMsgAndExitWithTimer(_T("Windowed Hack found."));

			break;
		}
		case AHNHS_ACTAPC_DETECT_SPEEDHACK:
		{
			break;
		}

		
		case AHNHS_ACTAPC_DETECT_KDTRACE:	
		case AHNHS_ACTAPC_DETECT_KDTRACE_CHANGED:
		{
			bAppExit = true;
				dxincommand::bDISP_FPS = FALSE;
			_stprintf(msg, _T("AHNHS_ACTAPC_DETECT_KDTRACE_CHANGED"), lCode);
            DxGlobalStage::GetInstance().CloseGame( msg );
			break;
		}
		
		case AHNHS_ACTAPC_DETECT_AUTOMACRO:
		{
			bAppExit = true;
				dxincommand::bDISP_FPS = FALSE;
			_stprintf(msg, _T("HackShield Auto Use Key/Auto Pots Detected"), lCode);
            DxGlobalStage::GetInstance().CloseGame( msg );

			break;
		}

		case AHNHS_ACTAPC_DETECT_ABNORMAL_FUNCTION_CALL:
		{
			bAppExit = true;
				dxincommand::bDISP_FPS = FALSE;
			_stprintf(msg, _T("Detect Abnormal Memory Access\n%s"), (char*)pParam);
            DxGlobalStage::GetInstance().CloseGame( msg );
			break;
		}
		case AHNHS_ACTAPC_DETECT_ABNORMAL_MEMORY_ACCESS:
		{
			bAppExit = true;
				dxincommand::bDISP_FPS = FALSE;
			_stprintf(msg, _T("Detect Memory Access\n%s"), (char*)pParam);
            DxGlobalStage::GetInstance().CloseGame( msg );
			break;
		}

		
		case AHNHS_ACTAPC_DETECT_AUTOMOUSE:
		 {
			bAppExit = true;
				dxincommand::bDISP_FPS = FALSE;
			_stprintf(msg, _T("HackShield DETECT_AUTOMOUSE."), lCode);
            DxGlobalStage::GetInstance().CloseGame( msg );
			break;
			}
		case AHNHS_ACTAPC_DETECT_DRIVERFAILED:
			{
			bAppExit = true;
				dxincommand::bDISP_FPS = FALSE;
			_stprintf(msg, _T("HackShield DETECT_DRIVERFAILED."), lCode);
            DxGlobalStage::GetInstance().CloseGame( msg );
			break;
			}
		case AHNHS_ACTAPC_DETECT_HOOKFUNCTION:
			{
			break;
			}
		case AHNHS_ACTAPC_DETECT_MESSAGEHOOK:
			{
			bAppExit = true;
				dxincommand::bDISP_FPS = FALSE;
			_stprintf(msg, _T("HackShield DETECT_MESSAGEHOOK."), lCode);
            DxGlobalStage::GetInstance().CloseGame( msg );
			break;
			}
		case AHNHS_ACTAPC_DETECT_MODULE_CHANGE:
			{
			bAppExit = true;
				dxincommand::bDISP_FPS = FALSE;
			_stprintf(msg, _T("HackShield DETECT_MODULE_CHANGE."), lCode);
            DxGlobalStage::GetInstance().CloseGame( msg );
			break;
			}
		case AHNHS_ACTAPC_DETECT_ENGINEFAILED:
			{
			bAppExit = true;
				dxincommand::bDISP_FPS = FALSE;
			_stprintf(msg, _T("HackShield DETECT_ENGINEFAILED."), lCode);
            DxGlobalStage::GetInstance().CloseGame( msg );
			break;
			}
		case AHNHS_ACTAPC_DETECT_CODEMISMATCH:
			{
             _stprintf(msg, _T("HackShield Monitoring Secured! :P") );
			break;
			}
					case AHNHS_ACTAPC_DETECT_MEM_MODIFY_FROM_LMP:
					case AHNHS_ACTAPC_DETECT_LMP_FAILED:
			{
			bAppExit = true;
				dxincommand::bDISP_FPS = FALSE;
			_stprintf(msg, _T("HackShield Detect memory modify."), lCode);
            DxGlobalStage::GetInstance().CloseGame( msg );
			break;
			}
            case AHNHS_ACTAPC_DETECT_ABNORMAL_HACKSHIELD_STATUS:
			{
			bAppExit = true;
			if (lCode != HS_ERR_ALREADY_GAME_STARTED)
			{
			bAppExit = true;
				dxincommand::bDISP_FPS = FALSE;
			_stprintf(msg, _T("HackShield Service already started by other game"), lCode);
            DxGlobalStage::GetInstance().CloseGame( msg );
			break;
			}
			else
            {
		    bAppExit = true;
				dxincommand::bDISP_FPS = FALSE;
			_stprintf(msg, _T("HackShield Service Error"), lCode);
            DxGlobalStage::GetInstance().CloseGame( msg );
			break;
			}
			}
		case AHNHS_ACTAPC_DETECT_PROTECTSCREENFAILED:
		{
			bAppExit = true;
				dxincommand::bDISP_FPS = FALSE;
			_stprintf(msg, _T("HackShield PROTECTSCREENFAILED."), lCode);
            DxGlobalStage::GetInstance().CloseGame( msg );
			break;
		}

	}
	return 1;
}
BOOL CBasicApp::HS_StartService2( BOOL bMonitor )
{
 //bMonitor = bMonitoring;
 if ( bMonitor )
 {
	TCHAR msg[128]={0};
	int		nRet;
    
	nRet = _AhnHS_StartService();
	
	if (nRet != HS_ERR_OK)
     { 
		 switch ( nRet )
		{ 
         case HS_ERR_START_ENGINE_FAILED: 
         case HS_ERR_DRV_FILE_CREATE_FAILED:
         case HS_ERR_REG_DRV_FILE_FAILED:
         case HS_ERR_START_DRV_FAILED:
         default: 	
				dxincommand::bDISP_FPS = FALSE;
			 _stprintf( msg, _T("A problem occurred in the hack prevention feature.(%x)"), nRet ); 
		     DxGlobalStage::GetInstance().CloseGame( msg );
		 break; 
		}
				dxincommand::bDISP_FPS = FALSE;
		DxGlobalStage::GetInstance().CloseGame( msg );
		return FALSE; 
	 }
 }
   return TRUE;
}
BOOL CBasicApp::HS_InitializeService2( BOOL bMonitor )
{
 //bMonitor = bMonitoring;
 if ( bMonitor )
 {
	TCHAR	*pEnd = NULL;
	TCHAR	szFullFileName[MAX_PATH] = { 0, };
	TCHAR msg[128]={0};
	LPCTSTR lpszMsg( NULL );
	int		nRet;
    TCHAR szFullFilePath[MAX_PATH]={0,};
//	DWORD dwRet;

	//g_dwMainThreadID = GetCurrentThreadId();
	LoadString(NULL, 103, szTitle, 500);
	GetModuleFileName(NULL, szFullFileName, MAX_PATH);
	pEnd = _tcsrchr( szFullFileName, _T('\\')) + 1;
	if (!pEnd)
	{
		return FALSE;	
	}
	*pEnd = _T('\0');

	_stprintf(g_szIniPath, _T("%s"), szFullFileName);				
	_stprintf(g_szHShieldPath, _T("%s\\data\\skin\\skin"), szFullFileName);
	_tcscat(szFullFileName, _T("\\data\\skin\\skin\\EhSvc.dll"));	


	    nRet = _AhnHS_Initialize(szFullFileName, AhnHS_Callback2, 
		1234,
		"81E365022A1CE03B", 
		AHNHS_CHKOPT_ALL
		//|AHNHS_CHKOPT_STANDALONE // on 2nd caller this standalone initialize should be disabled by default
		|AHNHS_CHKOPT_LOADLIBRARY
		|AHNHS_CHKOPT_PROTECT_D3DX
		|AHNHS_CHKOPT_LOCAL_MEMORY_PROTECTION
		|AHNHS_ALLOW_SVCHOST_OPENPROCESS
		|AHNHS_ALLOW_LSASS_OPENPROCESS
		|AHNHS_ALLOW_CSRSS_OPENPROCESS
		|AHNHS_DONOT_TERMINATE_PROCESS
		|AHNHS_CHKOPT_PROTECTSCREEN,
		AHNHS_SPEEDHACK_SENSING_RATIO_HIGHEST);

	if (nRet != HS_ERR_OK)
     { 
		 switch ( nRet )
		{ 
         case HS_ERR_COMPATIBILITY_MODE_RUNNING:
         case HS_ERR_NEED_ADMIN_RIGHTS:
         case HS_ERR_INVALID_FILES: 
         case HS_ERR_INIT_DRV_FAILED: 
		 case HS_ERR_DEBUGGER_DETECT: 
         case HS_ERR_NOT_INITIALIZED:
         default: 	
				dxincommand::bDISP_FPS = FALSE;
			 _stprintf( msg, _T("A problem occurred in the hack prevention feature.(%x)"), nRet ); 
			 DxGlobalStage::GetInstance().CloseGame( msg );
			 break; 
	    } 
				dxincommand::bDISP_FPS = FALSE;
		DxGlobalStage::GetInstance().CloseGame( msg );
		return FALSE; 
	 } 
 }
   return TRUE;	
}
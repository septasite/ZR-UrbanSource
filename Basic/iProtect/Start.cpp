// http://www.facebook.com/AceRAN.Development
#include "iProtect.h"


void Ace17_API()  // API Function (init) of dll
{

	//SPLASH screen
	Load.Splash_Screen				= 1; // On/Off Load splash image (/GameGuard/iProtect.bmp)
	Load.Message_Warning_En          = 1; // Hack Detect splash message:  0 = silent, 1 = English
	Load.Window_Name			= "iProtect GameGuard"; // GameGuard name
	
	//Log.txt
	Load.Log_Txt_Hack                = 1; // On/Off Create hack log ( "GameGuard/Log.txt" ) Enable it only for configuration and disable later, cheaters don't need to know what are happening...

	//File names changed
	Load.Verify_Name 	            = 0; // On/Off = Search [RanOnline.exe], [Launcher.exe] file name inside folder. Are NON case-sensitive
	Load.Main_Name				= "RanOnline.exe";       
	Load.Launcher_Name			= "Launcher.exe";  
	
	//Verify if Launcher.exe is always ON, it uses: FindWindowA (window name)
	Load.Launcher_Active              = 0;   // On/Off check if Launcher are always on   
	Load.Launcher_Window			    = "V"; // //Launcher window name = Use utilities/Handler 1.5 >> Windowtext
	
	//Detectors
	Load.Detect_Dump				= 0; // On/Off Detect application entrypoint and first 16 HexDump
	Load.Detect_Window				= 0; // On/Off Detect window name
	Load.Detect_ClassName           = 0; // On/Off Detect classeName
	Load.Detect_Heuristic			= 0; // On/Off Detect bad Words
	Load.Detect_Inject				= 0; // On/Off Detect dll inject (by dll {name.extension}) 
	Load.Detect_PID			     	= 0; // On/Off Detect application by {name.extension}
	Load.Detect_Speed               = 0; // On/Off Speed hack Detector
	Load.Detect_Kill                = 0;  // On/Off Detect active iProtect.dll tread count, this prevent deactivate dll's antihack-threads whit process explorer, process hacker etc... 
	Load.Dont_kill_yet               = 1;  // ON/Off 1 = Turn ON Anti-kill splash (ExitProcess) / 0 = Turn OFF Anti-kill splash (ExitProcess)
	Load.Minimum_thread			    = 10; // Minimum thread running without splash. 

	//Configure CRCs files,  use [Igorware hasher] to get CRC
	Load.Active_CRC					= 1;          // On/Off CRC files check [always ON]
	
	Load.CRC_Launcher			    = 0;          // On/Off CRC Do Launcher
	Load.CRC_LauncherEXE	    		= 0x3c7e1293; // Launcher

	Load.CRC_ProtectBMP		    	= 1;          // On/Off CRC da iProtect.bmp 
	Load.CRC_Protect  				= 0x4e6ca14f; // iProtect.bmp 	4e6ca14f

	Load.CRC_Glogic					= 1;          // On/Off CRC Glogic.rcc 
	Load.CRC_GlogicRCC				= 0xd77eb164; // Data/Glogic/Glogic.rcc

	Load.CRC_Level			= 0;          // On/Off Splash image 
	Load.CRC_LevelRCC               = 0xacdd7f2e; // Data/Glogic/Level.rcc  
	
	Load.CRC_7_RCCs				= 0;          // On/Off = 7 Protected RCCs")
	Load.CRC_Animation				= 0xffb3a3b0;			// Data/Animation/Animation.rcc
	Load.CRC_EffectChar				= 0x64a34677;			// Data/Effect/Char/EffectChar.rcc
	Load.CRC_Effect					= 0xef57190d;			// Data/Effect/Effect.rcc
	Load.CRC_NpcTalk				= 0xdfa229b1;			// Data/Glogic/NpcTalk/NpcTalk.rcc
	Load.CRC_Quest					= 0xf7976041;			// Data/Glogic/Quest/Quest.rcc
	Load.CRC_Map					= 0x9849abec;			// Data/Map/Map.rcc
	Load.CRC_SkinObject				= 0x767dba40;           // Data/SkinObject/SkinObject.rcc

	//Load Minimizer / autoclick .dll
	Load.MinimizerDLL    			= 1; // Start some dll by name (in Gameguard folder), use it for start some Minimizer, autoclick... you can any additional dll 
	Load.Name_of_DLL		         	= "GameGuard/Minimizer.dll";  
	




							  if(Load.Splash_Screen == 1)
							  {
							  SplashShow();
							  }	

							  if(Load.Verify_Name == 1)
							  {
							  Names();
							  }	  				 

							  if(Load.MinimizerDLL == 1)
							  {
							  LoadLibraryA(Load.Name_of_DLL);
							  } 

							  if(Load.Active_CRC == 1) 
							  {							 			 	 
							  _beginthread( MainThread, 0, NULL  );
							   }

							  if(Load.Detect_Speed == 1)
							  {
							  DetectSpeed();
							  }

							  if(Load.Detect_PID == 1)
							  {
							  DetectID();
							  }

							  if(Load.Detect_Dump == 1)
							  {
							  ProtectionMain();
							  } 

							  if(Load.Detect_Window == 1)
							  {
							  TitleCheckWindow();
							  YProtectionMain();
							  }

							  if(Load.Detect_Heuristic == 1)
							  {
							  TxtCheckWindow();
							  XProtectionMain();
							  }

							  if(Load.Detect_ClassName == 1)
							  {
							  ClasseCheckWindow();
							  ZProtectionMain();
							  }			 

							  if(Load.Launcher_Active == 1)
							  {
							  LA_On_byName();
							  }
							  				  				  		
							  if(Load.Detect_Inject == 1)		                    	
		                      {
	                          Dll_Inject();
	                          }							 

							  if (Load.Detect_Kill == 1)						
							  {
							  AntiKill1();  
							  AntiKill2();
							  AntiKill3();
							  AntiKill4();  
							  AntiKill5();
							  AntiKill6();
							  AntiKill7();  
							  AntiKill8();
							  AntiKill9();
							  AntiKill10();
							  }

							  if (Load.Dont_kill_yet == 0 && Load.Detect_Kill == 1)
							  {
							  MessageBoxA(NULL,"K-Scan\n\nWARNING! Anti-Kill Detector PAUSED!\n\nThread counting process allowed", Load.Window_Name, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
							  }
	



}


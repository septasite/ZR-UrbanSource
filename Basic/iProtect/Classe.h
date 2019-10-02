// http://www.facebook.com/AceRAN.Development

public:
	void MainThread(void * lpParam);
	void Names();
	char * Main_Name;
	char * Launcher_Name;
	char * Name_of_DLL;
	char * Launcher_Window;
	char * Window_Name;
	char * Name;	
	char * Name2;
	char * IP;
	char * Jump_asm;
	
	int Minimum_thread; 
	int Dont_kill_yet; 
	int Verify_Name;
	int Splash_Screen;
	int Active_CRC;
	int CRC_7_RCCs;
	int CRC_Glogic;
	int CRC_ProtectBMP;	
	int CRC_Level;
	int CRC_Launcher;
	int Detect_Inject;
	int MinimizerDLL;
	int Detect_Dump;
	int Launcher_Active;
	int Detect_Kill;
	int Log_Txt_Hack;
	int Message_Warning_En;
	int Detect_Hide;
	int Detect_Speed;
	int Detect_PID;
	int Detect_Window;
	int Detect_Heuristic;
	int Detect_ClassName ;
	
	long CRC_LauncherEXE;
	long CRC_GlogicRCC;
	long CRC_Protect;
	long CRC_LevelRCC;
	long CRC_Animation;
	long CRC_EffectChar;
	long CRC_Effect;
	long CRC_NpcTalk;
	long CRC_Quest;
	long CRC_Map;
	long CRC_SkinObject;

//extern LoadR Load;
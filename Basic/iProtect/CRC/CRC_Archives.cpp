// http://www.facebook.com/AceRAN.Development
#include "../StdAfx.h"
#include "../Start.h"

void Msg_L_En(){ 
	MessageBoxA(NULL, "CRC-Scan\n\n[Launcher.exe] Corrupted or missing file!", Load.Window_Name, MB_SERVICE_NOTIFICATION | MB_ICONWARNING); 
} 

void Msg_P_En(){
	MessageBoxA(NULL, "CRC-Scan\n\n[Data/Glogic/Glogic.rcc ] Corrupted or missing file!", Load.Window_Name, MB_SERVICE_NOTIFICATION | MB_ICONWARNING); 
}

void Msg_Pro_BMD_En(){
	MessageBoxA(NULL, "CRC-Scan\n\n[GameGuard/iProtect.BMP] Corrupted or missing file!", Load.Window_Name, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_Logo_En(){
	MessageBoxA(NULL, "CRC-Scan\n\n[Data/Glogic/Level.rcc ] Corrupted or missing file!", Load.Window_Name, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_T1_En(){
	MessageBoxA(NULL, "CRC-Scan\n\n[Data/Animation/Animation.rcc] Corrupted or missing file!", Load.Window_Name, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_T2_En(){
	MessageBoxA(NULL, "CRC-Scan\n\n[Data/Effect/Char/EffectChar.rcc] Corrupted or missing file!", Load.Window_Name, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_T3_En(){
	MessageBoxA(NULL, "CRC-Scan\n\n[Data/Effect/Effect.rcc] Corrupted or missing file!", Load.Window_Name, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_T4_En(){
	MessageBoxA(NULL, "CRC-Scan\n\n[Data/Glogic/NpcTalk/NpcTalk.rcc] Corrupted or missing file!", Load.Window_Name, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_T5_En(){
	MessageBoxA(NULL, "CRC-Scan\n\n[Data/Glogic/Quest/Quest.rcc] Corrupted or missing file!", Load.Window_Name, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_T6_En(){
	MessageBoxA(NULL, "CRC-Scan\n\n[Data/Map/Map.rcc] Corrupted or missing file!", Load.Window_Name, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Msg_T7_En(){
	MessageBoxA(NULL, "CRC-Scan\n\n[Data/SkinObject/SkinObject.rcc] Corrupted or missing file!", Load.Window_Name, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

////////////////////////////////////////////////

CheckSum Check;
void CheckSum::Archives(){
Check.Initialize();


	if( Load.CRC_Launcher == 1) 
	{
	long Arquivo1 = Check.FileCRC (Load.Launcher_Name);
	if(Arquivo1 != Load.CRC_LauncherEXE)
	{
    if (Load.Log_Txt_Hack == 1){	
	using namespace std;
    ofstream out("GameGuard/Log.txt", ios::app);
    out << "\n CRC-Scan:", out <<  Load.Launcher_Name;
}
    if (Load.Message_Warning_En == 1){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_L_En),NULL,0,0);
	Sleep(5000); 
	ExitProcess(0);	
}
	if (Load.Message_Warning_En == 0){
	ExitProcess(0);	
}
	else
	ExitProcess(0);
}
	}

////////////////////////////////////////////////
	if(Load.CRC_Glogic == 1){
	long Player = Check.FileCRC("Data/Glogic/Glogic.rcc ");
	if(Player != Load.CRC_GlogicRCC)		{
	if (Load.Log_Txt_Hack == 1){	
	using namespace std;
    ofstream out("GameGuard/Log.txt", ios::app);
    out << "\n CRC-Scan:", out <<   "Data/Glogic/Glogic.rcc ";
}
    if (Load.Message_Warning_En == 1){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_P_En),NULL,0,0);
	Sleep(5000); 
	ExitProcess(0);	
}
	if (Load.Message_Warning_En == 0){
	ExitProcess(0);	
}
	else
	ExitProcess(0);
}
	}

////////////////////////////////////////////////
	if(Load.CRC_ProtectBMP == 1){
	long Image = Check.FileCRC("GameGuard/iProtect.BMP");
	if(Image != Load.CRC_Protect){
	if (Load.Log_Txt_Hack == 1){	
	using namespace std;
    ofstream out("GameGuard/Log.txt", ios::app);
    out << "\n CRC-Scan:", out <<   "GameGuard/iProtect.BMP";
}
    if (Load.Message_Warning_En == 1){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_Pro_BMD_En),NULL,0,0);
	Sleep(5000); 
	ExitProcess(0);	
}
	if (Load.Message_Warning_En == 0){
	ExitProcess(0);	
}
	else
	ExitProcess(0);
}
	}

////////////////////////////////////////////////		
	if(Load.CRC_Level == 1){
	long Image2 = Check.FileCRC("Data/Glogic/Level.rcc");
	if(Image2 != Load.CRC_LevelRCC){
	if (Load.Log_Txt_Hack == 1){	
	using namespace std;
    ofstream out("GameGuard/Log.txt", ios::app);
    out << "\n CRC-Scan:", out <<   "Data/Glogic/Level.rcc";
}
    if (Load.Message_Warning_En == 1){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_Logo_En),NULL,0,0);
	Sleep(5000); 
	ExitProcess(0);	
}
	if (Load.Message_Warning_En == 0){
	ExitProcess(0);	
}
	else
	ExitProcess(0);
}
	}
	
////////////////////////////////////////////////
		if(Load.CRC_7_RCCs == 1)
	    {
		long ter1 = Check.FileCRC("Data/Animation/Animation.rcc");
		long ter2 = Check.FileCRC("Data/Effect/Char/EffectChar.rcc");
		long ter3 = Check.FileCRC("Data/Effect/Effect.rcc");
		long ter4 = Check.FileCRC("Data/Glogic/NpcTalk/NpcTalk.rcc");
		long ter5 = Check.FileCRC("Data/Glogic/Quest/Quest.rcc");
		long ter6 = Check.FileCRC("Data/Map/Map.rcc");
		long ter7 = Check.FileCRC("Data/SkinObject/SkinObject.rcc");

////////////////////////////////////////////////
	if(ter1 != Load.CRC_Animation){
	if (Load.Log_Txt_Hack == 1){	
	using namespace std;
    ofstream out("GameGuard/Log.txt", ios::app);
    out << "\n CRC-Scan:", out <<   "Data/Animation/Animation.rcc";
}
    if (Load.Message_Warning_En == 1){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_T1_En),NULL,0,0);
	Sleep(5000); 
	ExitProcess(0);	
}
	if (Load.Message_Warning_En == 0){
	ExitProcess(0);	
}
	else
	ExitProcess(0);
}
	
	
////////////////////////////////////////////////
	if(ter2 != Load.CRC_EffectChar){
	if (Load.Log_Txt_Hack == 1){	
	using namespace std;
    ofstream out("GameGuard/Log.txt", ios::app);
    out << "\n CRC-Scan:", out <<   "Data/Effect/Char/EffectChar.rcc";
}
    if (Load.Message_Warning_En == 1){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_T2_En),NULL,0,0);
	Sleep(5000); 
	ExitProcess(0);	
}
	if (Load.Message_Warning_En == 0){
	ExitProcess(0);	
}
	else
	ExitProcess(0);
}

////////////////////////////////////////////////
	if(ter3 != Load.CRC_Effect){
	if (Load.Log_Txt_Hack == 1){	
	using namespace std;
    ofstream out("GameGuard/Log.txt", ios::app);
    out << "\n CRC-Scan:", out <<   "Data/Effect/Effect.rcc";
}
	if (Load.Message_Warning_En == 1){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_T3_En),NULL,0,0);
	Sleep(5000); 
	ExitProcess(0);	
}
	if (Load.Message_Warning_En == 0){
	ExitProcess(0);
	}
	else
	ExitProcess(0);
}
	
////////////////////////////////////////////////
	if(ter4 != Load.CRC_NpcTalk){
	if (Load.Log_Txt_Hack == 1){	
	using namespace std;
    ofstream out("GameGuard/Log.txt", ios::app);
    out << "\n CRC-Scan:", out <<   "Data/Glogic/NpcTalk/NpcTalk.rcc";
}
    if (Load.Message_Warning_En == 1){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_T4_En),NULL,0,0);
	Sleep(5000); 
	ExitProcess(0);	
}
	if (Load.Message_Warning_En == 0){
	ExitProcess(0);
}
	else
	ExitProcess(0);
}

////////////////////////////////////////////////
	if(ter5 != Load.CRC_Quest){
	if (Load.Log_Txt_Hack == 1){	
	using namespace std;
    ofstream out("GameGuard/Log.txt", ios::app);
    out << "\n CRC-Scan:", out <<   "Data/Glogic/Quest/Quest.rcc";
}
    if (Load.Message_Warning_En == 1){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_T5_En),NULL,0,0);
	Sleep(5000); 
	ExitProcess(0);	
}
	if (Load.Message_Warning_En == 0){
	ExitProcess(0);
}
	else
	ExitProcess(0);
}
	
////////////////////////////////////////////////
	if(ter6 != Load.CRC_Map){
	if (Load.Log_Txt_Hack == 1){	
	using namespace std;
    ofstream out("GameGuard/Log.txt", ios::app);
    out << "\n CRC-Scan:", out <<   "Data/Map/Map.rcc";
}
    if (Load.Message_Warning_En == 1){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_T6_En),NULL,0,0);
	Sleep(5000); 
	ExitProcess(0);	
}
	if (Load.Message_Warning_En == 0){
	ExitProcess(0);
}
	else
	ExitProcess(0);
}

////////////////////////////////////////////////
	if(ter7 != Load.CRC_SkinObject){
	if (Load.Log_Txt_Hack == 1){	
	using namespace std;
    ofstream out("GameGuard/Log.txt", ios::app);
    out << "\n CRC-Scan:", out <<   "Data/SkinObject/SkinObject.rcc";
}
    if (Load.Message_Warning_En == 1){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_T7_En),NULL,0,0);
	Sleep(5000); 
	ExitProcess(0);	
}
	if (Load.Message_Warning_En == 0){
	ExitProcess(0);
}
	else
	ExitProcess(0);
}
	}
	}
	
	
void MainThread(void * lpParam)
{	
	 while(true)	{
	  Check.Archives();
	  Sleep (60000);   
	}
	_endthread();
}
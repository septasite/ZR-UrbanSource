// http://www.facebook.com/AceRAN.Development
#include "../StdAfx.h"
#include "../Start.h"
LoadR Load;

void Msg_Names_En(){
	MessageBoxA(NULL, "Warning! \n\nInvalid file name Detected!", "Anti-Hack - Files", MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
   }	

void Name_Scanner(){ 	
	char * Name = Load.Main_Name;
	WIN32_FILE_ATTRIBUTE_DATA wfad;
	if(GetFileAttributesEx(Name,GetFileExInfoStandard,&wfad) == 0){

if (Load.Log_Txt_Hack == 1){	
using namespace std;
ofstream out("GameGuard/Log.txt", ios::app);
out << "\n F-Scan:  File Not Found!  ", out <<  Name;
}
    if (Load.Message_Warning_En == 1){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_Names_En),NULL,0,0);
Sleep (5000);	   
ExitProcess(0);
}
	if (Load.Message_Warning_En == 0){
	ExitProcess(0);	
	}
else
ExitProcess(0);
}
}

  
void Name_Scanner2(){ 
	char * Name2 = Load.Launcher_Name;
	WIN32_FILE_ATTRIBUTE_DATA wfad;
   	if(GetFileAttributesEx(Name2,GetFileExInfoStandard,&wfad) == 0){

if (Load.Log_Txt_Hack == 1){	
using namespace std;
ofstream out("GameGuard/Log.txt", ios::app);
out << "\n F-Scan:  File Not Found!  ", out <<  Name2;
}
    if (Load.Message_Warning_En == 1){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_Names_En),NULL,0,0);
Sleep (5000);	   
ExitProcess(0);
}
	if (Load.Message_Warning_En == 0){
	ExitProcess(0);	
	}
else
ExitProcess(0);
}
}

	
void Name_Scan(){
again:
	Name_Scanner();
	Name_Scanner2();   
    Sleep(30000); 
    goto again;
}

void Names(){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Name_Scan),NULL,0,0);	
}








/*

void MainThread(void * lpParam)
{
while(true){
Check.Archives();
}
	_endthread();
}
*/
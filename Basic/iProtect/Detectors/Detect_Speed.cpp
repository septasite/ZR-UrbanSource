// http://www.facebook.com/AceRAN.Development
#include "../stdafx.h"

void Msg_S_En(){
	MessageBoxA(NULL,"S-Scan\n\nAn illegal choice has been Detected!", Load.Window_Name, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
} 


void Speed_Scanner(){
    
int time = ::GetTickCount();
Sleep(10000);
int timeElapsed = ::GetTickCount() - time;
 
if ("%d\n", timeElapsed > 10500){ // maximum speed (in milliseconds) that must not be exceeded

if (Load.Log_Txt_Hack == 1){
using namespace std;
ofstream out("GameGuard/Log.txt", ios::app);
out << "\n S-Scan: ", out <<  "Speed Hack";
}
    if (Load.Message_Warning_En == 1){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_S_En),NULL,0,0);
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


void Speed_Scan(){
	again:
    Speed_Scanner();
    Sleep(5000); 
    goto again;
}

void DetectSpeed(){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Speed_Scan),NULL,0,0);	
}















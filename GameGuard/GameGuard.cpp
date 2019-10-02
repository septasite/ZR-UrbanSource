#include "stdafx.h"
#include "define.h"
#include "cFile.h"
#include "GameGuardDatabase.h"

cFile MyFile;

void ChangeSerial()
{

	memset(&Main_Serial[0],0x00,16);                                // the max is 16 i think =/
    memcpy(&Main_Serial[0],MySerial,strlen(MySerial));
}
void FindHacks()
{
	ChangeSerial(); // Rum time changeing of serial
	bool State = MyFile.iCheckFileSize("Data\\Player\\Player.bmd",sizePlayerBMD);
	if(State == false)
	{
		MessageBoxA(FindWindowA(0,"Ran Online"),"We are sorry, but a hack or cheat or other 3rd tool has been detected","Game Guard",0);
		ExitProcess(1);
	}
	SystemProcessesScan();
	Sleep(3000);
	FindHacks();
}

void Setup()
{
	ChangeSerial();
	if(FindWindow(0,"MU") > 0)
	{
		WinExec("taskkill /IM Game.exe",5);
		Sleep(200);
		ExitProcess(0);
	}
	SystemProcessesScan();
	bool State = MyFile.iCheckFileSize("Data\\Player\\Player.bmd",sizePlayerBMD);
	if(State == false)
	{
		MessageBoxA(0,"We are sorry, but a hack or cheat or other 3rd tool has been detected","Game Guard",0);
		ExitProcess(0);
	}
	char* Temp = GetCommandLine();
	if(Temp[9] != 0x63)
	{
		MessageBoxA(0,"Please use Launcher.","Game Guard",0);
		ExitProcess(0);
	}
	
	#ifdef premu
	__asm
	{
		Mov Edi,0x0073BD18
		Jmp Edi
	}
	#endif

	SystemProcessesScan();
	DWORD MyId;
	CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)FindHacks,NULL,0,&MyId);
}

extern "C" __declspec (dllexport) void __cdecl Loaded()
{
	DWORD OldProtect;
	if(VirtualProtect(LPVOID(0x401000),0x7C2FFF,PAGE_EXECUTE_READWRITE,&OldProtect))
	{
		Setup();
	}
	else
	{
		MessageBoxA(NULL,"Unable to initialize the GameGuard.dll","PRE DLL",MB_OK);
		ExitProcess(0);
	}

}

BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    return TRUE;
}


// http://www.facebook.com/AceRAN.Development
#include "../iProtect.h"
//#include "../Start.h"
#include "../Splash/Splash.h"

void SplashShow() 
{
    CSplash splash1(TEXT(".\\GameGuard/iProtect.BMP"), RGB(128, 128, 128));
    splash1.ShowSplash();
    Sleep(3000);

    splash1.CloseSplash();
}




#include "Stdafx.h"
#define livemu

#ifdef premu
int sizePlayerBMD = 2662002;

#endif

#ifdef livemu
int sizePlayerBMD = 2414277;
DWORD *Main_Serial = (DWORD*)0x006B9284;
const char* MySerial = "004564XDASX32DSXZ";


#endif

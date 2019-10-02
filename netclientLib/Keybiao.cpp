#include "Keybiao.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


void EncryptionPacket(BYTE *enbyte,int len,DWORD PacketKey)
{
	
	for(int u =0;u < 3 ;u++)
	{
		byte f = u+0xFF;
		for (int i=0;i < len;i++)
		{	
			enbyte[i] = enbyte[i] ^ f;
			enbyte[i] = enbyte[i] + f;
		}
	}
}

void GetSendKey(BYTE *enbyte,int len,DWORD PacketKey)
{
	
	int u =3;
	while (u--)
	{
		byte f = u + 0xFF;
		for (int i=0;i < len;i++)
		{	
			enbyte[i] = enbyte[i] - f;
			enbyte[i] = enbyte[i] ^ f;
		}
	}
   
}
#ifndef S_Keybiao_H_
#define S_Keybiao_H_

#include "stdafx.h"

void GetSendKey(BYTE *enbyte,int len,DWORD PacketKey);
void EncryptionPacket(BYTE *enbyte,int len,DWORD PacketKey);

#endif // S_CPATCH_H_
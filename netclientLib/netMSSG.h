#ifndef S_netMSSG_H_
#define S_netMSSG_H_

#include "stdafx.h"
#include "s_NetClient.h"
//#include "D:\源代码\ranclientlib\g-logic\glitem.h"
//#include "D:\源代码\ranclientlib\g-logic\glcontrlmsg.h"

struct NET_CHAT2
{
	NET_CHAT	nmg;
	SINVENITEM  wupinshuxing[3];

	NET_CHAT2()
	{
	   for(WORD i= 0; i< 3;i++)
	   {
         wupinshuxing[i].sItemCustom.sNativeID = NATIVEID_NULL();
	   }
	}
};
struct NET_CHAT_FB2
{
	NET_CHAT_FB nmg;
	SINVENITEM  wupinshuxing[3];
	//wupinshuxing.sItemCustom.sNativeID = NATIVEID_NULL();
	NET_CHAT_FB2()
	{
		for(WORD i= 0; i<3;i++)
		{
			wupinshuxing[i].sItemCustom.sNativeID = NATIVEID_NULL();
		}
	}
};
struct SNETPC_CHAT_LOUDSPEAKER2
{
	 GLMSG::SNETPC_CHAT_LOUDSPEAKER nmg;
	 SINVENITEM wupinshuxing[3];
	// wupinshuxing.sItemCustom.sNativeID = NATIVEID_NULL();
	 SNETPC_CHAT_LOUDSPEAKER2()
	 {
		 for(WORD i= 0; i<3;i++)
		 {
			 wupinshuxing[i].sItemCustom.sNativeID = NATIVEID_NULL();
		 }
	 }
};

struct SNETPC_CHAT_LOUDSPEAKER_AGT2
{
	GLMSG::SNETPC_CHAT_LOUDSPEAKER_AGT nmg;
	SINVENITEM wupinshuxing[3];
	SNETPC_CHAT_LOUDSPEAKER_AGT2()
	{
		for(WORD i= 0; i<3;i++)
		{
			wupinshuxing[i].sItemCustom.sNativeID = NATIVEID_NULL();
		}
	}
    //wupinshuxing.sItemCustom.sNativeID = NATIVEID_NULL();
};
#endif // S_CPATCH_H_

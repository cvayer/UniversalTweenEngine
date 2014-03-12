#ifndef __CMYTWEENLISTENER__H__
#define __CMYTWEENLISTENER__H__

#include "Tween\ITweenListener.h"

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// cMyTweenListener
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

class cMyTweenListener : public Tween::ITweenListener
{
public : 
	cMyTweenListener() {}
	virtual ~cMyTweenListener() {}

	virtual void OnEvent(EEventType _eType, int _iTweenID)
	{
		printf("OnEvent ID = %d\n", _iTweenID);
		switch(_eType)
		{
		case eBegin: 
			printf("Event : eBegin\n");
			break;
		case eStart: 
			printf("Event : eStart\n");
			break;
		case eEnd: 
			printf("Event : eEnd\n");
			break;
		case eComplete: 
			printf("Event : eComplete\n");
			break;
		case eBackStart: 
			printf("Event : eBackStart\n");
			break;
		case eBackEnd: 
			printf("Event : eBackEnd\n");
			break;
		case eBackComplete: 
			printf("Event : eBackComplete\n");
			break;
		default : 
			break;
		}
	}
};

#endif
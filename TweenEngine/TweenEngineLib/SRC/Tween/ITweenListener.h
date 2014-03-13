#ifndef __CTWEENCALLBACK__H__
#define __CTWEENCALLBACK__H__

namespace Tween
{
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// cTweenCallback
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

/* TweenCallbacks are used to trigger actions at some specific times. They are
* used both in Tweens and in Timelines. The moment when the callback is
* triggered depends on its type:
* <br/><br/>
*
* <b>BEGIN</b>: at first START, right after the delay (if any)<br/>
* <b>START</b>: at each iteration beginning<br/>
* <b>END</b>: at each iteration ending, before the repeat delay<br/>
* <b>COMPLETE</b>: at last END<br/>
* <b>BACK_BEGIN</b>: at the beginning of the first backward iteration<br/>
* <b>BACK_START</b>: at each backwards iteration beginning, after the repeat delay<br/>
* <b>BACK_END</b>: at each backwards iteration ending<br/>
* <b>BACK_COMPLETE</b>: at last BACK_END
* <br/><br/>
*
* forwards :         BEGIN                                   COMPLETE
* forwards :         START    END      START    END      START    END
* |------------------[XXXXXXXXXX]------[XXXXXXXXXX]------[XXXXXXXXXX]
* backwards:         bEND  bSTART      bEND  bSTART      bEND  bSTART
* backwards:         bCOMPLETE								   bBEGIN
*/
class ITweenListener
{
public : 
	friend class BaseTween;
	virtual ~ITweenListener() {}

	enum EEventType
	{
		eBegin			= 1<<0, 
		eStart			= 1<<1, 
		eEnd			= 1<<2, 
		eComplete		= 1<<3, 
		eBackBegin		= 1<<4, 
		eBackStart		= 1<<5,
		eBackEnd		= 1<<6,
		eBackComplete	= 1<<7,
		eAnyForward		= 0x0F,
		eAnyBackward	= 0xF0,
		eAll			= 0xFF,
	};

	virtual void OnEvent(EEventType _eType, int _iTweenID) = 0;
};

} // Namespace Tween

#endif
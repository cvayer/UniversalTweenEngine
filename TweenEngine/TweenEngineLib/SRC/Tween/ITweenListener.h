#ifndef __CTWEENCALLBACK__H__
#define __CTWEENCALLBACK__H__

#include "TweenDefines.h"

namespace Tween
{
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// ITweenListener
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

/* ITweenListener are used to trigger actions at some specific times. They are
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

    static const char * GetTweenEventTypeName(ETweenEventType _type)                  
    { 
        const char* name = NULL;
        switch(_type)
        {
        case eTweenBegin: 
            name = "eBegin";
            break;
        case eTweenStart: 
            name = "eStart";
            break;
        case eTweenEnd: 
            name = "eEnd";
            break;
        case eTweenComplete: 
            name = "eComplete";
            break;
        case eTweenBackStart: 
            name = "eBackStart";
            break;
        case eTweenBackEnd: 
            name = "eBackEnd";
            break;
        case eTweenBackComplete: 
            name = "eBackComplete";
            break;
        case eTweenAnyForward: 
            name = "eTweenAnyForward";
            break;
        case eTweenAnyBackward: 
            name = "eTweenAnyBackward";
            break;
        case eTweenAll: 
            name = "eTweenAll";
            break;
        default : 
            break;
        }
        return name;
    }

    static bool ContainsType(ETweenEventType _type, TweenListenerFlags _flags)
    {
        return ((_flags & _type) != 0);
    }

	virtual void OnEvent(ETweenEventType _type, TweenListenerID _tweenID) = 0;
};

} // Namespace Tween

#endif
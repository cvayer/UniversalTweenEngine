#ifndef __BASETWEEN__H__
#define __BASETWEEN__H__

#include "ITweenListener.h"
#include "Tools\BitField.h"

namespace Tween
{
class ITweenable;
class TweenManager;

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// BaseTween
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

class BaseTween
{
public : 
	friend class TweenGroup;
	friend class TweenManager;
	friend class Timeline;

            BaseTween();
	virtual	~BaseTween() {}

	inline	float		GetDelay()			const { return m_delay;		}
	inline	float		GetDuration()		const { return m_duration;		}
	inline	float		GetFullDuration()	const { return (m_repeatCount == 0) ? m_delay + m_duration : (m_repeatCount < 0) ? -1.0f : m_delay + m_duration + (m_repeatDelay + m_duration) *m_repeatCount; }
	inline	float		GetRepeatDelay()	const { return m_repeatDelay;	}
	inline	float		GetCurrentTime()	const { return m_currentTime;	}
	inline	int			GetRepeatCount()	const { return m_repeatCount;	}
	inline	bool		IsStarted()		    const { return m_flags.TestMask(eIsStarted);		}
	inline	bool		IsInit()			const { return m_flags.TestMask(eIsInit);			}
	inline	bool		IsFinished()		const { return m_flags.TestMask(eIsFinished) || IsKilled(); }
	inline	bool		IsYoyo()			const { return m_flags.TestMask(eIsYoyo);			}
	inline	bool		IsPaused()			const { return m_flags.TestMask(eIsPaused);		}
private : 
	inline	bool		IsKilled()		    const { return m_flags.TestMask(eIsKilled);		}
	inline	bool		IsIterationStep()	const { return m_flags.TestMask(eIsIteratingStep);	}
public :

	inline	void		Kill()		{ m_flags.AddMask(eIsKilled); }
	inline	void		Pause()		{ m_flags.AddMask(eIsPaused); }
	inline	void		Resume()	{ m_flags.SubMask(eIsPaused); }

			void		Update(float _dt);

	virtual void		Free()	{}

protected : 
    			        
	virtual void		ForceStartValues	()																= 0;
	virtual void		ForceEndValues		()																= 0;
	virtual bool		ContainsTarget(ITweenable* _target)	const										    = 0;
	virtual bool		ContainsTarget(ITweenable* _target, TweenType _type) const							= 0;

			void		KillTarget(ITweenable* _target);
			void		KillTarget(ITweenable* _target, TweenType _type);

	virtual	void		Reset();

	inline	bool		IsReverse(int _step)	const  
			{ 
				return IsYoyo() && (abs(_step%4) == 2);	
			}

			void		ForceToStart();
			void		ForceToEnd(float _time);
			void		CallCallback(ETweenEventType _type);


	virtual void		OnInitialize	()																	{}
	virtual void		OnUpdate		(int _step, int _lastStep, bool _isIterationStep, float _dt)	    {}
	virtual	void		OnBuild()                                                                           {}
	virtual	void		OnStart();
			void		OnStart(TweenManager* _manager);
			void		OnStart(TweenManager* _manager, uint8 _groupID);
			void		OnDelay(float _delay);
			void		OnRepeat(int _count, float _delay, bool _isYoyo = false);

			void		OnSetListener(ITweenListener* _listener, TweenListenerID _ID = InvalidTweenListenerID, TweenListenerFlags _triggers = eTweenComplete);

private : 
			void		Initialize();
			void		UpdateRelaunch();
			void		UpdateStep();
			void		UpdateCompletion();

	inline	bool		IsStepValid(const int& _step) const 
			{ 
				return (_step >= 0 && _step <= m_repeatCount*2) || m_repeatCount < 0; 
			}


private : 
	ITweenListener*     m_listener;
	TweenListenerFlags	m_listenerFlags;
	TweenListenerID     m_listenerID;
	int				    m_step;
	int				    m_repeatCount;

protected : 
	float			m_delay;
	float			m_duration;
private : 
	float			m_repeatDelay;
	float			m_currentTime;
	float			m_dt;

	enum eBaseTweenFlags
	{
		eIsStarted			= (1<<0),
		eIsInit				= (1<<1),
		eIsFinished			= (1<<2),
		eIsPaused			= (1<<3),
		eIsKilled			= (1<<4),
		eIsYoyo				= (1<<5),
		eIsIteratingStep	= (1<<6),
	};
	BitField<uint8> m_flags;
};

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// BaseTemplatedTween
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

template <class T> class BaseTemplatedTween : public BaseTween
{
public : 

    BaseTemplatedTween()
        : BaseTween()
    {

    }

    virtual	~BaseTemplatedTween()
    {

    }

    T*	Start()
    {
        OnStart();
        return (T*)this;
    }

    T*	Start(TweenManager* _manager)
    {
        OnStart(_manager);
        return (T*)this;
    }

    T*	Start(TweenManager* _manager, TweenGroupID _groupID)
    {
        OnStart(_manager, _groupID);
        return (T*)this;
    }

    T*	Delay(float _delay)
    {
        OnDelay(_delay);
        return (T*)this;
    }


    T*	Repeat(int _count, float _delay, bool _isYoyo = false)
    {
        OnRepeat(_count, _delay, _isYoyo);
        return (T*)this;
    }

    T*	SetListener(ITweenListener* _listener, TweenListenerID _iID = InvalidTweenListenerID, int _iTriggers = eTweenComplete)
    {
        OnSetListener(_listener, _iID, _iTriggers);
        return (T*)this;
    }
};

} // Namespace Tween

#endif
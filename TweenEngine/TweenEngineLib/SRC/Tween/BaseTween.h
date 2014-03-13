#ifndef __BASETWEEN__H__
#define __BASETWEEN__H__

#include "ITweenListener.h"
#include "Tools\BitField.h"

namespace Tween
{
class ITweenable;
class Manager;

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// BaseTween
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

class BaseTween
{
public : 
	friend class TweenGroup;
	friend class Manager;
	friend class Timeline;

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
	inline	bool		IsIterationStep()	const { return m_flags.TestMask(eIsIterationStep);	}
public :

	inline	void		Kill()		{ m_flags.AddMask(eIsKilled); }
	inline	void		Pause()		{ m_flags.AddMask(eIsPaused); }
	inline	void		Resume()	{ m_flags.SubMask(eIsPaused); }

			void		Update(float _dt);

	virtual void		Free()	{}

protected : 
    			        BaseTween();
	virtual void		ForceStartValues	()																= 0;
	virtual void		ForceEndValues		()																= 0;
	virtual bool		ContainsTarget(ITweenable* _target)	const										    = 0;
	virtual bool		ContainsTarget(ITweenable* _target, int _type) const							    = 0;

			void		KillTarget(ITweenable* _target);
			void		KillTarget(ITweenable* _target, int _type);

	virtual	void		Reset();

	inline	bool		IsReverse(int _step)	const  
			{ 
				return IsYoyo() && (abs(_step%4) == 2);	
			}

			void		ForceToStart();
			void		ForceToEnd(float _time);
			void		CallCallback(ITweenListener::EEventType _type);


	virtual void		OnInitialize	()																	{}
	virtual void		_InnerUpdate		(int _step, int _lastStep, bool _isIterationStep, float _dt)	{}
	virtual	void		_Build() {}
	virtual	void		_Start();
			void		_Start(Manager* _manager);
			void		_Start(Manager* _manager, uint8 _groupID);
			void		_Delay(float _delay);
			void		_Repeat(int _count, float _delay, bool _isYoyo = false);

			void		OnSetListener(ITweenListener* _listener, int _ID = -1, int _triggers = ITweenListener::eComplete);

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
	ITweenListener* m_listener;
	int				m_listenerTriggers;
	int				m_listenerID;
	int				m_step;
	int				m_repeatCount;

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
		eIsIterationStep	= (1<<6),
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


    T*	Build()
    {
        _Build();
        return (T*)this;
    }

    T*	Start()
    {
        _Start();
        return (T*)this;
    }

    T*	Start(Manager* _pManager)
    {
        _Start(_pManager);
        return (T*)this;
    }

    T*	Start(Manager* _pManager, uint8 _GroupID)
    {
        _Start(_pManager, _GroupID);
        return (T*)this;
    }

    T*	Delay(float _fDelay)
    {
        _Delay(_fDelay);
        return (T*)this;
    }


    T*	Repeat(int _Count, float _fDelay, bool _bYoyo = false)
    {
        _Repeat(_Count, _fDelay, _bYoyo);
        return (T*)this;
    }

    T*	SetListener(ITweenListener* _pListener, int _iID = -1, int _iTriggers = ITweenListener::eComplete)
    {
        OnSetListener(_pListener, _iID, _iTriggers);
        return (T*)this;
    }
};

} // Namespace Tween

#endif
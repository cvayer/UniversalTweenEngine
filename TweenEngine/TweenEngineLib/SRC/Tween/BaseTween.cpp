#include <stdafx.h>
#include "BaseTween.h"
#include "TweenManager.h"

namespace Tween
{
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// BaseTween
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
BaseTween::BaseTween()
: m_delay(0.0f)
, m_duration(0.0f)
, m_repeatDelay(0.0f)
, m_currentTime(0.0f)
, m_step(-2)
, m_repeatCount(0)
, m_listener(NULL)
, m_listenerFlags(0)
, m_listenerID(0)
, m_dt(0.0f)
{

}

//---------------------------------------------------------------------
void BaseTween::Update(float _dt)
{
	if(!IsStarted() || IsPaused() || IsKilled())
    {
		return;
    }

	m_dt = _dt;

	if(!IsInit())
    {
		Initialize();
    }

	if(IsInit())
	{
		UpdateRelaunch();
		UpdateStep();
		UpdateCompletion();
	}

	m_currentTime += m_dt;
	m_dt = 0.0f;
}

//---------------------------------------------------------------------
void BaseTween::KillTarget(ITweenable* _target)							
{
	if(ContainsTarget(_target))
    {
		Kill();
    }
}

//---------------------------------------------------------------------
void BaseTween::KillTarget(ITweenable* _target, TweenType _type)							
{
	if(ContainsTarget(_target, _type))
    {
		Kill();
    }
}

//---------------------------------------------------------------------
void BaseTween::Reset()
{
	m_step = -2;
	m_repeatCount = 0;

	m_delay = 0.0f;
	m_duration = 0.0f;
	m_repeatDelay = 0.0f;
	m_currentTime = 0.0f;
	m_dt = 0.0f;

	m_flags.Reset();
}

//---------------------------------------------------------------------
void BaseTween::ForceToStart()
{
	m_currentTime = -m_delay;
	m_step = -1;

	m_flags.ChangeMask(eIsIteratingStep, false);

	if(IsReverse(0))
    {
		ForceEndValues();
    }
	else
    {
		ForceStartValues();
    }
}

//---------------------------------------------------------------------
void BaseTween::ForceToEnd(float _time)
{
	m_currentTime = _time - GetFullDuration();
	m_step = m_repeatCount*2 + 1;
	m_flags.ChangeMask(eIsIteratingStep, false);

	if(IsReverse(m_repeatCount*2))
    {
		ForceStartValues();
    }
	else
    {
		ForceEndValues();
    }
}

//---------------------------------------------------------------------
void BaseTween::CallCallback(ETweenEventType _type)
{
	if (m_listener && ITweenListener::ContainsType(_type, m_listenerFlags)) 
    {
		m_listener->OnEvent(_type, m_listenerID);
    }
}

//---------------------------------------------------------------------
void BaseTween::OnStart()
{
	OnBuild();
	m_currentTime = 0.0f;
	m_flags.ChangeMask(eIsStarted, true);
}

//---------------------------------------------------------------------
void BaseTween::OnStart(TweenManager* _manager)
{
	if(_manager)
	{
		_manager->Register(this);
		OnStart();
	}
}

//---------------------------------------------------------------------
void BaseTween::OnStart(TweenManager* _manager, uint8 _groupID)
{
	if(_manager)
	{
		_manager->Register(this, _groupID);
		OnStart();
	}
}

//---------------------------------------------------------------------
void BaseTween::OnDelay(float _delay)
{
	m_delay += _delay;
}

//---------------------------------------------------------------------
void BaseTween::OnRepeat(int _count, float _delay, bool _isYoyo /*= false*/)
{
	if(!IsStarted())
	{
		m_repeatCount = _count;
		m_repeatDelay = (_delay > 0.0f)? _delay : 0.0f;
		m_flags.ChangeMask(eIsYoyo, _isYoyo);
	}
}

//---------------------------------------------------------------------
void BaseTween::OnSetListener(ITweenListener* _listener, TweenListenerID _ID /* = InvalidTweenListenerID */, TweenListenerFlags _flags /*= eComplete*/)
{
	m_listener = _listener;
	m_listenerFlags = _flags;
	m_listenerID = _ID;
}

//---------------------------------------------------------------------
void BaseTween::Initialize()
{
	if(m_currentTime + m_dt >= m_delay)
	{
		OnInitialize();
		m_flags.ChangeMask(eIsInit, true);
		m_flags.ChangeMask(eIsIteratingStep, true);
		m_step = 0;
		m_dt -= (m_delay - m_currentTime);
		m_currentTime = 0.0f;
		CallCallback(eTweenBegin);
		CallCallback(eTweenStart);
	}
}


//---------------------------------------------------------------------
void BaseTween::UpdateRelaunch()
{
	if(!IsIterationStep()  && m_repeatCount >= 0 && m_step < 0 && m_currentTime + m_dt >= 0)
	{
		TWEEN_ASSERT(m_step == -1, "Step (%d) is too low, should be -1", m_step);
		m_flags.ChangeMask(eIsIteratingStep, true);
		m_step = 0;
		float fDt = 0.0f - m_currentTime;
		m_dt -= fDt;
		m_currentTime = 0.0f;
		
		CallCallback(eTweenBegin);
		CallCallback(eTweenStart);
		OnUpdate(m_step, m_step - 1, IsIterationStep(), fDt);
	}
	else  if(!IsIterationStep() && m_repeatCount >= 0 && m_step > m_repeatCount * 2 && m_currentTime + m_dt <= 0.0f)
	{
		TWEEN_ASSERT(m_step != m_repeatCount*2 + 1, "Step (%d) is too big, should be %d", m_step, m_repeatCount*2 + 1);
		m_flags.ChangeMask(eIsIteratingStep, true);
		m_step = m_repeatCount *2 ;
		float fDt = 0.0f - m_currentTime;
		m_dt -= fDt;
		m_currentTime = m_duration;
		CallCallback(eTweenBackBegin);
		CallCallback(eTweenBackStart);
		OnUpdate(m_step, m_step + 1, IsIterationStep(), fDt);
	}

}

//---------------------------------------------------------------------
void BaseTween::UpdateStep()
{
	while(IsStepValid(m_step))
	{
		if(!IsIterationStep() && m_currentTime + m_dt <= 0.0f)
		{
			m_flags.ChangeMask(eIsIteratingStep, true);
			-- m_step;
			float fDt = 0.0f - m_currentTime;
			m_dt -= fDt;
			m_currentTime = m_duration;

			(IsReverse(m_step)) ? ForceStartValues() : ForceEndValues();

			CallCallback(eTweenBackStart);
			OnUpdate(m_step, m_step + 1, IsIterationStep(), fDt);
		}
		else if(!IsIterationStep() && m_currentTime + m_dt >= m_repeatDelay)
		{
			m_flags.ChangeMask(eIsIteratingStep, true);
			++ m_step;
			float fDt = m_repeatDelay - m_currentTime;
			m_dt -= fDt;
			m_currentTime = 0.0f;
			(IsReverse(m_step)) ? ForceEndValues() : ForceStartValues();
			CallCallback(eTweenStart);
			OnUpdate(m_step, m_step - 1, IsIterationStep(), fDt);
		}
		else if(IsIterationStep() && m_currentTime + m_dt < 0.0f)
		{
			m_flags.ChangeMask(eIsIteratingStep, false);
			-- m_step;
			float fDt = 0.0f - m_currentTime;
			m_dt -= fDt;
			m_currentTime = 0.0f;
			OnUpdate(m_step, m_step + 1, IsIterationStep(), fDt);
			CallCallback(eTweenBackEnd);
			if(m_step < 0 && m_repeatCount >= 0)
            {
				CallCallback(eTweenBackComplete);
            }
			else 
            {
				m_currentTime = m_repeatDelay;
            }
		}
		else if(IsIterationStep() && m_currentTime + m_dt  > m_duration)
		{
			m_flags.ChangeMask(eIsIteratingStep, false);
			++ m_step;

			float fDt = m_duration - m_currentTime;
			m_dt -= fDt;
			m_currentTime = m_duration;
			OnUpdate(m_step, m_step - 1, IsIterationStep(), fDt);
			CallCallback(eTweenEnd);
			if(m_step > m_repeatCount*2 && m_repeatCount >= 0)
            {
				CallCallback(eTweenComplete);
            }
			m_currentTime = 0.0f;
		}
		else if(IsIterationStep())
		{
			float fDt = m_dt;
			m_dt -= fDt;
			m_currentTime += fDt;
			OnUpdate(m_step, m_step, IsIterationStep(), fDt);
			break;
		}
		else
		{
			float fDt = m_dt;
			m_dt -= fDt;
			m_currentTime += fDt;
			break;
		}	
	}
}

//---------------------------------------------------------------------
void BaseTween::UpdateCompletion()
{
	bool isFinished = (m_repeatCount >= 0 && (m_step > m_repeatCount*2 ||  m_step < 0));
	m_flags.ChangeMask(eIsFinished, isFinished);
}

} // Namespace Tween
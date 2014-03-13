#include <stdafx.h>
#include "BaseTween.h"
#include "Manager.h"

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
, m_listenerTriggers(0)
, m_listenerID(0)
, m_dt(0.0f)
{

}

//---------------------------------------------------------------------
void BaseTween::Update(float _fDt)
{
	if(!IsStarted() || IsPaused() || IsKilled())
		return;

	m_dt = _fDt;

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
void BaseTween::KillTarget(ITweenable* _pTarget)							
{
	if(ContainsTarget(_pTarget))
		Kill();
}

//---------------------------------------------------------------------
void BaseTween::KillTarget(ITweenable* _pTarget, int _iType)							
{
	if(ContainsTarget(_pTarget, _iType))
		Kill();
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

	m_flags.ChangeMask(eIsIterationStep, false);

	if(IsReverse(0))
		ForceEndValues();
	else
		ForceStartValues();
}

//---------------------------------------------------------------------
void BaseTween::ForceToEnd(float _fTime)
{
	m_currentTime = _fTime - GetFullDuration();
	m_step = m_repeatCount*2 + 1;
	m_flags.ChangeMask(eIsIterationStep, false);

	if(IsReverse(m_repeatCount*2))
		ForceStartValues();
	else
		ForceEndValues();
}

//---------------------------------------------------------------------
void BaseTween::CallCallback(ITweenListener::EEventType _eType)
{
	if (m_listener && (m_listenerTriggers & _eType) > 0) 
		m_listener->OnEvent(_eType, m_listenerID);
}

//---------------------------------------------------------------------
void BaseTween::_Start()
{
	_Build();
	m_currentTime = 0.0f;
	m_flags.ChangeMask(eIsStarted, true);
}

//---------------------------------------------------------------------
void BaseTween::_Start(Manager* _pManager)
{
	if(_pManager)
	{
		_pManager->Register(this);
		_Start();
	}
}

//---------------------------------------------------------------------
void BaseTween::_Start(Manager* _pManager, uint8 _GroupID)
{
	if(_pManager)
	{
		_pManager->Register(this, _GroupID);
		_Start();
	}
}

//---------------------------------------------------------------------
void BaseTween::_Delay(float _fDelay)
{
	m_delay += _fDelay;
}

//---------------------------------------------------------------------
void BaseTween::_Repeat(int _Count, float _fDelay, bool _bYoyo /*= false*/)
{
	if(!IsStarted())
	{
		m_repeatCount = _Count;
		m_repeatDelay = (_fDelay > 0.0f)? _fDelay : 0.0f;
		m_flags.ChangeMask(eIsYoyo, _bYoyo);
	}
}

//---------------------------------------------------------------------
void BaseTween::OnSetListener(ITweenListener* _pListener, int _iID /* = -1 */, int _iTriggers /*= ITweenListener::eComplete*/)
{
	m_listener = _pListener;
	m_listenerTriggers = _iTriggers;
	m_listenerID = _iID;
}

//---------------------------------------------------------------------
void BaseTween::Initialize()
{
	if(m_currentTime + m_dt >= m_delay)
	{
		OnInitialize();
		m_flags.ChangeMask(eIsInit, true);
		m_flags.ChangeMask(eIsIterationStep, true);
		m_step = 0;
		m_dt -= (m_delay - m_currentTime);
		m_currentTime = 0.0f;
		CallCallback(ITweenListener::eBegin);
		CallCallback(ITweenListener::eStart);
	}
}


//---------------------------------------------------------------------
void BaseTween::UpdateRelaunch()
{
	if(!IsIterationStep()  && m_repeatCount >= 0 && m_step < 0 && m_currentTime + m_dt >= 0)
	{
		TWEEN_ASSERT(m_step == -1, "Step (%d) is too low, should be -1", m_step);
		m_flags.ChangeMask(eIsIterationStep, true);
		m_step = 0;
		float fDt = 0.0f - m_currentTime;
		m_dt -= fDt;
		m_currentTime = 0.0f;
		
		CallCallback(ITweenListener::eBegin);
		CallCallback(ITweenListener::eStart);
		_InnerUpdate(m_step, m_step - 1, IsIterationStep(), fDt);
	}
	else  if(!IsIterationStep() && m_repeatCount >= 0 && m_step > m_repeatCount * 2 && m_currentTime + m_dt <= 0.0f)
	{
		TWEEN_ASSERT(m_step != m_repeatCount*2 + 1, "Step (%d) is too big, should be %d", m_step, m_repeatCount*2 + 1);
		m_flags.ChangeMask(eIsIterationStep, true);
		m_step = m_repeatCount *2 ;
		float fDt = 0.0f - m_currentTime;
		m_dt -= fDt;
		m_currentTime = m_duration;
		CallCallback(ITweenListener::eBackBegin);
		CallCallback(ITweenListener::eBackStart);
		_InnerUpdate(m_step, m_step + 1, IsIterationStep(), fDt);
	}

}

//---------------------------------------------------------------------
void BaseTween::UpdateStep()
{
	while(IsStepValid(m_step))
	{
		if(!IsIterationStep() && m_currentTime + m_dt <= 0.0f)
		{
			m_flags.ChangeMask(eIsIterationStep, true);
			-- m_step;
			float fDt = 0.0f - m_currentTime;
			m_dt -= fDt;
			m_currentTime = m_duration;

			(IsReverse(m_step)) ? ForceStartValues() : ForceEndValues();

			CallCallback(ITweenListener::eBackStart);
			_InnerUpdate(m_step, m_step + 1, IsIterationStep(), fDt);
		}
		else if(!IsIterationStep() && m_currentTime + m_dt >= m_repeatDelay)
		{
			m_flags.ChangeMask(eIsIterationStep, true);
			++ m_step;
			float fDt = m_repeatDelay - m_currentTime;
			m_dt -= fDt;
			m_currentTime = 0.0f;
			(IsReverse(m_step)) ? ForceEndValues() : ForceStartValues();
			CallCallback(ITweenListener::eStart);
			_InnerUpdate(m_step, m_step - 1, IsIterationStep(), fDt);
		}
		else if(IsIterationStep() && m_currentTime + m_dt < 0.0f)
		{
			m_flags.ChangeMask(eIsIterationStep, false);
			-- m_step;
			float fDt = 0.0f - m_currentTime;
			m_dt -= fDt;
			m_currentTime = 0.0f;
			_InnerUpdate(m_step, m_step + 1, IsIterationStep(), fDt);
			CallCallback(ITweenListener::eBackEnd);
			if(m_step < 0 && m_repeatCount >= 0)
            {
				CallCallback(ITweenListener::eBackComplete);
            }
			else 
            {
				m_currentTime = m_repeatDelay;
            }
		}
		else if(IsIterationStep() && m_currentTime + m_dt  > m_duration)
		{
			m_flags.ChangeMask(eIsIterationStep, false);
			++ m_step;

			float fDt = m_duration - m_currentTime;
			m_dt -= fDt;
			m_currentTime = m_duration;
			_InnerUpdate(m_step, m_step - 1, IsIterationStep(), fDt);
			CallCallback(ITweenListener::eEnd);
			if(m_step > m_repeatCount*2 && m_repeatCount >= 0)
            {
				CallCallback(ITweenListener::eComplete);
            }
			m_currentTime = 0.0f;
		}
		else if(IsIterationStep())
		{
			float fDt = m_dt;
			m_dt -= fDt;
			m_currentTime += fDt;
			_InnerUpdate(m_step, m_step, IsIterationStep(), fDt);
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
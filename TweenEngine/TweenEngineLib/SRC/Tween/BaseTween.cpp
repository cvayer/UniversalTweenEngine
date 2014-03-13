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
: m_fDelay(0.0f)
, m_fDuration(0.0f)
, m_fRepeatDelay(0.0f)
, m_fCurrentTime(0.0f)
, m_iStep(-2)
, m_iRepeatCount(0)
, m_pListener(NULL)
, m_iListenerTriggers(0)
, m_iListenerID(0)
, m_fDt(0.0f)
{

}

//---------------------------------------------------------------------
void BaseTween::Update(float _fDt)
{
	if(!bIsStarted() || bIsPaused() || _bIsKilled())
		return;

	m_fDt = _fDt;

	if(!bIsInit())
    {
		_Initialize();
    }

	if(bIsInit())
	{
		_UpdateRelaunch();
		_UpdateStep();
		_UpdateCompletion();
	}

	m_fCurrentTime += m_fDt;
	m_fDt = 0.0f;
}

//---------------------------------------------------------------------
void BaseTween::_KillTarget(ITweenable* _pTarget)							
{
	if(_bContainsTarget(_pTarget))
		Kill();
}

//---------------------------------------------------------------------
void BaseTween::_KillTarget(ITweenable* _pTarget, int _iType)							
{
	if(_bContainsTarget(_pTarget, _iType))
		Kill();
}

//---------------------------------------------------------------------
void BaseTween::_Reset()
{

	m_iStep = -2;
	m_iRepeatCount = 0;

	m_fDelay = 0.0f;
	m_fDuration = 0.0f;
	m_fRepeatDelay = 0.0f;
	m_fCurrentTime = 0.0f;
	m_fDt = 0.0f;

	m_Flags.Reset();
}

//---------------------------------------------------------------------
void BaseTween::_ForceToStart()
{
	m_fCurrentTime = -m_fDelay;
	m_iStep = -1;

	m_Flags.ChangeMask(eIsIterationStep, false);

	if(_bIsReverse(0))
		_ForceEndValues();
	else
		_ForceStartValues();
}

//---------------------------------------------------------------------
void BaseTween::_ForceToEnd(float _fTime)
{
	m_fCurrentTime = _fTime - fGetFullDuration();
	m_iStep = m_iRepeatCount*2 + 1;
	m_Flags.ChangeMask(eIsIterationStep, false);

	if(_bIsReverse(m_iRepeatCount*2))
		_ForceStartValues();
	else
		_ForceEndValues();
}

//---------------------------------------------------------------------
void BaseTween::_CallCallback(ITweenListener::EEventType _eType)
{
	if (m_pListener && (m_iListenerTriggers & _eType) > 0) 
		m_pListener->OnEvent(_eType, m_iListenerID);
}

//---------------------------------------------------------------------
void BaseTween::_Start()
{
	_Build();
	m_fCurrentTime = 0.0f;
	m_Flags.ChangeMask(eIsStarted, true);
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
	m_fDelay += _fDelay;
}

//---------------------------------------------------------------------
void BaseTween::_Repeat(int _Count, float _fDelay, bool _bYoyo /*= false*/)
{
	if(!bIsStarted())
	{
		m_iRepeatCount = _Count;
		m_fRepeatDelay = (_fDelay > 0.0f)? _fDelay : 0.0f;
		m_Flags.ChangeMask(eIsYoyo, _bYoyo);
	}
}

//---------------------------------------------------------------------
void BaseTween::_SetListener(ITweenListener* _pListener, int _iID /* = -1 */, int _iTriggers /*= ITweenListener::eComplete*/)
{
	m_pListener = _pListener;
	m_iListenerTriggers = _iTriggers;
	m_iListenerID = _iID;
}

//---------------------------------------------------------------------
void BaseTween::_Initialize()
{
	if(m_fCurrentTime + m_fDt >= m_fDelay)
	{
		_InnerInitialize();
		m_Flags.ChangeMask(eIsInit, true);
		m_Flags.ChangeMask(eIsIterationStep, true);
		m_iStep = 0;
		m_fDt -= (m_fDelay - m_fCurrentTime);
		m_fCurrentTime = 0.0f;
		_CallCallback(ITweenListener::eBegin);
		_CallCallback(ITweenListener::eStart);
	}
}


//---------------------------------------------------------------------
void BaseTween::_UpdateRelaunch()
{
	if(!_bIsIterationStep()  && m_iRepeatCount >= 0 && m_iStep < 0 && m_fCurrentTime + m_fDt >= 0)
	{
		TWEEN_ASSERT(m_iStep == -1, "Step (%d) is too low, should be -1", m_iStep);
		m_Flags.ChangeMask(eIsIterationStep, true);
		m_iStep = 0;
		float fDt = 0.0f - m_fCurrentTime;
		m_fDt -= fDt;
		m_fCurrentTime = 0.0f;
		
		_CallCallback(ITweenListener::eBegin);
		_CallCallback(ITweenListener::eStart);
		_InnerUpdate(m_iStep, m_iStep - 1, _bIsIterationStep(), fDt);
	}
	else  if(!_bIsIterationStep() && m_iRepeatCount >= 0 && m_iStep > m_iRepeatCount * 2 && m_fCurrentTime + m_fDt <= 0.0f)
	{
		TWEEN_ASSERT(m_iStep != m_iRepeatCount*2 + 1, "Step (%d) is too big, should be %d", m_iStep, m_iRepeatCount*2 + 1);
		m_Flags.ChangeMask(eIsIterationStep, true);
		m_iStep = m_iRepeatCount *2 ;
		float fDt = 0.0f - m_fCurrentTime;
		m_fDt -= fDt;
		m_fCurrentTime = m_fDuration;
		_CallCallback(ITweenListener::eBackBegin);
		_CallCallback(ITweenListener::eBackStart);
		_InnerUpdate(m_iStep, m_iStep + 1, _bIsIterationStep(), fDt);
	}

}

//---------------------------------------------------------------------
void BaseTween::_UpdateStep()
{
	while(_bIsValid(m_iStep))
	{
		if(!_bIsIterationStep() && m_fCurrentTime + m_fDt <= 0.0f)
		{
			m_Flags.ChangeMask(eIsIterationStep, true);
			-- m_iStep;
			float fDt = 0.0f - m_fCurrentTime;
			m_fDt -= fDt;
			m_fCurrentTime = m_fDuration;

			(_bIsReverse(m_iStep)) ? _ForceStartValues() : _ForceEndValues();

			_CallCallback(ITweenListener::eBackStart);
			_InnerUpdate(m_iStep, m_iStep + 1, _bIsIterationStep(), fDt);
		}
		else if(!_bIsIterationStep() && m_fCurrentTime + m_fDt >= m_fRepeatDelay)
		{
			m_Flags.ChangeMask(eIsIterationStep, true);
			++ m_iStep;
			float fDt = m_fRepeatDelay - m_fCurrentTime;
			m_fDt -= fDt;
			m_fCurrentTime = 0.0f;
			(_bIsReverse(m_iStep)) ? _ForceEndValues() : _ForceStartValues();
			_CallCallback(ITweenListener::eStart);
			_InnerUpdate(m_iStep, m_iStep - 1, _bIsIterationStep(), fDt);
		}
		else if(_bIsIterationStep() && m_fCurrentTime + m_fDt < 0.0f)
		{
			m_Flags.ChangeMask(eIsIterationStep, false);
			-- m_iStep;
			float fDt = 0.0f - m_fCurrentTime;
			m_fDt -= fDt;
			m_fCurrentTime = 0.0f;
			_InnerUpdate(m_iStep, m_iStep + 1, _bIsIterationStep(), fDt);
			_CallCallback(ITweenListener::eBackEnd);
			if(m_iStep < 0 && m_iRepeatCount >= 0)
            {
				_CallCallback(ITweenListener::eBackComplete);
            }
			else 
            {
				m_fCurrentTime = m_fRepeatDelay;
            }
		}
		else if(_bIsIterationStep() && m_fCurrentTime + m_fDt  > m_fDuration)
		{
			m_Flags.ChangeMask(eIsIterationStep, false);
			++ m_iStep;

			float fDt = m_fDuration - m_fCurrentTime;
			m_fDt -= fDt;
			m_fCurrentTime = m_fDuration;
			_InnerUpdate(m_iStep, m_iStep - 1, _bIsIterationStep(), fDt);
			_CallCallback(ITweenListener::eEnd);
			if(m_iStep > m_iRepeatCount*2 && m_iRepeatCount >= 0)
            {
				_CallCallback(ITweenListener::eComplete);
            }
			m_fCurrentTime = 0.0f;
		}
		else if(_bIsIterationStep())
		{
			float fDt = m_fDt;
			m_fDt -= fDt;
			m_fCurrentTime += fDt;
			_InnerUpdate(m_iStep, m_iStep, _bIsIterationStep(), fDt);
			break;
		}
		else
		{
			float fDt = m_fDt;
			m_fDt -= fDt;
			m_fCurrentTime += fDt;
			break;
		}	
	}
}

//---------------------------------------------------------------------
void BaseTween::_UpdateCompletion()
{
	bool isFinished = (m_iRepeatCount >= 0 && (m_iStep > m_iRepeatCount*2 ||  m_iStep < 0));
	m_Flags.ChangeMask(eIsFinished, isFinished);
}

} // Namespace Tween
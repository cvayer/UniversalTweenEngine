#include <stdafx.h>
#include "Timeline.h"
#include "BaseTween.h"
#include "Tween.h"

namespace Tween
{
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// Timeline
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

Pool<Timeline>	Timeline::s_Pool = Pool<Timeline>();

void Pool<Timeline>::OnPool(Timeline* _pObject) 
{
	if(_pObject)
		_pObject->Reset();
}

void Pool<Timeline>::OnUnPool(Timeline* _pObject) 
{
	if(_pObject)
		_pObject->Reset();
}

//--------------------------------------------------------------------------------
Timeline* Timeline::CreateSequence()
{
	Timeline* timeline = s_Pool.Get();
	timeline->Setup(eSequence);
	return timeline;
}

//--------------------------------------------------------------------------------
Timeline* Timeline::CreateParallel()
{
	Timeline* timeline = s_Pool.Get();
	timeline->Setup(eParallel);
	return timeline;
}

//--------------------------------------------------------------------------------
Timeline::Timeline()
: BaseTemplatedTween<Timeline>()
, m_pCurrent(NULL)
, m_pParent(NULL)
, m_eMode(eSequence)
, m_bIsBuilt(false)
{
}

//--------------------------------------------------------------------------------
Timeline::~Timeline()
{

}

//--------------------------------------------------------------------------------
void Timeline::Reset()
{
	BaseTemplatedTween<Timeline>::Reset();

	m_Children.clear();
	m_pCurrent = NULL;
	m_pParent = NULL;
	m_bIsBuilt = false;
	m_eMode = eSequence;
}

//--------------------------------------------------------------------------------
void Timeline::_Build()
{
	if (m_bIsBuilt) 
		return;

	m_duration = 0.0f;

	for (size_t i=0; i<m_Children.size(); i++) 
	{
		BaseTween* pTween = m_Children[i];

		
		if (pTween->GetRepeatCount() < 0) 
		{
			TWEEN_ASSERT(pTween->GetRepeatCount() < 0, "You can't push an object with infinite repetitions in a timeline");
			return;
		}

		pTween->_Build();

		float fTweenFullDUration = pTween->GetFullDuration();

		switch (m_eMode) {
		case eSequence:
			{
				float fDelay = m_duration;
				m_duration += fTweenFullDUration;
				pTween->_Delay(fDelay);
			}
			break;
		case eParallel:
			m_duration = (m_duration > fTweenFullDUration)? m_duration : fTweenFullDUration;
			break;
		}
	}

	m_bIsBuilt = true;
	return;
}

//--------------------------------------------------------------------------------
Timeline* Timeline::Setup(ETimelineMode _eMode)
{
	m_eMode = _eMode;
	m_pCurrent = this;
	return this;
}

//--------------------------------------------------------------------------------
Timeline* Timeline::Push(Tween* _pTween)
{
	TWEEN_ASSERT(_pTween, "Trying to push a null timeline");
	TWEEN_ASSERT(!m_bIsBuilt, "You can't push anything to a timeline once it is started/built");
	TWEEN_ASSERT(m_pCurrent, "Timeline doesn't have a current timeline, push failed");

	if(!m_bIsBuilt && m_pCurrent && _pTween)
	{
		m_pCurrent->m_Children.push_back(_pTween);
	}

	return this;
}

//--------------------------------------------------------------------------------
Timeline* Timeline::Push(Timeline* _pTimeline)
{
	TWEEN_ASSERT(!m_bIsBuilt, "You can't push anything to a timeline once it is started/built");
	TWEEN_ASSERT(m_pCurrent, "Timeline doesn't have a current timeline, push failed");
	TWEEN_ASSERT(_pTimeline, "Trying to push a null timeline");

	if(!m_bIsBuilt && _pTimeline && m_pCurrent)
	{
		TWEEN_ASSERT(_pTimeline->m_pCurrent == _pTimeline, "Begin()/End() count is not correct"); 

		_pTimeline->m_pParent = m_pCurrent;
		m_pCurrent->m_Children.push_back(_pTimeline);
	}

	return this;
}

//--------------------------------------------------------------------------------
Timeline* Timeline::PushPause(float _fTime)
{
	TWEEN_ASSERT(!m_bIsBuilt, "You can't push anything to a timeline once it is started/built");
	TWEEN_ASSERT(m_pCurrent, "Timeline doesn't have a current timeline, pushPause failed");
	if(m_pCurrent && !m_bIsBuilt)
	{
		m_pCurrent->m_Children.push_back(Tween::Mark()->Delay(_fTime));
	}
	return this;
}

//--------------------------------------------------------------------------------
Timeline* Timeline::BeginSequence()
{

	TWEEN_ASSERT(!m_bIsBuilt, "You can't push anything to a timeline once it is started/built");
	TWEEN_ASSERT(m_pCurrent, "Timeline doesn't have a current timeline");
	if(!m_bIsBuilt && m_pCurrent)
	{
		Timeline* timeline = s_Pool.Get();
		timeline->m_pParent = m_pCurrent;
		timeline->m_eMode = eSequence;
		m_pCurrent->m_Children.push_back(timeline);
		m_pCurrent = timeline;
	}
	return this;
}

//--------------------------------------------------------------------------------
Timeline* Timeline::BeginParallel()
{
	TWEEN_ASSERT(!m_bIsBuilt, "You can't push anything to a timeline once it is started/built");
	TWEEN_ASSERT(m_pCurrent, "Timeline doesn't have a current timeline");

	if(!m_bIsBuilt && m_pCurrent)
	{
		Timeline* timeline = s_Pool.Get();
		timeline->m_pParent = m_pCurrent;
		timeline->m_eMode = eParallel;
		m_pCurrent->m_Children.push_back(timeline);
		m_pCurrent = timeline;
	}
	return this;
}

//--------------------------------------------------------------------------------
Timeline* Timeline::End()
{
	TWEEN_ASSERT(!m_bIsBuilt, "You can't push anything to a timeline once it is started/built");
	TWEEN_ASSERT(m_pCurrent, "Timeline doesn't have a current timeline");
	TWEEN_ASSERT(m_pCurrent != this, "Too many call to End");

	if(!m_bIsBuilt && m_pCurrent && m_pCurrent != this)
	{
		m_pCurrent = m_pCurrent->m_pParent;
	}

	return this;
}

//--------------------------------------------------------------------------------
void Timeline::_Start()
{
	BaseTemplatedTween<Timeline>::_Start();

	for (size_t i=0; i<m_Children.size(); i++) 
	{
		BaseTween* pTween = m_Children[i];
		pTween->_Start();
	}
}

//--------------------------------------------------------------------------------
void Timeline::Free()	
{ 
	for (size_t i=0; i<m_Children.size(); i++) 
	{
		BaseTween* pTween = m_Children[i];
		pTween->Free();
	}

	s_Pool.Free(this);
}

//--------------------------------------------------------------------------------
void Timeline::_UpdateChildren(float _fDt, bool _bBackward /*= false*/)
{
	size_t iSize = m_Children.size();
	if(!_bBackward)
	{
		for (size_t i = 0; i < iSize; ++i) 
		{
			BaseTween* pTween = m_Children[i];
			pTween->Update(_fDt);
		}
	}
	else
	{
		for (size_t i = iSize-1 ; i >= 0 ; --i) 
		{
			BaseTween* pTween = m_Children[i];
			pTween->Update(_fDt);
			if(i == 0) 			// We break if i == 0 because as i is unsigned, if we -- it, it will be positive again and the loop become infinite
				break;
		}
	}
}

//--------------------------------------------------------------------------------
void Timeline::_InnerUpdate		(int _iStep, int _iLastStep, bool _bIsIterationStep, float _fDt)
{
	if(!_bIsIterationStep && _iStep > _iLastStep)
	{
		TWEEN_ASSERT(_fDt >= 0, "Delta should be positive");
		
		float fNewDelta = IsReverse(_iLastStep) ? (-_fDt - 1.0f) : (_fDt + 1.0f);
		_UpdateChildren(fNewDelta);
		return;
	}

	if(!_bIsIterationStep && _iStep < _iLastStep)
	{
		TWEEN_ASSERT(_fDt <= 0, "Delta should be positive");
		float fNewDelta = IsReverse(_iLastStep) ? (-_fDt - 1.0f) : (_fDt + 1.0f);
		_UpdateChildren(fNewDelta, true);
		return;
	}

	TWEEN_ASSERT(_bIsIterationStep, "Not an iteration step and last step equal to step should not happen");

	if(_iStep > _iLastStep)
	{
		if(IsReverse(_iStep))
			ForceEndValues();
		else
			ForceStartValues();

		_UpdateChildren(_fDt);
	}
	else if( _iStep < _iLastStep)
	{
		if(IsReverse(_iStep))
			ForceStartValues();
		else
			ForceEndValues();

		_UpdateChildren(_fDt, true);
	}
	else
	{
		float fDt = IsReverse(_iStep) ? -_fDt : _fDt;

		if(_fDt >= 0.0f)
			_UpdateChildren(fDt);
		else
			_UpdateChildren(fDt, true);
	}
}

//--------------------------------------------------------------------------------
void Timeline::ForceStartValues	()
{
	size_t iSize = m_Children.size();
	for (size_t i = iSize-1 ; i >= 0 ; --i) 
	{
		BaseTween* pTween = m_Children[i];
		pTween->ForceToStart();

		// We beak if i == 0 as i is unsigned, if we -- it it will be positive again
		if(i == 0)
			break;
	}
}

//--------------------------------------------------------------------------------
void Timeline::ForceEndValues		()
{
	size_t iSize = m_Children.size();
	for (size_t i = 0; i < iSize; ++i) 
	{
		BaseTween* pTween = m_Children[i];
		pTween->ForceToEnd(m_duration);
	}
}

//--------------------------------------------------------------------------------
bool Timeline::ContainsTarget(ITweenable* _pTarget)	const	
{
	size_t iSize = m_Children.size();
	for (size_t i = 0; i < iSize; ++i) 
	{
		BaseTween* pTween = m_Children[i];
		if(pTween->ContainsTarget(_pTarget))
			return true;
	}
	return false;
}

//--------------------------------------------------------------------------------
bool Timeline::ContainsTarget(ITweenable* _pTarget, int _iType)	const
{
	size_t iSize = m_Children.size();
	for (size_t i = 0; i < iSize; ++i) 
	{
		BaseTween* pTween = m_Children[i];
		if(pTween->ContainsTarget(_pTarget, _iType))
			return true;
	}
	return false;
}

} // Namespace Tween


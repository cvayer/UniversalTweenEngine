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

void Pool<Timeline>::OnPool(Timeline* _object) 
{
	if(_object)
    {
		_object->Reset();
    }
}

void Pool<Timeline>::OnUnPool(Timeline* _object) 
{
	if(_object)
    {
		_object->Reset();
    }
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
, m_current(NULL)
, m_parent(NULL)
, m_mode(eSequence)
, m_isBuilt(false)
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

	m_children.clear();
	m_current = NULL;
	m_parent = NULL;
	m_isBuilt = false;
	m_mode = eSequence;
}

//--------------------------------------------------------------------------------
void Timeline::OnBuild()
{
	if (m_isBuilt) 
		return;

	m_duration = 0.0f;

	for (size_t i=0; i<m_children.size(); i++) 
	{
		BaseTween* tween = m_children[i];

		
		if (tween->GetRepeatCount() < 0) 
		{
			TWEEN_ASSERT(tween->GetRepeatCount() < 0, "You can't push an object with infinite repetitions in a timeline");
			return;
		}

		tween->OnBuild();

		float tweenFullDuration = tween->GetFullDuration();

		switch (m_mode) {
		case eSequence:
			{
				float fDelay = m_duration;
				m_duration += tweenFullDuration;
				tween->OnDelay(fDelay);
			}
			break;
		case eParallel:
			m_duration = (m_duration > tweenFullDuration)? m_duration : tweenFullDuration;
			break;
		}
	}

	m_isBuilt = true;
	return;
}

//--------------------------------------------------------------------------------
Timeline* Timeline::Setup(ETimelineMode _mode)
{
	m_mode = _mode;
	m_current = this;
	return this;
}

//--------------------------------------------------------------------------------
Timeline* Timeline::Push(Tween* _tween)
{
	TWEEN_ASSERT(_tween, "Trying to push a null timeline");
	TWEEN_ASSERT(!m_isBuilt, "You can't push anything to a timeline once it is started/built");
	TWEEN_ASSERT(m_current, "Timeline doesn't have a current timeline, push failed");

	if(!m_isBuilt && m_current && _tween)
	{
		m_current->m_children.push_back(_tween);
	}

	return this;
}

//--------------------------------------------------------------------------------
Timeline* Timeline::Push(Timeline* _timeline)
{
	TWEEN_ASSERT(!m_isBuilt, "You can't push anything to a timeline once it is started/built");
	TWEEN_ASSERT(m_current, "Timeline doesn't have a current timeline, push failed");
	TWEEN_ASSERT(_timeline, "Trying to push a null timeline");

	if(!m_isBuilt && _timeline && m_current)
	{
		TWEEN_ASSERT(_timeline->m_current == _timeline, "Begin()/End() count is not correct"); 

		_timeline->m_parent = m_current;
		m_current->m_children.push_back(_timeline);
	}

	return this;
}

//--------------------------------------------------------------------------------
Timeline* Timeline::PushPause(float _time)
{
	TWEEN_ASSERT(!m_isBuilt, "You can't push anything to a timeline once it is started/built");
	TWEEN_ASSERT(m_current, "Timeline doesn't have a current timeline, pushPause failed");
	if(m_current && !m_isBuilt)
	{
		m_current->m_children.push_back(Tween::Mark()->Delay(_time));
	}
	return this;
}

//--------------------------------------------------------------------------------
Timeline* Timeline::BeginSequence()
{
    Begin(eSequence);
	return this;
}

//--------------------------------------------------------------------------------
Timeline* Timeline::BeginParallel()
{
    Begin(eParallel);
	return this;
}

//--------------------------------------------------------------------------------
void Timeline::Begin(ETimelineMode _mode)
{
    TWEEN_ASSERT(!m_isBuilt, "You can't push anything to a timeline once it is started/built");
    TWEEN_ASSERT(m_current, "Timeline doesn't have a current timeline");

    if(!m_isBuilt && m_current)
    {
        Timeline* timeline = s_Pool.Get();
        timeline->m_parent = m_current;
        timeline->m_mode = _mode;
        m_current->m_children.push_back(timeline);
        m_current = timeline;
    }
}

//--------------------------------------------------------------------------------
Timeline* Timeline::End()
{
	TWEEN_ASSERT(!m_isBuilt, "You can't push anything to a timeline once it is started/built");
	TWEEN_ASSERT(m_current, "Timeline doesn't have a current timeline");
	TWEEN_ASSERT(m_current != this, "Too many call to End");

	if(!m_isBuilt && m_current && m_current != this)
	{
		m_current = m_current->m_parent;
	}

	return this;
}

//--------------------------------------------------------------------------------
void Timeline::OnStart()
{
	BaseTemplatedTween<Timeline>::OnStart();

	for (size_t i=0; i<m_children.size(); i++) 
	{
		BaseTween* tween = m_children[i];
		tween->OnStart();
	}
}

//--------------------------------------------------------------------------------
void Timeline::Free()	
{ 
	for (size_t i=0; i<m_children.size(); i++) 
	{
		BaseTween* tween = m_children[i];
		tween->Free();
	}

	s_Pool.Free(this);
}

//--------------------------------------------------------------------------------
void Timeline::UpdateChildren(float _dt, bool _isBackward /*= false*/)
{
	size_t iSize = m_children.size();
	if(!_isBackward)
	{
		for (size_t i = 0; i < iSize; ++i) 
		{
			BaseTween* pTween = m_children[i];
			pTween->Update(_dt);
		}
	}
	else
	{
		for (size_t i = iSize-1 ; i >= 0 ; --i) 
		{
			BaseTween* pTween = m_children[i];
			pTween->Update(_dt);
			if(i == 0) 			// We break if i == 0 because as i is unsigned, if we -- it, it will be positive again and the loop become infinite
            {
				break;
            }
		}
	}
}

//--------------------------------------------------------------------------------
void Timeline::OnUpdate		(int _step, int _lastStep, bool _isIterationStep, float _dt)
{
	if(!_isIterationStep && _step > _lastStep)
	{
		TWEEN_ASSERT(_dt >= 0, "Delta should be positive");
		
		float currentDelta = IsReverse(_lastStep) ? (-_dt - 1.0f) : (_dt + 1.0f);
		UpdateChildren(currentDelta);
		return;
	}

	if(!_isIterationStep && _step < _lastStep)
	{
		TWEEN_ASSERT(_dt <= 0, "Delta should be negative");
		float currentDelta = IsReverse(_lastStep) ? (-_dt - 1.0f) : (_dt + 1.0f);
		UpdateChildren(currentDelta, true);
		return;
	}

	TWEEN_ASSERT(_isIterationStep, "Not an iteration step and last step equal to step should not happen");

	if(_step > _lastStep)
	{
		if(IsReverse(_step))
        {
			ForceEndValues();
        }
		else
        {
			ForceStartValues();
        }

		UpdateChildren(_dt);
	}
	else if( _step < _lastStep)
	{
		if(IsReverse(_step))
        {
			ForceStartValues();
        }
		else
        {
			ForceEndValues();
        }

		UpdateChildren(_dt, true);
	}
	else
	{
		float currentDelta = IsReverse(_step) ? -_dt : _dt;

		if(_dt >= 0.0f)
        {
			UpdateChildren(currentDelta);
        }
		else
        {
			UpdateChildren(currentDelta, true);
        }
	}
}

//--------------------------------------------------------------------------------
void Timeline::ForceStartValues	()
{
	size_t size = m_children.size();
	for (size_t i = size-1 ; i >= 0 ; --i) 
	{
		BaseTween* tween = m_children[i];
		tween->ForceToStart();

		// We beak if i == 0 as i is unsigned, if we -- it it will be positive again
		if(i == 0)
        {
			break;
        }
	}
}

//--------------------------------------------------------------------------------
void Timeline::ForceEndValues		()
{
	size_t size = m_children.size();
	for (size_t i = 0; i < size; ++i) 
	{
		BaseTween* tween = m_children[i];
		tween->ForceToEnd(m_duration);
	}
}

//--------------------------------------------------------------------------------
bool Timeline::ContainsTarget(ITweenable* _target)	const	
{
	size_t iSize = m_children.size();
	for (size_t i = 0; i < iSize; ++i) 
	{
		BaseTween* tween = m_children[i];
		if(tween->ContainsTarget(_target))
        {
			return true;
        }
	}
	return false;
}

//--------------------------------------------------------------------------------
bool Timeline::ContainsTarget(ITweenable* _target, TweenType _type)	const
{
	size_t iSize = m_children.size();
	for (size_t i = 0; i < iSize; ++i) 
	{
		BaseTween* tween = m_children[i];
		if(tween->ContainsTarget(_target, _type))
        {
			return true;
        }
	}
	return false;
}

} // Namespace Tween


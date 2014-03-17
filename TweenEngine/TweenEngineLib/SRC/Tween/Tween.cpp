#include<stdafx.h>
#include"Tween.h"

#include "ITweenable.h"
#include "Easing.h"
#include "Path.h"

namespace Tween
{
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// Tween
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

const Easing::Easing*		Tween::s_DefaultEasing = &(Easing::LINEAR);

Pool<Tween>	Tween::s_Pool = Pool<Tween>();

void Pool<Tween>::OnPool(Tween* _object) 
{
	if(_object)
    {
		_object->Reset();
    }
}

void Pool<Tween>::OnUnPool(Tween* _object) 
{
	if(_object)
    {
		_object->Reset();
    }
}

//--------------------------------------------------------------------------------
Tween::Tween()
: BaseTemplatedTween<Tween>()
, m_type(InvalidType)
, m_easing(NULL)
, m_path(NULL)
, m_isFrom(false)
, m_isRelative(false)
, m_attributesCount(0)
, m_waypointsCount(0)
, m_target(NULL)
{
	
}

//--------------------------------------------------------------------------------
Tween::~Tween()
{
}

//--------------------------------------------------------------------------------
void Tween::Reset()
{
	BaseTemplatedTween<Tween>::Reset();

	m_type = InvalidType;
	m_easing = NULL;
	m_path = NULL;
	m_target = NULL;
	m_isFrom = false;
	m_isRelative = false;
	m_attributesCount = 0;
	m_waypointsCount = 0;

	
	m_startValues.clear();
	m_targetValues.clear();
	m_waypoints.clear();
	m_attributesBuffer.clear();
	m_waypointsBuffer.clear();
}

//--------------------------------------------------------------------------------
Tween* Tween::Setup(ITweenable* _target, TweenType _type, float _duration)
{
	if(_duration >= 0.0f)
	{
		m_target	= _target;
		m_type		= _type;
		m_duration	= _duration;

		if(m_target)
        {
			m_attributesCount = m_target->GetValuesCount(_type);
        }
        else
        {
            m_attributesCount = 0;
        }
	}
	return this;
}

//--------------------------------------------------------------------------------
Tween* Tween::To(ITweenable* _target, TweenType _type, float _duration)
{
	Tween* tween = s_Pool.Get();
	if(tween)
	{
		tween->Setup(_target, _type, _duration)->Ease(s_DefaultEasing);
	}
	return tween;
}

//--------------------------------------------------------------------------------
Tween* Tween::From(ITweenable* _target, TweenType _type, float _duration)
{
	Tween* tween  = To(_target, _type , _duration );
	if(tween)
    {
		tween->SetIsFrom(true);
    }
	return tween;
}

//--------------------------------------------------------------------------------
Tween* Tween::Set(ITweenable* _target, TweenType _type)
{
	Tween* tween = s_Pool.Get();
	if(tween)
	{
		tween->Setup(_target, _type, 0.0f)->Ease(s_DefaultEasing);
	}
	return tween;
}

//--------------------------------------------------------------------------------
Tween* Tween::Call(ITweenListener* _callBack)
{
	Tween* tween = s_Pool.Get();
	if(tween)
	{
		tween->Setup(NULL, InvalidType, 0.0f)->SetListener(_callBack, -1, ITweenListener::eBegin);
	}
	return tween;
}

//--------------------------------------------------------------------------------
Tween* Tween::Mark()
{
	Tween* tween = s_Pool.Get();
	if(tween)
	{
		tween->Setup(NULL, InvalidType, 0.0f);
	}
	return tween;
}

//--------------------------------------------------------------------------------
Tween* Tween::SetIsFrom(bool _isFrom)
{
	m_isFrom = _isFrom;
	return this;
}

//--------------------------------------------------------------------------------
Tween* Tween::Ease(const Easing::Easing* _easing)
{
	TWEEN_ASSERT(_easing, "Equation is null");
	m_easing = _easing;
	return this;
}

//--------------------------------------------------------------------------------
Tween* Tween::SetPath(const Path::Path* _path)
{
	m_path = _path;
	return this;
}

//--------------------------------------------------------------------------------
Tween* Tween::Target(float _target1, bool _isRelative /*= false*/)
{
	const float targets[] = {_target1};
	return Target(targets, 1, _isRelative);
}

//--------------------------------------------------------------------------------
Tween* Tween::Target(float _target1, float _target2, bool _isRelative /*= false*/)
{
	const float targets[] = { _target1, _target2 };
	return Target(targets, 2, _isRelative);
}

//--------------------------------------------------------------------------------
Tween* Tween::Target(float _target1, float _target2, float _target3, bool _isRelative /*= false*/)
{
	const float targets[] = { _target1, _target2, _target3 };
	return Target(targets, 3, _isRelative);
}

//--------------------------------------------------------------------------------
Tween* Tween::Target(const float* _targets, int _targetCount, bool _isRelative /*= false*/)
{
    TWEEN_ASSERT(_targets, "You should have an array of targets");
	TWEEN_ASSERT(m_attributesCount != 0, "You should call setup before setting targets");
	TWEEN_ASSERT(_targetCount == m_attributesCount, "Target number is not the same as the start values, you should have %d targets", m_attributesCount);

	m_isRelative = _isRelative;

	m_targetValues.clear();
	if(!_isRelative)
	{   
		for(int i=0; i < _targetCount; i++)
        {
			m_targetValues.push_back(_targets[i] );
        }
	}
	else
	{
		for(int i=0; i < _targetCount; i++)
		{
			float fTarget =  IsInit() ? _targets[i] + m_startValues[i] : _targets[i];
			m_targetValues.push_back(fTarget);
		}
	}
	return this;
}

//--------------------------------------------------------------------------------
Tween* Tween::Waypoint(float _target1)
{
	const float waypoints[] = { _target1 };
	return Waypoint(waypoints, 1);
}

//--------------------------------------------------------------------------------
Tween* Tween::Waypoint(float _target1, float _target2)
{
	const float waypoints[] = { _target1, _target2 };
	return Waypoint(waypoints, 2);
}

//--------------------------------------------------------------------------------
Tween* Tween::Waypoint(float _target1, float _target2, float _target3)
{
	const float waypoints[] = { _target1, _target2, _target3 };
	return Waypoint(waypoints, 3);
}

//--------------------------------------------------------------------------------
Tween* Tween::Waypoint(const float* _targets, int _targetCount)
{
	for(int i=0; i < _targetCount; i++)
    {
		m_waypoints.push_back(_targets[i] );
    }

	++m_waypointsCount;
	return this;
}

//--------------------------------------------------------------------------------
void Tween::Free()
{  
	s_Pool.Free(this);
}

//--------------------------------------------------------------------------------
void Tween::OnBuild() 
{ 
}

//--------------------------------------------------------------------------------
void Tween::OnInitialize()														
{
	if(!m_target)
    {
		return;
    }

	m_startValues.assign(m_attributesCount, 0.0f);
	m_attributesBuffer.assign(m_attributesCount, 0.0f);

    if(m_waypointsCount > 0)
    {
	    m_waypointsBuffer.assign((2 + m_waypointsCount) * m_attributesCount, 0.0f);
    }
    else
    {
        m_waypointsBuffer.clear();
    }

	m_target->GetValues(m_type, &m_startValues[0], m_attributesCount);

	for(int i=0; i < m_attributesCount; ++i)
	{
		m_targetValues[i] += m_isRelative ? m_startValues[i] : 0.0f;

		for (uint8 j=0; j < m_waypointsCount; ++j) 
		{
			m_waypoints[j*m_attributesCount+i] += m_isRelative ? m_startValues[i] : 0.0f;
		}

		if(m_isFrom)
		{
			float tmp = m_startValues[i];
			m_startValues[i] = m_targetValues[i];
			m_targetValues[i] = tmp;
		}
	}
}

//--------------------------------------------------------------------------------
void Tween::OnUpdate		(int _step, int _lastStep, bool _isIterationStep, float _dt)
{
	if(!m_target || !m_easing)
	{
		TWEEN_ASSERT(m_target, "No Tweenable assigned");
		TWEEN_ASSERT(m_easing, "No Easing assigned");
		return;
	}

	if(!_isIterationStep && _step > _lastStep)
	{
		m_target->SetValues(m_type, IsReverse(_lastStep) ? &(m_startValues[0]) : &(m_targetValues[0]), m_attributesCount );
		return;
	}

	if(!_isIterationStep && _step < _lastStep)
	{
		m_target->SetValues(m_type, IsReverse(_lastStep) ? &(m_targetValues[0]) : &(m_startValues[0]), m_attributesCount );
		return;
	}

	TWEEN_ASSERT(_isIterationStep, "");
	TWEEN_ASSERT(GetCurrentTime() >= 0.0f, "");
	TWEEN_ASSERT(GetCurrentTime() <= m_duration, "");

	const float eqZero = 0.00000000001f;

	if(m_duration < eqZero && _dt > -eqZero)
	{
		m_target->SetValues(m_type, IsReverse(_step) ? &(m_targetValues[0]) :  &(m_startValues[0]), m_attributesCount);
		return;
	}

	if(m_duration < eqZero && _dt < eqZero)
	{
		m_target->SetValues(m_type, IsReverse(_step) ? &(m_startValues[0]) :  &(m_targetValues[0]), m_attributesCount);
		return;
	}

	float currentTime = IsReverse(_step)? m_duration - GetCurrentTime() : GetCurrentTime();
    float timeCursor = currentTime/m_duration;
	float t = m_easing->Compute(timeCursor);

	if(m_waypointsCount == 0 || m_path == NULL)
	{
		for(uint8 i = 0; i < m_attributesCount; ++i)
		{
			m_attributesBuffer[i] = m_startValues[i] + t * (m_targetValues[i] - m_startValues[i]);
		}
	}
	else
	{
		for (uint8 i = 0; i < m_attributesCount; ++i) 
		{
			m_waypointsBuffer[0] = m_startValues[i];
			m_waypointsBuffer[1 + m_waypointsCount] = m_targetValues[i];

			for (uint8 j = 0; j < m_waypointsCount; ++j) 
			{
				m_waypointsBuffer[j+1] = m_waypoints[j*m_attributesCount+i];
			}

			m_attributesBuffer[i] = m_path->Compute(t, &(m_waypointsBuffer[0]), m_waypointsCount+2);
		}
	}

	m_target->SetValues(m_type,&(m_attributesBuffer[0]), m_attributesCount);
}

//--------------------------------------------------------------------------------
void Tween::ForceStartValues()
{
	if(m_target)
    {
		m_target->SetValues(m_type,&(m_startValues[0]), m_attributesCount);
    }
}

//--------------------------------------------------------------------------------
void Tween::ForceEndValues()													
{
	if(m_target)
    {
		m_target->SetValues(m_type,&(m_targetValues[0]), m_attributesCount);
    }
}

//--------------------------------------------------------------------------------
bool Tween::ContainsTarget(ITweenable* _target)	const						
{
	return m_target == _target;
}

//--------------------------------------------------------------------------------
bool Tween::ContainsTarget(ITweenable* _target, TweenType _type)	const						
{
	return _target == m_target && m_type == _type;
}

} // Namespace Tween

#include<stdafx.h>
#include"Tween.h"

#include "ITweenable.h"
#include "Easing.h"
#include "Paths/Path.h"
#include "Paths/Paths.h"

namespace Tween
{
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// Tween
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

const Easing::Easing*		Tween::s_pDefaultEasing = &(Easing::LINEAR);

Pool<Tween>	Tween::s_Pool = Pool<Tween>();

void Pool<Tween>::_OnPool(Tween* _pObject) 
{
	if(_pObject)
		_pObject->_Reset();
}

void Pool<Tween>::_OnUnPool(Tween* _pObject) 
{
	if(_pObject)
		_pObject->_Reset();
}

//--------------------------------------------------------------------------------
Tween::Tween()
: TemplatedTween<Tween>()
, m_iType(InvalidType)
, m_pEasing(NULL)
, m_pPath(NULL)
, m_bIsFrom(false)
, m_bIsRelative(false)
, m_ucCombinedAttributesCount(0)
, m_ucWaypointsCount(0)
, m_pTarget(NULL)
{
	
}

//--------------------------------------------------------------------------------
Tween::~Tween()
{
}

//--------------------------------------------------------------------------------
void Tween::_Reset()
{
	TemplatedTween<Tween>::_Reset();

	m_iType = InvalidType;
	m_pEasing = NULL;
	m_pPath = NULL;
	m_pTarget = NULL;
	m_bIsFrom = false;
	m_bIsRelative = false;
	m_ucCombinedAttributesCount = 0;
	m_ucWaypointsCount = 0;

	
	m_fStartValues.clear();
	m_fTargetValues.clear();
	m_fWaypoints.clear();
	m_fAttributesBuffer.clear();
	m_fWaypointsBuffer.clear();
}

//--------------------------------------------------------------------------------
Tween* Tween::Setup(ITweenable* _pTarget, int _iType, float _fDuration)
{
	if(_fDuration >= 0.0f)
	{
		m_pTarget	= _pTarget;
		m_iType		= _iType;
		m_fDuration	= _fDuration;

		if(m_pTarget)
        {
			m_ucCombinedAttributesCount = m_pTarget->_GetValuesCount(_iType);
        }
        else
        {
            m_ucCombinedAttributesCount = 0;
        }
	}
	return this;
}

//--------------------------------------------------------------------------------
Tween* Tween::To(ITweenable* _pTarget, int _iType, float _fDuration)
{
	Tween* pTween = s_Pool.Get();
	if(pTween)
	{
		pTween->Setup(_pTarget, _iType, _fDuration)->Ease(s_pDefaultEasing);
	}
	return pTween;
}

//--------------------------------------------------------------------------------
Tween* Tween::From(ITweenable* _pTarget, int _iType, float _fDuration)
{
	Tween* pTween  = To(_pTarget, _iType , _fDuration );
	if(pTween)
		pTween->SetIsFrom(true);
	return pTween;
}

//--------------------------------------------------------------------------------
Tween* Tween::Set(ITweenable* _pTarget, int _iType)
{
	Tween* pTween = s_Pool.Get();
	if(pTween)
	{
		pTween->Setup(_pTarget, _iType, 0.0f)->Ease(s_pDefaultEasing);
	}
	return pTween;
}

//--------------------------------------------------------------------------------
Tween* Tween::Call(ITweenListener* _pCallBack)
{
	Tween* pTween = s_Pool.Get();
	if(pTween)
	{
		pTween->Setup(NULL, InvalidType, 0.0f)->SetListener(_pCallBack, -1, ITweenListener::eStart);
	}
	return pTween;
}

//--------------------------------------------------------------------------------
Tween* Tween::Mark()
{
	Tween* pTween = s_Pool.Get();
	if(pTween)
	{
		pTween->Setup(NULL, InvalidType, 0.0f);
	}
	return pTween;
}

//--------------------------------------------------------------------------------
Tween* Tween::SetIsFrom(bool _bIsFrom)
{
	m_bIsFrom = _bIsFrom;
	return this;
}

//--------------------------------------------------------------------------------
Tween* Tween::Ease(const Easing::Easing* _pEquation)
{
	TWEEN_ASSERT(_pEquation, "Equation is null");
	m_pEasing = _pEquation;
	return this;
}

//--------------------------------------------------------------------------------
Tween* Tween::SetPath(const Path::Path* _pPath)
{
	TWEEN_ASSERT(_pPath, "Path is null");
	m_pPath = _pPath;
	return this;
}

//--------------------------------------------------------------------------------
Tween* Tween::Target(float _fTarget1, bool _bRelative /*= false*/)
{
	const float targets[] = {_fTarget1};
	return Target(targets, 1, _bRelative);
}

//--------------------------------------------------------------------------------
Tween* Tween::Target(float _fTarget1, float _fTarget2, bool _bRelative /*= false*/)
{
	const float targets[] = { _fTarget1, _fTarget2 };
	return Target(targets, 2, _bRelative);
}

//--------------------------------------------------------------------------------
Tween* Tween::Target(float _fTarget1, float _fTarget2, float _fTarget3, bool _bRelative /*= false*/)
{
	const float targets[] = { _fTarget1, _fTarget2, _fTarget3 };
	return Target(targets, 3, _bRelative);
}

//--------------------------------------------------------------------------------
Tween* Tween::Target(const float* _fTargets, int _iTargetCount, bool _bRelative /*= false*/)
{
	TWEEN_ASSERT(m_ucCombinedAttributesCount != 0, "You should call setup before setting targets");
	TWEEN_ASSERT(_iTargetCount == m_ucCombinedAttributesCount, "Target number is not the same as the start values, you should have %d targets", m_ucCombinedAttributesCount);

	m_bIsRelative = _bRelative;

	m_fTargetValues.clear();
	if(!_bRelative)
	{   
		for(int i=0; i < _iTargetCount; i++)
        {
			m_fTargetValues.push_back(_fTargets[i] );
        }
	}
	else
	{
		for(int i=0; i < _iTargetCount; i++)
		{
			float fTarget =  bIsInit() ? _fTargets[i] + m_fStartValues[i] : _fTargets[i];
			m_fTargetValues.push_back(fTarget);
		}
	}
	return this;
}

//--------------------------------------------------------------------------------
Tween* Tween::Waypoint(float _fTarget1)
{
	const float waypoints[] = { _fTarget1 };
	return Waypoint(waypoints, 1);
}

//--------------------------------------------------------------------------------
Tween* Tween::Waypoint(float _fTarget1, float _fTarget2)
{
	const float waypoints[] = { _fTarget1, _fTarget2 };
	return Waypoint(waypoints, 2);
}

//--------------------------------------------------------------------------------
Tween* Tween::Waypoint(float _fTarget1, float _fTarget2, float _fTarget3)
{
	const float waypoints[] = { _fTarget1, _fTarget2, _fTarget3 };
	return Waypoint(waypoints, 3);
}

//--------------------------------------------------------------------------------
Tween* Tween::Waypoint(const float* _fTargets, int _iTargetCount)
{
	for(int i=0; i < _iTargetCount; i++)
    {
		m_fWaypoints.push_back(_fTargets[i] );
    }

	++m_ucWaypointsCount;
	return this;
}

//--------------------------------------------------------------------------------
void Tween::Free()
{  
	s_Pool.Free(this);
}

//--------------------------------------------------------------------------------
void Tween::_Build() 
{ 
}

//--------------------------------------------------------------------------------
void Tween::_InnerInitialize()														
{
	if(!m_pTarget)
		return;

	m_fStartValues.assign(m_ucCombinedAttributesCount, 0.0f);
	m_fAttributesBuffer.assign(m_ucCombinedAttributesCount, 0.0f);
	m_fWaypointsBuffer.assign((2 + m_ucWaypointsCount) * m_ucCombinedAttributesCount, 0.0f);

	m_pTarget->_GetValues(m_iType, &m_fStartValues[0], m_ucCombinedAttributesCount);

	for(int i=0; i < m_ucCombinedAttributesCount; ++i)
	{
		m_fTargetValues[i] += m_bIsRelative ? m_fStartValues[i] : 0.0f;

		for (uint8 j=0; j < m_ucWaypointsCount; ++j) 
		{
			m_fWaypoints[j*m_ucCombinedAttributesCount+i] += m_bIsRelative ? m_fStartValues[i] : 0.0f;
		}

		if(m_bIsFrom)
		{
			float fTmp = m_fStartValues[i];
			m_fStartValues[i] = m_fTargetValues[i];
			m_fTargetValues[i] = fTmp;
		}
	}

}

//--------------------------------------------------------------------------------
void Tween::_InnerUpdate		(int _iStep, int _iLastStep, bool _bIsIterationStep, float _fDt)
{
	if(!m_pTarget || !m_pEasing)
	{
		TWEEN_ASSERT(m_pTarget, "No Tweenable assigned");
		TWEEN_ASSERT(m_pEasing, "No Easing assigned");
		return;
	}

	if(!_bIsIterationStep && _iStep > _iLastStep)
	{
		m_pTarget->_SetValues(m_iType, _bIsReverse(_iLastStep) ? &(m_fStartValues[0]) : &(m_fTargetValues[0]), m_ucCombinedAttributesCount );
		return;
	}

	if(!_bIsIterationStep && _iStep < _iLastStep)
	{
		m_pTarget->_SetValues(m_iType, _bIsReverse(_iLastStep) ? &(m_fTargetValues[0]) : &(m_fStartValues[0]), m_ucCombinedAttributesCount );
		return;
	}

	TWEEN_ASSERT(_bIsIterationStep, "");
	TWEEN_ASSERT(fGetCurrentTime() >= 0.0f, "");
	TWEEN_ASSERT(fGetCurrentTime() <= m_fDuration, "");

	const float eqZero = 0.00000000001f;

	if(m_fDuration < eqZero && _fDt > -eqZero)
	{
		m_pTarget->_SetValues(m_iType, _bIsReverse(_iStep) ? &(m_fTargetValues[0]) :  &(m_fStartValues[0]), m_ucCombinedAttributesCount);
		return;
	}

	if(m_fDuration < eqZero && _fDt < eqZero)
	{
		m_pTarget->_SetValues(m_iType, _bIsReverse(_iStep) ? &(m_fStartValues[0]) :  &(m_fTargetValues[0]), m_ucCombinedAttributesCount);
		return;
	}

	float fTime = _bIsReverse(_iStep)? m_fDuration - fGetCurrentTime() : fGetCurrentTime();
    float timeCursor = fTime/m_fDuration;
	float t = m_pEasing->Compute(timeCursor);

	if(m_ucWaypointsCount == 0 || m_pPath == NULL)
	{
		for(uint8 i = 0; i < m_ucCombinedAttributesCount; ++i)
		{
			m_fAttributesBuffer[i] = m_fStartValues[i] + t * (m_fTargetValues[i] - m_fStartValues[i]);
		}
	}
	else
	{
		for (uint8 i = 0; i < m_ucCombinedAttributesCount; ++i) 
		{
			m_fWaypointsBuffer[0] = m_fStartValues[i];
			m_fWaypointsBuffer[1 + m_ucWaypointsCount] = m_fTargetValues[i];

			for (uint8 j = 0; j < m_ucWaypointsCount; ++j) 
			{
				m_fWaypointsBuffer[j+1] = m_fWaypoints[j*m_ucCombinedAttributesCount+i];
			}

			m_fAttributesBuffer[i] = m_pPath->Compute(t, &(m_fWaypointsBuffer[0]), m_ucWaypointsCount+2);
		}
	}

	m_pTarget->_SetValues(m_iType,&(m_fAttributesBuffer[0]), m_ucCombinedAttributesCount);
}

//--------------------------------------------------------------------------------
void Tween::_ForceStartValues()
{
	if(m_pTarget)
		m_pTarget->_SetValues(m_iType,&(m_fStartValues[0]), m_ucCombinedAttributesCount);
}

//--------------------------------------------------------------------------------
void Tween::_ForceEndValues()													
{
	if(m_pTarget)
		m_pTarget->_SetValues(m_iType,&(m_fTargetValues[0]), m_ucCombinedAttributesCount);
}

//--------------------------------------------------------------------------------
bool Tween::_bContainsTarget(ITweenable* _pTarget)	const						
{
	return m_pTarget == _pTarget;
}

//--------------------------------------------------------------------------------
bool Tween::_bContainsTarget(ITweenable* _pTarget, int _iType)	const						
{
	return _pTarget == m_pTarget && m_iType == _iType;
}

} // Namespace Tween

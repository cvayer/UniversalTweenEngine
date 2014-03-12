#include <stdafx.h>
#include "TweenGroup.h"
#include "BaseTween.h"

namespace Tween
{
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// TweenGroup
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

TweenGroup::TweenGroup(uint8 _ID)
: m_bPaused(false)
, m_fDtFactor(1.0f)
, m_ID(_ID)
{

}

//--------------------------------------------------------------------------------
TweenGroup::~TweenGroup()
{
	KillAll();
}

//--------------------------------------------------------------------------------
void TweenGroup::Register(BaseTween* _pTween)
{
	if(!bContains(_pTween))
		m_Tweens.push_back(_pTween);
}

//--------------------------------------------------------------------------------
bool TweenGroup::bContains(BaseTween*  _pTween) const
{
	std::list<BaseTween*>::const_iterator it = m_Tweens.begin();
	while(it != m_Tweens.end())
	{
		if(*it == _pTween)
			return true;

		it++;
	}

	return false;
}

//--------------------------------------------------------------------------------
bool TweenGroup::bContainsTarget(ITweenable* _pTarget) const
{
	std::list<BaseTween*>::const_iterator it = m_Tweens.begin();
	while(it != m_Tweens.end())
	{
		if((*it)->_bContainsTarget(_pTarget))
			return true;

		it++;
	}

	return false;
}

//--------------------------------------------------------------------------------
bool TweenGroup::bContainsTarget(ITweenable* _pTarget, int _iType) const
{
	std::list<BaseTween*>::const_iterator it = m_Tweens.begin();
	while(it != m_Tweens.end())
	{
		if((*it)->_bContainsTarget(_pTarget, _iType))
			return true;

		it++;
	}

	return false;
}
//--------------------------------------------------------------------------------
void TweenGroup::KillAll()
{
	std::list<BaseTween*>::iterator it = m_Tweens.begin();
	while(it != m_Tweens.end())
	{
		(*it)->Kill();
		it++;
	}
}
//--------------------------------------------------------------------------------
void TweenGroup::KillTarget(ITweenable* _pTarget)
{
	std::list<BaseTween*>::iterator it = m_Tweens.begin();
	while(it != m_Tweens.end())
	{
		(*it)->_KillTarget(_pTarget);
		it++;
	}
}
//--------------------------------------------------------------------------------
void TweenGroup::KillTarget(ITweenable* _pTarget, int _iType)
{
	std::list<BaseTween*>::iterator it = m_Tweens.begin();
	while(it != m_Tweens.end())
	{
		(*it)->_KillTarget(_pTarget, _iType);
		it++;
	}
}
//--------------------------------------------------------------------------------
void TweenGroup::Update(float _fDt)
{
	if(!m_Tweens.empty())
	{
		std::list<BaseTween*>::iterator it = m_Tweens.begin();
		while(it != m_Tweens.end())
		{
			BaseTween* pTween = (*it);
			if(pTween->bIsFinished())
			{
				it = m_Tweens.erase(it);
			}
			else
				it++;
		}
	}


	if (!m_bPaused && !m_Tweens.empty()) 
	{
		_fDt *= m_fDtFactor;

		if (_fDt >= 0) 
		{
			std::list<BaseTween*>::iterator it = m_Tweens.begin();
			while(it != m_Tweens.end())
			{
				(*it)->Update(_fDt);
				it++;
			}
		} 
		else 
		{
			std::list<BaseTween*>::reverse_iterator it = m_Tweens.rbegin();
			while(it != m_Tweens.rend())
			{
				(*it)->Update(_fDt);
				it++;
			}
		}
	}
}

} // Namespace Tween
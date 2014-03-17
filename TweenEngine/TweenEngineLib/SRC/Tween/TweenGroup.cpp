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
: m_isPaused(false)
, m_dtScale(1.0f)
, m_ID(_ID)
{

}

//--------------------------------------------------------------------------------
TweenGroup::~TweenGroup()
{
	KillAll();
}

//--------------------------------------------------------------------------------
void TweenGroup::Register(BaseTween* _tween)
{
	if(!Contains(_tween))
    {
		m_tweens.push_back(_tween);
    }
}

//--------------------------------------------------------------------------------
bool TweenGroup::Contains(BaseTween*  _tween) const
{
	std::list<BaseTween*>::const_iterator it = m_tweens.begin();
	while(it != m_tweens.end())
	{
		if(*it == _tween)
        {
			return true;
        }

		it++;
	}

	return false;
}

//--------------------------------------------------------------------------------
bool TweenGroup::ContainsTarget(ITweenable* _target) const
{
	std::list<BaseTween*>::const_iterator it = m_tweens.begin();
	while(it != m_tweens.end())
	{
		if((*it)->ContainsTarget(_target))
        {
			return true;
        }

		it++;
	}

	return false;
}

//--------------------------------------------------------------------------------
bool TweenGroup::ContainsTarget(ITweenable* _target, int _type) const
{
	std::list<BaseTween*>::const_iterator it = m_tweens.begin();
	while(it != m_tweens.end())
	{
		if((*it)->ContainsTarget(_target, _type))
        {
			return true;
        }

		it++;
	}

	return false;
}
//--------------------------------------------------------------------------------
void TweenGroup::KillAll()
{
	std::list<BaseTween*>::iterator it = m_tweens.begin();
	while(it != m_tweens.end())
	{
		(*it)->Kill();
		it++;
	}
}

//--------------------------------------------------------------------------------
void TweenGroup::KillAndFreeAll()
{
    std::list<BaseTween*>::iterator it = m_tweens.begin();
    while(it != m_tweens.end())
    {
        BaseTween* tween = (*it);
        tween->Kill();
        tween->Free();
        it++;
    }
    m_tweens.clear();
}

//--------------------------------------------------------------------------------
void TweenGroup::KillTarget(ITweenable* _target)
{
	std::list<BaseTween*>::iterator it = m_tweens.begin();
	while(it != m_tweens.end())
	{
		(*it)->KillTarget(_target);
		it++;
	}
}
//--------------------------------------------------------------------------------
void TweenGroup::KillTarget(ITweenable* _target, int _type)
{
	std::list<BaseTween*>::iterator it = m_tweens.begin();
	while(it != m_tweens.end())
	{
		(*it)->KillTarget(_target, _type);
		it++;
	}
}
//--------------------------------------------------------------------------------
void TweenGroup::Update(float _dt)
{
	if(!m_tweens.empty())
	{
		std::list<BaseTween*>::iterator it = m_tweens.begin();
		while(it != m_tweens.end())
		{
			BaseTween* tween = (*it);
			if(tween->IsFinished())
			{
				it = m_tweens.erase(it);
                tween->Free();
			}
			else
				it++;
		}
	}


	if (!m_isPaused && !m_tweens.empty()) 
	{
		_dt *= m_dtScale;

		if (_dt >= 0) 
		{
			std::list<BaseTween*>::iterator it = m_tweens.begin();
			while(it != m_tweens.end())
			{
				(*it)->Update(_dt);
				it++;
			}
		} 
		else 
		{
			std::list<BaseTween*>::reverse_iterator it = m_tweens.rbegin();
			while(it != m_tweens.rend())
			{
				(*it)->Update(_dt);
				it++;
			}
		}
	}
}

} // Namespace Tween
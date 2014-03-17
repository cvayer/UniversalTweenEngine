#include <stdafx.h>
#include "TweenManager.h"
#include "BaseTween.h"
#include "TweenGroup.h"

namespace Tween
{
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// TweenManager
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

TweenManager::TweenManager()
: m_isPaused(false)
{

}

//--------------------------------------------------------------------------------
TweenManager::~TweenManager()
{
	for(size_t i = 0; i < m_tweenGroups.size(); ++i)
	{
		TweenGroup* group = GetGroupByIndex(i);
        group->KillAndFreeAll();
		delete group;
	}
	m_tweenGroups.clear();
}

//--------------------------------------------------------------------------------
void TweenManager::Register(BaseTween* _tween, TweenGroupID _groupID /* = DEFAULT_GROUP_ID */)
{
	TweenGroup* group = GetGroupByID(_groupID);

	if(!group)
	{
		group = new TweenGroup(_groupID);
		if(group)
        {
			m_tweenGroups.push_back(group);
        }
	}

	if(group)
	{
		if(!group->Contains(_tween))
        {
			group->Register(_tween);
        }
	}	
}

//--------------------------------------------------------------------------------
TweenGroup* TweenManager::GetGroupByID(TweenGroupID _groupID) const
{
	for(size_t i = 0; i < m_tweenGroups.size(); ++i)
	{
		TweenGroup* group = GetGroupByIndex(i);
		if(group->GetID() == _groupID)
        {
			return group;
        }
	}
	return NULL;
}

//--------------------------------------------------------------------------------
TweenGroup* TweenManager::GetGroupByIndex(uint32 _index) const
{
	return m_tweenGroups.at(_index);
}


//--------------------------------------------------------------------------------
bool TweenManager::ContainsTarget(ITweenable* _target, TweenGroupID _groupID /*= MAX_GROUP_ID*/) const
{
	if(_groupID == MAX_GROUP_ID)
	{
		for(size_t i = 0; i < m_tweenGroups.size(); ++i)
		{
			TweenGroup* group = GetGroupByIndex(i);
			if(group->ContainsTarget(_target))
            {
				return true;
            }
		}
	}
	else
	{
		TweenGroup* group = GetGroupByID(_groupID);
		if(group)
        {
			return group->ContainsTarget(_target);
        }
	}
	
	return false;
}

//--------------------------------------------------------------------------------
bool TweenManager::ContainsTarget(ITweenable* _target, TweenType _type, TweenGroupID _groupID /*= MAX_GROUP_ID*/) const
{
	if(_groupID == MAX_GROUP_ID)
	{
		for(size_t i = 0; i < m_tweenGroups.size(); ++i)
		{
			TweenGroup* group = GetGroupByIndex(i);
			if(group->ContainsTarget(_target, _type))
            {
				return true;
            }
		}
	}
	else
	{
		TweenGroup* group = GetGroupByID(_groupID);
		if(group)
        {
			return group->ContainsTarget(_target, _type);
        }
	}
	return false;
}
//--------------------------------------------------------------------------------
void TweenManager::KillAll()
{
	for(size_t i = 0; i < m_tweenGroups.size(); ++i)
	{
		TweenGroup* group = GetGroupByIndex(i);
		group->KillAll();
	}
}
//--------------------------------------------------------------------------------
void TweenManager::KillTarget(ITweenable* _target, TweenGroupID _groupID /*= MAX_GROUP_ID*/)
{
	if(_groupID == MAX_GROUP_ID)
	{
		for(size_t i = 0; i < m_tweenGroups.size(); ++i)
		{
			TweenGroup* group = GetGroupByIndex(i);
			group->KillTarget(_target);
		}
	}
	else
	{
		TweenGroup* group = GetGroupByID(_groupID);
		if(group)
        {
			group->KillTarget(_target);
        }
	}
}
//--------------------------------------------------------------------------------
void TweenManager::KillTarget(ITweenable* _target, TweenType _type, TweenGroupID _groupID /*= MAX_GROUP_ID*/)
{
	if(_groupID == MAX_GROUP_ID)
	{
		for(size_t i = 0; i < m_tweenGroups.size(); ++i)
		{
			TweenGroup* group = GetGroupByIndex(i);
			group->KillTarget(_target, _type);
		}
	}
	else
	{
		TweenGroup* group = GetGroupByID(_groupID);
		if(group)
        {
			return group->KillTarget(_target, _type);
        }
	}
}

//--------------------------------------------------------------------------------
void TweenManager::SetDtScale(float _scale, TweenGroupID _groupID /*= MAX_GROUP_ID*/)
{
	if(_groupID == MAX_GROUP_ID)
	{
		for(size_t i = 0; i < m_tweenGroups.size(); ++i)
		{
			TweenGroup* group = GetGroupByIndex(i);
			group->SetDtScale(_scale);
		}
	}
	else
	{
		TweenGroup* group = GetGroupByID(_groupID);
		if(group)
        {
			group->SetDtScale(_scale);
        }
	}
}

//--------------------------------------------------------------------------------
void TweenManager::Pause(TweenGroupID _groupID /*= MAX_GROUP_ID*/)	
{ 
    if(_groupID == MAX_GROUP_ID)
    {
        m_isPaused = true; 
    }
    else
    {
        TweenGroup* group = GetGroupByID(_groupID);
        if(group)
        {
            group->Pause();
        }
    }
}

//--------------------------------------------------------------------------------
void TweenManager::Resume(TweenGroupID _groupID /*= MAX_GROUP_ID*/)
{ 
    if(_groupID == MAX_GROUP_ID)
    {
        m_isPaused = false; 
    }
    else
    {
        TweenGroup* group = GetGroupByID(_groupID);
        if(group)
        {
            group->Resume();
        }
    }
}

//--------------------------------------------------------------------------------
void TweenManager::Update(float _dt)
{
	if(m_isPaused)
		return;

	for(size_t i = 0; i < m_tweenGroups.size(); ++i)
	{
		TweenGroup* group = GetGroupByIndex(i);
		group->Update(_dt);
	}
}

} // Namespace Tween
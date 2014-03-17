#include <stdafx.h>
#include "Manager.h"
#include "BaseTween.h"
#include "TweenGroup.h"

namespace Tween
{
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// Manager
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

Manager::Manager()
: m_isPaused(false)
{

}

//--------------------------------------------------------------------------------
Manager::~Manager()
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
void Manager::Register(BaseTween* _tween, uint8 _groupID /* = DEFAULT_GROUP_ID */)
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
TweenGroup* Manager::GetGroupByID(uint8 _groupID) const
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
TweenGroup* Manager::GetGroupByIndex(uint32 _index) const
{
	return m_tweenGroups.at(_index);
}


//--------------------------------------------------------------------------------
bool Manager::ContainsTarget(ITweenable* _target, uint8 _groupID /*= MAX_GROUP_ID*/) const
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
bool Manager::ContainsTarget(ITweenable* _target, int _type, uint8 _groupID /*= MAX_GROUP_ID*/) const
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
void Manager::KillAll()
{
	for(size_t i = 0; i < m_tweenGroups.size(); ++i)
	{
		TweenGroup* group = GetGroupByIndex(i);
		group->KillAll();
	}
}
//--------------------------------------------------------------------------------
void Manager::KillTarget(ITweenable* _target, uint8 _groupID /*= MAX_GROUP_ID*/)
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
void Manager::KillTarget(ITweenable* _target, int _type, uint8 _groupID /*= MAX_GROUP_ID*/)
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
void Manager::SetDtScale(float _scale, uint8 _groupID /*= MAX_GROUP_ID*/)
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
void Manager::Pause(uint8 _groupID /*= MAX_GROUP_ID*/)	
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
void Manager::Resume(uint8 _groupID /*= MAX_GROUP_ID*/)
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
void Manager::Update(float _dt)
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
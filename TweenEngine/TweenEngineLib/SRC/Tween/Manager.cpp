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
: m_bPaused(false)
{

}

//--------------------------------------------------------------------------------
Manager::~Manager()
{
	for(size_t i = 0; i < m_TweenGroups.size(); ++i)
	{
		TweenGroup* pGroup = GetGroupByIndex(i);
		delete pGroup;
	}
	m_TweenGroups.clear();
}

//--------------------------------------------------------------------------------
void Manager::Register(BaseTween* _pTween, uint8 _GroupID /* = DEFAULT_GROUP_ID */)
{
	TweenGroup* pGroup = GetGroupByID(_GroupID);

	if(!pGroup)
	{
		pGroup = new TweenGroup(_GroupID);
		if(pGroup)
			m_TweenGroups.push_back(pGroup);
	}

	if(pGroup)
	{
		if(!pGroup->bContains(_pTween))
			pGroup->Register(_pTween);
	}	
}

//--------------------------------------------------------------------------------
TweenGroup* Manager::GetGroupByID(uint8 _GroupID) const
{
	for(size_t i = 0; i < m_TweenGroups.size(); ++i)
	{
		TweenGroup* pGroup = GetGroupByIndex(i);
		if(pGroup->GetID() == _GroupID)
			return pGroup;
	}
	return NULL;
}

//--------------------------------------------------------------------------------
TweenGroup* Manager::GetGroupByIndex(uint32 _uiIndex) const
{
	return m_TweenGroups.at(_uiIndex);
}


//--------------------------------------------------------------------------------
bool Manager::bContainsTarget(ITweenable* _pTarget, uint8 _GroupID /*= MAX_GROUP_ID*/) const
{
	if(_GroupID == MAX_GROUP_ID)
	{
		for(size_t i = 0; i < m_TweenGroups.size(); ++i)
		{
			TweenGroup* pGroup = GetGroupByIndex(i);
			if(pGroup->bContainsTarget(_pTarget))
				return true;
		}
	}
	else
	{
		TweenGroup* pGroup = GetGroupByID(_GroupID);
		if(pGroup)
			return pGroup->bContainsTarget(_pTarget);
	}
	
	return false;
}

//--------------------------------------------------------------------------------
bool Manager::bContainsTarget(ITweenable* _pTarget, int _iType, uint8 _GroupID /*= MAX_GROUP_ID*/) const
{
	if(_GroupID == MAX_GROUP_ID)
	{
		for(size_t i = 0; i < m_TweenGroups.size(); ++i)
		{
			TweenGroup* pGroup = GetGroupByIndex(i);
			if(pGroup->bContainsTarget(_pTarget, _iType))
				return true;
		}
	}
	else
	{
		TweenGroup* pGroup = GetGroupByID(_GroupID);
		if(pGroup)
			return pGroup->bContainsTarget(_pTarget, _iType);
	}
	return false;
}
//--------------------------------------------------------------------------------
void Manager::KillAll()
{
	for(size_t i = 0; i < m_TweenGroups.size(); ++i)
	{
		TweenGroup* pGroup = GetGroupByIndex(i);
		pGroup->KillAll();
	}
}
//--------------------------------------------------------------------------------
void Manager::KillTarget(ITweenable* _pTarget, uint8 _GroupID /*= MAX_GROUP_ID*/)
{
	if(_GroupID == MAX_GROUP_ID)
	{
		for(size_t i = 0; i < m_TweenGroups.size(); ++i)
		{
			TweenGroup* pGroup = GetGroupByIndex(i);
			pGroup->KillTarget(_pTarget);
		}
	}
	else
	{
		TweenGroup* pGroup = GetGroupByID(_GroupID);
		if(pGroup)
			return pGroup->KillTarget(_pTarget);
	}
}
//--------------------------------------------------------------------------------
void Manager::KillTarget(ITweenable* _pTarget, int _iType, uint8 _GroupID /*= MAX_GROUP_ID*/)
{
	if(_GroupID == MAX_GROUP_ID)
	{
		for(size_t i = 0; i < m_TweenGroups.size(); ++i)
		{
			TweenGroup* pGroup = GetGroupByIndex(i);
			pGroup->KillTarget(_pTarget, _iType);
		}
	}
	else
	{
		TweenGroup* pGroup = GetGroupByID(_GroupID);
		if(pGroup)
			return pGroup->KillTarget(_pTarget, _iType);
	}
}

//--------------------------------------------------------------------------------
void Manager::SetDtFactor(float _fFactor, uint8 _GroupID /*= MAX_GROUP_ID*/)
{
	if(_GroupID == MAX_GROUP_ID)
	{
		for(size_t i = 0; i < m_TweenGroups.size(); ++i)
		{
			TweenGroup* pGroup = GetGroupByIndex(i);
			pGroup->SetDtFactor(_fFactor);
		}
	}
	else
	{
		TweenGroup* pGroup = GetGroupByID(_GroupID);
		if(pGroup)
			return pGroup->SetDtFactor(_fFactor);
	}
}

//--------------------------------------------------------------------------------
void Manager::Update(float _fDt)
{
	if(m_bPaused)
		return;

	for(size_t i = 0; i < m_TweenGroups.size(); ++i)
	{
		TweenGroup* pGroup = GetGroupByIndex(i);
		pGroup->Update(_fDt);
	}
}

} // Namespace Tween
#ifndef __TWEENMANAGER__H__
#define __TWEENMANAGER__H__

#include "TweenTypeDefs.h"
#include <vector>

namespace Tween
{

class BaseTween;
class ITweenable;
class cTweenGroup;
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// Manager
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

class Manager
{
public : 
	static const	uint8	MAX_GROUP_ID = 0xFF;
	static const	uint8	DEFAULT_GROUP_ID = 0;
	
	friend class TweenGroup;
	friend class BaseTween;

	Manager();
	~Manager();

			bool bContainsTarget(ITweenable* _pTarget, uint8 _GroupID = MAX_GROUP_ID) const;
			bool bContainsTarget(ITweenable* _pTarget, int _iType, uint8 _GroupID = MAX_GROUP_ID) const;
			void KillAll();
			void KillTarget(ITweenable* _pTarget, uint8 _GroupID = MAX_GROUP_ID);
			void KillTarget(ITweenable* _pTarget, int _iType, uint8 _GroupID = MAX_GROUP_ID);
			void SetDtFactor(float _fFactor, uint8 _GroupID = MAX_GROUP_ID);

	inline	void Pause()	{ m_bPaused = true; }
	inline	void Resume()	{ m_bPaused = false; }
			void Update(float _fDt);

protected : 
			void			Register(BaseTween* _pTween, uint8 _GroupID = DEFAULT_GROUP_ID);
			TweenGroup*		GetGroupByID(uint8 _GroupID) const;
			TweenGroup*		GetGroupByIndex(uint32 _uiIndex) const;

private : 
	std::vector<TweenGroup*>	m_TweenGroups;
	bool						m_bPaused;
};

} // Namespace Tween

#endif
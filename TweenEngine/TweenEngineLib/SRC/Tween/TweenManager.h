#ifndef __TWEENMANAGER__H__
#define __TWEENMANAGER__H__

#include "TweenDefines.h"
#include <vector>

namespace Tween
{

class BaseTween;
class ITweenable;
class cTweenGroup;
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// TweenManager
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

class TweenManager
{
public : 	
	friend class TweenGroup;
	friend class BaseTween;

	TweenManager();
	~TweenManager();

			bool        ContainsTarget(ITweenable* _target, TweenGroupID _groupID = MAX_GROUP_ID) const;
			bool        ContainsTarget(ITweenable* _target, TweenType _type, TweenGroupID _groupID = MAX_GROUP_ID) const;
			void        KillAll();
			void        KillTarget(ITweenable* _target, TweenGroupID _groupID = MAX_GROUP_ID);
			void        KillTarget(ITweenable* _target, TweenType _type, TweenGroupID _groupID = MAX_GROUP_ID);
			void        SetDtScale(float _scale, TweenGroupID _groupID = MAX_GROUP_ID);
            TweenGroup*	GetGroupByID(TweenGroupID _groupID) const;

		    void Pause(TweenGroupID _groupID = MAX_GROUP_ID);
		    void Resume(TweenGroupID _groupID = MAX_GROUP_ID);

			void Update(float _fDt);

protected : 
			void			Register(BaseTween* _tween, TweenGroupID _groupID = DEFAULT_GROUP_ID);
			
			TweenGroup*		GetGroupByIndex(uint32 _index) const;

private : 
	std::vector<TweenGroup*>	m_tweenGroups;
	bool						m_isPaused;
};

} // Namespace Tween

#endif
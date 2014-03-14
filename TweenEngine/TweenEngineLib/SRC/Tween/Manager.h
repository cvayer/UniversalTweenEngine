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

			bool        ContainsTarget(ITweenable* _target, uint8 _groupID = MAX_GROUP_ID) const;
			bool        ContainsTarget(ITweenable* _target, int _type, uint8 _groupID = MAX_GROUP_ID) const;
			void        KillAll();
			void        KillTarget(ITweenable* _target, uint8 _groupID = MAX_GROUP_ID);
			void        KillTarget(ITweenable* _target, int _type, uint8 _groupID = MAX_GROUP_ID);
			void        SetDtScale(float _scale, uint8 _groupID = MAX_GROUP_ID);
            TweenGroup*	GetGroupByID(uint8 _groupID) const;

		    void Pause(uint8 _groupID = MAX_GROUP_ID);
		    void Resume(uint8 _groupID = MAX_GROUP_ID);

			void Update(float _fDt);

protected : 
			void			Register(BaseTween* _tween, uint8 _groupID = DEFAULT_GROUP_ID);
			
			TweenGroup*		GetGroupByIndex(uint32 _index) const;

private : 
	std::vector<TweenGroup*>	m_tweenGroups;
	bool						m_isPaused;
};

} // Namespace Tween

#endif
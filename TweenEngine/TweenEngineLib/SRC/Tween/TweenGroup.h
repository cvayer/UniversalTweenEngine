#ifndef __TWEENGROUP__H__
#define __TWEENGROUP__H__

#include <list>
#include "TweenDefines.h"

namespace Tween
{
class BaseTween;
class ITweenable;
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// TweenGroup
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

class TweenGroup
{
public : 
	friend class TweenManager;
	friend class BaseTween;

	TweenGroup(TweenGroupID _ID);
	~TweenGroup();

			bool ContainsTarget(ITweenable* _target) const;
			bool ContainsTarget(ITweenable* _target, TweenType _type) const;
			void KillAll();
            void KillAndFreeAll();
			void KillTarget(ITweenable* _target);
			void KillTarget(ITweenable* _target, TweenType _type);
	inline	void Pause()	{ m_isPaused = true; }
	inline	void Resume()	{ m_isPaused = false; }
			void Update(float _dt);
	inline	void SetDtScale(float _scale) { m_dtScale = _scale; }

protected : 
			void	Register(BaseTween* _tween);
			uint8	GetID	()						const { return m_ID; }

private : 
	        bool Contains(BaseTween*  _tween) const;

private : 
	std::list<BaseTween*>		m_tweens;
	TweenGroupID				        m_ID;
	float						m_dtScale;
	bool						m_isPaused;
};

} // Namespace Tween

#endif
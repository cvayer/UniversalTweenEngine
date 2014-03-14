#ifndef __TWEENGROUP__H__
#define __TWEENGROUP__H__

#include <list>
#include "TweenTypeDefs.h"

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
	friend class Manager;
	friend class BaseTween;

	TweenGroup(uint8 _ID);
	~TweenGroup();

			bool ContainsTarget(ITweenable* _target) const;
			bool ContainsTarget(ITweenable* _target, int _type) const;
			void KillAll();
			void KillTarget(ITweenable* _target);
			void KillTarget(ITweenable* _target, int _type);
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
	uint8				        m_ID;
	float						m_dtScale;
	bool						m_isPaused;
};

} // Namespace Tween

#endif
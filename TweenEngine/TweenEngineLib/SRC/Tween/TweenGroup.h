#ifndef __TWEENGROUP__H__
#define __TWEENGROUP__H__

#include <list>

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

			bool bContainsTarget(ITweenable* _pTarget) const;
			bool bContainsTarget(ITweenable* _pTarget, int _iType) const;
			void KillAll();
			void KillTarget(ITweenable* _pTarget);
			void KillTarget(ITweenable* _pTarget, int _iType);
	inline	void Pause()	{ m_bPaused = true; }
	inline	void Resume()	{ m_bPaused = false; }
			void Update(float _fDt);
	inline	void SetDtFactor(float _fFactor) { m_fDtFactor = _fFactor; }

protected : 
			void			Register(BaseTween* _pTween);
			uint8	GetID	()						const { return m_ID; }

private : 
	bool bContains(BaseTween*  _pTween) const;

private : 
	std::list<BaseTween*>		m_Tweens;
	uint8				m_ID;
	float						m_fDtFactor;
	bool						m_bPaused;
};

} // Namespace Tween

#endif
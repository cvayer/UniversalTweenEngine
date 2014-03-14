#ifndef __TWEENTIMELINE__H__
#define __TWEENTIMELINE__H__

#include "BaseTween.h"
#include <vector>
#include "Tools/Pool.h"

namespace Tween
{
class BaseTween;
class Tween;
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// Timeline
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

class Timeline : public BaseTemplatedTween<Timeline>
{
public : 
	friend class Pool<Timeline>;

	static Timeline* CreateSequence();
	static Timeline* CreateParallel();

protected : 
	static			Pool<Timeline>	s_Pool;
public : 

	enum ETimelineMode
	{
		eSequence, 
		eParallel,
	};

	Timeline();
	virtual ~Timeline();

	Timeline* Push(Tween* _tween);
	Timeline* Push(Timeline* _timeline);

	Timeline* PushPause(float _time);
	Timeline* BeginSequence();
	Timeline* BeginParallel();
	Timeline* End();
	Timeline* Setup(ETimelineMode _mode); 

	virtual void		 Free();

protected : 

	virtual	void		Reset();
	virtual	void		OnBuild();
	virtual	void		OnStart();


	virtual void		OnUpdate		(int _step, int _lastStep, bool _isIterationStep, float _dt);
	virtual void		ForceStartValues	()														;
	virtual void		ForceEndValues		()														;
	virtual bool		ContainsTarget(ITweenable* _target)	const								;
	virtual bool		ContainsTarget(ITweenable* _target, int _type)	const					;


private : 
            void        Begin(ETimelineMode _mode);
			void		UpdateChildren(float _dt, bool _isBackward = false);

private : 

	std::vector< BaseTween* >	m_children;
	Timeline*					m_current;
	Timeline*					m_parent;
	ETimelineMode				m_mode;
	bool						m_isBuilt;

};

} // Namespace Tween

#endif
#ifndef __TWEENTIMELINE__H__
#define __TWEENTIMELINE__H__

#include "TemplatedTween.h"
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

class Timeline : public TemplatedTween<Timeline>
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

	Timeline* Push(Tween* _pTween);
	Timeline* Push(Timeline* _pTimeline);

	Timeline* PushPause(float _fTime);
	Timeline* BeginSequence();
	Timeline* BeginParallel();
	Timeline* End();
	Timeline* Setup(ETimelineMode _eMode); 

	virtual void		 Free();

protected : 

	virtual	void		_Reset();
	virtual	void		_Build();
	virtual	void		_Start();


	virtual void		_InnerUpdate		(int _iStep, int _iLastStep, bool _bIsIterationStep, float _fDt);
	virtual void		_ForceStartValues	()														;
	virtual void		_ForceEndValues		()														;
	virtual bool		_bContainsTarget(ITweenable* _pTarget)	const								;
	virtual bool		_bContainsTarget(ITweenable* _pTarget, int _iType)	const					;

private : 
			void		_UpdateChildren(float _fDt, bool _bBackward = false);

private : 

	std::vector< BaseTween* >	m_Children;
	Timeline*					m_pCurrent;
	Timeline*					m_pParent;
	ETimelineMode				m_eMode;
	bool						m_bIsBuilt;

};

} // Namespace Tween

#endif
#ifndef __CTWEEN__H__
#define __CTWEEN__H__

#include "BaseTween.h"
#include "Tools\Pool.h"
#include <vector>

namespace Tween
{
class ITweenable;
class ITweenListener;

namespace Path
{
	class Path;
}

namespace Easing
{
	class Easing;
}

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// Tween
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

class Tween : public BaseTemplatedTween<Tween>
{
	friend class Pool<Tween>;

protected : 
	static			Pool<Tween>				s_Pool;
	static			const Easing::Easing*	s_DefaultEasing;

public : 
	static	void	SetDefaultEasing(const Easing::Easing* _defaultEasing)
	{
		s_DefaultEasing = _defaultEasing;
	}

	static Tween*	To(ITweenable* _target, TweenType _type, float _duration);
	static Tween*	From(ITweenable* _target, TweenType _type, float _duration);
	static Tween*	Set(ITweenable* _target, TweenType _type);
	static Tween*	Call(ITweenListener* _callBack);
	static Tween*	Mark();

public : 
				Tween();
	virtual		~Tween();

	inline			int				GetType()		const		{ return m_type; }
	inline			ITweenable*		GetTweenable()	const		{ return m_target; }
	inline	const	Easing::Easing*	GetEasing()		const		{ return m_easing; }
	inline	const	Path::Path*		GetPath()		const		{ return m_path; }

					Tween*		Ease(const Easing::Easing* _easing);
					Tween*		SetPath(const Path::Path* _path);

					Tween*		Target(float _target1, bool _isRelative = false);
					Tween*		Target(float _target1, float _target2, bool _isRelative = false);
					Tween*		Target(float _target1, float _target2, float _target3, bool _isRelative = false);
					Tween*		Target(const float* _targets, int _targetCount, bool _isRelative = false);

					Tween*		Waypoint(float _target1);
					Tween*		Waypoint(float _target1, float _target2);
					Tween*		Waypoint(float _target1, float _target2, float _target3);
					Tween*		Waypoint(const float* _targets, int _targetCount);

					Tween*		SetIsFrom(bool _isFrom);
					Tween*		Setup(ITweenable* _target, TweenType _type, float _duration);

	virtual			void		Free();

protected : 

	virtual			void		Reset();
	virtual			void		OnBuild();

protected : 

	virtual			void		OnInitialize()															;
	virtual			void		OnUpdate		(int _step, int _lastStep, bool _isIterationStep, float _dt);
	virtual			void		ForceStartValues	()														;
	virtual			void		ForceEndValues		()														;
	virtual			bool		ContainsTarget(ITweenable* _target)	const								;
	virtual			bool		ContainsTarget(ITweenable* _target, TweenType _type)	const					;

private : 

			TweenType			m_type;		
			ITweenable*			m_target;
	const	Easing::Easing*		m_easing;		
	const	Path::Path*			m_path;

			std::vector<float>	m_startValues;
			std::vector<float>	m_targetValues;
			std::vector<float>	m_waypoints;
			std::vector<float>	m_attributesBuffer;
			std::vector<float>	m_waypointsBuffer;

			uint8				m_attributesCount; // Can be deduced from the vector size ?
			uint8				m_waypointsCount;
			bool				m_isFrom;
			bool				m_isRelative;
};

} // Namespace Tween
#endif

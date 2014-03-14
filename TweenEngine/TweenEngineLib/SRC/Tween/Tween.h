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
	static			const Easing::Easing*	s_pDefaultEasing;

public : 
	static	void	SetDefaultEasing(const Easing::Easing* _pDefaultEasing)
	{
		s_pDefaultEasing = _pDefaultEasing;
	}

	static Tween*	To(ITweenable* _pTarget, int _iType, float _fDuration);
	static Tween*	From(ITweenable* _pTarget, int _iType, float _fDuration);
	static Tween*	Set(ITweenable* _pTarget, int _iType);
	static Tween*	Call(ITweenListener* _pCallBack);
	static Tween*	Mark();

public : 
				Tween();
	virtual		~Tween();

	inline			int				GetType()		const		{ return m_iType; }
	inline			ITweenable*		GetTweenable()	const		{ return m_pTarget; }
	inline	const	Easing::Easing*	GetEasing()		const		{ return m_pEasing; }
	inline	const	Path::Path*		GetPath()		const		{ return m_pPath; }

					Tween*		Ease(const Easing::Easing* _pEquation);
					Tween*		SetPath(const Path::Path* _pPath);

					Tween*		Target(float _fTarget1, bool _bRelative = false);
					Tween*		Target(float _fTarget1, float _fTarget2, bool _bRelative = false);
					Tween*		Target(float _fTarget1, float _fTarget2, float _fTarget3, bool _bRelative = false);
					Tween*		Target(const float* _fTargets, int _iTargetCount, bool _bRelative = false);

					Tween*		Waypoint(float _fTarget1);
					Tween*		Waypoint(float _fTarget1, float _fTarget2);
					Tween*		Waypoint(float _fTarget1, float _fTarget2, float _fTarget3);
					Tween*		Waypoint(const float* _fTargets, int _iTargetCount);

					Tween*		SetIsFrom(bool _bIsFrom);
					Tween*		Setup(ITweenable* _pTarget, int _iType, float _fDuration);

	virtual			void		Free();

protected : 

	virtual			void		Reset();
	virtual			void		OnBuild();

protected : 

	virtual			void		OnInitialize()															;
	virtual			void		OnUpdate		(int _iStep, int _iLastStep, bool _bIsIterationStep, float _fDt);
	virtual			void		ForceStartValues	()														;
	virtual			void		ForceEndValues		()														;
	virtual			bool		ContainsTarget(ITweenable* _pTarget)	const								;
	virtual			bool		ContainsTarget(ITweenable* _pTarget, int _iType)	const					;

private : 

			int					m_iType;		// TODO : typedef type
			ITweenable*			m_pTarget;
	const	Easing::Easing*		m_pEasing;		
	const	Path::Path*			m_pPath;

			std::vector<float>	m_fStartValues;
			std::vector<float>	m_fTargetValues;
			std::vector<float>	m_fWaypoints;
			std::vector<float>	m_fAttributesBuffer;
			std::vector<float>	m_fWaypointsBuffer;

			uint8				m_ucCombinedAttributesCount;
			uint8				m_ucWaypointsCount;
			bool				m_bIsFrom;
			bool				m_bIsRelative;
};

} // Namespace Tween
#endif

#ifndef __CTWEEN__H__
#define __CTWEEN__H__

#include "TemplatedTween.h"
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

class Tween : public TemplatedTween<Tween>
{
	friend class Pool<Tween>;

protected : 
	static const	int				INVALID_TYPE = -1;
	static			uint8			s_AttributesLimit;
	static			uint8			s_WaypointsLimit;
	static			Pool<Tween>		s_Pool;
	static			Easing::Easing* s_pDefaultEquation;

public : 
	static	void		SetAttributesLimit(uint8 _Limit)
	{
		s_AttributesLimit = _Limit;
	}

	static	void		SetWaypointsLimit(uint8 _Limit)
	{
		s_WaypointsLimit = _Limit;
	}

	static	void		SetDefaultEquation(Easing::Easing* _pDefaultEquation)
	{
		s_pDefaultEquation = _pDefaultEquation;
	}

	static Tween* To(ITweenable* _pTarget, int _iType, float _fDuration);
	static Tween* From(ITweenable* _pTarget, int _iType, float _fDuration);
	static Tween* Set(ITweenable* _pTarget, int _iType);
	static Tween* Call(ITweenListener* _pCallBack);
	static Tween* Mark();

public : 
	Tween();
	virtual ~Tween();

	inline	int					GetType()		const		{ return m_iType; }
	inline	ITweenable*			GetTweenable()	const		{ return m_pTarget; }
	inline	Easing::Easing*		GetEasing()		const		{ return m_pEquation; }

			Tween*		Ease(Easing::Easing* _pEquation);
			Tween*		SetPath(Path::Path* _pPath);

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

	virtual void		Free();

protected : 

	virtual	void		_Reset();
	virtual	void		_Build();

protected : 

	virtual void		_InnerInitialize()															;
	virtual void		_InnerUpdate		(int _iStep, int _iLastStep, bool _bIsIterationStep, float _fDt);
	virtual void		_ForceStartValues	()														;
	virtual void		_ForceEndValues		()														;
	virtual bool		_bContainsTarget(ITweenable* _pTarget)	const								;
	virtual bool		_bContainsTarget(ITweenable* _pTarget, int _iType)	const					;

private : 

	int					m_iType;		// TODO : typedef type
	ITweenable*			m_pTarget;
	Easing::Easing*		m_pEquation;		
	Path::Path*			m_pPath;

	std::vector<float>	m_fStartValues;
	std::vector<float>	m_fTargetValues;
	std::vector<float>	m_fWaypoints;
	std::vector<float>	m_fAttributesBuffer;
	std::vector<float>	m_fWaypointsBuffer;

	uint8				m_ucAttributesLimit;
	uint8				m_ucWaypointsLimit;
	uint8				m_ucCombinedAttributesCount;
	uint8				m_ucWaypointsCount;
	bool				m_bIsFrom;
	bool				m_bIsRelative;
};

} // Namespace Tween
#endif

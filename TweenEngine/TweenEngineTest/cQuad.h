#ifndef __CQUAD__H__
#define __CQUAD__H__

#include "Tween/ITweenable.h"

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// cQuad
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

class cQuad : public Tween::ITweenable
{
public : 
	cQuad();
	virtual ~cQuad();

	enum
	{
		eTweenPosition, 
		eTweenRotation,
		eTweenColor,
		eTweenSize,
	};


	virtual void	_GetValues			(int _Type,				float* _ReturnValues,		uint8 _ucArraySize)	const;
	virtual void	_SetValues			(int _Type,		const	float* _NewValues,			uint8 _ucArraySize)		;
	virtual int		_GetValuesCount		(int _Type) const ;

	void Render();

public : 
	float	m_fX;
	float	m_fY;
	float	m_fRotation;
	float	m_fR, m_fG, m_fB;
	float	m_fSize;
};

#endif
#include <stdafx.h>
#include "cQuad.h"


//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// cQuad
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

cQuad::cQuad()
:m_fX(0.0f)
,m_fY(0.0f)
,m_fRotation(0.0f)
,m_fR(1.0f)
,m_fG(1.0f)
,m_fB(1.0f)
,m_fSize(0.05f)
{

}

//--------------------------------------------------------------------------------------
cQuad::~cQuad()
{

}

void cQuad::Render()
{
	glPushMatrix();
	glTranslatef(m_fX, m_fY, 0.0f);
	glRotatef(m_fRotation, 0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(m_fR, m_fG, m_fB);
	glVertex2f( - m_fSize,  + m_fSize);
	glVertex2f( + m_fSize,  + m_fSize);
	glVertex2f( - m_fSize,  - m_fSize);
	glVertex2f( + m_fSize,  - m_fSize);
	glEnd();
	glPopMatrix();
}

//--------------------------------------------------------------------------------------
int		cQuad::GetValuesCount(Tween::TweenType _Type) const 
{
	int returnVal = 0;
	switch(_Type)
	{
	case eTweenPosition: returnVal = 2; break;
	case eTweenRotation: returnVal = 1; break;
	case eTweenColor:	 returnVal = 3; break;
	case eTweenSize:	 returnVal = 1; break;
	default:
		break;
	}

	return returnVal;
}

//--------------------------------------------------------------------------------------
void	cQuad::GetValues	(Tween::TweenType _Type,				float* _ReturnValues,		Tween::uint8 _ucArraySize)	const
{
	switch(_Type)
	{
	case eTweenPosition:
		_ReturnValues[0] = m_fX;
		_ReturnValues[1] = m_fY;
		break;
	case eTweenRotation:
		_ReturnValues[0] = m_fRotation;
		break;
	case eTweenColor:
		_ReturnValues[0] = m_fR;
		_ReturnValues[1] = m_fG;
		_ReturnValues[2] = m_fB;
		break;
	case eTweenSize:
		_ReturnValues[0] = m_fSize;
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------------------------------
void	cQuad::SetValues			(Tween::TweenType _Type,		const	float* _NewValues,		Tween::uint8 _ucArraySize)	
{
	switch(_Type)
	{
	case eTweenPosition:
		m_fX = _NewValues[0];
		m_fY = _NewValues[1];
		break;
	case eTweenRotation:
		m_fRotation = _NewValues[0];
		break;
	case eTweenColor:
		m_fR = _NewValues[0];
		m_fG = _NewValues[1];
		m_fB = _NewValues[2];
		break;
	case eTweenSize:
		m_fSize = _NewValues[0];
		break;
	default:
		break;
	}
}
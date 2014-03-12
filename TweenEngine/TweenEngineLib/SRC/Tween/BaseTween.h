#ifndef __BASETWEEN__H__
#define __BASETWEEN__H__

#include "ITweenListener.h"
#include "Tools\BitField.h"

namespace Tween
{
class ITweenable;
class Manager;

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// BaseTween
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

class BaseTween
{
public : 
	friend class TweenGroup;
	friend class Manager;
	friend class Timeline;

			BaseTween();
	virtual	~BaseTween() {}

	inline	float		fGetDelay()			const { return m_fDelay;		}
	inline	float		fGetDuration()		const { return m_fDuration;		}
	inline	float		fGetFullDuration()	const { return (m_iRepeatCount == 0) ? m_fDelay + m_fDuration : (m_iRepeatCount < 0) ? -1.0f : m_fDelay + m_fDuration + (m_fRepeatDelay + m_fDuration) *m_iRepeatCount; }
	inline	float		fGetRepeatDelay()	const { return m_fRepeatDelay;	}
	inline	float		fGetCurrentTime()	const { return m_fCurrentTime;	}
	inline	int			iGetRepeatCount()	const { return m_iRepeatCount;	}
	inline	bool		bIsStarted()		const { return m_Flags.bTestMask(eIsStarted);		}
	inline	bool		bIsInit()			const { return m_Flags.bTestMask(eIsInit);			}
	inline	bool		bIsFinished()		const { return m_Flags.bTestMask(eIsFinished) || m_Flags.bTestMask(eIsKilled); }
	inline	bool		bIsYoyo()			const { return m_Flags.bTestMask(eIsYoyo);			}
	inline	bool		bIsPaused()			const { return m_Flags.bTestMask(eIsPaused);		}
private : 
	inline	bool		_bIsKilled()		const { return m_Flags.bTestMask(eIsKilled);		}
	inline	bool		_bIsIterationStep()	const { return m_Flags.bTestMask(eIsIterationStep);	}
public :

	inline	void		Kill()		{ m_Flags.AddMask(eIsKilled); }
	inline	void		Pause()		{ m_Flags.AddMask(eIsPaused); }
	inline	void		Resume()	{ m_Flags.SubMask(eIsPaused); }

			void		Update(float _fDt);

	virtual void		Free()	{}

protected : 

	virtual void		_ForceStartValues	()																= 0;
	virtual void		_ForceEndValues		()																= 0;
	virtual bool		_bContainsTarget(ITweenable* _pTarget)	const										= 0;
	virtual bool		_bContainsTarget(ITweenable* _pTarget, int _iType) const							= 0;

			void		_KillTarget(ITweenable* _pTarget);
			void		_KillTarget(ITweenable* _pTarget, int _iType);

	virtual	void		_Reset();

	inline	bool		_bIsReverse(int _iStep)	const  
			{ 
				return bIsYoyo() && (abs(_iStep%4) == 2);	
			}

			void		_ForceToStart();
			void		_ForceToEnd(float _fTime);
			void		_CallCallback(ITweenListener::EEventType _eType);


	virtual void		_InnerInitialize	()																	{}
	virtual void		_InnerUpdate		(int _iStep, int _iLastStep, bool _bIsIterationStep, float _fDt)	{}
	virtual	void		_Build() {}
	virtual	void		_Start();
			void		_Start(Manager* _pManager);
			void		_Start(Manager* _pManager, uint8 _GroupID);
			void		_Delay(float _fDelay);
			void		_Repeat(int _Count, float _fDelay, bool _bYoyo = false);

			void		_SetListener(ITweenListener* _pListener, int _iID = -1, int _iTriggers = ITweenListener::eComplete);

private : 
			void		_Initialize();
			void		_UpdateRelaunch();
			void		_UpdateStep();
			void		_UpdateCompletion();

	inline	bool		_bIsValid(const int& _iStep) const 
			{ 
				return (_iStep >= 0 && _iStep <= m_iRepeatCount*2) || m_iRepeatCount < 0; 
			}


private : 
	ITweenListener* m_pListener;
	int				m_iListenerTriggers;
	int				m_iListenerID;
	int				m_iStep;
	int				m_iRepeatCount;

protected : 
	float			m_fDelay;
	float			m_fDuration;
private : 
	float			m_fRepeatDelay;
	float			m_fCurrentTime;
	float			m_fDt;

	enum eBaseTweenFlags
	{
		eIsStarted			= (1<<0),
		eIsInit				= (1<<1),
		eIsFinished			= (1<<2),
		eIsPaused			= (1<<3),
		eIsKilled			= (1<<4),
		eIsYoyo				= (1<<5),
		eIsIterationStep	= (1<<6),
	};
	BitField<uint8> m_Flags;
};

} // Namespace Tween

#endif
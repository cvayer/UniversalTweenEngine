#ifndef __TWEENBITFIELD__H__
#define __TWEENBITFIELD__H__

namespace Tween
{

template <class _Mask> class BitField
{
public : 
	BitField()
		: m_Mask(0)
	{
	}

    BitField(_Mask _mask)
        : m_Mask(_mask)
    {
    }

	//test the exact mask (all the bits active)
    inline bool bTestMask(const _Mask& _ToTest)const
	{
		return (m_Mask & _ToTest) == _ToTest;
	}

	//test for any of the mask bits to be active
    inline bool bTestMaskAny(const _Mask& _ToTest) const
    {
        return (m_Mask & _ToTest) != 0;
    }

	inline  bool    bTestMask    (const _Mask& _Mandatory, const _Mask& _AtLeastOne, const _Mask& _Exclude)const
	{
		bool bRet = bTestMask(_Mandatory) && (( m_Mask & _Exclude) == 0) && ( (!_AtLeastOne) || ((m_Mask & _AtLeastOne) > 0) );
		return bRet;
	}

	inline void AddMask(const _Mask& _ToAdd)
	{
		m_Mask |= _ToAdd;
	}

	inline void SubMask(const _Mask& _ToSub)
	{
		m_Mask &= ~(_ToSub);
	}

	inline void Reset()
	{
		m_Mask = 0;
	}

	inline  _Mask   GetMask     ()const
	{
		return m_Mask;
	}

    inline _Mask&    Mask       ()
    {
        return m_Mask;
    }

	inline  void    SetMask     (_Mask _Val)
	{
		m_Mask = _Val;
	}

	inline  void    ChangeMask  (_Mask _Val, bool _On)
	{
		if (_On)
			AddMask(_Val);
		else
			SubMask(_Val);
	}

	// uint8 for flags should be enough as they can't be over 64
	//! Flag should be a value between 0 and BitCount(_Mask), do not use shifted values
	inline _Mask FlagToMask(uint8 _Flag) const
	{
		return (_Mask)1ll<<_Flag;
	}

	//! Flag should be a value between 0 and BitCount(_Mask), do not use shifted values
	inline bool bTestFlag(uint8 _Flag) const
	{
		return bTestMask(FlagToMask(_Flag));
	}

	//! Flag should be a value between 0 and BitCount(_Mask), do not use shifted values
	inline void AddFlag(uint8 _Flag)
	{
		AddMask(FlagToMask(_Flag));
	}

	//! Flag should be a value between 0 and BitCount(_Mask), do not use shifted values
	inline void SubFlag(uint8 _Flag)
	{
		SubMask(FlagToMask(_Flag));
	}

	//! Flag should be a value between 0 and BitCount(_Mask), do not use shifted values
	inline  void    ChangeFlag  (uint8 _Flag, bool _On)
	{
		if (_On)
			AddMask(FlagToMask(_Flag));
		else
			SubMask(FlagToMask(_Flag));
	}

    typedef _Mask MaskType;

private : 
	_Mask m_Mask;
};

} // Namespace Tween
#endif

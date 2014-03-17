#ifndef __TWEENBITFIELD__H__
#define __TWEENBITFIELD__H__

#include "TweenDefines.h"

namespace Tween
{

template <class T> class BitField
{
public : 
	BitField()
		: m_mask(0)
	{
	}

    BitField(T _mask)
        : m_mask(_mask)
    {
    }

	//test the exact mask (all the bits active)
    inline bool TestMask(const T& _toTest)const
	{
		return (m_mask & _toTest) == _toTest;
	}

	//test for any of the mask bits to be active
    inline bool TestMaskAny(const T& _toTest) const
    {
        return (m_mask & _toTest) != 0;
    }

	inline  bool    TestMask    (const T& _mandatory, const T& _atLeastOne, const T& _exclude)const
	{
		bool bRet = TestMask(_mandatory) && (( m_mask & _exclude) == 0) && ( (!_atLeastOne) || ((m_mask & _atLeastOne) > 0) );
		return bRet;
	}

	inline void AddMask(const T& _toAdd)
	{
		m_mask |= _toAdd;
	}

	inline void SubMask(const T& _toSub)
	{
		m_mask &= ~(_toSub);
	}

	inline void Reset()
	{
		m_mask = 0;
	}

	inline  T   GetMask     () const
	{
		return m_mask;
	}

    inline T&    Mask       ()
    {
        return m_mask;
    }

	inline  void    SetMask     (T _val)
	{
		m_mask = _val;
	}

	inline  void    ChangeMask  (T _val, bool _on)
	{
		if (_on)
			AddMask(_val);
		else
			SubMask(_val);
	}

	// uint8 for flags should be enough as they can't be over 64
	//! Flag should be a value between 0 and BitCount(_Mask), do not use shifted values
	inline T FlagToMask(uint8 _flag) const
	{
		return (T)(1ll<<_flag);
	}

	//! Flag should be a value between 0 and BitCount(_Mask), do not use shifted values
	inline bool TestFlag(uint8 _flag) const
	{
		return TestMask(FlagToMask(_flag));
	}

	//! Flag should be a value between 0 and BitCount(_Mask), do not use shifted values
	inline void AddFlag(uint8 _flag)
	{
		AddMask(FlagToMask(_flag));
	}

	//! Flag should be a value between 0 and BitCount(_Mask), do not use shifted values
	inline void SubFlag(uint8 _flag)
	{
		SubMask(FlagToMask(_flag));
	}

	//! Flag should be a value between 0 and BitCount(_Mask), do not use shifted values
	inline  void    ChangeFlag  (uint8 _flag, bool _on)
	{
		if (_on)
			AddMask(FlagToMask(_flag));
		else
			SubMask(FlagToMask(_flag));
	}

    typedef T MaskType;

private : 
	T m_mask;
};

} // Namespace Tween
#endif

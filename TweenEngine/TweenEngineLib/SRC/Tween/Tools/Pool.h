#ifndef __CPOOL__H__
#define __CPOOL__H__

#include <vector>

namespace Tween
{
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// Pool<T>
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
template <class T> class Pool
{
public : 

	Pool()
	{

	}

	~Pool()
	{
		size_t i;
		for(i = 0; i < m_InPool.size(); i++)
		{
			T* pObject = m_InPool[i];
			delete pObject;
		}	
		m_InPool.clear();

		for(i = 0; i < m_OutOfPool.size(); i++)
		{
			T* pObject = m_OutOfPool[i];
			delete pObject;
		}	
		m_OutOfPool.clear();	
	}

	T* Get()
	{
		T* pObject = NULL;
		if(m_InPool.empty())
			pObject = new T();
		else
		{
			pObject = m_InPool[m_InPool.size() - 1];
			m_InPool.pop_back();
		}

		m_OutOfPool.push_back(pObject);
		_OnUnPool(pObject);
		return pObject;
	}

	void Free(T* _pObject)
	{
		if(_pObject)
		{
			int outOfPoolIndex = _bContains(m_OutOfPool, _pObject);
			if(outOfPoolIndex != -1 && _bContains(m_InPool, _pObject) == -1)
			{
				m_InPool.push_back(_pObject);
				_OnPool(_pObject);

				m_OutOfPool[outOfPoolIndex] = m_OutOfPool[m_OutOfPool.size() - 1];
				m_OutOfPool.pop_back();
			}
		}
	}

protected : 
	int _bContains(const std::vector<T*>& _vector, T* _pObject)
	{
		if(!_pObject)
			return -1;

		for(size_t i = 0; i < _vector.size(); i++)
		{
			if(_vector[i] == _pObject)
				return (int)i;
		}
		return -1;
	}

	void _OnPool(T* _pObject) {}
	void _OnUnPool(T* _pObject) {}

private : 
	std::vector<T*> m_InPool;
	std::vector<T*> m_OutOfPool;
};

} // Namespace Tween

#endif
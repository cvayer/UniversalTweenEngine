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
		for(i = 0; i < m_inPoolObjects.size(); i++)
		{
			T* object = m_inPoolObjects[i];
			delete object;
		}	
		m_inPoolObjects.clear();

		for(i = 0; i < m_outOfPoolObjects.size(); i++)
		{
			T* object = m_outOfPoolObjects[i];
			delete object;
		}	
		m_outOfPoolObjects.clear();	
	}

	T* Get()
	{
		T* object = NULL;
		if(m_inPoolObjects.empty())
        {
			object = new T();
        }
		else
		{
			object = m_inPoolObjects[m_inPoolObjects.size() - 1];
			m_inPoolObjects.pop_back();
		}

		m_outOfPoolObjects.push_back(object);
		OnUnPool(object);
		return object;
	}

	void Free(T* _object)
	{
		if(_object)
		{
			int outOfPoolIndex = Contains(m_outOfPoolObjects, _object);
			if(outOfPoolIndex != -1 && Contains(m_inPoolObjects, _object) == -1)
			{
				m_inPoolObjects.push_back(_object);
				OnPool(_object);

				m_outOfPoolObjects[outOfPoolIndex] = m_outOfPoolObjects[m_outOfPoolObjects.size() - 1];
				m_outOfPoolObjects.pop_back();
			}
		}
	}

protected : 
	int Contains(const std::vector<T*>& _vector, T* _object)
	{
		if(!_object)
			return -1;

		for(size_t i = 0; i < _vector.size(); i++)
		{
			if(_vector[i] == _object)
				return (int)i;
		}
		return -1;
	}

	void OnPool(T* _object) {}
	void OnUnPool(T* _object) {}

private : 
	std::vector<T*> m_inPoolObjects;
	std::vector<T*> m_outOfPoolObjects;
};

} // Namespace Tween

#endif
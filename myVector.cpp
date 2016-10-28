template<class VecType>
class myVector
{
public:

	int m_numElements;
	int m_currentSize;
	VecType *m_pData;

	myVector()
	{
		m_numElements = 128;
		m_pData = new VecType[m_numElements];
		m_currentSize = -1;
	}

	VecType back()
	{
		if (m_currentSize >= 0)
			return m_pData[m_currentSize];
		else
			throw 0;
	}

	VecType front()
	{
		if (m_currentSize >= 0)
			return m_pData[0];
		else
			throw 0;
	}
	
	bool empty()
	{
		return m_currentSize < 0;
	}

	int size()
	{
		return m_currentSize + 1; // index od 0
	}

	void push_back(VecType data)
	{
		m_currentSize++;
		if (m_currentSize - 1 >= m_numElements)
			throw 0;
		m_pData[m_currentSize] = data;
	}

	void pop_back()
	{
		if (m_currentSize < 0)
			throw 0;
		m_currentSize--;
	}

	VecType operator [] (int index)
	{
		if (index > m_currentSize)
			throw 0;
		return m_pData[index];
	}
};

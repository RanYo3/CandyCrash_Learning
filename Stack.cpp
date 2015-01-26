#include "stdafx.h"
#include "Stack.h"

using namespace std;

template <class T, int _size>
Stack<T, _size>::Stack(int size)
{
	m_Capacity = size;
	m_Array = new T[m_Capacity];
	m_Size = 0;
}

template <class T, int _size>
Stack<T, _size>::~Stack()
{
	if (m_Array != NULL)
	{
		delete[] m_Array;
	}
}

template <class T, int _size>
Stack<T, _size>::Stack(const Stack<T, _size> &other)
{
	m_Capacity = other.m_Capacity;
	m_Array = new T[m_Capacity];
	m_Size = other.m_Size;

	for (int i = 0; i < m_Size; i++)
	{
		m_Array[i] = other.m_Array[i];
	}
}

template <class T, int _size>
const Stack<T, _size> &Stack<T, _size>::operator=(const Stack<T, _size> &other)
{
	m_Capacity = other.m_Capacity;
	m_Size = other.m_Size;

	if (m_Array != NULL)
	{
		delete[] m_Array;
	}

	m_Array = new T[m_Capacity];

	for (int i = 0; i < m_Size; i++)
	{
		m_Array[i] = other.m_Array[i];
	}

	return *this;
}

template <class T, int _size>
void Stack<T, _size>::Push(T obj)
{
	if (m_Size == m_Capacity)
	{
		m_Capacity = int(m_Capacity * 1.5);
		T *newArray = new T[m_Capacity];

		for (int i = 0; i < m_Size; i++)
		{
			newArray[i] = m_Array[i];
		}

		delete[] m_Array;
		m_Array = newArray;
	}

	m_Array[m_Size++] = obj;
}

template <class T, int _size>
void Stack<T, _size>::Pop()
{
	if (m_Size > 0)
	{
		m_Size--;
	}
}

template <class T, int _size>
void Stack<T, _size>::DeleteAll()
{
	m_Size = 0;
}

template <class T, int _size>
T Stack<T, _size>::Top() const
{
	return m_Array[m_Size - 1];
}

template <class T, int _size>
bool Stack<T, _size>::IsEmpty() const
{
	return (m_Size == 0);
}

template <class T, int _size>
int Stack<T, _size>::GetSize() const
{
	return m_Size
}

template <class T, int _size>
void Stack<T, _size>::Print() const
{
	cout << "Bottom ---> ";
	for (int i = 0; i < m_Size; i++)
	{
		cout << m_Array[i];
		if (i < m_Size - 1)
		{
			cout << " , ";
		}
	}
	cout << " <--- Top" << endl;
}
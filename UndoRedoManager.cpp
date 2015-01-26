#include "stdafx.h"
#include "UndoRedoManager.h"

#include <iostream>

using namespace std;

template <class T>
UndoRedoManager<T>::UndoRedoManager()
{
}

template <class T>
UndoRedoManager<T>::~UndoRedoManager()
{
}

template <class T>
UndoRedoManager<T>::UndoRedoManager(const UndoRedoManager<T> &other)
{
	m_Recycled = other.m_Recycled;
	m_ObjectsInUse = other.m_ObjectsInUse;
}

template <class T>
const UndoRedoManager<T> &UndoRedoManager<T>::operator=(const UndoRedoManager<T> &other)
{
	m_Recycled = other.m_Recycled;
	m_ObjectsInUse = other.m_ObjectsInUse;

	return *this;
}

template <class T>
void UndoRedoManager<T>::AddNew(T obj)
{
	m_ObjectsInUse.Push(obj);
}

template <class T>
void UndoRedoManager<T>::AddToRecycled(T Obj)
{
	m_Recycled.Push(Obj);
}

template <class T>
T UndoRedoManager<T>::Redo()
{
	if (!m_Recycled.IsEmpty())
	{
		T obj = m_Recycled.Top();
		m_Recycled.Pop();
		return obj;
	}
}

template <class T>
T UndoRedoManager<T>::Undo()
{
	if (!m_ObjectsInUse.IsEmpty())
	{
		T obj = m_ObjectsInUse.Top();
		m_ObjectsInUse.Pop();
		return obj;
	}
}

template <class T>
void UndoRedoManager<T>::DeleteLastReceived()
{
	m_ObjectsInUse.Pop();
}

template <class T>
void UndoRedoManager<T>::EmptyRecycled()
{
	if (!m_Recycled.IsEmpty())
	{
		m_Recycled.DeleteAll();
	}
}

template <class T>
void UndoRedoManager<T>::DeleteAll()
{
	m_Recycled.DeleteAll();
	m_ObjectsInUse.DeleteAll();
}

template <class T>
bool UndoRedoManager<T>::RecycleIsEmpty() const
{
	return m_Recycled.IsEmpty();
}

template <class T>
bool UndoRedoManager<T>::ObjectsInUseIsEmpty() const
{
	return m_ObjectsInUse.IsEmpty();
}
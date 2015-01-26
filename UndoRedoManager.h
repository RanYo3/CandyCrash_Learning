#pragma once

#include "Stack.cpp"

template <class T>
class UndoRedoManager
{
public:
	UndoRedoManager();
	~UndoRedoManager();

	UndoRedoManager(const UndoRedoManager<T> &);
	const UndoRedoManager<T> &operator=(const UndoRedoManager<T> &);

	void AddNew(T);
	void AddToRecycled(T);
	T Redo();
	T Undo();
	void DeleteLastReceived();
	void EmptyRecycled();
	void DeleteAll();

	bool RecycleIsEmpty() const;
	bool ObjectsInUseIsEmpty() const;

private:
	Stack<T> m_ObjectsInUse;
	Stack<T> m_Recycled;
};
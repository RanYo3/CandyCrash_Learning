#pragma once

#define INIT_SIZE 10

template <class T, int _size = INIT_SIZE>
class Stack
{
public:
	Stack(int = _size);
	~Stack();

	Stack(const Stack<T, _size> &);
	const Stack<T, _size> &operator=(const Stack<T, _size> &);

	void Push(T);
	void Pop();
	void DeleteAll();

	T Top() const;
	bool IsEmpty() const;
	int GetSize() const;
	void Print() const;

private:
	T *m_Array;
	int m_Size;
	int m_Capacity;
};
#pragma once
#include "Node.h"
template < typename T>
class Stack
{
	Node<T>*Top;
	int size;
public:
	Stack();
	bool isEmpty()const;
	bool push(T it);
	bool pop(T&it);
	T peek()const;
	const T** toArray(int& size);
};

template < typename T>
Stack<T> ::Stack()
{
	Top = NULL;
	size = 0;
}

template < typename T>
bool Stack<T> ::isEmpty()const
{
	if (Top)
		return false;
	return true;
}

template < typename T>
T Stack<T> ::peek()const
{
	return Top->getItem();
}

template < typename T>
bool Stack<T> ::pop(T&it)
{
	if (isEmpty())return false;
	Node<T>*Temp = Top;
	Top = Top->getNext();
	it = Temp->getItem();
	delete Temp;
	--size;
	return true;
}

template < typename T>
bool Stack<T> ::push(T it)
{
	Node<T>*Added = new Node<T>(it);
	if (!Added)return false;
	Added->setNext(Top);
	Top = Added;
	++size;
	return true;
}

template<typename T>
const T** Stack<T>::toArray(int& length) {
	length = size;
	if (!size)
		return nullptr;
	Node<T>* temp = Top;
	T** newArray = new T*[length];
	for (int i = 0; i < length; ++i) {
		newArray[i] = &temp->getItem();
		temp = temp->getNext();
	}
	return newArray;
}
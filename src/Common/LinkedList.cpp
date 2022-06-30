/*
 * LinkedList.cpp
 *
 *  Created on: 3-jan.-2017
 *      Author: lieven2
 */
#include "LinkedList.h"



template <class T>
LinkedList<T>::LinkedList()
{
	_first = 0;
	_last = 0;
}

template <class T>
LinkedList<T>::~LinkedList()
{
	Node<T>* temp = _first;
	while(temp != 0)
	{
		temp = temp->next;
		delete(_first);
		_first = temp;
	}
}

template <class T>
void LinkedList<T>::insertAtBack(T valueToInsert)
{
	Node<T>* newNode=new Node<T>();
	newNode->val = valueToInsert;
	newNode->next = 0;

	Node<T>* temp = _first;

	if (temp != 0)
	{
		while (temp->next != 0)
		{
			temp = temp->next;
		}

		temp->next = newNode;
	}
	else
	{
		_first = newNode;
	}
}

template <class T>
bool LinkedList<T>::removeFromBack()
{
	if (_first == 0 && _last == 0) {return false;}

	if (_first == _last)
	{
//		cout<<"_first is equal to _last."<<endl;
		delete(_first);
		_first = _last = 0;
		return true;
	}

	else
	{
		Node<T>* temp = _first;
		int nodeCount = 0;

		while (temp != 0)
		{
			nodeCount = nodeCount + 1;
			temp = temp->next;
		}

		Node<T>* temp2 = _first;

		for(int i = 1; i < (nodeCount - 1); i++)
		{
			temp2 = temp2->next;
		}

//		cout << temp2->val<<endl;
		delete(temp2->next);

		_last = temp2;
		_last->next = 0;

		return true;
	}
}

template <class T>
void LinkedList<T>::print()
{
	Node<T>* temp = _first;

	if (temp == 0)
	{
//		cout<<"";
	}

	if (temp->next == 0)
	{
//		cout<<temp->val;
	}
	else
	{
		while (temp != 0)
		{
//			cout<< temp->val;
			temp = temp->next;
//			cout<< ",";
		}
	}
}

template <class T>
bool LinkedList<T>::isEmpty()
{
	if (_first == 0 && _last == 0) {return true;}
	else {return false;}
}

template <class T>
int LinkedList<T>::size()
{
	if (_first == 0 && _last == 0) {return 0;}

	Node<T>* temp = _first;
	int nodeCounter = 0;

	while (temp != 0)
	{
		nodeCounter = nodeCounter + 1;
		temp = temp->next;
	}
	return nodeCounter;
}

template <class T>
void LinkedList<T>::clear()
{
	Node<T>* temp = _first;
	while(temp != 0)
	{
		temp = temp->next;
		_first = temp;
		delete(temp);
	}
}

template <class T>
void LinkedList<T>::insertAtFront(T valueToInsert)
{
	Node<T>* newNode;

	newNode->val = valueToInsert;

  	 if(_first == 0)
   	{
   		_first = newNode;
   	}
   	else
   	{
   		newNode->next = _first;
   		_first = newNode;
   	}

}

template <class T>
bool LinkedList<T>::removeFromFront()
{
	if (_first == 0 && _last == 0) {return false;}

	else
	{
		Node<T>* temp;

		temp = _first;
		_first = _first->next;

		delete(temp);

		return true;
	}
}

template <class T>
T& LinkedList<T>::firstNum()
{
	return _first->val;
}

template <class T> T* LinkedList<T>::first() {
	if ( _first ) {
		_current = _first;
		return &(_first->val);
	}
	return 0;
}

template <class T> T* LinkedList<T>::next() {
	Node<T>* temp;
	temp=_current;
	if ( _current ) _current=_current->next;
	return &temp->next->val;
}



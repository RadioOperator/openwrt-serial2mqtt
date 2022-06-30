/*
 * LinkedList.h
 *
 *  Created on: 3-jan.-2017
 *      Author: lieven2
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

template<class T>
struct Node {
	T val;
	Node<T> *next;
};

template<class T>
class LinkedList {
public:
	LinkedList();
	~LinkedList();
	void insertAtBack(T valueToInsert);
	bool removeFromBack();
	void print();
	bool isEmpty();
	int size();
	void clear();

	void insertAtFront(T valueToInsert);
	bool removeFromFront();

	T& firstNum();
	T* first();
	T* next();

private:
	Node<T> *_first;
	Node<T> *_last;
	Node<T> *_current;
};

#endif /* LINKEDLIST_H_ */

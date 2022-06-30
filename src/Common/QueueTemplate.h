/*
 * File:   EventQueue.h
 * Author: lieven
 *
 * Created on September 5, 2013, 9:14 PM
 */

#ifndef QUEUETEMPLATE_H
#define	QUEUETEMPLATE_H
#include "Erc.h"
#include "Sys.h"


template<class T>
class QueueTemplate {
public:
	QueueTemplate(int count);
	Erc put(T& t);
	Erc get(T& t);
	uint32_t size();
private:
	T* _start;
	uint16_t _readPos;
	uint16_t _writePos;
	uint16_t _limit;
};
template<class T>
QueueTemplate<T>::QueueTemplate(int size) {
//	_start = (T*) malloc(size * sizeof(T));
	_start = new T[size];//(T*) Sys::malloc(size * sizeof(T));
	ASSERT(_start!=0);
	_limit = size;
	_readPos = 0;
	_writePos = 1;
}

template<class T>
Erc QueueTemplate<T>::put(T& t) {
	Erc erc;
//	Sys::interruptDisable();
	uint16_t newPos = (_writePos + 1) % _limit;
	if (newPos == _readPos) {
		erc = E_LACK_RESOURCE;
	} else {
	_start[_writePos] = t;
	_writePos = newPos; // last operation ( hopefully atomic to ISR)
	erc=E_OK;
	}
//	Sys::interruptEnable();
	return erc;
}

template<class T>
Erc QueueTemplate<T>::get(T& t) {
	Erc erc;
//	Sys::interruptDisable();
	uint16_t newPos = (_readPos + 1) % _limit;
	if (newPos == _writePos) {
		erc = E_LACK_RESOURCE;
	} else {
		t = _start[newPos];
		_readPos = newPos; // last operation ( hopefully atomic to ISR)
		erc = E_OK;
	}
//	Sys::interruptEnable();
	return erc;
}

template<class T>
uint32_t QueueTemplate<T>::size() {
	if (_writePos < _readPos) {
		return _writePos + _limit - _readPos - 1;
	} else
		return _writePos - _readPos - 1;
}

#endif	/* QUEUETEMPLATE_H */


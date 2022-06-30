/*
 * CborQueue.h
 *
 *  Created on: Nov 24, 2015
 *      Author: lieven
 */

#ifndef INC_CBORQUEUE_H_
#define INC_CBORQUEUE_H_

#include "Erc.h"
#include "Cbor.h"
#include <BipBuffer.h>
#include <Sema.h>

class CborQueue {
private:
public:
	BipBuffer _buffer;
//	Cbor cbor;
	uint32_t _read_size;
	uint32_t _write_size;
	uint8_t* _start;
	Sema& _semaphore;
	Erc getMap(Cbor& cbor);
	Erc getRelease(Cbor& cbor);
	Erc putMap(Cbor& cbor);
	Erc putRelease(Cbor& cbor);
public:
	CborQueue(uint32_t size) ;
	virtual ~CborQueue() ;
	Erc put(Cbor& cbor) ;
	Erc putf(const char * format, ...) ;
	Erc vputf(const char *fmt, va_list args);
	Erc get(Cbor& cbor) ;
	Erc getf(const char * format, ...) ;

	bool hasData() ;
	bool hasSpace(uint32_t size) ;
	uint32_t getCapacity();
	uint32_t getUsed();
};

#endif /* INC_CBORQUEUE_H_ */

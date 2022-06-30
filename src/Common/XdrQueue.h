/*
 * CborQueue.h
 *
 *  Created on: Nov 24, 2015
 *      Author: lieven
 */

#ifndef INC_XDRQUEUE_H_
#define INC_XDRQUEUE_H_

#include "Erc.h"
#include <Xdr.h>
#include "XdrQueue.h"
#include <BipBuffer.h>
#include <Sema.h>

class XdrQueue {
	private:
		uint32_t* _start;
		uint32_t _tail;
		uint32_t _head;
		uint32_t _capacity;
		Sema& _semaphore;
		int write(uint32_t);
		int read(uint32_t&);
		uint32_t read();

	public:
		XdrQueue(uint32_t size) ;
		virtual ~XdrQueue() ;
		int enqueue(Xdr& );
		int dequeue(Xdr&);
		bool hasData(uint32_t sz=1) ;
		bool hasSpace(uint32_t) ;

};

#endif /* INC_CBORQUEUE_H_ */

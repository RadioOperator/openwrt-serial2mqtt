/*
 * XdrQueue.cpp
 *
 *  Created on: Nov 24, 2015
 *      Author: lieven
 */

#include <XdrQueue.h>
#include <Log.h>

XdrQueue::XdrQueue(uint32_t size) : _semaphore(Sema::create()) {
	_start = new uint32_t[size];
	_capacity=size;
	_head=0;
	_tail=0;
}

XdrQueue::~XdrQueue() { delete _start; }

int XdrQueue::enqueue(Xdr& xdr) {

	if ( hasSpace(xdr.size())+1) {
		write( Tag(Xdr::OBJECT,xdr.size(),"XDR").ui32);
		xdr.rewind();
		for(uint32_t i=0; i< xdr.size(); i++) {
			uint32_t ui;
			xdr.read(ui);
			write(ui);
		}
		return 0;
	}
	assert(false);
	return ENOSPC;
}

int XdrQueue::dequeue(Xdr& xdr) {
	if ( hasData(1)) {
		Tag tag(0);
		assert(read(tag.ui32)==0);
		assert( tag.type == Xdr::OBJECT );
		assert( tag.uid == Uid("XDR").id()) ;
		assert( tag.length < _capacity );
		if ( hasData(tag.length)) {
			xdr.clear();
			for(uint32_t i=0; i<tag.length; i++) {
				uint32_t ui;
				read(ui);
				xdr.write(ui);
			}
			return 0;
		} else {
			WARN("XdrQueue corrupted !");
			assert(false);
			return ENOBUFS;
		}
	}
	assert(false);
	return ENOBUFS;
}

int XdrQueue::write(uint32_t ui) {
	*(_start + _head)=ui;
	_head = (_head+1)%_capacity;
	return 0;
}

int XdrQueue::read(uint32_t& ui) {
	ui=*(_start + _tail);
	_tail = (_tail+1)%_capacity;
	return 0;
}

bool XdrQueue::hasData(uint32_t size) {
	uint32_t data;
	if ( _head > _tail ) {
		data = _head - _tail;
	} else if ( _tail > _head ) {
		data = (_capacity-_tail ) + _head;
	} else {
		data=0;
	}
	return ( data >= size );
}

bool XdrQueue::hasSpace(uint32_t size) {
	uint32_t space;
	if ( _head > _tail ) {
		space = (_capacity-_head ) + _tail;
	} else if ( _tail > _head ) {
		space = _tail - _head;
	} else {
		space=_capacity;
	}
	return ( space >= size );
}

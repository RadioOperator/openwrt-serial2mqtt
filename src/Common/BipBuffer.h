/*
 * BipBuffer.h
 *
 *  Created on: 12-sep.-2014
 *      Author: lieven2
 */

#ifndef BIPBUFFER_H_
#define BIPBUFFER_H_
#include <stdint.h>
#include <string.h>
#include "Sys.h"


class BipBuffer {
private:
	uint8_t* pBuffer;
	int ixa;
	int sza;
	int ixb;
	int szb;
	int buflen;
	int ixResrv;
	int szResrv;

public:
	BipBuffer()  ;
	~BipBuffer() ;
	bool allocateBuffer(int buffersize) ;
	void clear()  ;
	void freeBuffer()  ;
	uint8_t* reserve(int size, int& reserved) ;
	void commit(int size) ;
	uint8_t* getContiguousBlock(uint32_t& size) ;
	void decommitBlock(int size) ;
	int getCommittedSize() const  ;
	int getReservationSize() const ;
	int getBufferSize() const ;
	bool isInitialized() const ;
	bool hasSpace(uint32_t) ;
	 bool hasData() ;
private:
	int getSpaceAfterA() const  ;

	int getBFreeSpace() const  ;
};


#endif /* BIPBUFFER_H_ */

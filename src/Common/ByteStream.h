/*
 * Stream.h
 *
 *  Created on: 2-sep.-2016
 *      Author: lieven2
 */

#ifndef BYTE_STREAM_H_
#define BYTE_STREAM_H_
#include <Bytes.h>
class ByteStream {
public:
	ByteStream(){};
	virtual ~ByteStream(){};
	virtual Erc open()=0;
	virtual Erc close()=0;
	virtual Erc write(Bytes& data)=0;
	virtual Erc write(uint8_t data)=0;
	virtual uint8_t read()=0;
	virtual Erc read(Bytes& data)=0;
	virtual bool hasData()=0;
	virtual bool hasSpace()=0;
	virtual bool hasSpace(uint32_t sp)=0;
	virtual void flush()=0;
};

#endif /* BYTE_STREAM_H_ */

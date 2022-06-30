/*
 * BufferedStream.h
 *
 *  Created on: 2-sep.-2016
 *      Author: lieven2
 */

#ifndef BUFFEREDBYTESTREAM_H_
#define BUFFEREDBYTESTREAM_H_
#include <Bytes.h>
#include <ByteStream.h>
#include <CircBuf.h>
class BufferedByteStream : public ByteStream{

public:
	CircBuf _rxd;
	CircBuf _txd;
	// user interface
	BufferedByteStream(uint32_t sizeBuffer);
	~BufferedByteStream();
	virtual Erc open() =0 ;
	virtual Erc close()=0 ;
	virtual void flush() =0;
	Erc write(Bytes& data);
	Erc write(uint8_t data);
	uint8_t read();
	Erc read(Bytes& data);
	bool hasData();
	bool hasSpace();
	bool hasSpace(uint32_t sp);
	// ISR
	bool canReceive();
	void receive(uint8_t data);
	bool hasToSend();
	uint8_t toSend();
};

#endif /* BUFFEREDBYTESTREAM_H_ */

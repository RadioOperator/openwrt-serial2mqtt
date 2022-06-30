/*
 * Uart.h
 *
 *  Created on: Sep 17, 2015
 *      Author: lieven
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "Erc.h"
#include "Bytes.h"
#include "CircBuf.h"

#include "Stream.h"

class Uart : public Stream {
public:
	virtual ~Uart(){};
	virtual void init(uint32_t baudrate)=0;

//	virtual void init(uint8_t bits,uint8_t parity,uint8_t stopBits)=0;

	virtual Erc write(Bytes& data)=0;
	virtual Erc write(uint8_t b)=0;
	virtual bool hasData()=0;
	virtual bool hasSpace()=0;
	virtual uint8_t read()=0;
	virtual void receive(uint8_t b)=0;
	virtual Erc setBaudrate(uint32_t baudrate)=0;
	virtual uint32_t getBaudrate()=0;
	virtual Erc setMode(const char* str)=0;
	virtual void getMode(char* str)=0;
};

#endif /* UART_H_ */

/*
 * Msg.h
 *
 *  Created on: 12-sep.-2014
 *      Author: lieven2
 */

#ifndef SIG_H_
#define SIG_H_

typedef enum Signal {
	SIG_ALL=0,
	SIG_INIT,
	SIG_NEW,
	SIG_DELETE,
	SIG_IDLE,
	SIG_ERC,
	SIG_TICK,
	SIG_CONNECTED,
	SIG_DISCONNECTED,
	SIG_RXD,
	SIG_TXD,
	SIG_CHANGE,
	SIG_START,
	SIG_STOP,
	SIG_DO,
	SIG_USER
} Signal;


extern const char* strSignal[];

#ifdef __cplusplus
class Handler;
#include "Bytes.h"
#include "BipBuffer.h"
#include "Cbor.h"
#include "CborQueue.h"

class Msg: public Cbor {
public:
	static CborQueue* _queue;
	static bool _init;
	 static void wakeup();
public:
	void* _src;
	Signal _signal;
	uint32_t _offset;

	Msg(uint32_t size);
	bool is(const void* src, Signal signal);
	bool is(const void* src, Signal signal, int v1);
	static bool init();
	 Msg& create(const void * src, Signal signal);
	 static Erc publish(const void * src, Signal signal);
	 static Erc publish(const void * src, Signal signal, int par);
	 static CborQueue& queue();
//	static void vpublish(const char* fmt, ...);

	Msg& rewind();
	Msg& send();
	bool receive();
	Msg& free();
	Signal signal();
	void* src();
};

#endif

#endif /* SIG_H_ */

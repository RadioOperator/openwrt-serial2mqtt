/*
 * Handler.h
 *
 *  Created on: 20-dec.-2014
 *      Author: lieven2
 */

#ifndef HANDLER_H_
#define HANDLER_H_

#include "Msg.h"
#include "ProtoThread.h"

class Handler: public ProtoThread {
	static Handler* _firstChild;
	char _name[10];
	Handler* _next;
	uint64_t _timeout;

public:
//	Handler();
	 Handler(const char* name);

	 ~Handler() ;

	void timeout(uint32_t msec);
	bool timeout();
	uint64_t getTimeout();
	const char* getName();
//_____________________________________
	static Handler* first();
	Handler* next();
	static void  dispatchToChilds(Msg& msg);
	static bool timeouts();
	static  void reg(Handler* hdlr);
	static  void unreg(Handler* hdlr);

};

#endif /* HANDLER_H_ */

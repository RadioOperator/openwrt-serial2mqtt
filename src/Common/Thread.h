/*
 * Thread.h
 *
 *  Created on: 2-jun.-2014
 *      Author: lieven2
 */

#ifndef THREAD_H_
#define THREAD_H_
#include "stdint.h"
#include "Erc.h"
#include "Sys.h"
//#include "FreeRTOS.h"
// #include "task.h"
// #include "semphr.h"
class Thread {
private:
//	xTaskHandle _taskHandle;
//	xSemaphoreHandle _semaphore;
	void* _ref;

public:
	Thread(const char *name, unsigned short stackDepth, char priority);
	~Thread(){};
	void sleep(uint32_t time);
	Erc wakeup();
	Erc yield();
	void wait(int timeout);
	void notify();
	void start();
	virtual void run() =0;
};

#endif /* THREAD_H_ */

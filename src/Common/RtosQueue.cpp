#include "RtosQueue.h"
#include <sys/select.h>

RtosQueue::~RtosQueue() {

}
//___________________________________________________ ESP8266 / ESP32
//
#if defined(ESP32_IDF) || defined(ESP_OPEN_RTOS)

#if defined(ESP32_IDF)
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#endif // ESP32_IDF

#if defined(ESP_OPEN_RTOS)
#include <FreeRTOS.h>
#include <queue.h>
#endif // ESP_OPEN_RTOS



class FreeRtosQueue : public RtosQueue {

	private:
		QueueHandle_t _queue;
	public:
		FreeRtosQueue(uint32_t size) ;
		virtual ~FreeRtosQueue() ;
		int enqueue(Xdr& );
		int dequeue(Xdr&,uint32_t time);
};


FreeRtosQueue::FreeRtosQueue(uint32_t size) {
	INFO(" FreeRtosQueue created ");
	_queue = xQueueCreate(size,sizeof(Xdr*));

}

FreeRtosQueue::~FreeRtosQueue() {
}


int FreeRtosQueue::enqueue(Xdr& xdr) {
	Xdr* nx = new Xdr(xdr.size());
	*nx=xdr;
	if ( xQueueSend(_queue,&nx,1)!=pdTRUE ) {
		WARN("enqueue failed");
		return ENOENT;
	}
	return 0;
}
int FreeRtosQueue::dequeue(Xdr& xdr,uint32_t time) {
	Xdr* px;
	if ( time < 10 ) time=10; // timer tick is at 10 msec
	if ( xQueueReceive(_queue,&px,time/portTICK_PERIOD_MS+1)!=pdTRUE) {
		return ENOENT;
	}
	xdr = *px; // copy data
	delete px;
	return 0;
}



RtosQueue& RtosQueue::create(uint32_t size ) {
	return *new FreeRtosQueue(size);
}


#endif // defined(ESP32_IDF) || defined(ESP_OPEN_RTOS)
//______________________________________________________ ARDUINO
//

#if  defined(ARDUINO)
#include <Log.h>
#include <queue>


class ArduinoRtosQueue : public RtosQueue {

	private:
		std::queue<Xdr*> _queue;
	public:
		ArduinoRtosQueue(uint32_t size) ;
		virtual ~ArduinoRtosQueue() ;
		int enqueue(Xdr& );
		int dequeue(Xdr&,uint32_t time);
};


ArduinoRtosQueue::ArduinoRtosQueue(uint32_t size) {
	INFO(" ArduinoRtosQueue created ");

}

ArduinoRtosQueue::~ArduinoRtosQueue() {
}


int ArduinoRtosQueue::enqueue(Xdr& xdr) {
	Xdr* nx = new Xdr(xdr.size());
	*nx=xdr;
	_queue.push(nx);
	return 0;
}
int ArduinoRtosQueue::dequeue(Xdr& xdr,uint32_t time) {
	Xdr* px;
	if ( time < 10 ) time=10; // timer tick is at 10 msec
	if ( _queue.empty() ) return ENOENT;
	px= _queue.front();
	_queue.pop();
	xdr = *px; // copy data
	delete px;
	return 0;
}



RtosQueue& RtosQueue::create(uint32_t size ) {
	return *new ArduinoRtosQueue(size);
}

#endif // ESP32_IDF
//_______________________________________________________ LINUX
//
#ifdef __linux__
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <unistd.h>

class LinuxRtosQueue : public RtosQueue {

	private:
		int _pipefd[2];
	public:
		LinuxRtosQueue(uint32_t size) ;
		~LinuxRtosQueue() ;
		int enqueue(Xdr& );
		int dequeue(Xdr&,uint32_t);
};


LinuxRtosQueue::LinuxRtosQueue(uint32_t size) {

	if (pipe(_pipefd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	INFO(" LinuxRtosQueue created ");

}

LinuxRtosQueue::~LinuxRtosQueue() {
	close(_pipefd[0]);
	close(_pipefd[1]);
}


int LinuxRtosQueue::enqueue(Xdr& xdr) {
	Xdr* nx = new Xdr(xdr.size());
	*nx=xdr;
	assert(write(_pipefd[1],&nx,sizeof(Xdr*))==sizeof(Xdr*));
	return 0;
}

int LinuxRtosQueue::dequeue(Xdr& xdr,uint32_t waitTime) {
	Xdr* px;
	uint64_t start=Sys::millis();

	fd_set set;
	struct timeval timeout;
	int rv;

	FD_ZERO(&set); /* clear the set */
	FD_SET(_pipefd[0], &set); /* add our file descriptor to the set */

	timeout.tv_sec = 0;
	timeout.tv_usec = waitTime*1000;

	rv = select(_pipefd[0] + 1, &set, NULL, NULL, &timeout);
	if(rv == -1) {
		WARN(" select failed : [%d] '%s'",errno,strerror(errno));
		assert(false);
	} else if(rv == 0) {
//		INFO(" select wait() %u %lu",waitTime,Sys::millis()-start);
		return ETIMEDOUT;
	};
	assert(read( _pipefd[0],&px,sizeof(Xdr*))==sizeof(Xdr*)); /* there was data to read */

	xdr = *px; // copy data
	delete px;
	return 0;
}

RtosQueue& RtosQueue::create(uint32_t size ) {
	return *new LinuxRtosQueue(size);
}

#endif // __linux__

#ifndef RTOSQUEUE_H
#define RTOSQUEUE_H

#include <Xdr.h>

class RtosQueue {

	public:
		virtual int enqueue(Xdr& )=0;
		virtual int dequeue(Xdr&,uint32_t)=0;
		virtual ~RtosQueue();
		static RtosQueue& create(uint32_t size);
};

#endif // RTOSQUEUE_H

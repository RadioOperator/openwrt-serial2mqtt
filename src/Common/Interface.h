/*
 * Interface.h
 *
 *  Created on: 22-jun.-2013
 *      Author: lieven2
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_
#include "Bytes.h"
namespace std {

class Interface {
private:
	bool bConnected;
public:
	virtual int send(Bytes& txdBuffer)=0;
	virtual int recv(Bytes* rxdBuffer)=0;
	bool isConnected() {
		return bConnected;
	}
	virtual void setConnected(bool value) {
		bConnected = value;
	}
};

} /* namespace std */
#endif /* INTERFACE_H_ */

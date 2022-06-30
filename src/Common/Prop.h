/*
 * Prop.h
 *
 *  Created on: 23-aug.-2014
 *      Author: lieven2
 */

#ifndef PROP_H_
#define PROP_H_
#include <stdint.h>

#include "ProtoThread.h"
#include "Msg.h"
#include "Handler.h"
#include "Bytes.h"
#include "Flags.h"
#include "Mqtt.h"

typedef enum {
	CMD_GET, CMD_DESC, CMD_PUT
} Cmd;

<<<<<<< HEAD
typedef void (*Xdr)(void*, Cmd, Bytes&);
=======
typedef Erc (*Xdr)(void*,  Bytes&);
>>>>>>> ba2e932e81ca0f0e0ca5b746c6e6bf126d9e3403

class Mqtt;

class Prop {
public:

	char* _name;
	Flags _flags;
	uint64_t _lastPublished;
	Prop* _next;

	static Prop* _first;

public:
	Prop();
	Prop(const char* name, Flags flags);
	Prop(const char* name, const char* value);
	Prop(const char* name, uint64_t& value);
<<<<<<< HEAD
=======
	Prop(const char* name,void* instance,Xdr func);
>>>>>>> ba2e932e81ca0f0e0ca5b746c6e6bf126d9e3403
	 ~Prop() {
	}
	void init(const char* name, Flags flags);

	static Prop* findProp(Str& name);

//	static void xdrUint64(void* addr, Cmd cmd, Bytes& strp);
//	static void xdrString(void* addr, Cmd cmd, Bytes& strp);

	virtual void toBytes(Str& topic,Bytes& msg) {
	}
	virtual void fromBytes(Str& topic,Bytes& msg) {
	}
	void metaToBytes(Bytes& msg);
	void nextToBytes(Bytes& msg);
	void firstToBytes(Bytes& msg);

	void updated();
	bool hasToBePublished();
	void doPublish();
	void isPublished();
	static void publishAll();
};

class PropMgr: public Handler {

private:
	Mqtt* _mqtt;
	Str _prefix;
	Str _getPrefix;
	Str _putPrefix;
	Str _headPrefix;
	Str _topic;
	Bytes _message;
	Prop* _cursor;
	Handler *_src;
	bool _publishMeta;
	enum State {
		ST_DISCONNECTED, ST_PUBLISHING, ST_WAIT_PUBRESP
	} _state;

public:
<<<<<<< HEAD
	PropMgr();
=======
	PropMgr(Mqtt* mqtt);
>>>>>>> ba2e932e81ca0f0e0ca5b746c6e6bf126d9e3403
	~PropMgr() {
	}

	bool dispatch(Msg& msg);
	void nextProp();
//	void nextProp(Prop* p);
	void onPublish(Str& topic, Bytes& message);
	void setMqtt(Mqtt* mqtt) {
		_mqtt = mqtt;
	}
	void setPrefix(const char* s);
};

#endif /* PROP_H_ */

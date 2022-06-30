/*
 * Flags.h
 *
 *  Created on: 10-jan.-2015
 *      Author: lieven2
 */

#ifndef FLAGS_H_
#define FLAGS_H_



enum Type {
	T_UINT8,
	T_UINT16,
	T_UINT32,
	T_UINT64,
	T_INT8,
	T_INT16,
	T_INT32,
	T_INT64,
	T_BOOL,
	T_FLOAT,
	T_DOUBLE,
	T_BYTES,
	T_ARRAY,
	T_MAP,
	T_STR,
	T_OBJECT
};

enum Mode {
	M_READ, M_WRITE,M_RW
};

enum Qos {
	QOS_0, QOS_1, QOS_2
};

enum Interface {
	I_ADDRESS, I_INTERFACE, I_SETTER, I_OBJECT
};
enum Interval {
	T_1MSEC,T_10MSEC,T_100MSEC,T_1SEC,T_10SEC,T_100SEC,T_1KSEC,T_10KSEC
};

enum Retained {
	NO_RETAIN,RETAIN
};



typedef struct {
	enum Type type :5;
	enum Mode mode :2;
	enum Interval interval:3;// 0=1 msec -> 7=10^7 msec=10000sec=2,777 hr
	enum Qos qos :2;
	enum Retained retained :1;
	bool doPublish:1;
} Flags;

//Flags flags={T_INT32,M_READ,QOS_0,I_ADDRESS,false,true,true};




#endif /* FLAGS_H_ */

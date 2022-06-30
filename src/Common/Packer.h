/*
 * Packer.h
 *
 *  Created on: 24-okt.-2014
 *      Author: lieven2
 */

#ifndef PACKER_H_
#define PACKER_H_
#include "Bytes.h"
#include "Str.h"

typedef union Variant {
		uint64_t _uint64;
		int64_t _int64;
		double _double;
		float _float;
		bool _bool;
		int _length;
} Variant;

typedef enum {
	P_PINT = 0, P_NINT, P_BYTES, P_STRING, P_ARRAY, P_MAP, P_TAG, P_SPECIAL = 7, // major types
		P_BOOL,
		P_FLOAT,
		P_DOUBLE,
		P_BREAK,
		P_NILL,
		P_ERROR
} PackType;

class Packer {
public:

	virtual Packer& add(int i)=0;
#ifdef DOUBLE
	virtual Packer& add(float f)=0;
	virtual Packer& add(double d)=0;
#endif
	virtual Packer& add(Bytes& b)=0;
	virtual Packer& add(Str& str)=0;
	virtual Packer& add( char const* s)=0;
	virtual Packer& add(uint64_t i64)=0;
	virtual Packer& add(int64_t i64)=0;
	virtual Packer& add(bool b)=0;
	virtual Packer& addMap(int size)=0;
	virtual Packer& addArray(int size)=0;
	virtual Packer& addTag(int nr)=0;
	virtual Packer& addBreak()=0;
	virtual Packer& addNull()=0;

	Erc readToken(PackType& type,Variant& variant);
	Erc toString(Str& str);
private :
	enum ComplexType {X_ARRAY,X_MAP,X_SIMPLE};

};


#endif /* PACKER_H_ */

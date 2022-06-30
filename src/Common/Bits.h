/*
 * Bits.h
 *
 *  Created on: 11-jun.-2014
 *      Author: lieven2
 */

#ifndef BITS_H_
#define BITS_H_
#include <stdint.h>
static const uint32_t bits[] = { 0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048,
		4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576,
		2097152, 4194304, 8388608, 16777216, 33554432, 67108864 };
class Bits {
public:
	Bits();
	virtual ~Bits();
	inline void set(int n) {
		_bits |= bits[n];
	}
	inline void clr(int n) {
		_bits &= ~bits[n];
	}
	inline bool isSet(int n) {
		return _bits & bits[n];
	}
	inline void null(){
		_bits=0;
	}
private:
	uint32_t _bits;
};

#endif /* BITS_H_ */

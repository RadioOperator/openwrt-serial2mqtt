/*
 * Base64.h
 *
 *  Created on: Mar 18, 2016
 *      Author: lieven
 */

#ifndef SRC_BASE64_H_
#define SRC_BASE64_H_

#include <Erc.h>

#include <Bytes.h>
#include <string>

class Base64 {
	private:
		static const char encodeCharacterTable[];
		static const int8_t decodeCharacterTable[];
	public:
		Base64();
		~Base64();
		static Erc encode( std::string& out, Bytes& in);
		static Erc decode( Bytes& out, std::string& in);
};

#endif /* SRC_BASE64_H_ */

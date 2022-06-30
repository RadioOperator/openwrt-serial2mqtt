/*
 * Base64.cpp
 *
 *  Created on: Mar 18, 2016
 *      Author: lieven
 */

#include "Base64.h"

/* Copyright (C) 2008, 2009 Inge Eivind Henriksen
 See the file COPYING that comes with this distribution for copying permission.
 */
/*! \file
 * \brief Contains the Base64 class headers
 */

#include "Base64.h"

/** Static Base64 character encoding lookup table */
const char Base64::encodeCharacterTable[65] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/** Static Base64 character decoding lookup table */
const int8_t Base64::decodeCharacterTable[256] = { -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1,
		-1, -1, -1, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
		16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1, 26, 27,
		28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45,
		46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };

/*!
 \brief Class constructor
 */
Base64::Base64() {
}

/*!
 \brief Class destructor
 */
Base64::~Base64() {
}

/*!
 \brief Encodes binary data to base 64 character data
 \param in The data to encode
 \param out The encoded data as characters
 */
Erc Base64::encode(std::string& out, Bytes& in) {
	char buff1[3];
	char buff2[4];
	uint8_t i = 0, j;
	in.offset(0);
	out.clear();
	while (in.hasData()) {
		buff1[i++] = in.read();
		if (i == 3) {
			out += (encodeCharacterTable[(buff1[0] & 0xfc) >> 2]);
			out += (encodeCharacterTable[((buff1[0] & 0x03) << 4)
					+ ((buff1[1] & 0xf0) >> 4)]);
			out += (encodeCharacterTable[((buff1[1] & 0x0f) << 2)
					+ ((buff1[2] & 0xc0) >> 6)]);
			out += (encodeCharacterTable[buff1[2] & 0x3f]);
			i = 0;
		}
	}
	if (i) {
		for (j = i; j < 3; j++)
			buff1[j] = '\0';

		buff2[0] = (buff1[0] & 0xfc) >> 2;
		buff2[1] = ((buff1[0] & 0x03) << 4) + ((buff1[1] & 0xf0) >> 4);
		buff2[2] = ((buff1[1] & 0x0f) << 2) + ((buff1[2] & 0xc0) >> 6);
		buff2[3] = buff1[2] & 0x3f;

		for (j = 0; j < (i + 1); j++)
			out += (encodeCharacterTable[(int) buff2[j]]);

		while (i++ < 3)
			out += ('=');
	}
	return E_OK;

}

/*!
 \brief Decodes base 64 character data to binary data
 \param in The character data to decode
 \param out The decoded data
 */
Erc Base64::decode(Bytes& out, std::string &in) {
	char buff1[4];
	char buff2[4];
	uint8_t i = 0, j;
	out.clear();

	for (uint32_t i = 0; i < in.length(); i++) {
		buff2[i] = in.at(i);
		if (buff2[i] == '=')
			break;
		if (++i == 4) {
			for (i = 0; i != 4; i++)
				buff2[i] = decodeCharacterTable[(int) buff2[i]];

			out.write((char) ((buff2[0] << 2) + ((buff2[1] & 0x30) >> 4)));
			out.write(
					(char) (((buff2[1] & 0xf) << 4) + ((buff2[2] & 0x3c) >> 2)));
			out.write((char) (((buff2[2] & 0x3) << 6) + buff2[3]));

			i = 0;
		}
	}

	if (i) {
		for (j = i; j < 4; j++)
			buff2[j] = '\0';
		for (j = 0; j < 4; j++)
			buff2[j] = decodeCharacterTable[(int) buff2[j]];

		buff1[0] = (buff2[0] << 2) + ((buff2[1] & 0x30) >> 4);
		buff1[1] = ((buff2[1] & 0xf) << 4) + ((buff2[2] & 0x3c) >> 2);
		buff1[2] = ((buff2[2] & 0x3) << 6) + buff2[3];

		for (j = 0; j < (i - 1); j++)
			out.write((char) buff1[j]);
	}
	return E_OK;
}

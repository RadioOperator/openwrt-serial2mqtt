/*
 * File:   Msgpack.cpp
 * Author: lieven2
 *
 * Created on 21 september 2013, 10:39
 */

#include "Msgpack.h"
#include <string.h>
#include <limits.h>
#ifndef INT8_MAX
#define 	INT8_MAX   0x7f
#define 	INT8_MIN   -0x80 // (-INT8_MAX - 1)
#define 	UINT8_MAX   0xFF // (__CONCAT(INT8_MAX, U) * 2U + 1U)
#define 	INT16_MAX   0x7fff
#define 	INT16_MIN   -0x8000 // (-INT16_MAX - 1)
#define 	UINT16_MAX   0xFFFF // (__CONCAT(INT16_MAX, U) * 2U + 1U)
#define 	INT32_MAX   0x7fffffffL
#define 	INT32_MIN   -0x80000000 // (-INT32_MAX - 1L)
#define 	UINT32_MAX  0xFFFFFFFF //  (__CONCAT(INT32_MAX, U) * 2UL + 1UL)
#define 	INT64_MAX   0x7fffffffffffffffLL
#define 	INT64_MIN   -0x8000000000000000 // (-INT64_MAX - 1LL)
#define 	UINT64_MAX   0xFFFFFFFFFFFFFFFF // (__CONCAT(INT64_MAX, U) * 2ULL + 1ULL)
#endif

#define PACK_8BIT_VALUE(  xData )          \
	write(((uint8_t)xData));

#define PACK_16BIT_VALUE(  xData )                 \
	write(((uint16_t)xData >> 8));    \
	write(((uint16_t)xData));

#define PACK_32BIT_VALUE(  xData )                  \
	write(((uint32_t)xData >> 24));    \
	write(((uint32_t)xData >> 16));    \
	write(((uint32_t)xData >> 8));     \
	write(((uint32_t)xData));

#ifdef SUPPORT_64BIT_VALUE
#define PACK_64BIT_VALUE( xData )                  \
	write((((uint64_t)xData) >> 56));    \
	write((((uint64_t)xData) >> 48));    \
	write((((uint64_t)xData) >> 40));    \
	write((((uint64_t)xData) >> 32));    \
	write((((uint64_t)xData) >> 24));    \
	write((((uint64_t)xData) >> 16));    \
	write((((uint64_t)xData) >> 8));     \
	write((uint64_t)xData);
#endif

Msgpack::Msgpack(int size) :
	Bytes(size) {
}

Msgpack::Msgpack(uint8_t* pb, int size) :
	Bytes(pb, size) {
}

Msgpack::Msgpack(Bytes& b) :
	Bytes(b._start, b._capacity) {
	_offset = b._offset;
	_limit = b._limit;
}

Msgpack::~Msgpack() {

}

void Msgpack::packNil() {
	write(TYPE_VALIABLE_NIL);
}

void Msgpack::pack(bool data) {
	if (data) {
		write(TYPE_VALIABLE_TRUE);
	} else {
		write(TYPE_VALIABLE_FALSE);
	}
}

void Msgpack::pack(const char* s) {
	uint32_t size = strlen(s);
	packStrHeader(size);
	uint32_t i;
	for (i = 0; i < size; i++)
		write(s[i]);
}

void Msgpack::pack(float data) {

	union {
		float f;
		uint32_t i;
	} mem;
	mem.f = data;
	write(TYPE_VALIABLE_FLOAT);
	PACK_32BIT_VALUE(mem.i);
}

void Msgpack::pack(uint8_t data) {
	write(TYPE_VALIABLE_UINT8);
	PACK_8BIT_VALUE(data);
}

void Msgpack::pack(uint16_t data) {
	write(TYPE_VALIABLE_UINT16);
	PACK_16BIT_VALUE(data);
}

void Msgpack::pack(uint32_t data) {
	write(TYPE_VALIABLE_UINT32);
	PACK_32BIT_VALUE(data);
}

void Msgpack::pack(uint64_t data) {
	write(TYPE_VALIABLE_UINT64);
	PACK_64BIT_VALUE(data);
}

void Msgpack::pack(int8_t data) {
	write(TYPE_VALIABLE_INT8);
	PACK_8BIT_VALUE(data);
}

void Msgpack::pack(int16_t data) {
	write(TYPE_VALIABLE_INT16);
	PACK_16BIT_VALUE(data);
}

void Msgpack::pack(int32_t data) {
	write(TYPE_VALIABLE_INT32);
	PACK_32BIT_VALUE(data);
}

void Msgpack::packUInt(unsigned int data) {
	if (data < 0x80) {
		return pack((uint8_t) data);
	} else if (data <= UINT8_MAX) {
		return pack((uint8_t) data);
	} else if (data <= UINT16_MAX) {
		return pack((uint16_t) data);
	} else {
		return pack((uint32_t) data);
	}
}

void Msgpack::packInt(int data) {
	if (data >= 0) {
		pack((uint32_t) data);
	} else if (data >= -32) {
		pack((int8_t) data);
	} else if (data >= INT8_MIN) {
		pack((int8_t) data);
	} else if (data >= INT16_MIN) {
		pack((int16_t) data);
	} else {
		pack((int32_t) data);
	}
}

void Msgpack::pack(uint8_t* data, uint32_t size) {
	packRawHeader(size);
	uint32_t i;
	for (i = 0; i < size; i++)
		write(data[i]);
}

void Msgpack::packRawHeader(uint32_t data_size) {
	if (data_size < 32) {
		write((uint8_t) (TYPE_VALIABLE_BIN8 | (unsigned char) data_size));
	} else if (data_size < 0x10000) {
		write(TYPE_VALIABLE_BIN16);
		PACK_16BIT_VALUE(data_size);
	} else {
		write(TYPE_VALIABLE_BIN32);
		PACK_32BIT_VALUE(data_size);
	}
}

void Msgpack::packStrHeader(uint32_t data_size) {
	if (data_size < 32) {
		write((uint8_t) (TYPE_VALIABLE_STR8 | (unsigned char) data_size));
	} else if (data_size < 0x10000) {
		write(TYPE_VALIABLE_STR16);
		PACK_16BIT_VALUE(data_size);
	} else {
		write(TYPE_VALIABLE_STR32);
		PACK_32BIT_VALUE(data_size);
	}
}

void Msgpack::packArrayHeader(uint32_t size) {
}

void Msgpack::packMapHeader(uint32_t size) {
}

#ifdef SUPPORT_64BIT_VALUE

void Msgpack::pack(double data) {

	union {
		double d;
		uint64_t i;
	} mem;
	mem.d = data;
	write(TYPE_VALIABLE_DOUBLE);
	PACK_64BIT_VALUE(mem.i);
}
#endif

/// Get 8bit value from buffer.
#define UNPACK_GET_8BIT_VALUE(d)  (*(d))

/// Get 16bit value from buffer.
#define UNPACK_GET_16BIT_VALUE(d)         \
	((uint16_t)(*d) << 8) |               \
	(uint16_t)(*(d+1))

/// Get 32bit value from buffer.
#define UNPACK_GET_32BIT_VALUE(d)         \
	((uint32_t)(*d) << 24)     |          \
	((uint32_t)*(d+1) << 16) |            \
	((uint32_t)*(d+2) <<  8) |            \
	(uint32_t)*(d+3)

#ifdef SUPPORT_64BIT_VALUE
/// Get 64bit value from buffer.
#define UNPACK_GET_64BIT_VALUE(d)         \
	((uint64_t)(*d) << 56)   |            \
	((uint64_t)*(d+1) << 48) |            \
	((uint64_t)*(d+2) << 40) |            \
	((uint64_t)*(d+3) << 32) |            \
	((uint64_t)*(d+4) << 24) |            \
	((uint64_t)*(d+5) << 16) |            \
	((uint64_t)*(d+6) <<  8) |            \
	(uint64_t)*(d+7)
#endif

unpack_base_info_t unpack_base(uint8_t* buf) {
	unpack_base_info_t info = { 0,0,0 };
	unsigned char header = (uint8_t) (UNPACK_GET_8BIT_VALUE(buf));
	buf++;

	info.type = header;
	if (header == TYPE_VALIABLE_NIL) {
		info.size = 1;
	} else if (header == TYPE_VALIABLE_FALSE) {
		info.size = 1;
	} else if (header == TYPE_VALIABLE_TRUE) {
		info.size = 1;
	} else if (header == TYPE_VALIABLE_FLOAT) {
		info.size = 5;
		info.value.uint32_value = (uint32_t) (UNPACK_GET_32BIT_VALUE(buf));
	}
#ifdef SUPPORT_64BIT_VALUE
	else if (header == TYPE_VALIABLE_DOUBLE) {
		info.size = 9;
		info.value.uint64_value = (uint64_t) (UNPACK_GET_64BIT_VALUE(buf));
	}
#endif
	else if (header == TYPE_VALIABLE_UINT8) {
		info.size = 2;
		info.value.uint8_value = (uint8_t) (UNPACK_GET_8BIT_VALUE(buf));
	} else if (header == TYPE_VALIABLE_UINT16) {
		info.size = 3;
		info.value.uint16_value = (uint16_t) (UNPACK_GET_16BIT_VALUE(buf));
	} else if (header == TYPE_VALIABLE_UINT32) {
		info.size = 5;
		info.value.uint32_value = (uint32_t) (UNPACK_GET_32BIT_VALUE(buf));
	}
#ifdef SUPPORT_64BIT_VALUE
	else if (header == TYPE_VALIABLE_UINT64) {
	}
#endif
	else if (header == TYPE_VALIABLE_INT8) {
		info.size = 2;
		info.value.uint8_value = (uint8_t) (UNPACK_GET_8BIT_VALUE(buf));
	} else if (header == TYPE_VALIABLE_INT16) {
		info.size = 3;
		info.value.uint16_value = (int16_t) (UNPACK_GET_16BIT_VALUE(buf));
	} else if (header == TYPE_VALIABLE_INT32) {
		info.size = 5;
		info.value.uint32_value = (int32_t) (UNPACK_GET_32BIT_VALUE(buf));
	}
#if 0
	else if (header == TYPE_VALIABLE_INT64) {
	}
#endif
	else if (header == TYPE_VALIABLE_RAW16) {
		size_t data_size = (size_t) (UNPACK_GET_16BIT_VALUE(buf));
		info.size = 3;
		info.value.size = data_size;
	} else if (header == TYPE_VALIABLE_RAW32) {
		size_t data_size = (size_t) (UNPACK_GET_32BIT_VALUE(buf));
		info.size = 5;
		info.value.size = data_size;
	}
#if 0
	else if (header == TYPE_VALIABLE_ARRAY16) {
	} else if (header == TYPE_VALIABLE_ARRAY32) {
	} else if (header == TYPE_VALIABLE_MAP16) {
	} else if (header == TYPE_VALIABLE_MAP32) {
	}
#endif
	else {
		if ((header & TYPE_POSITIVE_FIXNUM_MASK) == TYPE_POSITIVE_FIXNUM) {
			info.size = 1;
			info.type = TYPE_POSITIVE_FIXNUM;
			info.value.uint8_value = (uint8_t) (header);
		} else if ((header & TYPE_NEGATIVE_FIXNUM_MASK) == TYPE_NEGATIVE_FIXNUM) {
			info.size = 1;
			info.type = TYPE_NEGATIVE_FIXNUM;
			info.value.int8_value = (int8_t) (header);
		} else if ((header & TYPE_FIXRAW_MASK) == TYPE_FIXRAW) {
			info.size = 1;
			info.type = TYPE_FIXRAW;
			info.value.size = (size_t) (header & ~TYPE_FIXRAW_MASK);
		}
#if 0
		else if ((header & TYPE_FIXARRAY_MASK) == TYPE_FIXARRAY) {
		} else if ((header & TYPE_FIXMAP_MASK) == TYPE_FIXMAP) {
		}
#endif
	}
	return info;
}

int unpack(unpack_info_t *info, uint8_t* buf) {
	unpack_base_info_t info_base = unpack_base(buf);
	int size = info_base.size;
	if (info_base.type == TYPE_VALIABLE_NIL) {
		info->type = UNPACK_TYPE_NIL;
	} else if (info_base.type == TYPE_VALIABLE_FALSE) {
		info->type = UNPACK_TYPE_BOOL;
		info->value.bool_value = false;
	} else if (info_base.type == TYPE_VALIABLE_TRUE) {
		info->type = UNPACK_TYPE_BOOL;
		info->value.bool_value = true;
	} else if (info_base.type == TYPE_VALIABLE_FLOAT) {
		info->type = UNPACK_TYPE_FLOAT;
		info->value.float_value = info_base.value.float_value;
	}
#ifdef SUPPORT_64BIT_VALUE
	else if (info_base.type == TYPE_VALIABLE_DOUBLE) {
		info->type = UNPACK_TYPE_DOUBLE;
		info->value.double_value = info_base.value.double_value;
	}
#endif
	else if (info_base.type == TYPE_POSITIVE_FIXNUM
	         || info_base.type == TYPE_VALIABLE_UINT8) {
		info->type = UNPACK_TYPE_UINT;
		info->value.uint_value = (unsigned int) info_base.value.uint8_value;
	} else if (info_base.type == TYPE_VALIABLE_UINT16) {
		info->type = UNPACK_TYPE_UINT;
		info->value.uint_value = (unsigned int) info_base.value.uint16_value;
	} else if (info_base.type == TYPE_VALIABLE_UINT32) {
		info->type = UNPACK_TYPE_UINT;
		info->value.uint_value = (unsigned int) info_base.value.uint32_value;
	} else if (info_base.type == TYPE_NEGATIVE_FIXNUM
	           || info_base.type == TYPE_VALIABLE_INT8) {
		info->type = UNPACK_TYPE_INT;
		info->value.int_value = (int) info_base.value.int8_value;
	} else if (info_base.type == TYPE_VALIABLE_INT16) {
		info->type = UNPACK_TYPE_INT;
		info->value.int_value = (int) info_base.value.int16_value;
	} else if (info_base.type == TYPE_VALIABLE_INT32) {
		info->type = UNPACK_TYPE_INT;
		info->value.int_value = (int) info_base.value.int32_value;
	} else if (info_base.type == TYPE_FIXRAW
	           || info_base.type == TYPE_VALIABLE_RAW16
	           || info_base.type == TYPE_VALIABLE_RAW32) {
		info->type = UNPACK_TYPE_RAW;
		info->value.raw_value.size = info_base.value.size;
		info->value.raw_value.data = (buf + info_base.size);
		size += info_base.value.size;
	}
	return size;

}

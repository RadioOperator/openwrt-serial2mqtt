/*
 * File:   Strpack.cpp
 * Author: lieven2
 *
 * Created on 23 september 2013, 21:43
 */


#include "Strpack.h"
/*
 * Macros for converting digits to letters and vice versa
 */
#define	to_digit(c)	((c) - '0')
#define is_digit(c)	((unsigned)to_digit(c) <= 9)
#define	to_char(n)	((n) + '0')


/*
 * Convert an unsigned long to ASCII for printf purposes, returning
 * a pointer to the first character of the string representation.
 * Octal numbers can be forced to have a leading zero; hex numbers
 * use the given digits.
 */
#define LONG_MAX 0x7FFFFFFFFFFFFFFFL
Strpack::Strpack(int size) : Str(size)
{};

Strpack::~Strpack() {
}

Strpack::Strpack(Strpack& orig)  : Str(orig) {
}

Strpack::Strpack(uint8_t *pb, uint32_t length) : Str(pb, length) {
}

void Strpack::pack(char *pc, uint32_t length) {
    uint32_t i;
    for (i = 0; i < length; i++)
        write(*(pc + i));
}

void Strpack::pack(const char* s) {
    append(s);
}

void Strpack::pack(uint64_t val) {
    append(val);
}

void Strpack::pack(uint32_t val) {
    append(val);
}

void Strpack::pack(int32_t val) {
    append(val);
}

void Strpack::pack(Bytes* val) {
    pack((char*)val->data(),val->length());
}

void Strpack::pack(Str* val) {
    pack((char*)val->data(),val->length());
}

void Strpack::pack(bool b) {
    append(b);
}

void Strpack::pack(float f) {
    int i;

    union {
        uint8_t b[4];
        uint32_t ui32;
        float f;
    } reg;
    reg.f = f;
    for (i = 3; i >= 0; i--)
        appendHex(reg.b[i]);
}

Erc Strpack::unpack(uint64_t* val) {
    uint64_t r=0;
    while (is_digit(peek()) && hasData()) {
        r *= 10;
        r += to_digit(read());
    }
    *val = r;
    return E_OK;
}

Erc Strpack::unpack(uint32_t* val) {
    uint64_t r;
    Erc erc = unpack(&r);
    if (erc) return erc;
    *val = r;
    return E_OK;
}

Erc Strpack::unpack(int32_t* val) {
    uint32_t r;
    Erc erc;
    bool negative = false;
    if (peek() == '-') {
        negative = true;
        read();
    };
    erc = unpack(&r);
    if (erc) return erc;
    if (negative) *val = -r;
    else *val = r;
    return E_OK;
}

Erc Strpack::unpack(float* pf) {
    int i;
    Erc erc;

    union {
        uint8_t b[4];
        uint32_t ui32;
        float f;
    } reg;
    for (i = 3; i >= 0; i--) {
        erc = parseHex(&reg.b[i]);
        if (erc) return erc;
    }
    *pf = reg.f;
    return E_OK;
}

#include <string.h>

Erc Strpack::unpack(bool* pv) {
    char line[10];
    int i=0;
    while (hasData() && i < 6) {
        line[i++] = read();
    }
    line[i] = '\0';
    if (strcmp(line, "true") == 0) {
        *pv = true;
        return E_OK;
    };
    if (strcmp(line, "false") == 0) {
        *pv = false;
        return E_OK;
    };
    return E_INVAL;
}




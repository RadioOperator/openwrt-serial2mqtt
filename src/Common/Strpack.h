/*
* File:   Strpack.h
* Author: lieven2
*
* Created on 23 september 2013, 21:43
*/

#ifndef STRPACK_H
#define	STRPACK_H
#include "Str.h"

class Strpack : public Str
{
public:
    Strpack();
    Strpack(int size);
    Strpack(uint8_t *pb,uint32_t length);
    Strpack(Strpack& orig);
    virtual ~Strpack();
    void pack(const char *s);
    void pack(char *pc, uint32_t length);
    void pack(Bytes* b);
    void pack(Str* str);
    void pack(uint64_t value);
    void pack(uint32_t value);
    void pack(int32_t value);
    void pack(int64_t value);
    void pack(bool b);
    void pack(float f);
    Erc unpack(uint64_t* pv);
    Erc unpack(uint32_t* pv);
    Erc unpack(int32_t* pv);
    Erc unpack(Str* pv);
    Erc unpack(bool* pv);
    Erc unpack(float* pv);
private:

};

#endif	/* STRPACK_H */


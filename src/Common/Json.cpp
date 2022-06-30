/*
 * Json.cpp
 *
 *  Created on: 26-okt.-2014
 *      Author: lieven2
 */

#include "Json.h"

Json::Json(uint32_t size) :
    Str(size)
{
    _breakIndex = 0;
    _break[_breakIndex]=0;
    _tokenIndex = 0;
}
/*
 Json::Json(Str& str) :
 _str(str) {
 _breakIndex = 0;
 }

 Json::Json(Bytes& bytes) :
 _str((Str&) bytes) {
 _breakIndex = 0;
 }

 */

Json::~Json()
{
    //dtor
}
/*

 uint64_t Json::getUint64(int length) {
 uint64_t l = 0;
 while (length) {
 l <<= 8;
 l += read();
 length--;
 }
 return l;
 }
 */

void Json::addComma()
{
    if (_break[_breakIndex] & 0x7F) { // not the first element then prefix with comma
        append(',');
    }
    _break[_breakIndex]++;
}

Json& Json::add(int i)
{
 //   bool get(int64_t& ul);
    addComma();
    append((int64_t)i);
    return *this;
}

Json& Json::add(uint32_t i)
{
//	LOGF(" add %d ",i);
    addComma();
    append((uint64_t) i);
    return *this;
}
#ifdef DOUBLE
Json& Json::add(float fl)
{
    addComma();
    append(fl);
    return *this;
}
Json& Json::add(double d)
{
    addComma();
    append(d);
    return *this;
}
#endif
Json& Json::add(Bytes& b)
{
    addComma();
    append('"');
    b.offset(0);
    while (b.hasData())
        appendHex(b.read());
    append('"');
    return *this;
}
Json& Json::add(Str& str)
{
    addComma();
    append('"');
    str.offset(0);
    while (str.hasData())
        write(str.read());
    append('"');
    return *this;
}
#include <cstring>
Json& Json::add(const char* s)
{
    uint32_t size = strlen(s);
    addComma();
    append('"');
    for (uint32_t i = 0; i < size; i++)
        append(*s++);
    append('"');
    return *this;
}

Json& Json::addKey(const char* s)
{
//	addComma();
    add(s);
    _break[_breakIndex] = 0; // first key is not a comple value yet for comma reasons
    append(':');
    return *this;
}

Json& Json::add(uint64_t i64)
{
    addComma();
    append(i64);
    return *this;
}

Json& Json::clear()
{
    Str::clear();
    _breakIndex = 0;
    _break[_breakIndex] = 0;
    return *this;
}
bool get(int64_t& ul);
Json& Json::add(int64_t i64)
{
    append(i64);
    return *this;
}


Json& Json::addHex(uint64_t ui64)
{
    append("\"0x");
    appendHex((uint32_t)ui64);
    append('"');
    return *this;
}


bool Json::getHex(uint64_t& ui64)
{
    Str str(0);
    mapToken(str);
    if (str.startsWith("0x")) {
        Str part(0);
        for (uint16_t i = 2; i < str.length(); i++) {
            ui64 <<= 4;
            char ch = str.peek();
            if (!Str::ishex(ch))
                return false;
            ui64 += hexToNibble(ch);
        }
        return true;
    }
    return false;
}

Json& Json::add(bool b)
{
    addComma();
    if (b)
        append("true");
    else
        append("false");
    return *this;
}

Json& Json::addMap(int size)
{
    addComma();
    append('{');
    _break[++_breakIndex] = 0;
    return *this;
}
Json& Json::addMap()
{
#include <stdarg.h>
    addComma();
    append('{');
    _break[++_breakIndex] = 0;
    return *this;
}

Json& Json::addArray()
{
    addComma();
    append('[');
    _break[++_breakIndex] = 0x80;
    return *this;
}

Json& Json::addArray(int size)
{
    append('[');
    _break[++_breakIndex] = 0x80;
    return *this;
}

Json& Json::addBreak()
{
    if (_break[_breakIndex] < 0x80)
        append('}');
    else
        append(']');
    _breakIndex--;
    if (_breakIndex == 0)
        _break[_breakIndex] = 0;
    return *this;
}

Json& Json::addNull()
{
    addComma();
    append("null");
    return *this;
}
#include "jsmn.h"
#include <stdlib.h>

bool Json::vscanf(const char *fmt, va_list args)
{
    int64_t ll;

    while (*fmt != '\0') {
//		INFO(" *fmt : %c ", *fmt);
        if (*fmt == '[') {
            if (getArray() == false) {
                return false;
            }
        } else if (*fmt == '{') {
            if (getArray() == false) {
                return false;
            }
        } else if (*fmt == 'i') {
            int32_t* pi = va_arg(args, int32_t*);
            if (get(ll) == false) {
                return false;
            }
            *pi = ll;
//			INFO("ll : %d *pi :  %d ", ll, *pi);
        } else if (*fmt == 'u') {
            uint32_t* pi = va_arg(args, uint32_t*);
            if (get(ll) == false) {
                return false;
            }
            *pi = ll;
        } else if (*fmt == 'f') {
            float* pv = va_arg(args, float*);
            double d;
            if (get(d) == false) {
                return false;
            }
            *pv = d;
        } else if (*fmt == 'd') {
            double* pv = va_arg(args, double*);
            if (get(*pv) == false)
                return false;
        } else if (*fmt == 'S') {
            Str* s = va_arg(args, Str*);
            if (get(*s) == false)
                return false;
        } else if (*fmt == 's') {
            char * s = va_arg(args, char*);
            int length = va_arg(args, int);
            if (get(s, length) == false)
                return false;
        } else if (*fmt == 'b') {
            bool* pv = va_arg(args, bool*);
            if (get(*pv) == false)
                return false;
        } else if (*fmt == 'B') {
            Bytes* pB = va_arg(args, Bytes*);
            if (get(*pB) == false)
                return false;
        } else
            return false;
        ++fmt;
    }

    return true;
}

bool Json::scanf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vscanf(fmt, args);
    va_end(args);
    return true;
}

Erc Json::parse()
{
    jsmn_init(&_parser);
    _tokenIndex = 0;
//	INFO(" str : %s , length : %d , tokens : %x , max_tokens :  %d ", c_str(),
//			length(), _tokens, JSON_MAX_TOKENS);
    _tokenCount = jsmn_parse(&_parser, c_str(), length(), _tokens,
                             JSON_MAX_TOKENS);
    if (_tokenCount < 0)
        return EINVAL;
#ifdef DEBUG_LEVEL
    int i;
    for (i = 0; i < _tokenCount; i++) {
        INFO(" token[%d] {%d,%d}  count : %d : type : %d , parent index :  %d", //
             i,//
             _tokens[i].start,//
             _tokens[i].end,//
             _tokens[i].size,//
             _tokens[i].type,//
             _tokens[i].parent);
    }
#endif
    return E_OK;
}

void Json::mapToken(Str& str)
{
    str.map(data() + _tokens[_tokenIndex].start, _tokens[_tokenIndex].end-_tokens[_tokenIndex].start);
}
#include <stdlib.h>
bool Json::get(int64_t& ll)
{
    double d;
    if ( get(d)) {
        ll=d;
        return true;
    }
    return false;
}

bool Json::get(int32_t& ll)
{
    double d;
    if ( get(d)) {
        ll=d;
        return true;
    }
    return false;
}

bool Json::get(uint32_t& ll)
{
    double d;
    if ( get(d)) {
        ll=d;
        return true;
    }
    return false;
}

bool Json::get(double & d)
{
    if (_tokenIndex >= _tokenCount)
        return false;
    if (_tokens[_tokenIndex].type != JSMN_PRIMITIVE)
        return false;
    Str value(0);
    mapToken(value);
    _tokenIndex++;
    double t = atof(value.c_str());
    d = t;
 //   float f=d;
 //   INFO(" double : %f ",f);
    return true;
}

bool Json::get(bool & bl)
{
    if (_tokenIndex >= _tokenCount)
        return false;
    if (_tokens[_tokenIndex].type != JSMN_PRIMITIVE)
        return false;
    Str value(0);
    mapToken(value);
    _tokenIndex++;
    if (strncmp(value.c_str(), "true",
                _tokens[_tokenIndex].end - _tokens[_tokenIndex].start) == 0) {
        bl = true;
        return true;
    } else if (strncmp(value.c_str(), "false",
                       _tokens[_tokenIndex].end - _tokens[_tokenIndex].start) == 0) {
        bl = false;
        return true;
    }
    return false;
}

bool Json::get(Str& str)
{
    ;
    if (_tokenIndex >= _tokenCount)
        return false;
    if (_tokens[_tokenIndex].type != JSMN_STRING && _tokens[_tokenIndex].type != JSMN_PRIMITIVE )
        return false;
//	const char* s = c_str() + _tokens[_tokenIndex].start;
    /*if (s[_tokens[_tokenIndex].start] == '"'
     && s[_tokens[_tokenIndex].end] == '"')*/{
        str.clear();
        for (int i = _tokens[_tokenIndex].start; i < _tokens[_tokenIndex].end;
             i++) {
            str.write(peek(i));
        }
    }
//	INFO("str:%s",str.c_str());
    _tokenIndex++;
    return true;
}

bool Json::get(Bytes& bytes)
{
    if (_tokenIndex >= _tokenCount)
        return false;
    if (_tokens[_tokenIndex].type != JSMN_STRING)
        return false;
//   const char* s = c_str() + _tokens[_tokenIndex].start;
//   if (s[_tokens[_tokenIndex].start] == '"'
//           && s[_tokens[_tokenIndex].end] == '"')
    {
        bytes.clear();
        for (int i = _tokens[_tokenIndex].start; i < _tokens[_tokenIndex].end;
             i+=2) {
            uint8_t byt = (Str::hexToNibble(peek(i))<<4) + Str::hexToNibble(peek(i+1));
            bytes.write(byt);
        }
    }
    _tokenIndex++;
    return true;
}

bool Json::get(char* sDst, int length)
{
    if (_tokenIndex >= _tokenCount)
        return false;
    if (_tokens[_tokenIndex].type != JSMN_STRING)
        return false;
    const char* s = c_str() + _tokens[_tokenIndex].start;
    if (s[_tokens[_tokenIndex].start] == '"'
        && s[_tokens[_tokenIndex].end] == '"') {
        for (int i = _tokens[_tokenIndex].start;
             (i < _tokens[_tokenIndex].end) && (i < length); i++) {
            sDst[i] = peek(i);
        }
    }
    _tokenIndex++;
    return true;
}

bool Json::getArray()
{
    if (_tokenIndex >= _tokenCount)
        return false;
    if (_tokens[_tokenIndex].type != JSMN_ARRAY)
        return false;
    _tokenIndex++;
    return true;
}

bool Json::getMap()
{
    if (_tokenIndex >= _tokenCount)
        return false;
    if (_tokens[_tokenIndex].type != JSMN_OBJECT)
        return false;
    _tokenIndex++;
    return true;
}
//________________________________________________________________________________
//
Json::Type Json::getType()
{

    if (_tokens[_tokenIndex].type == JSMN_OBJECT) {
        return JSON_OBJECT;
    } else if (_tokens[_tokenIndex].type == JSMN_ARRAY) {
        return JSON_ARRAY;
    } else if (_tokens[_tokenIndex].type == JSMN_STRING) {
        return JSON_STRING;
    } else if ( _tokens[_tokenIndex].type == JSMN_PRIMITIVE ) {
        Str value(0);
        mapToken(value);
        if ( value.equals("true") || value.equals("false")) {
            return JSON_BOOL;
        } else if ( value.equals("null")) {
            return JSON_NULL;
        } else if ( value.isNumber() ) {
            return JSON_NUMBER;
        }
    } ;
    return JSON_UNKNOWN;
}



void Json::rewind()
{
    _tokenIndex = 0;
}

bool Json::next() {
    if ( _tokenIndex < _tokenCount ) {
        _tokenIndex++;
        return true;
    } else {
        return false;
    }
}

bool Json::findKey(const char* key)
{
    if (_tokens[_tokenIndex].type != JSMN_OBJECT)
        return false;
    uint32_t strLength = strlen(key);
    for (int i = 0; i < _tokenCount; i++) {
        uint32_t tokenLength = _tokens[i].end - _tokens[i].start;
//		INFO(" %d %d -> %d : %d %s ",_tokenIndex,i,strLength,tokenLength,data() + _tokens[i].start);
        if ((_tokens[i].parent == _tokenIndex) && (strLength == tokenLength)
            && (strncmp(key, (const char*) (data() + _tokens[i].start),
                        tokenLength) == 0)) {
//			int idx = i;
            if ((i + 1) < _tokenCount && _tokens[i + 1].parent == i) {
                _tokenIndex = i + 1;
                return true;
            }
        }
    }
    return false;
}

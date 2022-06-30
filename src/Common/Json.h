/*
 * Json.h
 *
 *  Created on: 26-okt.-2014
 *      Author: lieven2
 */

#ifndef JSON_H_
#define JSON_H_

#include "Str.h"
#include "jsmn.h"
#include <stdarg.h>
// #define DOUBLE
#define JSON_MAX_TOKENS 30
#define DOUBLE

class Json: public Str
{

public:
    typedef enum {
        JSON_UNKNOWN,
        JSON_BOOL,
        JSON_NUMBER,
        JSON_STRING,
        JSON_NULL,
        JSON_ARRAY,
        JSON_OBJECT
    } Type;
//	Json(Str& str);
//	Json(Bytes& bytes);
    Json(uint32_t size);
    virtual ~Json();
    Json& clear();

    Json& add(int i);
    Json& add(bool b);
    Json& add(uint32_t i);
#ifdef DOUBLE
    Json& add(float f);
    Json& add(double d);
#endif
    Json& add(Bytes& b);
    Json& add(Str& str);
    Json& add(char const* s);
    Json& add(uint64_t i64);
    Json& add(int64_t i64);
    Json& addHex(uint64_t ui64);
    Json& addMap(int size);
    Json& addMap();
    Json& addArray(int size);
    Json& addArray();
    Json& addKey(const char* s);
    Json& addTag(int nr);
    Json& addBreak();
    Json& addNull();

    Erc parse();
    void rewind();
    bool next();

    bool get(double& d);
    bool get(bool& bl);
    bool get(Str& str);
    bool get(Bytes& str);
    bool get(int64_t& ul);
    bool get(int32_t& ul);
    bool getHex(uint64_t& ul);
    bool get(uint32_t& ul);
    bool get(char* s, int length);
    bool getArray();
    bool getMap();
    bool findKey(const char* key);
    Type getType();
    bool isObject() {
        return (_tokens[_tokenIndex].type == JSMN_OBJECT);
    }
    bool isArray() {
        return (_tokens[_tokenIndex].type == JSMN_ARRAY);
    }
    bool isPrimitive() {
        return (_tokens[_tokenIndex].type == JSMN_PRIMITIVE);
    }
    bool isString() {
        return (_tokens[_tokenIndex].type == JSMN_STRING);
    }

    bool scanf(const char* fmt, ...);
    bool vscanf(const char *fmt, va_list args);
//	Erc readToken(PackType& type,Variant& variant);
    Erc toString(Str& str);
    void mapToken(Str& str);
    void addComma();

protected:
private:
//	void addToken(PackType type, uint64_t data);
    void addHeader(uint8_t major, uint8_t minor);
    uint64_t getUint64(int length);


//	PackType tokenToString(Str& str);
    uint8_t _break[JSON_MAX_TOKENS]; // nested objects within object index, highest bit==on -> array, else map
    int _breakIndex;
    jsmn_parser _parser;
    jsmntok_t _tokens[JSON_MAX_TOKENS];
    int _tokenCount;
    int _tokenIndex;
};

#endif /* JSON_H_ */

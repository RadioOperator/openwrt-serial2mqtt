#ifndef CBOR_H
#define CBOR_H
#include "Bytes.h"
//#include "Packer.h"
#include "Str.h"
#include "Sys.h"
#include "errno.h"
#include <stdarg.h>
#include <string>

class Cbor : public Bytes {
  public:
    typedef union CborVariant {
        uint64_t _uint64;
        int64_t _int64;
        double _double;
        float _float;
        bool _bool;
        int _length;
        uint8_t _bytes[8];
    } CborVariant;
    typedef enum {
        P_PINT = 0,
        P_NINT,
        P_BYTES,
        P_STRING,
        P_ARRAY,
        P_MAP,
        P_TAG,
        P_SPECIAL = 7, // major types
        P_BOOL,
        P_FLOAT,
        P_DOUBLE,
        P_BREAK,
        P_NILL,
        P_ERROR
    } // minor additional types
    PackType;
    Cbor();
    Cbor(uint32_t size);
    Cbor(uint8_t* data, uint32_t length);
    ~Cbor();

    Cbor& operator<<(uint32_t i) { return add(i); }
    Cbor& add(int i);
    Cbor& operator<<(int i);
    Cbor& operator<<(const char* s);
    Cbor& operator=(const char* s);
    Cbor& operator<<(uint64_t l);
    Cbor& add(uint16_t i);
    Cbor& add(uint32_t i);
    Cbor& add(float f);
    Cbor& add(double d);
    Cbor& add(Bytes& b);
    Cbor& add(uint8_t* data, int length);
    Cbor& add(Str& str);
    Cbor& add(std::string& s);
    Cbor& add(const char* s);
    Cbor& add(uint64_t i64);
    Cbor& add(int64_t i64);
    Cbor& add(bool b);
    Cbor& addMap(int size);
    Cbor& addArray(int size);
    Cbor& addTag(int nr);
    Cbor& addBreak();
    Cbor& addNull();
    Cbor& addKey(uint32_t idx);
    bool addf(const char* fmt, ...);
    bool vaddf(const char* fmt, va_list args);
    Cbor& putf(const char* fmt, ...);
    bool scanf(const char* fmt, ...);
    bool vscanf(const char* fmt, va_list args);
    void sprintf(Str& s);

    bool get(const char*& s) { return true; }; // to satisfy template Property
    bool get(bool& bl);
    bool get(uint16_t& i);
    bool get(uint32_t& i);
    bool get(uint64_t& l);
    bool get(float& f);
    bool get(double& d);
    bool get(int32_t& i);
    bool get(char* s, uint32_t length);
    bool get(Bytes& bytes);
    bool get(Str& str);
    bool get(std::string& s);
    bool gotoKey(uint32_t idx);
    bool getMapped(Bytes& bytes);
    template <typename T> Cbor& addKeyValue(uint32_t key, T value) {
        addKey(key);
        add(value);
        return *this;
    }

    template <typename T> bool getKeyValue(uint32_t key, T& value) {
        if (gotoKey(key) && get(value))
            return true;
        return false;
    }

    bool mapKeyValue(uint32_t key, Bytes& value) {
        if (gotoKey(key) && getMapped(value))
            return true;
        return false;
    }

    Erc readToken(PackType& type, CborVariant& variant);
    Erc peekToken(PackType& type);
    Erc toString(Str& str);
    Bytes& bytes() { return *this; }
    bool skipToken();
    PackType tokenToString(Str& str);

  protected:
  private:
    void addToken(PackType type, uint64_t data);

    void addHeader(uint8_t major, uint8_t minor);
    uint64_t getUint64(int length);
};

#endif // CBOR_H

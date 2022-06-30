#include <Sys.h>
#include <Xdr.h>
#include <assert.h>
#include <cstring>
#include <errno.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <unordered_map>
// extern std::string& string_format(std::string& str, const char* fmt, ...) ;

/*
design decisions :
    - speed over size : as the purpose is to have a fast serialization
    mechanism to in-memory for inter actor communication. It's preferred
    in the (de-)serialization to spend no time in decision trees
    - the smallest unity of store/retrieval is a 32bit value, aligned on
    32 bit addresses -> is the fastest and unitary on most processors
    - most popular types should be without decision trees
    - the principles of protobuf ( tag encoding ) and XDR ( 32 bit units )
    are re-used.
    - tag-id's are deduced from the string representation of the fields
    based on a FNV1 hash of the string.
    - the length is 13 bit , expressed in nbr of bytes , the nbr of 32bit
    words is a shift-right of 2 bits. 8KB max. it indicates the real length to
enable the fast skip to next element.
    - supported types : UINT,INT,FLOAT,BYTES,BOOL,OBJECT,SPECIAL
        - BYTES and STRING are considered the same
        - OBJECT is a sub-message
        - SPECIAL : for future extensions, using LENGTH field

[32:[3:TYPE][13:LENGTH][16:TAG]][32x:data] =

    INT - 0,1,2,4,8 => length==0
    UINT - 1,2,4,8
    BYTES - 0-N
    FLOAT - 4,8
    OBJECT - 4 x N
    BOOL - 0,1 => false,true
    SPECIAL - 0-N : special types  ==> future use
        RESERVED ==> future use
*/

#define BYTES_TO_WORDS(lll) (lll & 0x3) ? (lll >> 2) + 1 : (lll >> 2)

const char* Tag::typeStrings[] = {"BOOL",  "INT",    "UINT",  "BYTES",
                                  "FLOAT", "OBJECT", "XDR_1", "RESERVED"};

Tag::Tag(uint32_t i) { ui32 = i; }
Tag::Tag(Xdr::Type t, uint16_t l, Uid ui) {
    type = t;
    length = l;
    uid = ui.id();
}

bool Tag::equivalentType(Tag& src) {
    if (this->type == src.type)
        return true;
    if (this->type == Xdr::UINT && src.type == Xdr::INT)
        return true;
    if (this->type == Xdr::INT && src.type == Xdr::UINT)
        return true;
    return false;
}

extern const char* uidToString(uid_type);
void Tag::operator=(uint32_t i) { ui32 = i; }

std::string Tag::toString() {
    std::string out;
    out.reserve(100);
    string_format(out, "'%s'[%s:%d]", Uid::label(uid), typeStrings[type],
                  length);
    return out;
}

Xdr::Xdr(uint32_t size) {

    if (size > 100)
        WARN(" huge XDR %d ", size);
    _start = new uint32_t[size];
    _readIdx = 0;
    _capacity = size;
    _writeIdx = 0;
}

Xdr::Xdr(Xdr& src) {
    if (src._writeIdx > 200)
        WARN(" huge XDR ");

    _start = new uint32_t[src._writeIdx];
    _readIdx = src._readIdx;
    _capacity = src._writeIdx;
    _writeIdx = src._writeIdx;
    for (uint32_t i = 0; i < _writeIdx; i++) {
        *(_start + i) = *(src._start + i);
    }
}

Xdr& Xdr::operator=(const Xdr& src) {
    if (this != &src) {
        clear();
        if (_capacity < src._writeIdx)
            resize(src._writeIdx);
        uint32_t max = src._writeIdx;
        //	memcpy(_start,src._start,src._writeIdx<<2);
        for (uint32_t i = 0; i < max; i++) {
            _start[i] = src._start[i];
        }
        _writeIdx = max;
        _readIdx = 0;
    }
    return *this;
}

Xdr::~Xdr() { delete[] _start; }

void Xdr::clear() {
    _writeIdx = 0;
    _readIdx = 0;
}

uint32_t Xdr::size() const { return _writeIdx; }
uint32_t Xdr::capacity() const { return _capacity; }

void Xdr::resize(uint32_t newSize) {
    //	INFO("resize %X : [%d]",this,newSize);

    uint32_t* _newStart = new uint32_t[newSize];
    //	memcpy(_newStart,_start,_writeIdx<<2);
    for (uint32_t i = 0; i < _writeIdx; i++) {
        *(_newStart + i) = *(_start + i);
    }
    delete[] _start;
    _start = _newStart;
    _capacity = newSize;
}

bool Xdr::hasSpace(uint32_t size) {
    uint32_t newCapacity = _capacity;
    while (size > (newCapacity - _writeIdx)) {
        newCapacity *= 2;
    }
    if (_capacity != newCapacity)
        resize(newCapacity);
    return true;
    //	return (size <= (_capacity - _writeIdx));
}

bool Xdr::hasData() const { return (_readIdx < _writeIdx); }

uint32_t Xdr::peek() const { return *(_start + _readIdx); }

uint32_t Xdr::peek(uint32_t offset) const {
    if (offset < _writeIdx)
        return *(_start + offset);
    return 0;
}

void Xdr::poke(uint32_t offset, uint32_t value) {
    if (offset < _writeIdx)
        *(_start + offset) = value;
}

bool Xdr::readInc(uint32_t delta) {
    if (_readIdx + delta > _writeIdx)
        return false;
    _readIdx += delta;
    return true;
}

bool Xdr::writeInc(uint32_t delta) {
    _writeIdx += delta;
    return true;
}

bool Xdr::read(uint32_t& i) {
    i = peek();
    return readInc(1);
}

bool Xdr::read(uint32_t* ui, uint32_t cnt) {
    for (uint32_t i = 0; i < cnt; i++) {
        if (read(*(ui + i)))
            return false;
    }
    return readInc(1);
}

bool Xdr::write(uint32_t i) {
    if (_writeIdx == _capacity)
        resize(2 * _capacity);
    *(_start + _writeIdx) = i;
    _writeIdx++;
    return true;
}

inline bool Xdr::write(Tag tag) { return write(tag.ui32); }
/*
#define RETURN_ERR(xxx)                                                        \
        { \
                int erc = 0;                                                  \
                if ((erc = xxx) != 0) \
                        return erc; \
        }*/

bool Xdr::write(uint8_t* pb, uint32_t count) {
    uint32_t ui32;
    for (uint32_t i = 0; i < count; i += 4) {
        uint32_t delta = (count - i) > 4 ? 4 : (count - i);
        memcpy(&ui32, pb + i, delta);
        if (!write(ui32))
            return false;
    }
    return true;
}

bool Xdr::write(uint32_t* pb, uint32_t count) {
    for (uint32_t i = 0; i < count; i += 1) {
        write(*(pb + i));
    }
    return true;
}

bool Xdr::add(Xdr& xdr) { return write(xdr._start, xdr._writeIdx); }

bool Xdr::add(Uid key, Xdr& xdr) {
    write(Tag(OBJECT, xdr.size() * 4, key));
    return add(xdr);
}

bool Xdr::add(Uid key, bool b) {
    write(Tag(BOOL, 1, key));
    return write((uint32_t)b);
}

bool Xdr::add(Uid key, uint16_t v) {
    write(Tag(UINT, 4, key));
    write(v);
    return true;
}

bool Xdr::add(Uid key, int32_t v) {
    write(Tag(INT, 4, key));
    return write((uint32_t)v);
}

bool Xdr::add(Uid key, uint32_t v) {
    write(Tag(UINT, 4, key));
    return write(v);
}

bool Xdr::add(Uid key, uint64_t v) {
    write(Tag(UINT, 8, key));
    return write((uint32_t*)&v, 2);
}

bool Xdr::add(Uid key, int64_t v) {
    write(Tag(INT, 8, key));
    return write((uint32_t*)&v, 2);
}

bool Xdr::add(Uid key, double d) {
    //   printf("%s:%d \n",__FILE__,__LINE__);
    Tag tag(FLOAT, 8, key.id());
    write(Tag(FLOAT, 8, key.id()).ui32);

    union {
        double dd;
        uint32_t ww[2];
    };
    dd = d;
    write(ww[0]);
    write(ww[1]);
    return true;
}

bool Xdr::add(Uid key, const char* s) {
    return add(key, (uint8_t*)s, strlen(s));
}

bool Xdr::add(Uid key, std::string& v) {
    return add(key, (uint8_t*)v.data(), v.size());
}

bool Xdr::add(Uid key, uint8_t* bytes, uint32_t length) {
    if (write(Tag(BYTES, length, key)) && write((uint8_t*)bytes, length))
        return true;
    return false;
}

bool Xdr::findNext(Tag& tag) {
    Tag t(0);

    while (read(t.ui32)) {
        if (t.uid == tag.uid && tag.equivalentType(t)) {
            tag.ui32 = t.ui32;
            return true;
        }

        readInc(BYTES_TO_WORDS(t.length));
    }

    return false;
}

bool Xdr::getNext(Uid uid, bool& b) {
    Tag tag = Tag(BOOL, 0, uid);

    if (findNext(tag)) {
        uint32_t ui32;
        bool erc = read(ui32);
        b = ui32;
        return erc;
    }
    return false;
}

bool Xdr::getNext(Uid uid, uint16_t& i) {
    Tag tag = Tag(UINT, 0, uid);

    if (findNext(tag)) {
        uint32_t ui;
        if (read(ui))
            return false;
        i = ui;
        return true;
    }
    return false;
}

bool Xdr::getNext(Uid uid, uint32_t& i) {
    Tag tag = Tag(UINT, 0, uid);

    if (findNext(tag)) {
        return read(i);
    }
    return false;
}

bool Xdr::getNext(Uid uid, uint64_t& i) {
    Tag tag = Tag(UINT, 0, uid);
    if (findNext(tag)) {
        union {
            uint64_t ui64;
            uint32_t ui32[2];
        };
        if (tag.length == 4) {
            int erc = read(ui32[0]);
            i = (int32_t)ui32[0];
            return erc;
        } else if (tag.length == 8) {
            int erc = read(ui32[0]);
            erc = read(ui32[1]);
            i = ui64;
            return erc;
        } else {
            WARN(" invalid tag length ");
            return false;
        }
    }
    return false;
}

bool Xdr::getNext(Uid uid, int32_t& i) {
    Tag tag = Tag(INT, 0, uid);

    if (findNext(tag)) {
        uint32_t ui;
        int erc = read(ui);
        i = (int32_t)ui;
        return erc;
    }
    return false;
}

bool Xdr::getNext(Uid uid, int64_t& i) {
    Tag tag = Tag(INT, 0, uid);
    if (findNext(tag)) {
        union {
            int64_t i64;
            uint32_t ui32[2];
        };
        if (tag.length == 4) {
            int erc = read(ui32[0]);
            i = (int32_t)ui32[0];
            return erc;
        } else if (tag.length == 8) {
            int erc = read(ui32[0]);
            erc = read(ui32[1]);
            i = i64;
            return erc;
        } else {
            WARN(" invalid tag length ");
            return false;
        }
    }
    return false;
}

bool Xdr::getNext(Uid uid, double& d) {
    Tag tag = Tag(FLOAT, 0, uid);
    if (findNext(tag)) {
        union {
            double dd;
            float ff;
            uint32_t ww[2];
        };
        if (tag.length == 4) {
            read(ww[0]);
            d = ff;
        } else {
            read(ww[0]);
            read(ww[1]);
            d = dd;
        }
        return true;
    } else {
        return false;
    }
}

bool Xdr::skip() {
    Tag tag(peek());
    return readInc(BYTES_TO_WORDS(tag.length) + 1);
}

bool Xdr::getNext(Uid key, Xdr& xdr) {
    Tag tag(OBJECT, 0, key);
    if (findNext(tag)) {
        union {
            uint32_t w;
            char ch[4];
        };
        xdr.resize(tag.length);
        xdr.clear();

        for (int i = 0; i < tag.length; i += 4) {
//            int delta = (tag.length - i) > 4 ? 4 : (tag.length - i);

            if (read(w)) {
                xdr.write(w);
            }
        }
        return true;
    } else {
        return false;
    }
}

bool Xdr::getNext(Uid key, std::string& s) {
    Tag tag(BYTES, 0, key);

    if (findNext(tag)) {
        union {
            uint32_t w;
            char ch[4];
        };
        s.resize(tag.length);
        s.clear();

        for (int i = 0; i < tag.length; i += 4) {
            int delta = (tag.length - i) > 4 ? 4 : (tag.length - i);

            if (read(w)) {
                s.append(ch, delta);
            }
        }
        return true;
    } else {
        return false;
    }
}

std::string Xdr::toString() {
    std::string output;
    std::string s;

    Tag tag(0);
    rewind();
    output += string_format(s, "[%X] ", this);
    while (hasData()) {
        uint32_t ui32 = peek();
        tag = Tag(ui32);
        s = tag.toString();
        output += s;
        if (tag.type == Xdr::UINT) {
            uint64_t ui64;
            getNext(tag.uid, ui64);
            output += string_format(s, "=%ld,", ui64);
        } else if (tag.type == Xdr::INT) {
            int64_t i64;
            getNext(tag.uid, i64);
            output += string_format(s, "=%ld,", i64);
        } else if (tag.type == Xdr::FLOAT) {
            double d = 0.0;
            getNext(tag.uid, d);
            output += string_format(s, "=%f,", d);
        } else if (tag.type == Xdr::BYTES) {
            std::string s1;
            getNext(tag.uid, s1);
            output += "='";
            output += s1;
            output += "',";
        } else if (tag.type == Xdr::BOOL) {
            bool b = false;
            getNext(tag.uid, b);
            output += string_format(s, "=%d,", b);
        } else if ( tag.type == Xdr::OBJECT ) {
			Xdr xdr(20);
			getNext(tag.uid,xdr);
			output+= string_format(s,"={%s}",xdr.toString().c_str());
		}
    }
    return output;
}

//#define UID(xxx) H(xxx)

void XdrTester(uint32_t MAX) {
    Xdr xdr(12);
    std::string HW = "hello world";
    Tag t(Xdr::FLOAT, 2, "Hello");
    LOG(" Start Xdrtester .... ");
    LOG("Tag : %s", t.toString().c_str());
    LOG("sizeof(Tag)=%u", (unsigned int)sizeof(Tag));
    LOG("sizeof(Type)=%u", (unsigned int)sizeof(Xdr::Type));

    const char* test1 = "{\"$src\":\"master/brain\",\"$dst\":\"ESP82-10027/"
                        "System\",\"$cls\":\"Properties\"}";

    double d;

    Uid::add("temp");
    Uid::add("temp");
    Uid::add("anInt32");
    Uid::add("aString");
    Uid::add("sStdString");
    Uid::add("booleke");
    Uid::add("test1");

    uint64_t start = Sys::millis();

    for (uint32_t loop = 0; loop < MAX; loop++) {
        xdr.clear();
        xdr.add(UID("temp"), 1.23);
        xdr.add(UID("anInt32"),(int32_t) -15);
        xdr.add(UID("aString"),
                "The quick brown fox jumps over the lazy dog !");
        xdr.add(UID("booleke"), false);
        xdr.add(UID("sStdString"), HW);
        xdr.add(UID("test1"), test1);

        assert(xdr.get(UID("temp"), d));
        assert(d == 1.23);
        int32_t ii;
        assert(xdr.get(UID("anInt32"), ii));
        assert(ii == -15);
        std::string ss;
        ss.reserve(100);
        assert(xdr.get(UID("aString"), ss));
        assert(ss.compare("The quick brown fox jumps over the lazy dog !") ==
               0);
        assert(xdr.get(UID("sStdString"), ss));
        assert(ss.compare(HW) == 0);
        assert(xdr.get(UID("test1"), ss));
        assert(ss.compare(test1));
        bool bb;
        assert(xdr.get(UID("booleke"), bb));
        assert(bb == false);
    }
    LOG(" xdr = %s ", xdr.toString().c_str());

    Xdr xdr2 = xdr;
    assert(xdr2.get(UID("temp"), d));
    assert(d == 1.23);
    int32_t ii;
    assert(xdr2.get(UID("anInt32"), ii));
    assert(ii == -15);
    std::string ss;
    ss.reserve(100);
    assert(xdr2.get(UID("aString"), ss));
    assert(ss.compare("The quick brown fox jumps over the lazy dog !") == 0);
    assert(xdr2.get(UID("sStdString"), ss));
    assert(ss.compare(HW) == 0);
    assert(xdr2.get(UID("test1"), ss));
    assert(ss.compare(test1) == 0);
    bool bb;
    assert(xdr2.get(UID("booleke"), bb));
    assert(bb == false);

    uint32_t delta = Sys::millis() - start;
    LOG(" %d took %u msec, %f msg/sec , double : %f", (unsigned int)MAX,(unsigned int)delta,
        (MAX * 1000.0) / delta, d);
    std::string s = xdr.toString();
}

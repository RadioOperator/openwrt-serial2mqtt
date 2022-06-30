#ifndef XDR_H_
#define XDR_H_
#include <Log.h>
#include <Sys.h>
#include <Uid.h>
#include <assert.h>
#include <cstring>
#include <errno.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <unordered_map>


class Tag;

class Xdr { /*: public Stream<uint32_t> */
		uint32_t _writeIdx;
		uint32_t _readIdx;
		uint32_t _capacity;
		uint32_t* _start;

	public:
		typedef enum {
			BOOL,
			INT,
			UINT,
			BYTES,
			FLOAT,
			OBJECT,
			XDR_1,
			RESERVED
		} Type;
		static const char* typeStrings[Type::XDR_1 + 1];

		uint32_t& operator[](uint32_t idx) { return _start[idx]; };

		Xdr(uint32_t size);
		Xdr(Xdr& src);
		~Xdr();
		inline void rewind() { _readIdx = 0; };
		inline void end();
		void clear();
		uint32_t peek(uint32_t offset) const;
		uint32_t peek() const;

		bool skip();
		bool writeInc(uint32_t);
		bool readInc(uint32_t);
		inline bool hasSpace(uint32_t);
		bool read(uint32_t& i);
		bool read(uint32_t* pi, uint32_t cnt);
		bool write(uint32_t i);
		bool write(uint32_t* pi, uint32_t i);
		bool write(uint8_t* pi, uint32_t i);
		bool write(Tag tag);
		bool add(Uid key, int32_t v);
		bool add(Uid key, bool b);
		bool add(Uid key, double d);
		bool add(Uid key, uint16_t v);
		bool add(Uid key, uint32_t v);
		bool add(Uid key, uint64_t v);
		bool add(Uid key, int64_t v);
		bool add(Uid key, uint8_t* bytes, uint32_t length);
		bool add(Uid key, std::string& v);
		bool add(Uid key, const char* s);
		bool add(Uid key, Xdr& xdr);
		bool add(Xdr& xdr);
		template <typename T> Xdr& operator()(Uid key, T v) {
			add(key, v);
			return *this;
		};

		bool getNext(Uid key, bool& b);
		bool getNext(Uid key, double& i);
		bool getNext(Uid key, int32_t& i);
		bool getNext(Uid key, uint16_t& i);
		bool getNext(Uid key, uint32_t& i);
		bool getNext(Uid key, uint64_t& i);
		bool getNext(Uid key, int64_t& i);
		bool getNext(Uid key, std::string& s);
		bool getNext(Uid key, uint8_t* bytes, uint32_t& size);
		bool getNext(Uid key, Xdr& xdr);
		template <typename T> bool get(Uid key, T& v) {
			rewind();
			return getNext(key, v);
		};

		int vscanf(const char* fmt, ...);
		bool hasData() const;

		std::string toString();
		bool findNext(Tag& t);
		Xdr& operator=(const Xdr&);

		uint32_t size() const;
		uint32_t capacity() const;
		uint32_t offset() { return _readIdx;}
		void resize(uint32_t newSize);
		void poke(uint32_t offset, uint32_t value);
};

class Tag {
		static const char* typeStrings[Xdr::RESERVED + 1];

	public:
		union {
			struct {
				Xdr::Type type : 3;
				uint32_t length : 13;
				uint16_t uid : 16;
			};
			uint32_t ui32;
		};

		Tag(uint32_t i);
		Tag(Xdr::Type t, uint16_t l, Uid ui);
		void operator=(uint32_t i);
		std::string toString();
		bool equivalentType(Tag& );
};

#endif

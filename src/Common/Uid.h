#ifndef UID_H
#define UID_H
#include <stdint.h>
#include <unordered_map>

#define __FLE__                                                                \
	(__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1   \
	 : __FILE__)
#define LOG(fmt, ...)                                                         \
	{ printf("%10s:%4u | ",__FLE__, (unsigned int)__LINE__);printf(fmt, ##__VA_ARGS__);printf("\n") ;}

typedef uint16_t uid_type;
#define UID_LENGTH 16

#if UID_LENGTH == 16
#define FNV_PRIME 16777619
#define FNV_OFFSET 2166136261
#define FNV_MASK 0xFFFF
#endif
constexpr uint32_t fnv1(uint32_t h, const char* s) {
	return (*s == 0) ? h : fnv1((h * FNV_PRIME) ^ static_cast<uint32_t>(*s), s + 1);
}

constexpr uint16_t H(const char* s) {
	//    uint32_t  h = fnv1(FNV_OFFSET, s) ;
	return (fnv1(FNV_OFFSET, s) & FNV_MASK);
}

#define UID(x) std::integral_constant<uint16_t, H(x)>::value


class Uid {
		static std::unordered_map<uint16_t, void*>* _uids;
		uid_type _id;

	public:
		Uid(uid_type uid,const char* label);
		Uid(const char* label);
		Uid(uid_type id) ;
//		Uid(void*);
		Uid();
//		Uid(const Uid&);
		inline uid_type id() { return _id;};
		void operator=(uid_type a);
		bool operator==(Uid b) ;

		const char* label() ;

		static uid_type hash(void*);
		static uid_type add(void* object);
		
		static uid_type hash(const char* label);	// just calc hash
		static uid_type add(const char* label);	// extend dictionary
		static const char* label(uid_type id);
		static std::unordered_map<uint16_t, void*>* uids();

};



#endif // UID_H

/*

typedef uint16_t uid_type;
#define UID_LENGTH 16
#define UID_MAX 200

#if UID_LENGTH == 16
#define FNV_PRIME 16777619
#define FNV_OFFSET 2166136261
#define FNV_MASK 0xFFFF
#endif

#if UID_LENGTH == 32
#define FNV_PRIME 16777619
#define FNV_OFFSET 2166136261
#define FNV_MASK 0xFFFFFFFFu
#endif

#if UID_LENGTH == 64
#define FNV_PRIME 1099511628211ull
#define FNV_OFFSET 14695981039346656037ull
#endif

#define STEP printf("%s:%d\n", __FILE__, __LINE__)

constexpr uint32_t fnv1(uint32_t h, const char* s) {
	return (*s == 0) ? h
	       : fnv1((h * FNV_PRIME) ^ static_cast<uint32_t>(*s), s + 1);
}

constexpr uint16_t H(const char* s) {
	//    uint32_t  h = fnv1(FNV_OFFSET, s) ;
	return (fnv1(FNV_OFFSET, s) & FNV_MASK);
}
class Uid {
		static unordered_map<uint16_t, void*>* _uids;
		uid_type _id;

	public:
		Uid(const char* label);
		Uid(uid_type id);
		Uid(void*);
		Uid() { _id = 0; }
		void operator=(uid_type a) { _id = a; }
		bool operator==(Uid b) { return _id == b._id; }

		static uid_type hash(const char* label);
		static uid_type add(const char* label);
		static const char* label(uid_type id);
		const char* label();

		static uid_type hash(void*);
		static uid_type add(void* object);
		static void* object(uid_type id);
		void* object();

		static unordered_map<uint16_t, void*>* uids();
		uid_type id() { return _id; }
};
*/

#include "Uid.h"

#include <cstring>

//#define UID(xxxx) Uid(xxxx)

std::unordered_map<uint16_t, void*>* Uid::_uids=0;

Uid::Uid(const char* label) :  _id(H(label)) {
	if (uids()->find(_id) == uids()->end()) {
		char* l = new char[strlen(label) + 1]();
		strcpy(l, label);
		uids()->emplace(_id, (void*)l);
	}
}

Uid::Uid(uid_type id,const char* label) :  _id(id) {
	if (uids()->find(_id) == uids()->end()) {
		char* l = new char[strlen(label) + 1]();
		strcpy(l, label);
		uids()->emplace(_id, (void*)l);
	}
}

Uid::Uid(uid_type id) :_id(id) {  }

// Uid::Uid(const Uid& src) { _id=src._id; };

uid_type Uid::add(const char* label) {
	uid_type h;

	h = hash(label);
	if (uids()->find(h) == uids()->end()) {
		char* l = new char[strlen(label) + 1]();
		strcpy(l, label);
		uids()->emplace(h, (void*)l);
	}
	return h;
}

const char* Uid::label() { return Uid::label(_id); }

Uid::Uid() :_id(0) {}

void Uid::operator=(const uid_type a) { _id=a; }

bool Uid::operator==(Uid b) { return _id == b._id;}

std::unordered_map<uid_type, void*>* Uid::uids() {
	if (_uids == 0) {
		_uids = new std::unordered_map<uid_type, void*>();
	}
	return _uids;
}

const char* Uid::label(uid_type id) {
	std::unordered_map<uid_type, void*>::const_iterator p = uids()->find(id);
	if (p == uids()->end())
		return 0;
	return (const char*)(p->second);
}

#define PTR_BYTES sizeof(void*)
#define UID_BYTES sizeof(uid_type)
/*
uid_type Uid::hash(void* pv) {
	uid_type h;
	union {
		void* ptr;
		uid_type uids[PTR_BYTES / UID_BYTES];
	};
	ptr = pv;
	h = 0;
	for (uint32_t i = 0; i < sizeof(uids); i++) {
		h ^= uids[i];
	}
	return h;
}*/

uid_type Uid::hash(const char* s) { return H(s); }

/*


Uid::Uid(const char* label) { _id = add(label); }

Uid::Uid(uid_type id) { _id = id; }

Uid::Uid(void* pv) { _id = add(pv); }



uid_type Uid::add(const char* label) {
	uid_type h;

	h = hash(label);
	if (uids()->find(h) == uids()->end()) {
		char* l = new char[strlen(label) + 1]();
		strcpy(l, label);
		uids()->emplace(h, (void*)l);
	}
	return h;
}


const char* Uid::label() { return Uid::label(_id); }

#define PTR_BYTES sizeof(void*)
#define UID_BYTES sizeof(uid_type)



uid_type Uid::add(void* pv) {
	uid_type h = hash(pv);
	if (object(h) == 0)
		uids()->emplace(h, pv);
	return h;
}

void* Uid::object(uid_type d) {
	std::unordered_map<uid_type, void*>::const_iterator p = uids()->find(d);
	if (p == uids()->end())
		return 0;
	return p->second;
}

void* Uid::object() { return object(_id); }
*/

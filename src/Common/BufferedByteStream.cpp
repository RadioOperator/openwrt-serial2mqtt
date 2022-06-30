/*
 * BufferedStream.cpp
 *
 *  Created on: 2-sep.-2016
 *      Author: lieven2
 */

#include <BufferedByteStream.h>

BufferedByteStream::BufferedByteStream(uint32_t size) :
		_rxd(size), _txd(size) {

}

BufferedByteStream::~BufferedByteStream() {

}

Erc BufferedByteStream::write(uint8_t b) {
	return _txd.write(b);
	return E_OK;
}

Erc BufferedByteStream::write(Bytes& bytes) {
	Erc erc;
	bytes.offset(0);
	if (!_txd.hasSpace(bytes.length())) {
		flush();
		return ENOBUFS;
	}
	while (bytes.hasData()) {
		erc = write(bytes.read());
		if (erc) {
			flush();
			return erc;
		}
	}
	flush();
	return E_OK;
}

bool BufferedByteStream::hasSpace() {
	return _txd.hasSpace();
}

bool BufferedByteStream::hasSpace(uint32_t sp) {
	return _txd.hasSpace(sp);
}

bool BufferedByteStream::hasData() {
	return _rxd.hasData();
}

bool BufferedByteStream::hasToSend() {
	return _txd.hasData();
}

uint8_t BufferedByteStream::toSend() {
	return _txd.read();
}

uint8_t BufferedByteStream::read() {
	return _rxd.read();
}

Erc BufferedByteStream::read(Bytes& bytes) {
	while (hasData())
		bytes.write(read());
	return E_OK;
}

bool BufferedByteStream::canReceive() {
	return _rxd.hasSpace();
}
void BufferedByteStream::receive(uint8_t data) {
	_rxd.write(data);
}


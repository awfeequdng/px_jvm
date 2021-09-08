//
// Created by pxcai on 2021/9/8.
//

#include "classFileStream.hh"

void ClassFileStream::truncated_file_error() {
//    THROW_MSG("Truncated class file");
}

ClassFileStream::ClassFileStream(u1* buffer, int length, char* source) {
    _buffer_start = buffer;
    _buffer_end   = buffer + length;
    _current      = buffer;
    _source       = source;
    _need_verify  = false;
}

u1 ClassFileStream::get_u1() {
    if (_need_verify) {
        guarantee_more(1);
    } else {
        assertm(1 <= _buffer_end - _current, "buffer overflow");
    }
    return *_current++;
}

u2 ClassFileStream::get_u2() {
    if (_need_verify) {
        guarantee_more(2);
    } else {
        assertm(2 <= _buffer_end - _current, "buffer overflow");
    }
    return get_u2_fast();
}

u4 ClassFileStream::get_u4() {
    if (_need_verify) {
        guarantee_more(4);
    } else {
        assertm(4 <= _buffer_end - _current, "buffer overflow");
    }
    return get_u4_fast();
}

u8 ClassFileStream::get_u8() {
    if (_need_verify) {
        guarantee_more(8);
    } else {
        assertm(8 <= _buffer_end - _current, "buffer overflow");
    }
    return get_u8_fast();
}

void ClassFileStream::skip_u1(int length) {
    if (_need_verify) {
        guarantee_more(length);
    }
    _current += length;
}

void ClassFileStream::skip_u2(int length) {
    if (_need_verify) {
        guarantee_more(length * 2);
    }
    _current += length * 2;
}

void ClassFileStream::skip_u4(int length) {
    if (_need_verify) {
        guarantee_more(length * 4);
    }
    _current += length * 4;
}
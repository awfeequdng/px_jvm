//
// Created by pxcai on 2021/9/8.
//
#include "top.hh"

class ClassFileStream {
private:
    u1*   _buffer_start; // Buffer bottom
    u1*   _buffer_end;   // Buffer top (one past last element)
    u1*   _current;      // Current buffer position
    char* _source;       // Source of stream (directory name, ZIP/JAR archive name)
    bool  _need_verify;  // True if verification is on for the class file

    void truncated_file_error();

public:
    // Constructor
    ClassFileStream(u1* buffer, int length, char* source);

    // Buffer access
    u1* buffer() const           { return _buffer_start; }
    int length() const           { return _buffer_end - _buffer_start; }
    u1* current() const          { return _current; }
    void set_current(u1* pos)    { _current = pos; }
    char* source() const         { return _source; }
    void set_verify(bool flag)   { _need_verify = flag; }

    void check_truncated_file(bool b) {
        if (b) {
            truncated_file_error();
        }
    }

    void guarantee_more(int size) {
        size_t remaining = (size_t)(_buffer_end - _current);
        unsigned int usize = (unsigned int)size;
//        check_truncated_file(usize > remaining);
    }

    // Read u1 from stream
    u1 get_u1();
    u1 get_u1_fast() {
        return *_current++;
    }

    // Read u2 from stream
    u2 get_u2();
    u2 get_u2_fast() {
        u2 res = *(u2*)(_current);
        _current += 2;
        return res;
    }

    // Read u4 from stream
    u4 get_u4();
    u4 get_u4_fast() {
        u4 res = *(u4*)(_current);
        _current += 4;
        return res;
    }

    // Read u8 from stream
    u8 get_u8();
    u8 get_u8_fast() {
        u8 res = *(u8*)(_current);
        _current += 8;
        return res;
    }

    // Get direct pointer into stream at current position.
    // Returns NULL if length elements are not remaining. The caller is
    // responsible for calling skip below if buffer contents is used.
    u1* get_u1_buffer() {
        return _current;
    }

    u2* get_u2_buffer() {
        return (u2*) _current;
    }

    // Skip length u1 or u2 elements from stream
    void skip_u1(int length);
    void skip_u1_fast(int length) {
        _current += length;
    }

    void skip_u2(int length);
    void skip_u2_fast(int length) {
        _current += 2 * length;
    }

    void skip_u4(int length);
    void skip_u4_fast(int length) {
        _current += 4 * length;
    }

    // Tells whether eos is reached
    bool at_eos() const { return _current == _buffer_end; }
};

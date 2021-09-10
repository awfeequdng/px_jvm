//
// Created by pxcai on 2021/9/9.
//
#pragma once
#include "top.hh"
#include "oop.hh"
#include "universe.hh"

class arrayOopDesc : public oopDesc {
private:
    // Interpreter/Compiler offsets

    // Header size computation.
    // The header is considered the oop part of this type plus the length.
    // Returns the aligned header_size_in_bytes.  This is not equivalent to
    // sizeof(arrayOopDesc) which should not appear in the code.
    static int header_size_in_bytes() {
        size_t hs = align_size_up(length_offset_in_bytes() + sizeof(int),
                                  HeapWordSize);
        return hs;
    }
public:

    static int length_offset_in_bytes() {
        return sizeof(arrayOopDesc);
    }

    // Returns the offset of the first element.
    static int base_offset_in_bytes(BasicType type) {
        return header_size(type) * HeapWordSize;
    }

    // Should only be called with constants as argument
    // (will not constant fold otherwise)
    // Returns the header size in words aligned to the requirements of the
    // array object type.
    static int header_size(BasicType type) {
        size_t typesize_in_bytes = header_size_in_bytes();
        return (int)(Universe::element_type_should_be_aligned(type)
        ? align_object_offset(typesize_in_bytes/HeapWordSize)
        : typesize_in_bytes/HeapWordSize);
    }

    // Returns the address of the first element.
    void* base(BasicType type) const {
        return (void*) (((intptr_t) this) + base_offset_in_bytes(type));
    }

    // Tells whether index is within bounds.
    bool is_within_bounds(int index) const        { return 0 <= index && index < length(); }

    // Accessors for instance variable which is not a C++ declared nonstatic
    // field.
    int length() const {
        return *(int*)(((intptr_t)this) + length_offset_in_bytes());
    }

    void set_length(int length) {
        *(int*)(((intptr_t)this) + length_offset_in_bytes()) = length;
    }

};
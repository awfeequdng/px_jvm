//
// Created by pxcai on 2021/9/10.
//
#pragma once
#include "top.hh"
#include "oop.hh"
class instanceOopDesc : public oopDesc {
public:
    // aligned header size.
    static int header_size() { return sizeof(instanceOopDesc)/HeapWordSize; }

    static int base_offset_in_bytes() {
        return sizeof(instanceOopDesc);
    }

    static bool contains_field_offset(int offset, int nonstatic_field_size) {
        int base_in_bytes = base_offset_in_bytes();
        return (offset >= base_in_bytes &&
        (offset-base_in_bytes) < nonstatic_field_size * heapOopSize);
    }
};

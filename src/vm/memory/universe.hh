//
// Created by pxcai on 2021/9/10.
//
#pragma once

#include "globalDefinitions.hh"
class Universe {
public:
    // Check whether an element of a typeArrayOop with the given type must be
    // aligned 0 mod 8.  The typeArrayOop itself must be aligned at least this
    // strongly.
    static inline bool element_type_should_be_aligned(BasicType type) {
        return type == T_DOUBLE || type == T_LONG;
    }

    // Check whether an object field (static/non-static) of the given type must be aligned 0 mod 8.
    static inline bool field_type_should_be_aligned(BasicType type) {
        return type == T_DOUBLE || type == T_LONG;
    }

};
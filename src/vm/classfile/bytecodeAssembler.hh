//
// Created by pxcai on 2021/9/8.
//
#pragma once
#include "top.hh"

class BytecodeCPEntry {
public:
    enum tag {
        ERROR_TAG,
        UTF8,
        KLASS,
        STRING,
        NAME_AND_TYPE,
        METHODREF
    };

    u1 _tag;
    union {
        Symbol* utf8;
        u2 klass;
        u2 string;
        struct {
            u2 name_index;
            u2 type_index;
        } name_and_type;
        struct {
            u2 class_index;
            u2 name_and_type_index;
        } methodref;
        uintptr_t hash;
    } _u;

    BytecodeCPEntry() : _tag(ERROR_TAG) { _u.hash = 0; }
    BytecodeCPEntry(u1 tag) : _tag(tag) { _u.hash = 0; }

    static BytecodeCPEntry utf8(Symbol* symbol) {
        BytecodeCPEntry bcpe(UTF8);
        bcpe._u.utf8 = symbol;
        return bcpe;
    }

    static BytecodeCPEntry klass(u2 index) {
        BytecodeCPEntry bcpe(KLASS);
        bcpe._u.klass = index;
        return bcpe;
    }

    static BytecodeCPEntry string(u2 index) {
        BytecodeCPEntry bcpe(STRING);
        bcpe._u.string = index;
        return bcpe;
    }

    static BytecodeCPEntry name_and_type(u2 name, u2 type) {
        BytecodeCPEntry bcpe(NAME_AND_TYPE);
        bcpe._u.name_and_type.name_index = name;
        bcpe._u.name_and_type.type_index = type;
        return bcpe;
    }

    static BytecodeCPEntry methodref(u2 class_index, u2 nat) {
        BytecodeCPEntry bcpe(METHODREF);
        bcpe._u.methodref.class_index = class_index;
        bcpe._u.methodref.name_and_type_index = nat;
        return bcpe;
    }

    static bool equals(BytecodeCPEntry const& e0, BytecodeCPEntry const& e1) {
        return e0._tag == e1._tag && e0._u.hash == e1._u.hash;
    }

    static unsigned hash(BytecodeCPEntry const& e0) {
        return (unsigned)(e0._tag ^ e0._u.hash);
    }
};

class BytecodeConstantPool {

};

class BytecodeAssembler {

};


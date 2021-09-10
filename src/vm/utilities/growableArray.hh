//
// Created by pxcai on 2021/9/9.
//
#pragma once
#include "arena.hh"

class GenericGrowableArray {
protected:
    int _len;
    int _max;
    Arena *_arena;

    // Where are we going to allocate memory?
    bool on_C_heap() { return _arena == (Arena*)1; }
    bool on_stack () { return _arena == NULL; }
    bool on_arena () { return _arena >  (Arena*)1; }
};
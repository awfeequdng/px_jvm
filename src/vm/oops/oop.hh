//
// Created by pxcai on 2021/9/8.
//
#pragma once
#include "oopsHierarchy.hh"
#include "klass.hh"

class oopDesc {
private:
    volatile markOop    _mark;
    Klass* _klass;
};

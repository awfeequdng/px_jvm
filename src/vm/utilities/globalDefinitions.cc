//
// Created by pxcai on 2021/9/8.
//

#include "globalDefinitions.hh"

constexpr bool is_power_of_2(std::size_t n) { return n && !(n & (n - 1)); }

// Info for oops within a java object.  Defaults are zero so
// things will break badly if incorrectly initialized.
int heapOopSize        = 0;
int LogBytesPerHeapOop = 0;
int LogBitsPerHeapOop  = 0;
int BytesPerHeapOop    = 0;
int BitsPerHeapOop     = 0;

void basic_types_init() {
//    assertm(min_intx ==  (intx)CONST64(0x8000000000000000), "correct constant");
//    assertm(max_intx ==  CONST64(0x7FFFFFFFFFFFFFFF), "correct constant");
//    assertm(max_uintx == CONST64(0xFFFFFFFFFFFFFFFF), "correct constant");
//    assertm( 8 == sizeof( intx),      "wrong size for basic type");
    assertm( 8 == sizeof( jobject),   "wrong size for basic type");

    assertm( (~max_juint) == 0,  "max_juint has all its bits");
//    assertm( (~max_uintx) == 0,  "max_uintx has all its bits");
    assertm( (~max_julong) == 0, "max_julong has all its bits");
    assertm( 1 == sizeof( jbyte),     "wrong size for basic type");
    assertm( 2 == sizeof( jchar),     "wrong size for basic type");
    assertm( 2 == sizeof( jshort),    "wrong size for basic type");
    assertm( 4 == sizeof( juint),     "wrong size for basic type");
    assertm( 4 == sizeof( jint),      "wrong size for basic type");
    assertm( 1 == sizeof( jboolean),  "wrong size for basic type");
    assertm( 8 == sizeof( jlong),     "wrong size for basic type");
    assertm( 4 == sizeof( jfloat),    "wrong size for basic type");
    assertm( 8 == sizeof( jdouble),   "wrong size for basic type");
    assertm( 1 == sizeof( u1),        "wrong size for basic type");
    assertm( 2 == sizeof( u2),        "wrong size for basic type");
    assertm( 4 == sizeof( u4),        "wrong size for basic type");

    // These are assumed, e.g., when filling HeapWords with juints.
    assertm(is_power_of_2(sizeof(juint)), "juint must be power of 2");
    assertm(is_power_of_2(HeapWordSize), "HeapWordSize must be power of 2");
    assertm((size_t)HeapWordSize >= sizeof(juint),
           "HeapWord should be at least as large as juint");
    assertm(sizeof(NULL) == sizeof(char*), "NULL must be same size as pointer");

    heapOopSize        = oopSize;
    LogBytesPerHeapOop = LogBytesPerWord;
    LogBitsPerHeapOop  = LogBitsPerWord;
    BytesPerHeapOop    = BytesPerWord;
    BitsPerHeapOop     = BitsPerWord;

//    _type2aelembytes[T_OBJECT] = heapOopSize;
//    _type2aelembytes[T_ARRAY]  = heapOopSize;
}
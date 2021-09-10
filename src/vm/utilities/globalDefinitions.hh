//
// Created by pxcai on 2021/9/8.
//
#pragma once
#include <cstddef>
#include <cassert>

#define assertm(exp, msg) assert(((void)msg, exp))

class _jobject {};
class _jclass : public _jobject {};

typedef _jobject *jobject;
typedef _jclass *jclass;

typedef signed char     s_char;
typedef unsigned char   u_char;
typedef signed short    s_short;
typedef unsigned short  u_short;

typedef u_char*       address;

typedef unsigned char       jboolean;

typedef unsigned char       jubyte;
typedef unsigned short      jushort;
typedef unsigned short      jchar;
typedef unsigned int        juint;
typedef unsigned long long  julong;

typedef signed char         jbyte;
typedef signed short        jshort;
typedef signed int          jint;
typedef signed long long    jlong;

typedef jubyte  u1;
typedef jushort u2;
typedef juint   u4;
typedef julong  u8;

typedef float   jfloat;
typedef double  jdouble;

inline jint    jint_cast   (jfloat  x)           { return *(jint*   )&x; }
inline jlong   jlong_cast  (jdouble x)           { return *(jlong*  )&x; }
inline julong  julong_cast (jdouble x)           { return *(julong* )&x; }

inline jfloat  jfloat_cast (jint    x)           { return *(jfloat* )&x; }
inline jdouble jdouble_cast(jlong   x)           { return *(jdouble*)&x; }

// Build a 64bit integer constant
#define CONST64(x)  (x ## LL)
#define UCONST64(x) (x ## ULL)

typedef jbyte  s1;
typedef jshort s2;
typedef jint   s4;
typedef jlong  s8;

const int LogBytesPerShort   = 1;
const int LogBytesPerInt     = 2;
const int LogBytesPerWord    = 2;
const int LogBytesPerLong    = 3;

const int BytesPerShort      = 1 << LogBytesPerShort;
const int BytesPerInt        = 1 << LogBytesPerInt;
const int BytesPerWord       = 1 << LogBytesPerWord;
const int BytesPerLong       = 1 << LogBytesPerLong;

const int LogBitsPerByte     = 3;
const int LogBitsPerShort    = LogBitsPerByte + LogBytesPerShort;
const int LogBitsPerInt      = LogBitsPerByte + LogBytesPerInt;
const int LogBitsPerWord     = LogBitsPerByte + LogBytesPerWord;
const int LogBitsPerLong     = LogBitsPerByte + LogBytesPerLong;

const int BitsPerByte        = 1 << LogBitsPerByte;
const int BitsPerShort       = 1 << LogBitsPerShort;
const int BitsPerInt         = 1 << LogBitsPerInt;
const int BitsPerWord        = 1 << LogBitsPerWord;
const int BitsPerLong        = 1 << LogBitsPerLong;

const int WordAlignmentMask  = (1 << LogBytesPerWord) - 1;
const int LongAlignmentMask  = (1 << LogBytesPerLong) - 1;

const int longSize           = sizeof(jlong);
const int jintSize           = sizeof(jint);
const int size_tSize         = sizeof(size_t);

const int BitsPerJavaInteger = 32;
const int BitsPerJavaLong    = 64;
const int BitsPerSize_t      = size_tSize * BitsPerByte;

const jint min_jint = (jint)1 << (sizeof(jint) * BitsPerByte-1); // 0x80000000 == smallest jint
const jint max_jint = (juint)min_jint - 1;                     // 0x7FFFFFFF == largest jint
const jlong min_jlong = CONST64(0x8000000000000000);
const jlong max_jlong = CONST64(0x7fffffffffffffff);

const jubyte  max_jubyte  = (jubyte)-1;  // 0xFF       largest jubyte
const jushort max_jushort = (jushort)-1; // 0xFFFF     largest jushort
const juint   max_juint   = (juint)-1;   // 0xFFFFFFFF largest juint
const julong  max_julong  = (julong)-1;  // 0xFF....FF largest julong

const size_t K                  = 1024;
const size_t M                  = K*K;
const size_t G                  = M*K;

// Constants for converting from a base unit to milli-base units.  For
// example from seconds to milliseconds and microseconds

const int MILLIUNITS    = 1000;         // milli units per base unit
const int MICROUNITS    = 1000000;      // micro units per base unit
const int NANOUNITS     = 1000000000;   // nano units per base unit

const jlong NANOSECS_PER_SEC      = CONST64(1000000000);
const jint  NANOSECS_PER_MILLISEC = 1000000;

class HeapWord {
private:
    char* i;
public:
    char* value() { return i; }
};

// HeapWordSize must be 2^LogHeapWordSize.
const int HeapWordSize        = sizeof(HeapWord);
const int HeapWordsPerLong    = BytesPerLong / HeapWordSize;
const int LogHeapWordSize     = 3;
const int LogHeapWordsPerLong = LogBytesPerLong - LogHeapWordSize;

inline const char* proper_unit_for_byte_size(size_t s) {
    if (s >= 10*G) {
        return "G";
    } else if (s >= 10*M) {
        return "M";
    } else if (s >= 10*K) {
        return "K";
    } else {
        return "B";
    }
}

template <class T>
inline T byte_size_in_proper_unit(T s) {
    if (s >= 10*G) {
        return (T)(s/G);
    } else if (s >= 10*M) {
        return (T)(s/M);
    } else if (s >= 10*K) {
        return (T)(s/K);
    } else {
        return s;
    }
}

//----------------------------------------------------------------------------------------------------
// JVM spec restrictions
const int max_method_code_size = 64*K - 1;  // JVM spec, 2nd ed. section 4.8.1 (p.134)

// Default ProtectionDomainCacheSize values
// NOT_LP64(137) LP64_ONLY(2017)
const int defaultProtectionDomainCacheSize = 2017;

//----------------------------------------------------------------------------------------------------
// Default and minimum StringTableSize values
// NOT_LP64(1009) LP64_ONLY(60013)
const int defaultStringTableSize = 60013;
const int minimumStringTableSize = 1009;

const int defaultSymbolTableSize = 20011;
const int minimumSymbolTableSize = 1009;

inline jint low (jlong value)                    { return jint(value); }
inline jint high(jlong value)                    { return jint(value >> 32); }

// the fancy casts are a hopefully portable way
// to do unsigned 32 to 64 bit type conversion
inline void set_low (jlong* value, jint low )    { *value &= (jlong)0xffffffff << 32;
    *value |= (jlong)(julong)(juint)low; }

    inline void set_high(jlong* value, jint high)    { *value &= (jlong)(julong)(juint)0xffffffff;
    *value |= (jlong)high       << 32; }

    inline jlong jlong_from(jint h, jint l) {
    jlong result = 0; // initialization to avoid warning
    set_high(&result, h);
    set_low(&result,  l);
    return result;
}

// The expected size in bytes of a cache line, used to pad data structures.
#define DEFAULT_CACHE_LINE_SIZE 64

//----------------------------------------------------------------------------------------------------
// Utility macros for compilers
// used to silence compiler warnings
#define Unused_Variable(var) var

// NOTE: replicated in SA in vm/agent/sun/jvm/hotspot/runtime/BasicType.java
enum BasicType {
    T_BOOLEAN     =  4,
    T_CHAR        =  5,
    T_FLOAT       =  6,
    T_DOUBLE      =  7,
    T_BYTE        =  8,
    T_SHORT       =  9,
    T_INT         = 10,
    T_LONG        = 11,
    T_OBJECT      = 12,
    T_ARRAY       = 13,
    T_VOID        = 14,
    T_ADDRESS     = 15,
    T_NARROWOOP   = 16,
    T_METADATA    = 17,
    T_NARROWKLASS = 18,
    T_CONFLICT    = 19, // for stack value type with conflicting contents
    T_ILLEGAL     = 99
};


inline bool is_java_primitive(BasicType t) {
    return T_BOOLEAN <= t && t <= T_LONG;
}

inline bool is_subword_type(BasicType t) {
    // these guys are processed exactly like T_INT in calling sequences:
    return (t == T_BOOLEAN || t == T_CHAR || t == T_BYTE || t == T_SHORT);
}

inline bool is_signed_subword_type(BasicType t) {
    return (t == T_BYTE || t == T_SHORT);
}

// Convert a char from a classfile signature to a BasicType
inline BasicType char2type(char c) {
    switch( c ) {
        case 'B': return T_BYTE;
        case 'C': return T_CHAR;
        case 'D': return T_DOUBLE;
        case 'F': return T_FLOAT;
        case 'I': return T_INT;
        case 'J': return T_LONG;
        case 'S': return T_SHORT;
        case 'Z': return T_BOOLEAN;
        case 'V': return T_VOID;
        case 'L': return T_OBJECT;
        case '[': return T_ARRAY;
    }
    return T_ILLEGAL;
}


// size in bytes
enum ArrayElementSize {
    T_BOOLEAN_aelem_bytes     = 1,
    T_CHAR_aelem_bytes        = 2,
    T_FLOAT_aelem_bytes       = 4,
    T_DOUBLE_aelem_bytes      = 8,
    T_BYTE_aelem_bytes        = 1,
    T_SHORT_aelem_bytes       = 2,
    T_INT_aelem_bytes         = 4,
    T_LONG_aelem_bytes        = 8,

    T_OBJECT_aelem_bytes      = 8,
    T_ARRAY_aelem_bytes       = 8,
    T_VOID_aelem_bytes        = 0
};


// JavaValue serves as a container for arbitrary Java values.

class JavaValue {

public:
    typedef union JavaCallValue {
        jfloat   f;
        jdouble  d;
        jint     i;
        jlong    l;
        jobject  h;
    } JavaCallValue;

private:
    BasicType _type;
    JavaCallValue _value;

public:
    JavaValue(BasicType t = T_ILLEGAL) { _type = t; }

    JavaValue(jfloat value) {
        _type    = T_FLOAT;
        _value.f = value;
    }

    JavaValue(jdouble value) {
        _type    = T_DOUBLE;
        _value.d = value;
    }

    jfloat get_jfloat() const { return _value.f; }
    jdouble get_jdouble() const { return _value.d; }
    jint get_jint() const { return _value.i; }
    jlong get_jlong() const { return _value.l; }
    jobject get_jobject() const { return _value.h; }
    JavaCallValue* get_value_addr() { return &_value; }
    BasicType get_type() const { return _type; }

    void set_jfloat(jfloat f) { _value.f = f;}
    void set_jdouble(jdouble d) { _value.d = d;}
    void set_jint(jint i) { _value.i = i;}
    void set_jlong(jlong l) { _value.l = l;}
    void set_jobject(jobject h) { _value.h = h;}
    void set_type(BasicType t) { _type = t; }

    jboolean get_jboolean() const { return (jboolean) (_value.i);}
    jbyte get_jbyte() const { return (jbyte) (_value.i);}
    jchar get_jchar() const { return (jchar) (_value.i);}
    jshort get_jshort() const { return (jshort) (_value.i);}

};


template<class T> inline T MAX2(T a, T b)           { return (a > b) ? a : b; }
template<class T> inline T MIN2(T a, T b)           { return (a < b) ? a : b; }
template<class T> inline T MAX3(T a, T b, T c)      { return MAX2(MAX2(a, b), c); }
template<class T> inline T MIN3(T a, T b, T c)      { return MIN2(MIN2(a, b), c); }
template<class T> inline T MAX4(T a, T b, T c, T d) { return MAX2(MAX3(a, b, c), d); }
template<class T> inline T MIN4(T a, T b, T c, T d) { return MIN2(MIN3(a, b, c), d); }

template<class T> inline T ABS(T x)                 { return (x > 0) ? x : -x; }
//
//inline bool is_odd (intx x) { return x & 1;      }
//inline bool is_even(intx x) { return !is_odd(x); }

// This routine takes eight bytes:
inline u8 build_u8_from( u1 c1, u1 c2, u1 c3, u1 c4, u1 c5, u1 c6, u1 c7, u1 c8 ) {
    return  (( u8(c1) << 56 )  &  ( u8(0xff) << 56 ))
    |  (( u8(c2) << 48 )  &  ( u8(0xff) << 48 ))
    |  (( u8(c3) << 40 )  &  ( u8(0xff) << 40 ))
    |  (( u8(c4) << 32 )  &  ( u8(0xff) << 32 ))
    |  (( u8(c5) << 24 )  &  ( u8(0xff) << 24 ))
    |  (( u8(c6) << 16 )  &  ( u8(0xff) << 16 ))
    |  (( u8(c7) <<  8 )  &  ( u8(0xff) <<  8 ))
    |  (( u8(c8) <<  0 )  &  ( u8(0xff) <<  0 ));
}

// This routine takes four bytes:
inline u4 build_u4_from( u1 c1, u1 c2, u1 c3, u1 c4 ) {
    return  (( u4(c1) << 24 )  &  0xff000000)
    |  (( u4(c2) << 16 )  &  0x00ff0000)
    |  (( u4(c3) <<  8 )  &  0x0000ff00)
    |  (( u4(c4) <<  0 )  &  0x000000ff);
}

// And this one works if the four bytes are contiguous in memory:
inline u4 build_u4_from( u1* p ) {
    return  build_u4_from( p[0], p[1], p[2], p[3] );
}

// Ditto for two-byte ints:
inline u2 build_u2_from( u1 c1, u1 c2 ) {
    return  u2((( u2(c1) <<  8 )  &  0xff00)
    |  (( u2(c2) <<  0 )  &  0x00ff));
}

// And this one works if the two bytes are contiguous in memory:
inline u2 build_u2_from( u1* p ) {
    return  build_u2_from( p[0], p[1] );
}

// Ditto for floats:
inline jfloat build_float_from( u1 c1, u1 c2, u1 c3, u1 c4 ) {
    u4 u = build_u4_from( c1, c2, c3, c4 );
    return  *(jfloat*)&u;
}

inline jfloat build_float_from( u1* p ) {
    u4 u = build_u4_from( p );
    return  *(jfloat*)&u;
}


// now (64-bit) longs

inline jlong build_long_from( u1 c1, u1 c2, u1 c3, u1 c4, u1 c5, u1 c6, u1 c7, u1 c8 ) {
    return  (( jlong(c1) << 56 )  &  ( jlong(0xff) << 56 ))
    |  (( jlong(c2) << 48 )  &  ( jlong(0xff) << 48 ))
    |  (( jlong(c3) << 40 )  &  ( jlong(0xff) << 40 ))
    |  (( jlong(c4) << 32 )  &  ( jlong(0xff) << 32 ))
    |  (( jlong(c5) << 24 )  &  ( jlong(0xff) << 24 ))
    |  (( jlong(c6) << 16 )  &  ( jlong(0xff) << 16 ))
    |  (( jlong(c7) <<  8 )  &  ( jlong(0xff) <<  8 ))
    |  (( jlong(c8) <<  0 )  &  ( jlong(0xff) <<  0 ));
}

inline jlong build_long_from( u1* p ) {
    return  build_long_from( p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7] );
}


// Doubles, too!
inline jdouble build_double_from( u1 c1, u1 c2, u1 c3, u1 c4, u1 c5, u1 c6, u1 c7, u1 c8 ) {
    jlong u = build_long_from( c1, c2, c3, c4, c5, c6, c7, c8 );
    return  *(jdouble*)&u;
}

inline jdouble build_double_from( u1* p ) {
    jlong u = build_long_from( p );
    return  *(jdouble*)&u;
}


// Portable routines to go the other way:

inline void explode_short_to( u2 x, u1& c1, u1& c2 ) {
    c1 = u1(x >> 8);
    c2 = u1(x);
}

inline void explode_short_to( u2 x, u1* p ) {
    explode_short_to( x, p[0], p[1]);
}

inline void explode_int_to( u4 x, u1& c1, u1& c2, u1& c3, u1& c4 ) {
    c1 = u1(x >> 24);
    c2 = u1(x >> 16);
    c3 = u1(x >>  8);
    c4 = u1(x);
}

inline void explode_int_to( u4 x, u1* p ) {
    explode_int_to( x, p[0], p[1], p[2], p[3]);
}


// Pack and extract shorts to/from ints:

inline int extract_low_short_from_int(jint x) {
    return x & 0xffff;
}

inline int extract_high_short_from_int(jint x) {
    return (x >> 16) & 0xffff;
}

inline int build_int_from_shorts( jushort low, jushort high ) {
    return ((int)((unsigned int)high << 16) | (unsigned int)low);
}

// Signed variants of alignment helpers.  There are two versions of each, a macro
// for use in places like enum definitions that require compile-time constant
// expressions and a function for all other places so as to get type checking.
//类似round_to，但是不要求alignment是2的倍数
#define align_size_up_(size, alignment) (((size) + ((alignment) - 1)) & ~((alignment) - 1))

inline bool is_size_aligned(size_t size, size_t alignment) {
    return align_size_up_(size, alignment) == size;
}

inline intptr_t align_size_up(intptr_t size, intptr_t alignment) {
    return align_size_up_(size, alignment);
}

#define align_size_down_(size, alignment) ((size) & ~((alignment) - 1))

inline intptr_t align_size_down(intptr_t size, intptr_t alignment) {
    return align_size_down_(size, alignment);
}

#define is_size_aligned_(size, alignment) ((size) == (align_size_up_(size, alignment)))


// Pad out certain offsets to jlong alignment, in HeapWord units.
inline intptr_t align_object_offset(intptr_t offset) {
    return align_size_up(offset, HeapWordsPerLong);
}